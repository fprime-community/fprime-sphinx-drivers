// ======================================================================
// \title  SphinxUartOnboardDriverImpl.hpp
// \author muellerd
// \brief  hpp file for SphinxUartOnboardDriver component implementation class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
// ======================================================================
/** \file SphinxUartOnboardDriverImpl.hpp */

#ifndef SphinxUartOnboardDriver_HPP
#define SphinxUartOnboardDriver_HPP

#include <fprime-sphinx-drivers/GPIOInterruptHandler/GPIOInterruptHandler.hpp>
#include "fprime-sphinx-drivers/SphinxUartOnboardDriver/SphinxUartOnboardDriverComponentAc.hpp"
#include <Fw/Types/BasicTypes.hpp>

#ifdef TGT_OS_TYPE_VXWORKS
extern "C" {
#include <intLib.h>
#include <iv.h>
}
#endif


//------------------------
// User Configuration
//------------------------
#define MAX_PURGE_CNT   1000
#define READ_BUF_SIZE   4096 //TODO: pass in for constructor argument
#define RX_FIFO_SZ      8


//------------------------
// Misc Defines
//------------------------
#define MEGA_FACTOR     1000000

 // INT_MASK's are decimel bit offsets
#define UART0_IVEC_NUM      2
#define UART1_IVEC_NUM      17
#define UART2_INT_BIT_NUM   0
#define UART3_INT_BIT_NUM   1
#define UART4_IVEC_NUM      20
#define UART5_IVEC_NUM      21
#define UART6_INT_BIT_NUM   2
#define UART7_INT_BIT_NUM   3


//------------------------
// Baud Rates
//------------------------
#define BAUD_2400       2400
#define BAUD_4800       4800
#define BAUD_9600       9600
#define BAUD_19200      19200
#define BAUD_38500      38500
#define BAUD_57600      57600
#define BAUD_115200     115200
#define BAUD_1000000    1000000
#define BAUD_RX_MIN     BAUD_2400
#define BAUD_RX_MAX     230400
#define BAUD_TX_MIN     BAUD_4800
#define BAUD_TX_MAX     2500000
#define BAUD_DEFAULT    BAUD_115200

#define REG_BAUD_2400           0x0
#define REG_BAUD_4800           0x1
#define REG_BAUD_9600           0x2
#define REG_BAUD_19200          0x3
#define REG_BAUD_38500          0x4
#define REG_BAUD_57600          0x5
#define REG_BAUD_115200         0x6
#define REG_BAUD_1000000        0x7


//------------------------
// Register/Offsets
//------------------------
#define REG_PORT_0              0x80000100
#define REG_PORT_1              0x80100100
#define REG_PORT_2              0x20160000
#define REG_PORT_3              0x20170000
#define REG_PORT_4              0x80100400
#define REG_PORT_5              0x80100500
#define REG_PORT_6              0x20180000
#define REG_PORT_7              0x20190000
#define REG_FW_INT              0x20020004

#define REG_OFF_HW_DATA         0x00
#define REG_OFF_HW_STATUS       0x04
#define REG_OFF_HW_CONTROL      0x08
#define REG_OFF_HW_SCALER       0x0C
#define REG_OFF_HW_FIFO_DEBUG   0x10

#define REG_OFF_FW_CONTROL      0x00    //control register
#define REG_OFF_FW_STATUS       0x04    //status register
#define REG_OFF_FW_BAUD_RATE    0x08    //baud rate register
#define REG_OFF_FW_N_BYTES      0x0C    //number of bytes in the RX fifo
#define REG_OFF_FW_TX_PORT      0x10    //tx data port
#define REG_OFF_FW_RX_PORT      0x14    //rx data port



//---------------------
// Hardware/Firmware Bits
//---------------------
#define HW_CTRL_ENABLE_RX       (0x1 << 0)
#define HW_CTRL_ENABLE_TX       (0x1 << 1)
#define HW_CTRL_RX_INT          (0x1 << 2)
#define HW_CTRL_TX_INT          (0x1 << 3)
#define HW_CTRL_SELECT_PARITY   (0x1 << 4)
#define HW_CTRL_ENABLE_PARITY   (0x1 << 5)
#define HW_CTRL_FLOW_CONTROL    (0x1 << 6)
#define HW_CTRL_LOOP_BACK       (0x1 << 7)
#define HW_CTRL_FIFO_TX_INT     (0x1 << 9)
#define HW_CTRL_FIFO_RX_INT     (0x1 << 10)
#define HW_CTRL_DISABLE         0x0


#define HW_STAT_DR              (0x1 << 0) // Data ready
#define HW_STAT_TS              (0x1 << 1) // Transmitter shift register empty
#define HW_STAT_TE              (0x1 << 2) // Transmitter empty
#define HW_STAT_BR              (0x1 << 3)
#define HW_STAT_OV              (0x1 << 4) // Overrun
#define HW_STAT_PE              (0x1 << 5) // Parity error
#define HW_STAT_FE              (0x1 << 6) // Framing error
#define HW_STAT_TH              (0x1 << 7) // Transmitter FIFO half full
#define HW_STAT_RH              (0x1 << 8) // Receiver FIFO half full
#define HW_STAT_TF              (0x1 << 9) // Transmitter FIFO full
#define HW_STAT_RF              (0x1 << 10) // Receiver FIFO full
#define HW_STAT_TCNT            (0x3F00000)       // # data frames in TX FIFO
#define HW_STAT_RCNT            (0xFC000000)      // # data frames in RX FIFO
#define HW_STAT_ERROR           (HW_STAT_PE | \
                                HW_STAT_FE  | \
                                HW_STAT_OV)  // Error mask


#define FW_CTRL_TRIGGER_READ    (0x1 << 0)
#define FW_CTRL_TRIGGER_WRITE   (0x1 << 1)
#define FW_CTRL_ENABLE_RX       (0x1 << 2)
#define FW_CTRL_DISABLE_RX      0x0

#define FW_STAT_RX              (0x1 << 0)
#define FW_STAT_TF              (0x1 << 1)
#define FW_STAT_RE              (0x1 << 2)


namespace Drv {

  class SphinxUartOnboardDriverComponentImpl :
    public SphinxUartOnboardDriverComponentBase, public GPIOInterruptHandler
  {

    public:

      // ----------------------------------------------------------------------
      // Construction, initialization, and destruction
      // ----------------------------------------------------------------------

      // Construct object SphinxUartOnboardDriver
      SphinxUartOnboardDriverComponentImpl(
#if FW_OBJECT_NAMES == 1
          const char *const compName	// Component name
#endif
      );
      // Initialize object SphinxUartOnboardDriver
      void init(
          const NATIVE_INT_TYPE instance = 0 // Instance number
      );

      // Destroy object SphinxUartOnboardDriver
      ~SphinxUartOnboardDriverComponentImpl(void);


      void init_comp(
        U8 portNum,                     // UART port to use
        U32 baudRate,                   // Transceive rate
        U32 clockSpeed,                 // Processor clock speed (MegaHertz)
        U32 flag = 0                    // If set, prevents interrupts. By default is 0 for VxWorks
      );


      void lock_read_fifo(void);
      void HandleGPIOInterrupt(void);

      enum IOErrorBit {
        IOErrorBit_OK =             0x0,
        IOErrorBit_PARITY =        (0x1 << 31) | (0x1 << 0), // Parity bit in status register
        IOErrorBit_FRAMING =       (0x1 << 31) | (0x1 << 1), // Framing bit in status register
        IOErrorBit_TIMEOUT =       (0x1 << 31) | (0x1 << 2), // IO timout, as described in the SDD
        IOErrorBit_OVERFLOW =      (0x1 << 31) | (0x1 << 3), // Overflow bit in the stat
        IOErrorBit_RX_TRIGGER =    (0x1 << 31) | (0x1 << 4), // Incorrect receive strobe bit
        IOErrorBit_TX_TRIGGER =    (0x1 << 31) | (0x1 << 5)  // Incorrect transmit
      };

    PRIVATE:

      // ----------------------------------------------------------------------
      // Methods
      // ----------------------------------------------------------------------



      /**
      * Return true if receive FIFO device is empty
      *
      * Side effect: calls pull_status()
      */
      bool is_rx_empty(void);


      /**
      * Dequeue 1 byte from the read FIFO device
      *
      * If successful, the most significant bit will be 0, and the least
      * significant 8 bits will contain the data. If an error occurs,
      * the most significant bit will 1, and the least significant bits will
      * indicate what combination of errors occured. See IOErrorBit enum.
      */
      U32 pull_byte(void);


      /**
       * Return 0 if no receive error was detected. If an error occurs, the most
       * significant bit will 1, and the least significant bits will indicate
       * what combination of errors occured. See IOErrorBit enum.
       *
       * Side effect: calls pull_status()
       */
      U32 has_rx_error(void);


      /**
       * Clear all errors from the status register
       */
      void clear_errors(void);


      /**
       * Enqueue 1 byte to the write FIFO device
       */
      void push_byte(const U8 bits);


      /**
       * Set the control register bits
       */
      void push_control(const U32 bits);


      /**
       * Reads the status register bits
       *
       * Returns the bits retrieved from the register.
       */
      U32 pull_status(void);

      /**
       * Set bits in the status register
       *
       * Used for clearing errors
       */
      //prevents clearing bit on Linux build that would cause infinite loops
      void push_status(const U32 bits, U32 flag=0);

 
      /**
       * Return true if new data is available in the read FIFO
       *
       * Side effect: calls pull_status()
       */
      bool is_data_ready(void);


      /**
       * Return true if transmit FIFO device is empty
       *
       * Side effect: calls pull_status()
       */
      bool is_tx_empty(void);


      /**
       * Return true if no more space is available in the transmit FIFO device
       *
       * Side effect: calls pull_status()
       */
      bool is_tx_full(void);


      /**
       * If enable is true, enables the receiver. Otherwise, disables the
       * receiver.
      */
      void set_rx_enable(const bool enable);


      /**
       * If enable is true, enables the transmitter. Otherwise, disables the
       * receiver.
       *
       * Returns 0 if successful. If an error is detected, returns a negative
       * number, where the least significant bits indicate what combination of
       * errors occured. See IOErrorBit enum.
       */
      void set_tx_enable(const bool enable);



      void read_fifo(void);

      void setup_port(U8 portNum);

      void setup_interrupts(U8 portNum);

      void set_baud_rate(U32 clockSpeed, U32 baudRate);

      void purge_fifos();

      void EnableFWInterrupt(U32 intNum);

      // ----------------------------------------------------------------------
      // Handler implementations for user-defined typed input ports
      // ----------------------------------------------------------------------


      // Handler implementation for bytesAvail
      U32 bytesUsed_handler(
        const NATIVE_INT_TYPE portNum  // Port number
      );


      // Implementation for read handler
      I32 read_handler(
          NATIVE_INT_TYPE portNum,  // Port number
          U8 *read_buf_ptr,         // Pointer to read buffer
          U32 nBytes,               // Number of bytes to read from buffer
          U32 timeout               // Timeout in micro-seconds
      );


      // Implementation for write handler
      I32 write_handler(
          NATIVE_INT_TYPE portNum,  // Port number
          U8 *write_buf_ptr,        // Pointer to write buffer
          U32 nBytes,               // Number of bytes to write to buffer
          U32 timeout               // Timeout in micro-seconds
      );


      // ----------------------------------------------------------------------
      // Members
      // ----------------------------------------------------------------------

      enum HwStatusPostInit {
        HwStatusPostInit_DR = 0, // Data ready
        HwStatusPostInit_TS = 1, // Transmitter shift register empty
        HwStatusPostInit_TE = 1, // Transmitter empty
        HwStatusPostInit_TH = 0, // Transmitter FIFO half full
        HwStatusPostInit_RH = 1, // Receiver FIFO half full
        HwStatusPostInit_TF = 0, // Transmitter FIFO full
        HwStatusPostInit_RF = 0, // Receiver FIFO full
      };

      enum RegisterType {
        RegisterType_HARDWARE = 1,
        RegisterType_FIRMWARE = 2
      };

      U8 m_read_buf[READ_BUF_SIZE]; // Circular buffer
      volatile U32 m_read_buf_wp;   // Index into write location of m_read_buf
      volatile U32 m_read_buf_rp;   // Index into read location of m_read_buf
      U32 m_control;                // To control register
      U32 m_address;                // Register memory address
      RegisterType m_registerType;  // Register type: hardware or firmware

    };

    void UARTHWintHandler
    #ifdef TGT_OS_TYPE_VXWORKS
      (I32 arg);
    #else 
      (I64 arg);
    #endif

} // end namespace Drv

#endif
