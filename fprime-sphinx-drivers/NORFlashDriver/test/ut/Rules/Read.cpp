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
    //read one byte
    U8 data[1] = {0};

    U32 status = this->invoke_to_read(0, addr, data);
    ASSERT_EQ(status, 1);

  }

  bool TestState ::
    precondition__Read__ERROR(void) const
  {
    bool result = true;
    //precondition is always true
    //printf("Precondition for Read ERROR result is: %d\n", result);
    return result;
  }

  void TestState ::
    action__Read__ERROR(void)
  {
    //printf("Action for Read ERROR\n");

    U32 addr = 0x00000000;
    //read one byte
    U8 data[1] = {0};

    //Check null read ptr
    U8* null_read_buf = NULL;
    ASSERT_DEATH({this->invoke_to_read(0, addr, null_read_buf);},
                 "Assertion");

    //Check invalid address
    U32 invalid_address = 0x20000001;
    U32 status = this->invoke_to_read(0, invalid_address, data);
    ASSERT_EQ(status, 1);

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

    void Tester ::
      ERROR(void)
    {
      //apply rule
      this->ruleERROR.apply(this->testState);
    }

  }

}
