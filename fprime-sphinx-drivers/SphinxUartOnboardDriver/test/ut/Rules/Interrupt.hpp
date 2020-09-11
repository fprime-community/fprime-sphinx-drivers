// ====================================================================== 
// \title  Rules/Interrupt.hpp
// \author ciankc
// \brief  Rules/Interrupt class interface
//
// \copyright
// Copyright (C) 2019 California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
// ======================================================================

#ifndef Drv_Interrupt_HPP
#define Drv_Interrupt_HPP

#include "fprime-sphinx-drivers/SphinxUartOnboardDriver/test/ut/Rules/Rules.hpp"
#include "fprime-sphinx-drivers/SphinxUartOnboardDriver/test/ut/TestState/TestState.hpp"
#include "fprime-sphinx-drivers/Util/SphinxDrvBitUtil.hpp"

namespace Drv {

  namespace Interrupt {

    class Tester {

      public:

        // ---------------------------------------------------------------------- 
        // Tests
        // ---------------------------------------------------------------------- 

        //! OK
        void OK(void);

      public:

        // ----------------------------------------------------------------------
        // Rules 
        // ----------------------------------------------------------------------

        Rules::Interrupt::OK ruleOK;

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
