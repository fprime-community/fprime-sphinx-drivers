// ======================================================================
// \title  GPTimerDriver/test/ut/TesterBase.cpp
// \author Auto-generated
// \brief  cpp file for GPTimerDriver component test harness base class
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

  GPTimerDriverTesterBase ::
    GPTimerDriverTesterBase(
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

  GPTimerDriverTesterBase ::
    ~GPTimerDriverTesterBase(void) 
  {
  }

  void GPTimerDriverTesterBase ::
    init(
        const NATIVE_INT_TYPE instance
    )
  {

    // Initialize base class

		Fw::PassiveComponentBase::init(instance);

    // Initialize output port gPTimerDriver_Unclaim

    for (
        NATIVE_INT_TYPE _port = 0;
        _port < this->getNum_to_gPTimerDriver_Unclaim();
        ++_port
    ) {
      this->m_to_gPTimerDriver_Unclaim[_port].init();

#if FW_OBJECT_NAMES == 1
      char _portName[80];
      snprintf(
          _portName,
          sizeof(_portName),
          "%s_to_gPTimerDriver_Unclaim[%d]",
          this->m_objName,
          _port
      );
      this->m_to_gPTimerDriver_Unclaim[_port].setObjName(_portName);
#endif

    }

    // Initialize output port gPTimerDriver_Claim

    for (
        NATIVE_INT_TYPE _port = 0;
        _port < this->getNum_to_gPTimerDriver_Claim();
        ++_port
    ) {
      this->m_to_gPTimerDriver_Claim[_port].init();

#if FW_OBJECT_NAMES == 1
      char _portName[80];
      snprintf(
          _portName,
          sizeof(_portName),
          "%s_to_gPTimerDriver_Claim[%d]",
          this->m_objName,
          _port
      );
      this->m_to_gPTimerDriver_Claim[_port].setObjName(_portName);
#endif

    }

    // Initialize output port gPTimerDriver_ReadControl

    for (
        NATIVE_INT_TYPE _port = 0;
        _port < this->getNum_to_gPTimerDriver_ReadControl();
        ++_port
    ) {
      this->m_to_gPTimerDriver_ReadControl[_port].init();

#if FW_OBJECT_NAMES == 1
      char _portName[80];
      snprintf(
          _portName,
          sizeof(_portName),
          "%s_to_gPTimerDriver_ReadControl[%d]",
          this->m_objName,
          _port
      );
      this->m_to_gPTimerDriver_ReadControl[_port].setObjName(_portName);
#endif

    }

    // Initialize output port gPTimerDriver_WriteCounter

    for (
        NATIVE_INT_TYPE _port = 0;
        _port < this->getNum_to_gPTimerDriver_WriteCounter();
        ++_port
    ) {
      this->m_to_gPTimerDriver_WriteCounter[_port].init();

#if FW_OBJECT_NAMES == 1
      char _portName[80];
      snprintf(
          _portName,
          sizeof(_portName),
          "%s_to_gPTimerDriver_WriteCounter[%d]",
          this->m_objName,
          _port
      );
      this->m_to_gPTimerDriver_WriteCounter[_port].setObjName(_portName);
#endif

    }

    // Initialize output port gPTimerDriver_WriteControl

    for (
        NATIVE_INT_TYPE _port = 0;
        _port < this->getNum_to_gPTimerDriver_WriteControl();
        ++_port
    ) {
      this->m_to_gPTimerDriver_WriteControl[_port].init();

#if FW_OBJECT_NAMES == 1
      char _portName[80];
      snprintf(
          _portName,
          sizeof(_portName),
          "%s_to_gPTimerDriver_WriteControl[%d]",
          this->m_objName,
          _port
      );
      this->m_to_gPTimerDriver_WriteControl[_port].setObjName(_portName);
#endif

    }

    // Initialize output port gPTimerDriver_ReadCounter

    for (
        NATIVE_INT_TYPE _port = 0;
        _port < this->getNum_to_gPTimerDriver_ReadCounter();
        ++_port
    ) {
      this->m_to_gPTimerDriver_ReadCounter[_port].init();

#if FW_OBJECT_NAMES == 1
      char _portName[80];
      snprintf(
          _portName,
          sizeof(_portName),
          "%s_to_gPTimerDriver_ReadCounter[%d]",
          this->m_objName,
          _port
      );
      this->m_to_gPTimerDriver_ReadCounter[_port].setObjName(_portName);
#endif

    }

    // Initialize output port gPTimerDriver_ReadReload

    for (
        NATIVE_INT_TYPE _port = 0;
        _port < this->getNum_to_gPTimerDriver_ReadReload();
        ++_port
    ) {
      this->m_to_gPTimerDriver_ReadReload[_port].init();

#if FW_OBJECT_NAMES == 1
      char _portName[80];
      snprintf(
          _portName,
          sizeof(_portName),
          "%s_to_gPTimerDriver_ReadReload[%d]",
          this->m_objName,
          _port
      );
      this->m_to_gPTimerDriver_ReadReload[_port].setObjName(_portName);
#endif

    }

    // Initialize output port gPTimerDriver_WriteReload

    for (
        NATIVE_INT_TYPE _port = 0;
        _port < this->getNum_to_gPTimerDriver_WriteReload();
        ++_port
    ) {
      this->m_to_gPTimerDriver_WriteReload[_port].init();

#if FW_OBJECT_NAMES == 1
      char _portName[80];
      snprintf(
          _portName,
          sizeof(_portName),
          "%s_to_gPTimerDriver_WriteReload[%d]",
          this->m_objName,
          _port
      );
      this->m_to_gPTimerDriver_WriteReload[_port].setObjName(_portName);
#endif

    }

  }

  // ----------------------------------------------------------------------
  // Getters for port counts
  // ----------------------------------------------------------------------

  NATIVE_INT_TYPE GPTimerDriverTesterBase ::
    getNum_to_gPTimerDriver_Unclaim(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_to_gPTimerDriver_Unclaim);
  }

  NATIVE_INT_TYPE GPTimerDriverTesterBase ::
    getNum_to_gPTimerDriver_Claim(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_to_gPTimerDriver_Claim);
  }

  NATIVE_INT_TYPE GPTimerDriverTesterBase ::
    getNum_to_gPTimerDriver_ReadControl(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_to_gPTimerDriver_ReadControl);
  }

  NATIVE_INT_TYPE GPTimerDriverTesterBase ::
    getNum_to_gPTimerDriver_WriteCounter(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_to_gPTimerDriver_WriteCounter);
  }

  NATIVE_INT_TYPE GPTimerDriverTesterBase ::
    getNum_to_gPTimerDriver_WriteControl(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_to_gPTimerDriver_WriteControl);
  }

  NATIVE_INT_TYPE GPTimerDriverTesterBase ::
    getNum_to_gPTimerDriver_ReadCounter(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_to_gPTimerDriver_ReadCounter);
  }

  NATIVE_INT_TYPE GPTimerDriverTesterBase ::
    getNum_to_gPTimerDriver_ReadReload(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_to_gPTimerDriver_ReadReload);
  }

  NATIVE_INT_TYPE GPTimerDriverTesterBase ::
    getNum_to_gPTimerDriver_WriteReload(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_to_gPTimerDriver_WriteReload);
  }

  // ----------------------------------------------------------------------
  // Connectors for to ports 
  // ----------------------------------------------------------------------

  void GPTimerDriverTesterBase ::
    connect_to_gPTimerDriver_Unclaim(
        const NATIVE_INT_TYPE portNum,
        Drv::InputGPTimerDriver_UnclaimPort *const gPTimerDriver_Unclaim
    ) 
  {
    FW_ASSERT(portNum < this->getNum_to_gPTimerDriver_Unclaim(),static_cast<AssertArg>(portNum));
    this->m_to_gPTimerDriver_Unclaim[portNum].addCallPort(gPTimerDriver_Unclaim);
  }

  void GPTimerDriverTesterBase ::
    connect_to_gPTimerDriver_Claim(
        const NATIVE_INT_TYPE portNum,
        Drv::InputGPTimerDriver_ClaimPort *const gPTimerDriver_Claim
    ) 
  {
    FW_ASSERT(portNum < this->getNum_to_gPTimerDriver_Claim(),static_cast<AssertArg>(portNum));
    this->m_to_gPTimerDriver_Claim[portNum].addCallPort(gPTimerDriver_Claim);
  }

  void GPTimerDriverTesterBase ::
    connect_to_gPTimerDriver_ReadControl(
        const NATIVE_INT_TYPE portNum,
        Drv::InputGPTimerDriver_ReadControlPort *const gPTimerDriver_ReadControl
    ) 
  {
    FW_ASSERT(portNum < this->getNum_to_gPTimerDriver_ReadControl(),static_cast<AssertArg>(portNum));
    this->m_to_gPTimerDriver_ReadControl[portNum].addCallPort(gPTimerDriver_ReadControl);
  }

  void GPTimerDriverTesterBase ::
    connect_to_gPTimerDriver_WriteCounter(
        const NATIVE_INT_TYPE portNum,
        Drv::InputGPTimerDriver_WriteCounterPort *const gPTimerDriver_WriteCounter
    ) 
  {
    FW_ASSERT(portNum < this->getNum_to_gPTimerDriver_WriteCounter(),static_cast<AssertArg>(portNum));
    this->m_to_gPTimerDriver_WriteCounter[portNum].addCallPort(gPTimerDriver_WriteCounter);
  }

  void GPTimerDriverTesterBase ::
    connect_to_gPTimerDriver_WriteControl(
        const NATIVE_INT_TYPE portNum,
        Drv::InputGPTimerDriver_WriteControlPort *const gPTimerDriver_WriteControl
    ) 
  {
    FW_ASSERT(portNum < this->getNum_to_gPTimerDriver_WriteControl(),static_cast<AssertArg>(portNum));
    this->m_to_gPTimerDriver_WriteControl[portNum].addCallPort(gPTimerDriver_WriteControl);
  }

  void GPTimerDriverTesterBase ::
    connect_to_gPTimerDriver_ReadCounter(
        const NATIVE_INT_TYPE portNum,
        Drv::InputGPTimerDriver_ReadCounterPort *const gPTimerDriver_ReadCounter
    ) 
  {
    FW_ASSERT(portNum < this->getNum_to_gPTimerDriver_ReadCounter(),static_cast<AssertArg>(portNum));
    this->m_to_gPTimerDriver_ReadCounter[portNum].addCallPort(gPTimerDriver_ReadCounter);
  }

  void GPTimerDriverTesterBase ::
    connect_to_gPTimerDriver_ReadReload(
        const NATIVE_INT_TYPE portNum,
        Drv::InputGPTimerDriver_ReadReloadPort *const gPTimerDriver_ReadReload
    ) 
  {
    FW_ASSERT(portNum < this->getNum_to_gPTimerDriver_ReadReload(),static_cast<AssertArg>(portNum));
    this->m_to_gPTimerDriver_ReadReload[portNum].addCallPort(gPTimerDriver_ReadReload);
  }

  void GPTimerDriverTesterBase ::
    connect_to_gPTimerDriver_WriteReload(
        const NATIVE_INT_TYPE portNum,
        Drv::InputGPTimerDriver_WriteReloadPort *const gPTimerDriver_WriteReload
    ) 
  {
    FW_ASSERT(portNum < this->getNum_to_gPTimerDriver_WriteReload(),static_cast<AssertArg>(portNum));
    this->m_to_gPTimerDriver_WriteReload[portNum].addCallPort(gPTimerDriver_WriteReload);
  }


  // ----------------------------------------------------------------------
  // Invocation functions for to ports
  // ----------------------------------------------------------------------

  void GPTimerDriverTesterBase ::
    invoke_to_gPTimerDriver_Unclaim(
        const NATIVE_INT_TYPE portNum,
        I8 timer
    )
  {
    FW_ASSERT(portNum < this->getNum_to_gPTimerDriver_Unclaim(),static_cast<AssertArg>(portNum));
    FW_ASSERT(portNum < this->getNum_to_gPTimerDriver_Unclaim(),static_cast<AssertArg>(portNum));
    this->m_to_gPTimerDriver_Unclaim[portNum].invoke(
        timer
    );
  }

  I8 GPTimerDriverTesterBase ::
    invoke_to_gPTimerDriver_Claim(
        const NATIVE_INT_TYPE portNum,
        I8 timer
    )
  {
    FW_ASSERT(portNum < this->getNum_to_gPTimerDriver_Claim(),static_cast<AssertArg>(portNum));
    FW_ASSERT(portNum < this->getNum_to_gPTimerDriver_Claim(),static_cast<AssertArg>(portNum));
    return this->m_to_gPTimerDriver_Claim[portNum].invoke(
        timer
    );
  }

  U32 GPTimerDriverTesterBase ::
    invoke_to_gPTimerDriver_ReadControl(
        const NATIVE_INT_TYPE portNum,
        I8 timer
    )
  {
    FW_ASSERT(portNum < this->getNum_to_gPTimerDriver_ReadControl(),static_cast<AssertArg>(portNum));
    FW_ASSERT(portNum < this->getNum_to_gPTimerDriver_ReadControl(),static_cast<AssertArg>(portNum));
    return this->m_to_gPTimerDriver_ReadControl[portNum].invoke(
        timer
    );
  }

  void GPTimerDriverTesterBase ::
    invoke_to_gPTimerDriver_WriteCounter(
        const NATIVE_INT_TYPE portNum,
        I8 timer,
        U32 counter
    )
  {
    FW_ASSERT(portNum < this->getNum_to_gPTimerDriver_WriteCounter(),static_cast<AssertArg>(portNum));
    FW_ASSERT(portNum < this->getNum_to_gPTimerDriver_WriteCounter(),static_cast<AssertArg>(portNum));
    this->m_to_gPTimerDriver_WriteCounter[portNum].invoke(
        timer, counter
    );
  }

  void GPTimerDriverTesterBase ::
    invoke_to_gPTimerDriver_WriteControl(
        const NATIVE_INT_TYPE portNum,
        I8 timer,
        U32 control
    )
  {
    FW_ASSERT(portNum < this->getNum_to_gPTimerDriver_WriteControl(),static_cast<AssertArg>(portNum));
    FW_ASSERT(portNum < this->getNum_to_gPTimerDriver_WriteControl(),static_cast<AssertArg>(portNum));
    this->m_to_gPTimerDriver_WriteControl[portNum].invoke(
        timer, control
    );
  }

  U32 GPTimerDriverTesterBase ::
    invoke_to_gPTimerDriver_ReadCounter(
        const NATIVE_INT_TYPE portNum,
        I8 timer
    )
  {
    FW_ASSERT(portNum < this->getNum_to_gPTimerDriver_ReadCounter(),static_cast<AssertArg>(portNum));
    FW_ASSERT(portNum < this->getNum_to_gPTimerDriver_ReadCounter(),static_cast<AssertArg>(portNum));
    return this->m_to_gPTimerDriver_ReadCounter[portNum].invoke(
        timer
    );
  }

  U32 GPTimerDriverTesterBase ::
    invoke_to_gPTimerDriver_ReadReload(
        const NATIVE_INT_TYPE portNum,
        I8 timer
    )
  {
    FW_ASSERT(portNum < this->getNum_to_gPTimerDriver_ReadReload(),static_cast<AssertArg>(portNum));
    FW_ASSERT(portNum < this->getNum_to_gPTimerDriver_ReadReload(),static_cast<AssertArg>(portNum));
    return this->m_to_gPTimerDriver_ReadReload[portNum].invoke(
        timer
    );
  }

  void GPTimerDriverTesterBase ::
    invoke_to_gPTimerDriver_WriteReload(
        const NATIVE_INT_TYPE portNum,
        I8 timer,
        U32 reload
    )
  {
    FW_ASSERT(portNum < this->getNum_to_gPTimerDriver_WriteReload(),static_cast<AssertArg>(portNum));
    FW_ASSERT(portNum < this->getNum_to_gPTimerDriver_WriteReload(),static_cast<AssertArg>(portNum));
    this->m_to_gPTimerDriver_WriteReload[portNum].invoke(
        timer, reload
    );
  }

  // ----------------------------------------------------------------------
  // Connection status for to ports
  // ----------------------------------------------------------------------

  bool GPTimerDriverTesterBase ::
    isConnected_to_gPTimerDriver_Unclaim(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_to_gPTimerDriver_Unclaim(), static_cast<AssertArg>(portNum));
    return this->m_to_gPTimerDriver_Unclaim[portNum].isConnected();
  }

  bool GPTimerDriverTesterBase ::
    isConnected_to_gPTimerDriver_Claim(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_to_gPTimerDriver_Claim(), static_cast<AssertArg>(portNum));
    return this->m_to_gPTimerDriver_Claim[portNum].isConnected();
  }

  bool GPTimerDriverTesterBase ::
    isConnected_to_gPTimerDriver_ReadControl(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_to_gPTimerDriver_ReadControl(), static_cast<AssertArg>(portNum));
    return this->m_to_gPTimerDriver_ReadControl[portNum].isConnected();
  }

  bool GPTimerDriverTesterBase ::
    isConnected_to_gPTimerDriver_WriteCounter(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_to_gPTimerDriver_WriteCounter(), static_cast<AssertArg>(portNum));
    return this->m_to_gPTimerDriver_WriteCounter[portNum].isConnected();
  }

  bool GPTimerDriverTesterBase ::
    isConnected_to_gPTimerDriver_WriteControl(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_to_gPTimerDriver_WriteControl(), static_cast<AssertArg>(portNum));
    return this->m_to_gPTimerDriver_WriteControl[portNum].isConnected();
  }

  bool GPTimerDriverTesterBase ::
    isConnected_to_gPTimerDriver_ReadCounter(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_to_gPTimerDriver_ReadCounter(), static_cast<AssertArg>(portNum));
    return this->m_to_gPTimerDriver_ReadCounter[portNum].isConnected();
  }

  bool GPTimerDriverTesterBase ::
    isConnected_to_gPTimerDriver_ReadReload(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_to_gPTimerDriver_ReadReload(), static_cast<AssertArg>(portNum));
    return this->m_to_gPTimerDriver_ReadReload[portNum].isConnected();
  }

  bool GPTimerDriverTesterBase ::
    isConnected_to_gPTimerDriver_WriteReload(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_to_gPTimerDriver_WriteReload(), static_cast<AssertArg>(portNum));
    return this->m_to_gPTimerDriver_WriteReload[portNum].isConnected();
  }

} // end namespace Drv
