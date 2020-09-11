// ====================================================================== 
// \title  Rules/Time.hpp
// \author ciankc
// \brief  Rules/Time class interface
//
// \copyright
// Copyright (C) 2019 California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
// ======================================================================

#ifndef Drv_Time_HPP
#define Drv_Time_HPP

#include "fprime-sphinx-drivers/FPGADriver/test/ut/Rules/Rules.hpp"
#include "fprime-sphinx-drivers/FPGADriver/test/ut/TestState/TestState.hpp"
#include "fprime-sphinx-drivers/Util/SphinxDrvBitUtil.hpp"

namespace Drv {

  namespace Time {

    class Tester {

      public:

        // ---------------------------------------------------------------------- 
        // Tests
        // ---------------------------------------------------------------------- 
        
        void OK(void);
        void ERROR(void);

      public:

        // ----------------------------------------------------------------------
        // Rules 
        // ----------------------------------------------------------------------

        Rules::Time::OK ruleOK;
        Rules::Time::ERROR ruleERROR;

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
