// ====================================================================== 
// \title  Rules/Owner.cpp
// \author ciankc
// \brief  Rules/Owner class implementation
//
// \copyright
// Copyright (C) 2019 California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
// ======================================================================

#include "fprime-sphinx-drivers/Test/Scenario/Test/State.hpp"
#include "Owner.hpp"

namespace Drv {
  // ---------------------------------------------------------------------- 
  // Rule definitions
  // ---------------------------------------------------------------------- 

  bool TestState ::
    precondition__Owner__ClaimOK(void) const
  {
    bool result = true;
    //precondition is true if all timers are unclaimed
    for(U32 i = 0; i < 4; i++)
    {
        result &= this->component.freeTimers[i];
    }
    //printf("Precondition for Owner ClaimOK result is: %d\n", result);
    return result;
  }

  void TestState ::
    action__Owner__ClaimOK(void)
  {
    //printf("Action for Owner ClaimOK\n");
    

    U32 timer = 0;

    //invoke for TIMER_ANY
    timer = this->invoke_to_gPTimerDriver_Claim(0, 4);
    ASSERT_EQ(timer, 0);
    ASSERT_TRUE(this->component.freeTimers[0] == false);
    
    //return timer for remaining 3 timers
    for(U32 i = 1; i < 4; i++)
    {
      timer = this->invoke_to_gPTimerDriver_Claim(0, i);
      ASSERT_EQ(timer, i);
      //check that freeTimers is now false
      ASSERT_TRUE(this->component.freeTimers[i] == false);
    }

  }

  bool TestState ::
    precondition__Owner__ClaimERROR(void) const
  {
    bool result = true;
    //precondition is that all timers are already claimed
    for(U32 i = 0; i < 4; i++)
    {
      result &= !(this->component.freeTimers[i]);
    }
    //printf("Precondition for Owner ClaimERROR result is: %d\n", result);
    return result;
  }

  void TestState ::
    action__Owner__ClaimERROR(void)
  {
    //printf("Action for Owner ClaimERROR\n");

    //status should be NOT_AVAILABLE (-1)
    U32 timer = 0;
    for(U32 i = 0; i < 4; i++)
    {
      timer = this->invoke_to_gPTimerDriver_Claim(0, i);
      ASSERT_EQ(timer, -1);
    }

    //should fail with invalid timer
    ASSERT_DEATH({this->invoke_to_gPTimerDriver_Claim(0, 5);},
	       "Assertion `0' failed.");

  }

  bool TestState ::
    precondition__Owner__UnclaimOK(void) const
  {
    bool result = true;
    //precondition is that all timers are already claimed
    for(U32 i = 0; i < 4; i++)
    {
      result &= !(this->component.freeTimers[i]);
    } 
    //printf("Precondition for Owner UnclaimOK result is: %d\n", result);
    return result;
  }

  void TestState ::
    action__Owner__UnclaimOK(void)
  {
    //printf("Action for Owner UnclaimOK\n");
    
    for(U32 i = 0; i < 4; i++)
    {
      this->invoke_to_gPTimerDriver_Unclaim(0, i);
      ASSERT_TRUE(this->component.freeTimers[i] == true);
    }
    
  }

  bool TestState ::
    precondition__Owner__UnclaimERROR(void) const
  {
    bool result = true;
    //precondition is always true
    //printf("Precondition for Owner UnclaimERROR result is: %d\n", result);
    return result;
  }

  void TestState ::
    action__Owner__UnclaimERROR(void)
  {
    //printf("Action for Owner UnclaimERROR\n");

    //should fail with invalid timer
    ASSERT_DEATH({this->invoke_to_gPTimerDriver_Unclaim(0, 5);},
	       "Assertion `0' failed.");
    
  }


  namespace Owner {

    Tester ::
    Tester(
           const char *const compName,

           const U32 prescalerReload,
           const U32 prescalerValue,

           // Timer 1
           const bool timer1Reserved,
           const bool timer1UsrConfig,
           const U32 timer1CntReg,
           const U32 timer1RldReg,
           const U32 timer1CtlReg,

           // Timer 2
           const bool timer2Reserved,
           const bool timer2UsrConfig,
           const U32 timer2CntReg,
           const U32 timer2RldReg,
           const U32 timer2CtlReg,

           // Timer 3
           const bool timer3Reserved,
           const bool timer3UsrConfig,
           const U32 timer3CntReg,
           const U32 timer3RldReg,
           const U32 timer3CtlReg,

           // Timer 4
           const bool timer4Reserved,
           const bool timer4UsrConfig,
           const U32 timer4CntReg,
           const U32 timer4RldReg,
           const U32 timer4CtlReg) :
           testState(compName, prescalerReload, prescalerValue,
	      timer1Reserved, timer1UsrConfig, timer1CntReg, timer1RldReg, timer1CtlReg,
	      timer2Reserved, timer2UsrConfig, timer2CntReg, timer2RldReg, timer2CtlReg,
	      timer3Reserved, timer3UsrConfig, timer3CntReg, timer3RldReg, timer3CtlReg,
	      timer4Reserved, timer4UsrConfig, timer4CntReg, timer4RldReg, timer4CtlReg)
    {

    }


    // ---------------------------------------------------------------------- 
    // Tests
    // ----------------------------------------------------------------------     
    
    void Tester ::
      UnclaimOK(void)
    {
      //apply rule
      this->ruleClaimOK.apply(this->testState);
      this->ruleUnclaimOK.apply(this->testState);
    }    

    void Tester ::
      UnclaimERROR(void)
    {
      //apply rule
      this->ruleClaimOK.apply(this->testState);
      this->ruleUnclaimERROR.apply(this->testState);
    }

    void Tester ::
      ClaimOK(void)
    {
      //apply rule
      this->ruleClaimOK.apply(this->testState);
    }    

    void Tester ::
      ClaimERROR(void)
    {
      //apply rule
      this->ruleClaimOK.apply(this->testState);
      this->ruleClaimERROR.apply(this->testState);
    }

  }

}
