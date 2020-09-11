// ======================================================================
// \title  NORFlashDriver/test/ut/TesterBase.cpp
// \author Auto-generated
// \brief  cpp file for NORFlashDriver component test harness base class
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

  NORFlashDriverTesterBase ::
    NORFlashDriverTesterBase(
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

  NORFlashDriverTesterBase ::
    ~NORFlashDriverTesterBase(void) 
  {
  }

  void NORFlashDriverTesterBase ::
    init(
        const NATIVE_INT_TYPE instance
    )
  {

    // Initialize base class

		Fw::PassiveComponentBase::init(instance);

    // Initialize output port read

    for (
        NATIVE_INT_TYPE _port = 0;
        _port < this->getNum_to_read();
        ++_port
    ) {
      this->m_to_read[_port].init();

#if FW_OBJECT_NAMES == 1
      char _portName[80];
      snprintf(
          _portName,
          sizeof(_portName),
          "%s_to_read[%d]",
          this->m_objName,
          _port
      );
      this->m_to_read[_port].setObjName(_portName);
#endif

    }

    // Initialize output port write

    for (
        NATIVE_INT_TYPE _port = 0;
        _port < this->getNum_to_write();
        ++_port
    ) {
      this->m_to_write[_port].init();

#if FW_OBJECT_NAMES == 1
      char _portName[80];
      snprintf(
          _portName,
          sizeof(_portName),
          "%s_to_write[%d]",
          this->m_objName,
          _port
      );
      this->m_to_write[_port].setObjName(_portName);
#endif

    }

  }

  // ----------------------------------------------------------------------
  // Getters for port counts
  // ----------------------------------------------------------------------

  NATIVE_INT_TYPE NORFlashDriverTesterBase ::
    getNum_to_read(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_to_read);
  }

  NATIVE_INT_TYPE NORFlashDriverTesterBase ::
    getNum_to_write(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_to_write);
  }

  // ----------------------------------------------------------------------
  // Connectors for to ports 
  // ----------------------------------------------------------------------

  void NORFlashDriverTesterBase ::
    connect_to_read(
        const NATIVE_INT_TYPE portNum,
        Drv::InputNORFlash_ReadBPort *const read
    ) 
  {
    FW_ASSERT(portNum < this->getNum_to_read(),static_cast<AssertArg>(portNum));
    this->m_to_read[portNum].addCallPort(read);
  }

  void NORFlashDriverTesterBase ::
    connect_to_write(
        const NATIVE_INT_TYPE portNum,
        Drv::InputNORFlash_WriteBPort *const write
    ) 
  {
    FW_ASSERT(portNum < this->getNum_to_write(),static_cast<AssertArg>(portNum));
    this->m_to_write[portNum].addCallPort(write);
  }


  // ----------------------------------------------------------------------
  // Invocation functions for to ports
  // ----------------------------------------------------------------------

  I8 NORFlashDriverTesterBase ::
    invoke_to_read(
        const NATIVE_INT_TYPE portNum,
        U32 dest,
        U8 *data
    )
  {
    FW_ASSERT(portNum < this->getNum_to_read(),static_cast<AssertArg>(portNum));
    FW_ASSERT(portNum < this->getNum_to_read(),static_cast<AssertArg>(portNum));
    return this->m_to_read[portNum].invoke(
        dest, data
    );
  }

  I8 NORFlashDriverTesterBase ::
    invoke_to_write(
        const NATIVE_INT_TYPE portNum,
        U32 dest_addr,
        U8 src
    )
  {
    FW_ASSERT(portNum < this->getNum_to_write(),static_cast<AssertArg>(portNum));
    FW_ASSERT(portNum < this->getNum_to_write(),static_cast<AssertArg>(portNum));
    return this->m_to_write[portNum].invoke(
        dest_addr, src
    );
  }

  // ----------------------------------------------------------------------
  // Connection status for to ports
  // ----------------------------------------------------------------------

  bool NORFlashDriverTesterBase ::
    isConnected_to_read(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_to_read(), static_cast<AssertArg>(portNum));
    return this->m_to_read[portNum].isConnected();
  }

  bool NORFlashDriverTesterBase ::
    isConnected_to_write(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_to_write(), static_cast<AssertArg>(portNum));
    return this->m_to_write[portNum].isConnected();
  }

} // end namespace Drv
