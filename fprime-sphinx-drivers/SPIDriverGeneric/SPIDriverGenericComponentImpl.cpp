// ====================================================================== 
// \title  SPIDriverGenericImpl.cpp
// \author bsoudry
// \brief  cpp file for SPIDriverGeneric component implementation class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
// ====================================================================== 


#include <fprime-sphinx-drivers/SPIDriverGeneric/SPIDriverGenericComponentImpl.hpp>
#include <fprime-sphinx-drivers/SPIDriverGeneric/SPIDriverGenericErrorCodes.hpp>
#include <fprime-sphinx-drivers/Util/SphinxDrvIntUtil.hpp>
#include "Fw/Types/BasicTypes.hpp"
#include "Fw/Types/Assert.hpp"
#include <Os/Mutex.hpp>
#include <Os/Task.hpp>
#include <Os/TaskId.hpp>


namespace Drv {

  // ----------------------------------------------------------------------
  // Construction, initialization, and destruction 
  // ----------------------------------------------------------------------

  SPIDriverGenericComponentImpl ::
#if FW_OBJECT_NAMES == 1
    SPIDriverGenericComponentImpl(
        const char *const compName,
        const U8 loopback_mode,
        const U8 clock_polarity,
        const U8 clock_phase,
        const U8 div_clock_16,
        const U8 reverse_mode,
        const U8 word_len,
        const U8 prescale_modulus,
        const U8 prescale_modulus_factor,
        const U8 clock_gap
    ) :
      SPIDriverGenericComponentBase(compName)
#else
    SPIDriverGenericImpl( 
      const U8 loopback_mode,
      const U8 clock_polarity,
      const U8 clock_phase,
      const U8 div_clock_16,
      const U8 reverse_mode,
      const U8 word_len,
      const U8 prescale_modulus,
      const U8 prescale_modulus_factor,
      const U8 clock_gap)

#endif
  {
    m_isOwned = false;
    //validate all boolean settings:
    FW_ASSERT(loopback_mode <= 1);
    FW_ASSERT(clock_polarity <= 1);
    FW_ASSERT(clock_phase <= 1);
    FW_ASSERT(div_clock_16 <= 1);
    FW_ASSERT(reverse_mode <= 1);
    FW_ASSERT(prescale_modulus_factor <= 1);

    //Validate word_len - 4-16 bit or 32 bit words
    FW_ASSERT(word_len == 32 || (word_len >= 4 && word_len <= 16));
      
    //Validate prescale modulus
    FW_ASSERT(prescale_modulus <= 0xF);

    //Validate clock gap
    FW_ASSERT(clock_gap <= 0xF);
      
    m_loopback_mode = loopback_mode;
    m_clock_polarity = clock_polarity;
    m_clock_phase = clock_phase;
    m_div_clock_16 = div_clock_16;
    m_reverse_mode = reverse_mode;
    m_word_len = word_len;
    m_prescale_modulus = prescale_modulus;
    m_prescale_modulus_factor = prescale_modulus_factor;
    m_clock_gap = clock_gap;
  }


 /*Alternate constructor, if no arguments are given, use settings for Iris radio*/
 SPIDriverGenericComponentImpl ::
#if FW_OBJECT_NAMES == 1
    SPIDriverGenericComponentImpl(
        const char *const compName
    ) :
      SPIDriverGenericComponentBase(compName)
#else
    SPIDriverGenericImpl(void)
#endif
 {
    m_isOwned = false;
    m_loopback_mode = false;
    m_clock_polarity = false;
    m_clock_phase = false;
    m_div_clock_16 = false;
    m_reverse_mode = true;
    m_word_len = 8; //8 bit word length

#if defined(BUILD_GR712DEV)
    //Set PM to 0b1111 = 15
    //Set SPI Clock to 0.75MHz
    m_prescale_modulus = 0xF;
#elif defined(BUILD_SPHINX)
    //Set PM to 0b1100 = 12
    //Set SPI Clock to 0.77MHz
    m_prescale_modulus = 0xC;
#else 
    m_prescale_modulus = 0xC;
#endif

    m_prescale_modulus_factor = false;
    m_clock_gap = 0x0; //back-to back transfers
  }

  void SPIDriverGenericComponentImpl ::
    init(
        const NATIVE_INT_TYPE instance
    ) 
    {
      SPIDriverGenericComponentBase::init(instance);
      this->init_registers();
    }

  SPIDriverGenericComponentImpl ::
    ~SPIDriverGenericComponentImpl(void)
  {

  }
  
  void SPIDriverGenericComponentImpl ::
    init_registers(void)
  {
      //Disable SPI Core to allow for modifying register
      Drv::clearBit(SPI_CTRL_MODE_REG, MODE_EN);
      
      //Initialize mode register
      Drv::writeRegPartial(SPI_CTRL_MODE_REG, MODE_LOOP, 1,  m_loopback_mode);
      Drv::writeRegPartial(SPI_CTRL_MODE_REG, MODE_CPOL, 1, m_clock_polarity);
      Drv::writeRegPartial(SPI_CTRL_MODE_REG, MODE_CPHA, 1, m_clock_phase);
      Drv::writeRegPartial(SPI_CTRL_MODE_REG, MODE_DIV16, 1, m_div_clock_16);
      Drv::writeRegPartial(SPI_CTRL_MODE_REG, MODE_REV, 1, m_reverse_mode);
      
      Drv::setBit(SPI_CTRL_MODE_REG, MODE_MS);
      
      Drv::writeRegPartial(SPI_CTRL_MODE_REG, MODE_PM0, 4, m_prescale_modulus);
      Drv::writeRegPartial(SPI_CTRL_MODE_REG, MODE_CG, 4, m_clock_gap);

      //Convert Word Length to correct register value (see GR712 manual p170)
      U8 word_len_reg;
      if(m_word_len == 32)
      {
        word_len_reg = 0x0;
      } 
      else
      {
        word_len_reg = m_word_len-1;
      }
      FW_ASSERT(word_len_reg == 0 || (word_len_reg >= 0x3 && word_len_reg <= 0xF));
      Drv::writeRegPartial(SPI_CTRL_MODE_REG, MODE_LEN, 4, word_len_reg);

      Drv::writeRegPartial(SPI_CTRL_MODE_REG, MODE_FACT, 1, m_prescale_modulus_factor);
      
      //Enable SPI Core
      Drv::setBit(SPI_CTRL_MODE_REG, MODE_EN); 

      //Initialize EVT register by setting LT, OV and UN bits
      Drv::setBit(SPI_CTRL_EVT_REG, EVENT_LT);
      Drv::setBit(SPI_CTRL_EVT_REG, EVENT_OV);
      Drv::setBit(SPI_CTRL_EVT_REG, EVENT_UN);
  }
 
  // ----------------------------------------------------------------------
  // Handler implementations for user-defined typed input ports
  // ----------------------------------------------------------------------
  I32 SPIDriverGenericComponentImpl ::
    spi_claim_handler(
        const NATIVE_INT_TYPE portNum
    )
  {
    //Check that the caller is not the task that already owns the SPI driver
    Os::TaskId callerID = Os::Task::getOsIdentifier();
    if(callerID == m_ownerID && m_isOwned == true) 
    {
      return SPI_CLAIM_ALREADY_OWNER_ERR;
    }
    m_mutex.lock();
   
    //Note, m_ownerID must be updated before m_isOwned is set to true
    //To avoid a state where the previous owner can access the SPI interface
    m_ownerID = callerID; 
    m_isOwned = true;

    return 0;

  }
  
  I32 SPIDriverGenericComponentImpl ::
    spi_unclaim_handler(
        const NATIVE_INT_TYPE portNum
    )
  {
    //Check that the caller is the current owner of the SPI driver
    Os::TaskId callerID = Os::Task::getOsIdentifier();
    if(callerID != m_ownerID || m_isOwned == false)
    {
      return SPI_UNCLAIM_NOT_OWNER_ERR;
    }
    m_isOwned = false;

    m_mutex.unLock();
    
    return 0;
  }

  I32 SPIDriverGenericComponentImpl ::
    spi_configure_handler(
        const NATIVE_INT_TYPE portNum,
        U8 loopback_mode,
        U8 clock_polarity,
        U8 clock_phase,
        U8 div_clock_16,
        U8 reverse_mode,
        U8 word_len,
        U8 prescale_modulus,
        U8 prescale_modulus_factor,
        U8 clock_gap
    )
  {
    //Check that the caller is the current owner of the SPI driver
    Os::TaskId callerID = Os::Task::getOsIdentifier();
    if(callerID != m_ownerID || m_isOwned == false)
    {
      return SPI_CONFIGURE_NOT_OWNER_ERR;
    }
    
    //validate all boolean settings:
    FW_ASSERT(loopback_mode <= 1);
    FW_ASSERT(clock_polarity <= 1);
    FW_ASSERT(clock_phase <= 1);
    FW_ASSERT(div_clock_16 <= 1);
    FW_ASSERT(reverse_mode <= 1);
    FW_ASSERT(prescale_modulus_factor <= 1);

    //Validate word_len - 4-16 bit or 32 bit words
    FW_ASSERT(word_len == 32 || (word_len >= 4 && word_len <= 16));
      
    //Validate prescale modulus
    FW_ASSERT(prescale_modulus <= 0xF);
    //Validate clock gap
    FW_ASSERT(clock_gap <= 0xF);
      
    m_loopback_mode = loopback_mode;
    m_clock_polarity = clock_polarity;
    m_clock_phase = clock_phase;
    m_div_clock_16 = div_clock_16;
    m_reverse_mode = reverse_mode;
    m_word_len = word_len;
    m_prescale_modulus = prescale_modulus;
    m_prescale_modulus_factor = prescale_modulus_factor;
    m_clock_gap = clock_gap;
    
    this->init_registers();
    return 0;
  }

  I32 SPIDriverGenericComponentImpl ::
    read_write_8_handler(
        const NATIVE_INT_TYPE portNum,
        U8 *write_buf_ptr,
        U8 *read_buf_ptr,
        U32 nWords,
        U32 timeout_uS
    )
 { 
    I32 status;
    //Check that the caller is the current owner of the SPI driver
    Os::TaskId callerID = Os::Task::getOsIdentifier();
    if(callerID != m_ownerID || m_isOwned == false)
    {
      return SPI_RW_NOT_OWNER_ERR; 
    }
    
    if (nWords > 0) {
      FW_ASSERT(write_buf_ptr != NULL);
      FW_ASSERT(read_buf_ptr != NULL);
    }
    if (nWords == 0)
    {
      return 0;
    }
   
    //Check that the word size is configured correctly for this port 
    FW_ASSERT(m_word_len >= 4 && m_word_len <= 8);
    
    status = this->spi_rw((void*) write_buf_ptr, 
                    (void*) read_buf_ptr,
                    SPI_U8_BUF_PTR, 
                    nWords, 
                    timeout_uS);
    return status;
  }
  
  I32 SPIDriverGenericComponentImpl ::
    read_write_16_handler(
        const NATIVE_INT_TYPE portNum,
        U16 *write_buf_ptr,
        U16 *read_buf_ptr,
        U32 nWords,
        U32 timeout_uS
    )
 {
    I32 status;
 
    //Check that the caller is the current owner of the SPI driver
    Os::TaskId callerID = Os::Task::getOsIdentifier();
    if(callerID != m_ownerID || m_isOwned == false)
    {
      return SPI_RW_NOT_OWNER_ERR;
    }
      
    if (nWords > 0) {
      FW_ASSERT(write_buf_ptr != NULL);
      FW_ASSERT(read_buf_ptr != NULL);
    }
    if (nWords == 0)
    {
      return 0;
    }

    //Check that the word size is configured correctly for this port 
    FW_ASSERT(m_word_len > 8 && m_word_len <= 16);
    
    status = this->spi_rw((void*) write_buf_ptr, 
                          (void*) read_buf_ptr,
                           SPI_U16_BUF_PTR, 
                           nWords, 
                           timeout_uS);
    return status;
  }

   I32 SPIDriverGenericComponentImpl ::
    read_write_32_handler(
        const NATIVE_INT_TYPE portNum,
        U32 *write_buf_ptr,
        U32 *read_buf_ptr,
        U32 nWords,
        U32 timeout_uS
    )
   {
    I32 status;
 
    //Check that the caller is the current owner of the SPI driver
    Os::TaskId callerID = Os::Task::getOsIdentifier();
    if(callerID != m_ownerID || m_isOwned == false)
    {
      return SPI_RW_NOT_OWNER_ERR;
    }
      
    if (nWords > 0) {
      FW_ASSERT(write_buf_ptr != NULL);
      FW_ASSERT(read_buf_ptr != NULL);
    }
    if (nWords == 0)
    {
      return 0;
    }
   
    //Check that the word size is configured correctly for this port 
    FW_ASSERT(m_word_len == 32);
    status = this->spi_rw((void*) write_buf_ptr, 
                          (void*) read_buf_ptr,
                          SPI_U32_BUF_PTR, 
                          nWords, 
                          timeout_uS);
    return status;
  }

  I32 SPIDriverGenericComponentImpl :: 
    spi_rw(
        void *write_buf_ptr,
        void *read_buf_ptr,
        U8 buf_ptr_size,
        U32 nWords,
        U32 timeout_uS
    )
  {
    I32 status;

    FW_ASSERT(write_buf_ptr != NULL);
    FW_ASSERT(read_buf_ptr != NULL);
    
    FW_ASSERT(nWords < MAX_WORDS_PER_SPI_TRANSACTION);    
    FW_ASSERT(timeout_uS < SPI_MAX_TIMEOUT_USECS);
    FW_ASSERT(buf_ptr_size == SPI_U8_BUF_PTR 
           || buf_ptr_size == SPI_U16_BUF_PTR
           || buf_ptr_size == SPI_U32_BUF_PTR);

    // Resetting spi core here in order to clear any errors or hang ups
    this->resetSpiCore();

    while(nWords > 0)
    {
      // write to spi reg
      status = this->write((void*) write_buf_ptr, buf_ptr_size, 1, timeout_uS);
      if(status != 0)
      {
        return status;
      }
  
      // read from spi reg
      status = this->read((void*) read_buf_ptr, buf_ptr_size, 1, timeout_uS);
      if(status != 0)
      {
        return status;
      }
      this->incrementPointer(write_buf_ptr, buf_ptr_size);
      this->incrementPointer(read_buf_ptr, buf_ptr_size);
      nWords--;
    }

    return 0;
  }

  void SPIDriverGenericComponentImpl ::
      incrementPointer(void*& ptr, U8 ptr_size)
  {
      FW_ASSERT(ptr != NULL);
      FW_ASSERT(ptr_size == SPI_U8_BUF_PTR 
             || ptr_size == SPI_U16_BUF_PTR
             || ptr_size == SPI_U32_BUF_PTR);

      switch(ptr_size)
      {
        case SPI_U8_BUF_PTR:
          ptr = (U8*) ptr + 1;
          break;
        case SPI_U16_BUF_PTR:
          ptr = (U16*) ptr + 1;
          break;
        case SPI_U32_BUF_PTR:
          ptr = (U32*) ptr + 1;
          break;
        default:
          break;
      }
  }

  I32 SPIDriverGenericComponentImpl :: 
     read(
        void *data_ptr,
        U8 data_ptr_size,
        U32 nWords,
        const U32 timeout_uS
    )
  { 
    U32 val;
    U32 rx_val; //value of recieve register 

    // Check input values for validity
    FW_ASSERT(data_ptr != NULL);
    FW_ASSERT(nWords < MAX_WORDS_PER_SPI_TRANSACTION);    
    FW_ASSERT(timeout_uS < SPI_MAX_TIMEOUT_USECS);
    FW_ASSERT(data_ptr_size == SPI_U8_BUF_PTR 
           || data_ptr_size == SPI_U16_BUF_PTR
           || data_ptr_size == SPI_U32_BUF_PTR);

    //Check that data_ptr_size argument is consistent with m_word_len
    switch(data_ptr_size)
    {
      case SPI_U8_BUF_PTR:
        FW_ASSERT(m_word_len >= 4 && m_word_len <= 8);
        break;
      case SPI_U16_BUF_PTR:
        FW_ASSERT(m_word_len > 8 && m_word_len <= 16);
        break;
      case SPI_U32_BUF_PTR:
        FW_ASSERT(m_word_len == 32);
        break;
      default:
        FW_ASSERT(0);
        break;
    }
  
    while (nWords > 0) {
      // Decrement bytes first. If failure occurs then loop
      // will return out
      nWords -= 1;

      //Check if receive queue is Not Empty (NE) in EVT register
      val = Drv::readBit(SPI_CTRL_EVT_REG, EVENT_NE);


      //Wait for recieve queue not empty or timeout using system time 
      Fw::Time increment(0, timeout_uS);
      Fw::Time now = this->getTime();
      Fw::Time target = Fw::Time::add(now, increment);

      U32 bound = SPI_COUNT_PER_USEC_OF_DELAY*timeout_uS;
      U32 counter = 0;
     
      while(val == 0 && (counter < bound)) 
      {
        if(this->getTime() >= target)
        {
          break;
        }
        val = readBit(SPI_CTRL_EVT_REG, EVENT_NE);
        counter++;
      }
 
      if (!val) {
        //SPI receive queue empty
        return SPI_RECV_Q_EMPTY_ERR;
      }

      //Check if receive queue is not OVERRUN (OV) in EVT register
      val = Drv::readBit(SPI_CTRL_EVT_REG, EVENT_OV);
      if (val) {
        //SPI receive queue received data when queue was full.
        //New data is discarded
        return SPI_RECV_Q_FULL_ERR;
      }
      
      //Read 1 word of data from RX register
      rx_val = Drv::readReg(SPI_RX_REG);
      
      /*Handle loading data from RX register to data_ptr for all configurations:
          Refer to p172 of GR712RC manual for official documentation
          on how the recieved bits are placed in the RX register
          depending on word size and reverse data mode*/
      if(m_word_len == 32)
      {
        U32* data_ptr_U32 = (U32*) data_ptr; 
        *data_ptr_U32 = (U32) rx_val;
      }
      else if(m_reverse_mode == 1 && m_word_len >= 4 && m_word_len <= 8)
      {
        U8* data_ptr_U8 = (U8*) data_ptr;
        *data_ptr_U8 = (U8)(rx_val >> 16);
      }
      else if(m_reverse_mode == 1 && m_word_len > 8 && m_word_len <= 16)
      {
        U16* data_ptr_U16 = (U16*) data_ptr;
        *data_ptr_U16 = (U16)(rx_val >> 16);
      }
      else if(m_reverse_mode == 0 && m_word_len >= 4 && m_word_len <= 8)
      {
        U8* data_ptr_U8 = (U8*) data_ptr;
        *data_ptr_U8 = (U8)(rx_val >> (16 - m_word_len));
      }
      else if(m_reverse_mode == 0 && m_word_len > 8 && m_word_len <= 16)
      {
        U16* data_ptr_U16 = (U16*) data_ptr;
        *data_ptr_U16 = (U16)(rx_val >> (16 - m_word_len));
      }
      else
      {
        //Invalid m_word_len error
        FW_ASSERT(false);
      }
      this->incrementPointer(data_ptr, data_ptr_size);
    }

    return 0;
  }
  I32 SPIDriverGenericComponentImpl ::  
    write(
        void *data_ptr,
        U8 data_ptr_size,
        U32 nWords,
        const U32 timeout_uS
    )
  {
    U32 val;
    U32 tx_val = 0; //value written to the TX register

    // Check input values for validity
    FW_ASSERT(data_ptr != NULL);
    FW_ASSERT(nWords < MAX_WORDS_PER_SPI_TRANSACTION);    
    FW_ASSERT(timeout_uS < SPI_MAX_TIMEOUT_USECS); 
    FW_ASSERT(data_ptr_size == SPI_U8_BUF_PTR 
           || data_ptr_size == SPI_U16_BUF_PTR
           || data_ptr_size == SPI_U32_BUF_PTR);


    //Check that data_ptr_size argument is consistent with m_word_len
    switch(data_ptr_size)
    {
      case SPI_U8_BUF_PTR:
        FW_ASSERT(m_word_len >= 4 && m_word_len <= 8);
        break;
      case SPI_U16_BUF_PTR:
        FW_ASSERT(m_word_len > 8 && m_word_len <= 16);
        break;
      case SPI_U32_BUF_PTR:
        FW_ASSERT(m_word_len == 32);
        break;
      default:
        FW_ASSERT(0);
        break;
    }   
    
    while (nWords > 0) {
      // Decrement first. If failure occurs then 
      // loop will return out
      
      nWords -= 1;

      //Set LST bit in CMD reg
      Drv::setBit(SPI_CMD_REG, CMD_LST);

      //Check if transmit queue is Not Full (NF) in EVT register
      val = Drv::readBit(SPI_CTRL_EVT_REG, EVENT_NF);
      if (!val) {
        //SPI transmit queue full
        return SPI_TX_Q_FULL_ERR;
      }
         
      /*Handle writing data from data_ptr to TX register for all configurations:
          Refer to p172 of GR712RC manual for official documentation
          on how the data to be sent are placed in the TX register
          depending on word size and reverse data mode*/
      if(m_word_len == 32)
      {
        tx_val = *( (U32*) data_ptr);
      }        
      else if(m_reverse_mode == 1 && m_word_len >= 4 && m_word_len <= 8)
      {
        U8 data = *( (U8*) data_ptr);
        tx_val = ((U32) data) << (32 - m_word_len);
      }
      else if(m_reverse_mode == 1 && m_word_len > 8 && m_word_len <= 16)
      {
        U16 data = *( (U16*) data_ptr);
        tx_val = ((U32) data) << (32 - m_word_len);
      }
      else if(m_reverse_mode == 0 && m_word_len >= 4 && m_word_len <= 8)
      {
        U8 data = *( (U8*) data_ptr);
        tx_val = (U32) data;
      }
      else if(m_reverse_mode == 0 && m_word_len > 8 && m_word_len <= 16)
      {
        U16 data = *( (U16*) data_ptr);
        tx_val = (U32) data;
      }
      else
      {
        //Invalid m_word_len error
        FW_ASSERT(false);
      }
      Drv::writeReg(SPI_TX_REG, tx_val);
     
      //Verify transfer is complete by 
      //waiting for TIP to go low or timeout using system time
      val = Drv::readBit(SPI_CTRL_EVT_REG, EVENT_TIP);

      Fw::Time increment(0, timeout_uS);
      Fw::Time now = this->getTime();
      Fw::Time target = Fw::Time::add(now, increment);

      U32 bound = SPI_COUNT_PER_USEC_OF_DELAY*timeout_uS;
      U32 counter = 0;
     
      while(val && (counter < bound)) 
      {	
	if(this->getTime() >= target)
        {
          break;
        } 
        val = Drv::readBit(SPI_CTRL_EVT_REG, EVENT_TIP);
        counter++;
      }
      if(val) 
      {
        return SPI_TX_TIMEOUT_ERR;
      } 

      //Check that the LT bit was set, verifying transfer is complete. 
      //If so write back 1 to that bit to clear it for the next transfer. 
      val = Drv::readBit(SPI_CTRL_EVT_REG, EVENT_LT);
      if (!val) {
        //SPI transfer not complete
        return SPI_TX_NOT_DONE_ERR;
      }
      Drv::setBit(SPI_CTRL_EVT_REG, EVENT_LT);
      
      this->incrementPointer(data_ptr, data_ptr_size);
    }
    return 0;  
  }
   
  void SPIDriverGenericComponentImpl ::
    resetSpiCore(void)
  {
    //Disable SPI Core to allow for modifying register
    Drv::clearBit(SPI_CTRL_MODE_REG, MODE_EN);
    //Enable SPI Core
    Drv::setBit(SPI_CTRL_MODE_REG, MODE_EN); 
  }

  Fw::Time SPIDriverGenericComponentImpl ::
    getTime()
  {
    Fw::Time _time;
    this->timeCaller_out(0, _time);
    return _time;
  }


} // end namespace Drv
