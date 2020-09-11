// ====================================================================== 
// \title  Rules/Writer.hpp
// \author ciankc
// \brief  Rules/Writer class interface
//
// \copyright
// Copyright (C) 2019 California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
// ======================================================================

#ifndef Drv_Writer_HPP
#define Drv_Writer_HPP

#include "fprime-sphinx-drivers/SphinxUartOnboardDriver/test/ut/Rules/Rules.hpp"
#include "fprime-sphinx-drivers/SphinxUartOnboardDriver/test/ut/TestState/TestState.hpp"
#include "fprime-sphinx-drivers/Util/SphinxDrvBitUtil.hpp"
#include "fprime-sphinx-drivers/SphinxUartOnboardDriver/test/ut/Rules/Init.hpp"

namespace Drv {

  namespace Writer {

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

      public:

        // ----------------------------------------------------------------------
        // Rules 
        // ----------------------------------------------------------------------

        //! Rule Write::TIMEOUT
        Rules::Writer::TIMEOUT ruleTIMEOUT;
        Rules::Writer::OK ruleOK;
        Rules::Writer::NULLPTR ruleNULLPTR;
        Rules::Writer::NBYTES ruleNBYTES;

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
