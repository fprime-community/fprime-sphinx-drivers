// ====================================================================== 
// \title  Rules/Writer.cpp
// \author ciankc
// \brief  Rules/Writer class implementation
//
// \copyright
// Copyright (C) 2019 California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
// ======================================================================

#include "fprime-sphinx-drivers/Test/Scenario/Test/State.hpp"
#include "fprime-sphinx-drivers/Random/Random.hpp"
#include "Writer.hpp"

namespace Drv {
  // ---------------------------------------------------------------------- 
  // Rule definitions
  // ---------------------------------------------------------------------- 

  bool TestState ::
    precondition__Writer__TIMEOUT(void) const
  {
    bool result = true;
    //precondition is always true
    //printf("Precondition for Writer TIMEOUT result is: %d\n", result);
    return result;
  }

  void TestState ::
    action__Writer__TIMEOUT(void)
  {
    //printf("Action for Writer TIMEOUT\n");
    // Initialize test state
    this->clearHistory();

    U32 status;
    U8 data[5] = {1};
    //set timeout value to zero
    status = this->invoke_to_write(0, data, 1, 0);
    ASSERT_TRUE(status & (0x1 << 2));

  }

  bool TestState ::
    precondition__Writer__OK(void) const
  {
    bool result = true;
    //precondition is always true
    //printf("Precondition for Writer OK result is: %d\n", result);
    return result;
  }

  void TestState ::
    action__Writer__OK(void)
  {
    // printf("Action for Writer OK\n");
    // Initialize test state
    this->clearHistory();

    U32 status;
    U8 data[5] = {1,2,3,4,5};

    //set isempty bits to 1
    writeReg(this->component.m_address + REG_OFF_HW_STATUS, 6);
    status = this->invoke_to_write(0, data, 5, 100);
    ASSERT_EQ(status, 0);

  }

  bool TestState ::
    precondition__Writer__NBYTES(void) const
  {
    bool result = true;
    //precondition is always true
    //printf("Precondition for Writer NBYTES result is: %d\n", result);
    return result;
  }

  void TestState ::
    action__Writer__NBYTES(void)
  {
    // printf("Action for Writer NBYTES\n");
    // Initialize test state
    this->clearHistory();

    U32 status;
    U8 data[5] = {1,2,3,4,5};
    //set isempty bits to 1
    writeReg(this->component.m_address + REG_OFF_HW_STATUS, 6);
    //nbytes to read is 0
    status = this->invoke_to_write(0, data, 0, 100);
    //should return normally
    ASSERT_EQ(status, 0);

  }

  bool TestState ::
    precondition__Writer__NULLPTR(void) const
  {
    bool result = true;
    //precondition is always true
    //printf("Precondition for Writer NULLPTR result is: %d\n", result);
    return result;
  }

  void TestState ::
    action__Writer__NULLPTR(void)
  {
    //printf("Action for Writer NULLPTR\n");
    // Initialize test state
    this->clearHistory();

    U8* data = NULL;
    ASSERT_DEATH({this->invoke_to_write(0, data, 1, 100);},
                 "Assertion `0' failed.");

  }

  namespace Writer {

    // ---------------------------------------------------------------------- 
    // Tests
    // ---------------------------------------------------------------------- 

    void Tester ::
      TIMEOUT(void)
    {
      //apply rule
      this->ruleTIMEOUT.apply(this->testState);
    }

    void Tester ::
      OK(void)
    {
      //apply rule
      this->ruleOK.apply(this->testState);
    }

    void Tester ::
      NBYTES(void)
    {
      //apply rule
      this->ruleNBYTES.apply(this->testState);
    }

    void Tester ::
      NULLPTR(void)
    {
      //apply rule
      this->ruleNULLPTR.apply(this->testState);
    }

  }

}
