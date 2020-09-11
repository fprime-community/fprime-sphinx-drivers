// ====================================================================== 
// \title  Rules/Size.hpp
// \author ciankc
// \brief  Rules/Size class interface
//
// \copyright
// Copyright (C) 2019 California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
// ======================================================================

#ifndef Drv_Size_HPP
#define Drv_Size_HPP

#include "fprime-sphinx-drivers/NORFlashManager/test/ut/Rules/Rules.hpp"
#include "fprime-sphinx-drivers/NORFlashManager/test/ut/TestState/TestState.hpp"
#include "fprime-sphinx-drivers/Util/SphinxDrvBitUtil.hpp"

namespace Drv {

  namespace Size {

    class Tester {

      public:

        Tester(const char* compName, U32 timeout);
      
        // ---------------------------------------------------------------------- 
        // Tests
        // ---------------------------------------------------------------------- 
        
        void Block(void);
        void FSW(void);

      public:

        // ----------------------------------------------------------------------
        // Rules 
        // ----------------------------------------------------------------------

        Rules::Size::Block ruleBlock;
        Rules::Size::FSW ruleFSW;

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
