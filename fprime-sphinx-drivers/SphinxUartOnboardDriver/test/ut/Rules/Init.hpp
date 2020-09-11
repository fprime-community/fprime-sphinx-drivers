// ====================================================================== 
// \title  Rules/Init.hpp
// \author ciankc
// \brief  Rules/Init class interface
//
// \copyright
// Copyright (C) 2019 California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
// ======================================================================

#ifndef Drv_Init_HPP
#define Drv_Init_HPP

#include "fprime-sphinx-drivers/SphinxUartOnboardDriver/test/ut/Rules/Rules.hpp"
#include "fprime-sphinx-drivers/SphinxUartOnboardDriver/test/ut/TestState/TestState.hpp"
#include "fprime-sphinx-drivers/Util/SphinxDrvBitUtil.hpp"

namespace Drv {

  namespace Init {

    class Tester {

      public:

        // ---------------------------------------------------------------------- 
        // Tests
        // ---------------------------------------------------------------------- 

        //! OK
        void OK(void);
        void HWOK(void);

      public:

        // ----------------------------------------------------------------------
        // Rules 
        // ----------------------------------------------------------------------

        //! Rule Init::OK
        Rules::Init::OK ruleOK;
        Rules::Init::HWOK ruleHWOK;

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
