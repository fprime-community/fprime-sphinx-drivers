// ====================================================================== 
// \title  Rules/Write.cpp
// \author ciankc
// \brief  Rules/Write class implementation
//
// \copyright
// Copyright (C) 2019 California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
// ======================================================================

#include "fprime-sphinx-drivers/Test/Scenario/Test/State.hpp"
#include "fprime-sphinx-drivers/Random/Random.hpp"
#include "Write.hpp"

namespace Drv {
  // ---------------------------------------------------------------------- 
  // Rule definitions
  // ---------------------------------------------------------------------- 

  bool TestState ::
    precondition__Write__OK(void) const
  {
    bool result = true;
    //precondition is always true
    //printf("Precondition for Write OK result is: %d\n", result);
    return result;
  }

  void TestState ::
    action__Write__OK(void)
  {
    //printf("Action for Write OK\n");
    
    //base address of NOR flash
    U32 addr = 0x00000000;
    //write one byte of data
    U8 data = 0xCC;

    U32 status = this->invoke_to_write(0, addr, data);
    ASSERT_EQ(status, 1);

  }

  bool TestState ::
    precondition__Write__ERROR(void) const
  {
    bool result = true;
    //precondition is always true
    //printf("Precondition for Write ERROR result is: %d\n", result);
    return result;
  }

  void TestState ::
    action__Write__ERROR(void)
  {
    //printf("Action for Write ERROR\n");
    
    //write one byte of data
    U8 data = 0xCC;
    
    //Check invalid address
    U32 invalid_address = 0x20000001;
    U32 status = this->invoke_to_write(0, invalid_address, data);
    ASSERT_EQ(status, 1);

  }


  namespace Write {

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
