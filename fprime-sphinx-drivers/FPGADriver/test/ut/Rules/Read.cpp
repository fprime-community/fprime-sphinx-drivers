// ====================================================================== 
// \title  Rules/Read.cpp
// \author ciankc
// \brief  Rules/Read class implementation
//
// \copyright
// Copyright (C) 2019 California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
// ======================================================================

#include "fprime-sphinx-drivers/Test/Scenario/Test/State.hpp"
#include "Read.hpp"

namespace Drv {
  // ---------------------------------------------------------------------- 
  // Rule definitions
  // ---------------------------------------------------------------------- 

  bool TestState ::
    precondition__Read__OK(void) const
  {
    bool result = true;
    //precondition is always true
    //printf("Precondition for Read OK result is: %d\n", result);
    return result;
  }

  void TestState ::
    action__Read__OK(void)
  {
    //printf("Action for Read OK\n");

    U32 addr = 0x00000000;
    //value to read into
    U32 data = 0x00;

    //write known value to address
    writeReg(addr, 0xCC);

    //read value from address into data and check
    U32 status = this->invoke_to_read_reg(0, addr, data);
    ASSERT_EQ(status, 0);
    ASSERT_EQ(data,  0xCC);
  }

  namespace Read {

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
