// ======================================================================
// \title  Rules/Write.cpp
// \author ciankc
// \brief  Rules/Write class implementation
//
// \copyright
// Copyright (C) 2019 California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
// ======================================================================

#include "fprime-sphinx-drivers/Test/Scenario/Test/State.hpp"
#include "fprime-sphinx-drivers/Random/Random.hpp"
#include "Write.hpp"

namespace Drv {
  // ----------------------------------------------------------------------
  // Rule definitions
  // ----------------------------------------------------------------------

  bool TestState ::
    precondition__Write__OK(void) const
  {
    bool result = true;
    //precondition is true when the state is idle
    result &= (this->component.m_state == NORMGR_IDLE);
    //printf("Precondition for Write OK result is: %d\n", result);
    return result;
  }

  void TestState ::
    action__Write__OK(void)
  {
    //printf("Action for Write OK\n");

    //base address of NOR flash
    U32 addr = 0x00000000;
    //write 8 bytes of data
    U8 data[8] = {0xDE, 0xAD, 0xBE, 0xEF, 0x12, 0x34, 0x56, 0x78};
    U32 mark = 0xDEADBEEF;
    U32 mark2 = 0x12345678;

    //without edac disabled
    this->invoke_to_request_write(0, addr, data, 8, 0);
    this->component.doDispatch();

    U32 val = readReg(addr);
    ASSERT_EQ(val, mark);
    U32 next_addr = addr + 0x4;
    val = readReg(next_addr);
    ASSERT_EQ(val, mark2);
    ASSERT_EQ(this->component.m_state, NORMGR_WRITING);

    U8 data2[8] = {0xCC, 0xCC, 0xCC, 0xCC, 0x87, 0x65, 0x43, 0x21};
    U32 mark3 = 0xCCCCCCCC;
    U32 mark4 = 0x87654321;
    U32 addr2 = 0x10000000;
    this->clearHistory();

    this->component.m_state = NORMGR_IDLE;

    //with edac disabled
    this->invoke_to_request_write(0, addr2, data2, 8, 1);
    this->component.doDispatch();

    val = readReg(addr2);
    ASSERT_EQ(val, mark3);
    val = readReg(addr2+0x4);
    ASSERT_EQ(val, mark4);

    ASSERT_EQ(this->component.m_state, NORMGR_WRITING);
    this->component.m_state = NORMGR_IDLE;
  }

  bool TestState ::
    precondition__Write__ERROR(void) const
  {
    bool result = true;
    //precondition is always true
    //printf("Precondition for Write ERROR result is: %d\n", result);
    return result;
  }

  void TestState ::
    action__Write__ERROR(void)
  {
    //printf("Action for Write ERROR\n");

    U32 addr = 0x00000000;
    U8 data[5] = {1,2,3,4,5};
    writeReg(0x00000000, 0xDEADC0DE);

    this->component.m_state = NORMGR_WRITING;

    this->invoke_to_request_write(0, addr, data, 5, 0);
    this->component.doDispatch();
    ASSERT_EQ(readReg(0x00000000), 0xDEADC0DE);

    this->component.m_state = NORMGR_IDLE;

    //null ptr
    U8* null_ptr = NULL;
    ASSERT_DEATH({this->invoke_to_request_write(0, addr, null_ptr, 8, 0);
                  this->component.doDispatch();},
                 "Assertion");

    //invalid addr
    U32 invalid_addr = 0x30000000;
    ASSERT_DEATH({this->invoke_to_request_write(0, invalid_addr, data, 5, 0);
	       this->component.doDispatch();},
	       "Assertion");

    //invalid count
    U32 invalid_count = 70000;
    ASSERT_DEATH({this->invoke_to_request_write(0, addr, data, invalid_count, 0);
	       this->component.doDispatch();},
                 "Assertion");

    //out of bounds write
    U32 close_addr = 0x1FFFFFFF;
    ASSERT_DEATH({this->invoke_to_request_write(0, close_addr, data, 5, 0);
	       this->component.doDispatch();},
	       "Assertion");

  }


  namespace Write {

    // ----------------------------------------------------------------------
    // Tests
    // ----------------------------------------------------------------------

    Tester :: Tester(const char* compName, U32 timeout)
      : testState(compName, timeout)
    {

    }

    void Tester ::
      OK(void)
    {
      //apply rule
      this->ruleOK.apply(this->testState);
    }

    void Tester ::
      ERROR(void)
    {
      //apply rule
      this->ruleERROR.apply(this->testState);
    }

  }

}
