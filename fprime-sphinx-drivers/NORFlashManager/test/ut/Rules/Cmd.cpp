// ====================================================================== 
// \title  Rules/Cmd.cpp
// \author ciankc
// \brief  Rules/Cmd class implementation
//
// \copyright
// Copyright (C) 2019 California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
// ======================================================================

#include "fprime-sphinx-drivers/Test/Scenario/Test/State.hpp"
#include "fprime-sphinx-drivers/Random/Random.hpp"
#include "Cmd.hpp"

namespace Drv {
  // ---------------------------------------------------------------------- 
  // Rule definitions
  // ---------------------------------------------------------------------- 

  bool TestState ::
    precondition__Cmd__Reset(void) const
  {
    bool result = true;
    //precondition is always true
    //printf("Precondition for Cmd OK result is: %d\n", result);
    return result;
  }

  void TestState ::
    action__Cmd__Reset(void)
  {
    //printf("Action for Cmd OK\n");
    
    U32 instance = 0;
    U32 cmdSeq = 0;
    
    for(U32 i = 0; i < 5; i++)
    {
      if(i < 4)
      {
        this->component.m_state = NORMGR_ERASING;
        this->sendCmd_NOR_FLASH_RESET(instance,cmdSeq,i);
        this->component.doDispatch();
        ASSERT_EVENTS_NOR_RESET_FAIL_SIZE(1);
        ASSERT_CMD_RESPONSE(0,NORFlashManagerComponentImpl::OPCODE_NOR_FLASH_RESET ,0,Fw::COMMAND_EXECUTION_ERROR);
        this->clearHistory();

        this->component.m_state = NORMGR_IDLE;
        this->sendCmd_NOR_FLASH_RESET(instance,cmdSeq,i);
        this->component.doDispatch();
        ASSERT_EVENTS_NOR_RESETTING_SIZE(1);
        ASSERT_EQ(this->component.m_state, NORMGR_RESETING);        
        this->clearHistory();
      }
      else
      {
        this->sendCmd_NOR_FLASH_RESET(instance,cmdSeq,i);
        this->component.doDispatch();
        ASSERT_EVENTS_NOR_FAILED_TO_RESET_SIZE(1);
        ASSERT_CMD_RESPONSE(0,NORFlashManagerComponentImpl::OPCODE_NOR_FLASH_RESET,0,Fw::COMMAND_EXECUTION_ERROR);
        this->clearHistory();
      }
    }
  }

  bool TestState ::
    precondition__Cmd__Timeout(void) const
  {
    bool result = true;
    //precondition is always true
    //printf("Precondition for Cmd ERROR result is: %d\n", result);
    return result;
  }

  void TestState ::
    action__Cmd__Timeout(void)
  {
    //printf("Action for Cmd ERROR\n");

    this->sendCmd_NOR_FLASH_SET_WRITE_TIMEOUT(0, 0, 100);
    this->component.doDispatch();
    ASSERT_CMD_RESPONSE_SIZE(1);
    ASSERT_EQ(this->component.m_write_timeout, 100);
    this->clearHistory();

    this->sendCmd_NOR_FLASH_SET_ERASE_TIMEOUT(0, 0, 100);
    this->component.doDispatch();
    ASSERT_CMD_RESPONSE_SIZE(1);
    ASSERT_EQ(this->component.m_erase_timeout, 100);
    this->clearHistory();

    this->sendCmd_NOR_FLASH_SET_VERIFY_TIMEOUT(0, 0, 100);
    this->component.doDispatch();
    ASSERT_CMD_RESPONSE_SIZE(1);
    ASSERT_EQ(this->component.m_verify_timeout, 100);
    this->clearHistory();
  }


  namespace Cmd {

    // ---------------------------------------------------------------------- 
    // Tests
    // ----------------------------------------------------------------------     

    Tester :: Tester(const char* compName, U32 timeout) 
      : testState(compName, timeout)
    {

    }

    void Tester ::
      Reset(void)
    {
      //apply rule
      this->ruleReset.apply(this->testState);
    }    

    void Tester ::
      Timeout(void)
    {
      //apply rule
      this->ruleTimeout.apply(this->testState);
    }

  }

}
