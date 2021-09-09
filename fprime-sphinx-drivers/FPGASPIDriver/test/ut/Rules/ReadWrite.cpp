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
    precondition__ReadWrite__OK(void) const
  {
    bool result = true;
    //precondition is always true
    //printf("Precondition for ReadWrite OK result is: %d\n", result);
    return result;
  }

  void TestState ::
    action__ReadWrite__OK(void)
  {
    //printf("Action for ReadWrite OK\n");

    NATIVE_INT_TYPE portNum = 0;
    U8 write_buf[5] = {1,2,3,4,5};
    U8 read_buf[5] = {1,2,3,4,5};
    U32 nBytes = 5;
    U8 activate_slave = 0;
    U16 timeout = 100;
    U8 clock_bitrate = FPGA_SPI_BITRATE_10_MBS;
    U8 bit_order = 0;
    U32 delay_timeout = 1;
    U32 delay = 0;

    this->setTestTime(Fw::Time(1, 100));

    //Should correctly time out when counter < bound
    ASSERT_DEATH({this->invoke_to_read_write(portNum, write_buf,
                                            read_buf, nBytes, activate_slave,
				     timeout, clock_bitrate, bit_order, delay_timeout);},
                 "Assertion");

    U32 status = this->invoke_to_read_write(portNum, write_buf,
                                            read_buf, nBytes, activate_slave,
				    timeout, clock_bitrate, bit_order, delay);
    ASSERT_EQ(status, 0);

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

    NATIVE_INT_TYPE portNum = 0;
    U8 write_buf[5] = {1,2,3,4,5};
    U8 read_buf[5] = {1,2,3,4,5};
    U32 nBytes = 5;
    U8 activate_slave = 0;
    U16 timeout = 100;
    U8 clock_bitrate = FPGA_SPI_BITRATE_10_MBS;
    U8 bit_order = 0;
    U32 delay = 0;

    //Check null write ptr
    U8* null_write_buf = NULL;
    ASSERT_DEATH({this->invoke_to_read_write(portNum, null_write_buf,
                                            read_buf, nBytes, activate_slave,
				     timeout, clock_bitrate, bit_order, delay);},
                 "Assertion");

    //Check null read ptr
    U8* null_read_buf = NULL;
    ASSERT_DEATH({this->invoke_to_read_write(portNum, write_buf,
				     null_read_buf, nBytes, activate_slave,
				     timeout, clock_bitrate, bit_order, delay);},
                 "Assertion");

    //Check max nbytes
    U32 invalid_nBytes = (FPGA_SPI_MAX_BYTES_PER_TRANSACTION+1);
    ASSERT_DEATH({this->invoke_to_read_write(portNum, write_buf,
                                            read_buf, invalid_nBytes, activate_slave,
				     timeout, clock_bitrate, bit_order, delay);},
                 "Assertion");

    //Check clock_br, 4 is invalid
    U8 invalid_bit_rate = 4;
    ASSERT_DEATH({this->invoke_to_read_write(portNum, write_buf,
                                            read_buf, nBytes, activate_slave,
				     timeout, invalid_bit_rate, bit_order, delay);},
                 "Assertion");

    //Check bit order, 2 is invalid
    U8 invalid_bit_order = 2;
    ASSERT_DEATH({this->invoke_to_read_write(portNum, write_buf,
                                            read_buf, nBytes, activate_slave,
				     timeout, clock_bitrate, invalid_bit_order, delay);},
                 "Assertion");

    //Check delay value, max is 1000000
    U32 invalid_delay = 1000001;
    ASSERT_DEATH({this->invoke_to_read_write(portNum, write_buf,
                                            read_buf, nBytes, activate_slave,
				     timeout, clock_bitrate, bit_order, invalid_delay);},
                 "Assertion");

  }


  namespace ReadWrite {

    // ----------------------------------------------------------------------
    // Tests
    // ----------------------------------------------------------------------

    Tester :: Tester(const char* compName,
		     U32 spiNumber,
                         U32 spiWidth)
      : testState(compName, spiNumber, spiWidth)
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
