// ====================================================================== 
// \title  SPIDriverGeneric/test/ut/Tester.cpp
// \author bsoudry
// \brief  cpp file for SPIDriverGeneric test harness implementation class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
// ====================================================================== 

#include "Tester.hpp"

#define INSTANCE 0
#define MAX_HISTORY_SIZE 10

namespace Drv {

  // ----------------------------------------------------------------------
  // Construction and destruction 
  // ----------------------------------------------------------------------

  Tester ::
    Tester(void) : 
#if FW_OBJECT_NAMES == 1
      SPIDriverGenericGTestBase("Tester", MAX_HISTORY_SIZE),
      component("SPIDriverGeneric")
#else
      SPIDriverGenericGTestBase(MAX_HISTORY_SIZE),
      component()
#endif
  {
    this->initComponents();
    this->connectPorts();

    //initial register values, set as desired
    SphinxDrvReg::fileEntry fileRegs[] = {
        {0, SPI_CTRL_MODE_REG},
        {13, SPI_CTRL_EVT_REG},
        {21, SPI_CMD_REG},
        {17,SPI_TX_REG},
        {6, SPI_RX_REG}
    };

    //currently set to zero to not interfere with other reads/writes
    //change to 5 to initialize the above register with values
    SphinxDrvReg regData(fileRegs, 0);
    regData.writeFile();

  }

   //alternate constructor
  Tester::Tester(const char* compName,
		 U8 loopback_mode,
		 U8 clock_polarity,
		 U8 clock_phase,
		 U8 div_clock_16,
		 U8 reverse_mode,
		 U8 word_len,
		 U8 prescale_modulus,
		 U8 prescale_modulus_factor,
		 U8 clock_gap) :
    #if FW_OBJECT_NAMES == 1
        SPIDriverGenericGTestBase("Tester", MAX_HISTORY_SIZE),
        //component("SPIDriverGeneric")
	component(compName, 
		  loopback_mode,
		  clock_polarity,
		  clock_phase,
		  div_clock_16,
		  reverse_mode,
		  word_len,
		  prescale_modulus,
		  prescale_modulus_factor,
		  clock_gap)
    #else
        SPIDriverGenericGTestBase(MAX_HISTORY_SIZE),
        component(loopback_mode, 
	      clock_polarity, 
	      clock_phase, 
	      div_clock_16,
	      reverse_mode,
	      word_len,
	      prescale_modulus, 
	      prescale_modulus_factor, 
	      clock_gap)
    #endif
  {
    this->initComponents();
    this->connectPorts();

    //initial register values
    SphinxDrvReg::fileEntry fileRegs[] = {
      {0, 0x80000420},
      {13, 0x80000424},
      {21, 0x80000430},
      {17,0x80000434}
    };

    //currently set to zero to not interfere with other reads/writes
    SphinxDrvReg regData(fileRegs, 0);
    regData.writeFile();

  }

  Tester ::
    ~Tester(void) 
  {
    //check for claimed semaphore here and call unclaim if 
    if(this->component.m_isOwned)
    {
      (void) this->invoke_to_spi_unclaim(0);
    }
  }

  // ----------------------------------------------------------------------
  // Tests 
  // ----------------------------------------------------------------------
  
  void Tester ::
    testClaimUnclaimOK(void) 
  {
    I32 status;
    
    ASSERT_EQ(this->component.m_isOwned, false);  
    
    //claim
    status = this->invoke_to_spi_claim(0);
    ASSERT_EQ(status, 0);
    ASSERT_EQ(this->component.m_isOwned, true);   

    //unclaim
    status = this->invoke_to_spi_unclaim(0);
    ASSERT_EQ(status, 0);
    ASSERT_EQ(this->component.m_isOwned, false);  
  }
  
  void Tester ::
    testDoubleClaim(void) 
  {
    I32 status;
    
    ASSERT_EQ(this->component.m_isOwned, false);  
    
    //claim
    status = this->invoke_to_spi_claim(0);
    ASSERT_EQ(status, 0);
    ASSERT_EQ(this->component.m_isOwned, true);
    
    //claim after we already claimed
    status = this->invoke_to_spi_claim(0);
    ASSERT_EQ(status, SPI_CLAIM_ALREADY_OWNER_ERR);
    ASSERT_EQ(this->component.m_isOwned, true);
    
    //unclaim
    status = this->invoke_to_spi_unclaim(0);
    ASSERT_EQ(status, 0);
    ASSERT_EQ(this->component.m_isOwned, false);
 }
   
  void Tester ::
    testDoubleUnclaim(void) 
  {
    I32 status;
    
    ASSERT_EQ(this->component.m_isOwned, false);
    
    //claim
    status = this->invoke_to_spi_claim(0);
    ASSERT_EQ(status, 0);
    ASSERT_EQ(this->component.m_isOwned, true);

    //unclaim
    status = this->invoke_to_spi_unclaim(0);
    ASSERT_EQ(status, 0);
    ASSERT_EQ(this->component.m_isOwned, false);
    
    //unclaim after already unclaimed
    status = this->invoke_to_spi_unclaim(0);
    ASSERT_EQ(status, SPI_UNCLAIM_NOT_OWNER_ERR);
    ASSERT_EQ(this->component.m_isOwned, false);
 }
  void Tester ::
    testInitOK(void) 
 {
    //Confirm that member variables are configure for the Iris radio in the constructor 
    ASSERT_EQ(this->component.m_loopback_mode, false);
    ASSERT_EQ(this->component.m_clock_polarity, false);
    ASSERT_EQ(this->component.m_clock_phase, false);
    ASSERT_EQ(this->component.m_div_clock_16, false);
    ASSERT_EQ(this->component.m_reverse_mode, true);
    ASSERT_EQ(this->component.m_word_len, 8);
    ASSERT_EQ(this->component.m_prescale_modulus, 12);
    ASSERT_EQ(this->component.m_prescale_modulus_factor, false);
    ASSERT_EQ(this->component.m_clock_gap, 0);
    }
 void Tester ::
    testConfigureOK(void) 
 {
    I32 status;
    
    ASSERT_EQ(this->component.m_isOwned, false);

    //claim
    status = this->invoke_to_spi_claim(0);
    ASSERT_EQ(status, 0);
    ASSERT_EQ(this->component.m_isOwned, true);

    //configure registers (settings not for Iris)
    status = this->invoke_to_spi_configure(0, 0, 1, 1, 0, 1, 32, 15, 0, 0);
    ASSERT_EQ(status, 0);

    ASSERT_EQ(this->component.m_loopback_mode, false);
    ASSERT_EQ(this->component.m_clock_polarity, true);
    ASSERT_EQ(this->component.m_clock_phase, true);
    ASSERT_EQ(this->component.m_div_clock_16, false);
    ASSERT_EQ(this->component.m_reverse_mode, true);
    ASSERT_EQ(this->component.m_word_len, 32);
    ASSERT_EQ(this->component.m_prescale_modulus, 15);
    ASSERT_EQ(this->component.m_prescale_modulus_factor, false);
    ASSERT_EQ(this->component.m_clock_gap, 0);
 
    //unclaim
    status = this->invoke_to_spi_unclaim(0);
    ASSERT_EQ(status, 0);
    ASSERT_EQ(this->component.m_isOwned, false);
 }
  
  void Tester ::
    testConfigureNotOwner(void) 
 {
    I32 status;
    
    ASSERT_EQ(this->component.m_isOwned, false);
 
    //configure registers without claiming (settings not for Iris)
    status = this->invoke_to_spi_configure(0, 0, 1, 1, 0, 1, 32, 15, 0, 0);
    ASSERT_EQ(status, SPI_CONFIGURE_NOT_OWNER_ERR);
    
    //Verify registers are still configured for Iris (Not new configuration)
    ASSERT_EQ(this->component.m_loopback_mode, false);
    ASSERT_EQ(this->component.m_clock_polarity, false);
    ASSERT_EQ(this->component.m_clock_phase, false);
    ASSERT_EQ(this->component.m_div_clock_16, false);
    ASSERT_EQ(this->component.m_reverse_mode, true);
    ASSERT_EQ(this->component.m_word_len, 8);
    ASSERT_EQ(this->component.m_prescale_modulus, 12);
    ASSERT_EQ(this->component.m_prescale_modulus_factor, false);
    ASSERT_EQ(this->component.m_clock_gap, 0);      
    
    ASSERT_EQ(this->component.m_isOwned, false);
}

  void Tester ::
    testRWNotOwner(void) 
 {
    U8 data_8[5] = {1,2,3,4,5};
    I32 status;
    
    ASSERT_EQ(this->component.m_isOwned, false);
 
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

  void Tester::testConstructor(void)
  {
    ASSERT_EQ(this->component.m_loopback_mode, false);
    ASSERT_EQ(this->component.m_clock_polarity, false);
    ASSERT_EQ(this->component.m_clock_phase, false);
    ASSERT_EQ(this->component.m_div_clock_16, false);
    ASSERT_EQ(this->component.m_reverse_mode, true);
    ASSERT_EQ(this->component.m_word_len, 8);
    ASSERT_EQ(this->component.m_prescale_modulus, 12);
    ASSERT_EQ(this->component.m_prescale_modulus_factor, false);
    ASSERT_EQ(this->component.m_clock_gap, 0);
  }
  
  // ----------------------------------------------------------------------
  // Handlers for typed from ports
  // ----------------------------------------------------------------------

  void Tester ::
    from_timeCaller_handler(
        const NATIVE_INT_TYPE portNum,
        Fw::Time &time
    )
  {
    this->pushFromPortEntry_timeCaller(time);
  }

  // ----------------------------------------------------------------------
  // Helper methods 
  // ----------------------------------------------------------------------

  void Tester ::
    connectPorts(void) 
  {

    // spi_unclaim
    this->connect_to_spi_unclaim(
        0,
        this->component.get_spi_unclaim_InputPort(0)
    );

    // read_write_16
    this->connect_to_read_write_16(
        0,
        this->component.get_read_write_16_InputPort(0)
    );

    // read_write_32
    this->connect_to_read_write_32(
        0,
        this->component.get_read_write_32_InputPort(0)
    );

    // spi_claim
    this->connect_to_spi_claim(
        0,
        this->component.get_spi_claim_InputPort(0)
    );

    // spi_configure
    this->connect_to_spi_configure(
        0,
        this->component.get_spi_configure_InputPort(0)
    );

    // read_write_8
    this->connect_to_read_write_8(
        0,
        this->component.get_read_write_8_InputPort(0)
    );

    // timeCaller
    this->component.set_timeCaller_OutputPort(
        0, 
        this->get_from_timeCaller(0)
    );

  }

  void Tester ::
    initComponents(void) 
  {
    this->init();
    this->component.init(
        INSTANCE
    );
  }

} // end namespace Drv
