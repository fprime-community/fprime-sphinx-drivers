// ====================================================================== 
// \title  Rules/BytesUsed.cpp
// \author ciankc
// \brief  Rules/BytesUsed class implementation
//
// \copyright
// Copyright (C) 2019 California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
// ======================================================================

#include "fprime-sphinx-drivers/Test/Scenario/Test/State.hpp"
#include "fprime-sphinx-drivers/Random/Random.hpp"
#include "BytesUsed.hpp"

namespace Drv {
  // ---------------------------------------------------------------------- 
  // Rule definitions
  // ---------------------------------------------------------------------- 

  bool TestState ::
    precondition__BytesUsed__OK(void) const
  {
    bool result = true;
    //precondition is always true
    //printf("Precondition for BytesUsed OK result is: %d\n", result);
    return result;
  }

  void TestState ::
    action__BytesUsed__OK(void)
  {
    //printf("Action for BytesUsed OK\n");
    // Initialize test state
    this->clearHistory();
    U32 bytes;

    bytes = this->invoke_to_bytesUsed(0);
    ASSERT_TRUE(bytes >= 0);
 
  }

  namespace BytesUsed {

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
