// ====================================================================== 
// \title  Rules/Erase.hpp
// \author ciankc
// \brief  Rules/Erase class interface
//
// \copyright
// Copyright (C) 2019 California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
// ======================================================================

#ifndef Drv_Erase_HPP
#define Drv_Erase_HPP

#include "fprime-sphinx-drivers/NORFlashMgrWorker/test/ut/Rules/Rules.hpp"
#include "fprime-sphinx-drivers/NORFlashMgrWorker/test/ut/TestState/TestState.hpp"
#include "fprime-sphinx-drivers/Util/SphinxDrvBitUtil.hpp"

namespace Drv {

  namespace Erase {

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

        Rules::Erase::OK ruleOK;

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
