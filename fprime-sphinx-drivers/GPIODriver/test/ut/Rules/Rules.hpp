// ====================================================================== 
// \title  Rules.hpp
// \author ciankc
// \brief  Rules for testing GPIODriver
//
// \copyright
// Copyright (C) 2019 California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
// ======================================================================

#ifndef Drv_Rules_HPP
#define Drv_Rules_HPP

#include "fprime-sphinx-drivers/Test/Scenario/Rule.hpp"
#include "fprime-sphinx-drivers/GPIODriver/test/ut/TestState/TestState.hpp"

namespace Drv {

  namespace Rules { 

    namespace ReadWrite {
    
      struct DIRIN :
        public Test::Rule<TestState>
      {
      
        DIRIN(void) :
          Rule<TestState>("ReadWrite.DIRIN")
        {
    
        }
      
        bool precondition(const TestState& state) {
          return state.precondition__ReadWrite__DIRIN();
        }
    
        void action(TestState& state) {
          state.action__ReadWrite__DIRIN();
        }
      
      };
    
    }

    namespace ReadWrite {
    
      struct DIROUT :
        public Test::Rule<TestState>
      {
      
        DIROUT(void) :
          Rule<TestState>("ReadWrite.DIROUT")
        {
    
        }
      
        bool precondition(const TestState& state) {
          return state.precondition__ReadWrite__DIROUT();
        }
    
        void action(TestState& state) {
          state.action__ReadWrite__DIROUT();
        }
      
      };
    
    }

    namespace ReadWrite {
    
      struct READIN :
        public Test::Rule<TestState>
      {
      
        READIN(void) :
          Rule<TestState>("ReadWrite.READIN")
        {
    
        }
      
        bool precondition(const TestState& state) {
          return state.precondition__ReadWrite__READIN();
        }
    
        void action(TestState& state) {
          state.action__ReadWrite__READIN();
        }
      
      };
    
    }

    namespace ReadWrite {
    
      struct READOUT :
        public Test::Rule<TestState>
      {
      
        READOUT(void) :
          Rule<TestState>("ReadWrite.READOUT")
        {
    
        }
      
        bool precondition(const TestState& state) {
          return state.precondition__ReadWrite__READOUT();
        }
    
        void action(TestState& state) {
          state.action__ReadWrite__READOUT();
        }
      
      };
    
    }

    namespace ReadWrite {
    
      struct SETOUT :
        public Test::Rule<TestState>
      {
      
        SETOUT(void) :
          Rule<TestState>("ReadWrite.SETOUT")
        {
    
        }
      
        bool precondition(const TestState& state) {
          return state.precondition__ReadWrite__SETOUT();
        }
    
        void action(TestState& state) {
          state.action__ReadWrite__SETOUT();
        }
      
      };
    
    }

    namespace ReadWrite {
    
      struct CLEAROUT :
        public Test::Rule<TestState>
      {
      
        CLEAROUT(void) :
          Rule<TestState>("ReadWrite.CLEAROUT")
        {
    
        }
      
        bool precondition(const TestState& state) {
          return state.precondition__ReadWrite__CLEAROUT();
        }
    
        void action(TestState& state) {
          state.action__ReadWrite__CLEAROUT();
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

    namespace Init {

      struct OK :
        public Test::Rule<TestState>
      {

        OK(void) :
          Rule<TestState>("Init.OK")
        {

        }

        bool precondition(const TestState& state) {
          return state.precondition__Init__OK();
        }

        void action(TestState& state) {
          state.action__Init__OK();
        }

      };

    }

    namespace Init {

      struct ERROR :
        public Test::Rule<TestState>
      {

        ERROR(void) :
          Rule<TestState>("Init.ERROR")
        {

        }

        bool precondition(const TestState& state) {
          return state.precondition__Init__ERROR();
        }

        void action(TestState& state) {
          state.action__Init__ERROR();
        }

      };

    }

    namespace Interrupt {

      struct OK :
        public Test::Rule<TestState>
      {

        OK(void) :
          Rule<TestState>("Interrupt.OK")
        {

        }

        bool precondition(const TestState& state) {
          return state.precondition__Interrupt__OK();
        }

        void action(TestState& state) {
          state.action__Interrupt__OK();
        }

      };

    }

  }

}

#endif
