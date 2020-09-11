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

#include "fprime-sphinx-drivers/NORFlashManager/test/ut/Tester.hpp"

namespace Drv {

  class TestState :
    public Tester
  {
    
  public:

    TestState(const char* compName, U32 timeout)
      : Tester(compName, timeout)
    {

    }

    void checkValues(U8* data, U32 mark, U32 mark2, U32 count);

    // ----------------------------------------------------------------------                     
    // Rule definitions                                                                           
    // ---------------------------------------------------------------------- 

    bool precondition__Write__OK(void) const;
    void action__Write__OK(void);

    bool precondition__Write__ERROR(void) const;
    void action__Write__ERROR(void);

    bool precondition__Read__OK(void) const;
    void action__Read__OK(void);

    bool precondition__Read__ERROR(void) const;
    void action__Read__ERROR(void);

    bool precondition__Erase__OK(void) const;
    void action__Erase__OK(void);

    bool precondition__Erase__ERROR(void) const;
    void action__Erase__ERROR(void);

    bool precondition__Size__Block(void) const;
    void action__Size__Block(void);

    bool precondition__Size__FSW(void) const;
    void action__Size__FSW(void);

    bool precondition__Worker__Write(void) const;
    void action__Worker__Write(void);

    bool precondition__Worker__Read(void) const;
    void action__Worker__Read(void);

    bool precondition__Worker__Erase(void) const;
    void action__Worker__Erase(void);

    bool precondition__Worker__Reset(void) const;
    void action__Worker__Reset(void);

    bool precondition__Worker__Verify(void) const;
    void action__Worker__Verify(void);

    bool precondition__Worker__Error(void) const;
    void action__Worker__Error(void);

    bool precondition__Misc__SchedIn(void) const;
    void action__Misc__SchedIn(void);

    bool precondition__Misc__Ping(void) const;
    void action__Misc__Ping(void);

    bool precondition__Misc__Verify(void) const;
    void action__Misc__Verify(void);

    bool precondition__Cmd__Reset(void) const;
    void action__Cmd__Reset(void);

    bool precondition__Cmd__Timeout(void) const;
    void action__Cmd__Timeout(void);

  };

}

#endif
