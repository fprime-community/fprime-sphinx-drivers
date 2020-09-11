// ====================================================================== 
// \title  Rules.hpp
// \author ciankc
// \brief  Rules for testing GPTimerDriver
//
// \copyright
// Copyright (C) 2019 California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
// ======================================================================

#ifndef Drv_Rules_HPP
#define Drv_Rules_HPP

#include "fprime-sphinx-drivers/Test/Scenario/Rule.hpp"
#include "fprime-sphinx-drivers/GPTimerDriver/test/ut/TestState/TestState.hpp"

namespace Drv {

  namespace Rules { 

    namespace Owner {
    
      struct ClaimOK :
        public Test::Rule<TestState>
      {
      
        ClaimOK(void) :
          Rule<TestState>("Owner.ClaimOK")
        {
    
        }
      
        bool precondition(const TestState& state) {
          return state.precondition__Owner__ClaimOK();
        }
    
        void action(TestState& state) {
          state.action__Owner__ClaimOK();
        }
      
      };
    
    }

    namespace Owner {
    
      struct ClaimERROR :
        public Test::Rule<TestState>
      {
      
        ClaimERROR(void) :
          Rule<TestState>("Owner.ClaimERROR")
        {
    
        }
      
        bool precondition(const TestState& state) {
          return state.precondition__Owner__ClaimERROR();
        }
    
        void action(TestState& state) {
          state.action__Owner__ClaimERROR();
        }
      
      };
    
    }

    namespace Owner {
    
      struct UnclaimOK :
        public Test::Rule<TestState>
      {
      
        UnclaimOK(void) :
          Rule<TestState>("Owner.UnclaimOK")
        {
    
        }
      
        bool precondition(const TestState& state) {
          return state.precondition__Owner__UnclaimOK();
        }
    
        void action(TestState& state) {
          state.action__Owner__UnclaimOK();
        }
      
      };
    
    }

    namespace Owner {
    
      struct UnclaimERROR :
        public Test::Rule<TestState>
      {
      
        UnclaimERROR(void) :
          Rule<TestState>("Owner.UnclaimERROR")
        {
    
        }
      
        bool precondition(const TestState& state) {
          return state.precondition__Owner__UnclaimERROR();
        }
    
        void action(TestState& state) {
          state.action__Owner__UnclaimERROR();
        }
      
      };
    
    }
    
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
