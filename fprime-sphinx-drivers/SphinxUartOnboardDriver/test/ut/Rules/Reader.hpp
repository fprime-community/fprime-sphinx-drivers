// ====================================================================== 
// \title  Rules/Reader.hpp
// \author ciankc
// \brief  Rules/Reader class interface
//
// \copyright
// Copyright (C) 2019 California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
// ======================================================================

#ifndef Drv_Reader_HPP
#define Drv_Reader_HPP

#include "fprime-sphinx-drivers/SphinxUartOnboardDriver/test/ut/Rules/Rules.hpp"
#include "fprime-sphinx-drivers/SphinxUartOnboardDriver/test/ut/TestState/TestState.hpp"
#include "fprime-sphinx-drivers/Util/SphinxDrvBitUtil.hpp"

namespace Drv {

  namespace Reader {

    class Tester {

      public:

        // ---------------------------------------------------------------------- 
        // Tests
        // ---------------------------------------------------------------------- 

        //! OK
        void TIMEOUT(void);
        void NULLPTR(void);
        void OK(void);
        void NBYTES(void);
        void DATA(void);
        void ERROR(void);
        void EMPTY(void);
        void FWOK(void);

      public:

        // ----------------------------------------------------------------------
        // Rules 
        // ----------------------------------------------------------------------

        //! Rule Write::TIMEOUT
        Rules::Reader::TIMEOUT ruleTIMEOUT;
        Rules::Reader::OK ruleOK;
        Rules::Reader::NULLPTR ruleNULLPTR;
        Rules::Reader::NBYTES ruleNBYTES;
        Rules::Reader::DATA ruleDATA;
        Rules::Reader::ERROR ruleERROR;
        Rules::Reader::EMPTY ruleEMPTY;
        Rules::Reader::FWOK ruleFWOK;

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
