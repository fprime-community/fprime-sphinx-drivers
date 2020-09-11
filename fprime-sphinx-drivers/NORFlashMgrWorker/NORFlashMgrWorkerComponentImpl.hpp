// ====================================================================== 
// \title  NORFlashMgrWorkerImpl.hpp
// \author arizvi,ortega
// \brief  hpp file for NORFlashMgrWorker component implementation class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
// ====================================================================== 

#ifndef NORFlashMgrWorker_HPP
#define NORFlashMgrWorker_HPP

#include "Os/Mutex.hpp"
#include "fprime-sphinx-drivers/NORFlashMgrWorker/NORFlashMgrWorkerComponentAc.hpp"
#include "fprime-sphinx-drivers/NORFlashManager/NORFlashManagerComponentImpl.hpp"
#include "fprime-sphinx-drivers/NOR/nor.hpp"

extern "C" {
#include "fprime-sphinx-drivers/OCM/ocm.h"
}

#define NOR_WORKER_MAX_BLOCK_SIZE (16 * 1024)
// Assuming processor is 40MHz and time to program is 80us max (per NOR chip doc)
// 40 MHz -> 40,000,000 cycles / s -> 40 cycles / us
// 40 cycles / us  * 80 us  = 3200 cycles for each write.
// And round up for good measure.
#define NOR_WORKER_WRITE_CYCLES 20000
//Roughly 5 seconds
#define NOR_WORKER_ERASE_CYCLES 200000000
#define NOR_WORKER_RETRY 3
#define NOR_WORKER_BANK_COUNT 4

namespace Drv {

  class NORFlashMgrWorkerComponentImpl :
    public NORFlashMgrWorkerComponentBase
  {

    public:

      // ----------------------------------------------------------------------
      // Construction, initialization, and destruction
      // ----------------------------------------------------------------------

      //! Construct object NORFlashMgrWorker
      //!
      NORFlashMgrWorkerComponentImpl(
#if FW_OBJECT_NAMES == 1
          const char *const compName /*!< The component name*/
#else
          void
#endif
      );

      //! Initialize object NORFlashMgrWorker
      //!
      void init(
          const NATIVE_INT_TYPE queueDepth, /*!< The queue depth*/
          const NATIVE_INT_TYPE instance = 0 /*!< The instance number*/
      );

      //! Destroy object NORFlashMgrWorker
      //!
      ~NORFlashMgrWorkerComponentImpl(void);

    PRIVATE:
      const static U8 DQ5_MASK = 0x20;
      const static U8 DQ7_MASK = 0x80;
      // Assuming processor is 40MHz and time to program is 80us max (per NOR chip doc)
      // 40 MHz -> 40,000,000 cycles / s -> 40 cycles / us
      // 40 cycles / us  * 80 us  = 3200 cycles for each write.
      // And round up for good measure.
      const static U32 NOR_POLL_WRITE_TIMEOUT = 4000;

      // ----------------------------------------------------------------------
      // Handler implementations for user-defined typed input ports
      // ----------------------------------------------------------------------

      //! Handler implementation for cancel
      //!
      void cancel_handler(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

      //! Handler implementation for write_block
      //!
      void write_block_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          U32 dest, /*!< Destination address */
          U8 *src, /*!< Src pointer */
          U32 count, /*!< Count pointer */
          U32 bank /*!< Bank address */
      );

      //! Handler implementation for read_block
      //!
      void read_block_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          U8 *dest,
          U32 src,
          U32 count,
          U32 bank
      );

      //! Reset call handler
      //!
      void reset_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          U32 bank /*!< Bank to reset */
      );

      //! Handler implementation for verify
      //!
      void verify_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          U32 blc_filesize, 
          U32 fsw_filesize 
      );

      //! Erase handler
      //!
      void erase_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          U32 bank_addr 
      );

      //! Helper to compute checksum
      //!
      U32 checksum_compute(
          U32 size,  /*!< Number of bytes to check */
          U32 image /*!< Start address of memory to check */
      );
      //! Helper to reset all functions of nor worker
      //!
      nor_mgr_status reset_all(
          U32 bank /*!< Bank to reset */
      );
      nor_mgr_status erase_poll(
          U32 addr /*!< Address to poll */
      );
      nor_mgr_status reset_nor(
          U32 bank_addr /*!< Bank to reset */
      );
      //! Start the erase of the nor
      //!
      nor_mgr_status start_erase(
          U32 bank_addr /*!< Address for bank */
      );
      //! Poll the data bit q7
      //!
      nor_mgr_status data_poll_qd7(
          U32 addr, /*!< Address to poll */
          U8 src, /*!< Expected src byte */
          U8 *data /*!< Data byte */
      );
      //! Verify and validate data in NOR
      //!
      nor_mgr_status verify_and_validate_nor(
          const U32 blc_num_bytes, /*!< Number of bytes for the blc image */
          const U32 fsw_num_bytes, /*!< Number of bytes for the fsw image */
          U32 &cptd_blc_checksum,  /*!< Computed checksum for blc */
          U32 &cptd_fsw_checksum   /*!< Computed checksum for fsw */
      );
      //! Verify the data previously written
      //!
      bool verify_data(
          U32 addr, /*!< Address to poll */
          U8 src /*!< src to poll */
      );
      //! Unlock the bypass quick programming mode
      //!
      nor_mgr_status unlock_bypass(
          U32 bank /*!< Bank to unlock */
      );
      //! Program when in the quick programming mode
      //!
      nor_mgr_status unlock_bypass_program(
          U32 dest_ptr, /*!< Address to write to */
          U8 src, /*!< Src data to write */
          U32 bank /*!< Bank to program to */
      );
      //! Reset the bypass mode
      //!
      nor_mgr_status unlock_bypass_reset(
          U32 bank /*!< Bank to reset */
      );

      volatile bool m_cancel; /*!< Cancel flag to stop the writes*/
      Os::Mutex m_cancel_lock; /*!< Lock for canceling */
    };

} // end namespace Drv
#endif
