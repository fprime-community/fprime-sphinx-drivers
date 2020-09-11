// ====================================================================== 
// \title  Rules/Erase.cpp
// \author ciankc
// \brief  Rules/Erase class implementation
//
// \copyright
// Copyright (C) 2019 California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
// ======================================================================

#include "fprime-sphinx-drivers/Test/Scenario/Test/State.hpp"
#include "fprime-sphinx-drivers/Random/Random.hpp"
#include "Erase.hpp"

namespace Drv {
  // ---------------------------------------------------------------------- 
  // Rule definitions
  // ---------------------------------------------------------------------- 

  bool TestState ::
    precondition__Erase__OK(void) const
  {
    bool result = true;
    //precondition is always true
    //printf("Precondition for Erase OK result is: %d\n", result);
    return result;
  }

  void TestState ::
    action__Erase__OK(void)
  {
    //printf("Action for Erase OK\n");

    this->clearHistory();
    
    writeReg(0x0, 0xFFFFFFFF);
    
    U32 reg1 = 0x555;
    U32 reg2 = 0xAAA;
    U32 diff1 = reg1 % 0x4;
    U32 diff2 = reg2 % 0x4;
    U32 n_reg1 = reg1 - diff1;
    U32 n_reg2 = reg2 - diff2;
    
    writeReg(n_reg1, 0x0);
    writeReg(n_reg2, 0x0);

    //invoke erase
    this->invoke_to_erase(0, 0);
    this->component.doDispatch();
    
    U32 shift1 = 0x55 << ((3-diff1)*8);
    U32 shift2 = (0x10 | 0xAA | 0x80) << ((3-diff2)*8);
    
    //check that erase sequence was written
    ASSERT_EQ(readReg(n_reg1), shift1);
    ASSERT_EQ(readReg(n_reg2), shift2);
    
  }

  namespace Erase {

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
