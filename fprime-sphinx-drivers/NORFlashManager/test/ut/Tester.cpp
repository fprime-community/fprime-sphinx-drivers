// ====================================================================== 
// \title  NORFlashManager.hpp
// \author ciankc
// \brief  cpp file for NORFlashManager test harness implementation class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
// ====================================================================== 

#include "Tester.hpp"

#define INSTANCE 0
#define MAX_HISTORY_SIZE 10
#define QUEUE_DEPTH 10

namespace Drv {

  // ----------------------------------------------------------------------
  // Construction and destruction 
  // ----------------------------------------------------------------------

  Tester ::
  Tester(const char* compName,
         U32 timeout) : 
#if FW_OBJECT_NAMES == 1
      NORFlashManagerGTestBase("Tester", MAX_HISTORY_SIZE),
      component(compName, timeout)
#else
      NORFlashManagerGTestBase(MAX_HISTORY_SIZE),
      component()
#endif
  {
    this->initComponents();
    this->connectPorts();
  }

  Tester ::
    ~Tester(void) 
  {
    
  }

  // ----------------------------------------------------------------------
  // Tests 
  // ----------------------------------------------------------------------

  void Tester ::
    toDo(void) 
  {
    // TODO
  }

  // ----------------------------------------------------------------------
  // Handlers for typed from ports
  // ----------------------------------------------------------------------

  void Tester ::
    from_PingResponse_handler(
        const NATIVE_INT_TYPE portNum,
        U32 key
    )
  {
    ASSERT_EQ(key, 0xCC);
    this->pushFromPortEntry_PingResponse(key);
  }

  void Tester ::
    from_verification_done_handler(
        const NATIVE_INT_TYPE portNum,
        I32 valid_nor,
        U32 read_blc_checksum,
        U32 read_fsw_checksum,
        U32 cptd_blc_checksum,
        U32 cptd_fsw_checksum
    )
  {
    ASSERT_EQ(read_blc_checksum, 0);
    ASSERT_EQ(read_fsw_checksum, 0);
    this->pushFromPortEntry_verification_done(valid_nor, read_blc_checksum, read_fsw_checksum, cptd_blc_checksum, cptd_fsw_checksum);
  }

  void Tester ::
    from_erase_done_handler(
        const NATIVE_INT_TYPE portNum,
         I8 done,
        U32 context1,
        U32 context2
    )
  {
    this->pushFromPortEntry_erase_done(done, context1, context2);
  }

  void Tester ::
    from_read_done_handler(
        const NATIVE_INT_TYPE portNum,
        I8 done,
        U32 context1,
        U32 context2
    )
  {
    this->pushFromPortEntry_read_done(done, context1, context2);
  }

  void Tester ::
    from_worker_verify_handler(
        const NATIVE_INT_TYPE portNum,
        U32 blc_filesize,
        U32 fsw_filesize
    )
  {
    ASSERT_EQ(blc_filesize, 1024);
    ASSERT_EQ(fsw_filesize, 512);
    this->pushFromPortEntry_worker_verify(blc_filesize, fsw_filesize);
  }

  void Tester ::
    from_worker_write_handler(
        const NATIVE_INT_TYPE portNum,
        U32 dest,
        U8 *src,
        U32 count,
        U32 bank
    )
  {
    U32 data = 0;
    U32 j = 0;
    for(U32 i = 0; i < count; i++)
    {
      data |= (src[i] << (3-i)*8);
      j++;
      if(j == 4)
      {
        writeReg(dest, data);
        dest += 0x4;
        j = 0;
        data = 0;
      }
    } 
    this->pushFromPortEntry_worker_write(dest, src, count, bank);
  }

  void Tester ::
    from_write_done_handler(
        const NATIVE_INT_TYPE portNum,
        I8 done,
        U32 context1,
        U32 context2
    )
  {
    this->pushFromPortEntry_write_done(done, context1, context2);
  }

  void Tester ::
    from_worker_erase_handler(
        const NATIVE_INT_TYPE portNum,
        U32 bank_addr
    )
  {
    //chip erase sequence 
    writeReg(0xaaa, 0xaa);
    writeReg(0x555, 0x55);
    writeReg(0xaaa, 0x80);
    writeReg(0xaaa, 0xaa);
    writeReg(0x555, 0x55);
    writeReg(0xaaa, 0x10);
    this->pushFromPortEntry_worker_erase(bank_addr);
  }

  void Tester ::
    from_worker_cancel_handler(
        const NATIVE_INT_TYPE portNum
    )
  {
    ASSERT_TRUE((this->component.m_timer <= 1001 && this->component.m_timer > 100) || this->component.m_timer == 0);
    this->pushFromPortEntry_worker_cancel();
  }

  void Tester ::
    from_worker_reset_handler(
        const NATIVE_INT_TYPE portNum,
        U32 dontcare_addr
    )
  {
    ASSERT_EQ(dontcare_addr, 0);
    this->pushFromPortEntry_worker_reset(dontcare_addr);
  }

  void Tester ::
    from_worker_read_handler(
        const NATIVE_INT_TYPE portNum,
        U8 *dest,
        U32 src,
        U32 count,
        U32 bank
    )
  {
    U32 val = readReg(src);
    U32 j = 0;
    for(U32 i = 0; i < count; i++)
    {
      dest[i] = (val >> ((3-i)*8));
      j++;
      if(j == 4)
      {
        j = 0;
        val = readReg(src+0x4);
      }
    } 
    this->pushFromPortEntry_worker_read(dest, src, count, bank);
  }

  // ----------------------------------------------------------------------
  // Helper methods 
  // ----------------------------------------------------------------------

  void Tester ::
    connectPorts(void) 
  {

    // get_bl_size
    this->connect_to_get_bl_size(
        0,
        this->component.get_get_bl_size_InputPort(0)
    );

    // PingRecv
    this->connect_to_PingRecv(
        0,
        this->component.get_PingRecv_InputPort(0)
    );

    // request_verification
    this->connect_to_request_verification(
        0,
        this->component.get_request_verification_InputPort(0)
    );

    // cmdIn
    this->connect_to_cmdIn(
        0,
        this->component.get_cmdIn_InputPort(0)
    );

    // get_fsw_size
    this->connect_to_get_fsw_size(
        0,
        this->component.get_get_fsw_size_InputPort(0)
    );

    // request_write
    this->connect_to_request_write(
        0,
        this->component.get_request_write_InputPort(0)
    );

    // worker_done
    this->connect_to_worker_done(
        0,
        this->component.get_worker_done_InputPort(0)
    );

    // request_read
    this->connect_to_request_read(
        0,
        this->component.get_request_read_InputPort(0)
    );

    // schedIn
    this->connect_to_schedIn(
        0,
        this->component.get_schedIn_InputPort(0)
    );

    // request_erase
    this->connect_to_request_erase(
        0,
        this->component.get_request_erase_InputPort(0)
    );

    // eventOut
    this->component.set_eventOut_OutputPort(
        0, 
        this->get_from_eventOut(0)
    );

    // PingResponse
    this->component.set_PingResponse_OutputPort(
        0, 
        this->get_from_PingResponse(0)
    );

    // verification_done
    this->component.set_verification_done_OutputPort(
        0, 
        this->get_from_verification_done(0)
    );

    // erase_done
    this->component.set_erase_done_OutputPort(
        0, 
        this->get_from_erase_done(0)
    );

    // read_done
    this->component.set_read_done_OutputPort(
        0, 
        this->get_from_read_done(0)
    );

    // worker_verify
    this->component.set_worker_verify_OutputPort(
        0, 
        this->get_from_worker_verify(0)
    );

    // timeCaller
    this->component.set_timeCaller_OutputPort(
        0, 
        this->get_from_timeCaller(0)
    );

    // cmdResponse
    this->component.set_cmdResponse_OutputPort(
        0, 
        this->get_from_cmdResponse(0)
    );

    // worker_write
    this->component.set_worker_write_OutputPort(
        0, 
        this->get_from_worker_write(0)
    );

    // cmdReg
    this->component.set_cmdReg_OutputPort(
        0, 
        this->get_from_cmdReg(0)
    );

    // write_done
    this->component.set_write_done_OutputPort(
        0, 
        this->get_from_write_done(0)
    );

    // worker_erase
    this->component.set_worker_erase_OutputPort(
        0, 
        this->get_from_worker_erase(0)
    );

    // worker_cancel
    this->component.set_worker_cancel_OutputPort(
        0, 
        this->get_from_worker_cancel(0)
    );

    // worker_reset
    this->component.set_worker_reset_OutputPort(
        0, 
        this->get_from_worker_reset(0)
    );

    // worker_read
    this->component.set_worker_read_OutputPort(
        0, 
        this->get_from_worker_read(0)
    );

    // LogText
    this->component.set_LogText_OutputPort(
        0, 
        this->get_from_LogText(0)
    );

  }

  void Tester ::
    initComponents(void) 
  {
    this->init();
    this->component.init(
        QUEUE_DEPTH, INSTANCE
    );
  }

} // end namespace Drv
