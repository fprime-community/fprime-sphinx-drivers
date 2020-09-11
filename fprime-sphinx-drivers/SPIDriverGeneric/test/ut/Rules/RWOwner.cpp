// ====================================================================== 
// \title  Rules/RWOwner.cpp
// \author ciankc
// \brief  Rules/RWOwner class implementation
//
// \copyright
// Copyright (C) 2019 California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
// ======================================================================

#include "fprime-sphinx-drivers/Test/Scenario/Test/State.hpp"
#include "fprime-sphinx-drivers/Random/Random.hpp"
#include "RWOwner.hpp"

namespace Drv {
  // ---------------------------------------------------------------------- 
  // Rule definitions
  // ---------------------------------------------------------------------- 

  bool TestState ::
    precondition__RWOwner__ERROR(void) const
  {
    bool result = true;
    result &= !(this->component.m_isOwned);
    //printf("Precondition RWOwner Error result is: %d\n", result);
    return result;
  }


  void TestState ::
    action__RWOwner__ERROR(void)
  {
    //printf("Action for RWOwner ERROR\n");
    // Initialize test state
    this->clearHistory();

    I32 status;

    U8 data_8[5] = {1,2,3,4,5};
    
    //read/write 8 bit spi word without claiming
    status = this->invoke_to_read_write_8(0, data_8, data_8, 5, 10000);
    ASSERT_EQ(status, SPI_RW_NOT_OWNER_ERR);
    ASSERT_EQ(this->component.m_isOwned, false);

    U16 data_16[5] = {1,2,3,4,5};

    //read/write 16 bit spi word without claiming
    status = this->invoke_to_read_write_16(0, data_16, data_16, 5, 10000);
    ASSERT_EQ(status, SPI_RW_NOT_OWNER_ERR);
    ASSERT_EQ(this->component.m_isOwned, false);

    U32 data_32[5] = {1,2,3,4,5};

    //read/write 32 bit spi word without claiming
    status = this->invoke_to_read_write_32(0, data_32, data_32, 5, 10000);
    ASSERT_EQ(status, SPI_RW_NOT_OWNER_ERR);
    ASSERT_EQ(this->component.m_isOwned, false);
  }


  bool TestState ::
    precondition__RWOwner__SUCCESS8(void) const
  {
    bool result = true;
    result &= this->component.m_isOwned;
    //printf("Precondition for RWOwner SUCCESS8 result is: %d\n", result);
    return result;
  }


  void TestState ::
    action__RWOwner__SUCCESS8(void)
  {
    //printf("Action for RWOwner SUCCESS8\n");
    // Initialize test state
    this->clearHistory();

    I32 status;

    status = this->invoke_to_spi_configure((NATIVE_INT_TYPE) 0, //portNum
				  (U8) 0, //loopback_mode
				  (U8) 0, //clock_polarity
				  (U8) 0, //clock_phase
				  (U8) 0, //div_clock_16
				  (U8) 1, //reverse_mode
				  (U8) 8, //word_len
				  (U8) 12, //prescale modulus
				  (U8) 0,  //prescale modulus factor
				  (U8) 0); //clock_gap
    ASSERT_EQ(status, 0);
    
    setBit(SPI_CTRL_EVT_REG, EVENT_NF);
    setBit(SPI_CTRL_EVT_REG, EVENT_NE);
    clearBit(SPI_CTRL_EVT_REG, EVENT_TIP);
    clearBit(SPI_CTRL_EVT_REG, EVENT_OV);

    U8 data_8[5] = {1,2,3,4,5};

    //read/write 8 bit spi word with claiming
    status = this->invoke_to_read_write_8(0, data_8, data_8, 5, 10000);
    ASSERT_EQ(status, 0);
    ASSERT_EQ(this->component.m_isOwned, true);
    
    U16 data_16[5] = {1,2,3,4,5};

    //read/write 16 bit spi word with claiming, should fail since the word length is incorrect
    ASSERT_DEATH({this->invoke_to_read_write_16(0, data_16, data_16, 5, 10000);},
                 "Assertion `0' failed.");
    ASSERT_EQ(this->component.m_isOwned, true);
    
    U32 data_32[5] = {1,2,3,4,5};

    //read/write 32 bit spi word with claiming, should fail since the word length is incorrect
    ASSERT_DEATH({this->invoke_to_read_write_32(0, data_32, data_32, 5, 10000);},
                 "Assertion `0' failed.");
    ASSERT_EQ(this->component.m_isOwned, true);
  }

  bool TestState ::
    precondition__RWOwner__TIMEOUT(void) const
  {
    bool result = true;
    result &= this->component.m_isOwned;
    //printf("Precondition for RWOwner SUCCESS8 result is: %d\n", result);
    return result;
  }


  void TestState ::
    action__RWOwner__TIMEOUT(void)
  {
    //printf("Action for RWOwner SUCCESS8\n");
    // Initialize test state
    this->clearHistory();

    I32 status;

    status = this->invoke_to_spi_configure((NATIVE_INT_TYPE) 0, //portNum
				  (U8) 0, //loopback_mode
				  (U8) 0, //clock_polarity
				  (U8) 0, //clock_phase
				  (U8) 0, //div_clock_16
				  (U8) 1, //reverse_mode
				  (U8) 8, //word_len
				  (U8) 12, //prescale modulus
				  (U8) 0,  //prescale modulus factor
				  (U8) 0); //clock_gap
    ASSERT_EQ(status, 0);
    
    setBit(SPI_CTRL_EVT_REG, EVENT_NF);
    setBit(SPI_CTRL_EVT_REG, EVENT_NE);
    clearBit(SPI_CTRL_EVT_REG, EVENT_TIP);
    clearBit(SPI_CTRL_EVT_REG, EVENT_OV);

    U8 data_8[5] = {1,2,3,4,5};

    clearBit(SPI_CTRL_EVT_REG, EVENT_NF);
    status = this->invoke_to_read_write_8(0, data_8, data_8, 5, 10000);
    ASSERT_EQ(status, -103);
    setBit(SPI_CTRL_EVT_REG, EVENT_NF);
    
    setBit(SPI_CTRL_EVT_REG, EVENT_OV);
    status = this->invoke_to_read_write_8(0, data_8, data_8, 5, 10000);
    ASSERT_EQ(status, -102);
    clearBit(SPI_CTRL_EVT_REG, EVENT_OV);

    setBit(SPI_CTRL_EVT_REG, EVENT_TIP);  
    ASSERT_DEATH({this->invoke_to_read_write_8(0, data_8, data_8, 5, 10000);},
		 "Assertion `0' failed.");
    clearBit(SPI_CTRL_EVT_REG, EVENT_TIP); 

    clearBit(SPI_CTRL_EVT_REG, EVENT_NE); 
    ASSERT_DEATH({this->invoke_to_read_write_8(0, data_8, data_8, 5, 10000);},
                 "Assertion `0' failed.");
    setBit(SPI_CTRL_EVT_REG, EVENT_NE); 

    ASSERT_EQ(this->component.m_isOwned, true);
  }


  bool TestState ::
    precondition__RWOwner__SUCCESS16(void) const
  {
    bool result = true;
    result &= this->component.m_isOwned;
    //printf("Precondition for RWOwner SUCCESS16 result is: %d\n", result);
    return result;
  }


  void TestState ::
    action__RWOwner__SUCCESS16(void)
  {
    //printf("Action for RWOwner SUCCESS16\n");
    // Initialize test state
    this->clearHistory();
    
    I32 status;

    status = this->invoke_to_spi_configure((NATIVE_INT_TYPE) 0, //portNum
				  (U8) 0, //loopback_mode
				  (U8) 0, //clock_polarity
				  (U8) 0, //clock_phase
				  (U8) 0, //div_clock_16
				  (U8) 1, //reverse_mode
				  (U8) 16, //word_len
				  (U8) 12, //prescale modulus
				  (U8) 0,  //prescale modulus factor
				  (U8) 0); //clock_gap
    ASSERT_EQ(status, 0);

    clearBit(SPI_CTRL_EVT_REG, EVENT_OV);

    U16 data_16[5] = {1,2,3,4,5};

    //read/write 16 bit spi word with claiming
    status = this->invoke_to_read_write_16(0, data_16, data_16, 5, 10000);
    ASSERT_EQ(status, 0);
    ASSERT_EQ(this->component.m_isOwned, true);
    
    U8 data_8[5] = {1,2,3,4,5};

    //read/write 8 bit spi word with claiming, should fail since the word length is incorrect
    ASSERT_DEATH({this->invoke_to_read_write_8(0, data_8, data_8, 5, 10000);},
                 "Assertion `0' failed.");
    ASSERT_EQ(this->component.m_isOwned, true);
    
    U32 data_32[5] = {1,2,3,4,5};

    //read/write 32 bit spi word with claiming, should fail since the word length is incorrect
    ASSERT_DEATH({this->invoke_to_read_write_32(0, data_32, data_32, 5, 10000);},
                 "Assertion `0' failed.");
    ASSERT_EQ(this->component.m_isOwned, true);
  }



  bool TestState ::
    precondition__RWOwner__SUCCESS32(void) const
  {
    bool result = true;
    result &= this->component.m_isOwned;
    //printf("Precondition for RWOwner SUCCESS32 result is: %d\n", result);
    return result;
  }


  void TestState ::
    action__RWOwner__SUCCESS32(void)
  {
    //printf("Action for RWOwner SUCCESS32\n");
    // Initialize test state
    this->clearHistory();
    
    I32 status;

    status = this->invoke_to_spi_configure((NATIVE_INT_TYPE) 0, //portNum
				  (U8) 0, //loopback_mode
				  (U8) 0, //clock_polarity
				  (U8) 0, //clock_phase
				  (U8) 0, //div_clock_16
				  (U8) 1, //reverse_mode
				  (U8) 32, //word_len
				  (U8) 12, //prescale modulus
				  (U8) 0,  //prescale modulus factor
				  (U8) 0); //clock_gap
    ASSERT_EQ(status, 0);

    clearBit(SPI_CTRL_EVT_REG, EVENT_OV);

    U32 data_32[5] = {1,2,3,4,5};

    //read/write 32 bit spi word with claiming
    status = this->invoke_to_read_write_32(0, data_32, data_32, 5, 10000);
    ASSERT_EQ(status, 0);
    ASSERT_EQ(this->component.m_isOwned, true);
    
    U16 data_16[5] = {1,2,3,4,5};

    //read/write 16 bit spi word with claiming, should fail since the word length is incorrect
    ASSERT_DEATH({this->invoke_to_read_write_16(0, data_16, data_16, 5, 10000);},
                 "Assertion `0' failed.");
    ASSERT_EQ(this->component.m_isOwned, true);
    
    U8 data_8[5] = {1,2,3,4,5};

    //read/write 8 bit spi word with claiming, should fail since the word length is incorrect
    ASSERT_DEATH({this->invoke_to_read_write_8(0, data_8, data_8, 5, 10000);},
                 "Assertion `0' failed.");
    ASSERT_EQ(this->component.m_isOwned, true);
  }



  namespace RWOwner {

    // ---------------------------------------------------------------------- 
    // Tests
    // ---------------------------------------------------------------------- 

    void Tester ::
      ERROR(void)
    {
      this->ruleERROR.apply(this->testState);
    }

    void Tester ::
    SUCCESS8(void)
    {
      //apply rule
      this->mutexTester.ruleClaimOK.apply(this->testState);
      this->ruleSUCCESS8.apply(this->testState);
    }

    void Tester ::
    TIMEOUT(void)
    {
      //apply rule
      this->mutexTester.ruleClaimOK.apply(this->testState);
      this->ruleTIMEOUT.apply(this->testState);
    }

    
    void Tester ::
    SUCCESS16(void)
    {
      //apply rule
      this->mutexTester.ruleClaimOK.apply(this->testState);
      this->ruleSUCCESS16.apply(this->testState);
    }

    void Tester ::
    SUCCESS32(void)
    {
      //apply rule
      this->mutexTester.ruleClaimOK.apply(this->testState);
      this->ruleSUCCESS32.apply(this->testState);
    }

  }

}
