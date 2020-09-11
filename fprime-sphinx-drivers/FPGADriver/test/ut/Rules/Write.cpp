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
    U32 data = 0xCC;

    U32 status = this->invoke_to_write_reg(0, addr, data);
    ASSERT_EQ(status, 0);
    ASSERT_EQ(data, readReg(addr));
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

  }

}
