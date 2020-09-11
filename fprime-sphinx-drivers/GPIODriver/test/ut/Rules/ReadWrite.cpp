// ====================================================================== 
// \title  Rules/ReadWrite.cpp
// \author ciankc
// \brief  Rules/ReadWrite class implementation
//
// \copyright
// Copyright (C) 2019 California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
// ======================================================================

#include "fprime-sphinx-drivers/Test/Scenario/Test/State.hpp"
#include "fprime-sphinx-drivers/Random/Random.hpp"
#include "ReadWrite.hpp"

namespace Drv {
  // ---------------------------------------------------------------------- 
  // Rule definitions
  // ---------------------------------------------------------------------- 

  bool TestState ::
    precondition__ReadWrite__DIRIN(void) const
  {
    bool result = true;
    //precondition is always true
    //printf("Precondition for ReadWrite DIRIN result is: %d\n", result);
    return result;
  }

  void TestState ::
    action__ReadWrite__DIRIN(void)
  {
    //printf("Action for ReadWrite DIRIN\n");

    clearBit(addr1 + GPIO_DIR_OFFSET, pn1);
    clearBit(addr2 + GPIO_DIR_OFFSET, pn2-32);
    
  }


  bool TestState ::
    precondition__ReadWrite__DIROUT(void) const
  {
    bool result = true;
    //precondition is always true
    //printf("Precondition for ReadWrite DIROUT result is: %d\n", result);
    return result;
  }

  void TestState ::
    action__ReadWrite__DIROUT(void)
  {
    //printf("Action for ReadWrite DIROUT\n");

    setBit(addr1 + GPIO_DIR_OFFSET, pn1);
    setBit(addr2 + GPIO_DIR_OFFSET, pn2-32);
  }


  bool TestState ::
    precondition__ReadWrite__READIN(void) const
  {
    bool result = true;
    // both must be inputs 
    result = !(readBit(addr1 + GPIO_DIR_OFFSET, pn1) || readBit(addr2 + GPIO_DIR_OFFSET, pn2-32));
    //printf("Precondition for ReadWrite READIN result is: %d\n", result);
    return result;
  }

  void TestState ::
    action__ReadWrite__READIN(void)
  {
    //printf("Action for ReadWrite READIN\n");

    U32 value = this->invoke_to_gpio_readPin(0, pn1);
    U32 val_check = readBit(addr1 + GPIO_DATA_OFFSET, pn1);
    ASSERT_EQ(value, val_check);
    value = this->invoke_to_gpio_readPin(0, pn2);
    val_check = readBit(addr2 + GPIO_DATA_OFFSET, pn2-32);
    ASSERT_EQ(value, val_check);
   
  }


bool TestState ::
    precondition__ReadWrite__READOUT(void) const
  {
    bool result = true;
    // both must be outputs
    result = readBit(addr1 + GPIO_DIR_OFFSET, pn1) && readBit(addr2 + GPIO_DIR_OFFSET, pn2-32);
    //printf("Precondition for ReadWrite READOUT result is: %d\n", result);
    return result;
  }

  void TestState ::
    action__ReadWrite__READOUT(void)
  {
    //printf("Action for ReadWrite READOUT\n");

    U32 value = this->invoke_to_gpio_readPin(0, pn1);
    U32 val_check = readBit(addr1 + GPIO_OUT_OFFSET, pn1);
    ASSERT_EQ(value, val_check);

    value = this->invoke_to_gpio_readPin(0, pn2);
    val_check = readBit(addr2 + GPIO_OUT_OFFSET, pn2-32);
    ASSERT_EQ(value, val_check);
   
  }

bool TestState ::
    precondition__ReadWrite__SETOUT(void) const
  {
    bool result = true;
    // both must be outputs
    result = readBit(addr1 + GPIO_DIR_OFFSET, pn1) && readBit(addr2 + GPIO_DIR_OFFSET, pn2-32);
    //printf("Precondition for ReadWrite SETOUT result is: %d\n", result);
    return result;
  }


void TestState ::
    action__ReadWrite__SETOUT(void)
  {
    //printf("Action for ReadWrite SETOUT\n");

    U32 status = this->invoke_to_gpio_setPin(0, pn1);
    ASSERT_EQ(status, 0);
    U32 value = readBit(addr1 + GPIO_OUT_OFFSET, pn1);
    ASSERT_EQ(value, 1);

    status = this->invoke_to_gpio_setPin(0, pn2);
    ASSERT_EQ(status, 0);
    value = readBit(addr2 + GPIO_OUT_OFFSET, pn2-32);
    ASSERT_EQ(value, 1);

  }

bool TestState ::
    precondition__ReadWrite__CLEAROUT(void) const
  {
    bool result = true;
    // both must be outputs
    result = readBit(addr1 + GPIO_DIR_OFFSET, pn1) && readBit(addr2 + GPIO_DIR_OFFSET, pn2-32);
    //printf("Precondition for ReadWrite CLEAROUT result is: %d\n", result);
    return result;
  }


void TestState ::
    action__ReadWrite__CLEAROUT(void)
  {
    //printf("Action for ReadWrite CLEAROUT\n");

    U32 status = this->invoke_to_gpio_clearPin(0, pn1);
    ASSERT_EQ(status, 0);
    U32 value = readBit(addr1 + GPIO_OUT_OFFSET, pn1);
    ASSERT_EQ(value, 0);

    status = this->invoke_to_gpio_clearPin(0, pn2);
    ASSERT_EQ(status, 0);
    value = readBit(addr2 + GPIO_OUT_OFFSET, pn2-32);
    ASSERT_EQ(value, 0);

  }

  bool TestState ::
    precondition__ReadWrite__ERROR(void) const
  {
    bool result = true;
    //precondition is always true
    //printf("Precondition for ReadWrite ERROR result is: %d\n", result);
    return result;
  }

  void TestState ::
    action__ReadWrite__ERROR(void)
  {
    //printf("Action for ReadWrite ERROR\n");

    //only 64 pins available
    U32 pin_num = 70;

    ASSERT_DEATH({this->invoke_to_gpio_readPin(0, pin_num);},
                 "Assertion `0' failed.");
    ASSERT_DEATH({this->invoke_to_gpio_setPin(0, pin_num);},
                 "Assertion `0' failed.");
    ASSERT_DEATH({this->invoke_to_gpio_clearPin(0, pin_num);},
                 "Assertion `0' failed.");

  }

  namespace ReadWrite {

    // ---------------------------------------------------------------------- 
    // Tests
    // ---------------------------------------------------------------------- 

    void Tester ::
      DIRIN(void)
    {
      //apply rule
      this->ruleDIRIN.apply(this->testState);
    }

    void Tester ::
      DIROUT(void)
    {
      //apply rule
      this->ruleDIROUT.apply(this->testState);
    }

    void Tester ::
      READIN(void)
    {
      //apply rules
      this->ruleDIRIN.apply(this->testState);
      this->ruleREADIN.apply(this->testState);
    }

    void Tester ::
      READOUT(void)
    {
      //apply rules
      this->ruleDIROUT.apply(this->testState);
      this->ruleREADOUT.apply(this->testState);
    }

    void Tester ::
      SETOUT(void)
    {
      //apply rules
      this->ruleDIROUT.apply(this->testState);
      this->ruleSETOUT.apply(this->testState);
    }

    void Tester ::
      CLEAROUT(void)
    {
      //apply rules
      this->ruleDIROUT.apply(this->testState);
      this->ruleCLEAROUT.apply(this->testState);
    }

    void Tester ::
      ERROR(void)
    {
      //apply rule
      this->ruleERROR.apply(this->testState);
    }

  }

}
