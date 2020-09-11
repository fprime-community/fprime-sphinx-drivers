// ======================================================================
// \title  FPGASPIDriver/test/ut/TesterBase.cpp
// \author Auto-generated
// \brief  cpp file for FPGASPIDriver component test harness base class
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

  FPGASPIDriverTesterBase ::
    FPGASPIDriverTesterBase(
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
    this->fromPortHistory_Time =
      new History<FromPortEntry_Time>(maxHistorySize);
    // Clear history
    this->clearHistory();
  }

  FPGASPIDriverTesterBase ::
    ~FPGASPIDriverTesterBase(void) 
  {
  }

  void FPGASPIDriverTesterBase ::
    init(
        const NATIVE_INT_TYPE instance
    )
  {

    // Initialize base class

		Fw::PassiveComponentBase::init(instance);

    // Attach input port Time

    for (
        NATIVE_INT_TYPE _port = 0;
        _port < this->getNum_from_Time();
        ++_port
    ) {

      this->m_from_Time[_port].init();
      this->m_from_Time[_port].addCallComp(
          this,
          from_Time_static
      );
      this->m_from_Time[_port].setPortNum(_port);

#if FW_OBJECT_NAMES == 1
      char _portName[80];
      (void) snprintf(
          _portName,
          sizeof(_portName),
          "%s_from_Time[%d]",
          this->m_objName,
          _port
      );
      this->m_from_Time[_port].setObjName(_portName);
#endif

    }

    // Initialize output port read_write

    for (
        NATIVE_INT_TYPE _port = 0;
        _port < this->getNum_to_read_write();
        ++_port
    ) {
      this->m_to_read_write[_port].init();

#if FW_OBJECT_NAMES == 1
      char _portName[80];
      snprintf(
          _portName,
          sizeof(_portName),
          "%s_to_read_write[%d]",
          this->m_objName,
          _port
      );
      this->m_to_read_write[_port].setObjName(_portName);
#endif

    }

  }

  // ----------------------------------------------------------------------
  // Getters for port counts
  // ----------------------------------------------------------------------

  NATIVE_INT_TYPE FPGASPIDriverTesterBase ::
    getNum_to_read_write(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_to_read_write);
  }

  NATIVE_INT_TYPE FPGASPIDriverTesterBase ::
    getNum_from_Time(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_from_Time);
  }

  // ----------------------------------------------------------------------
  // Connectors for to ports 
  // ----------------------------------------------------------------------

  void FPGASPIDriverTesterBase ::
    connect_to_read_write(
        const NATIVE_INT_TYPE portNum,
        Drv::InputSphinxFPGASPI_RWPort *const read_write
    ) 
  {
    FW_ASSERT(portNum < this->getNum_to_read_write(),static_cast<AssertArg>(portNum));
    this->m_to_read_write[portNum].addCallPort(read_write);
  }


  // ----------------------------------------------------------------------
  // Invocation functions for to ports
  // ----------------------------------------------------------------------

  I32 FPGASPIDriverTesterBase ::
    invoke_to_read_write(
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
    FW_ASSERT(portNum < this->getNum_to_read_write(),static_cast<AssertArg>(portNum));
    FW_ASSERT(portNum < this->getNum_to_read_write(),static_cast<AssertArg>(portNum));
    return this->m_to_read_write[portNum].invoke(
        write_buf_ptr, read_buf_ptr, nBytes, activate_slave, timeout, clock_bitrate, bit_order, delay
    );
  }

  // ----------------------------------------------------------------------
  // Connection status for to ports
  // ----------------------------------------------------------------------

  bool FPGASPIDriverTesterBase ::
    isConnected_to_read_write(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_to_read_write(), static_cast<AssertArg>(portNum));
    return this->m_to_read_write[portNum].isConnected();
  }

  // ----------------------------------------------------------------------
  // Getters for from ports
  // ----------------------------------------------------------------------
 
  Fw::InputTimePort *FPGASPIDriverTesterBase ::
    get_from_Time(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_from_Time(),static_cast<AssertArg>(portNum));
    return &this->m_from_Time[portNum];
  }

  // ----------------------------------------------------------------------
  // Static functions for from ports
  // ----------------------------------------------------------------------

  void FPGASPIDriverTesterBase ::
    from_Time_static(
        Fw::PassiveComponentBase *const callComp,
        const NATIVE_INT_TYPE portNum,
        Fw::Time &time
    )
  {
    FW_ASSERT(callComp);
    FPGASPIDriverTesterBase* _testerBase = 
      static_cast<FPGASPIDriverTesterBase*>(callComp);
    _testerBase->from_Time_handlerBase(
        portNum,
        time
    );
  }

  // ----------------------------------------------------------------------
  // Histories for typed from ports
  // ----------------------------------------------------------------------

  void FPGASPIDriverTesterBase ::
    clearFromPortHistory(void)
  {
    this->fromPortHistorySize = 0;
    this->fromPortHistory_Time->clear();
  }

  // ---------------------------------------------------------------------- 
  // From port: Time
  // ---------------------------------------------------------------------- 

  void FPGASPIDriverTesterBase ::
    pushFromPortEntry_Time(
        Fw::Time &time
    )
  {
    FromPortEntry_Time _e = {
      time
    };
    this->fromPortHistory_Time->push_back(_e);
    ++this->fromPortHistorySize;
  }

  // ----------------------------------------------------------------------
  // Handler base functions for from ports
  // ----------------------------------------------------------------------

  void FPGASPIDriverTesterBase ::
    from_Time_handlerBase(
        const NATIVE_INT_TYPE portNum,
        Fw::Time &time
    )
  {
    FW_ASSERT(portNum < this->getNum_from_Time(),static_cast<AssertArg>(portNum));
    this->from_Time_handler(
        portNum,
        time
    );
  }

  // ----------------------------------------------------------------------
  // History 
  // ----------------------------------------------------------------------

  void FPGASPIDriverTesterBase ::
    clearHistory()
  {
    this->clearFromPortHistory();
  }

  // ----------------------------------------------------------------------
  // Time
  // ----------------------------------------------------------------------
  
  void FPGASPIDriverTesterBase ::
  setTestTime(const Fw::Time& time)
  {
    this->m_testTime = time;
  }

} // end namespace Drv
