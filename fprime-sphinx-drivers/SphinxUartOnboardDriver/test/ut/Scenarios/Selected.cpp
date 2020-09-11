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
#include "fprime-sphinx-drivers/SphinxUartOnboardDriver/test/ut/Rules/Rules.hpp"
#include "fprime-sphinx-drivers/SphinxUartOnboardDriver/test/ut/Scenarios/Selected.hpp"

 namespace Drv {

   namespace Selected {

     // ----------------------------------------------------------------------
     // Rule definitions
     // ----------------------------------------------------------------------

     Rules::BytesUsed::OK rule0;
     Rules::Writer::TIMEOUT rule1;
     Rules::Writer::NULLPTR rule2;
     Rules::Writer::OK rule3;
     Rules::Writer::NBYTES rule4;
     Rules::Reader::NULLPTR rule5;
     Rules::Reader::OK rule6;
     Rules::Reader::NBYTES rule7;
     Rules::Reader::DATA rule8;
     Rules::Reader::ERROR rule9;
     Rules::Reader::EMPTY rule10;

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
         &rule10
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

