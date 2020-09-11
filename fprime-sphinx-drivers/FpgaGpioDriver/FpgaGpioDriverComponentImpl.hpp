// ======================================================================
// \title  FpgaGpioDriverImpl.hpp
// \author vwong
// \brief  hpp file for FpgaGpioDriver component implementation class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
// ======================================================================

#ifndef FpgaGpioDriver_HPP
#define FpgaGpioDriver_HPP

#include "fprime-sphinx-drivers/FpgaGpioDriver/FpgaGpioDriverComponentAc.hpp"

// MAX_AVAIL_PINS == 16, because there is only one FPGA GPIO register, which
// houses both the signal pins and the enable pins
#define FPGA_GPIO_MAX_NUM_PINS 16
#define FPGA_GPIO_REG_ADDR 0x20030000
#define FPGA_GPIO_MAX_LOOPS 10

namespace Drv {

  class FpgaGpioDriverComponentImpl :
    public FpgaGpioDriverComponentBase
  {

    public:

      // ----------------------------------------------------------------------
      // Construction, initialization, and destruction
      // ----------------------------------------------------------------------

      //! Construct object FpgaGpioDriver
      //!
      FpgaGpioDriverComponentImpl(
#if FW_OBJECT_NAMES == 1
          const char *const compName, //!< The component name
          NATIVE_UINT_TYPE total_avail_pins,
          NATIVE_UINT_TYPE pin_nums[],
          NATIVE_UINT_TYPE n_pin_nums
#else
          NATIVE_UINT_TYPE total_avail_pins,
          NATIVE_UINT_TYPE pin_nums[],
          NATIVE_UINT_TYPE n_pin_nums
#endif
      );

      //! Initialize object FpgaGpioDriver
      //!
      void init(
          const NATIVE_INT_TYPE instance = 0 //!< The instance number
      );

      //! Destroy object FpgaGpioDriver
      //!
      ~FpgaGpioDriverComponentImpl(void);

    PRIVATE:

      // ----------------------------------------------------------------------
      // Handler implementations for user-defined typed input ports
      // ----------------------------------------------------------------------

      //! Handler implementation for setPin
      //!
      I32 setPin_handler(
          const NATIVE_INT_TYPE portNum, //!< The port number
          U32 pin_num
      );

      //! Handler implementation for clearPin
      //!
      I32 clearPin_handler(
          const NATIVE_INT_TYPE portNum, //!< The port number
          U32 pin_num
      );

      U32 readPin(U32 pin_num);

      //! Handler implementation for readPin
      //!
      U32 readPin_handler(
          const NATIVE_INT_TYPE portNum, //!< The port number
          U32 pin_num
      );

      //! Handler implementation for enablePin
      //!
      I32 enablePin_handler(
          const NATIVE_INT_TYPE portNum, //!< The port number
          U32 pin_num
      );

      //! Handler implementation for disablePin
      //!
      I32 disablePin_handler(
          const NATIVE_INT_TYPE portNum, //!< The port number
          U32 pin_num
      );

    PRIVATE: //methods

      void enablePin(U32 pin);
      void disablePin(U32 pin);

    PRIVATE: //members

      // parameters
      const U32 m_totalAvailPins;
      U32 m_pinsToEnable[FPGA_GPIO_MAX_NUM_PINS];
      const U32 m_numPinsToEnable;

    };

} // end namespace Drv

#endif
