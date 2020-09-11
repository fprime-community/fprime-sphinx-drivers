// ====================================================================== 
// \title  FpgaGpioDriverImpl.cpp
// \author vwong
// \brief  cpp file for FpgaGpioDriver component implementation class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
// ====================================================================== 


#include <fprime-sphinx-drivers/FpgaGpioDriver/FpgaGpioDriverComponentImpl.hpp>
#include <fprime-sphinx-drivers/Util/SphinxDrvIntUtil.hpp>
#include "Fw/Types/BasicTypes.hpp"
#include "Fw/Types/Assert.hpp"

namespace Drv {

  // ----------------------------------------------------------------------
  // Construction, initialization, and destruction 
  // ----------------------------------------------------------------------

  FpgaGpioDriverComponentImpl ::
#if FW_OBJECT_NAMES == 1
    FpgaGpioDriverComponentImpl(
        const char *const compName,
        NATIVE_UINT_TYPE total_avail_pins,
        NATIVE_UINT_TYPE pin_nums[],
        NATIVE_UINT_TYPE n_pin_nums
    ) :
      FpgaGpioDriverComponentBase(compName),
#else
    FpgaGpioDriverImpl(
      NATIVE_UINT_TYPE total_avail_pins,
      NATIVE_UINT_TYPE pin_nums[],
      NATIVE_UINT_TYPE n_pin_nums
    ) :
#endif
      m_totalAvailPins(total_avail_pins),
      m_numPinsToEnable(n_pin_nums)
  {
    // save parameters
    for (U32 i = 0; i < n_pin_nums; i++) {
      this->m_pinsToEnable[i] = pin_nums[i];
    }
  }

  void FpgaGpioDriverComponentImpl ::
    init(
        const NATIVE_INT_TYPE instance
    ) 
  {
    FpgaGpioDriverComponentBase::init(instance);

    // perform asserts and actions in init
    FW_ASSERT(this->m_totalAvailPins <= FPGA_GPIO_MAX_NUM_PINS);
    for (U32 i = 0; i < this->m_numPinsToEnable; i++) {
      this->enablePin(this->m_pinsToEnable[i]);
    }
  }

  FpgaGpioDriverComponentImpl ::
    ~FpgaGpioDriverComponentImpl(void)
  {

  }

  // ----------------------------------------------------------------------
  // Handler implementations for user-defined typed input ports
  // ----------------------------------------------------------------------

  I32 FpgaGpioDriverComponentImpl ::
    setPin_handler(
        const NATIVE_INT_TYPE portNum,
        U32 pin_num
    )
  {
    U32 read_val;
    U32 i;

    FW_ASSERT(pin_num < this->m_totalAvailPins);

#if defined(BUILD_SPHINX)
    Drv::setBit(FPGA_GPIO_REG_ADDR, pin_num);
#endif

    for(i=0; i<FPGA_GPIO_MAX_LOOPS; i++) {
      // Verify pin state by read-back
      read_val = this->readPin(pin_num);
      if (read_val == 1) {
        // Pin set successfully
        return 0;
      }
    }    

    // Failed to set pin successfully
    return -1;
  }

  I32 FpgaGpioDriverComponentImpl ::
    clearPin_handler(
        const NATIVE_INT_TYPE portNum,
        U32 pin_num
    )
  {
    U32 read_val;
    U32 i;

    FW_ASSERT(pin_num < this->m_totalAvailPins);

#if defined(BUILD_SPHINX)
    Drv::clearBit(FPGA_GPIO_REG_ADDR, pin_num);
#endif

    // Verify pin state by read-back
    for(i=0; i<FPGA_GPIO_MAX_LOOPS; i++) {
      // Verify pin state by read-back
      read_val = this->readPin(pin_num);
      if (read_val == 0) {
        // Pin cleared successfully
        return 0;
      }
    }    

    // Failed to clear pin successfully
    return -1;
  }

  U32 FpgaGpioDriverComponentImpl ::
    readPin(
        U32 pin_num
    )
  {
    FW_ASSERT(pin_num < this->m_totalAvailPins);

    U32 val = 0;

#if defined(BUILD_SPHINX)
    val = Drv::readBit(FPGA_GPIO_REG_ADDR, pin_num);
#endif

    return val;
  }

  U32 FpgaGpioDriverComponentImpl ::
    readPin_handler(
        const NATIVE_INT_TYPE portNum,
        U32 pin_num
    )
  {
    U32 val;

    val = this->readPin(pin_num);    

    return val;
  }

  I32 FpgaGpioDriverComponentImpl ::
    enablePin_handler(
        const NATIVE_INT_TYPE portNum,
        U32 pin_num
    )
  {
    this->enablePin(pin_num);
    return 0;
  }

  I32 FpgaGpioDriverComponentImpl ::
    disablePin_handler(
        const NATIVE_INT_TYPE portNum,
        U32 pin_num
    )
  {
    this->disablePin(pin_num);
    return 0;
  }

  // ----------------------------------------------------------------------
  // Private supporting functions
  // ----------------------------------------------------------------------

  void FpgaGpioDriverComponentImpl ::
    enablePin(
        U32 pin
    )
  {
    FW_ASSERT(pin < this->m_totalAvailPins);

#if defined(BUILD_SPHINX)
    Drv::setBit(FPGA_GPIO_REG_ADDR, pin + this->m_totalAvailPins);
#endif
  }

  void FpgaGpioDriverComponentImpl ::
    disablePin(
        U32 pin
    )
  {
    FW_ASSERT(pin < this->m_totalAvailPins);

#if defined(BUILD_SPHINX)
    Drv::clearBit(FPGA_GPIO_REG_ADDR, pin + this->m_totalAvailPins);
#endif
  }

} // end namespace Drv
