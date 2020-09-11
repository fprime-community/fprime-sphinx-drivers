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
#include "fprime-sphinx-drivers/Random/Random.hpp"
#include "Read.hpp"

namespace Drv {
  // ---------------------------------------------------------------------- 
  // Rule definitions
  // ---------------------------------------------------------------------- 

  bool TestState ::
    precondition__Read__OK(void) const
  {
    bool result = true;
    //precondition is true when the state is idle
    result &= (this->component.m_state == NORMGR_IDLE);
    //printf("Precondition for Read OK result is: %d\n", result);
    return result;
  }


  void TestState ::
  checkValues(U8* data, U32 mark, U32 mark2, U32 count)
  {
    U32 check = 0;
    U32 j = 0;
    for(U32 i = 0; i < count; i++)
    {
      check |= (data[i] << (3-i)*8);
      j++;
      if(j == 4)
      {
        ASSERT_EQ(check, mark);
        mark = mark2;
        j = 0;
        check = 0;
      }
    }
  }


  void TestState ::
    action__Read__OK(void)
  {
    //printf("Action for Read OK\n");
    
    //base address of NOR flash
    U32 addr = 0x00000000;
    //write 8 bytes of data
    U8 data[8] = {0};
    U32 mark = 0xDEADBEEF;
    U32 mark2 = 0x12345678;
    writeReg(addr, mark);
    writeReg(addr+0x4, mark2);

    //without edac disabled
    this->invoke_to_request_read(0, addr, data, 8, 0);
    this->component.doDispatch();

    checkValues(data, mark, mark2, 8);
    
    ASSERT_EQ(this->component.m_state, NORMGR_READING);
   
    U8 data2[8] = {0};
    U32 mark3 = 0xCCCCCCCC;
    U32 mark4 = 0x87654321;
    U32 addr2 = 0x10000000;
    writeReg(addr2, mark3);
    writeReg(addr2+0x4, mark4);

    this->clearHistory();

    this->component.m_state = NORMGR_IDLE;

    //with edac disabled
    this->invoke_to_request_read(0, addr2, data2, 8, 1);
    this->component.doDispatch();

    checkValues(data2, mark3, mark4, 8);

    ASSERT_EQ(this->component.m_state, NORMGR_READING);
    this->component.m_state = NORMGR_IDLE;
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
    
    U8 data[4] = {0xDE,0xAD,0xC0,0xDE};
    U32 addr = 0x00000000;
    writeReg(0x00000000, 0xDEADDEAD);
    this->component.m_state = NORMGR_READING;
    
    //write out busy, check that data wasn't actually read in
    this->invoke_to_request_read(0, addr, data, 4, 0);
    this->component.doDispatch();
    checkValues(data, 0xDEADC0DE, 0x00000000, 4);

    this->component.m_state = NORMGR_IDLE;
    
    //null ptr
    U8* null_ptr = NULL;
    ASSERT_DEATH({this->invoke_to_request_read(0, addr, null_ptr, 8, 0);
                  this->component.doDispatch();},
                 "Assertion `0' failed.");

    //invalid addr
    U32 invalid_addr = 0x30000000;
    ASSERT_DEATH({this->invoke_to_request_read(0, invalid_addr, data, 5, 0);
	       this->component.doDispatch();},
	       "Assertion `0' failed.");

    //invalid count
    U32 invalid_count = 70000;
    ASSERT_DEATH({this->invoke_to_request_read(0, addr, data, invalid_count, 0);
	       this->component.doDispatch();},
                 "Assertion `0' failed.");

    //out of bounds read
    U32 close_addr = 0x1FFFFFFF;
    ASSERT_DEATH({this->invoke_to_request_read(0, close_addr, data, 5, 0);
	       this->component.doDispatch();},
	       "Assertion `0' failed.");

  }


  namespace Read {

    // ---------------------------------------------------------------------- 
    // Tests
    // ----------------------------------------------------------------------     

    Tester :: Tester(const char* compName, U32 timeout) 
      : testState(compName, timeout)
    {

    }

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
