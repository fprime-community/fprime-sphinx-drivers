// ====================================================================== 
// \title  FPGASPIDriverImpl.cpp
// \author mstarch
// \brief  cpp file for FPGASPIDriver component implementation class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
// ====================================================================== 


#include <fprime-sphinx-drivers/FPGASPIDriver/FPGASPIDriverComponentImpl.hpp>
#include <fprime-sphinx-drivers/Util/SphinxDrvUtil.hpp>
#include "Fw/Types/BasicTypes.hpp"
#include "Fw/Types/Assert.hpp"
extern "C" {
    #include <string.h>
}
namespace Drv {

  // ----------------------------------------------------------------------
  // Construction, initialization, and destruction 
  // ----------------------------------------------------------------------

  FPGASPIDriverComponentImpl ::
#if FW_OBJECT_NAMES == 1
    FPGASPIDriverComponentImpl(
        const char *const compName,
        U32 spiNumber,
        U32 spiWidth
    ) :
      FPGASPIDriverComponentBase(compName)
#else
    FPGASPIDriverImpl(U32 spiNumber, U32 spiWidth)
#endif
  {
      FW_ASSERT(spiWidth == FPGA_SPI_WIDTH_16 || spiWidth == FPGA_SPI_WIDTH_8);
      FW_ASSERT(spiNumber >= FPGA_SPI_1_NUMBER && spiNumber <= FPGA_SPI_3_NUMBER);
      this->m_baseAddress = 0;
      this->m_spiWidth = spiWidth;
#if defined(BUILD_SPHINX)
      switch (spiNumber) {
          case FPGA_SPI_1_NUMBER:
              this->m_baseAddress = FPGA_SPI_1_BASE_ADDRESS;
              break;
          case FPGA_SPI_2_NUMBER:
              this->m_baseAddress = FPGA_SPI_2_BASE_ADDRESS;
              break;
          case FPGA_SPI_3_NUMBER:
              this->m_baseAddress = FPGA_SPI_3_BASE_ADDRESS;
              break;
          default:
              FW_ASSERT(spiNumber >= FPGA_SPI_1_NUMBER && spiNumber <= FPGA_SPI_3_NUMBER);
      }
#endif
  }

  void FPGASPIDriverComponentImpl ::
    init(
        const NATIVE_INT_TYPE instance
    ) 
  {
    FPGASPIDriverComponentBase::init(instance);
  }

  FPGASPIDriverComponentImpl ::
    ~FPGASPIDriverComponentImpl(void)
  {

  }

  // ----------------------------------------------------------------------
  // Handler implementations for user-defined typed input ports
  // ----------------------------------------------------------------------

  I32 FPGASPIDriverComponentImpl ::
    read_write_handler(
        const NATIVE_INT_TYPE portNum,
        U8 *write_buf_ptr,
        U8 *read_buf_ptr,
        U32 nBytes,
        U8 activate_slave,
        U16 timeout,
        U8 clock_bitrate,
        U8 bit_order,
        U32 delay
    )
  {
    I32 status = 0;
    U32 i = 0;
    FW_ASSERT(activate_slave <= FPGA_SPI_MAX_SLAVE_SELECT);
    FW_ASSERT(write_buf_ptr != NULL);
    FW_ASSERT(read_buf_ptr != NULL);
    FW_ASSERT(nBytes < FPGA_SPI_MAX_BYTES_PER_TRANSACTION);
    FW_ASSERT(clock_bitrate == FPGA_SPI_BITRATE_0_769_MBS ||
              clock_bitrate == FPGA_SPI_BITRATE_10_MBS ||
              clock_bitrate == FPGA_SPI_BITRATE_2_5_MBS ||
              clock_bitrate == FPGA_SPI_BITRATE_1_25_MBS);
    FW_ASSERT(bit_order == FPGA_SPI_MSB_FIRST ||
              bit_order == FPGA_SPI_LSB_FIRST);
    FW_ASSERT(delay < 1000000);
#if defined(BUILD_SPHINX)
    //Setup for this transaction
    U8 ssMask = ((U8)1) << activate_slave;
    U32 setupValue = (((U32)clock_bitrate) << FPGA_SPI_CLOCKRATE_BIT_SHIFT) |
                     (((U32)bit_order) << FPGA_SPI_BIT_ORDER_SHIFT) |
                     ((U32)ssMask);
    Drv::writeReg(this->m_baseAddress, setupValue);
#endif
    //Loop through and write all the bytes, read all the bytes
    FW_ASSERT(m_spiWidth > 0);
    const U32 incr = this->m_spiWidth;
    for (i = 0; i < nBytes; i = i + incr) {
        status = this->write_read_byte(write_buf_ptr+i, read_buf_ptr+i, timeout);
        if (status == FPGA_SPI_ER_TIMEOUT) {
            break;
        }
        if (delay > 0 && i + incr < nBytes) {
          busy_wait(delay);
        }
    }
#if defined(BUILD_SPHINX)
    //Turn off any active slave
    Drv::writeRegPartial(this->m_baseAddress, 0, FPGA_SPI_BITS_PER_BYTE, 0);
#endif
    return status;
  }
  I32 FPGASPIDriverComponentImpl ::
    write_read_byte(
        U8 *write_byte_ptr,
        U8 *read_byte_ptr,
        U16 timeout
    )
  {
    //NULL is a nonsense value representing a problem within the driver logic
    FW_ASSERT(write_byte_ptr != NULL);
    FW_ASSERT(read_byte_ptr != NULL);
#if defined(BUILD_SPHINX)
    U32 timer = 0;
    U32 writeVal = 0;
    U32 size =  sizeof(U8);
    U16 readVal = 0;
    if (this->m_spiWidth == FPGA_SPI_WIDTH_16) {
        size = sizeof(U16);
        writeVal = ((U32)write_byte_ptr[0] << 8) | ((U32)write_byte_ptr[1]);
    } else {
        writeVal = (U32) *(write_byte_ptr);
    }
    Drv::writeReg(this->m_baseAddress + FPGA_SPI_DATA_REG_OFFSET, writeVal);
    Drv::writeReg(this->m_baseAddress + FPGA_SPI_TRANSFER_REG_OFFSET,
             ((U32)1) << FPGA_SPI_START_TRANSFER_SHIFT);
    //Busy wait
    while (Drv::readBit(this->m_baseAddress + FPGA_SPI_TRANSFER_REG_OFFSET,
                   FPGA_SPI_TRANSFER_FINISHED_BIT) != 1 && timer < timeout) {
           timer++;
    }
    //Timeout failed
    if (timer >= timeout) {
        return FPGA_SPI_ER_TIMEOUT;
    }
    readVal = (U16)(Drv::readReg(this->m_baseAddress + FPGA_SPI_DATA_REG_OFFSET) >> FPGA_SPI_READ_BYTE_SHIFT);
    if (this->m_spiWidth == FPGA_SPI_WIDTH_16) {
        memcpy(read_byte_ptr, &readVal, sizeof(U16));
    } else {
        *read_byte_ptr = (U8)(readVal & 0xFF);
    }
#endif
    return 0;
  }

  void FPGASPIDriverComponentImpl ::
    busy_wait(
        U32 usecs
    )
  {
    FW_ASSERT(usecs < 1000000);
    Fw::Time increment(0, usecs);
    Fw::Time now = this->getTime();
    Fw::Time target = Fw::Time::add(now, increment);
    U32 bound = FPGA_SPI_CNT_PER_USEC_OF_DELAY * usecs;
    U32 counter;
    for (counter = 0; counter < bound; counter++) {
      if (this->getTime() >= target) {
        break;
      }
    }
    FW_ASSERT(counter < bound);
  }

  Fw::Time FPGASPIDriverComponentImpl ::
    getTime()
  {
    Fw::Time _time;
    this->Time_out(0, _time);
    return _time;
  }

} // end namespace Drv
