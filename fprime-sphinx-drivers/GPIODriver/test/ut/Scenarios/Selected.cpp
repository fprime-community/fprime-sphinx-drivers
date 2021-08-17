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
#include "fprime-sphinx-drivers/GPIODriver/test/ut/Rules/Rules.hpp"
#include "fprime-sphinx-drivers/GPIODriver/test/ut/Scenarios/Selected.hpp"

 namespace Drv {

   namespace Selected {

     // ----------------------------------------------------------------------
     // Rule definitions
     // ----------------------------------------------------------------------

     Rules::ReadWrite::DIRIN rule0;
     Rules::ReadWrite::DIROUT rule1;
     Rules::ReadWrite::READIN rule2;
     Rules::ReadWrite::READOUT rule3;
     Rules::ReadWrite::SETOUT rule4;
     Rules::ReadWrite::CLEAROUT rule5;
     Rules::ReadWrite::ERROR rule6;
     Rules::Init::OK rule7;
     Rules::Init::ERROR rule8;
     Rules::Interrupt::OK rule9;

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
         &rule9
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
       scenario.runWithBound(100);
     }

   }

 }

