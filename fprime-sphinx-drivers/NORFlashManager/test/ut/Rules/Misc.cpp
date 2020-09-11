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
    precondition__Misc__SchedIn(void) const
  {
    bool result = true;
    //precondition is always true
    //printf("Precondition for Misc OK result is: %d\n", result);
    return result;
  }

  void TestState ::
    action__Misc__SchedIn(void)
  {
    //printf("Action for Misc OK\n");
    
    this->component.m_state = NORMGR_ERASING;
    for(U32 i = 0; i < 1001; i++)
    {
      this->invoke_to_schedIn(0,0);
      this->component.doDispatch(); 
    }
    //should be one greater than  max timeout value of 1000
    ASSERT_EQ(this->component.m_timer, 1001);
    this->component.m_timer = 0;
    
    this->component.m_state = NORMGR_WRITING;
    for(U32 i = 0; i < 1001; i++)
    {
      this->invoke_to_schedIn(0,0);
      this->component.doDispatch(); 
    }
    //should be one greater than  max timeout value of 1000
    ASSERT_EQ(this->component.m_timer, 1001);
    this->component.m_timer = 0;
    
    this->component.m_state = NORMGR_VERIFYING;
    for(U32 i = 0; i < 1001; i++)
    {
      this->invoke_to_schedIn(0,0);
      this->component.doDispatch(); 
    }
    //should be one greater than  max timeout value of 1000
    ASSERT_EQ(this->component.m_timer, 1001);
    this->component.m_timer = 0;

    //default case in switch statement, does nothing
    this->component.m_state = NORMGR_READING;
    this->invoke_to_schedIn(0,0);
    this->component.doDispatch();
    ASSERT_EQ(this->component.m_timer, 0);
    
    this->clearHistory();
  }

  bool TestState ::
    precondition__Misc__Ping(void) const
  {
    bool result = true;
    //precondition is always true
    //printf("Precondition for Misc ERROR result is: %d\n", result);
    return result;
  }

  void TestState ::
    action__Misc__Ping(void)
  {
    //printf("Action for Misc ERROR\n");
    
    //invoke Ping with key of 0xCC
    this->invoke_to_PingRecv(0,0xCC);
    this->component.doDispatch();
    
  }


  bool TestState ::
    precondition__Misc__Verify(void) const
  {
    bool result = true;
    //precondition is always true
    //printf("Precondition for Misc ERROR result is: %d\n", result);
    return result;
  }

  void TestState ::
    action__Misc__Verify(void)
  {
    //printf("Action for Misc ERROR\n");
    
    this->component.m_state = NORMGR_READING;
    this->invoke_to_request_verification(0, 1024, 512);
    this->component.doDispatch();
    ASSERT_EVENTS_NOR_VERIFY_BUSY_SIZE(1);
    this->clearHistory();

    this->component.m_state = NORMGR_IDLE;
    this->invoke_to_request_verification(0, 1024, 512);
    this->component.doDispatch();
    ASSERT_EQ(this->component.m_timer, 0);
    ASSERT_EQ(this->component.m_state, NORMGR_VERIFYING);    
  }


  namespace Misc {

    // ---------------------------------------------------------------------- 
    // Tests
    // ----------------------------------------------------------------------     

    Tester :: Tester(const char* compName, U32 timeout) 
      : testState(compName, timeout)
    {

    }

    void Tester ::
      SchedIn(void)
    {
      //apply rule
      this->ruleSchedIn.apply(this->testState);
    }    

    void Tester ::
      Ping(void)
    {
      //apply rule
      this->rulePing.apply(this->testState);
    }

    void Tester ::
      Verify(void)
    {
      //apply rule
      this->ruleVerify.apply(this->testState);
    }

  }

}
