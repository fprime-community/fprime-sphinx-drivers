// ====================================================================== 
// \title  Rules/Size.cpp
// \author ciankc
// \brief  Rules/Size class implementation
//
// \copyright
// Copyright (C) 2019 California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
// ======================================================================

#include "fprime-sphinx-drivers/Test/Scenario/Test/State.hpp"
#include "fprime-sphinx-drivers/Random/Random.hpp"
#include "Size.hpp"

namespace Drv {
  // ---------------------------------------------------------------------- 
  // Rule definitions
  // ---------------------------------------------------------------------- 

  bool TestState ::
    precondition__Size__Block(void) const
  {
    bool result = true;
    //precondition is always true
    //printf("Precondition for Size OK result is: %d\n", result);
    return result;
  }

  void TestState ::
    action__Size__Block(void)
  {
    //printf("Action for Size OK\n");
    
    U32 size = 0xCC;
    
    U32 status = this->invoke_to_get_bl_size(0, size);

    ASSERT_EQ(status, NORMGR_OK);
    ASSERT_EQ(0, size);
  }

  bool TestState ::
    precondition__Size__FSW(void) const
  {
    bool result = true;
    //precondition is always true
    //printf("Precondition for Size ERROR result is: %d\n", result);
    return result;
  }

  void TestState ::
    action__Size__FSW(void)
  {
    //printf("Action for Size ERROR\n");
    
    U32 size = 0xCC;

    U32 status = this->invoke_to_get_fsw_size(0, size);

    ASSERT_EQ(status, NORMGR_OK);
    ASSERT_EQ(0, size);
  }


  namespace Size {

    // ---------------------------------------------------------------------- 
    // Tests
    // ----------------------------------------------------------------------     

    Tester :: Tester(const char* compName, U32 timeout) 
      : testState(compName, timeout)
    {

    }

    void Tester ::
      Block(void)
    {
      //apply rule
      this->ruleBlock.apply(this->testState);
    }    

    void Tester ::
      FSW(void)
    {
      //apply rule
      this->ruleFSW.apply(this->testState);
    }

  }

}
