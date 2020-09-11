// ====================================================================== 
// \title  SPWDriverComponentImpl.cpp
// \author vwong
// \brief  cpp file for SPWDriver component implementation class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
// ====================================================================== 


#include "fprime-sphinx-drivers/SPWDriver/SPWDriverComponentImpl.hpp"
#include "fprime-sphinx-drivers/SPWDriver/SPWStatus.hpp"
#include "fprime-sphinx-drivers/Util/SphinxDrvUtil.hpp"
#include "fprime-sphinx-drivers/Include/utils.h"
#include "fprime-sphinx-drivers/Include/config.hpp"
#include "Fw/Types/BasicTypes.hpp"
#include "Fw/Types/Assert.hpp"
#include <string.h> // memset

namespace Drv {

  // ----------------------------------------------------------------------
  // Construction, initialization, and destruction 
  // ----------------------------------------------------------------------

  SPWDriverComponentImpl ::
#if FW_OBJECT_NAMES == 1
    SPWDriverComponentImpl(
        const char *const compName,
        const U8 coreNum,
        const U8 logicalAddr,
        const U32 spwClkMhz
    ) :
      SPWDriverComponentBase(compName),
#else
    SPWDriverImpl(
        const U8 coreNum,
        const U8 logicalAddr,
        const U32 spwClkMhz
    ) :
      SPWDriverComponentBase(),
#endif
      m_coreNum(coreNum),
      m_logicalAddr(logicalAddr),
      m_spwClkMhz(spwClkMhz),
      m_state(0),
      m_tid(0)
  {
    // zero initialize
    memset(&this->m_spwcore, 0, sizeof(this->m_spwcore));
    memset(&this->m_transaction, 0, sizeof(this->m_transaction));
  }

  void SPWDriverComponentImpl ::
    init(
        const NATIVE_INT_TYPE instance
    ) 
  {
    SPWDriverComponentBase::init(instance);

    I32 status = 0;

    // GRSPW2 register addresses
    U32 spwadr = SPW_CORE0_BASE_ADDR;
    switch (this->m_coreNum) {
      case 0: break;
      case 1: spwadr = SPW_CORE1_BASE_ADDR; break;
      case 2: spwadr = SPW_CORE2_BASE_ADDR; break;
      case 3: spwadr = SPW_CORE3_BASE_ADDR; break;
      case 4: spwadr = SPW_CORE4_BASE_ADDR; break;
      case 5: spwadr = SPW_CORE5_BASE_ADDR; break;
      default: FW_ASSERT(0, this->m_coreNum);
    }

    // SPW core settings
    FW_ASSERT(this->m_spwClkMhz >= 10 && this->m_spwClkMhz <= 200, this->m_spwClkMhz);
    status = spw_setparam(
        this->m_logicalAddr, // set logical address
        0, // no clock divide
        0, // dummy dest_key for now
        0, // no time codes
        0, // no time codes
        spwadr, // register address base
        0, // legacy
        &this->m_spwcore,
        0, // legacy
        (this->m_spwClkMhz / 10) - 1); // divide start-up to 10 MHz
    FW_ASSERT(status == 0, status); // assert will only happen due to validation

    // SPW DMA channel settings
    // use 1024-byte-aligned part of buffers
    U32 tx_aligned = (ptrToU32(this->m_txdesc_tbl_buf) + MAX_SPW_DESC_TABLE_SIZE) & ~(MAX_SPW_DESC_TABLE_SIZE-1);
    U32 rx_aligned = (ptrToU32(this->m_rxdesc_tbl_buf) + MAX_SPW_DESC_TABLE_SIZE) & ~(MAX_SPW_DESC_TABLE_SIZE-1);
    status = spw_setparam_dma(
        0,  // always use channel 0
        this->m_spwcore.nodeaddr, // channel's logical address
        0, // address mask
        0, // turn off nospill (i.e. DO spill unsolicited packets)
        MAX_RMAP_PACKET_SIZE, // default max rx size
        tx_aligned, // address tx descriptor table
        rx_aligned, // address rx descriptor table
        &this->m_spwcore);
    FW_ASSERT(status == 0, status); // assert will only happen due to validation

    // reset SPW state
    this->m_state = this->reset();
  }

  SPWDriverComponentImpl ::
    ~SPWDriverComponentImpl(void)
  {
  }

  // ----------------------------------------------------------------------
  // Handler implementations for user-defined typed input ports
  // ----------------------------------------------------------------------

  I32 SPWDriverComponentImpl ::
    writeRMAP_handler(
        const NATIVE_INT_TYPE portNum,
        U8 dest_addr,
        U8 dest_key,
        U32 write_addr,
        U8 *buf_ptr,
        U32 num_bytes,
        U8 increment,
        U8 verify,
        U8 acknowledge
    )
  {
    FW_ASSERT(buf_ptr != NULL);
    FW_ASSERT(num_bytes <= MAX_RMAP_PACKET_SIZE, num_bytes); // less than 16 MiB
    FW_ASSERT(increment <= 1, increment);
    FW_ASSERT(verify <= 1, verify);
    FW_ASSERT(acknowledge <= 1, acknowledge);

    if (this->m_state != SPW_STATUS_SUCCESS) {
      this->m_state = this->reset();
      if (this->m_state != SPW_STATUS_SUCCESS) {
        return this->m_state;
      }
    }

    this->m_tid = this->nextTransactionID(this->m_tid);

    this->m_transaction.tx_hdr_buf = this->m_header_buf;
    this->m_transaction.tx_hdr_size = sizeof(this->m_header_buf);
    this->m_transaction.tx_data_buf = buf_ptr;
    this->m_transaction.tx_data_size = num_bytes;
    this->m_transaction.rx_buf = acknowledge ? this->m_write_reply_buf : NULL;
    this->m_transaction.rx_size = acknowledge ? sizeof(this->m_write_reply_buf) : 0;

    this->m_transaction.pkt.type = writecmd;
    this->m_transaction.pkt.verify = (verify == 1 ? yes : no);
    this->m_transaction.pkt.ack = (acknowledge == 1 ? yes : no);
    this->m_transaction.pkt.incr = (increment == 1 ? yes : no);
    this->m_transaction.pkt.destaddr = dest_addr;
    this->m_transaction.pkt.destkey = dest_key;
    this->m_transaction.pkt.srcaddr = this->m_spwcore.nodeaddr;
    this->m_transaction.pkt.tid = this->m_tid;
    this->m_transaction.pkt.addr = write_addr;
    this->m_transaction.pkt.len = num_bytes;
    this->m_transaction.pkt.status = 0;
    this->m_transaction.pkt.dstspalen = 0;
    this->m_transaction.pkt.dstspa  = (char *)NULL;
    this->m_transaction.pkt.srcspalen = 0;
    this->m_transaction.pkt.srcspa = (char *)NULL;

    this->m_state = this->sendCommand(this->m_transaction);

    return SPW_STATUS_SUCCESS;
  }

  I32 SPWDriverComponentImpl ::
    readRMAP_handler(
        const NATIVE_INT_TYPE portNum,
        U8 dest_addr,
        U8 dest_key,
        U32 read_addr,
        U8 *buf_ptr,
        U32 num_bytes,
        U8 increment
    )
  {
    FW_ASSERT(buf_ptr != NULL);
    FW_ASSERT(num_bytes <= MAX_RMAP_PACKET_SIZE, num_bytes); // less than 16 MiB
    FW_ASSERT(increment <= 1, increment);

    if (this->m_state != SPW_STATUS_SUCCESS) {
      this->m_state = this->reset();
      if (this->m_state != SPW_STATUS_SUCCESS) {
        return this->m_state;
      }
    }

    this->m_tid = this->nextTransactionID(this->m_tid);

    this->m_transaction.tx_hdr_buf = this->m_header_buf;
    this->m_transaction.tx_hdr_size = sizeof(this->m_header_buf);
    this->m_transaction.tx_data_buf = buf_ptr; // no actual data, but spwapi requires non-NULL data pointer
    this->m_transaction.tx_data_size = 0;
    this->m_transaction.rx_buf = buf_ptr;
    // num_bytes is only the amount in the RMAP read request - when data comes
    // back, it will have a SPW and RMAP header, along with a 1-byte CRC. This
    // margin is encoded in RMAP_READ_REQUEST_BUF_MARGIN. The expected rx size
    // must also be 4-byte aligned
    this->m_transaction.rx_size = (num_bytes + RMAP_READ_REQUEST_BUF_MARGIN) & ~0x3;

    this->m_transaction.pkt.type = readcmd;
    this->m_transaction.pkt.verify = no;
    this->m_transaction.pkt.ack = yes;
    this->m_transaction.pkt.incr = (increment == 1 ? yes : no);
    this->m_transaction.pkt.destaddr = dest_addr;
    this->m_transaction.pkt.destkey = dest_key;
    this->m_transaction.pkt.srcaddr = this->m_spwcore.nodeaddr;
    this->m_transaction.pkt.tid = this->m_tid;
    this->m_transaction.pkt.addr = read_addr;
    this->m_transaction.pkt.len = num_bytes;
    this->m_transaction.pkt.status = 0;
    this->m_transaction.pkt.dstspalen = 0;
    this->m_transaction.pkt.dstspa  = (char *)NULL;
    this->m_transaction.pkt.srcspalen = 0;
    this->m_transaction.pkt.srcspa = (char *)NULL;

    this->m_state = this->sendCommand(this->m_transaction);

    return SPW_STATUS_SUCCESS;
  }

  I32 SPWDriverComponentImpl ::
    reset_handler(
        const NATIVE_INT_TYPE portNum
    )
  {
    this->m_state = this->reset();
    return this->m_state;
  }

  I32 SPWDriverComponentImpl ::
    getStatus_handler(
        const NATIVE_INT_TYPE portNum
    )
  {
    this->m_state = this->nextState(this->m_state);
    return this->m_state;
  }


  // ----------------------------------------------------------------------
  // Private supporting functions
  // ----------------------------------------------------------------------

  I32 SPWDriverComponentImpl::sendCommand(RMAPTransaction& transaction)
  {
    I32 status;

    // expecting a reply
    if (transaction.rx_buf != NULL) {
      // cap maximum receive length so our buf doesn't get overrun
      FW_ASSERT(transaction.rx_size > 0);
      FW_ASSERT((transaction.rx_size & 0x3) == 0); // must be 4-byte aligned
      this->m_spwcore.dma[0].rxmaxlen = transaction.rx_size;
      status = spw_set_rxmaxlength(0, &this->m_spwcore);
      FW_ASSERT(status == 0, status);
      status = spw_rx(0, reinterpret_cast<char*>(transaction.rx_buf), &this->m_spwcore);
      FW_ASSERT(status == 0, status);
    }

    int cmdsize = 0;
    status = build_rmap_hdr(&transaction.pkt, reinterpret_cast<char*>(transaction.tx_hdr_buf), &cmdsize);
    FW_ASSERT(status == 0);
    FW_ASSERT(cmdsize > 0);
    FW_ASSERT(static_cast<U32>(cmdsize) <= transaction.tx_hdr_size);

    // start transmission
    status = spw_tx(
        0, // dmachan
        1, // header CRC
        transaction.pkt.type == writecmd ? 1 : 0, // only RMAP write needs data CRC
        0, // crc skip amt
        cmdsize, // hdr size
        reinterpret_cast<char*>(transaction.tx_hdr_buf),  // header addr
        transaction.tx_data_size, // data size
        reinterpret_cast<char*>(transaction.tx_data_buf), // data addr
        &this->m_spwcore);
    FW_ASSERT(status == 0, status);

    return SPW_STATUS_SENDING;
  }

  I32 SPWDriverComponentImpl::checkSendState()
  {
    const I32 status = spw_checktx(0, &this->m_spwcore);

    I32 ret = 0;
    switch (status) {

      case 0:
        // still waiting
        ret = SPW_STATUS_SENDING;
        break;

      case 1:
        // done
        ret = SPW_STATUS_SUCCESS;
        break;

      case 2:
        // link error
        ret = SPW_STATUS_ERR_TX_LINK;
        break;

      default:
        FW_ASSERT(0, status); // case shouldn't exist
    }

    return ret;
  }

  I32 SPWDriverComponentImpl::checkReceiveState(U32& receivedSize)
  {
    int isize = 0;
    rxstatus rxstat;
    const I32 status = spw_checkrx(0, &isize, &rxstat, &this->m_spwcore);

    I32 ret = 0;
    switch (status) {
      case 0:
        // still waiting
        ret = SPW_STATUS_RECEIVING;
        break;

      case 1:
        // ended, but error needs to be checked separately
        FW_ASSERT(isize >= 0, isize); // the way spwapi sets it, shouldn't ever be <0
        receivedSize = static_cast<U32>(isize);

        if (rxstat.eep) {
          // received error end-of-packet
          ret = SPW_STATUS_ERR_RX_EEP;

        } else if (rxstat.truncated) {
          // packet truncated
          ret = SPW_STATUS_ERR_RX_TRUNCATED;

        } else if (rxstat.dcrcerr) {
          // data crc error
          ret = SPW_STATUS_ERR_RX_DATA_CRC;

        } else if (rxstat.hcrcerr) {
          // header crc error
          ret = SPW_STATUS_ERR_RX_HDR_CRC;

        } else {
          // all good on rx
          ret = SPW_STATUS_SUCCESS;
        }
        break;

      default:
        FW_ASSERT(0, status); // case shouldn't exist
    }

    return ret;
  }

  I32 SPWDriverComponentImpl::checkRMAPValidity(U8* buf, const U32 size, const RMAPTransaction& transaction)
  {
    FW_ASSERT(buf != NULL);

    // deserialize the RMAP reply header to check for errors
    struct rmap_pkt pkt;
    int hdrsize;
    I32 status = parse_rmap_pkt(&pkt, reinterpret_cast<char*>(buf), &hdrsize);
    if (status != 0) {
      return SPW_STATUS_ERR_RX_DESERIALIZATION;
    }

    // make sure it's actually an expected reply type
    if ((pkt.type != readrep && pkt.type != writerep) ||
        (pkt.type == writerep && transaction.pkt.type != writecmd) ||
        (pkt.type == readrep && transaction.pkt.type != readcmd)) {
      return SPW_STATUS_ERR_RX_UNEXPECTED_REPLY;
    }

    // check for transaction mismatch errors
    if (pkt.tid != transaction.pkt.tid) {
      return SPW_STATUS_ERR_RMAP_TRANS_ID_MISMATCH;
    }

    // check status of operation on other side
    if (pkt.status != 0) {
      return this->mapRMAPStatusToDriverStatus(pkt.status);
    }

    // if read rmap command, check expected length
    // this is done _after_ the status check because if status is fail, often
    // no data will be returned
    if (transaction.pkt.type == readcmd &&
        pkt.len != transaction.pkt.len) {
      return SPW_STATUS_ERR_RMAP_DATA_LEN_MISMATCH;
    }

    return SPW_STATUS_SUCCESS;
  }

  U16 SPWDriverComponentImpl::nextTransactionID(const U16 id) const
  {
    if (id == MAX_RMAP_TRANSACTION_ID) {
      return 0;
    } else {
      return id+1;
    }
  }

  I32 SPWDriverComponentImpl::nextState(I32 state)
  {
    if (state == SPW_STATUS_SENDING) {
      // in send state - check tx status
      state = this->checkSendState();

      if (state == SPW_STATUS_SUCCESS &&
          this->m_transaction.pkt.ack) {
        // send was successful, but transaction requested acknowledge, so go to
        // receiving state
        state = SPW_STATUS_RECEIVING;
      }
    }

    // intentionally possible to fallthrough from above (e.g. verified send is
    // complete, immediately check receive)
    if (state == SPW_STATUS_RECEIVING) {
      // in receive state - check rx status
      U32 size = 0;
      state = this->checkReceiveState(size);

      if (state == SPW_STATUS_SUCCESS) {
        // rx is fine, but also check RMAP packet validity
        state = this->checkRMAPValidity(
            this->m_transaction.rx_buf,
            size,
            this->m_transaction);
      }
    }

    return state;
  }

  I32 SPWDriverComponentImpl::reset()
  {
    int status;

    // to abort tx and rx, Gaisler recommends disabling the link entirely
    // (GR712 User Manual, pg. 110)
    spw_disable(&this->m_spwcore);

    // reset spw core
    spw_reset(&this->m_spwcore);

    // reset dma channel
    this->m_spwcore.regs->dma[0].ctrl = 0;

    // scrub descriptor tables
    memset(this->m_txdesc_tbl_buf, 0, sizeof(this->m_txdesc_tbl_buf));
    memset(this->m_rxdesc_tbl_buf, 0, sizeof(this->m_rxdesc_tbl_buf));

    // initialize core
    status = spw_init(&this->m_spwcore);
    if (status != 0) {
      return SPW_STATUS_ERR_INIT;
    }

    // re-enable link
    spw_enable(&this->m_spwcore);

    // wait for link connection
    status = wait_running(&this->m_spwcore);
    if (status != 0) {
      return SPW_STATUS_ERR_DISCONNECTED;
    }

    return SPW_STATUS_SUCCESS;
  }

  U32 SPWDriverComponentImpl::mapRMAPStatusToDriverStatus(U8 status)
  {
    FW_ASSERT(status != 0);
    switch (status) {
      case 1: return SPW_STATUS_ERR_RMAP_STAT_GENERAL;
      case 2: return SPW_STATUS_ERR_RMAP_STAT_UNUSED_TYPE;
      case 3: return SPW_STATUS_ERR_RMAP_STAT_INVALID_KEY;
      case 4: return SPW_STATUS_ERR_RMAP_STAT_INVALID_DATA_CRC;
      case 5: return SPW_STATUS_ERR_RMAP_STAT_EARLY_EOP;
      case 6: return SPW_STATUS_ERR_RMAP_STAT_CARGO_TOO_LARGE;
      case 7: return SPW_STATUS_ERR_RMAP_STAT_EEP;
      // case 8 is "reserved"
      case 9: return SPW_STATUS_ERR_RMAP_STAT_VERIFY_BUFFER_OVERRUN;
      case 10: return SPW_STATUS_ERR_RMAP_STAT_CMD_UNAUTHORIZED;
      case 11: return SPW_STATUS_ERR_RMAP_STAT_DATA_LEN_ERR;
      case 12: return  SPW_STATUS_ERR_RMAP_STAT_INVALID_DEST_ADDR;
      default: break;
    }
    return SPW_STATUS_ERR_RMAP_STAT_UNKNOWN;
  }

} // end namespace Drv
