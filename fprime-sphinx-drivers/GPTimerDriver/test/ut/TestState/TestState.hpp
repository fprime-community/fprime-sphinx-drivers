// ======================================================================                        
// \title  TestState.hpp                                                                           
// \author ciankc
// \brief  Test state for testing FPGASPIDriver
//                                                                                                 
// \copyright                                                                                      
// Copyright (C) 2019 California Institute of Technology.                                          
// ALL RIGHTS RESERVED.  United States Government Sponsorship                                      
// acknowledged.
// ======================================================================   

#ifndef Drv_TestState_HPP
#define Drv_TestState_HPP

#include "fprime-sphinx-drivers/GPTimerDriver/test/ut/Tester.hpp"

namespace Drv {

  class TestState :
    public Tester
  {
    
  public:

    TestState(const char *const compName,

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
	    const U32 timer4CtlReg) 
      : Tester(compName, prescalerReload, prescalerValue,
  	   timer1Reserved, timer1UsrConfig, timer1CntReg, timer1RldReg, timer1CtlReg,
  	   timer2Reserved, timer2UsrConfig, timer2CntReg, timer2RldReg, timer2CtlReg,
	   timer3Reserved, timer3UsrConfig, timer3CntReg, timer3RldReg, timer3CtlReg,
	   timer4Reserved, timer4UsrConfig, timer4CntReg, timer4RldReg, timer4CtlReg)
    {

    }

    // ----------------------------------------------------------------------                     
    // Rule definitions                                                                           
    // ---------------------------------------------------------------------- 

    bool precondition__Owner__ClaimOK(void) const;
    void action__Owner__ClaimOK(void);

    bool precondition__Owner__ClaimERROR(void) const;
    void action__Owner__ClaimERROR(void);

    bool precondition__Owner__UnclaimOK(void) const;
    void action__Owner__UnclaimOK(void);

    bool precondition__Owner__UnclaimERROR(void) const;
    void action__Owner__UnclaimERROR(void);

    bool precondition__Read__OK(void) const;
    void action__Read__OK(void);

    bool precondition__Read__ERROR(void) const;
    void action__Read__ERROR(void);

    bool precondition__Write__OK(void) const;
    void action__Write__OK(void);

    bool precondition__Write__ERROR(void) const;
    void action__Write__ERROR(void);

  };

}

#endif
