// ====================================================================== 
// \title  Rules/Time.cpp
// \author ciankc
// \brief  Rules/Time class implementation
//
// \copyright
// Copyright (C) 2019 California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
// ======================================================================

#include "fprime-sphinx-drivers/Test/Scenario/Test/State.hpp"
#include "Time.hpp"

namespace Drv {
  // ---------------------------------------------------------------------- 
  // Rule definitions
  // ---------------------------------------------------------------------- 

  bool TestState ::
    precondition__Time__OK(void) const
  {
    bool result = true;
    //precondition is always true
    //printf("Precondition for Time OK result is: %d\n", result);
    return result;
  }

  void TestState ::
    action__Time__OK(void)
  {
    //printf("Action for Time OK\n");

    U32 status = this->component.sphinx_time_go();
    ASSERT_EQ(status, 0);  
    
    FPGADriverComponentImpl* addr = &(this->component);
    //call time rti handler with valid pointer to component
    //do this 10 times to trigger timeRTIOut port call
    for(U32 i = 0; i < 10; i++)
    {
        this->component.sphinx_time_rti_handlr((I64)addr);
    }
   
  }
 
  bool TestState ::
    precondition__Time__ERROR(void) const
  {
    bool result = true;
    //precondition is always true
    //printf("Precondition for Time ERROR result is: %d\n", result);
    return result;
  }

  void TestState ::
    action__Time__ERROR(void)
  {
    //printf("Action for Time ERROR\n");

    U64 addr = 0x00000000;
 
    //call rti handler with invalid arg 
    ASSERT_DEATH({this->component.sphinx_time_rti_handlr(addr);},
      "Assertion `0' failed.");
  }

  namespace Time {

    // ---------------------------------------------------------------------- 
    // Tests
    // ----------------------------------------------------------------------     
    
    void Tester ::
      OK(void)
    {
      //apply rule
      this->ruleOK.apply(this->testState);
    }

    void Tester ::
      ERROR(void)
    {
      //apply rule
      this->ruleERROR.apply(this->testState);
    }
        
  }

}
