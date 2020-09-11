// ======================================================================
// \title  SPWManagerComponentImpl.cpp
// \author vwong
// \brief  cpp file for SPWManager component implementation class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
// ======================================================================


#include "fprime-sphinx-drivers/SPWManager/SPWManagerComponentImpl.hpp"
#include "fprime-sphinx-drivers/SPWManager/SPWRequestStatus.hpp"
#include "fprime-sphinx-drivers/SPWDriver/SPWStatus.hpp"
#include "fprime-sphinx-drivers/SPWDriver/RMAPHeader.hpp"
#include "fprime-sphinx-drivers/Util/SphinxDrvUtil.hpp"
#include "fprime-sphinx-drivers/Include/utils.h"
#include "Fw/Types/BasicTypes.hpp"
#include "Fw/Types/Assert.hpp"
#include <Os/Log.hpp>
#include <string.h> // memset

namespace Drv {

  // ----------------------------------------------------------------------
  // Construction, initialization, and destruction
  // ----------------------------------------------------------------------

  SPWManagerComponentImpl ::
#if FW_OBJECT_NAMES == 1
    SPWManagerComponentImpl(
        const char *const compName
    ) :
      SPWManagerComponentBase(compName),
#else
    SPWManagerImpl(void) :
#endif
      m_dest_addr(0),
      m_dest_key(0),
      m_increment(0),
      m_verify(0),
      m_acknowledge(0),
      m_driver_claimed(false),
      m_errorBucketLimiter(SPW_ERROR_BUCKET_LIMITER_USECS, SPW_ERROR_BUCKET_LIMITER_TOKENS)
  {
  }

  void SPWManagerComponentImpl ::
    init(
        const NATIVE_INT_TYPE queueDepth,
        const NATIVE_INT_TYPE instance
    )
  {
    SPWManagerComponentBase::init(queueDepth, instance);

    // default dest (unknown)
    m_dest_addr = 254;
    m_dest_key = 0;

    // default RMAP options
    m_increment = 1;
    m_verify = 1;
    m_acknowledge = 1;

    // driver unused initially
    m_driver_claimed = false;
  }

  SPWManagerComponentImpl ::
    ~SPWManagerComponentImpl(void)
  {
  }

  // ----------------------------------------------------------------------
  // Handler implementations for user-defined typed input ports
  // ----------------------------------------------------------------------

  I32 SPWManagerComponentImpl ::
    write_handler(
        const NATIVE_INT_TYPE portNum,
        U32 addr,
        U32 num_bytes,
        U8 *buf,
        U32 buf_size,
        U32 timeout
    )
  {
    return this->handleSyncWrite(portNum, addr, num_bytes, buf, buf_size, timeout);
  }

  I32 SPWManagerComponentImpl ::
    read_handler(
        const NATIVE_INT_TYPE portNum,
        U32 addr,
        U32 num_bytes,
        U8 *buf,
        U32 buf_size,
        U32 timeout
    )
  {
    return this->handleSyncRead(portNum, addr, num_bytes, buf, buf_size, timeout);
  }

  I32 SPWManagerComponentImpl ::
    writeAsync_handler(
        const NATIVE_INT_TYPE portNum,
        U32 addr,
        U32 num_bytes,
        U8 *buf,
        U32 buf_size,
        U32 timeout
    )
  {
    FW_ASSERT(buf != NULL);
    FW_ASSERT(num_bytes <= buf_size);

    SPWRequest req = this->initializeRequest(portNum, RMAPHeader::RMAP_WRITE, addr, buf, num_bytes, timeout, true, false);
    I32 status = m_requests.push(req);
    if (status != 0) {
      return SPW_REQUEST_STATUS_QUEUE_FULL;
    }
    return SPW_REQUEST_STATUS_ACCEPTED;
  }

  I32 SPWManagerComponentImpl ::
    readAsync_handler(
        const NATIVE_INT_TYPE portNum,
        U32 addr,
        U32 num_bytes,
        U8 *buf,
        U32 buf_size,
        U32 timeout
    )
  {
    FW_ASSERT(buf != NULL);
    FW_ASSERT(num_bytes <= buf_size);

    SPWRequest req = this->initializeRequest(portNum, RMAPHeader::RMAP_READ, addr, buf, num_bytes, timeout, true, false);
    I32 status = m_requests.push(req);
    if (status != 0) {
      return SPW_REQUEST_STATUS_QUEUE_FULL;
    }
    return SPW_REQUEST_STATUS_ACCEPTED;
  }

  void SPWManagerComponentImpl ::
    resetLink_handler(
        const NATIVE_INT_TYPE portNum
    )
  {
    I32 driverStatus = this->abortAndReset();
    if (driverStatus != SPW_STATUS_SUCCESS) {
      this->logSpaceWireError(driverStatus);
    }
  }

  void SPWManagerComponentImpl::schedIn_handler(
        const NATIVE_INT_TYPE portNum,
        NATIVE_UINT_TYPE context
    )
  {
    const U32 loopBound = SPW_REQUEST_QUEUE_SIZE+1;
    U32 counter = 0;
    while (!m_requests.isEmpty() && counter < loopBound) {
      counter++;

      // if the requests are small, try to finish more than one per schedIn
      SPWRequest& req = m_requests.top();

      I32 driverStatus;
      if (!req.active) {
        I32 claimed = this->claimDriver();
        if (!claimed) {
          // handling a synchronous request at the moment
          break;
        }
        driverStatus = this->startRequest(req);
      }

      if (req.active) {
        driverStatus = this->processRequest(req, SPW_ASYNC_TIMEOUT);
        req.timer++;
      }
      I32 requestStatus = this->evaluateStatus(req, driverStatus);
      if (requestStatus == SPW_REQUEST_STATUS_BUSY) {
        // still working but haven't hit timeout yet, just let it keep going
        break;
      } else {
        // done or hit an error, report it to the client and pop request
        this->reportStatus(req.client_port, requestStatus);
        I32 opStatus = this->m_requests.pop();
        FW_ASSERT(opStatus == 0); // current request should've been at the top
        this->unclaimDriver();
      }
    }
    FW_ASSERT(counter < loopBound);
  }

  I32 SPWManagerComponentImpl ::
    readAsyncDMA_handler(
        const NATIVE_INT_TYPE portNum,
        U32 addr,
        U32 num_bytes,
        U8 *buf,
        U32 buf_size,
        U32 timeout
    )
  {
    FW_ASSERT(buf != NULL);
    // buf needs to be big enough for SPW/RMAP header + crc, aligned to 4 bytes
    FW_ASSERT(U32_MAX - num_bytes >= RMAP_READ_RESPONSE_HDR_SIZE + 4); // overflow check
    FW_ASSERT(num_bytes + RMAP_READ_RESPONSE_HDR_SIZE + 4 <= buf_size);
    // dma reads cannot exceed one transaction
    FW_ASSERT(num_bytes <= MAX_RMAP_PACKET_SIZE);

    SPWRequest req = this->initializeRequest(portNum, RMAPHeader::RMAP_READ, addr, buf, num_bytes, timeout, true, true);
    I32 status = m_requests.push(req);
    if (status != 0) {
      // queue is full
      return SPW_REQUEST_STATUS_QUEUE_FULL;
    }
    return SPW_REQUEST_STATUS_ACCEPTED;
  }

  I32 SPWManagerComponentImpl ::
    setParam_handler(
        const NATIVE_INT_TYPE portNum,
        U8 dest_addr,
        U8 dest_key,
        U8 increment,
        U8 verify,
        U8 acknowledge
    )
  {
    FW_ASSERT(verify <= 1, verify);
    FW_ASSERT(acknowledge <= 1, acknowledge);
    FW_ASSERT(increment <= 1, increment);

    m_dest_addr = dest_addr;
    m_dest_key = dest_key;
    m_verify = verify;
    m_acknowledge = acknowledge;
    m_increment = increment;

    return 0;
  }

  void SPWManagerComponentImpl ::
    PingRecv_handler(
        const NATIVE_INT_TYPE portNum,
        U32 key
    )
  {
      if (this-> isConnected_PingResponse_OutputPort(0))
      {
        this->PingResponse_out(0, key);
      }
  }



  // ----------------------------------------------------------------------
  // Command handler implementations
  // ----------------------------------------------------------------------

  void SPWManagerComponentImpl ::
    SPWMGR_RMAP_WRITE_WORD_cmdHandler(
        const FwOpcodeType opCode,
        const U32 cmdSeq,
        U32 targetAddress,
        U32 value,
        U32 timeout
    )
  {
    I32 requestStatus = this->handleSyncWrite(0, targetAddress, sizeof(value), Drv::wordAsBuf(value), sizeof(value), timeout);

    if (requestStatus == SPW_REQUEST_STATUS_DONE) {
      this->log_ACTIVITY_LO_SPWManager_RMAPWriteResult(targetAddress);
      this->cmdResponse_out(opCode,cmdSeq,Fw::COMMAND_OK);

    } else if (requestStatus == SPW_REQUEST_STATUS_BUSY) {
      this->log_WARNING_LO_SPWManager_Busy();
      this->cmdResponse_out(opCode,cmdSeq,Fw::COMMAND_EXECUTION_ERROR);

    } else {
      this->cmdResponse_out(opCode,cmdSeq,Fw::COMMAND_EXECUTION_ERROR);
    }
  }

  void SPWManagerComponentImpl ::
    SPWMGR_RMAP_READ_WORD_cmdHandler(
        const FwOpcodeType opCode,
        const U32 cmdSeq,
        U32 targetAddress,
        U32 timeout
    )
  {
    U32 value = 0;

    I32 requestStatus = this->handleSyncRead(0, targetAddress, sizeof(value), Drv::wordAsBuf(value), sizeof(value), timeout);

    if (requestStatus == SPW_REQUEST_STATUS_DONE) {
      this->log_ACTIVITY_LO_SPWManager_RMAPReadResult(targetAddress, value);
      this->cmdResponse_out(opCode,cmdSeq,Fw::COMMAND_OK);

    } else if (requestStatus == SPW_REQUEST_STATUS_BUSY) {
      this->log_WARNING_LO_SPWManager_Busy();
      this->cmdResponse_out(opCode,cmdSeq,Fw::COMMAND_EXECUTION_ERROR);

    } else {
      this->cmdResponse_out(opCode,cmdSeq,Fw::COMMAND_EXECUTION_ERROR);
    }
  }

  void SPWManagerComponentImpl ::
    SPWMGR_RESET_LINK_cmdHandler(
        const FwOpcodeType opCode,
        const U32 cmdSeq
    )
  {
    I32 driverStatus = this->abortAndReset();
    if (driverStatus == SPW_STATUS_SUCCESS) {
      this->cmdResponse_out(opCode,cmdSeq,Fw::COMMAND_OK);
    } else {
      this->logSpaceWireError(driverStatus);
      this->cmdResponse_out(opCode,cmdSeq,Fw::COMMAND_EXECUTION_ERROR);
    }
  }

  void SPWManagerComponentImpl ::
    SPWMGR_SET_PARAMS_cmdHandler(
        const FwOpcodeType opCode,
        const U32 cmdSeq,
        U8 destinationAddress,
        U8 destinationKey,
        U8 increment,
        U8 verify,
        U8 acknowledge
    )
  {
    // TODO
    if (verify > 1 || acknowledge > 1 || increment > 1) {
      this->cmdResponse_out(opCode,cmdSeq,Fw::COMMAND_VALIDATION_ERROR);
      return;
    }

    m_dest_addr = destinationAddress;
    m_dest_key = destinationKey;
    m_verify = verify;
    m_acknowledge = acknowledge;
    m_increment = increment;

    this->cmdResponse_out(opCode,cmdSeq,Fw::COMMAND_OK);
  }

  // ----------------------------------------------------------------------
  // Private supporting functions
  // ----------------------------------------------------------------------

  SPWRequest SPWManagerComponentImpl::initializeRequest(
      NATIVE_INT_TYPE client_port,
      RMAPHeader::RMAPCommandType cmd,
      U32 addr,
      U8* buf,
      U32 num_bytes,
      U32 timeout,
      bool async,
      bool dma)
  {
    FW_ASSERT(buf != NULL);

    SPWRequest req;

    req.client_port = client_port;
    req.command = cmd;
    req.dest_addr = m_dest_addr;
    req.dest_key = m_dest_key;
    req.target_addr = addr;
    req.client_buf = buf;
    req.client_length = num_bytes;
    req.async = async;
    if (dma) {
      req.work_buf = buf;
    } else {
      req.work_buf = m_work_buf;
    }
    req.increment = m_increment;
    req.verify = m_verify;
    req.acknowledge = m_acknowledge;
    req.timer = 0;
    req.timeout = timeout;
    req.offset = 0;
    if (dma) {
      req.transaction_length = req.client_length;
    } else {
      req.transaction_length = FW_MIN(req.client_length, SPW_WORK_BUF_DATA_SIZE);
    }
    req.active = false;
    req.dma = dma;

    return req;
  }

  I32 SPWManagerComponentImpl::handleSyncWrite(U32 portNum, U32 addr, U32 num_bytes, U8 *buf, U32 buf_size, U32 timeout)
  {
    FW_ASSERT(buf != NULL);
    FW_ASSERT(num_bytes <= buf_size);

    I32 claimed = this->claimDriver();
    if (!claimed) {
      return SPW_REQUEST_STATUS_BUSY;
    }

    SPWRequest req = this->initializeRequest(portNum, RMAPHeader::RMAP_WRITE, addr, buf, num_bytes, timeout, false, false);
    I32 driverStatus = this->startRequest(req);
    if (driverStatus == SPW_STATUS_SUCCESS) {
      driverStatus = this->processRequest(req, timeout);
    }
    this->unclaimDriver();

    I32 requestStatus = this->evaluateStatus(req, driverStatus);
    return requestStatus;
  }

  I32 SPWManagerComponentImpl::handleSyncRead(U32 portNum, U32 addr, U32 num_bytes, U8 *buf, U32 buf_size, U32 timeout)
  {
    FW_ASSERT(buf != NULL);
    FW_ASSERT(num_bytes <= buf_size);

    I32 claimed = this->claimDriver();
    if (!claimed) {
      return SPW_REQUEST_STATUS_BUSY;
    }

    SPWRequest req = this->initializeRequest(portNum, RMAPHeader::RMAP_READ, addr, buf, num_bytes, timeout, false, false);
    I32 driverStatus = this->startRequest(req);
    if (driverStatus == SPW_STATUS_SUCCESS) {
      driverStatus = this->processRequest(req, timeout);
    }
    this->unclaimDriver();

    I32 requestStatus = this->evaluateStatus(req, driverStatus);
    return requestStatus;
  }

  I32 SPWManagerComponentImpl::startRequest(SPWRequest& req)
  {
    // if previously in sending or error condition, perform reset
    I32 driverStatus = this->driverGetStatus_out(0);
    if (driverStatus != SPW_STATUS_SUCCESS) {
      driverStatus = this->driverReset_out(0);
      if (driverStatus != SPW_STATUS_SUCCESS) {
        return driverStatus;
      }
    }

    // copy write data into work buffer
    if (req.command == RMAPHeader::RMAP_WRITE) {
      memcpy(req.work_buf, req.client_buf, req.transaction_length);
    }

    // send command
    driverStatus = this->sendCommand(req);
    if (driverStatus == SPW_STATUS_SUCCESS) {
      // mark request as active, if command successfully sent
      req.active = true;
    }

    return driverStatus;
  }

  I32 SPWManagerComponentImpl::sendCommand(const SPWRequest& req)
  {
    I32 status = 0;
    if (req.command == RMAPHeader::RMAP_WRITE) {
      status = this->driverWriteRMAP_out(0,
          req.dest_addr,
          req.dest_key,
          req.target_addr,
          req.work_buf,
          req.transaction_length,
          req.increment,
          req.verify,
          req.acknowledge);
    } else if (req.command == RMAPHeader::RMAP_READ) {
      status = this->driverReadRMAP_out(0,
          req.dest_addr,
          req.dest_key,
          req.target_addr,
          req.work_buf,
          req.transaction_length,
          req.increment);
    } else {
      FW_ASSERT(0);
    }

    return status;
  }

  I32 SPWManagerComponentImpl::processRequest(SPWRequest& req, U32 timeout)
  {
    U32 timer = 0;
    if (timeout == 0) {
      timeout = U32_MAX;
    }

    I32 driverStatus;
    do {
      driverStatus = this->driverGetStatus_out(0);

      if (driverStatus == SPW_STATUS_SUCCESS) {
        FW_ASSERT(req.transaction_length > 0);
        FW_ASSERT(req.transaction_length <= req.client_length - req.offset);

        // transaction finished, advance state
        if (req.command == RMAPHeader::RMAP_READ) {
          // read request, post-process read data
          if (!req.dma) {
            // saved into work buffer; copy received data into client buffer
            memcpy(req.client_buf + req.offset, req.work_buf + RMAP_READ_RESPONSE_HDR_SIZE, req.transaction_length);
          }
        }
        req.offset += req.transaction_length;
        if (req.increment) {
          req.target_addr += req.transaction_length;
        }

        // check if more transactions are needed
        if (req.offset != req.client_length) {
          FW_ASSERT(!req.dma); // dma requests cannot exceed one transaction
          // not all data received yet, process next chunk
          req.transaction_length = FW_MIN(req.client_length - req.offset, SPW_WORK_BUF_DATA_SIZE);
          if (req.command == RMAPHeader::RMAP_WRITE) {
            // if writing, copy client data into work buffer
            memcpy(req.work_buf, req.client_buf + req.offset, req.transaction_length);
          }
          driverStatus = this->sendCommand(req);
          if (driverStatus == SPW_STATUS_SUCCESS) {
            driverStatus = SPW_STATUS_SENDING;
          }
        }
      }

      timer++;
    } while (timer < timeout && (driverStatus == SPW_STATUS_SENDING || driverStatus == SPW_STATUS_RECEIVING));

    return driverStatus;
  }

  I32 SPWManagerComponentImpl::evaluateStatus(const SPWRequest& req, I32 driverStatus)
  {
    I32 requestStatus;

    switch (driverStatus) {

      case SPW_STATUS_SUCCESS:
        // success
        requestStatus = SPW_REQUEST_STATUS_DONE;
        break;

      case SPW_STATUS_RECEIVING:
      case SPW_STATUS_SENDING:
        // possibly timed out; see if its async and hasn't hit timeout yet
        if (req.async && (req.timeout == 0 || req.timer < req.timeout)) {
          requestStatus = SPW_REQUEST_STATUS_BUSY;
        } else {
          requestStatus = SPW_REQUEST_STATUS_TIMEDOUT;
          if (this->m_errorBucketLimiter.trigger(this->getTime())) {
            this->logSpaceWireTimeout(req, driverStatus);
          }
        }
        break;

      default:
        // some kind of error
        if (this->m_errorBucketLimiter.trigger(this->getTime())) {
          this->logSpaceWireError(driverStatus);
        }
        requestStatus = SPW_REQUEST_STATUS_ERROR;
        break;
    }

    return requestStatus;
  }

  void SPWManagerComponentImpl::logSpaceWireError(I32 driverStatus)
  {
    FW_ASSERT(driverStatus != SPW_STATUS_SUCCESS &&
              driverStatus != SPW_STATUS_SENDING &&
              driverStatus != SPW_STATUS_RECEIVING);

    switch (driverStatus) {

      case SPW_STATUS_ERR_INIT:
        this->log_WARNING_HI_SPWManager_SpaceWireInitializationError(driverStatus);
        break;

      case SPW_STATUS_ERR_DISCONNECTED:
        this->log_WARNING_HI_SPWManager_SpaceWireLinkDisconnected();
        break;

      default:
        SpaceWireError_status arg = toSpaceWireError_status(driverStatus);
        this->log_WARNING_HI_SPWManager_SpaceWireError(arg, driverStatus);
        break;
    }
  }

  void SPWManagerComponentImpl::logSpaceWireTimeout(const SPWRequest& req, I32 driverStatus)
  {
    FW_ASSERT(driverStatus == SPW_STATUS_SENDING ||
              driverStatus == SPW_STATUS_RECEIVING);

    // get cmd enum
    FW_ASSERT(req.command == RMAPHeader::RMAP_WRITE || req.command == RMAPHeader::RMAP_READ,
              static_cast<I32>(req.command));
    SpaceWireTransactionTimeout_command cmd = SYNC_RMAP_WRITE;
    if (req.command == RMAPHeader::RMAP_WRITE) {
      cmd = req.async ? ASYNC_RMAP_WRITE : SYNC_RMAP_WRITE;
    } else {
      cmd = req.async ? ASYNC_RMAP_READ : SYNC_RMAP_READ;
    }

    // get status enum
    FW_ASSERT(driverStatus == SPW_STATUS_SENDING || driverStatus == SPW_STATUS_RECEIVING, driverStatus);
    SpaceWireTransactionTimeout_status status = TRANSACTION_SENDING;
    if (driverStatus == SPW_STATUS_SENDING) {
      status = TRANSACTION_SENDING;
    } else {
      status = TRANSACTION_RECEIVING;
    }

    // log evr
    // TODO: split sync and async evr
    this->log_WARNING_HI_SPWManager_SpaceWireTransactionTimeout(
        req.timeout,
        cmd,
        req.target_addr,
        status);
  }

  bool SPWManagerComponentImpl::claimDriver()
  {
    m_mutex.lock();
    bool avail = !m_driver_claimed;
    if (avail) {
      m_driver_claimed = true;
    }
    m_mutex.unLock();
    return avail;
  }

  void SPWManagerComponentImpl::unclaimDriver()
  {
    m_mutex.lock();
    FW_ASSERT(m_driver_claimed == true);
    m_driver_claimed = false;
    m_mutex.unLock();
  }

  void SPWManagerComponentImpl::reportStatus(I32 portNum, I32 status)
  {
    if (this->isConnected_statusOut_OutputPort(0)) {
      this->statusOut_out(portNum, status);
    }
  }

  I32 SPWManagerComponentImpl::abortAndReset()
  {
    // lock the guarded port mutex
    this->lock();

    // at this point, the SPWManager task should have full control over all of
    // SPWManager's data, and no other ports can be running

    // reset the port to cut off any current transactions / DMA operations
    I32 driverStatus = this->driverReset_out(0);

    // abort existing requests
    U32 numAborted = 0;
    for (U32 i = 0; i < SPW_REQUEST_QUEUE_SIZE+1; i++) {
      if (this->m_requests.isEmpty()) {
        break;
      }
      SPWRequest& req = m_requests.top();
      this->reportStatus(req.client_port, SPW_REQUEST_STATUS_ABORTED);
      numAborted++;
      I32 status = m_requests.pop();
      FW_ASSERT(status == 0, status); // shouldn't have been empty
    }

    // evr
    this->log_ACTIVITY_LO_SPWManager_ResetLink(numAborted);

    // unclaim driver if it was claimed
    if (this->m_driver_claimed) {
      this->unclaimDriver();
    }

    this->unLock();
    return driverStatus;
  }

  SPWManagerComponentImpl::SpaceWireError_status SPWManagerComponentImpl::toSpaceWireError_status(I32 status)
  {
    switch (status) {
      case 3: return ERR_INIT;
      case 4: return ERR_DISCONNECTED;
      case 5: return ERR_TX_LINK;
      case 6: return ERR_RX_TRUNCATED;
      case 7: return ERR_RX_DATA_CRC;
      case 8: return ERR_RX_HDR_CRC;
      case 9: return ERR_RX_EEP;
      case 10: return ERR_RX_DESERIALIZATION;
      case 11: return ERR_RX_UNEXPECTED_REPLY;
      case 12: return ERR_RMAP_TRANS_ID_MISMATCH;
      case 13: return ERR_RMAP_DATA_LEN_MISMATCH;
      case 14: return ERR_RMAP_STAT_GENERAL;
      case 15: return ERR_RMAP_STAT_UNUSED_TYPE;
      case 16: return ERR_RMAP_STAT_INVALID_KEY;
      case 17: return ERR_RMAP_STAT_INVALID_DATA_CRC;
      case 18: return ERR_RMAP_STAT_EARLY_EOP;
      case 19: return ERR_RMAP_STAT_CARGO_TOO_LARGE;
      case 20: return ERR_RMAP_STAT_EEP;
      case 21: return ERR_RMAP_STAT_VERIFY_BUFFER_OVERRUN;
      case 22: return ERR_RMAP_STAT_CMD_UNAUTHORIZED;
      case 23: return ERR_RMAP_STAT_DATA_LEN_ERR;
      case 24: return ERR_RMAP_STAT_INVALID_DEST_ADDR;
      default: break;
    }
    return ERR_RMAP_STAT_UNKNOWN;
  }

} // end namespace Drv
