// ======================================================================
// \title  Rules/Pointer.cpp
// \author ciankc
// \brief  Rules/Pointer class implementation
//
// \copyright
// Copyright (C) 2019 California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
// ======================================================================

#include "fprime-sphinx-drivers/Test/Scenario/Test/State.hpp"
#include "fprime-sphinx-drivers/Random/Random.hpp"
#include "Pointer.hpp"

namespace Drv {
  // ----------------------------------------------------------------------
  // Rule definitions
  // ----------------------------------------------------------------------

  bool TestState ::
    precondition__Pointer__Invalid(void) const
  {
    bool result = true;
    result &= this->component.m_isOwned;
    //    printf("Precondition for pointer invalid result is: %d\n", result);
    return result;
  }

 void TestState ::
    action__Pointer__Invalid(void)
  {
    // printf("Action for Pointer Invalid\n");
    // Initialize test state
    this->clearHistory();

    //Null ptr passed to spi_rw
    U8* data_8 = NULL;
    ASSERT_DEATH({this->invoke_to_read_write_8(0, data_8, data_8, 5, 10000);},
		 "Assertion");

    //Null ptr passed to spi_rw
    U16* data_16 = NULL;
    ASSERT_DEATH({this->invoke_to_read_write_16(0, data_16, data_16, 5, 10000);},
                 "Assertion");

    //Null ptr passed to spi_rw
    U32* data_32 = NULL;
    ASSERT_DEATH({this->invoke_to_read_write_32(0, data_32, data_32, 5, 10000);},
                 "Assertion");
  }

  namespace Pointer {

    // ----------------------------------------------------------------------
    // Tests
    // ----------------------------------------------------------------------

    void Tester ::
      Invalid(void)
    {
      //apply rule
      this->mutexTester.ruleClaimOK.apply(this->testState);
      this->ruleInvalid.apply(this->testState);
    }

  }

}
