// ======================================================================
// \title  GPIODriver/test/ut/TesterBase.cpp
// \author Auto-generated
// \brief  cpp file for GPIODriver component test harness base class
//
// \copyright
// Copyright 2009-2016, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
// ======================================================================

#include <stdlib.h>
#include <string.h>
#include "TesterBase.hpp"

namespace Drv {

  // ----------------------------------------------------------------------
  // Construction, initialization, and destruction
  // ----------------------------------------------------------------------

  GPIODriverTesterBase ::
    GPIODriverTesterBase(
#if FW_OBJECT_NAMES == 1
        const char *const compName,
        const U32 maxHistorySize
#else
        const U32 maxHistorySize
#endif
    ) :
#if FW_OBJECT_NAMES == 1
      Fw::PassiveComponentBase(compName)
#else
      Fw::PassiveComponentBase()
#endif
  {
  }

  GPIODriverTesterBase ::
    ~GPIODriverTesterBase(void) 
  {
  }

  void GPIODriverTesterBase ::
    init(
        const NATIVE_INT_TYPE instance
    )
  {

    // Initialize base class

		Fw::PassiveComponentBase::init(instance);

    // Initialize output port gpio_readPin

    for (
        NATIVE_INT_TYPE _port = 0;
        _port < this->getNum_to_gpio_readPin();
        ++_port
    ) {
      this->m_to_gpio_readPin[_port].init();

#if FW_OBJECT_NAMES == 1
      char _portName[80];
      snprintf(
          _portName,
          sizeof(_portName),
          "%s_to_gpio_readPin[%d]",
          this->m_objName,
          _port
      );
      this->m_to_gpio_readPin[_port].setObjName(_portName);
#endif

    }

    // Initialize output port gpio_setPin

    for (
        NATIVE_INT_TYPE _port = 0;
        _port < this->getNum_to_gpio_setPin();
        ++_port
    ) {
      this->m_to_gpio_setPin[_port].init();

#if FW_OBJECT_NAMES == 1
      char _portName[80];
      snprintf(
          _portName,
          sizeof(_portName),
          "%s_to_gpio_setPin[%d]",
          this->m_objName,
          _port
      );
      this->m_to_gpio_setPin[_port].setObjName(_portName);
#endif

    }

    // Initialize output port gpio_clearPin

    for (
        NATIVE_INT_TYPE _port = 0;
        _port < this->getNum_to_gpio_clearPin();
        ++_port
    ) {
      this->m_to_gpio_clearPin[_port].init();

#if FW_OBJECT_NAMES == 1
      char _portName[80];
      snprintf(
          _portName,
          sizeof(_portName),
          "%s_to_gpio_clearPin[%d]",
          this->m_objName,
          _port
      );
      this->m_to_gpio_clearPin[_port].setObjName(_portName);
#endif

    }

  }

  // ----------------------------------------------------------------------
  // Getters for port counts
  // ----------------------------------------------------------------------

  NATIVE_INT_TYPE GPIODriverTesterBase ::
    getNum_to_gpio_readPin(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_to_gpio_readPin);
  }

  NATIVE_INT_TYPE GPIODriverTesterBase ::
    getNum_to_gpio_setPin(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_to_gpio_setPin);
  }

  NATIVE_INT_TYPE GPIODriverTesterBase ::
    getNum_to_gpio_clearPin(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_to_gpio_clearPin);
  }

  // ----------------------------------------------------------------------
  // Connectors for to ports 
  // ----------------------------------------------------------------------

  void GPIODriverTesterBase ::
    connect_to_gpio_readPin(
        const NATIVE_INT_TYPE portNum,
        Drv::InputSphinxGPIO_ReadPinPort *const gpio_readPin
    ) 
  {
    FW_ASSERT(portNum < this->getNum_to_gpio_readPin(),static_cast<AssertArg>(portNum));
    this->m_to_gpio_readPin[portNum].addCallPort(gpio_readPin);
  }

  void GPIODriverTesterBase ::
    connect_to_gpio_setPin(
        const NATIVE_INT_TYPE portNum,
        Drv::InputSphinxGPIO_WritePinPort *const gpio_setPin
    ) 
  {
    FW_ASSERT(portNum < this->getNum_to_gpio_setPin(),static_cast<AssertArg>(portNum));
    this->m_to_gpio_setPin[portNum].addCallPort(gpio_setPin);
  }

  void GPIODriverTesterBase ::
    connect_to_gpio_clearPin(
        const NATIVE_INT_TYPE portNum,
        Drv::InputSphinxGPIO_WritePinPort *const gpio_clearPin
    ) 
  {
    FW_ASSERT(portNum < this->getNum_to_gpio_clearPin(),static_cast<AssertArg>(portNum));
    this->m_to_gpio_clearPin[portNum].addCallPort(gpio_clearPin);
  }


  // ----------------------------------------------------------------------
  // Invocation functions for to ports
  // ----------------------------------------------------------------------

  U32 GPIODriverTesterBase ::
    invoke_to_gpio_readPin(
        const NATIVE_INT_TYPE portNum,
        U32 pin_num
    )
  {
    FW_ASSERT(portNum < this->getNum_to_gpio_readPin(),static_cast<AssertArg>(portNum));
    FW_ASSERT(portNum < this->getNum_to_gpio_readPin(),static_cast<AssertArg>(portNum));
    return this->m_to_gpio_readPin[portNum].invoke(
        pin_num
    );
  }

  I32 GPIODriverTesterBase ::
    invoke_to_gpio_setPin(
        const NATIVE_INT_TYPE portNum,
        U32 pin_num
    )
  {
    FW_ASSERT(portNum < this->getNum_to_gpio_setPin(),static_cast<AssertArg>(portNum));
    FW_ASSERT(portNum < this->getNum_to_gpio_setPin(),static_cast<AssertArg>(portNum));
    return this->m_to_gpio_setPin[portNum].invoke(
        pin_num
    );
  }

  I32 GPIODriverTesterBase ::
    invoke_to_gpio_clearPin(
        const NATIVE_INT_TYPE portNum,
        U32 pin_num
    )
  {
    FW_ASSERT(portNum < this->getNum_to_gpio_clearPin(),static_cast<AssertArg>(portNum));
    FW_ASSERT(portNum < this->getNum_to_gpio_clearPin(),static_cast<AssertArg>(portNum));
    return this->m_to_gpio_clearPin[portNum].invoke(
        pin_num
    );
  }

  // ----------------------------------------------------------------------
  // Connection status for to ports
  // ----------------------------------------------------------------------

  bool GPIODriverTesterBase ::
    isConnected_to_gpio_readPin(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_to_gpio_readPin(), static_cast<AssertArg>(portNum));
    return this->m_to_gpio_readPin[portNum].isConnected();
  }

  bool GPIODriverTesterBase ::
    isConnected_to_gpio_setPin(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_to_gpio_setPin(), static_cast<AssertArg>(portNum));
    return this->m_to_gpio_setPin[portNum].isConnected();
  }

  bool GPIODriverTesterBase ::
    isConnected_to_gpio_clearPin(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_to_gpio_clearPin(), static_cast<AssertArg>(portNum));
    return this->m_to_gpio_clearPin[portNum].isConnected();
  }

} // end namespace Drv
