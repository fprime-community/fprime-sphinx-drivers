// ====================================================================== 
// \title  Rules/RWReverse.hpp
// \author ciankc
// \brief  Rules/RWReverse class interface
//
// \copyright
// Copyright (C) 2019 California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
// ======================================================================

#ifndef Drv_RWReverse_HPP
#define Drv_RWReverse_HPP

#include "fprime-sphinx-drivers/SPIDriverGeneric/test/ut/Rules/Rules.hpp"
#include "fprime-sphinx-drivers/SPIDriverGeneric/test/ut/TestState/TestState.hpp"
#include "fprime-sphinx-drivers/Util/SphinxDrvBitUtil.hpp"
#include "SPIMutex.hpp"

namespace Drv {

  namespace RWReverse {

    class Tester {

      public:

        // ---------------------------------------------------------------------- 
        // Tests
        // ---------------------------------------------------------------------- 

        //! SUCCESS
        void SUCCESS8(void);
        void SUCCESS16(void);
        void SUCCESS32(void);

      public:

        // ----------------------------------------------------------------------
        // Rules 
        // ----------------------------------------------------------------------

        //! Rule RWReverse::SUCCESS
        Rules::RWReverse::SUCCESS8 ruleSUCCESS8;
        Rules::RWReverse::SUCCESS16 ruleSUCCESS16;
        Rules::RWReverse::SUCCESS32 ruleSUCCESS32;

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
