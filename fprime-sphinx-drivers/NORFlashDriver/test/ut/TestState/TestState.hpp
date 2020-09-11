// ======================================================================                        
// \title  TestState.hpp                                                                           
// \author ciankc
// \brief  Test state for testing NORFlashDriver
//                                                                                                 
// \copyright                                                                                      
// Copyright (C) 2019 California Institute of Technology.                                          
// ALL RIGHTS RESERVED.  United States Government Sponsorship                                      
// acknowledged.
// ======================================================================   

#ifndef Drv_TestState_HPP
#define Drv_TestState_HPP

#include "fprime-sphinx-drivers/NORFlashDriver/test/ut/Tester.hpp"

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

    bool precondition__Read__ERROR(void) const;
    void action__Read__ERROR(void);

    bool precondition__Write__OK(void) const;
    void action__Write__OK(void);

    bool precondition__Write__ERROR(void) const;
    void action__Write__ERROR(void);

  };

}

#endif
