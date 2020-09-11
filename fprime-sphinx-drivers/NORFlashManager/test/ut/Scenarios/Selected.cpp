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
#include "fprime-sphinx-drivers/NORFlashManager/test/ut/Rules/Rules.hpp"
#include "fprime-sphinx-drivers/NORFlashManager/test/ut/Scenarios/Selected.hpp"

 namespace Drv {

   namespace Selected {

     // ----------------------------------------------------------------------
     // Rule definitions
     // ----------------------------------------------------------------------

     Rules::Read::OK rule0;
     Rules::Read::ERROR rule1;
     Rules::Write::OK rule2;
     Rules::Write::ERROR rule3;
     Rules::Erase::OK rule4;
     Rules::Erase::ERROR rule5;
     Rules::Size::Block rule6;
     Rules::Size::FSW rule7;
     Rules::Worker::Write rule8;
     Rules::Worker::Read rule9;
     Rules::Worker::Erase rule10;
     Rules::Worker::Reset rule11;
     Rules::Worker::Verify rule12;
     Rules::Worker::Error rule13;
     Rules::Misc::SchedIn rule14;
     Rules::Misc::Ping rule15;
     Rules::Misc::Verify rule16;
     Rules::Cmd::Reset rule17;
     Rules::Cmd::Timeout rule18;

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
         &rule7,
         &rule8, 
         &rule9, 
         &rule10,
         &rule11,
         &rule12,
         &rule13,
         &rule14, 
         &rule15, 
         &rule16,
         &rule17, 
         &rule18
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
     
     Tester :: Tester(const char* compName, U32 timeout)
       : testState(compName, timeout)
     {

     }

   }

 }

