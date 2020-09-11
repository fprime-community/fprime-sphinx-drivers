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
#include "fprime-sphinx-drivers/NORFlashMgrWorker/test/ut/Rules/Rules.hpp"
#include "fprime-sphinx-drivers/NORFlashMgrWorker/test/ut/Scenarios/Selected.hpp"

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
     Rules::Misc::Cancel rule5;
     Rules::Misc::Reset rule6;
     Rules::Misc::Verify rule7;


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

