// ====================================================================== 
// \title  Rules.hpp
// \author bocchino
// \brief  Rules for test scenario testing
//
// \copyright
// Copyright (C) 2017 California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
// ====================================================================== 

#ifndef Test_Rules_HPP
#define Test_Rules_HPP

#include "fprime-sphinx-drivers/Test/Scenario/Rule.hpp"

#include "State.hpp"

namespace Test {

  class Set : 
    public Rule<State> 
  {

    public:

      Set(void) :
        Rule<State>("Set")
      {

      }

      bool precondition(const State& state) {
        return state.x == false;
      }

      void action(State& state) {
        state.x = true;
      }

  };

  class Unset : 
    public Rule<State> 
  {

    public:

      Unset(void) :
        Rule<State>("Unset")
      {

      }

      bool precondition(const State& state) {
        return state.x == true;
      }

      void action(State& state) {
        state.x = false;
      }

  };

}

#endif
