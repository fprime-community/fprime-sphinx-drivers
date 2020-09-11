// ======================================================================                        
// \title  TestState.hpp                                                                           
// \author AUTO-GENERATED: DO NOT EDIT                                                             
// \brief  Test state for testing Imager                                                           
//                                                                                                 
// \copyright                                                                                      
// Copyright (C) 2019 California Institute of Technology.                                          
// ALL RIGHTS RESERVED.  United States Government Sponsorship                                      
// acknowledged.
// ======================================================================   

#ifndef Drv_TestState_HPP
#define Drv_TestState_HPP

#include "fprime-sphinx-drivers/SPIDriverGeneric/test/ut/Tester.hpp"

namespace Drv {

  class TestState :
    public Tester
  {
    
  public:

    // ----------------------------------------------------------------------                     
    // Rule definitions                                                                           
    // ---------------------------------------------------------------------- 

    bool precondition__Claim__OK(void) const;
    void action__Claim__OK(void);

    bool precondition__Claim__Double(void) const;
    void action__Claim__Double(void);

    bool precondition__Unclaim__OK(void) const;
    void action__Unclaim__OK(void);

    bool precondition__Unclaim__Double(void) const;
    void action__Unclaim__Double(void);

    bool precondition__RWOwner__SUCCESS8(void) const;
    void action__RWOwner__SUCCESS8(void);

    bool precondition__RWOwner__SUCCESS16(void) const;
    void action__RWOwner__SUCCESS16(void);

    bool precondition__RWOwner__SUCCESS32(void) const;
    void action__RWOwner__SUCCESS32(void);

    bool precondition__RWOwner__TIMEOUT(void) const;
    void action__RWOwner__TIMEOUT(void);

    bool precondition__RWOwner__ERROR(void) const;
    void action__RWOwner__ERROR(void);
    
    bool precondition__Pointer__Invalid(void) const;
    void action__Pointer__Invalid(void);
  
    bool precondition__Reset__OK(void) const;
    void action__Reset__OK(void);

    bool precondition__RWReverse__SUCCESS8(void) const;
    void action__RWReverse__SUCCESS8(void);

    bool precondition__RWReverse__SUCCESS16(void) const;
    void action__RWReverse__SUCCESS16(void);

    bool precondition__RWReverse__SUCCESS32(void) const;
    void action__RWReverse__SUCCESS32(void);
    
  };

}

#endif
