// ====================================================================== 
// \title  Rules/Misc.hpp
// \author ciankc
// \brief  Rules/Misc class interface
//
// \copyright
// Copyright (C) 2019 California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
// ======================================================================

#ifndef Drv_Misc_HPP
#define Drv_Misc_HPP

#include "fprime-sphinx-drivers/NORFlashManager/test/ut/Rules/Rules.hpp"
#include "fprime-sphinx-drivers/NORFlashManager/test/ut/TestState/TestState.hpp"
#include "fprime-sphinx-drivers/Util/SphinxDrvBitUtil.hpp"

namespace Drv {

  namespace Misc {

    class Tester {

      public:

        Tester(const char* compName, U32 timeout);
      
        // ---------------------------------------------------------------------- 
        // Tests
        // ---------------------------------------------------------------------- 
        
        void SchedIn(void);
        void Ping(void);
        void Verify(void);

      public:

        // ----------------------------------------------------------------------
        // Rules 
        // ----------------------------------------------------------------------

        Rules::Misc::SchedIn ruleSchedIn;
        Rules::Misc::Ping rulePing;
        Rules::Misc::Verify ruleVerify;

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
