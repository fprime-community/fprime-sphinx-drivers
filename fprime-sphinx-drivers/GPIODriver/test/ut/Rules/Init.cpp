// ====================================================================== 
// \title  Rules/Init.cpp
// \author ciankc
// \brief  Rules/Init class implementation
//
// \copyright
// Copyright (C) 2019 California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
// ======================================================================

#include "fprime-sphinx-drivers/Test/Scenario/Test/State.hpp"
#include "fprime-sphinx-drivers/Random/Random.hpp"
#include "Init.hpp"

namespace Drv {
  // ---------------------------------------------------------------------- 
  // Rule definitions
  // ---------------------------------------------------------------------- 

  bool TestState ::
    precondition__Init__OK(void) const
  {
    bool result = true;
    //precondition is always true
    //printf("Precondition for Init OK result is: %d\n", result);
    return result;
  }

  void TestState ::
    action__Init__OK(void)
  {
    //printf("Action for Init OK\n");
    
    NATIVE_UINT_TYPE pin_nums[6] = {1,2,3,4,30,40};
    NATIVE_UINT_TYPE pin_dir[6] = {0,0,0,0,1,1};
    NATIVE_UINT_TYPE pin_int[6] = {1,1,1,1,0,0};
    NATIVE_UINT_TYPE pin_pol[6] = {1,1,0,0,0,0};
    NATIVE_UINT_TYPE pin_edge[6] = {0,1,0,1,0,0};
    GPIOInterruptRouter *int_router = new GPIOInterruptRouter();
    
    this->component.init_comp(pin_nums, 6, pin_dir, 6, pin_int, 6, pin_pol, 6, pin_edge, 6, int_router, 1);
    
    NATIVE_UINT_TYPE i = 0;
    while(i < 5)
    {
      ASSERT_EQ(pin_dir[i], readBit(GPIO_APB_1_ADDR + GPIO_DIR_OFFSET, pin_nums[i]));
      ASSERT_EQ(pin_int[i], readBit(GPIO_APB_1_ADDR + GPIO_INT_MASK_OFFSET, pin_nums[i]));
      ASSERT_EQ(pin_pol[i], readBit(GPIO_APB_1_ADDR + GPIO_INT_POL_OFFSET, pin_nums[i]));
      ASSERT_EQ(pin_edge[i], readBit(GPIO_APB_1_ADDR + GPIO_INT_EDGE_OFFSET, pin_nums[i]));
      i++;
    }

    // check APB2
    ASSERT_EQ(pin_dir[i], readBit(GPIO_APB_2_ADDR + GPIO_DIR_OFFSET, pin_nums[i]-32));
    ASSERT_EQ(pin_int[i], readBit(GPIO_APB_2_ADDR + GPIO_INT_MASK_OFFSET, pin_nums[i]-32));
    ASSERT_EQ(pin_pol[i], readBit(GPIO_APB_2_ADDR + GPIO_INT_POL_OFFSET, pin_nums[i]-32));
    ASSERT_EQ(pin_edge[i], readBit(GPIO_APB_2_ADDR + GPIO_INT_EDGE_OFFSET, pin_nums[i]-32));
    
  }

  bool TestState ::
    precondition__Init__ERROR(void) const
  {
    bool result = true;
    //precondition is always true
    //printf("Precondition for Init ERROR result is: %d\n", result);
    return result;
  }

  void TestState ::
    action__Init__ERROR(void)
  {
    //printf("Action for Init ERROR\n");
    
    NATIVE_UINT_TYPE pin_nums[4] = {1,2,3,4};
    NATIVE_UINT_TYPE pin_dir[4] = {0,1,0,1};
    NATIVE_UINT_TYPE pin_int[4] = {1,1,1,1};
    NATIVE_UINT_TYPE pin_pol[4] = {0,1,0,1};
    NATIVE_UINT_TYPE pin_edge[4] = {0,1,1,0};
    GPIOInterruptRouter *null_router = NULL;
    GPIOInterruptRouter *int_router = new GPIOInterruptRouter();
    
    //trigger linux error, set atomic
    NATIVE_UINT_TYPE valid_pin_dir[4] = {0,0,0,0};
    ASSERT_DEATH({this->component.init_comp(pin_nums, 4, valid_pin_dir, 4, pin_int, 4, pin_pol, 4, pin_edge, 4, int_router);},
                 "Assertion `0' failed.");

    // Null ptr
    ASSERT_DEATH({this->component.init_comp(pin_nums, 4, pin_dir, 4, pin_int, 4, pin_pol, 4, pin_edge, 4, null_router);},
                 "Assertion `0' failed.");
    
    // invalid pin number
    NATIVE_UINT_TYPE invalid_pin_nums[4] = {67, 72, 81, 93};
    ASSERT_DEATH({this->component.init_comp(invalid_pin_nums, 4, pin_dir, 4, pin_int, 4, pin_pol, 4, pin_edge, 4, int_router);},
                 "Assertion `0' failed.");

    // invalid direction
    NATIVE_UINT_TYPE invalid_pin_dir[4] = {2, 0, 3, 1};
    ASSERT_DEATH({this->component.init_comp(pin_nums, 4, invalid_pin_dir, 4, pin_int, 4, pin_pol, 4, pin_edge, 4, int_router);},
                 "Assertion `0' failed.");

    // invalid interrupt
    NATIVE_UINT_TYPE invalid_pin_int[4] = {3, 5, 1, 0};
    ASSERT_DEATH({this->component.init_comp(pin_nums, 4, pin_dir, 4, invalid_pin_int, 4, pin_pol, 4, pin_edge, 4, int_router);},
                 "Assertion `0' failed.");

    // invalid polarity
    NATIVE_UINT_TYPE invalid_pin_pol[4] = {7, 2, 1, 3};
    ASSERT_DEATH({this->component.init_comp(pin_nums, 4, pin_dir, 4, pin_int, 4, invalid_pin_pol, 4, pin_edge, 4, int_router);},
                 "Assertion `0' failed.");

    // invalid edge
    NATIVE_UINT_TYPE invalid_pin_edge[4] = {7, 2, 1, 3};
    ASSERT_DEATH({this->component.init_comp(pin_nums, 4, pin_dir, 4, pin_int, 4, pin_pol, 4, invalid_pin_edge, 4, int_router);},
                 "Assertion `0' failed.");

    
  }
    
  namespace Init {

    // ---------------------------------------------------------------------- 
    // Tests
    // ---------------------------------------------------------------------- 

    void Tester ::
      ERROR(void)
    {
      //apply rule
      this->ruleERROR.apply(this->testState);
    }

    void Tester ::
      OK(void)
    {
      //apply rule
      this->ruleOK.apply(this->testState);
    }

  }

}
