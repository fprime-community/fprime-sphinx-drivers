// ====================================================================== 
// \title  Rules/Pointer.hpp
// \author ciankc
// \brief  Rules/Pointer class interface
//
// \copyright
// Copyright (C) 2019 California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
// ======================================================================

#ifndef Drv_Pointer_HPP
#define Drv_Pointer_HPP

#include "fprime-sphinx-drivers/SPIDriverGeneric/test/ut/Rules/Rules.hpp"
#include "fprime-sphinx-drivers/SPIDriverGeneric/test/ut/TestState/TestState.hpp"
#include "SPIMutex.hpp"

namespace Drv {

  namespace Pointer {

    class Tester {

      public:

        // ---------------------------------------------------------------------- 
        // Tests
        // ---------------------------------------------------------------------- 

        //! OK
        void Invalid(void);

      public:

        // ----------------------------------------------------------------------
        // Rules 
        // ----------------------------------------------------------------------

        //! Rule Pointer::OK
        Rules::Pointer::Invalid ruleInvalid;

      private:

        // ----------------------------------------------------------------------
        // Private member variables
        // ----------------------------------------------------------------------

        //! Test state
        TestState testState;
        SPIMutex::Tester mutexTester;
    };

  }

}
#endif
