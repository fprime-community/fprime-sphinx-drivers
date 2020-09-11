// ====================================================================== 
// \title  Rules/Worker.cpp
// \author ciankc
// \brief  Rules/Worker class implementation
//
// \copyright
// Copyright (C) 2019 California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
// ======================================================================

#include "fprime-sphinx-drivers/Test/Scenario/Test/State.hpp"
#include "fprime-sphinx-drivers/Random/Random.hpp"
#include "Worker.hpp"

namespace Drv {
  // ---------------------------------------------------------------------- 
  // Rule definitions
  // ---------------------------------------------------------------------- 

  bool TestState ::
    precondition__Worker__Write(void) const
  {
    bool result = true;
    //precondition is always true
    //printf("Precondition for Worker Write result is: %d\n", result);
    return result;
  }

  void TestState ::
    action__Worker__Write(void)
  {
    //printf("Action for Worker Write\n");
    
    this->component.m_state = NORMGR_WRITING;
    this->invoke_to_worker_done(0, NORMGR_OK, 0, 0);
    this->component.doDispatch();
    this->clearHistory();
    
    this->component.m_state = NORMGR_WRITING;
    this->invoke_to_worker_done(0, NORMGR_TIMEOUT, 0, 0);
    this->component.doDispatch();
    ASSERT_EVENTS_NOR_WRITE_TIMEOUT_SIZE(1);
    this->clearHistory();

    this->component.m_state = NORMGR_WRITING;
    this->invoke_to_worker_done(0, NORMGR_FAILED_TO_UNLOCK, 0, 0);
    this->component.doDispatch();
    ASSERT_EVENTS_NOR_UNLOCK_BYPASS_FAILED_SIZE(1);
    this->clearHistory();

    this->component.m_state = NORMGR_WRITING;
    this->invoke_to_worker_done(0, NORMGR_FAILED_TO_READ, 0, 0);
    this->component.doDispatch();
    ASSERT_EVENTS_NOR_FAILED_TO_VERIFY_DATA_SIZE(1);
    this->clearHistory();

    this->component.m_state = NORMGR_WRITING;
    this->invoke_to_worker_done(0, NORMGR_FAILED_TO_UNLOCK_PROGRAM, 0, 0);
    this->component.doDispatch();
    ASSERT_EVENTS_NOR_UNLOCK_BYPASS_PROGRAM_FAILED_SIZE(1);
    this->clearHistory();

    this->component.m_state = NORMGR_WRITING;
    this->invoke_to_worker_done(0, NORMGR_FAILED_TO_READ_RESET_BYPASS, 0, 0);
    this->component.doDispatch();
    ASSERT_EVENTS_NOR_FAILED_TO_VERIFY_DATA_SIZE(1);
    ASSERT_EVENTS_NOR_UNLOCK_BYPASS_RESET_FAILED_SIZE(1);
    this->clearHistory();

    this->component.m_state = NORMGR_WRITING;
    this->invoke_to_worker_done(0, NORMGR_FAILED_TO_UNLOCK_PROGRAM_RESET_BYPASS, 0, 0);
    this->component.doDispatch();
    ASSERT_EVENTS_NOR_UNLOCK_BYPASS_PROGRAM_FAILED_SIZE(1);
    ASSERT_EVENTS_NOR_UNLOCK_BYPASS_RESET_FAILED_SIZE(1);
    this->clearHistory();

    this->component.m_state = NORMGR_WRITING;
    this->invoke_to_worker_done(0, NORMGR_FAILED_TO_RESET, 0, 0);
    this->component.doDispatch();
    ASSERT_EVENTS_NOR_FAILED_TO_VERIFY_DATA_SIZE(1);
    ASSERT_EVENTS_NOR_FAILED_TO_RESET_SIZE(1);
    this->clearHistory();
    
    this->component.m_state = NORMGR_WRITING;
    this->invoke_to_worker_done(0, NORMGR_FAILED_TO_RESET_BYPASS_RESET, 0, 0);
    this->component.doDispatch();
    ASSERT_EVENTS_NOR_FAILED_TO_VERIFY_DATA_SIZE(1);
    ASSERT_EVENTS_NOR_UNLOCK_BYPASS_RESET_FAILED_SIZE(1);
    ASSERT_EVENTS_NOR_FAILED_TO_RESET_SIZE(1);
    this->clearHistory();
  }

  bool TestState ::
    precondition__Worker__Read(void) const
  {
    bool result = true;
    //precondition is always true
    //printf("Precondition for Worker Read result is: %d\n", result);
    return result;
  }

  void TestState ::
    action__Worker__Read(void)
  {
    //printf("Action for Worker Read\n");
    
    this->component.m_state = NORMGR_READING;
    this->invoke_to_worker_done(0, NORMGR_OK, 0, 0);
    this->component.doDispatch();    
    this->clearHistory();

    this->component.m_state = NORMGR_READING;
    this->invoke_to_worker_done(0, NORMGR_FAILED_TO_READ, 0, 0);
    this->component.doDispatch();
    ASSERT_EVENTS_NOR_FAILED_TO_READ_DATA_SIZE(1);
    this->clearHistory();

    this->component.m_state = NORMGR_READING;
    this->invoke_to_worker_done(0, NORMGR_TIMEOUT, 0, 0);
    this->component.doDispatch();
    ASSERT_EVENTS_NOR_READ_TIMEOUT_SIZE(1);
    this->clearHistory();
  }

  bool TestState ::
    precondition__Worker__Erase(void) const
  {
    bool result = true;
    //precondition is always true
    //printf("Precondition for Worker Erase result is: %d\n", result);
    return result;
  }

  void TestState ::
    action__Worker__Erase(void)
  {
    //printf("Action for Worker Erase\n");
    
    this->component.m_state = NORMGR_ERASING;
    this->invoke_to_worker_done(0, NORMGR_OK, 0, 0);
    this->component.doDispatch();    
    ASSERT_EVENTS_NOR_ERASE_DONE_SIZE(1);
    this->clearHistory();

    this->component.m_state = NORMGR_ERASING;
    this->invoke_to_worker_done(0, NORMGR_FAILED_TO_RESET, 0, 0);
    this->component.doDispatch();
    ASSERT_EVENTS_NOR_FAILED_TO_RESET_SIZE(1);
    this->clearHistory();

    this->component.m_state = NORMGR_ERASING;
    this->invoke_to_worker_done(0, NORMGR_TIMEOUT, 0, 0);
    this->component.doDispatch();
    ASSERT_EVENTS_NOR_ERASE_TIMEOUT_SIZE(1);
    this->clearHistory();

    this->component.m_state = NORMGR_ERASING;
    this->invoke_to_worker_done(0, NORMGR_FAILED_TO_ERASE, 0, 0);
    this->component.doDispatch();
    ASSERT_EVENTS_NOR_ERASE_FAIL_SIZE(1);
    this->clearHistory();

    this->component.m_state = NORMGR_ERASING;
    this->invoke_to_worker_done(0, NORMGR_FAILED_TO_TIMEOUT_RESET, 0, 0);
    this->component.doDispatch();
    ASSERT_EVENTS_NOR_ERASE_TIMEOUT_SIZE(1);
    ASSERT_EVENTS_NOR_FAILED_TO_RESET_SIZE(1);
    this->clearHistory();

    this->component.m_state = NORMGR_ERASING;
    this->invoke_to_worker_done(0, NORMGR_FAILED_TO_ERASE_RESET, 0, 0);
    this->component.doDispatch();
    ASSERT_EVENTS_NOR_FAILED_TO_RESET_SIZE(1);
    ASSERT_EVENTS_NOR_ERASE_FAIL_SIZE(1);
    this->clearHistory();
  }

  bool TestState ::
    precondition__Worker__Reset(void) const
  {
    bool result = true;
    //precondition is always true
    //printf("Precondition for Worker Reset result is: %d\n", result);
    return result;
  }

  void TestState ::
    action__Worker__Reset(void)
  {
    //printf("Action for Worker Reset\n");
    
    this->component.m_state = NORMGR_RESETING;
    this->invoke_to_worker_done(0, NORMGR_OK, 0, 0);
    this->component.doDispatch();    
    ASSERT_CMD_RESPONSE_SIZE(1);
    this->clearHistory();

    this->component.m_state = NORMGR_RESETING;
    this->invoke_to_worker_done(0, NORMGR_TIMEOUT, 0, 0);
    this->component.doDispatch();
    ASSERT_EVENTS_NOR_FAILED_TO_RESET_SIZE(1);
    ASSERT_CMD_RESPONSE_SIZE(1);
    this->clearHistory();
  }

  bool TestState ::
    precondition__Worker__Verify(void) const
  {
    bool result = true;
    //precondition is always true
    //printf("Precondition for Worker Verify result is: %d\n", result);
    return result;
  }

  void TestState ::
    action__Worker__Verify(void)
  {
    //printf("Action for Worker Verify\n");
    
    this->component.m_state = NORMGR_VERIFYING;
    this->invoke_to_worker_done(0, NORMGR_OK, 0, 0);
    this->component.doDispatch();    
    ASSERT_EVENTS_NOR_CHECKSUM_VERIFY_DONE_SIZE(1);
    this->clearHistory();
    
    this->component.m_state = NORMGR_VERIFYING;
    this->invoke_to_worker_done(0, NORMGR_FAILED_TO_VERIFY, 0, 0);
    this->component.doDispatch();
    ASSERT_EVENTS_NOR_FAILED_TO_VERIFY_CHECKSUM_SIZE(1);
    this->clearHistory();
  }

  bool TestState ::
    precondition__Worker__Error(void) const
  {
    bool result = true;
    //precondition is always true
    //printf("Precondition for Worker Error result is: %d\n", result);
    return result;
  }

  void TestState ::
    action__Worker__Error(void)
  {
    //printf("Action for Worker Error\n");
    
    //invoke with invalid status
    this->component.m_state = NORMGR_WRITING;
    ASSERT_DEATH({this->invoke_to_worker_done(0, 30, 0, 0);
                  this->component.doDispatch();},
                  "Assertion `0' failed.");
    
    this->component.m_state = NORMGR_ERASING;
    ASSERT_DEATH({this->invoke_to_worker_done(0, 30, 0, 0);
                  this->component.doDispatch();},
                  "Assertion `0' failed.");

    this->component.m_state = NORMGR_READING;
    ASSERT_DEATH({this->invoke_to_worker_done(0, 30, 0, 0);
                  this->component.doDispatch();},
                  "Assertion `0' failed.");

    this->component.m_state = NORMGR_VERIFYING;
    ASSERT_DEATH({this->invoke_to_worker_done(0, 30, 0, 0);
                  this->component.doDispatch();},
                  "Assertion `0' failed.");

    //invalid state
    this->component.m_state = NORMGR_IDLE;
    ASSERT_DEATH({this->invoke_to_worker_done(0, 0, 0, 0);
                  this->component.doDispatch();},
                  "Assertion `0' failed.");
  }


  namespace Worker {

    // ---------------------------------------------------------------------- 
    // Tests
    // ----------------------------------------------------------------------     

    Tester :: Tester(const char* compName, U32 timeout) 
      : testState(compName, timeout)
    {

    }

    void Tester ::
      Write(void)
    {
      //apply rule
      this->ruleWrite.apply(this->testState);
    }    

    void Tester ::
      Read(void)
    {
      //apply rule
      this->ruleRead.apply(this->testState);
    }

    void Tester ::
      Erase(void)
    {
      //apply rule
      this->ruleErase.apply(this->testState);
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

    void Tester ::
      Error(void)
    {
      //apply rule
      this->ruleError.apply(this->testState);
    }

  }

}
