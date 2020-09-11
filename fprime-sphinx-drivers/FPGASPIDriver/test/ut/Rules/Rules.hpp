// ====================================================================== 
// \title  Rules.hpp
// \author ciankc
// \brief  Rules for testing FPGASPIDriver
//
// \copyright
// Copyright (C) 2019 California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
// ======================================================================

#ifndef Drv_Rules_HPP
#define Drv_Rules_HPP

#include "fprime-sphinx-drivers/Test/Scenario/Rule.hpp"
#include "fprime-sphinx-drivers/FPGASPIDriver/test/ut/TestState/TestState.hpp"

namespace Drv {

  namespace Rules { 

    namespace ReadWrite {
    
      struct OK :
        public Test::Rule<TestState>
      {
      
        OK(void) :
          Rule<TestState>("ReadWrite.OK")
        {
    
        }
      
        bool precondition(const TestState& state) {
          return state.precondition__ReadWrite__OK();
        }
    
        void action(TestState& state) {
          state.action__ReadWrite__OK();
        }
      
      };
    
    }

    namespace ReadWrite {
    
      struct ERROR :
        public Test::Rule<TestState>
      {
      
        ERROR(void) :
          Rule<TestState>("ReadWrite.ERROR")
        {
    
        }
      
        bool precondition(const TestState& state) {
          return state.precondition__ReadWrite__ERROR();
        }
    
        void action(TestState& state) {
          state.action__ReadWrite__ERROR();
        }
      
      };
    
    }

  }

}

#endif
