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
    
    this->clearHistory();

    //write 8 bytes of data
    U8 data[8] = {0};
    U32 addr = 0x00002000;
    U32 mark = 0xDEADBEEF;
    U32 mark2 = 0x12345678;
    writeReg(addr, mark);
    writeReg(addr+0x4, mark2);
    this->invoke_to_read_block(0, data, addr, 8, 0);
    this->component.doDispatch();

    checkValues(data, mark, mark2, 8);
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

    this->clearHistory();
    
    U8 data[8] = {0};
    U32 addr = 0x20000000;
    this->invoke_to_read_block(0, data, addr, 8, 0);
    this->component.doDispatch();

    //null ptr
    U8* null_data = NULL;
    ASSERT_DEATH({this->invoke_to_read_block(0, null_data, addr, 8, 0);
                  this->component.doDispatch();},                                                                                      
                  "Assertion `0' failed.");

    //invalid bank
    ASSERT_DEATH({this->invoke_to_read_block(0, data, addr, 8, 5);
                  this->component.doDispatch();},
                  "Assertion `0' failed.");

    ASSERT_DEATH({this->invoke_to_read_block(0, data, addr, 50000, 0);
                  this->component.doDispatch();},                       
                  "Assertion `0' failed.");

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
