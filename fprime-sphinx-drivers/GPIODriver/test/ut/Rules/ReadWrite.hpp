// ====================================================================== 
// \title  Rules/ReadWrite.hpp
// \author ciankc
// \brief  Rules/ReadWrite class interface
//
// \copyright
// Copyright (C) 2019 California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
// ======================================================================

#ifndef Drv_ReadWrite_HPP
#define Drv_ReadWrite_HPP

#include "fprime-sphinx-drivers/GPIODriver/test/ut/Rules/Rules.hpp"
#include "fprime-sphinx-drivers/GPIODriver/test/ut/TestState/TestState.hpp"
#include "fprime-sphinx-drivers/Util/SphinxDrvBitUtil.hpp"

namespace Drv {
    static U32 addr1 = GPIO_APB_1_ADDR;
    static U32 addr2 = GPIO_APB_2_ADDR;
    static U32 pn1 = 1;
    static U32 pn2 = 40;

  namespace ReadWrite {

    class Tester {

      public:

        // ---------------------------------------------------------------------- 
        // Tests
        // ---------------------------------------------------------------------- 

        void DIRIN(void);
        void DIROUT(void);
        void READIN(void);
        void READOUT(void);
        void SETOUT(void);
        void CLEAROUT(void);
        void ERROR(void);

      public:

        // ----------------------------------------------------------------------
        // Rules 
        // ----------------------------------------------------------------------

        Rules::ReadWrite::DIRIN ruleDIRIN;
        Rules::ReadWrite::DIROUT ruleDIROUT;
        Rules::ReadWrite::READIN ruleREADIN;
        Rules::ReadWrite::READOUT ruleREADOUT;
        Rules::ReadWrite::SETOUT ruleSETOUT;
        Rules::ReadWrite::CLEAROUT ruleCLEAROUT;
        Rules::ReadWrite::ERROR ruleERROR;

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
