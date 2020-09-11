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

#include "fprime-sphinx-drivers/FPGASPIDriver/test/ut/Tester.hpp"

namespace Drv {

  class TestState :
    public Tester
  {
    
  public:

    TestState(const char* compName,
	    U32 spiNumber,
              U32 spiWidth)
      : Tester(compName, spiNumber, spiWidth)
    {

    }

    // ----------------------------------------------------------------------                     
    // Rule definitions                                                                           
    // ---------------------------------------------------------------------- 

    bool precondition__ReadWrite__OK(void) const;
    void action__ReadWrite__OK(void);

    bool precondition__ReadWrite__ERROR(void) const;
    void action__ReadWrite__ERROR(void);

  };

}

#endif
