// ======================================================================
// \title  Selected.cpp
// \author AUTO-GENERATED: DO NOT EDIT
// \brief  Scenarios containing selected rules        
//
// \copyright
// Copyright (C) 2019 California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
// ======================================================================

#include "fprime-sphinx-drivers/Test/Scenario/RandomScenario.hpp"
#include "fprime-sphinx-drivers/SPIDriverGeneric/test/ut/Rules/Rules.hpp"
#include "fprime-sphinx-drivers/SPIDriverGeneric/test/ut/Scenarios/Selected.hpp"

 namespace Drv {

   namespace Selected {

     // ----------------------------------------------------------------------
     // Rule definitions
     // ----------------------------------------------------------------------

     Rules::SPIMutex::UnclaimOK rule0;
     Rules::SPIMutex::UnclaimDouble rule1;
     Rules::RWOwner::SUCCESS8 rule2;
     Rules::RWOwner::SUCCESS16 rule3;
     Rules::RWOwner::SUCCESS32 rule4;
     Rules::RWOwner::ERROR rule5;
     Rules::SPIMutex::ClaimOK rule6;
     Rules::SPIMutex::ClaimDouble rule7;
     Rules::Pointer::Invalid rule8;
     Rules::Reset::OK rule9;
     Rules::RWReverse::SUCCESS8 rule10;
     Rules::RWReverse::SUCCESS16 rule11;
     Rules::RWReverse::SUCCESS32 rule12;
     Rules::RWOwner::TIMEOUT rule13;

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
	 &rule13
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

