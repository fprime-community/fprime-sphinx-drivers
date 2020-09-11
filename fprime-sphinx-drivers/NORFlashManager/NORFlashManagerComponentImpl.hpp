// ======================================================================
// \title  NORFlashManagerImpl.hpp
// \author ortega
// \brief  hpp file for NORFlashManager component implementation class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
// ======================================================================

#ifndef NORFlashManager_HPP
#define NORFlashManager_HPP

#include "fprime-sphinx-drivers/NORFlashManager/NORFlashManagerComponentAc.hpp"
#include "fprime-sphinx-drivers/Include/config.hpp"

namespace Drv {
  typedef enum {
    NORMGR_IDLE, // When component is idle
    NORMGR_WRITING, // When component is writing chunk to the NOR
    NORMGR_READING, // When component is reading chunk to the NOR
    NORMGR_ERASING, // When erasing has started on the NOR
    NORMGR_RESETING, // When the NOR is resetting
    NORMGR_VERIFYING // When the NOR is verifying
  } nor_mgr_state;

  typedef enum {
    NORMGR_OK, // status for when everything is okay
    NORMGR_FAIL, // status for when there was a failure to erase or write the NOR
    NORMGR_BUSY, // status for when erase or write is issued and the manager is not in IDLE state
    NORMGR_TIMEOUT, // status for when there was a timeout erasing the NOR
    NORMGR_SUCCESSFUL_PROGRAM, // status for when there was a successful write
    NORMGR_SUCCESSFUL_ERASE, // status for when there was a successful erase
    NORMGR_SUCCESSFUL_VERIFY, // status for when there was a successful NOR verification
    NORMGR_KEEP_POLLING, // status for when to keep on polling for erase/write done
    NORMGR_FAILED_TO_READ, // status for when there was a failure to read
    NORMGR_FAILED_TO_ERASE, // status for when there was a failure doing the erase sequence
    NORMGR_FAILED_TO_ERASE_POLL, // status for when there was a failure polling for erase
    NORMGR_FAILED_TO_UNLOCK, // status for when there was a failure to unlock bypass
    NORMGR_FAILED_TO_UNLOCK_PROGRAM, // status for when there was a failure to unlock bypass program
    NORMGR_FAILED_TO_RESET_BYPASS, // status for when there was a failure to reset bypass
    NORMGR_FAILED_TO_READ_RESET_BYPASS, // status for when both read and reset bypass fails
    NORMGR_FAILED_TO_UNLOCK_PROGRAM_RESET_BYPASS, // status for when both unlock program and reset bypass fails
    NORMGR_FAILED_TO_RESET_BYPASS_RESET, // status for when both reset bypass and nor reset fail, implies read failure
    NORMGR_FAILED_TO_RESET, // status failed to reset nor, implies failure to read
    NORMGR_FAILED_TO_TIMEOUT_RESET, // status to timeout and reset
    NORMGR_FAILED_TO_ERASE_RESET, // status for when both erase and reset bypass fails
    NORMGR_FAILED_TO_VERIFY, // status for when nor verification fails
    NORMGR_ADDR_OUT_OF_RANGE, // status for Address is out of range for write/read
  } nor_mgr_status;

  class NORFlashManagerComponentImpl :
    public NORFlashManagerComponentBase
  {

    public:

      // ----------------------------------------------------------------------
      // Construction, initialization, and destruction
      // ----------------------------------------------------------------------

      //! Construct object NORFlashManager
      //!
      NORFlashManagerComponentImpl(
#if FW_OBJECT_NAMES == 1
          const char *const compName, //!< The component name
          U32 timeout
#else
          U32 timeout
#endif
      );

      //! Initialize object NORFlashManager
      //!
      void init(
          const NATIVE_INT_TYPE queueDepth, //!< The queue depth
          const NATIVE_INT_TYPE instance = 0 //!< The instance number
      );

      //! Destroy object NORFlashManager
      //!
      ~NORFlashManagerComponentImpl(void);

    PRIVATE:
      // Assuming processor is 40MHz and time to program is 80us max (per NOR chip doc)
      // 40 MHz -> 40,000,000 cycles / s -> 40 cycles / us
      // 40 cycles / us  * 80 us  = 3200 cycles for each write.
      // And round up for good measure.
      const static U32 NOR_POLL_WRITE_TIMEOUT = 4000 * 16 * 1024;
      U32 m_bank_addr;
      nor_mgr_state m_state;
      U32 m_timer;
      U32 m_erase_timeout;
      U32 m_write_timeout;
      U32 m_verify_timeout;
      FwOpcodeType m_reset_opcode;
      U32 m_reset_cmd_seq;
      //U32 m_extra_erase;
      bool m_using_prom_edac;

      // ----------------------------------------------------------------------
      // Handler implementations for user-defined typed input ports
      // ----------------------------------------------------------------------

      //! Handler implementation for get_bl_size
      //!
      I32 get_bl_size_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          U32 &size 
      );

      //! Handler implementation for worker_done
      //!
      void worker_done_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          I8 done,
          U32 context1,
          U32 context2 
      );

      //! Handler implementation for get_fsw_size
      //!
      I32 get_fsw_size_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          U32 &size 
      );

      //! Handler implementation for erase
      //!
      void request_erase_handler(
          const NATIVE_INT_TYPE portNum, //!< The port number
          U8 bank_number
      );

      //! Handler implementation for request_write
      //!
      void request_write_handler(
          const NATIVE_INT_TYPE portNum, //!< The port number
          U32 dest, //!< The NOR address to write to
          U8 *src,  //!< The membery buffer with the data to write to dest
          U32 count, //!< Number of bytes to write to dest
          bool disable_edac //!< Disable edac for this write call
      );

      //! Handler implementation for schedIn
      //!
      void schedIn_handler(
          const NATIVE_INT_TYPE portNum, //!< The port number
          NATIVE_UINT_TYPE context //!< The call order
      );

      //! Handler implementation for request_read
      //!
      void request_read_handler(
          const NATIVE_INT_TYPE portNum, //!< The port number
          U32 src, //!< The NOR address from which to read from
          U8 *dest,  //!< The buffer in which to store what is read from src
          U32 count, //!< Number of bytes to read from dest
          bool disable_edac //!< Disable edac for this write call
      );

      //! Handler implementation for PingRecv
      //!
      void PingRecv_handler(
          const NATIVE_INT_TYPE portNum, //!< The port number
          U32 key //!< Value to return to pinger
      );

      //! Handler implementation for request_verification
      //!
      void request_verification_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          U32 blc_filesize, 
          U32 fsw_filesize 
      );

      //! Disables prom edac
      void disable_prom_edac(void);
      //! Enables prom edac
      void enable_prom_edac(void);
      //! Handles reset
      void read_and_store_edac_status(void);
      //! Handles reset
      void reset_mgr_state(void);
    PRIVATE:
      // ----------------------------------------------------------------------
      // Command handler implementations
      // ----------------------------------------------------------------------

      //! Implementation for NOR_FLASH_RESET command handler
      //! Reset the NOR Flash
      void NOR_FLASH_RESET_cmdHandler(
          const FwOpcodeType opCode, /*!< The opcode*/
          const U32 cmdSeq, /*!< The command sequence number*/
          U8 bank_number /*!< The bank to reset*/
      );

      //! Implementation for NOR_FLASH_SET_WRITE_TIMEOUT command handler
      //! Set the timeout for a write to the specified value.
      void NOR_FLASH_SET_WRITE_TIMEOUT_cmdHandler(
          const FwOpcodeType opCode, /*!< The opcode*/
          const U32 cmdSeq, /*!< The command sequence number*/
          U32 timeout /*!< The timeout value in schedIn ticks*/
      );

      //! Implementation for NOR_FLASH_SET_ERASE_TIMEOUT command handler
      //! Set the timeout for erase to the specified value.
      void NOR_FLASH_SET_ERASE_TIMEOUT_cmdHandler(
          const FwOpcodeType opCode, /*!< The opcode*/
          const U32 cmdSeq, /*!< The command sequence number*/
          U32 timeout /*!< The timeout value in schedIn ticks*/
      );

      //! Implementation for NOR_FLASH_SET_VERIFY_TIMEOUT command handler
      //! Set the timeout for erase to the specified value.
      void NOR_FLASH_SET_VERIFY_TIMEOUT_cmdHandler(
          const FwOpcodeType opCode, /*!< The opcode*/
          const U32 cmdSeq, /*!< The command sequence number*/
          U32 timeout /*!< The timeout value in schedIn ticks*/
      );

    };

} // end namespace Drv

#endif
