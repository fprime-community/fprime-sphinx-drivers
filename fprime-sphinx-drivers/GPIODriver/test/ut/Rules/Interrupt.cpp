// ====================================================================== 
// \title  Rules/Interrupt.cpp
// \author ciankc
// \brief  Rules/Interrupt class implementation
//
// \copyright
// Copyright (C) 2019 California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
// ======================================================================

#include "fprime-sphinx-drivers/Test/Scenario/Test/State.hpp"
#include "fprime-sphinx-drivers/Random/Random.hpp"
#include "Interrupt.hpp"

namespace Drv {
  // ---------------------------------------------------------------------- 
  // Rule definitions
  // ---------------------------------------------------------------------- 

 bool TestState ::
    precondition__Interrupt__OK(void) const
  {
    bool result = true;
    //precondition is always true
    //printf("Precondition for Interrupt OK result is: %d\n", result);
    return result;
  }

  void TestState ::
    action__Interrupt__OK(void)
  {
    //printf("Action for Interrupt OK\n");

    //init the GPIO router
    NATIVE_UINT_TYPE pin_nums[4] = {1,2,3,4};
    NATIVE_UINT_TYPE pin_dir[4] = {0,0,0,0};
    NATIVE_UINT_TYPE pin_int[4] = {1,1,1,1};
    NATIVE_UINT_TYPE pin_pol[4] = {0,1,0,1};
    NATIVE_UINT_TYPE pin_edge[4] = {0,1,1,0};
    GPIOInterruptRouter* int_router = new GPIOInterruptRouter();

    this->component.init_comp(pin_nums, 4, pin_dir, 4, pin_int, 4, pin_pol, 4, pin_edge, 4, int_router, 1);

    //set correct irq bits
    writeReg(REG_IRQ_GPIO11_BASE + IRQ_GPIO11_STATE_OFFSET, UART6_INT_MASK);

    //register handler
    GPIOInterruptHandler* int_handler = new GPIODriverInterrupt();
    this->component.m_intRouter_p->RegisterHandler(UART6_HANDLER, int_handler);
   
    //only interrupt handler 11 is called
    GPIOintHandler_11((I64)(&(this->component)));
    U32 value = readReg(0x10020000);
    ASSERT_EQ(value, 0xDEADBEEF);

    //call remaining handlers (interrupt not implemented)
    GPIOintHandler_1((I64)(&(this->component)));
    GPIOintHandler_2((I64)(&(this->component)));
    GPIOintHandler_3((I64)(&(this->component)));
    GPIOintHandler_4((I64)(&(this->component)));
    GPIOintHandler_5((I64)(&(this->component)));
    GPIOintHandler_6((I64)(&(this->component)));
    GPIOintHandler_7((I64)(&(this->component)));
    GPIOintHandler_8((I64)(&(this->component)));
    GPIOintHandler_9((I64)(&(this->component)));
    GPIOintHandler_10((I64)(&(this->component)));
    GPIOintHandler_12((I64)(&(this->component)));
    GPIOintHandler_13((I64)(&(this->component)));
    GPIOintHandler_14((I64)(&(this->component)));
    GPIOintHandler_15((I64)(&(this->component)));
  }


  namespace Interrupt {

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
