// ====================================================================== 
// \title  Rules/Erase.cpp
// \author ciankc
// \brief  Rules/Erase class implementation
//
// \copyright
// Copyright (C) 2019 California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
// ======================================================================

#include "fprime-sphinx-drivers/Test/Scenario/Test/State.hpp"
#include "fprime-sphinx-drivers/Random/Random.hpp"
#include "Erase.hpp"

namespace Drv {
  // ---------------------------------------------------------------------- 
  // Rule definitions
  // ---------------------------------------------------------------------- 

  bool TestState ::
    precondition__Erase__OK(void) const
  {
    bool result = true;
    //precondition is true when the state is idle
    result &= (this->component.m_state == NORMGR_IDLE);
    //printf("Precondition for Erase OK result is: %d\n", result);
    return result;
  }

  void TestState ::
    action__Erase__OK(void)
  {
    //printf("Action for Erase OK\n");
    
    //erase for all 4 banks
    for(U32 i = 0; i < 4; i++)
    {
      this->invoke_to_request_erase(0, i);
      this->component.doDispatch();
      ASSERT_EQ(this->component.m_state, NORMGR_ERASING);
      this->component.m_state = NORMGR_IDLE;
    }
    
    ASSERT_EQ(readReg(0xaaa), 0x10);
    ASSERT_EQ(readReg(0x555), 0x55);
   
    this->clearHistory();
  }

  bool TestState ::
    precondition__Erase__ERROR(void) const
  {
    bool result = true;
    //precondition is always true
    //printf("Precondition for Erase ERROR result is: %d\n", result);
    return result;
  }

  void TestState ::
    action__Erase__ERROR(void)
  {
    //printf("Action for Erase ERROR\n");
    
    this->component.m_state = NORMGR_ERASING;
    
    //already erasing
    this->invoke_to_request_erase(0, 0);
    this->component.doDispatch();
    ASSERT_EVENTS_NOR_ALREADY_ERASING_SIZE(1);
    this->component.m_state = NORMGR_WRITING;
    this->clearHistory();

    //busy
    this->invoke_to_request_erase(0, 0);
    this->component.doDispatch();
    ASSERT_EVENTS_NOR_ERASE_BUSY_SIZE(1);
    this->component.m_state = NORMGR_IDLE;
    this->clearHistory();

    //invalid bank number
    this->invoke_to_request_erase(0, 5);
    this->component.doDispatch();
    ASSERT_EVENTS_NOR_ERASE_FAIL_SIZE(1);
    ASSERT_EQ(this->component.m_state, NORMGR_IDLE);
    this->clearHistory();
  }


  namespace Erase {

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
