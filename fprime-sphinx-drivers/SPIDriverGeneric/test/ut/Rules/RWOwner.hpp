// ====================================================================== 
// \title  Rules/RWOwner.hpp
// \author ciankc
// \brief  Rules/RWOwner class interface
//
// \copyright
// Copyright (C) 2019 California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
// ======================================================================

#ifndef Drv_RWOwner_HPP
#define Drv_RWOwner_HPP

#include "fprime-sphinx-drivers/SPIDriverGeneric/test/ut/Rules/Rules.hpp"
#include "fprime-sphinx-drivers/SPIDriverGeneric/test/ut/TestState/TestState.hpp"
#include "fprime-sphinx-drivers/Util/SphinxDrvBitUtil.hpp"
#include "SPIMutex.hpp"

namespace Drv {

  namespace RWOwner {

    class Tester {

      public:

        // ---------------------------------------------------------------------- 
        // Tests
        // ---------------------------------------------------------------------- 

        //! SUCCESS
        void SUCCESS8(void);
        void SUCCESS16(void);
        void SUCCESS32(void);
        void ERROR(void);
        void TIMEOUT(void);

      public:

        // ----------------------------------------------------------------------
        // Rules 
        // ----------------------------------------------------------------------

        //! Rule RWOwner::SUCCESS
        Rules::RWOwner::SUCCESS8 ruleSUCCESS8;
        Rules::RWOwner::SUCCESS16 ruleSUCCESS16;
        Rules::RWOwner::SUCCESS32 ruleSUCCESS32;
        Rules::RWOwner::ERROR ruleERROR;
        Rules::RWOwner::TIMEOUT ruleTIMEOUT;

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
