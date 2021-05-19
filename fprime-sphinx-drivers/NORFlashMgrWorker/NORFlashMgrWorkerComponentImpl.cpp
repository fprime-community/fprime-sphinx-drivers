
// \title  NORFlashMgrWorkerImpl.cpp
// \author arizvi,ortega
// \brief  cpp file for NORFlashMgrWorker component implementation class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
// ======================================================================


#include <fprime-sphinx-drivers/NORFlashMgrWorker/NORFlashMgrWorkerComponentImpl.hpp>
#include <fprime-sphinx-drivers/NORFlashDriver/NORFlashDriverComponentImpl.hpp>
#include <fprime-sphinx-drivers/FPGADriver/FPGADriverComponentImpl.hpp>
#include "Fw/Types/BasicTypes.hpp"
#include <fprime-sphinx-drivers/NORFlashManager/bootloader_defs.hpp>
#include <Os/Log.hpp>
#include <Utils/Hash/Hash.hpp>
#include <fprime-sphinx-drivers/Util/SphinxDrvUtil.hpp>

#ifdef TGT_OS_TYPE_VXWORKS
extern "C" {
    #include <taskLib.h>
    #include <intLib.h>
};
#endif

namespace Drv {

  // ----------------------------------------------------------------------
  // Construction, initialization, and destruction
  // ----------------------------------------------------------------------

    NORFlashMgrWorkerComponentImpl ::
#if FW_OBJECT_NAMES == 1
    NORFlashMgrWorkerComponentImpl(
        const char *const compName
    ) :
      NORFlashMgrWorkerComponentBase(compName),
#else
    NORFlashMgrWorkerImpl(void),
#endif
    m_cancel(false)
  {

  }

  void NORFlashMgrWorkerComponentImpl ::
    init(
        const NATIVE_INT_TYPE queueDepth,
        const NATIVE_INT_TYPE instance
    )
  {
    NORFlashMgrWorkerComponentBase::init(queueDepth, instance);
  }

  NORFlashMgrWorkerComponentImpl ::
    ~NORFlashMgrWorkerComponentImpl(void)
  {

  }

  // ----------------------------------------------------------------------
  // Handler implementations for user-defined typed input ports
  // ----------------------------------------------------------------------

  void NORFlashMgrWorkerComponentImpl ::
    cancel_handler(
        const NATIVE_INT_TYPE portNum
    )
  {
      m_cancel_lock.lock();
      m_cancel = true;
      m_cancel_lock.unLock();
  }

  void NORFlashMgrWorkerComponentImpl ::
    read_block_handler(
        const NATIVE_INT_TYPE portNum,
        U8 *dest,
        U32 src,
        U32 count,
        U32 bank
    )
  {
      U32 i = 0;
      U32 context1 = 0;
      U32 context2 = 0;
      nor_mgr_status status = NORMGR_OK;

      m_cancel_lock.lock();
      m_cancel = false;
      m_cancel_lock.unLock();
      FW_ASSERT(dest);
      FW_ASSERT(bank < NOR_WORKER_BANK_COUNT, bank);
      FW_ASSERT(count <= NOR_WORKER_MAX_BLOCK_SIZE, count);

      //Read every byte
      for(i = 0; i < count && i < NOR_WORKER_MAX_BLOCK_SIZE && !m_cancel; i++)
      {
          I8 stat = 0;
          U32 src_addr = src + i;
          U8 *dest_ptr = dest + i;
          FW_ASSERT(dest_ptr);
          context1 = src_addr;
          stat = this->read_out(0, src_addr, dest_ptr); // read byte
          if(stat != 0) {
              status = NORMGR_FAILED_TO_READ;
              break;
          }
      } //End byte-read loop

      context2 = i;
      //Cancel yields timeout, as it will be canceled
      if (m_cancel) {
          this->statusOut_out(0, static_cast<U8>(NORMGR_TIMEOUT), context1, context2);
      }

      this->statusOut_out(0, static_cast<U8>(status), context1, context2);
  }

  void NORFlashMgrWorkerComponentImpl ::
    write_block_handler(
        const NATIVE_INT_TYPE portNum,
        U32 dest,
        U8 *src,
        U32 count,
        U32 bank
    )
  {
      //There are alot of side effects here.
      volatile U32 i = 0;
      volatile U32 retry = 0;
      U32 context1 = 0;
      U32 context2 = 0;
      nor_mgr_status status = NORMGR_OK;

      m_cancel_lock.lock();
      m_cancel = false;
      m_cancel_lock.unLock();
      FW_ASSERT(bank < NOR_WORKER_BANK_COUNT, bank);
      FW_ASSERT(src != NULL);
      FW_ASSERT(count <= NOR_WORKER_MAX_BLOCK_SIZE, count);
      if(this->unlock_bypass(bank) != NORMGR_OK)
      {
          status = NORMGR_FAILED_TO_UNLOCK;
      } else {
          //Retry block write several times
          for (retry = 0; retry < NOR_WORKER_RETRY && !m_cancel; retry++)
          {
              //Write every byte
              for(i = 0; i < count && i < NOR_WORKER_MAX_BLOCK_SIZE && !m_cancel; i++)
              {
                  U32 dest_ptr = dest + i;
                  context1 = dest_ptr;
                  context2 = static_cast<U32>(src[i]);
                  status = this->unlock_bypass_program(dest_ptr, src[i], bank);
                  if (status != NORMGR_OK)
                  {
                      status = NORMGR_FAILED_TO_UNLOCK_PROGRAM;
                      break;
                  }
                  if (!this->verify_data(dest_ptr, src[i]))
                  {
                      status = NORMGR_FAILED_TO_READ;
                      break;
                  }
              } //End byte-write loop
              //If we didn't finish, retry
              if (i != count)
              {
                  continue;
              }
              break;
          } // End retry loop
          //Reset NOR quick program state
          if(this->unlock_bypass_reset(bank) != NORMGR_OK)
          {
              if (status == NORMGR_FAILED_TO_READ) {
                  status = NORMGR_FAILED_TO_READ_RESET_BYPASS;
              } else if (status == NORMGR_FAILED_TO_UNLOCK_PROGRAM) {
                  status = NORMGR_FAILED_TO_UNLOCK_PROGRAM_RESET_BYPASS;
              } else {
                  status = NORMGR_FAILED_TO_RESET_BYPASS;
              }
          }
          //On a read failure, attempt to reset
          if (status == NORMGR_FAILED_TO_READ || status == NORMGR_FAILED_TO_READ_RESET_BYPASS) {
              if (this->reset_nor(bank) != NORMGR_OK) {
                  if (status == NORMGR_FAILED_TO_READ_RESET_BYPASS) {
                      status = NORMGR_FAILED_TO_RESET_BYPASS_RESET;
                  } else {
                      status = NORMGR_FAILED_TO_RESET;
                  }
              }
          }
      } //End else
      //Cancel yields timeout, as it will be canceled
      if (m_cancel) {
          this->statusOut_out(0, static_cast<U8>(NORMGR_TIMEOUT), context1, context2);
      }

      this->statusOut_out(0, static_cast<U8>(status), context1, context2);
  }

  void NORFlashMgrWorkerComponentImpl ::
    reset_handler(
        const NATIVE_INT_TYPE portNum,
        U32 bank
    )
  {
      nor_mgr_status status = reset_all(bank);
      this->statusOut_out(0, static_cast<U8>(status), 0, 0);
  }

  void NORFlashMgrWorkerComponentImpl ::
    verify_handler(
        const NATIVE_INT_TYPE portNum,
        U32 blc_filesize,
        U32 fsw_filesize
    )
  {
    U32 cptd_blc_checksum = 0;
    U32 cptd_fsw_checksum = 0;
    nor_mgr_status status = this->verify_and_validate_nor(blc_filesize, fsw_filesize,
                                                   cptd_blc_checksum, cptd_fsw_checksum);
    this->statusOut_out(0, static_cast<U8>(status), cptd_blc_checksum, cptd_fsw_checksum);
  }

  void NORFlashMgrWorkerComponentImpl ::
    erase_handler(
        const NATIVE_INT_TYPE portNum,
        U32 bank_addr
    )
  {
      volatile U32 i = 0;
      U32 context1 = 0;
      U32 context2 = 0;
      nor_mgr_status status = NORMGR_OK;

      m_cancel_lock.lock();
      m_cancel = false;
      m_cancel_lock.unLock();
      //Reset nor, or exit
      if(this->reset_nor(bank_addr) != NORMGR_OK)
      {
          status = NORMGR_FAILED_TO_RESET;
      }
      //If reset nor didn't fail, start erase or exit
      else if(this->start_erase(bank_addr) != NORMGR_OK)
      {
          status = NORMGR_FAILED_TO_ERASE;
      }
      //If both of the above worked
      else {
          for (i = 0; i < NOR_WORKER_ERASE_CYCLES && !m_cancel; i++)
          {
              context1 = i;
              //Wait for erase to finish
#ifdef TGT_OS_TYPE_VXWORKS
              (void) taskDelay(SYS_CLK_RATE_HZ);
#endif
              status = this->erase_poll(bank_addr);
              if (status != NORMGR_KEEP_POLLING) {
                  break;
              }
          }
          //Wait a bit "for good measure"
#ifdef TGT_OS_TYPE_VXWORKS
          (void) taskDelay(SYS_CLK_RATE_HZ);
#endif
          if (i == NOR_WORKER_ERASE_CYCLES || m_cancel) {
              status = NORMGR_TIMEOUT;
          }
          //If not successful
          if (status != NORMGR_SUCCESSFUL_ERASE && this->reset_nor(bank_addr) != NORMGR_OK) {
              if (status == NORMGR_TIMEOUT) {
                  status = NORMGR_FAILED_TO_TIMEOUT_RESET;
              } else {
                  status = NORMGR_FAILED_TO_ERASE_RESET;
              }
          }
      }

      this->statusOut_out(0, static_cast<U8>(status), context1, context2);
  }

  U32 NORFlashMgrWorkerComponentImpl ::
    checksum_compute(U32 size, U32 image)
  {
    FW_ASSERT(size <= NOR_FSW_MAX_IMG_SIZE, size);

    // Can't check if image is null since it may
    // point to NOR's base address (which may be 0x00000000)
    U64 accum = NOR_FSW_CHECKSUM_SEED;
    U32 count = 0;

    while (size && (count <= NOR_FSW_MAX_IMG_SIZE))
    {
      U8 data;
      I8 stat = this->read_out(0, image, &data);
      if(stat != Drv::NORFlashDriverComponentImpl::NOR_OK) { return 0; }
      accum += data;
      image++;
      // Well, with a 32 bit checksum, we're not likely to carry...
      if (accum & 0xFFFFFFFF00000000ll)
      {
          // If there is a carry
          accum = (accum & 0xFFFFFFFF) + 1;   // Wrap it around

          if (accum & 0xFFFFFFFF00000000ll)
          {
              // In case of another carry
              accum = (accum & 0xFFFFFFFF) + 1;
          }
      }
      size--;
      count++;
    }
    return (U32)accum;
  }

  nor_mgr_status NORFlashMgrWorkerComponentImpl ::
    reset_all(U32 bank)
  {
      nor_mgr_status status = NORMGR_OK;
      m_cancel_lock.lock();
      m_cancel = false;
      m_cancel_lock.unLock();
      //Reset NOR quick program state
      if(this->unlock_bypass_reset(bank) != NORMGR_OK)
      {
          status = NORMGR_FAILED_TO_RESET_BYPASS;
      }
      //Reset global nor
      if (this->reset_nor(bank) != NORMGR_OK) {
          if (status == NORMGR_FAILED_TO_RESET_BYPASS) {
              status = NORMGR_FAILED_TO_RESET_BYPASS_RESET;
          } else {
              status = NORMGR_FAILED_TO_RESET;
          }
      }
      return status;
  }

  nor_mgr_status NORFlashMgrWorkerComponentImpl ::
    erase_poll(U32 addr)
  {
    U8 val;
    I8 stat;

    if(!Drv::isInNorAddrSpace(addr)) { return NORMGR_ADDR_OUT_OF_RANGE; }

    stat = this->read_out(0, addr, &val);
    if(stat != Drv::NORFlashDriverComponentImpl::NOR_OK) { return NORMGR_FAILED_TO_ERASE_POLL; }

    return (val == 0xFF) ? NORMGR_SUCCESSFUL_ERASE : NORMGR_KEEP_POLLING;
  }

  nor_mgr_status NORFlashMgrWorkerComponentImpl ::
      reset_nor(U32 bank_addr)
    {
      // If DQ5 goes high during a program  or erase operation, writing the reset
      // reset command returns the bank to the read mode.
      if(!Drv::isInNorAddrSpace(bank_addr)) { return NORMGR_ADDR_OUT_OF_RANGE; }

      return (this->write_out(0, bank_addr, 0xF0) == Drv::NORFlashDriverComponentImpl::NOR_OK) ? NORMGR_OK : NORMGR_FAIL;
    }

    nor_mgr_status NORFlashMgrWorkerComponentImpl ::
      start_erase(U32 bank_addr)
    {
      I8 stat;

      if(!Drv::isInNorAddrSpace(bank_addr)) { return NORMGR_ADDR_OUT_OF_RANGE; }

      // send the chip erase sequence
      stat = this->write_out(0, ( bank_addr + 0xaaa ),  0xaa );
      if(stat != Drv::NORFlashDriverComponentImpl::NOR_OK) {
          return NORMGR_FAILED_TO_ERASE;
      }

      stat = this->write_out(0, ( bank_addr + 0x555 ),  0x55 );
      if(stat != Drv::NORFlashDriverComponentImpl::NOR_OK) {
          return NORMGR_FAILED_TO_ERASE;
      }

      stat = this->write_out(0, ( bank_addr + 0xaaa ),  0x80 );
      if(stat != Drv::NORFlashDriverComponentImpl::NOR_OK) {
          return NORMGR_FAILED_TO_ERASE;
      }

      stat = this->write_out(0, ( bank_addr + 0xaaa ),  0xaa );
      if(stat != Drv::NORFlashDriverComponentImpl::NOR_OK) {
          return NORMGR_FAILED_TO_ERASE;
      }

      stat = this->write_out(0, ( bank_addr + 0x555 ),  0x55 );
      if(stat != Drv::NORFlashDriverComponentImpl::NOR_OK) {
          return NORMGR_FAILED_TO_ERASE;
      }

      stat = this->write_out(0, ( bank_addr + 0xaaa ),  0x10 );
      if(stat != Drv::NORFlashDriverComponentImpl::NOR_OK) {
          return NORMGR_FAILED_TO_ERASE;
      }

      return NORMGR_OK;
  }

  nor_mgr_status NORFlashMgrWorkerComponentImpl ::
    data_poll_qd7(U32 addr, U8 src, U8 *data)
  {
    FW_ASSERT(data != NULL);
    I8 stat = 0;

    if(!Drv::isInNorAddrSpace(addr)) { return NORMGR_ADDR_OUT_OF_RANGE; }

    stat = this->read_out(0, addr, data);
    if(stat != Drv::NORFlashDriverComponentImpl::NOR_OK) { return NORMGR_FAILED_TO_READ; }

    return (((*data) & DQ7_MASK) == (src & DQ7_MASK)) ? NORMGR_SUCCESSFUL_PROGRAM : NORMGR_KEEP_POLLING;
  }

  nor_mgr_status NORFlashMgrWorkerComponentImpl ::
    verify_and_validate_nor(const U32 blc_num_bytes, const U32 fsw_num_bytes,
                            U32 &cptd_blc_checksum, U32 &cptd_fsw_checksum)
  {
    bool result = true;

#ifdef BUILD_SPHINX
    // read blc/fsw checksum values
    const struct bl_headers *fsw_base = (struct bl_headers *)NOR_FSW_IMAGE_START_LOCATION;
    FW_ASSERT(fsw_num_bytes > sizeof(*fsw_base), fsw_num_bytes, sizeof(*fsw_base));
    const U32 read_blc_checksum = fsw_base->blc_checksum;
    const U32 read_fsw_checksum = fsw_base->fsw_checksum;

    // The checksum starts at address fsw_base+1
    const U32 fsw_num_bytes_to_check = fsw_num_bytes - sizeof(*fsw_base);

    //1. Compute Bootloader checksum
    cptd_blc_checksum = checksum_compute(
            blc_num_bytes,
            (U32)NOR_HW_PROM_BASE
          );

    //2. Compute FSW checksum
    cptd_fsw_checksum = checksum_compute(
          fsw_num_bytes_to_check,
          (U32)(fsw_base+1)
        );

    //3. If computed checksums differ from those of BL and FSW headers
    //   then return false
    result = ((cptd_blc_checksum == read_blc_checksum)
            &&(cptd_fsw_checksum == read_fsw_checksum));
#endif

    return (result) ? NORMGR_OK : NORMGR_FAILED_TO_VERIFY;
  }

  bool NORFlashMgrWorkerComponentImpl ::
    verify_data(U32 addr, U8 src)
  {
    // Using Data# Polling Algorithm
    U32 i;
    U8 data;

    if(!Drv::isInNorAddrSpace(addr)) { return false; }

    if(this->data_poll_qd7(addr, src, &data) == NORMGR_SUCCESSFUL_PROGRAM)
    {
      return src == data; // make sure data matches with what we wrote in
    }

    for(i = 0; (i < NOR_POLL_WRITE_TIMEOUT) && ((data & DQ5_MASK) != DQ5_MASK); i++)
    {
      if(this->data_poll_qd7(addr, src, &data) == NORMGR_SUCCESSFUL_PROGRAM)
      {
        return src == data;
      }
    }

    if(this->data_poll_qd7(addr, src, &data) == NORMGR_SUCCESSFUL_PROGRAM)
    {
      return src == data;
    }

    return false;
  }

  nor_mgr_status NORFlashMgrWorkerComponentImpl ::
    unlock_bypass(U32 bank)
  {
    I8 stat = 0;
    U32 addr;

    // unlock byte-mode sequence
    addr = bank + 0xAAA;
    stat = this->write_out(0, addr, 0xAA);
    if(stat != 0) {
        return NORMGR_FAILED_TO_UNLOCK;
    }

    addr = bank + 0x555;
    stat = this->write_out(0, addr, 0x55);
    if(stat != 0) {
        return NORMGR_FAILED_TO_UNLOCK;
    }

    addr = bank + 0xAAA;
    stat = this->write_out(0, addr, 0x20);
    if(stat != 0) {
        return NORMGR_FAILED_TO_UNLOCK;
    }

    return NORMGR_OK;
  }

  nor_mgr_status NORFlashMgrWorkerComponentImpl ::
    unlock_bypass_program(U32 dest_ptr, U8 src, U32 bank)
  {
    I8 stat = 0;
    if(!Drv::isInNorAddrSpace(dest_ptr)) { return NORMGR_ADDR_OUT_OF_RANGE; }
    // write byte-mode sequence
    stat = this->write_out(0, bank, 0xA0);
    if(stat != 0) {
        return NORMGR_FAILED_TO_UNLOCK_PROGRAM;
    }

    stat = this->write_out(0, dest_ptr, src);
    if(stat != 0) {
        return NORMGR_FAILED_TO_UNLOCK_PROGRAM;
    }

    return NORMGR_OK;
  }
  nor_mgr_status NORFlashMgrWorkerComponentImpl ::
      unlock_bypass_reset(U32 bank)
    {
      I8 stat = 0;

      // write byte-mode sequence
      stat = this->write_out(0, bank, 0x90);
      if(stat != 0) {
          return NORMGR_FAILED_TO_UNLOCK_PROGRAM;
      }

      stat = this->write_out(0, bank, 0x00);
      if(stat != 0) {
          return NORMGR_FAILED_TO_UNLOCK_PROGRAM;
      }

      return NORMGR_OK;
    }
} // end namespace Drv
