// ======================================================================
// \title  Rules/Misc.cpp
// \author ciankc
// \brief  Rules/Misc class implementation
//
// \copyright
// Copyright (C) 2019 California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
// ======================================================================

#include "fprime-sphinx-drivers/Test/Scenario/Test/State.hpp"
#include "fprime-sphinx-drivers/Random/Random.hpp"
#include "Misc.hpp"

namespace Drv {
  // ----------------------------------------------------------------------
  // Rule definitions
  // ----------------------------------------------------------------------

  bool TestState ::
    precondition__Misc__Cancel(void) const
  {
    bool result = true;
    //precondition is always true
    //printf("Precondition for Misc Cancel result is: %d\n", result);
    return result;
  }

  void TestState ::
    action__Misc__Cancel(void)
  {
    //printf("Action for Misc Cancel\n");
    this->clearHistory();
    this->invoke_to_cancel(0);
    ASSERT_EQ(this->component.m_cancel, true);
  }

  bool TestState ::
    precondition__Misc__Reset(void) const
  {
    bool result = true;
    //precondition is always true
    //printf("Precondition for Misc Reset result is: %d\n", result);
    return result;
  }

  void TestState ::
    action__Misc__Reset(void)
  {
    //printf("Action for Misc Reset\n");
    this->clearHistory();
    this->invoke_to_reset(0,0);
    this->component.doDispatch();
    ASSERT_EQ(this->component.m_cancel, false);
  }

  bool TestState ::
    precondition__Misc__Verify(void) const
  {
    bool result = true;
    //precondition is always true
    //printf("Precondition for Misc Verify result is: %d\n", result);
    return result;
  }

  void TestState ::
    action__Misc__Verify(void)
  {
    //printf("Action for Misc Verify\n");
    this->clearHistory();
    this->invoke_to_verify(0, 512, 1024);
    this->component.doDispatch();

    //checksum
    ASSERT_DEATH({this->component.checksum_compute(9*1024*1024, 512);},
                  "Assertion");

    writeReg(512, 0xFFFFFFFF);
    U32 res = this->component.checksum_compute(4, 512);
    ASSERT_EQ(NOR_FSW_CHECKSUM_SEED + (0xFF * 4), res);
  }


  namespace Misc {

    // ----------------------------------------------------------------------
    // Tests
    // ----------------------------------------------------------------------

    void Tester ::
      Cancel(void)
    {
      //apply rule
      this->ruleCancel.apply(this->testState);
    }

    void Tester ::
      Reset(void)
    {
      //apply rule
      this->ruleReset.apply(this->testState);
    }

    void Tester ::
      Verify(void)
    {
      //apply rule
      this->ruleVerify.apply(this->testState);
    }

  }

}
