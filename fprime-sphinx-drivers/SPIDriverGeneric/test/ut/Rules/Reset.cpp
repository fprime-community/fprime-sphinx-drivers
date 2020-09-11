// ====================================================================== 
// \title  Rules/Reset.cpp
// \author ciankc
// \brief  Rules/Reset class implementation
//
// \copyright
// Copyright (C) 2019 California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
// ======================================================================

#include "fprime-sphinx-drivers/Test/Scenario/Test/State.hpp"
#include "fprime-sphinx-drivers/Random/Random.hpp"
#include "Reset.hpp"

namespace Drv {
  // ---------------------------------------------------------------------- 
  // Rule definitions
  // ---------------------------------------------------------------------- 

  bool TestState ::
    precondition__Reset__OK(void) const
  {
    bool result = true;
    //always should be true
    //printf("Precondition for reset OK result is: %d\n", result);
    return result;
  }

  void TestState ::
    action__Reset__OK(void)
  {
    //printf("Action for Reset OK\n");
    // Initialize test state
    this->clearHistory();
    ASSERT_EQ(readRegPartial(SPI_CTRL_MODE_REG, MODE_EN, 1), 1);
  }

  namespace Reset {

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
