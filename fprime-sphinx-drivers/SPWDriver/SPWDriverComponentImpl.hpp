// ====================================================================== 
// \title  SPWDriverComponentImpl.hpp
// \author vwong
// \brief  hpp file for SPWDriver component implementation class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
// ====================================================================== 

#ifndef SPWDriver_HPP
#define SPWDriver_HPP

#include <Fw/Com/ComBuffer.hpp>

#include "fprime-sphinx-drivers/SPWDriver/SPWDriverComponentAc.hpp"
#include "fprime-sphinx-drivers/SPWDriver/RMAPTransaction.hpp"
#include "fprime-sphinx-drivers/SPWDriver/RMAPHeader.hpp"
#include "fprime-sphinx-drivers/SPWDriver/sphinx-spw/spwapi.h"

/* SpaceWire core defines */

#define MAX_SPW_DESC_TABLE_SIZE 1024
#define RMAP_READ_REQUEST_BUF_MARGIN (MAX_RMAP_HDR_SIZE + 4) // margin for hdr and data crc

/* SpaceWire Register Offsets */

#define SPW_CORE0_BASE_ADDR 0x80100800
#define SPW_CORE1_BASE_ADDR 0x80100900
#define SPW_CORE2_BASE_ADDR 0x80100A00
#define SPW_CORE3_BASE_ADDR 0x80100B00
#define SPW_CORE4_BASE_ADDR 0x80100C00
#define SPW_CORE5_BASE_ADDR 0x80100D00

namespace Drv {

  class SPWDriverComponentImpl :
    public SPWDriverComponentBase
  {

    public:

      // ----------------------------------------------------------------------
      // Construction, initialization, and destruction
      // ----------------------------------------------------------------------

      //! Construct object SPWDriver
      //!
      SPWDriverComponentImpl(
#if FW_OBJECT_NAMES == 1
          const char *const compName, //!< The component name
          const U8 coreNum,
          const U8 logicalAddr,
          const U32 spwClkMhz
#else
          const U8 coreNum,
          const U8 logicalAddr,
          const U32 spwClkMhz
#endif
      );

      //! Initialize object SPWDriver
      //!
      void init(
          const NATIVE_INT_TYPE instance = 0 //!< The instance number
      );

      //! Destroy object SPWDriver
      //!
      ~SPWDriverComponentImpl(void);

    PRIVATE:

      // ----------------------------------------------------------------------
      // Handler implementations for user-defined typed input ports
      // ----------------------------------------------------------------------

      //! Handler implementation for writeRMAP
      //!
      virtual I32 writeRMAP_handler(
          const NATIVE_INT_TYPE portNum, //!< The port number
          U8 dest_addr, 
          U8 dest_key, 
          U32 write_addr, 
          U8 *buf_ptr, 
          U32 num_bytes,
          U8 increment, 
          U8 verify, 
          U8 acknowledge 
      );

      //! Handler implementation for readRMAP
      //!
      virtual I32 readRMAP_handler(
          const NATIVE_INT_TYPE portNum, //!< The port number
          U8 dest_addr, 
          U8 dest_key, 
          U32 read_addr, 
          U8 *buf_ptr, 
          U32 num_bytes,
          U8 increment 
      );

      //! Handler implementation for reset
      //!
      virtual I32 reset_handler(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

      //! Handler implementation for getStatus
      //!
      virtual I32 getStatus_handler(
          const NATIVE_INT_TYPE portNum //!< The port number
      );


    PRIVATE: //methods

      U16 nextTransactionID(const U16 id) const;
      I32 nextState(I32 state);
      I32 checkSendState();
      I32 checkReceiveState(U32& receivedSize);
      I32 checkRMAPValidity(U8* buf, const U32 size, const RMAPTransaction& transaction);
      I32 sendCommand(RMAPTransaction& transaction);
      I32 reset();

    PRIVATE: //static functions

      static U32 mapRMAPStatusToDriverStatus(U8 status);

    PRIVATE: // members

      // Parameters
      //
      const U8 m_coreNum;
      const U8 m_logicalAddr;
      const U32 m_spwClkMhz;

      // Variables
      //
      // SPW core driver api and settings
      spwvars m_spwcore;

      // Current state of transaction
      I32 m_state;

      // Current transaction settings
      U16 m_tid;
      RMAPTransaction m_transaction;

      // Buffer for writing SpaceWire/RMAP headers
      U8 m_header_buf[MAX_RMAP_HDR_SIZE];

      // Buffer for storing RMAP write replies
      U8 m_write_reply_buf[MAX_RMAP_HDR_SIZE];

      // 2x table size used to find MAX_SPW_DESC_TABLE_SIZE-aligned region
      // within
      U8 m_txdesc_tbl_buf[2 * MAX_SPW_DESC_TABLE_SIZE];
      U8 m_rxdesc_tbl_buf[2 * MAX_SPW_DESC_TABLE_SIZE];
    };

} // end namespace Drv

#endif
