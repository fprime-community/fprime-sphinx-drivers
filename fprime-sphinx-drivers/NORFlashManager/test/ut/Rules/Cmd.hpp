// ====================================================================== 
// \title  Rules/Cmd.hpp
// \author ciankc
// \brief  Rules/Cmd class interface
//
// \copyright
// Copyright (C) 2019 California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
// ======================================================================

#ifndef Drv_Cmd_HPP
#define Drv_Cmd_HPP

#include "fprime-sphinx-drivers/NORFlashManager/test/ut/Rules/Rules.hpp"
#include "fprime-sphinx-drivers/NORFlashManager/test/ut/TestState/TestState.hpp"
#include "fprime-sphinx-drivers/Util/SphinxDrvBitUtil.hpp"

namespace Drv {

  namespace Cmd {

    class Tester {

      public:

        Tester(const char* compName, U32 timeout);
      
        // ---------------------------------------------------------------------- 
        // Tests
        // ---------------------------------------------------------------------- 
        
        void Reset(void);
        void Timeout(void);

      public:

        // ----------------------------------------------------------------------
        // Rules 
        // ----------------------------------------------------------------------

        Rules::Cmd::Reset ruleReset;
        Rules::Cmd::Timeout ruleTimeout;

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
