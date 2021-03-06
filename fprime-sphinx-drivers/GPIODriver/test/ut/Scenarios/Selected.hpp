// ====================================================================== 
// \title  Selected.hpp
// \author ciankc
// \brief  Scenarios containing selected rules
//
// \copyright
// Copyright (C) 2017 California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
// ====================================================================== 

#ifndef Drv_Selected_HPP
#define Drv_Selected_HPP

#include "fprime-sphinx-drivers/GPIODriver/test/ut/TestState/TestState.hpp"

namespace Drv {

  namespace Selected {

    class Tester {

      public:

        // ---------------------------------------------------------------------- 
        // Tests
        // ---------------------------------------------------------------------- 

        //! Random testing
        void Random(void);

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
