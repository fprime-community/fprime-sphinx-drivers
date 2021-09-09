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
    //precondition is always true
    //printf("Precondition for Write OK result is: %d\n", result);
    return result;
  }

  void TestState ::
    action__Write__OK(void)
  {
    //printf("Action for Write OK\n");

    this->clearHistory();

    //check for error in statusOut
    U8 data[8] = {0xDE, 0xAD, 0xBE, 0xEF, 0x12, 0x34, 0x56, 0x78};
    U32 addr = 0x00001000;
    U32 mark = 0xDEADBEEF;
    U32 mark2 = 0x12345678;

    //clear out registers to begin with
    writeReg(addr, 0x0);
    writeReg(addr+4, 0x0);

    this->invoke_to_write_block(0, addr, data, 8, 0);
    this->component.doDispatch();

    ASSERT_EQ(readReg(addr), mark);
    ASSERT_EQ(readReg(addr+0x4), mark2);

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

    this->clearHistory();

    //check for error in statusOut
    U8 data[4] = {0xCC, 0xCC, 0xCC, 0xCC};
    U32 addr = 0x20000000;
    this->invoke_to_write_block(0, addr, data, 4, 0);
    this->component.doDispatch();

    //null ptr
    U8* null_data = NULL;
    ASSERT_DEATH({this->invoke_to_write_block(0, addr, null_data, 4, 0);
        this->component.doDispatch();},
      "Assertion");

    //invalid bank
    ASSERT_DEATH({this->invoke_to_write_block(0, addr, data, 4, 5);
        this->component.doDispatch();},
      "Assertion");

    ASSERT_DEATH({this->invoke_to_write_block(0, addr, data, 50000, 0);
        this->component.doDispatch();},
      "Assertion");
  }


  namespace Write {

    // ----------------------------------------------------------------------
    // Tests
    // ----------------------------------------------------------------------

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
