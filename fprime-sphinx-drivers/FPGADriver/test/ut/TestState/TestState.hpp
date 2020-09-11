// ======================================================================                        
// \title  TestState.hpp                                                                           
// \author ciankc
// \brief  Test state for testing FPGADriver
//                                                                                                 
// \copyright                                                                                      
// Copyright (C) 2019 California Institute of Technology.                                          
// ALL RIGHTS RESERVED.  United States Government Sponsorship                                      
// acknowledged.
// ======================================================================   

#ifndef Drv_TestState_HPP
#define Drv_TestState_HPP

#include "fprime-sphinx-drivers/FPGADriver/test/ut/Tester.hpp"

namespace Drv {

  class TestState :
    public Tester
  {

  public:

    // ----------------------------------------------------------------------                     
    // Rule definitions                                                                           
    // ---------------------------------------------------------------------- 

    bool precondition__Read__OK(void) const;
    void action__Read__OK(void);

    bool precondition__Write__OK(void) const;
    void action__Write__OK(void);

    bool precondition__Time__OK(void) const;
    void action__Time__OK(void);

    bool precondition__Time__ERROR(void) const;
    void action__Time__ERROR(void);

  };

}

#endif
