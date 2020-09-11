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
    // Initialize test state
    this->clearHistory();

    //clear Bit in register to prevent empty register
    writeReg(this->component.m_address + REG_OFF_HW_STATUS, HW_STAT_RCNT);
    
    //write value into rx register
    writeReg(this->component.m_address + REG_OFF_HW_DATA, 0xDEADBEEF);
    
    //set maximum read_buf_rp
    this->component.m_read_buf_rp = 12;

    //Uart interrupt
    UARTHWintHandler((I64)(&(this->component)));
    
    //GPIO interrupt
    this->component.HandleGPIOInterrupt();

    //only pulls the last byte in register
    ASSERT_EQ(this->component.m_read_buf[this->component.m_read_buf_wp - 1], 0xEF);

    //asserts once when rp and wp both equal 0
    ASSERT_EVENTS_UOBD_BUFF_WRAP_SIZE(1);

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
