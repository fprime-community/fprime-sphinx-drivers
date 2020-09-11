// ======================================================================
// \title  SPWManagerComponentImpl.hpp
// \author vwong
// \brief  hpp file for SPWManager component implementation class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
// ======================================================================

#ifndef SPWManager_HPP
#define SPWManager_HPP

#include "fprime-sphinx-drivers/SPWManager/SPWManagerComponentAc.hpp"
#include "fprime-sphinx-drivers/SPWManager/SPWRequestQueue.hpp"
#include "fprime-sphinx-drivers/SPWDriver/RMAPHeader.hpp"
#include <Utils/TokenBucket.hpp>
#include <Os/Mutex.hpp>

#define SPW_ASYNC_TIMEOUT 10
#define SPW_WORK_BUF_DATA_SIZE (256 << 10)
#define SPW_WORK_BUF_MAX_SIZE (SPW_WORK_BUF_DATA_SIZE + MAX_RMAP_HDR_SIZE + 4)
#define SPW_SHIFT_BUF_SIZE 4096

#define SPW_ERROR_BUCKET_LIMITER_TOKENS 3 // 3 tokens
#define SPW_ERROR_BUCKET_LIMITER_USECS 10000000 // replenish 1 every 10s

namespace Drv {

  class SPWManagerComponentImpl :
    public SPWManagerComponentBase
  {

    public:

      // ----------------------------------------------------------------------
      // Construction, initialization, and destruction
      // ----------------------------------------------------------------------

      //! Construct object SPWManager
      //!
      SPWManagerComponentImpl(
#if FW_OBJECT_NAMES == 1
          const char *const compName //!< The component name
#else
          void
#endif
      );

      //! Initialize object SPWManager
      //!
      void init(
          const NATIVE_INT_TYPE queueDepth, //!< The queue depth
          const NATIVE_INT_TYPE instance = 0 //!< The instance number
      );

      //! Destroy object SPWManager
      //!
      ~SPWManagerComponentImpl(void);

    PRIVATE:

      // ----------------------------------------------------------------------
      // Handler implementations for user-defined typed input ports
      // ----------------------------------------------------------------------

      //! Handler implementation for write
      //!
      I32 write_handler(
          const NATIVE_INT_TYPE portNum, //!< The port number
          U32 addr,
          U32 num_bytes,
          U8 *buf,
          U32 buf_size,
          U32 timeout
      );

      //! Handler implementation for read
      //!
      I32 read_handler(
          const NATIVE_INT_TYPE portNum, //!< The port number
          U32 addr,
          U32 num_bytes,
          U8 *buf,
          U32 buf_size,
          U32 timeout
      );

      //! Handler implementation for writeAsync
      //!
      I32 writeAsync_handler(
          const NATIVE_INT_TYPE portNum, //!< The port number
          U32 addr,
          U32 num_bytes,
          U8 *buf,
          U32 buf_size,
          U32 timeout
      );

      //! Handler implementation for readAsync
      //!
      I32 readAsync_handler(
          const NATIVE_INT_TYPE portNum, //!< The port number
          U32 addr,
          U32 num_bytes,
          U8 *buf,
          U32 buf_size,
          U32 timeout
      );

      //! Handler implementation for resetLink
      //!
      void resetLink_handler(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

      //! Handler implementation for schedIn
      //!
      void schedIn_handler(
          const NATIVE_INT_TYPE portNum, //!< The port number
          NATIVE_UINT_TYPE context //!< The call order
      );

      //! Handler implementation for readAsyncDMA
      //!
      I32 readAsyncDMA_handler(
          const NATIVE_INT_TYPE portNum, //!< The port number
          U32 addr,
          U32 num_bytes,
          U8 *buf,
          U32 buf_size,
          U32 timeout
      );

      //! Handler implementation for setParam
      //!
      I32 setParam_handler(
          const NATIVE_INT_TYPE portNum, //!< The port number
          U8 dest_addr,
          U8 dest_key,
          U8 increment,
          U8 verify,
          U8 acknowledge
      );

      //! Handler implementation for PingRecv
      //!
      void PingRecv_handler(
          const NATIVE_INT_TYPE portNum, //!< The port number
          U32 key //!< Value to return to pinger
      );


    PRIVATE:

      // ----------------------------------------------------------------------
      // Command handler implementations
      // ----------------------------------------------------------------------

      //! Implementation for SPWMGR_RMAP_WRITE_WORD command handler
      //! Manually execute a synchronous RMAP write request for a single word (4 bytes)
      void SPWMGR_RMAP_WRITE_WORD_cmdHandler(
          const FwOpcodeType opCode, /*!< The opcode*/
          const U32 cmdSeq, /*!< The command sequence number*/
          U32 targetAddress, /*!< Address of target to write*/
          U32 value, /*!< Value to write*/
          U32 timeout /*!< Number of cycles to timeout request*/
      );

      //! Implementation for SPWMGR_RMAP_READ_WORD command handler
      //! Manually execute a synchronous RMAP read request for a single word (4 bytes)
      void SPWMGR_RMAP_READ_WORD_cmdHandler(
          const FwOpcodeType opCode, /*!< The opcode*/
          const U32 cmdSeq, /*!< The command sequence number*/
          U32 targetAddress, /*!< Address of target to read*/
          U32 timeout /*!< Number of cycles to timeout request*/
      );

      //! Implementation for SPWMGR_RESET_LINK command handler
      //! Reset the SpaceWire link
      void SPWMGR_RESET_LINK_cmdHandler(
          const FwOpcodeType opCode, /*!< The opcode*/
          const U32 cmdSeq /*!< The command sequence number*/
      );

      //! Implementation for SPWMGR_SET_PARAMS command handler
      //! Manually set the RMAP settings that the SPWManager uses
      void SPWMGR_SET_PARAMS_cmdHandler(
          const FwOpcodeType opCode, /*!< The opcode*/
          const U32 cmdSeq, /*!< The command sequence number*/
          U8 destinationAddress, /*!< The destination node address*/
          U8 destinationKey, /*!< The destination node's RMAP key*/
          U8 increment, /*!< RMAP increment setting*/
          U8 verify, /*!< RMAP verify setting*/
          U8 acknowledge /*!< acknowledge*/
      );


    PRIVATE: //methods

      /**
       * Initializes a new SPWRequest
       */
      SPWRequest initializeRequest(
          NATIVE_INT_TYPE client_port,
          RMAPHeader::RMAPCommandType cmd,
          U32 addr,
          U8* buf,
          U32 num_bytes,
          U32 timeout,
          bool async,
          bool dma);

      /** 
       * Implementation of the sync read/writes
       */
      I32 handleSyncWrite(U32 portNum, U32 addr, U32 num_bytes, U8 *buf, U32 buf_size, U32 timeout);
      I32 handleSyncRead(U32 portNum, U32 addr, U32 num_bytes, U8 *buf, U32 buf_size, U32 timeout);

      /**
       * Begins the execution of the request, returns whether request
       * successfully started
       */
      I32 startRequest(SPWRequest& req);

      /**
       * Invoke the appropriate RMAP command to send from SPWDriver, returns
       * whether command was successfully sent (function will automatically log
       * if error occurs)
       */
      I32 sendCommand(const SPWRequest& req);

      /**
       * Continuously checks status of transaction and tries to process more data,
       * subject to a timeout
       *
       * This timeout is not the same as the async timeout; the one used here is a
       * synchronous version incremented in a busy loop intended for small
       * transactions
       *
       * Returns the current status of the request, whether it's fully done,
       * encountered an error, or timed out
       *
       * NB: this function assumes that the first packet has already been sent, and
       * the status it receives from the driver is valid the packet in the
       * current request
       */
      I32 processRequest(SPWRequest& req, U32 timeout);

      /**
       * Evaluates the driver status in the context of the given request,
       * invoking logSpacewireError if determined to be an error. Returns a
       * SPWManager Request Status.
       */
      I32 evaluateStatus(const SPWRequest& req, I32 driverStatus);

      /**
       * Helper function to invoke non-timeout related error EVRs
       */
      void logSpaceWireError(I32 driverStatus);

      /**
       * Helper function to invoke timeout EVR
       */
      void logSpaceWireTimeout(const SPWRequest& req, I32 driverStatus);

      /**
       * Synchronization primitives for SPWDriver usage, since SPWDriver cannot
       * serve requests in parallel
       */
      bool claimDriver();
      void unclaimDriver();

      /**
       * Wrapper function to report the request status to client
       */
      void reportStatus(I32 portNum, I32 status);

      /**
       * Helper function to abort all async requests and reset the link
       *
       * Returns the driverStatus from the reset attempt
       */
      I32 abortAndReset();

      /**
       * Helper function to convert status code to evr enum
       */
      SpaceWireError_status toSpaceWireError_status(I32 status);

    PRIVATE: // members

      U8 m_dest_addr;
      U8 m_dest_key;
      U8 m_increment;
      U8 m_verify;
      U8 m_acknowledge;

      // queue of async requests that need to run
      SPWRequestQueue m_requests;

      // work buffer to use for DMA
      U8 m_work_buf[SPW_WORK_BUF_MAX_SIZE];

      // lock for driver access
      Os::Mutex m_mutex;
      bool m_driver_claimed;

      // token bucket for reporting errors
      Utils::TokenBucket m_errorBucketLimiter;

  };

} // end namespace Drv

#endif
