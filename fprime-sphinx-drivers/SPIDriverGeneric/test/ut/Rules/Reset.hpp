// ====================================================================== 
// \title  Rules/Reset.hpp
// \author ciankc
// \brief  Rules/Reset class interface
//
// \copyright
// Copyright (C) 2019 California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
// ======================================================================

#ifndef Drv_Reset_HPP
#define Drv_Reset_HPP

#include "fprime-sphinx-drivers/SPIDriverGeneric/test/ut/Rules/Rules.hpp"
#include "fprime-sphinx-drivers/SPIDriverGeneric/test/ut/TestState/TestState.hpp"
#include "fprime-sphinx-drivers/Util/SphinxDrvUtil.hpp"

namespace Drv {

  namespace Reset {

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

        //! Rule Reset::OK
        Rules::Reset::OK ruleOK;

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
