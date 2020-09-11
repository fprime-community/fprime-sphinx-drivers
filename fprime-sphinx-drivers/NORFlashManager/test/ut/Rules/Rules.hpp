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
#include "fprime-sphinx-drivers/NORFlashManager/test/ut/TestState/TestState.hpp"
#include "fprime-sphinx-drivers/NORFlashManager/test/ut/Tester.hpp"

namespace Drv {

  namespace Rules { 

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

    namespace Erase {
    
      struct ERROR :
        public Test::Rule<TestState>
      {
      
        ERROR(void) :
          Rule<TestState>("Erase.ERROR")
        {
    
        }
      
        bool precondition(const TestState& state) {
          return state.precondition__Erase__ERROR();
        }
    
        void action(TestState& state) {
          state.action__Erase__ERROR();
        }
      
      };
    
    }

    namespace Size {
    
      struct Block :
        public Test::Rule<TestState>
      {
      
        Block(void) :
          Rule<TestState>("Size.Block")
        {
    
        }
      
        bool precondition(const TestState& state) {
          return state.precondition__Size__Block();
        }
    
        void action(TestState& state) {
          state.action__Size__Block();
        }
      
      };
    
    }

    namespace Size {
    
      struct FSW :
        public Test::Rule<TestState>
      {
      
        FSW(void) :
          Rule<TestState>("Size.FSW")
        {
    
        }
      
        bool precondition(const TestState& state) {
          return state.precondition__Size__FSW();
        }
    
        void action(TestState& state) {
          state.action__Size__FSW();
        }
      
      };
    
    }

    namespace Worker {
    
      struct Write :
        public Test::Rule<TestState>
      {
      
        Write(void) :
          Rule<TestState>("Worker.Write")
        {
    
        }
      
        bool precondition(const TestState& state) {
          return state.precondition__Worker__Write();
        }
    
        void action(TestState& state) {
          state.action__Worker__Write();
        }
      
      };
    
    }
    
    namespace Worker {
    
      struct Read :
        public Test::Rule<TestState>
      {
      
        Read(void) :
          Rule<TestState>("Worker.Read")
        {
    
        }
      
        bool precondition(const TestState& state) {
          return state.precondition__Worker__Read();
        }
    
        void action(TestState& state) {
          state.action__Worker__Read();
        }
      
      };
    
    }
    
    namespace Worker {
    
      struct Erase :
        public Test::Rule<TestState>
      {
      
        Erase(void) :
          Rule<TestState>("Worker.Erase")
        {
    
        }
      
        bool precondition(const TestState& state) {
          return state.precondition__Worker__Erase();
        }
    
        void action(TestState& state) {
          state.action__Worker__Erase();
        }
      
      };
    
    }
    
    namespace Worker {
    
      struct Reset :
        public Test::Rule<TestState>
      {
      
        Reset(void) :
          Rule<TestState>("Worker.Reset")
        {
    
        }
      
        bool precondition(const TestState& state) {
          return state.precondition__Worker__Reset();
        }
    
        void action(TestState& state) {
          state.action__Worker__Reset();
        }
      
      };
    
    }
    
    namespace Worker {
    
      struct Verify :
        public Test::Rule<TestState>
      {
      
        Verify(void) :
          Rule<TestState>("Worker.Verify")
        {
    
        }
      
        bool precondition(const TestState& state) {
          return state.precondition__Worker__Verify();
        }
    
        void action(TestState& state) {
          state.action__Worker__Verify();
        }
      
      };
    
    }
    
    namespace Worker {
    
      struct Error :
        public Test::Rule<TestState>
      {
      
        Error(void) :
          Rule<TestState>("Worker.Error")
        {
    
        }
      
        bool precondition(const TestState& state) {
          return state.precondition__Worker__Error();
        }
    
        void action(TestState& state) {
          state.action__Worker__Error();
        }
      
      };
    
    }
    
    namespace Misc {
   
      struct SchedIn :
        public Test::Rule<TestState>
      {
      
        SchedIn(void) :
          Rule<TestState>("Misc.SchedIn")
        {
    
        }
      
        bool precondition(const TestState& state) {
          return state.precondition__Misc__SchedIn();
        }
    
        void action(TestState& state) {
          state.action__Misc__SchedIn();
        }
      
      };
    
    }

    namespace Misc {
    
      struct Ping :
        public Test::Rule<TestState>
      {
      
        Ping(void) :
          Rule<TestState>("Misc.Ping")
        {
    
        }
      
        bool precondition(const TestState& state) {
          return state.precondition__Misc__Ping();
        }
    
        void action(TestState& state) {
          state.action__Misc__Ping();
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

    namespace Cmd {
    
      struct Reset :
        public Test::Rule<TestState>
      {
      
        Reset(void) :
          Rule<TestState>("Cmd.Reset")
        {
    
        }
      
        bool precondition(const TestState& state) {
          return state.precondition__Cmd__Reset();
        }
    
        void action(TestState& state) {
          state.action__Cmd__Reset();
        }
      
      };
    
    }

    namespace Cmd {
    
      struct Timeout :
        public Test::Rule<TestState>
      {
      
        Timeout(void) :
          Rule<TestState>("Cmd.Timeout")
        {
    
        }
      
        bool precondition(const TestState& state) {
          return state.precondition__Cmd__Timeout();
        }
    
        void action(TestState& state) {
          state.action__Cmd__Timeout();
        }
      
      };
    
    }

  }

}

#endif
