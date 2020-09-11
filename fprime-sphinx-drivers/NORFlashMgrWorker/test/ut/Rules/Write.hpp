// ====================================================================== 
// \title  Rules/Write.hpp
// \author ciankc
// \brief  Rules/Write class interface
//
// \copyright
// Copyright (C) 2019 California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
// ======================================================================

#ifndef Drv_Write_HPP
#define Drv_Write_HPP

#include "fprime-sphinx-drivers/NORFlashMgrWorker/test/ut/Rules/Rules.hpp"
#include "fprime-sphinx-drivers/NORFlashMgrWorker/test/ut/TestState/TestState.hpp"
#include "fprime-sphinx-drivers/Util/SphinxDrvBitUtil.hpp"

namespace Drv {

  namespace Write {

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

        Rules::Write::OK ruleOK;
        Rules::Write::ERROR ruleERROR;

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
