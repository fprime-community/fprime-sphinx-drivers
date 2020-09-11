// ======================================================================
// \title  NORFlashManagerImpl.cpp
// \author ortega
// \brief  cpp file for NORFlashManager component implementation class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
// ======================================================================


#include <fprime-sphinx-drivers/NORFlashManager/NORFlashManagerComponentImpl.hpp>
#include "Fw/Types/BasicTypes.hpp"
#include "Fw/Types/Assert.hpp"
#include <fprime-sphinx-drivers/NOR/nor.hpp>
#include <fprime-sphinx-drivers/NORFlashManager/bootloader_defs.hpp>
extern "C" {
#include <fprime-sphinx-drivers/Util/SphinxDrvFTMCTRLUtil.h>
#include <stddef.h>
#ifdef TGT_OS_TYPE_VXWORKS
    #include "intLib.h"
    #include "taskLib.h"

#endif
};
#include <fprime-sphinx-drivers/Util/SphinxDrvBitUtil.hpp>
#include <fprime-sphinx-drivers/Util/SphinxDrvUtil.hpp>
#include <fprime-sphinx-drivers/NORFlashDriver/NORFlashDriverComponentImpl.hpp>

namespace Drv {

  // ----------------------------------------------------------------------
  // Construction, initialization, and destruction
  // ----------------------------------------------------------------------

  NORFlashManagerComponentImpl ::
#if FW_OBJECT_NAMES == 1
    NORFlashManagerComponentImpl(
        const char *const compName,
        U32 timeout
    ) :
      NORFlashManagerComponentBase(compName),
#else
    NORFlashManagerImpl(U32 timeout) :
#endif
    m_bank_addr(NOR_FLASH_BASE_ADDR),
    m_state(NORMGR_IDLE),
    m_timer(0),
    m_erase_timeout(timeout),
    m_write_timeout(NOR_POLL_WRITE_TIMEOUT),
    m_verify_timeout(timeout),
    m_reset_opcode(0),
    m_reset_cmd_seq(0),
    m_using_prom_edac(false)
  {

  }

  void NORFlashManagerComponentImpl ::
    init(
        const NATIVE_INT_TYPE queueDepth,
        const NATIVE_INT_TYPE instance
    )
  {
    NORFlashManagerComponentBase::init(queueDepth, instance);

    this->read_and_store_edac_status();
  }

  NORFlashManagerComponentImpl ::
    ~NORFlashManagerComponentImpl(void)
  {

  }

  // ----------------------------------------------------------------------
  // Handler implementations for user-defined typed input ports
  // ----------------------------------------------------------------------

  I32 NORFlashManagerComponentImpl ::
    get_bl_size_handler(
        const NATIVE_INT_TYPE portNum,
        U32 &size
    )
  {
#if defined(BUILD_SPHINX)
    const struct bl_headers *fsw_base = (struct bl_headers *)NOR_FSW_IMAGE_START_LOCATION;
    FW_ASSERT(fsw_base);
    size = fsw_base->blc_num_bytes;
#else
    size = 0;
#endif
    return NORMGR_OK;
  }

  void NORFlashManagerComponentImpl ::
    request_erase_handler(
        const NATIVE_INT_TYPE portNum,
        U8 bank_number
    )
  {
    // Return out if NOR is already erasing
    if(m_state == NORMGR_ERASING) {
      this->log_WARNING_HI_NOR_ALREADY_ERASING();
      return;
    }

    // Cannot erase if not in IDLE state
    if(m_state != NORMGR_IDLE)
    {
      // signal that we did not erase chip
      this->log_WARNING_HI_NOR_ERASE_BUSY(m_state, NORMGR_IDLE, NORMGR_BUSY);
      this->erase_done_out(0, NORMGR_BUSY, 0, 0);
      return;
    }

    // Validate bank_number and use
    // appropriate bank_addr
    switch(bank_number)
    {
      case 0:
        m_bank_addr = NOR_FLASH_BASE_ADDR_0;
        break;
      case 1:
        m_bank_addr = NOR_FLASH_BASE_ADDR_1;
        break;
      case 2:
        m_bank_addr = NOR_FLASH_BASE_ADDR_2;
        break;
      case 3:
        m_bank_addr = NOR_FLASH_BASE_ADDR_3;
        break;
      default:
        // signal that we did not erase chip
        this->log_WARNING_HI_NOR_ERASE_FAIL(NORMGR_FAIL);
        this->erase_done_out(0, NORMGR_FAIL, 0, 0);
        this->reset_mgr_state();
        return;
    }
    // Start erasing whole chip
    this->disable_prom_edac();
    this->log_ACTIVITY_LO_NOR_ERASING();
    this->worker_erase_out(0, m_bank_addr);
    m_state = NORMGR_ERASING;
  }


  void NORFlashManagerComponentImpl ::
    request_write_handler(
        const NATIVE_INT_TYPE portNum,
        U32 dest,
        U8 *src,
        U32 count,
        bool disable_edac
    )
  {
    if(m_state != NORMGR_IDLE)
    {
      // Signal that write failed to write
      this->write_done_out(0, NORMGR_BUSY, 0, 0);
      return;
    }

    FW_ASSERT(src != NULL);
    FW_ASSERT(count <= NOR_FLASH_MAX_BYTES_RW, count);
    FW_ASSERT(dest < NOR_FLASH_HIGH_ADDR, dest);
    // Make sure when we write, we will stay within the NOR_FLASH memory bounds.
    FW_ASSERT((NOR_FLASH_HIGH_ADDR - dest)  >= count);
    //Set timer to zero, nor to write and go!
    m_timer = 0;
    m_state = NORMGR_WRITING;
    if(disable_edac) {
      this->disable_prom_edac();
    }
    this->worker_write_out(portNum, dest, src, count, m_bank_addr);
  }

  void NORFlashManagerComponentImpl ::
    worker_done_handler(
        const NATIVE_INT_TYPE portNum,
        I8 done,
        U32 context1,
        U32 context2
    )
  {
    nor_mgr_status status = static_cast<nor_mgr_status>(done);
    switch (m_state) {
        case NORMGR_WRITING:
            //Handle printing of EVRs for return state
            switch (status)
            {
                case NORMGR_OK:
                case NORMGR_SUCCESSFUL_PROGRAM:
                    status = NORMGR_OK;
                    break;
                case NORMGR_TIMEOUT:
                    this->log_WARNING_HI_NOR_WRITE_TIMEOUT();
                    break;
                case NORMGR_FAILED_TO_UNLOCK:
                    this->log_WARNING_HI_NOR_UNLOCK_BYPASS_FAILED();
                    break;
                case NORMGR_FAILED_TO_READ:
                    this->log_WARNING_HI_NOR_FAILED_TO_VERIFY_DATA(context1, static_cast<U8>(context2));
                    break;
                case NORMGR_FAILED_TO_UNLOCK_PROGRAM:
                    this->log_WARNING_HI_NOR_UNLOCK_BYPASS_PROGRAM_FAILED();
                    break;
                case NORMGR_FAILED_TO_READ_RESET_BYPASS:
                    this->log_WARNING_HI_NOR_FAILED_TO_VERIFY_DATA(context1, static_cast<U8>(context2));
                    this->log_WARNING_HI_NOR_UNLOCK_BYPASS_RESET_FAILED();
                    break;
                case NORMGR_FAILED_TO_UNLOCK_PROGRAM_RESET_BYPASS:
                    this->log_WARNING_HI_NOR_UNLOCK_BYPASS_PROGRAM_FAILED();
                    this->log_WARNING_HI_NOR_UNLOCK_BYPASS_RESET_FAILED();
                    break;
                case NORMGR_FAILED_TO_RESET:
                    this->log_WARNING_HI_NOR_FAILED_TO_VERIFY_DATA(context1, static_cast<U8>(context2));
                    this->log_WARNING_HI_NOR_FAILED_TO_RESET();
                    break;
                case NORMGR_FAILED_TO_RESET_BYPASS_RESET:
                    this->log_WARNING_HI_NOR_FAILED_TO_VERIFY_DATA(context1, static_cast<U8>(context2));
                    this->log_WARNING_HI_NOR_UNLOCK_BYPASS_RESET_FAILED();
                    this->log_WARNING_HI_NOR_FAILED_TO_RESET();
                    break;
                //Any other states encountered on a writing return is a software error
                default:
                    FW_ASSERT(false);
                    break;
            }
            this->write_done_out(0, status, context1, context2);
            break;
        case NORMGR_ERASING:
            //Handle printing of EVRs for return state
            switch (status)
            {
                case NORMGR_OK:
                case NORMGR_SUCCESSFUL_ERASE:
                    status = NORMGR_OK;
                    this->log_ACTIVITY_LO_NOR_ERASE_DONE();
                    break;
                case NORMGR_FAILED_TO_RESET:
                    this->log_WARNING_HI_NOR_FAILED_TO_RESET();
                    break;
                case NORMGR_TIMEOUT:
                    this->log_WARNING_HI_NOR_ERASE_TIMEOUT();
                    break;
                case NORMGR_FAILED_TO_ERASE:
                    this->log_WARNING_HI_NOR_ERASE_FAIL(status);
                    break;
                case NORMGR_FAILED_TO_TIMEOUT_RESET:
                    this->log_WARNING_HI_NOR_ERASE_TIMEOUT();
                    this->log_WARNING_HI_NOR_FAILED_TO_RESET();
                    break;
                case NORMGR_FAILED_TO_ERASE_RESET:
                    this->log_WARNING_HI_NOR_FAILED_TO_RESET();
                    this->log_WARNING_HI_NOR_ERASE_FAIL(status);
                    break;
                //Any other states encountered on a erase return is a software error
                default:
                    FW_ASSERT(false);
                    break;
            }
            this->erase_done_out(0, status, context1, context2);
            break;
        case NORMGR_READING:
            switch (status)
            {
                case NORMGR_OK:
                    break;
                case NORMGR_FAILED_TO_READ:
                    this->log_WARNING_HI_NOR_FAILED_TO_READ_DATA(context1, context2);
                    break;
                case NORMGR_TIMEOUT:
                    this->log_WARNING_HI_NOR_READ_TIMEOUT();
                    break;
                default:
                  FW_ASSERT(false);
                  break;
            }
            this->read_done_out(0, status, context1, context2);
          break;
        case NORMGR_RESETING:
            if (status != NORMGR_OK) {
                this->log_WARNING_HI_NOR_FAILED_TO_RESET();
                this->cmdResponse_out(m_reset_opcode, m_reset_cmd_seq, Fw::COMMAND_EXECUTION_ERROR);
            }
            else
            {
                this->cmdResponse_out(m_reset_opcode, m_reset_cmd_seq, Fw::COMMAND_OK);
            }
            break;
        case NORMGR_VERIFYING:
        {
            // read blc/fsw checksum values
#if defined(BUILD_SPHINX)
            const struct bl_headers *fsw_base = (struct bl_headers *)NOR_FSW_IMAGE_START_LOCATION;
            FW_ASSERT(fsw_base);
            const U32 read_blc_checksum = fsw_base->blc_checksum;
            const U32 read_fsw_checksum = fsw_base->fsw_checksum;
#else
            const U32 read_blc_checksum = 0;
            const U32 read_fsw_checksum = 0;
#endif

            //Handle printing of EVRs for verifying state
            switch (status)
            {
                case NORMGR_OK:
                case NORMGR_SUCCESSFUL_VERIFY:
                    this->log_ACTIVITY_LO_NOR_CHECKSUM_VERIFY_DONE();
                    break;
                case NORMGR_FAILED_TO_VERIFY:
                    this->log_WARNING_HI_NOR_FAILED_TO_VERIFY_CHECKSUM();
                    break;
                default:
                    FW_ASSERT(false);
                    break;
            }

            this->verification_done_out(0, status, read_blc_checksum, read_fsw_checksum, context1, context2);
        }
            break;
        //No other states can receive messages from worker
        default:
            FW_ASSERT(false);
            break;
    }
    this->reset_mgr_state();
  }

  void NORFlashManagerComponentImpl ::
    schedIn_handler(
        const NATIVE_INT_TYPE portNum,
        NATIVE_UINT_TYPE context
    )
  {
      //Use max possible timeout, if not in a timeout state
      //This is safe, as m_timer only increments in timeout states
      U32 current_timeout = 0xFFFFFFFF;
      switch(m_state)
      {
          case NORMGR_ERASING:
              m_timer++;
              current_timeout = m_erase_timeout;
              break;
          case NORMGR_WRITING:
              m_timer++;
              current_timeout = m_write_timeout;
              break;
          case NORMGR_VERIFYING:
              m_timer++;
              current_timeout = m_verify_timeout;
              break;
          default:
              break;
      }
      //Cancel the worker, if we violate the timeout
      if (m_timer > current_timeout) {
          this->worker_cancel_out(0);
      }
  }

  I32 NORFlashManagerComponentImpl ::
    get_fsw_size_handler(
        const NATIVE_INT_TYPE portNum,
        U32 &size
    )
  {
#if defined(BUILD_SPHINX)
    // This size accounts for both the header bytes and the FSW image
    const struct bl_headers *fsw_base = (struct bl_headers *)NOR_FSW_IMAGE_START_LOCATION;
    FW_ASSERT(fsw_base);
    size = fsw_base->fsw_num_bytes;
    size += sizeof(struct bl_headers);
#else
    size = 0;
#endif
    return NORMGR_OK;
  }

  void NORFlashManagerComponentImpl ::
    request_read_handler(
        const NATIVE_INT_TYPE portNum,
        U32 src,
        U8 *dest,
        U32 count,
        bool disable_edac
    )
  {
    if(m_state != NORMGR_IDLE)
    {
      // Signal that write failed to write
      this->read_done_out(0, NORMGR_BUSY, 0, 0);
      return;
    }

    // src is memory address in NOR to read from
    // and dest is the buffer in which to store what is read from src
    FW_ASSERT(dest != NULL);
    FW_ASSERT(count <= NOR_FLASH_MAX_BYTES_RW, count);
    FW_ASSERT(src < NOR_FLASH_HIGH_ADDR, src);
    // Make sure when we read, we will stay within the NOR_FLASH memory bounds.
    FW_ASSERT((NOR_FLASH_HIGH_ADDR - src)  >= count);
    //Set timer to zero, nor to read and go!
    m_timer = 0;
    m_state = NORMGR_READING;
    if(disable_edac) {
      this->disable_prom_edac();
    }
    this->worker_read_out(portNum, dest, src, count, m_bank_addr);
  }

  void NORFlashManagerComponentImpl ::
    PingRecv_handler(
        const NATIVE_INT_TYPE portNum,
        U32 key
    )
  {
      if (this->isConnected_PingResponse_OutputPort(0))
      {
        this->PingResponse_out(0, key);
      }
  }

  void NORFlashManagerComponentImpl ::
    request_verification_handler(
        const NATIVE_INT_TYPE portNum,
        U32 blc_filesize,
        U32 fsw_filesize
    )
  {
    if(m_state != NORMGR_IDLE)
    {
      // Signal that verification failed
      this->log_WARNING_HI_NOR_VERIFY_BUSY(m_state, NORMGR_IDLE);
      this->verification_done_out(0, NORMGR_BUSY, 0, 0, 0, 0);
      return;
    }

    //Set timer to zero
    m_timer = 0;
    m_state = NORMGR_VERIFYING;
    this->worker_verify_out(portNum, blc_filesize, fsw_filesize);
  }

  // ----------------------------------------------------------------------
  // Command handler implementations
  // ----------------------------------------------------------------------

  void NORFlashManagerComponentImpl ::
    NOR_FLASH_RESET_cmdHandler(
        const FwOpcodeType opCode,
        const U32 cmdSeq,
        U8 bank_number
    )
  {
      U32 bank_addr;
      m_reset_opcode = opCode;
      m_reset_cmd_seq = cmdSeq;
      // Validate bank_number and use
      // appropriate bank_addr
      switch(bank_number)
      {
          case 0:
              bank_addr = NOR_FLASH_BASE_ADDR_0;
              break;
          case 1:
              bank_addr = NOR_FLASH_BASE_ADDR_1;
              break;
          case 2:
              bank_addr = NOR_FLASH_BASE_ADDR_2;
              break;
          case 3:
              bank_addr = NOR_FLASH_BASE_ADDR_3;
              break;
          default:
              // signal that we did not reset chip
              this->log_WARNING_HI_NOR_FAILED_TO_RESET();
              this->cmdResponse_out(opCode, cmdSeq, Fw::COMMAND_EXECUTION_ERROR);
              return;
      }
      // Should not be in erase mode otherwise a reset command may get ignored
      // during the chip's erasing
      if(m_state == NORMGR_ERASING || m_state == NORMGR_RESETING)
      {
          this->log_WARNING_HI_NOR_RESET_FAIL(m_state, NORMGR_IDLE);
          this->cmdResponse_out(opCode, cmdSeq, Fw::COMMAND_EXECUTION_ERROR);
      }
      else
      {
          this->worker_cancel_out(0);
          this->log_ACTIVITY_LO_NOR_RESETTING();
          this->worker_reset_out(0, bank_addr);
      }
      m_state = NORMGR_RESETING;
  }

  void NORFlashManagerComponentImpl ::
    NOR_FLASH_SET_WRITE_TIMEOUT_cmdHandler(
        const FwOpcodeType opCode,
        const U32 cmdSeq,
        U32 timeout
    )
  {
    this->m_write_timeout = timeout;
    this->cmdResponse_out(opCode,cmdSeq,Fw::COMMAND_OK);
  }

  void NORFlashManagerComponentImpl ::
    NOR_FLASH_SET_ERASE_TIMEOUT_cmdHandler(
        const FwOpcodeType opCode,
        const U32 cmdSeq,
        U32 timeout
    )
  {
    this->m_erase_timeout = timeout;
    this->cmdResponse_out(opCode,cmdSeq,Fw::COMMAND_OK);
  }

  void NORFlashManagerComponentImpl ::
    NOR_FLASH_SET_VERIFY_TIMEOUT_cmdHandler(
        const FwOpcodeType opCode,
        const U32 cmdSeq,
        U32 timeout
    )
  {
    this->m_verify_timeout = timeout;
    this->cmdResponse_out(opCode,cmdSeq,Fw::COMMAND_OK);
  }

  // ----------------------------------------------------------------------
  // Helper methods
  // ----------------------------------------------------------------------

  void NORFlashManagerComponentImpl ::
    disable_prom_edac(void)
  {
#if defined(BUILD_SPHINX)
    this->read_and_store_edac_status();
    Drv::clearBitAtomic(SPHINX_FTMCTRL_MCFG3, SPHINX_FTMCTRL_PROM_EDAC_BIT);
#endif
  }

  void NORFlashManagerComponentImpl ::
    enable_prom_edac(void)
  {
#if defined(BUILD_SPHINX)
    if(m_using_prom_edac) {
      Drv::setBitAtomic(SPHINX_FTMCTRL_MCFG3, SPHINX_FTMCTRL_PROM_EDAC_BIT);
    }
#endif
  }

  void NORFlashManagerComponentImpl ::
    read_and_store_edac_status(void)
  {
#if defined(BUILD_SPHINX)
    // get value at this address
    U32 val = *((volatile U32*)SPHINX_FTMCTRL_MCFG3);

    // we care only about the prom edac bit
    val = (val >> SPHINX_FTMCTRL_PROM_EDAC_BIT) & 0x1;

    // check if prom edac bit was set or not
    m_using_prom_edac = (val == 1);
#endif
  }

  void NORFlashManagerComponentImpl ::
    reset_mgr_state(void)
  {
    m_timer = 0;
    m_state = NORMGR_IDLE;
    this->enable_prom_edac();
  }

} // end namespace Drv
