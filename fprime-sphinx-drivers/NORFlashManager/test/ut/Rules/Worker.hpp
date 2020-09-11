// ====================================================================== 
// \title  Rules/Worker.hpp
// \author ciankc
// \brief  Rules/Worker class interface
//
// \copyright
// Copyright (C) 2019 California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
// ======================================================================

#ifndef Drv_Worker_HPP
#define Drv_Worker_HPP

#include "fprime-sphinx-drivers/NORFlashManager/test/ut/Rules/Rules.hpp"
#include "fprime-sphinx-drivers/NORFlashManager/test/ut/TestState/TestState.hpp"
#include "fprime-sphinx-drivers/Util/SphinxDrvBitUtil.hpp"

namespace Drv {

  namespace Worker {

    class Tester {

      public:

        Tester(const char* compName, U32 timeout);
      
        // ---------------------------------------------------------------------- 
        // Tests
        // ---------------------------------------------------------------------- 
        
        void Write(void);
        void Read(void);
        void Erase(void);
        void Reset(void);
        void Verify(void);
        void Error(void);

      public:

        // ----------------------------------------------------------------------
        // Rules =        // ----------------------------------------------------------------------

        Rules::Worker::Write ruleWrite;
        Rules::Worker::Read ruleRead;
        Rules::Worker::Erase ruleErase;
        Rules::Worker::Reset ruleReset;
        Rules::Worker::Verify ruleVerify;
        Rules::Worker::Error ruleError;

      private:

        // ----------------------------------------------------------------------
        // Private member variables
        // ----------------------------------------------------------------------

        //! Test state
        TestState testState;

    };

  }

}
#endif
