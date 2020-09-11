// ====================================================================== 
// \title  Rules/Read.hpp
// \author ciankc
// \brief  Rules/Read class interface
//
// \copyright
// Copyright (C) 2019 California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
// ======================================================================

#ifndef Drv_Read_HPP
#define Drv_Read_HPP

#include "fprime-sphinx-drivers/FPGADriver/test/ut/Rules/Rules.hpp"
#include "fprime-sphinx-drivers/FPGADriver/test/ut/TestState/TestState.hpp"
#include "fprime-sphinx-drivers/Util/SphinxDrvBitUtil.hpp"
#include "Write.hpp"

namespace Drv {

  namespace Read {

    class Tester {

      public:

        // ---------------------------------------------------------------------- 
        // Tests
        // ---------------------------------------------------------------------- 
        
        void OK(void);

      public:

        // ----------------------------------------------------------------------
        // Rules 
        // ----------------------------------------------------------------------

        Rules::Read::OK ruleOK;

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
