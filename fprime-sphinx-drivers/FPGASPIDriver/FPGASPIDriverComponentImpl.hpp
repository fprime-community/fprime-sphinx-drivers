// ====================================================================== 
// \title  FPGASPIDriverImpl.hpp
// \author mstarch
// \brief  hpp file for FPGASPIDriver component implementation class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
// ====================================================================== 

#ifndef FPGASPIDriver_HPP
#define FPGASPIDriver_HPP

#include "fprime-sphinx-drivers/FPGASPIDriver/FPGASPIDriverComponentAc.hpp"

//Memory map for SPI is only valid on SPHINX
#if defined(BUILD_SPHINX)
    #define FPGA_SPI_1_BASE_ADDRESS 0x200A0000
    #define FPGA_SPI_2_BASE_ADDRESS 0x200B0000
    #define FPGA_SPI_3_BASE_ADDRESS 0x200C0000
#endif
#define FPGA_SPI_1_NUMBER 1
#define FPGA_SPI_2_NUMBER 2
#define FPGA_SPI_3_NUMBER 3

#define FPGA_SPI_TRANSFER_REG_OFFSET 0x4
#define FPGA_SPI_DATA_REG_OFFSET 0x8

#define FPGA_SPI_BITRATE_10_MBS 0
#define FPGA_SPI_BITRATE_2_5_MBS 1
#define FPGA_SPI_BITRATE_1_25_MBS 2
#define FPGA_SPI_BITRATE_0_769_MBS 3

//Different bit widths for SPI devices
#define FPGA_SPI_WIDTH_8  1
#define FPGA_SPI_WIDTH_16 2

//Borrowed from SPI driver
#define FPGA_SPI_MAX_BYTES_PER_TRANSACTION (100*1024*1024) /* 100 MB */
#define FPGA_SPI_MAX_SLAVE_SELECT 7 /* Slaves 0 - 7 */

#define FPGA_SPI_LSB_FIRST 0
#define FPGA_SPI_MSB_FIRST 1

#define FPGA_SPI_CLOCKRATE_BIT_SHIFT 24
#define FPGA_SPI_BIT_ORDER_SHIFT 16
#define FPGA_SPI_START_TRANSFER_SHIFT 0
#define FPGA_SPI_READ_BYTE_SHIFT 16

#define FPGA_SPI_TRANSFER_FINISHED_BIT 31

#define FPGA_SPI_ER_TIMEOUT 1
#define FPGA_SPI_OK 0

#define FPGA_SPI_BITS_PER_BYTE 8

// NB: assumes a <100 MHz processor
#define FPGA_SPI_CNT_PER_USEC_OF_DELAY 100

namespace Drv {

  class FPGASPIDriverComponentImpl :
    public FPGASPIDriverComponentBase
  {

    public:

      // ----------------------------------------------------------------------
      // Construction, initialization, and destruction
      // ----------------------------------------------------------------------

      //! Construct object FPGASPIDriver
      //!
      FPGASPIDriverComponentImpl(
#if FW_OBJECT_NAMES == 1
          const char *const compName, //!< The component name
#endif
          U32 spiNumber,
          U32 spiWidth
      );

      //! Initialize object FPGASPIDriver
      //!
      void init(
          const NATIVE_INT_TYPE instance = 0 //!< The instance number
      );

      //! Destroy object FPGASPIDriver
      //!
      ~FPGASPIDriverComponentImpl(void);

    PRIVATE:
      U32 m_baseAddress;
      U32 m_spiWidth;
      // ----------------------------------------------------------------------
      // Handler implementations for user-defined typed input ports
      // ----------------------------------------------------------------------

      //! Handler implementation for read_write
      //!
      I32 read_write_handler(
          const NATIVE_INT_TYPE portNum, //!< The port number
          U8 *write_buf_ptr, 
          U8 *read_buf_ptr, 
          U32 nBytes, 
          U8 activate_slave, 
          U16 timeout, 
          U8 clock_bitrate, 
          U8 bit_order ,
          U32 delay
      );

      // ----------------------------------------------------------------------
      // Helper functions
      // ----------------------------------------------------------------------

      I32 write_read_byte(
              U8 *write_byte_ptr,
              U8 *read_byte_ptr,
              U16 timeout
          );

      void busy_wait(
              U32 usecs
          );

      Fw::Time getTime(void);

    };

} // end namespace Drv

#endif
