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
#include "Write.hpp"

namespace Drv {
  // ---------------------------------------------------------------------- 
  // Rule definitions
  // ---------------------------------------------------------------------- 

  bool TestState ::
    precondition__Write__OK(void) const
  {
    bool result = true;
    //precondition is that all timers are already claimed
    for(U32 i = 0; i < 4; i++)
    {
      result &= !(this->component.freeTimers[i]);
    }
    //printf("Precondition for Write OK result is: %d\n", result);
    return result;
  }

  void TestState ::
    action__Write__OK(void)
  {
    //printf("Action for Write OK\n");
    
    //returns timer number for all 4 timers
    U32 val = 0;
    U32 wval = 0xCC;
    for(U32 i = 0; i < 4; i++)
    {
      //write value into register
      this->invoke_to_gPTimerDriver_WriteControl(0,i, wval);
      val = readReg(GPTimer::timerAddr[i].ctlRegAddr);
      ASSERT_EQ(val, wval & GPTimer::CONTROL_BITS_MASK);

      this->invoke_to_gPTimerDriver_WriteCounter(0,i, wval);
      val = readReg(GPTimer::timerAddr[i].cntRegAddr);
      ASSERT_EQ(val, wval);

      this->invoke_to_gPTimerDriver_WriteReload(0,i, wval);
      val = readReg(GPTimer::timerAddr[i].rldRegAddr);
      ASSERT_EQ(val, wval);
    }

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

    //should fail with invalid timer
    ASSERT_DEATH({this->invoke_to_gPTimerDriver_WriteControl(0,4,0);},
	       "Assertion `0' failed.");

    ASSERT_DEATH({this->invoke_to_gPTimerDriver_WriteCounter(0,4,0);},
                 "Assertion `0' failed.");

    ASSERT_DEATH({this->invoke_to_gPTimerDriver_WriteReload(0,4,0);},
                 "Assertion `0' failed.");

  }


  namespace Write {

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
	      timer4Reserved, timer4UsrConfig, timer4CntReg, timer4RldReg, timer4CtlReg),
           ownerTester(compName, prescalerReload, prescalerValue,
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
      OK(void)
    {
      //apply rule
      this->ownerTester.ruleClaimOK.apply(this->testState);
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
