// ====================================================================== 
// \title  Rules.hpp
// \author ciankc
// \brief  Rules for testing FPGADriver
//
// \copyright
// Copyright (C) 2019 California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
// ======================================================================

#ifndef Drv_Rules_HPP
#define Drv_Rules_HPP

#include "fprime-sphinx-drivers/Test/Scenario/Rule.hpp"
#include "fprime-sphinx-drivers/FPGADriver/test/ut/TestState/TestState.hpp"

namespace Drv {

  namespace Rules {

    namespace Read {
    
      struct OK :
        public Test::Rule<TestState>
      {
      
        OK(void) :
          Rule<TestState>("Read.OK")
        {
    
        }
      
        bool precondition(const TestState& state) {
          return state.precondition__Read__OK();
        }
    
        void action(TestState& state) {
          state.action__Read__OK();
        }
      
      };
    
    }

    namespace Write {
    
      struct OK :
        public Test::Rule<TestState>
      {
      
        OK(void) :
          Rule<TestState>("Write.OK")
        {
    
        }
      
        bool precondition(const TestState& state) {
          return state.precondition__Write__OK();
        }
    
        void action(TestState& state) {
          state.action__Write__OK();
        }
      
      };
    
    }

    namespace Time {
    
      struct OK :
        public Test::Rule<TestState>
      {
      
        OK(void) :
          Rule<TestState>("Time.OK")
        {
    
        }
      
        bool precondition(const TestState& state) {
          return state.precondition__Time__OK();
        }
    
        void action(TestState& state) {
          state.action__Time__OK();
        }
      
      };
    
    }

    namespace Time {
    
      struct ERROR :
        public Test::Rule<TestState>
      {
      
        ERROR(void) :
          Rule<TestState>("Time.ERROR")
        {
    
        }
      
        bool precondition(const TestState& state) {
          return state.precondition__Time__ERROR();
        }
    
        void action(TestState& state) {
          state.action__Time__ERROR();
        }
      
      };
    
    }

  }

}

#endif
