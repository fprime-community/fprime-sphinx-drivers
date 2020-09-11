// ====================================================================== 
// \title  Main.cpp
// \author bocchino
// \brief  Main file for test scenario testing
//
// \copyright
// Copyright (C) 2017 California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
// ====================================================================== 

#include "fprime-sphinx-drivers/Test/Scenario/InterleavedScenario.hpp"
#include "fprime-sphinx-drivers/Test/Scenario/RandomScenario.hpp"
#include "fprime-sphinx-drivers/Test/Scenario/SequenceScenario.hpp"

#include "Rules.hpp"

namespace Test {

  TEST(Sequence, OK) {
    State state;
    Set set;
    Unset unset;
    Rule<State>* rules[] = { &set, &unset };
    SequenceScenario<State>::Sequence sequence(
        rules, 
        sizeof(rules) / sizeof(Rule<State>*)
    );
    SequenceScenario<State> scenario("scenario", state, sequence);
    scenario.run();
  }

  TEST(Apply, Error) {
    State state;
    Unset unset;
    unset.apply(state);
  }

  TEST(Random, Bounded) {
    State state;
    Set set;
    Unset unset;
    Rule<State>* rules[] = { &set, &unset };
    RandomScenario<State>::RuleArray ruleArray(
        rules, 
        sizeof(rules) / sizeof(Rule<State>*)
    );
    RandomScenario<State> scenario("scenario", state, ruleArray);
    scenario.runWithBound(100);
  }

  TEST(Random, Terminating) {
    State state;
    Set set;
    Rule<State>* rules[] = { &set };
    RandomScenario<State>::RuleArray ruleArray(
        rules, 
        sizeof(rules) / sizeof(Rule<State>*)
    );
    RandomScenario<State> scenario("scenario", state, ruleArray);
    scenario.run();
  }

  TEST(Interleaved, Bounded) {
    State state;
    Set set;
    Unset unset;
    Rule<State>* rules[] = { &set, &unset };
    RandomScenario<State>::RuleArray ruleArray(
        rules, 
        sizeof(rules) / sizeof(Rule<State>*)
    );
    RandomScenario<State> randomScenario1("randomScenario1", state, ruleArray);
    RandomScenario<State> randomScenario2("randomScenario2", state, ruleArray);
    Scenario<State>* scenarios[] = { 
      &randomScenario1,
      &randomScenario2 
    };
    InterleavedScenario<State>::ScenarioArray scenarioArray(
      scenarios,
      sizeof(scenarios) / sizeof(Scenario<State>*)
    );
    InterleavedScenario<State> scenario("scenario", state, scenarioArray);
    scenario.runWithBound(100);
  }

}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
