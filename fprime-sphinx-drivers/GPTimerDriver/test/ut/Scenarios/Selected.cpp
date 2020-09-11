// ======================================================================
// \title  Selected.cpp
// \author ciankc
// \brief  Scenarios containing selected rules        
//
// \copyright
// Copyright (C) 2019 California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
// ======================================================================

#include "fprime-sphinx-drivers/Test/Scenario/RandomScenario.hpp"
#include "fprime-sphinx-drivers/GPTimerDriver/test/ut/Rules/Rules.hpp"
#include "fprime-sphinx-drivers/GPTimerDriver/test/ut/Scenarios/Selected.hpp"

 namespace Drv {

   namespace Selected {

     // ----------------------------------------------------------------------
     // Rule definitions
     // ----------------------------------------------------------------------

     Rules::Owner::ClaimOK rule0;
     Rules::Owner::ClaimERROR rule1;
     Rules::Owner::UnclaimOK rule2;
     Rules::Owner::UnclaimERROR rule3;
     Rules::Read::OK rule4;
     Rules::Read::ERROR rule5;
     Rules::Write::OK rule6;
     Rules::Write::ERROR rule7;

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

     void Tester:: Random(void)
     {
       Test::Rule<TestState>* rules[] = {
         &rule0,
         &rule1,
         &rule2, 
         &rule3,
         &rule4,
         &rule5, 
         &rule6, 
         &rule7
       };

       Test::RandomScenario<TestState>::RuleArray ruleArray(
           rules,
           sizeof(rules) / sizeof(Test::Rule<TestState>*)
       );

       Test::RandomScenario<TestState> scenario(
           "Selected.Random",
	   this->testState, 
	   ruleArray
       );
       scenario.runWithBound(1000);
     }

   }

 }

