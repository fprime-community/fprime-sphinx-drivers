// ======================================================================                        
// \title  TestState.hpp                                                                           
// \author ciankc
// \brief  Test state for testing GPIODriver                                                           
//                                                                                                 
// \copyright                                                                                      
// Copyright (C) 2019 California Institute of Technology.                                          
// ALL RIGHTS RESERVED.  United States Government Sponsorship                                      
// acknowledged.
// ======================================================================   

#ifndef Drv_TestState_HPP
#define Drv_TestState_HPP

#include "fprime-sphinx-drivers/GPIODriver/test/ut/Tester.hpp"

namespace Drv {

  class TestState :
    public Tester
  {
    
  public:

    // ----------------------------------------------------------------------                     
    // Rule definitions                                                                           
    // ---------------------------------------------------------------------- 

    bool precondition__ReadWrite__DIRIN(void) const;
    void action__ReadWrite__DIRIN(void);

    bool precondition__ReadWrite__DIROUT(void) const;
    void action__ReadWrite__DIROUT(void);

    bool precondition__ReadWrite__READIN(void) const;
    void action__ReadWrite__READIN(void);

    bool precondition__ReadWrite__READOUT(void) const;
    void action__ReadWrite__READOUT(void);

    bool precondition__ReadWrite__SETOUT(void) const;
    void action__ReadWrite__SETOUT(void);

    bool precondition__ReadWrite__CLEAROUT(void) const;
    void action__ReadWrite__CLEAROUT(void);

    bool precondition__ReadWrite__ERROR(void) const;
    void action__ReadWrite__ERROR(void);

    bool precondition__Init__OK(void) const;
    void action__Init__OK(void);

    bool precondition__Init__ERROR(void) const;
    void action__Init__ERROR(void);

    bool precondition__Interrupt__OK(void) const;
    void action__Interrupt__OK(void);

  };

}

#endif
