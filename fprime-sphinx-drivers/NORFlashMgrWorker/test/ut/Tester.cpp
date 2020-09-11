// ====================================================================== 
// \title  NORFlashMgrWorker.hpp
// \author ciankc
// \brief  cpp file for NORFlashMgrWorker test harness implementation class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
// ====================================================================== 

#include "Tester.hpp"

#define INSTANCE 0
#define MAX_HISTORY_SIZE 1000
#define QUEUE_DEPTH 10

namespace Drv {

  // ----------------------------------------------------------------------
  // Construction and destruction 
  // ----------------------------------------------------------------------

  Tester ::
    Tester(void) : 
#if FW_OBJECT_NAMES == 1
      NORFlashMgrWorkerGTestBase("Tester", MAX_HISTORY_SIZE),
      component("NORFlashMgrWorker")
#else
      NORFlashMgrWorkerGTestBase(MAX_HISTORY_SIZE),
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

  I8 Tester ::
    from_read_handler(
        const NATIVE_INT_TYPE portNum,
        U32 dest,
        U8 *data
    )
  {
    U32 diff = dest % 0x4;
    U32 addr = dest - diff;
    U32 val = readReg(addr);
    U32 mask = 0xff000000 >> (diff*8);
    U32 res = (val & mask) >> ((3-diff)*8);
    *data = (U8) res;
    
    this->pushFromPortEntry_read(dest, data);
    if(dest > 0x10000000)
    {
        return 1;
    }
    return 0;
  }

  void Tester ::
    from_statusOut_handler(
        const NATIVE_INT_TYPE portNum,
        I8 done,
        U32 context1,
        U32 context2
    )
  {
    if(context2 == 0)
    {
      ASSERT_TRUE(done == NORMGR_FAILED_TO_READ | done == NORMGR_SUCCESSFUL_ERASE | done == NORMGR_OK);
    }
    else if(context2 == 8)
    {
      ASSERT_EQ(done, NORMGR_OK);
    }
    else if(context2 == 0xC)
    {
      ASSERT_EQ(done, NORMGR_FAILED_TO_UNLOCK_PROGRAM);
    }

    this->pushFromPortEntry_statusOut(done, context1, context2);
  }

  I8 Tester ::
    from_write_handler(
        const NATIVE_INT_TYPE portNum,
        U32 dest_addr,
        U8 src
    )
  {
    U32 diff = dest_addr % 0x4;
    U32 addr = dest_addr - diff;
    U32 val = src  << ((3-diff)*8);
    U32 prev = readReg(addr);
    writeReg(addr, val | prev);
    this->pushFromPortEntry_write(addr, src);
    if(dest_addr > 0x10000000)
    {
      return 1;
    }
    return 0;
  }

  // ----------------------------------------------------------------------
  // Helper methods 
  // ----------------------------------------------------------------------

  void Tester ::
    connectPorts(void) 
  {

    // cancel
    this->connect_to_cancel(
        0,
        this->component.get_cancel_InputPort(0)
    );

    // erase
    this->connect_to_erase(
        0,
        this->component.get_erase_InputPort(0)
    );

    // reset
    this->connect_to_reset(
        0,
        this->component.get_reset_InputPort(0)
    );

    // verify
    this->connect_to_verify(
        0,
        this->component.get_verify_InputPort(0)
    );

    // write_block
    this->connect_to_write_block(
        0,
        this->component.get_write_block_InputPort(0)
    );

    // read_block
    this->connect_to_read_block(
        0,
        this->component.get_read_block_InputPort(0)
    );

    // read
    this->component.set_read_OutputPort(
        0, 
        this->get_from_read(0)
    );

    // statusOut
    this->component.set_statusOut_OutputPort(
        0, 
        this->get_from_statusOut(0)
    );

    // write
    this->component.set_write_OutputPort(
        0, 
        this->get_from_write(0)
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
