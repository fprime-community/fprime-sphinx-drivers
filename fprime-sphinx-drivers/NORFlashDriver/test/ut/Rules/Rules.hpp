// ====================================================================== 
// \title  Rules.hpp
// \author ciankc
// \brief  Rules for testing NORFlashDriver
//
// \copyright
// Copyright (C) 2019 California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
// ======================================================================

#ifndef Drv_Rules_HPP
#define Drv_Rules_HPP

#include "fprime-sphinx-drivers/Test/Scenario/Rule.hpp"
#include "fprime-sphinx-drivers/NORFlashDriver/test/ut/TestState/TestState.hpp"

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

    namespace Read {
    
      struct ERROR :
        public Test::Rule<TestState>
      {
      
        ERROR(void) :
          Rule<TestState>("Read.ERROR")
        {
    
        }
      
        bool precondition(const TestState& state) {
          return state.precondition__Read__ERROR();
        }
    
        void action(TestState& state) {
          state.action__Read__ERROR();
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

    namespace Write {
    
      struct ERROR :
        public Test::Rule<TestState>
      {
      
        ERROR(void) :
          Rule<TestState>("Write.ERROR")
        {
    
        }
      
        bool precondition(const TestState& state) {
          return state.precondition__Write__ERROR();
        }
    
        void action(TestState& state) {
          state.action__Write__ERROR();
        }
      
      };
    
    }

  }

}

#endif
