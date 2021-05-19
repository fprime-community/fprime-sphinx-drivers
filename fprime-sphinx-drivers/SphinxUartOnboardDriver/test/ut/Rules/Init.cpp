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
    // Initialize test state
    this->clearHistory();

    for(I32 i = 0; i < 4; i++)
    {
      for(I32 j = 0; j < 8; j++)
      {
	this->component.init_comp(fw[i], br[j], 100);
          ASSERT_EQ(this->component.m_address, rp[fw[i]]);
          ASSERT_EQ(this->component.m_registerType, 2); //2 = RegisterType_FIRMWARE
          ASSERT_EQ(readReg(this->component.m_address + REG_OFF_FW_BAUD_RATE), bm[j]);
      }
    }

    //init hw ports
    this->component.init_comp(0, 9600, 100, 1);
    ASSERT_EQ(this->component.m_address, REG_PORT_0);
    ASSERT_EQ(this->component.m_registerType, 1); //1 = RegisterType_HARDWARE
    U32 scaler = (100 * MEGA_FACTOR) / (9600 * 8) - 1;
    ASSERT_EQ(readReg(this->component.m_address + REG_OFF_HW_SCALER), scaler);


    this->component.init_comp(1, 9600, 100, 1);
    ASSERT_EQ(this->component.m_address, REG_PORT_1);
    ASSERT_EQ(this->component.m_registerType, 1); //1 = RegisterType_HARDWARE
    scaler = (100 * MEGA_FACTOR) / (9600 * 8) - 1;
    ASSERT_EQ(readReg(this->component.m_address + REG_OFF_HW_SCALER), scaler);


    //invalid port number
    ASSERT_DEATH({this->component.init_comp(9, 9600, 100, 1);},
	         "Assertion");

    //invalud baud rate
    ASSERT_DEATH({this->component.init_comp(1, 1000, 100, 1);},
                   "Assertion");

  }

  bool TestState ::
    precondition__Init__HWOK(void) const
  {
    bool result = true;
    //precondition is always true
    //printf("Precondition for Init FW OK result is: %d\n", result);
    return result;
  }


  void TestState ::
    action__Init__HWOK(void)
  {
    //printf("Action for Init FW OK\n");
    // Initialize test state
    this->clearHistory();

    this->component.init_comp(4, 9600, 100, 1);
    ASSERT_EQ(this->component.m_address, REG_PORT_4);
    ASSERT_EQ(this->component.m_registerType, 1); //1 = RegisterType_HARDWARE
    U32 scaler = (100 * MEGA_FACTOR) / (9600 * 8) - 1;
    ASSERT_EQ(readReg(this->component.m_address + REG_OFF_HW_SCALER), scaler);

    this->component.init_comp(5, 9600, 100, 1);
    ASSERT_EQ(this->component.m_address, REG_PORT_5);
    ASSERT_EQ(this->component.m_registerType, 1); //1 = RegisterType_HARDWARE
    scaler = (100 * MEGA_FACTOR) / (9600 * 8) - 1;
    ASSERT_EQ(readReg(this->component.m_address + REG_OFF_HW_SCALER), scaler);
  }

  namespace Init {

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
      HWOK(void)
    {
      //apply rule
      this->ruleHWOK.apply(this->testState);
    }

  }

}
