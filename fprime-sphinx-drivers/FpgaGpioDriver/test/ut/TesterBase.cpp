// ======================================================================
// \title  FpgaGpioDriver/test/ut/TesterBase.cpp
// \author Auto-generated
// \brief  cpp file for FpgaGpioDriver component test harness base class
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

  FpgaGpioDriverTesterBase ::
    FpgaGpioDriverTesterBase(
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

  FpgaGpioDriverTesterBase ::
    ~FpgaGpioDriverTesterBase(void) 
  {
  }

  void FpgaGpioDriverTesterBase ::
    init(
        const NATIVE_INT_TYPE instance
    )
  {

    // Initialize base class

		Fw::PassiveComponentBase::init(instance);

    // Initialize output port setPin

    for (
        NATIVE_INT_TYPE _port = 0;
        _port < this->getNum_to_setPin();
        ++_port
    ) {
      this->m_to_setPin[_port].init();

#if FW_OBJECT_NAMES == 1
      char _portName[80];
      snprintf(
          _portName,
          sizeof(_portName),
          "%s_to_setPin[%d]",
          this->m_objName,
          _port
      );
      this->m_to_setPin[_port].setObjName(_portName);
#endif

    }

    // Initialize output port clearPin

    for (
        NATIVE_INT_TYPE _port = 0;
        _port < this->getNum_to_clearPin();
        ++_port
    ) {
      this->m_to_clearPin[_port].init();

#if FW_OBJECT_NAMES == 1
      char _portName[80];
      snprintf(
          _portName,
          sizeof(_portName),
          "%s_to_clearPin[%d]",
          this->m_objName,
          _port
      );
      this->m_to_clearPin[_port].setObjName(_portName);
#endif

    }

    // Initialize output port readPin

    for (
        NATIVE_INT_TYPE _port = 0;
        _port < this->getNum_to_readPin();
        ++_port
    ) {
      this->m_to_readPin[_port].init();

#if FW_OBJECT_NAMES == 1
      char _portName[80];
      snprintf(
          _portName,
          sizeof(_portName),
          "%s_to_readPin[%d]",
          this->m_objName,
          _port
      );
      this->m_to_readPin[_port].setObjName(_portName);
#endif

    }

    // Initialize output port enablePin

    for (
        NATIVE_INT_TYPE _port = 0;
        _port < this->getNum_to_enablePin();
        ++_port
    ) {
      this->m_to_enablePin[_port].init();

#if FW_OBJECT_NAMES == 1
      char _portName[80];
      snprintf(
          _portName,
          sizeof(_portName),
          "%s_to_enablePin[%d]",
          this->m_objName,
          _port
      );
      this->m_to_enablePin[_port].setObjName(_portName);
#endif

    }

    // Initialize output port disablePin

    for (
        NATIVE_INT_TYPE _port = 0;
        _port < this->getNum_to_disablePin();
        ++_port
    ) {
      this->m_to_disablePin[_port].init();

#if FW_OBJECT_NAMES == 1
      char _portName[80];
      snprintf(
          _portName,
          sizeof(_portName),
          "%s_to_disablePin[%d]",
          this->m_objName,
          _port
      );
      this->m_to_disablePin[_port].setObjName(_portName);
#endif

    }

  }

  // ----------------------------------------------------------------------
  // Getters for port counts
  // ----------------------------------------------------------------------

  NATIVE_INT_TYPE FpgaGpioDriverTesterBase ::
    getNum_to_setPin(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_to_setPin);
  }

  NATIVE_INT_TYPE FpgaGpioDriverTesterBase ::
    getNum_to_clearPin(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_to_clearPin);
  }

  NATIVE_INT_TYPE FpgaGpioDriverTesterBase ::
    getNum_to_readPin(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_to_readPin);
  }

  NATIVE_INT_TYPE FpgaGpioDriverTesterBase ::
    getNum_to_enablePin(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_to_enablePin);
  }

  NATIVE_INT_TYPE FpgaGpioDriverTesterBase ::
    getNum_to_disablePin(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_to_disablePin);
  }

  // ----------------------------------------------------------------------
  // Connectors for to ports 
  // ----------------------------------------------------------------------

  void FpgaGpioDriverTesterBase ::
    connect_to_setPin(
        const NATIVE_INT_TYPE portNum,
        Drv::InputSphinxGPIO_WritePinPort *const setPin
    ) 
  {
    FW_ASSERT(portNum < this->getNum_to_setPin(),static_cast<AssertArg>(portNum));
    this->m_to_setPin[portNum].addCallPort(setPin);
  }

  void FpgaGpioDriverTesterBase ::
    connect_to_clearPin(
        const NATIVE_INT_TYPE portNum,
        Drv::InputSphinxGPIO_WritePinPort *const clearPin
    ) 
  {
    FW_ASSERT(portNum < this->getNum_to_clearPin(),static_cast<AssertArg>(portNum));
    this->m_to_clearPin[portNum].addCallPort(clearPin);
  }

  void FpgaGpioDriverTesterBase ::
    connect_to_readPin(
        const NATIVE_INT_TYPE portNum,
        Drv::InputSphinxGPIO_ReadPinPort *const readPin
    ) 
  {
    FW_ASSERT(portNum < this->getNum_to_readPin(),static_cast<AssertArg>(portNum));
    this->m_to_readPin[portNum].addCallPort(readPin);
  }

  void FpgaGpioDriverTesterBase ::
    connect_to_enablePin(
        const NATIVE_INT_TYPE portNum,
        Drv::InputSphinxGPIO_WritePinPort *const enablePin
    ) 
  {
    FW_ASSERT(portNum < this->getNum_to_enablePin(),static_cast<AssertArg>(portNum));
    this->m_to_enablePin[portNum].addCallPort(enablePin);
  }

  void FpgaGpioDriverTesterBase ::
    connect_to_disablePin(
        const NATIVE_INT_TYPE portNum,
        Drv::InputSphinxGPIO_WritePinPort *const disablePin
    ) 
  {
    FW_ASSERT(portNum < this->getNum_to_disablePin(),static_cast<AssertArg>(portNum));
    this->m_to_disablePin[portNum].addCallPort(disablePin);
  }


  // ----------------------------------------------------------------------
  // Invocation functions for to ports
  // ----------------------------------------------------------------------

  I32 FpgaGpioDriverTesterBase ::
    invoke_to_setPin(
        const NATIVE_INT_TYPE portNum,
        U32 pin_num
    )
  {
    FW_ASSERT(portNum < this->getNum_to_setPin(),static_cast<AssertArg>(portNum));
    FW_ASSERT(portNum < this->getNum_to_setPin(),static_cast<AssertArg>(portNum));
    return this->m_to_setPin[portNum].invoke(
        pin_num
    );
  }

  I32 FpgaGpioDriverTesterBase ::
    invoke_to_clearPin(
        const NATIVE_INT_TYPE portNum,
        U32 pin_num
    )
  {
    FW_ASSERT(portNum < this->getNum_to_clearPin(),static_cast<AssertArg>(portNum));
    FW_ASSERT(portNum < this->getNum_to_clearPin(),static_cast<AssertArg>(portNum));
    return this->m_to_clearPin[portNum].invoke(
        pin_num
    );
  }

  U32 FpgaGpioDriverTesterBase ::
    invoke_to_readPin(
        const NATIVE_INT_TYPE portNum,
        U32 pin_num
    )
  {
    FW_ASSERT(portNum < this->getNum_to_readPin(),static_cast<AssertArg>(portNum));
    FW_ASSERT(portNum < this->getNum_to_readPin(),static_cast<AssertArg>(portNum));
    return this->m_to_readPin[portNum].invoke(
        pin_num
    );
  }

  I32 FpgaGpioDriverTesterBase ::
    invoke_to_enablePin(
        const NATIVE_INT_TYPE portNum,
        U32 pin_num
    )
  {
    FW_ASSERT(portNum < this->getNum_to_enablePin(),static_cast<AssertArg>(portNum));
    FW_ASSERT(portNum < this->getNum_to_enablePin(),static_cast<AssertArg>(portNum));
    return this->m_to_enablePin[portNum].invoke(
        pin_num
    );
  }

  I32 FpgaGpioDriverTesterBase ::
    invoke_to_disablePin(
        const NATIVE_INT_TYPE portNum,
        U32 pin_num
    )
  {
    FW_ASSERT(portNum < this->getNum_to_disablePin(),static_cast<AssertArg>(portNum));
    FW_ASSERT(portNum < this->getNum_to_disablePin(),static_cast<AssertArg>(portNum));
    return this->m_to_disablePin[portNum].invoke(
        pin_num
    );
  }

  // ----------------------------------------------------------------------
  // Connection status for to ports
  // ----------------------------------------------------------------------

  bool FpgaGpioDriverTesterBase ::
    isConnected_to_setPin(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_to_setPin(), static_cast<AssertArg>(portNum));
    return this->m_to_setPin[portNum].isConnected();
  }

  bool FpgaGpioDriverTesterBase ::
    isConnected_to_clearPin(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_to_clearPin(), static_cast<AssertArg>(portNum));
    return this->m_to_clearPin[portNum].isConnected();
  }

  bool FpgaGpioDriverTesterBase ::
    isConnected_to_readPin(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_to_readPin(), static_cast<AssertArg>(portNum));
    return this->m_to_readPin[portNum].isConnected();
  }

  bool FpgaGpioDriverTesterBase ::
    isConnected_to_enablePin(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_to_enablePin(), static_cast<AssertArg>(portNum));
    return this->m_to_enablePin[portNum].isConnected();
  }

  bool FpgaGpioDriverTesterBase ::
    isConnected_to_disablePin(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_to_disablePin(), static_cast<AssertArg>(portNum));
    return this->m_to_disablePin[portNum].isConnected();
  }

} // end namespace Drv
