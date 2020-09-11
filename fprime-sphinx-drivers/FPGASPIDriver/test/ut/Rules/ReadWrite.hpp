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

#include "fprime-sphinx-drivers/FPGASPIDriver/test/ut/Rules/Rules.hpp"
#include "fprime-sphinx-drivers/FPGASPIDriver/test/ut/TestState/TestState.hpp"
#include "fprime-sphinx-drivers/Util/SphinxDrvBitUtil.hpp"

namespace Drv {

  namespace ReadWrite {

    class Tester {

      public:
      
        Tester(const char* compName,
                 U32 spiNumber,
                 U32 spiWidth);
      
        // ---------------------------------------------------------------------- 
        // Tests
        // ---------------------------------------------------------------------- 
        
        void OK(void);
        void ERROR(void);

      public:

        // ----------------------------------------------------------------------
        // Rules 
        // ----------------------------------------------------------------------

        Rules::ReadWrite::OK ruleOK;
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
