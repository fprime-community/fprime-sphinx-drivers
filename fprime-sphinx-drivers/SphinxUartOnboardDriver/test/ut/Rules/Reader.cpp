// ====================================================================== 
// \title  Rules/Reader.cpp
// \author ciankc
// \brief  Rules/Reader class implementation
//
// \copyright
// Copyright (C) 2019 California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
// ======================================================================

#include "fprime-sphinx-drivers/Test/Scenario/Test/State.hpp"
#include "fprime-sphinx-drivers/Random/Random.hpp"
#include "Reader.hpp"

namespace Drv {
  // ---------------------------------------------------------------------- 
  // Rule definitions
  // ---------------------------------------------------------------------- 

  bool TestState ::
    precondition__Reader__TIMEOUT(void) const
  {
    bool result = true;
    //precondition is always true
    //printf("Precondition for Reader TIMEOUT result is: %d\n", result);
    return result;
  }

  void TestState ::
    action__Reader__TIMEOUT(void)
  {
    //printf("Action for Reader TIMEOUT\n");
    // Initialize test state
    this->clearHistory();

    U32 status;
    U8 data[5] = {1};
    //set timeout value to zero
    status = this->invoke_to_read(0, data, 1, 0);
    ASSERT_TRUE(status & (0x1 << 2)); //IOErrorBit_TIMEOUT enum

  }

 bool TestState ::
    precondition__Reader__OK(void) const
  {
    bool result = true;
    //precondition is always true
    //printf("Precondition for Reader OK result is: %d\n", result);
    return result;
  }

  void TestState ::
    action__Reader__OK(void)
  {
    //printf("Action for Reader OK\n");
    // Initialize test state
    this->clearHistory();

    U32 status;
    U8 data[5];
    //set read location of m_read_buf to nonzero value
    this->component.m_read_buf_rp = 1;
    status = this->invoke_to_read(0, data, 5, 100);
    ASSERT_EQ(status, 0);

  }

  bool TestState ::
    precondition__Reader__FWOK(void) const
  {
    bool result = true;
    //precondition is always true
    //printf("Precondition for Reader FW OK result is: %d\n", result);
    return result;
  }

  void TestState ::
    action__Reader__FWOK(void)
  {
    //printf("Action for Reader FW OK\n");
    // Initialize test state
    this->clearHistory();

    U32 status;
    U8 data[5];

    //init fw
    this->component.init_comp(2, 9600, 100, 1);
    ASSERT_EQ(this->component.m_address, REG_PORT_2);
    ASSERT_EQ(this->component.m_registerType, 2); //2 = RegisterType_FIRMWARE
    ASSERT_EQ(readReg(this->component.m_address + REG_OFF_FW_BAUD_RATE), 0x2);
    
    //read fw
    this->component.m_read_buf_rp = 1;
    writeReg(this->component.m_address + REG_OFF_FW_STATUS, 0);
    status = this->invoke_to_read(0, data, 5, 100);
    ASSERT_EQ(status, 0);
  }


  bool TestState ::
    precondition__Reader__NBYTES(void) const
  {
    bool result = true;
    //precondition is always true
    //printf("Precondition for Reader NBYTES result is: %d\n", result);
    return result;
  }

  void TestState ::
    action__Reader__NBYTES(void)
  {
    //printf("Action for Reader NBYTES\n");
    // Initialize test state
    this->clearHistory();

    U32 status;
    U8 data[5] = {1,2,3,4,5};
    //nbytes to read is 0
    status = this->invoke_to_read(0, data, 0, 100);
    //should return normally
    ASSERT_EQ(status, 0);

    //circular buffer should be reset to zero
    U32 bytes = this->invoke_to_bytesUsed(0);
    ASSERT_TRUE(bytes == 0);

  }

  bool TestState ::
    precondition__Reader__NULLPTR(void) const
  {
    bool result = true;
    //precondition is always true
    //printf("Precondition for Reader NULLPTR result is: %d\n", result);
    return result;
  }

  void TestState ::
    action__Reader__NULLPTR(void)
  {
    //printf("Action for Reader NULLPTR\n");
    // Initialize test state
    this->clearHistory();

    U8* data = NULL;
    ASSERT_DEATH({this->invoke_to_read(0, data, 1, 100);},
                 "Assertion `0' failed.");

  }

  bool TestState ::
    precondition__Reader__DATA(void) const
  {
    bool result = true;
    //precondition is always true
    //printf("Precondition for Reader DATA result is: %d\n", result);
    return result;
  }

  void TestState ::
    action__Reader__DATA(void)
  {
    //printf("Action for Reader DATA\n");
    // Initialize test state
    this->clearHistory();

    bool result = this->component.is_data_ready();
    ASSERT_EQ(result, false);
  }

  bool TestState ::
    precondition__Reader__EMPTY(void) const
  {
    bool result = true;
    //precondition is always true
    //printf("Precondition for Reader EMPTY result is: %d\n", result);
    return result;
  }

  void TestState ::
    action__Reader__EMPTY(void)
  {
    //printf("Action for Reader EMPTY\n");
    // Initialize test state
    this->clearHistory();

    U8 data[5] = {1,2,3,4,5};
    U32 status;
    
    writeReg(this->component.m_address + REG_OFF_HW_STATUS, HW_STAT_RCNT);
    status = this->invoke_to_read(0, data, 5, 100);
    ASSERT_EQ(status, 0);
  }


  bool TestState ::
    precondition__Reader__ERROR(void) const
  {
    bool result = true;
    //precondition is always true
    //printf("Precondition for Reader ERROR result is: %d\n", result);
    return result;
  }

  void TestState ::
    action__Reader__ERROR(void)
  {
    //printf("Action for Reader ERROR\n");
    // Initialize test state
    this->clearHistory();
    
    U8 data[5] = {1,2,3,4,5};
    U32 status;

    //prevent infinite loop
    this->component.m_read_buf_rp = 1;

    //overrun
    writeReg(this->component.m_address + REG_OFF_HW_STATUS, (0x1 << 4));
    status = this->invoke_to_read(0, data, 5, 100);
    ASSERT_TRUE(status & (0x1 << 3));

    //parity error
    writeReg(this->component.m_address + REG_OFF_HW_STATUS, (0x1 << 5));
    status = this->invoke_to_read(0, data, 5, 100);
    ASSERT_TRUE(status & (0x1 << 0));

    //framing error
    writeReg(this->component.m_address + REG_OFF_HW_STATUS, (0x1 << 6));
    status = this->invoke_to_read(0, data, 5, 100);
    ASSERT_TRUE(status & (0x1 << 1));

  }


  namespace Reader {

    // ---------------------------------------------------------------------- 
    // Tests
    // ---------------------------------------------------------------------- 

    void Tester ::
      TIMEOUT(void)
    {
      //apply rule
      this->ruleTIMEOUT.apply(this->testState);
    }

    void Tester ::
      OK(void)
    {
      //apply rule
      this->ruleOK.apply(this->testState);
    }

    void Tester ::
      FWOK(void)
    {
      //apply rule
      this->ruleFWOK.apply(this->testState);
    }



    void Tester ::
      NBYTES(void)
    {
      //apply rule
      this->ruleNBYTES.apply(this->testState);
    }

    void Tester ::
      EMPTY(void)
    {
      //apply rule
      this->ruleEMPTY.apply(this->testState);
    }


    void Tester ::
      DATA(void)
    {
      //apply rule
      this->ruleDATA.apply(this->testState);
    }

    void Tester ::
      ERROR(void)
    {
      //apply rule
      this->ruleERROR.apply(this->testState);
    }

    void Tester ::
      NULLPTR(void)
    {
      //apply rule
      this->ruleNULLPTR.apply(this->testState);
    }

  }

}
