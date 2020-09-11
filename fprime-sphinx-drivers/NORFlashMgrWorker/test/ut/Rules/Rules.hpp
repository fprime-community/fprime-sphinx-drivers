// ====================================================================== 
// \title  Rules.hpp
// \author ciankc
// \brief  Rules for testing NORFlashMgrWorker
//
// \copyright
// Copyright (C) 2019 California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
// ======================================================================

#ifndef Drv_Rules_HPP
#define Drv_Rules_HPP

#include "fprime-sphinx-drivers/Test/Scenario/Rule.hpp"
#include "fprime-sphinx-drivers/NORFlashMgrWorker/test/ut/TestState/TestState.hpp"

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

    namespace Erase {
    
      struct OK :
        public Test::Rule<TestState>
      {
      
        OK(void) :
          Rule<TestState>("Erase.OK")
        {
    
        }
      
        bool precondition(const TestState& state) {
          return state.precondition__Erase__OK();
        }
    
        void action(TestState& state) {
          state.action__Erase__OK();
        }
      
      };
    
    }

    namespace Misc {
    
      struct Cancel :
        public Test::Rule<TestState>
      {
      
        Cancel(void) :
          Rule<TestState>("Misc.Cancel")
        {
    
        }
      
        bool precondition(const TestState& state) {
          return state.precondition__Misc__Cancel();
        }
    
        void action(TestState& state) {
          state.action__Misc__Cancel();
        }
      
      };
    
    }
    
    namespace Misc {
    
      struct Reset :
        public Test::Rule<TestState>
      {
      
        Reset(void) :
          Rule<TestState>("Misc.Reset")
        {
    
        }
      
        bool precondition(const TestState& state) {
          return state.precondition__Misc__Reset();
        }
    
        void action(TestState& state) {
          state.action__Misc__Reset();
        }
      
      };
    
    }
    
    namespace Misc {
    
      struct Verify :
        public Test::Rule<TestState>
      {
      
        Verify(void) :
          Rule<TestState>("Misc.Verify")
        {
    
        }
      
        bool precondition(const TestState& state) {
          return state.precondition__Misc__Verify();
        }
    
        void action(TestState& state) {
          state.action__Misc__Verify();
        }
      
      };
    
    }

  }

}

#endif
