// ====================================================================== 
// \title  Rules/SPIMutex.hpp
// \author ciankc
// \brief  Rules/SPIMutex class interface
//
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
// ======================================================================

#ifndef Drv_SPIMutex_HPP
#define Drv_SPIMutex_HPP

#include "fprime-sphinx-drivers/SPIDriverGeneric/test/ut/Rules/Rules.hpp"
#include "fprime-sphinx-drivers/SPIDriverGeneric/test/ut/TestState/TestState.hpp"

namespace Drv {

  namespace SPIMutex {

    class Tester {

      public:

        // ---------------------------------------------------------------------- 
        // Tests
        // ---------------------------------------------------------------------- 
        
        void ClaimOK(void);
        void ClaimDouble(void);
        void UnclaimOK(void);
        void UnclaimDouble(void);

      public:

        // ----------------------------------------------------------------------
        // Rules 
        // ----------------------------------------------------------------------

        Rules::SPIMutex::ClaimOK ruleClaimOK;
        Rules::SPIMutex::ClaimDouble ruleClaimDouble;
        Rules::SPIMutex::UnclaimOK ruleUnclaimOK;
        Rules::SPIMutex::UnclaimDouble ruleUnclaimDouble;

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
