// ======================================================================
// \title  SPWDriver/test/ut/TesterBase.cpp
// \author Auto-generated
// \brief  cpp file for SPWDriver component test harness base class
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

  SPWDriverTesterBase ::
    SPWDriverTesterBase(
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

  SPWDriverTesterBase ::
    ~SPWDriverTesterBase(void) 
  {
  }

  void SPWDriverTesterBase ::
    init(
        const NATIVE_INT_TYPE instance
    )
  {

    // Initialize base class

		Fw::PassiveComponentBase::init(instance);

    // Initialize output port writeRMAP

    for (
        NATIVE_INT_TYPE _port = 0;
        _port < this->getNum_to_writeRMAP();
        ++_port
    ) {
      this->m_to_writeRMAP[_port].init();

#if FW_OBJECT_NAMES == 1
      char _portName[80];
      snprintf(
          _portName,
          sizeof(_portName),
          "%s_to_writeRMAP[%d]",
          this->m_objName,
          _port
      );
      this->m_to_writeRMAP[_port].setObjName(_portName);
#endif

    }

    // Initialize output port readRMAP

    for (
        NATIVE_INT_TYPE _port = 0;
        _port < this->getNum_to_readRMAP();
        ++_port
    ) {
      this->m_to_readRMAP[_port].init();

#if FW_OBJECT_NAMES == 1
      char _portName[80];
      snprintf(
          _portName,
          sizeof(_portName),
          "%s_to_readRMAP[%d]",
          this->m_objName,
          _port
      );
      this->m_to_readRMAP[_port].setObjName(_portName);
#endif

    }

    // Initialize output port reset

    for (
        NATIVE_INT_TYPE _port = 0;
        _port < this->getNum_to_reset();
        ++_port
    ) {
      this->m_to_reset[_port].init();

#if FW_OBJECT_NAMES == 1
      char _portName[80];
      snprintf(
          _portName,
          sizeof(_portName),
          "%s_to_reset[%d]",
          this->m_objName,
          _port
      );
      this->m_to_reset[_port].setObjName(_portName);
#endif

    }

    // Initialize output port getStatus

    for (
        NATIVE_INT_TYPE _port = 0;
        _port < this->getNum_to_getStatus();
        ++_port
    ) {
      this->m_to_getStatus[_port].init();

#if FW_OBJECT_NAMES == 1
      char _portName[80];
      snprintf(
          _portName,
          sizeof(_portName),
          "%s_to_getStatus[%d]",
          this->m_objName,
          _port
      );
      this->m_to_getStatus[_port].setObjName(_portName);
#endif

    }

  }

  // ----------------------------------------------------------------------
  // Getters for port counts
  // ----------------------------------------------------------------------

  NATIVE_INT_TYPE SPWDriverTesterBase ::
    getNum_to_writeRMAP(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_to_writeRMAP);
  }

  NATIVE_INT_TYPE SPWDriverTesterBase ::
    getNum_to_readRMAP(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_to_readRMAP);
  }

  NATIVE_INT_TYPE SPWDriverTesterBase ::
    getNum_to_reset(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_to_reset);
  }

  NATIVE_INT_TYPE SPWDriverTesterBase ::
    getNum_to_getStatus(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_to_getStatus);
  }

  // ----------------------------------------------------------------------
  // Connectors for to ports 
  // ----------------------------------------------------------------------

  void SPWDriverTesterBase ::
    connect_to_writeRMAP(
        const NATIVE_INT_TYPE portNum,
        Drv::InputSphinxSPW_WriteRMAPPort *const writeRMAP
    ) 
  {
    FW_ASSERT(portNum < this->getNum_to_writeRMAP(),static_cast<AssertArg>(portNum));
    this->m_to_writeRMAP[portNum].addCallPort(writeRMAP);
  }

  void SPWDriverTesterBase ::
    connect_to_readRMAP(
        const NATIVE_INT_TYPE portNum,
        Drv::InputSphinxSPW_ReadRMAPPort *const readRMAP
    ) 
  {
    FW_ASSERT(portNum < this->getNum_to_readRMAP(),static_cast<AssertArg>(portNum));
    this->m_to_readRMAP[portNum].addCallPort(readRMAP);
  }

  void SPWDriverTesterBase ::
    connect_to_reset(
        const NATIVE_INT_TYPE portNum,
        Drv::InputSphinxSPW_StatusPort *const reset
    ) 
  {
    FW_ASSERT(portNum < this->getNum_to_reset(),static_cast<AssertArg>(portNum));
    this->m_to_reset[portNum].addCallPort(reset);
  }

  void SPWDriverTesterBase ::
    connect_to_getStatus(
        const NATIVE_INT_TYPE portNum,
        Drv::InputSphinxSPW_StatusPort *const getStatus
    ) 
  {
    FW_ASSERT(portNum < this->getNum_to_getStatus(),static_cast<AssertArg>(portNum));
    this->m_to_getStatus[portNum].addCallPort(getStatus);
  }


  // ----------------------------------------------------------------------
  // Invocation functions for to ports
  // ----------------------------------------------------------------------

  I32 SPWDriverTesterBase ::
    invoke_to_writeRMAP(
        const NATIVE_INT_TYPE portNum,
        U8 dest_addr,
        U8 dest_key,
        U32 write_addr,
        U8 *buf_ptr,
        U32 num_bytes,
        U8 increment,
        U8 verify,
        U8 acknowledge
    )
  {
    FW_ASSERT(portNum < this->getNum_to_writeRMAP(),static_cast<AssertArg>(portNum));
    FW_ASSERT(portNum < this->getNum_to_writeRMAP(),static_cast<AssertArg>(portNum));
    return this->m_to_writeRMAP[portNum].invoke(
        dest_addr, dest_key, write_addr, buf_ptr, num_bytes, increment, verify, acknowledge
    );
  }

  I32 SPWDriverTesterBase ::
    invoke_to_readRMAP(
        const NATIVE_INT_TYPE portNum,
        U8 dest_addr,
        U8 dest_key,
        U32 read_addr,
        U8 *buf_ptr,
        U32 num_bytes,
        U8 increment
    )
  {
    FW_ASSERT(portNum < this->getNum_to_readRMAP(),static_cast<AssertArg>(portNum));
    FW_ASSERT(portNum < this->getNum_to_readRMAP(),static_cast<AssertArg>(portNum));
    return this->m_to_readRMAP[portNum].invoke(
        dest_addr, dest_key, read_addr, buf_ptr, num_bytes, increment
    );
  }

  I32 SPWDriverTesterBase ::
    invoke_to_reset(
        const NATIVE_INT_TYPE portNum
    )
  {
    FW_ASSERT(portNum < this->getNum_to_reset(),static_cast<AssertArg>(portNum));
    FW_ASSERT(portNum < this->getNum_to_reset(),static_cast<AssertArg>(portNum));
    return this->m_to_reset[portNum].invoke(
        
    );
  }

  I32 SPWDriverTesterBase ::
    invoke_to_getStatus(
        const NATIVE_INT_TYPE portNum
    )
  {
    FW_ASSERT(portNum < this->getNum_to_getStatus(),static_cast<AssertArg>(portNum));
    FW_ASSERT(portNum < this->getNum_to_getStatus(),static_cast<AssertArg>(portNum));
    return this->m_to_getStatus[portNum].invoke(
        
    );
  }

  // ----------------------------------------------------------------------
  // Connection status for to ports
  // ----------------------------------------------------------------------

  bool SPWDriverTesterBase ::
    isConnected_to_writeRMAP(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_to_writeRMAP(), static_cast<AssertArg>(portNum));
    return this->m_to_writeRMAP[portNum].isConnected();
  }

  bool SPWDriverTesterBase ::
    isConnected_to_readRMAP(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_to_readRMAP(), static_cast<AssertArg>(portNum));
    return this->m_to_readRMAP[portNum].isConnected();
  }

  bool SPWDriverTesterBase ::
    isConnected_to_reset(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_to_reset(), static_cast<AssertArg>(portNum));
    return this->m_to_reset[portNum].isConnected();
  }

  bool SPWDriverTesterBase ::
    isConnected_to_getStatus(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_to_getStatus(), static_cast<AssertArg>(portNum));
    return this->m_to_getStatus[portNum].isConnected();
  }

} // end namespace Drv
