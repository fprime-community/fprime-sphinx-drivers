// ======================================================================                        
// \title  TestState.hpp                                                                           
// \author ciankc
// \brief  Test state for testing NORFlashMgrWorker
//                                                                                                 
// \copyright                                                                                      
// Copyright (C) 2019 California Institute of Technology.                                          
// ALL RIGHTS RESERVED.  United States Government Sponsorship                                      
// acknowledged.
// ======================================================================   

#ifndef Drv_TestState_HPP
#define Drv_TestState_HPP

#include "fprime-sphinx-drivers/NORFlashMgrWorker/test/ut/Tester.hpp"

namespace Drv {

  class TestState :
    public Tester
  {
    
  public:
    
    void checkValues(U8* data, U32 mark, U32 mark2, U32 count);

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

    bool precondition__Erase__OK(void) const;
    void action__Erase__OK(void);

    bool precondition__Misc__Cancel(void) const;
    void action__Misc__Cancel(void);

    bool precondition__Misc__Reset(void) const;
    void action__Misc__Reset(void);

    bool precondition__Misc__Verify(void) const;
    void action__Misc__Verify(void);

  };

}

#endif
