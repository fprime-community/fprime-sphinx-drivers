// ====================================================================== 
// \title  Selected.hpp
// \author ciankc
// \brief  Scenarios containing selected rules
//
// \copyright
// Copyright (C) 2017 California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
// ====================================================================== 

#ifndef Drv_Selected_HPP
#define Drv_Selected_HPP

#include "fprime-sphinx-drivers/GPTimerDriver/test/ut/TestState/TestState.hpp"

namespace Drv {

  namespace Selected {

    class Tester {

      public:


      Tester(const char *const compName,

	   const U32 prescalerReload,
	   const U32 prescalerValue,

	   // Timer 1                                                                                                                                    
	   const bool timer1Reserved,
	   const bool timer1UsrConfig,
	   const U32 timer1CntReg,
	   const U32 timer1RldReg,
	   const U32 timer1CtlReg,

	   // Timer 2                                                                                                                                    
	   const bool timer2Reserved,
	   const bool timer2UsrConfig,
	   const U32 timer2CntReg,
	   const U32 timer2RldReg,
	   const U32 timer2CtlReg,

	   // Timer 3                                                                                                                                    
	   const bool timer3Reserved,
	   const bool timer3UsrConfig,
	   const U32 timer3CntReg,
	   const U32 timer3RldReg,
	   const U32 timer3CtlReg,

	   // Timer 4                                                                                                                                    
	   const bool timer4Reserved,
	   const bool timer4UsrConfig,
	   const U32 timer4CntReg,
	   const U32 timer4RldReg,
	   const U32 timer4CtlReg);

        // ---------------------------------------------------------------------- 
        // Tests
        // ---------------------------------------------------------------------- 

        //! Random testing
        void Random(void);

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
