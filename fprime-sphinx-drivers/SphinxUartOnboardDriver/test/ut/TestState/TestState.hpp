// ======================================================================                        
// \title  TestState.hpp                                                                           
// \author AUTO-GENERATED: DO NOT EDIT                                                             
// \brief  Test state for testing SphinxUartOnboardDriver
//                                                                                                 
// \copyright                                                                                      
// Copyright (C) 2019 California Institute of Technology.                                          
// ALL RIGHTS RESERVED.  United States Government Sponsorship                                      
// acknowledged.
// ======================================================================   

#ifndef Drv_TestState_HPP
#define Drv_TestState_HPP

#include "fprime-sphinx-drivers/SphinxUartOnboardDriver/test/ut/Tester.hpp"

namespace Drv {

  class TestState :
    public Tester
  {
    
  public:

    // ----------------------------------------------------------------------                     
    // Rule definitions                                                                           
    // ---------------------------------------------------------------------- 

    bool precondition__BytesUsed__OK(void) const;
    void action__BytesUsed__OK(void);

    bool precondition__Init__OK(void) const;
    void action__Init__OK(void);

    bool precondition__Init__HWOK(void) const;
    void action__Init__HWOK(void);

    bool precondition__Reader__ERROR(void) const;
    void action__Reader__ERROR(void);

    bool precondition__Writer__TIMEOUT(void) const;
    void action__Writer__TIMEOUT(void);

    bool precondition__Writer__OK(void) const;
    void action__Writer__OK(void);

    bool precondition__Writer__NBYTES(void) const;
    void action__Writer__NBYTES(void);

    bool precondition__Writer__NULLPTR(void) const;
    void action__Writer__NULLPTR(void);

    bool precondition__Reader__TIMEOUT(void) const;
    void action__Reader__TIMEOUT(void);

    bool precondition__Reader__OK(void) const;
    void action__Reader__OK(void);

    bool precondition__Reader__NBYTES(void) const;
    void action__Reader__NBYTES(void);

    bool precondition__Reader__NULLPTR(void) const;
    void action__Reader__NULLPTR(void);

    bool precondition__Reader__DATA(void) const;
    void action__Reader__DATA(void);    

    bool precondition__Reader__EMPTY(void) const;
    void action__Reader__EMPTY(void);    

    bool precondition__Reader__FWOK(void) const;
    void action__Reader__FWOK(void);    

    bool precondition__Interrupt__OK(void) const;
    void action__Interrupt__OK(void);

  };

}

#endif
