// ======================================================================
// \title  FPGADriver/test/ut/TesterBase.cpp
// \author Auto-generated
// \brief  cpp file for FPGADriver component test harness base class
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

  FPGADriverTesterBase ::
    FPGADriverTesterBase(
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
    // Initialize histories for typed user output ports
    this->fromPortHistory_timeRTIOut =
      new History<FromPortEntry_timeRTIOut>(maxHistorySize);
    this->fromPortHistory_cycleOut =
      new History<FromPortEntry_cycleOut>(maxHistorySize);
    // Clear history
    this->clearHistory();
  }

  FPGADriverTesterBase ::
    ~FPGADriverTesterBase(void) 
  {
  }

  void FPGADriverTesterBase ::
    init(
        const NATIVE_INT_TYPE instance
    )
  {

    // Initialize base class

		Fw::PassiveComponentBase::init(instance);

    // Attach input port timeRTIOut

    for (
        NATIVE_INT_TYPE _port = 0;
        _port < this->getNum_from_timeRTIOut();
        ++_port
    ) {

      this->m_from_timeRTIOut[_port].init();
      this->m_from_timeRTIOut[_port].addCallComp(
          this,
          from_timeRTIOut_static
      );
      this->m_from_timeRTIOut[_port].setPortNum(_port);

#if FW_OBJECT_NAMES == 1
      char _portName[80];
      (void) snprintf(
          _portName,
          sizeof(_portName),
          "%s_from_timeRTIOut[%d]",
          this->m_objName,
          _port
      );
      this->m_from_timeRTIOut[_port].setObjName(_portName);
#endif

    }

    // Attach input port cycleOut

    for (
        NATIVE_INT_TYPE _port = 0;
        _port < this->getNum_from_cycleOut();
        ++_port
    ) {

      this->m_from_cycleOut[_port].init();
      this->m_from_cycleOut[_port].addCallComp(
          this,
          from_cycleOut_static
      );
      this->m_from_cycleOut[_port].setPortNum(_port);

#if FW_OBJECT_NAMES == 1
      char _portName[80];
      (void) snprintf(
          _portName,
          sizeof(_portName),
          "%s_from_cycleOut[%d]",
          this->m_objName,
          _port
      );
      this->m_from_cycleOut[_port].setObjName(_portName);
#endif

    }

    // Initialize output port read_reg

    for (
        NATIVE_INT_TYPE _port = 0;
        _port < this->getNum_to_read_reg();
        ++_port
    ) {
      this->m_to_read_reg[_port].init();

#if FW_OBJECT_NAMES == 1
      char _portName[80];
      snprintf(
          _portName,
          sizeof(_portName),
          "%s_to_read_reg[%d]",
          this->m_objName,
          _port
      );
      this->m_to_read_reg[_port].setObjName(_portName);
#endif

    }

    // Initialize output port write_reg

    for (
        NATIVE_INT_TYPE _port = 0;
        _port < this->getNum_to_write_reg();
        ++_port
    ) {
      this->m_to_write_reg[_port].init();

#if FW_OBJECT_NAMES == 1
      char _portName[80];
      snprintf(
          _portName,
          sizeof(_portName),
          "%s_to_write_reg[%d]",
          this->m_objName,
          _port
      );
      this->m_to_write_reg[_port].setObjName(_portName);
#endif

    }

  }

  // ----------------------------------------------------------------------
  // Getters for port counts
  // ----------------------------------------------------------------------

  NATIVE_INT_TYPE FPGADriverTesterBase ::
    getNum_to_read_reg(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_to_read_reg);
  }

  NATIVE_INT_TYPE FPGADriverTesterBase ::
    getNum_to_write_reg(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_to_write_reg);
  }

  NATIVE_INT_TYPE FPGADriverTesterBase ::
    getNum_from_timeRTIOut(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_from_timeRTIOut);
  }

  NATIVE_INT_TYPE FPGADriverTesterBase ::
    getNum_from_cycleOut(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_from_cycleOut);
  }

  // ----------------------------------------------------------------------
  // Connectors for to ports 
  // ----------------------------------------------------------------------

  void FPGADriverTesterBase ::
    connect_to_read_reg(
        const NATIVE_INT_TYPE portNum,
        Drv::InputSphinxRegReadPort *const read_reg
    ) 
  {
    FW_ASSERT(portNum < this->getNum_to_read_reg(),static_cast<AssertArg>(portNum));
    this->m_to_read_reg[portNum].addCallPort(read_reg);
  }

  void FPGADriverTesterBase ::
    connect_to_write_reg(
        const NATIVE_INT_TYPE portNum,
        Drv::InputSphinxRegWritePort *const write_reg
    ) 
  {
    FW_ASSERT(portNum < this->getNum_to_write_reg(),static_cast<AssertArg>(portNum));
    this->m_to_write_reg[portNum].addCallPort(write_reg);
  }


  // ----------------------------------------------------------------------
  // Invocation functions for to ports
  // ----------------------------------------------------------------------

  I32 FPGADriverTesterBase ::
    invoke_to_read_reg(
        const NATIVE_INT_TYPE portNum,
        U32 offset,
        U32 &value
    )
  {
    FW_ASSERT(portNum < this->getNum_to_read_reg(),static_cast<AssertArg>(portNum));
    FW_ASSERT(portNum < this->getNum_to_read_reg(),static_cast<AssertArg>(portNum));
    return this->m_to_read_reg[portNum].invoke(
        offset, value
    );
  }

  I32 FPGADriverTesterBase ::
    invoke_to_write_reg(
        const NATIVE_INT_TYPE portNum,
        U32 offset,
        U32 value
    )
  {
    FW_ASSERT(portNum < this->getNum_to_write_reg(),static_cast<AssertArg>(portNum));
    FW_ASSERT(portNum < this->getNum_to_write_reg(),static_cast<AssertArg>(portNum));
    return this->m_to_write_reg[portNum].invoke(
        offset, value
    );
  }

  // ----------------------------------------------------------------------
  // Connection status for to ports
  // ----------------------------------------------------------------------

  bool FPGADriverTesterBase ::
    isConnected_to_read_reg(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_to_read_reg(), static_cast<AssertArg>(portNum));
    return this->m_to_read_reg[portNum].isConnected();
  }

  bool FPGADriverTesterBase ::
    isConnected_to_write_reg(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_to_write_reg(), static_cast<AssertArg>(portNum));
    return this->m_to_write_reg[portNum].isConnected();
  }

  // ----------------------------------------------------------------------
  // Getters for from ports
  // ----------------------------------------------------------------------
 
  Svc::InputSchedPort *FPGADriverTesterBase ::
    get_from_timeRTIOut(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_from_timeRTIOut(),static_cast<AssertArg>(portNum));
    return &this->m_from_timeRTIOut[portNum];
  }

  Svc::InputCyclePort *FPGADriverTesterBase ::
    get_from_cycleOut(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_from_cycleOut(),static_cast<AssertArg>(portNum));
    return &this->m_from_cycleOut[portNum];
  }

  // ----------------------------------------------------------------------
  // Static functions for from ports
  // ----------------------------------------------------------------------

  void FPGADriverTesterBase ::
    from_timeRTIOut_static(
        Fw::PassiveComponentBase *const callComp,
        const NATIVE_INT_TYPE portNum,
        NATIVE_UINT_TYPE context
    )
  {
    FW_ASSERT(callComp);
    FPGADriverTesterBase* _testerBase = 
      static_cast<FPGADriverTesterBase*>(callComp);
    _testerBase->from_timeRTIOut_handlerBase(
        portNum,
        context
    );
  }

  void FPGADriverTesterBase ::
    from_cycleOut_static(
        Fw::PassiveComponentBase *const callComp,
        const NATIVE_INT_TYPE portNum,
        Svc::TimerVal &cycleStart
    )
  {
    FW_ASSERT(callComp);
    FPGADriverTesterBase* _testerBase = 
      static_cast<FPGADriverTesterBase*>(callComp);
    _testerBase->from_cycleOut_handlerBase(
        portNum,
        cycleStart
    );
  }

  // ----------------------------------------------------------------------
  // Histories for typed from ports
  // ----------------------------------------------------------------------

  void FPGADriverTesterBase ::
    clearFromPortHistory(void)
  {
    this->fromPortHistorySize = 0;
    this->fromPortHistory_timeRTIOut->clear();
    this->fromPortHistory_cycleOut->clear();
  }

  // ---------------------------------------------------------------------- 
  // From port: timeRTIOut
  // ---------------------------------------------------------------------- 

  void FPGADriverTesterBase ::
    pushFromPortEntry_timeRTIOut(
        NATIVE_UINT_TYPE context
    )
  {
    FromPortEntry_timeRTIOut _e = {
      context
    };
    this->fromPortHistory_timeRTIOut->push_back(_e);
    ++this->fromPortHistorySize;
  }

  // ---------------------------------------------------------------------- 
  // From port: cycleOut
  // ---------------------------------------------------------------------- 

  void FPGADriverTesterBase ::
    pushFromPortEntry_cycleOut(
        Svc::TimerVal &cycleStart
    )
  {
    FromPortEntry_cycleOut _e = {
      cycleStart
    };
    this->fromPortHistory_cycleOut->push_back(_e);
    ++this->fromPortHistorySize;
  }

  // ----------------------------------------------------------------------
  // Handler base functions for from ports
  // ----------------------------------------------------------------------

  void FPGADriverTesterBase ::
    from_timeRTIOut_handlerBase(
        const NATIVE_INT_TYPE portNum,
        NATIVE_UINT_TYPE context
    )
  {
    FW_ASSERT(portNum < this->getNum_from_timeRTIOut(),static_cast<AssertArg>(portNum));
    this->from_timeRTIOut_handler(
        portNum,
        context
    );
  }

  void FPGADriverTesterBase ::
    from_cycleOut_handlerBase(
        const NATIVE_INT_TYPE portNum,
        Svc::TimerVal &cycleStart
    )
  {
    FW_ASSERT(portNum < this->getNum_from_cycleOut(),static_cast<AssertArg>(portNum));
    this->from_cycleOut_handler(
        portNum,
        cycleStart
    );
  }

  // ----------------------------------------------------------------------
  // History 
  // ----------------------------------------------------------------------

  void FPGADriverTesterBase ::
    clearHistory()
  {
    this->clearFromPortHistory();
  }

} // end namespace Drv
