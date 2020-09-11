// ====================================================================== 
// \title  Rules.hpp
// \author ciankc
// \brief  Rules for testing SphinxUartOnboardDriver
//
// \copyright
// Copyright (C) 2019 California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
// ======================================================================

#ifndef Drv_Rules_HPP
#define Drv_Rules_HPP

#include "fprime-sphinx-drivers/Test/Scenario/Rule.hpp"
#include "fprime-sphinx-drivers/SphinxUartOnboardDriver/test/ut/TestState/TestState.hpp"

namespace Drv {

  static U32 fw[4] = {2, 3, 6, 7};
  static U32 hw[4] = {0, 1, 4, 5};
  static U32 br[8] = {2400, 4800, 9600, 19200, 38500, 57600, 115200, 1000000};
  static U32 bm[8] = {0x0, 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7};
  static U32 rp[8] = {0x80000100,0x80100100,0x20160000,0x20170000,0x80100400,0x80100500,0x20180000,0x20190000};

  namespace Rules {
    
    namespace BytesUsed {
    
      struct OK :
        public Test::Rule<TestState>
      {
      
        OK(void) :
          Rule<TestState>("BytesUsed.OK")
        {
    
        }
      
        bool precondition(const TestState& state) {
          return state.precondition__BytesUsed__OK();
        }
    
        void action(TestState& state) {
          state.action__BytesUsed__OK();
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
    
      struct HWOK :
        public Test::Rule<TestState>
      {
      
        HWOK(void) :
          Rule<TestState>("Init.HWOK")
        {
    
        }
      
        bool precondition(const TestState& state) {
          return state.precondition__Init__HWOK();
        }
    
        void action(TestState& state) {
          state.action__Init__HWOK();
        }
      
      };
    
    }

    
    namespace Writer {
    
      struct TIMEOUT :
        public Test::Rule<TestState>
      {
      
        TIMEOUT(void) :
          Rule<TestState>("Writer.TIMEOUT")
        {
    
        }
      
        bool precondition(const TestState& state) {
          return state.precondition__Writer__TIMEOUT();
        }
    
        void action(TestState& state) {
          state.action__Writer__TIMEOUT();
        }
      
      };
    
    }

    namespace Writer {
    
      struct OK :
        public Test::Rule<TestState>
      {
      
        OK(void) :
          Rule<TestState>("Writer.OK")
        {
    
        }
      
        bool precondition(const TestState& state) {
          return state.precondition__Writer__OK();
        }
    
        void action(TestState& state) {
          state.action__Writer__OK();
        }
      
      };
    
    }

    namespace Writer {
    
      struct NBYTES :
        public Test::Rule<TestState>
      {
      
        NBYTES(void) :
          Rule<TestState>("Writer.NBYTES")
        {
    
        }
      
        bool precondition(const TestState& state) {
          return state.precondition__Writer__NBYTES();
        }
    
        void action(TestState& state) {
          state.action__Writer__NBYTES();
        }
      
      };
    
    }

    namespace Writer {
    
      struct NULLPTR :
        public Test::Rule<TestState>
      {
      
        NULLPTR(void) :
          Rule<TestState>("Writer.NULLPTR")
        {
    
        }
      
        bool precondition(const TestState& state) {
          return state.precondition__Writer__NULLPTR();
        }
    
        void action(TestState& state) {
          state.action__Writer__NULLPTR();
        }
      
      };
    
    }
    
    namespace Reader {
    
      struct TIMEOUT :
        public Test::Rule<TestState>
      {
      
        TIMEOUT(void) :
          Rule<TestState>("Reader.TIMEOUT")
        {
    
        }
      
        bool precondition(const TestState& state) {
          return state.precondition__Reader__TIMEOUT();
        }
    
        void action(TestState& state) {
          state.action__Reader__TIMEOUT();
        }
      
      };
    
    }

    namespace Reader {
    
      struct OK :
        public Test::Rule<TestState>
      {
      
        OK(void) :
          Rule<TestState>("Reader.OK")
        {
    
        }
      
        bool precondition(const TestState& state) {
          return state.precondition__Reader__OK();
        }
    
        void action(TestState& state) {
          state.action__Reader__OK();
        }
      
      };
    
    }

    namespace Reader {
    
      struct NBYTES :
        public Test::Rule<TestState>
      {
      
        NBYTES(void) :
          Rule<TestState>("Reader.NBYTES")
        {
    
        }
      
        bool precondition(const TestState& state) {
          return state.precondition__Reader__NBYTES();
        }
    
        void action(TestState& state) {
          state.action__Reader__NBYTES();
        }
      
      };
    
    }

    namespace Reader {
    
      struct NULLPTR :
        public Test::Rule<TestState>
      {
      
        NULLPTR(void) :
          Rule<TestState>("Reader.NULLPTR")
        {
    
        }
      
        bool precondition(const TestState& state) {
          return state.precondition__Reader__NULLPTR();
        }
    
        void action(TestState& state) {
          state.action__Reader__NULLPTR();
        }
      
      };
    
    }

    namespace Reader {
    
      struct DATA :
        public Test::Rule<TestState>
      {
      
        DATA(void) :
          Rule<TestState>("Reader.DATA")
        {
    
        }
      
        bool precondition(const TestState& state) {
          return state.precondition__Reader__DATA();
        }
    
        void action(TestState& state) {
          state.action__Reader__DATA();
        }
      
      };
    
    }

    namespace Reader {
    
      struct ERROR :
        public Test::Rule<TestState>
      {
      
        ERROR(void) :
          Rule<TestState>("Reader.ERROR")
        {
    
        }
      
        bool precondition(const TestState& state) {
          return state.precondition__Reader__ERROR();
        }
    
        void action(TestState& state) {
          state.action__Reader__ERROR();
        }
      
      };
    
    }

    namespace Reader {
    
      struct EMPTY :
        public Test::Rule<TestState>
      {
      
        EMPTY(void) :
          Rule<TestState>("Reader.EMPTY")
        {
    
        }
      
        bool precondition(const TestState& state) {
          return state.precondition__Reader__EMPTY();
        }
    
        void action(TestState& state) {
          state.action__Reader__EMPTY();
        }
      
      };
    
    }

    namespace Reader {
    
      struct FWOK :
        public Test::Rule<TestState>
      {
      
        FWOK(void) :
          Rule<TestState>("Reader.FWOK")
        {
    
        }
      
        bool precondition(const TestState& state) {
          return state.precondition__Reader__FWOK();
        }
    
        void action(TestState& state) {
          state.action__Reader__FWOK();
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
