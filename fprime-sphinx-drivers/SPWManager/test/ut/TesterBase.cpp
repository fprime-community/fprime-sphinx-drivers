// ======================================================================
// \title  SPWManager/test/ut/TesterBase.cpp
// \author Auto-generated
// \brief  cpp file for SPWManager component test harness base class
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

  SPWManagerTesterBase ::
    SPWManagerTesterBase(
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
    // Initialize command history
    this->cmdResponseHistory = new History<CmdResponse>(maxHistorySize);
    // Initialize event histories
#if FW_ENABLE_TEXT_LOGGING
    this->textLogHistory = new History<TextLogEntry>(maxHistorySize);
#endif
    this->eventHistory_SPWManager_SpaceWireInitializationError =
      new History<EventEntry_SPWManager_SpaceWireInitializationError>(maxHistorySize);
    this->eventHistory_SPWManager_SpaceWireError =
      new History<EventEntry_SPWManager_SpaceWireError>(maxHistorySize);
    this->eventHistory_SPWManager_SpaceWireTransactionTimeout =
      new History<EventEntry_SPWManager_SpaceWireTransactionTimeout>(maxHistorySize);
    this->eventHistory_SPWManager_RMAPWriteResult =
      new History<EventEntry_SPWManager_RMAPWriteResult>(maxHistorySize);
    this->eventHistory_SPWManager_RMAPReadResult =
      new History<EventEntry_SPWManager_RMAPReadResult>(maxHistorySize);
    this->eventHistory_SPWManager_ResetLink =
      new History<EventEntry_SPWManager_ResetLink>(maxHistorySize);
    // Initialize histories for typed user output ports
    this->fromPortHistory_driverWriteRMAP =
      new History<FromPortEntry_driverWriteRMAP>(maxHistorySize);
    this->fromPortHistory_statusOut =
      new History<FromPortEntry_statusOut>(maxHistorySize);
    this->fromPortHistory_PingResponse =
      new History<FromPortEntry_PingResponse>(maxHistorySize);
    this->fromPortHistory_driverReadRMAP =
      new History<FromPortEntry_driverReadRMAP>(maxHistorySize);
    // Clear history
    this->clearHistory();
  }

  SPWManagerTesterBase ::
    ~SPWManagerTesterBase(void)
  {
    // Destroy command history
    delete this->cmdResponseHistory;
    // Destroy event histories
#if FW_ENABLE_TEXT_LOGGING
    delete this->textLogHistory;
#endif
    delete this->eventHistory_SPWManager_SpaceWireInitializationError;
    delete this->eventHistory_SPWManager_SpaceWireError;
    delete this->eventHistory_SPWManager_SpaceWireTransactionTimeout;
    delete this->eventHistory_SPWManager_RMAPWriteResult;
    delete this->eventHistory_SPWManager_RMAPReadResult;
    delete this->eventHistory_SPWManager_ResetLink;
  }

  void SPWManagerTesterBase ::
    init(
        const NATIVE_INT_TYPE instance
    )
  {

    // Initialize base class

		Fw::PassiveComponentBase::init(instance);

    // Attach input port driverWriteRMAP

    for (
        NATIVE_INT_TYPE _port = 0;
        _port < this->getNum_from_driverWriteRMAP();
        ++_port
    ) {

      this->m_from_driverWriteRMAP[_port].init();
      this->m_from_driverWriteRMAP[_port].addCallComp(
          this,
          from_driverWriteRMAP_static
      );
      this->m_from_driverWriteRMAP[_port].setPortNum(_port);

#if FW_OBJECT_NAMES == 1
      char _portName[128];
      (void) snprintf(
          _portName,
          sizeof(_portName),
          "%s_from_driverWriteRMAP[%d]",
          this->m_objName,
          _port
      );
      this->m_from_driverWriteRMAP[_port].setObjName(_portName);
#endif

    }

    // Attach input port cmdRegOut

    for (
        NATIVE_INT_TYPE _port = 0;
        _port < this->getNum_from_cmdRegOut();
        ++_port
    ) {

      this->m_from_cmdRegOut[_port].init();
      this->m_from_cmdRegOut[_port].addCallComp(
          this,
          from_cmdRegOut_static
      );
      this->m_from_cmdRegOut[_port].setPortNum(_port);

#if FW_OBJECT_NAMES == 1
      char _portName[128];
      (void) snprintf(
          _portName,
          sizeof(_portName),
          "%s_from_cmdRegOut[%d]",
          this->m_objName,
          _port
      );
      this->m_from_cmdRegOut[_port].setObjName(_portName);
#endif

    }

    // Attach input port statusOut

    for (
        NATIVE_INT_TYPE _port = 0;
        _port < this->getNum_from_statusOut();
        ++_port
    ) {

      this->m_from_statusOut[_port].init();
      this->m_from_statusOut[_port].addCallComp(
          this,
          from_statusOut_static
      );
      this->m_from_statusOut[_port].setPortNum(_port);

#if FW_OBJECT_NAMES == 1
      char _portName[128];
      (void) snprintf(
          _portName,
          sizeof(_portName),
          "%s_from_statusOut[%d]",
          this->m_objName,
          _port
      );
      this->m_from_statusOut[_port].setObjName(_portName);
#endif

    }

    // Attach input port eventOut

    for (
        NATIVE_INT_TYPE _port = 0;
        _port < this->getNum_from_eventOut();
        ++_port
    ) {

      this->m_from_eventOut[_port].init();
      this->m_from_eventOut[_port].addCallComp(
          this,
          from_eventOut_static
      );
      this->m_from_eventOut[_port].setPortNum(_port);

#if FW_OBJECT_NAMES == 1
      char _portName[128];
      (void) snprintf(
          _portName,
          sizeof(_portName),
          "%s_from_eventOut[%d]",
          this->m_objName,
          _port
      );
      this->m_from_eventOut[_port].setObjName(_portName);
#endif

    }

    // Attach input port PingResponse

    for (
        NATIVE_INT_TYPE _port = 0;
        _port < this->getNum_from_PingResponse();
        ++_port
    ) {

      this->m_from_PingResponse[_port].init();
      this->m_from_PingResponse[_port].addCallComp(
          this,
          from_PingResponse_static
      );
      this->m_from_PingResponse[_port].setPortNum(_port);

#if FW_OBJECT_NAMES == 1
      char _portName[128];
      (void) snprintf(
          _portName,
          sizeof(_portName),
          "%s_from_PingResponse[%d]",
          this->m_objName,
          _port
      );
      this->m_from_PingResponse[_port].setObjName(_portName);
#endif

    }

    // Attach input port cmdResponseOut

    for (
        NATIVE_INT_TYPE _port = 0;
        _port < this->getNum_from_cmdResponseOut();
        ++_port
    ) {

      this->m_from_cmdResponseOut[_port].init();
      this->m_from_cmdResponseOut[_port].addCallComp(
          this,
          from_cmdResponseOut_static
      );
      this->m_from_cmdResponseOut[_port].setPortNum(_port);

#if FW_OBJECT_NAMES == 1
      char _portName[128];
      (void) snprintf(
          _portName,
          sizeof(_portName),
          "%s_from_cmdResponseOut[%d]",
          this->m_objName,
          _port
      );
      this->m_from_cmdResponseOut[_port].setObjName(_portName);
#endif

    }

    // Attach input port driverReset

    for (
        NATIVE_INT_TYPE _port = 0;
        _port < this->getNum_from_driverReset();
        ++_port
    ) {

      this->m_from_driverReset[_port].init();
      this->m_from_driverReset[_port].addCallComp(
          this,
          from_driverReset_static
      );
      this->m_from_driverReset[_port].setPortNum(_port);

#if FW_OBJECT_NAMES == 1
      char _portName[128];
      (void) snprintf(
          _portName,
          sizeof(_portName),
          "%s_from_driverReset[%d]",
          this->m_objName,
          _port
      );
      this->m_from_driverReset[_port].setObjName(_portName);
#endif

    }

    // Attach input port driverReadRMAP

    for (
        NATIVE_INT_TYPE _port = 0;
        _port < this->getNum_from_driverReadRMAP();
        ++_port
    ) {

      this->m_from_driverReadRMAP[_port].init();
      this->m_from_driverReadRMAP[_port].addCallComp(
          this,
          from_driverReadRMAP_static
      );
      this->m_from_driverReadRMAP[_port].setPortNum(_port);

#if FW_OBJECT_NAMES == 1
      char _portName[128];
      (void) snprintf(
          _portName,
          sizeof(_portName),
          "%s_from_driverReadRMAP[%d]",
          this->m_objName,
          _port
      );
      this->m_from_driverReadRMAP[_port].setObjName(_portName);
#endif

    }

    // Attach input port timeCaller

    for (
        NATIVE_INT_TYPE _port = 0;
        _port < this->getNum_from_timeCaller();
        ++_port
    ) {

      this->m_from_timeCaller[_port].init();
      this->m_from_timeCaller[_port].addCallComp(
          this,
          from_timeCaller_static
      );
      this->m_from_timeCaller[_port].setPortNum(_port);

#if FW_OBJECT_NAMES == 1
      char _portName[128];
      (void) snprintf(
          _portName,
          sizeof(_portName),
          "%s_from_timeCaller[%d]",
          this->m_objName,
          _port
      );
      this->m_from_timeCaller[_port].setObjName(_portName);
#endif

    }

    // Attach input port driverGetStatus

    for (
        NATIVE_INT_TYPE _port = 0;
        _port < this->getNum_from_driverGetStatus();
        ++_port
    ) {

      this->m_from_driverGetStatus[_port].init();
      this->m_from_driverGetStatus[_port].addCallComp(
          this,
          from_driverGetStatus_static
      );
      this->m_from_driverGetStatus[_port].setPortNum(_port);

#if FW_OBJECT_NAMES == 1
      char _portName[128];
      (void) snprintf(
          _portName,
          sizeof(_portName),
          "%s_from_driverGetStatus[%d]",
          this->m_objName,
          _port
      );
      this->m_from_driverGetStatus[_port].setObjName(_portName);
#endif

    }

    // Attach input port LogText

#if FW_ENABLE_TEXT_LOGGING == 1
    for (
        NATIVE_INT_TYPE _port = 0;
        _port < this->getNum_from_LogText();
        ++_port
    ) {

      this->m_from_LogText[_port].init();
      this->m_from_LogText[_port].addCallComp(
          this,
          from_LogText_static
      );
      this->m_from_LogText[_port].setPortNum(_port);

#if FW_OBJECT_NAMES == 1
      char _portName[128];
      (void) snprintf(
          _portName,
          sizeof(_portName),
          "%s_from_LogText[%d]",
          this->m_objName,
          _port
      );
      this->m_from_LogText[_port].setObjName(_portName);
#endif

    }
#endif

    // Initialize output port read

    for (
        NATIVE_INT_TYPE _port = 0;
        _port < this->getNum_to_read();
        ++_port
    ) {
      this->m_to_read[_port].init();

#if FW_OBJECT_NAMES == 1
      char _portName[128];
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

    // Initialize output port readAsyncDMA

    for (
        NATIVE_INT_TYPE _port = 0;
        _port < this->getNum_to_readAsyncDMA();
        ++_port
    ) {
      this->m_to_readAsyncDMA[_port].init();

#if FW_OBJECT_NAMES == 1
      char _portName[128];
      snprintf(
          _portName,
          sizeof(_portName),
          "%s_to_readAsyncDMA[%d]",
          this->m_objName,
          _port
      );
      this->m_to_readAsyncDMA[_port].setObjName(_portName);
#endif

    }

    // Initialize output port setParam

    for (
        NATIVE_INT_TYPE _port = 0;
        _port < this->getNum_to_setParam();
        ++_port
    ) {
      this->m_to_setParam[_port].init();

#if FW_OBJECT_NAMES == 1
      char _portName[128];
      snprintf(
          _portName,
          sizeof(_portName),
          "%s_to_setParam[%d]",
          this->m_objName,
          _port
      );
      this->m_to_setParam[_port].setObjName(_portName);
#endif

    }

    // Initialize output port PingRecv

    for (
        NATIVE_INT_TYPE _port = 0;
        _port < this->getNum_to_PingRecv();
        ++_port
    ) {
      this->m_to_PingRecv[_port].init();

#if FW_OBJECT_NAMES == 1
      char _portName[128];
      snprintf(
          _portName,
          sizeof(_portName),
          "%s_to_PingRecv[%d]",
          this->m_objName,
          _port
      );
      this->m_to_PingRecv[_port].setObjName(_portName);
#endif

    }

    // Initialize output port writeAsync

    for (
        NATIVE_INT_TYPE _port = 0;
        _port < this->getNum_to_writeAsync();
        ++_port
    ) {
      this->m_to_writeAsync[_port].init();

#if FW_OBJECT_NAMES == 1
      char _portName[128];
      snprintf(
          _portName,
          sizeof(_portName),
          "%s_to_writeAsync[%d]",
          this->m_objName,
          _port
      );
      this->m_to_writeAsync[_port].setObjName(_portName);
#endif

    }

    // Initialize output port resetLink

    for (
        NATIVE_INT_TYPE _port = 0;
        _port < this->getNum_to_resetLink();
        ++_port
    ) {
      this->m_to_resetLink[_port].init();

#if FW_OBJECT_NAMES == 1
      char _portName[128];
      snprintf(
          _portName,
          sizeof(_portName),
          "%s_to_resetLink[%d]",
          this->m_objName,
          _port
      );
      this->m_to_resetLink[_port].setObjName(_portName);
#endif

    }

    // Initialize output port schedIn

    for (
        NATIVE_INT_TYPE _port = 0;
        _port < this->getNum_to_schedIn();
        ++_port
    ) {
      this->m_to_schedIn[_port].init();

#if FW_OBJECT_NAMES == 1
      char _portName[128];
      snprintf(
          _portName,
          sizeof(_portName),
          "%s_to_schedIn[%d]",
          this->m_objName,
          _port
      );
      this->m_to_schedIn[_port].setObjName(_portName);
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
      char _portName[128];
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

    // Initialize output port readAsync

    for (
        NATIVE_INT_TYPE _port = 0;
        _port < this->getNum_to_readAsync();
        ++_port
    ) {
      this->m_to_readAsync[_port].init();

#if FW_OBJECT_NAMES == 1
      char _portName[128];
      snprintf(
          _portName,
          sizeof(_portName),
          "%s_to_readAsync[%d]",
          this->m_objName,
          _port
      );
      this->m_to_readAsync[_port].setObjName(_portName);
#endif

    }

  }

  // ----------------------------------------------------------------------
  // Getters for port counts
  // ----------------------------------------------------------------------

  NATIVE_INT_TYPE SPWManagerTesterBase ::
    getNum_to_read(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_to_read);
  }

  NATIVE_INT_TYPE SPWManagerTesterBase ::
    getNum_from_driverWriteRMAP(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_from_driverWriteRMAP);
  }

  NATIVE_INT_TYPE SPWManagerTesterBase ::
    getNum_from_cmdRegOut(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_from_cmdRegOut);
  }

  NATIVE_INT_TYPE SPWManagerTesterBase ::
    getNum_to_readAsyncDMA(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_to_readAsyncDMA);
  }

  NATIVE_INT_TYPE SPWManagerTesterBase ::
    getNum_from_statusOut(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_from_statusOut);
  }

  NATIVE_INT_TYPE SPWManagerTesterBase ::
    getNum_from_eventOut(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_from_eventOut);
  }

  NATIVE_INT_TYPE SPWManagerTesterBase ::
    getNum_to_setParam(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_to_setParam);
  }

  NATIVE_INT_TYPE SPWManagerTesterBase ::
    getNum_from_PingResponse(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_from_PingResponse);
  }

  NATIVE_INT_TYPE SPWManagerTesterBase ::
    getNum_to_PingRecv(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_to_PingRecv);
  }

  NATIVE_INT_TYPE SPWManagerTesterBase ::
    getNum_from_cmdResponseOut(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_from_cmdResponseOut);
  }

  NATIVE_INT_TYPE SPWManagerTesterBase ::
    getNum_from_driverReset(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_from_driverReset);
  }

  NATIVE_INT_TYPE SPWManagerTesterBase ::
    getNum_from_driverReadRMAP(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_from_driverReadRMAP);
  }

  NATIVE_INT_TYPE SPWManagerTesterBase ::
    getNum_to_writeAsync(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_to_writeAsync);
  }

  NATIVE_INT_TYPE SPWManagerTesterBase ::
    getNum_from_timeCaller(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_from_timeCaller);
  }

  NATIVE_INT_TYPE SPWManagerTesterBase ::
    getNum_to_resetLink(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_to_resetLink);
  }

  NATIVE_INT_TYPE SPWManagerTesterBase ::
    getNum_to_schedIn(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_to_schedIn);
  }

  NATIVE_INT_TYPE SPWManagerTesterBase ::
    getNum_to_cmdIn(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_to_cmdIn);
  }

  NATIVE_INT_TYPE SPWManagerTesterBase ::
    getNum_to_write(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_to_write);
  }

  NATIVE_INT_TYPE SPWManagerTesterBase ::
    getNum_to_readAsync(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_to_readAsync);
  }

  NATIVE_INT_TYPE SPWManagerTesterBase ::
    getNum_from_driverGetStatus(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_from_driverGetStatus);
  }

#if FW_ENABLE_TEXT_LOGGING == 1
  NATIVE_INT_TYPE SPWManagerTesterBase ::
    getNum_from_LogText(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_from_LogText);
  }
#endif

  // ----------------------------------------------------------------------
  // Connectors for to ports
  // ----------------------------------------------------------------------

  void SPWManagerTesterBase ::
    connect_to_read(
        const NATIVE_INT_TYPE portNum,
        Drv::InputSphinxSPW_SendRequestPort *const read
    )
  {
    FW_ASSERT(portNum < this->getNum_to_read(),static_cast<AssertArg>(portNum));
    this->m_to_read[portNum].addCallPort(read);
  }

  void SPWManagerTesterBase ::
    connect_to_readAsyncDMA(
        const NATIVE_INT_TYPE portNum,
        Drv::InputSphinxSPW_SendRequestPort *const readAsyncDMA
    )
  {
    FW_ASSERT(portNum < this->getNum_to_readAsyncDMA(),static_cast<AssertArg>(portNum));
    this->m_to_readAsyncDMA[portNum].addCallPort(readAsyncDMA);
  }

  void SPWManagerTesterBase ::
    connect_to_setParam(
        const NATIVE_INT_TYPE portNum,
        Drv::InputSphinxSPW_SetParamPort *const setParam
    )
  {
    FW_ASSERT(portNum < this->getNum_to_setParam(),static_cast<AssertArg>(portNum));
    this->m_to_setParam[portNum].addCallPort(setParam);
  }

  void SPWManagerTesterBase ::
    connect_to_PingRecv(
        const NATIVE_INT_TYPE portNum,
        Svc::InputPingPort *const PingRecv
    )
  {
    FW_ASSERT(portNum < this->getNum_to_PingRecv(),static_cast<AssertArg>(portNum));
    this->m_to_PingRecv[portNum].addCallPort(PingRecv);
  }

  void SPWManagerTesterBase ::
    connect_to_writeAsync(
        const NATIVE_INT_TYPE portNum,
        Drv::InputSphinxSPW_SendRequestPort *const writeAsync
    )
  {
    FW_ASSERT(portNum < this->getNum_to_writeAsync(),static_cast<AssertArg>(portNum));
    this->m_to_writeAsync[portNum].addCallPort(writeAsync);
  }

  void SPWManagerTesterBase ::
    connect_to_resetLink(
        const NATIVE_INT_TYPE portNum,
        Drv::InputSphinxSPW_TriggerPort *const resetLink
    )
  {
    FW_ASSERT(portNum < this->getNum_to_resetLink(),static_cast<AssertArg>(portNum));
    this->m_to_resetLink[portNum].addCallPort(resetLink);
  }

  void SPWManagerTesterBase ::
    connect_to_schedIn(
        const NATIVE_INT_TYPE portNum,
        Svc::InputSchedPort *const schedIn
    )
  {
    FW_ASSERT(portNum < this->getNum_to_schedIn(),static_cast<AssertArg>(portNum));
    this->m_to_schedIn[portNum].addCallPort(schedIn);
  }

  void SPWManagerTesterBase ::
    connect_to_cmdIn(
        const NATIVE_INT_TYPE portNum,
        Fw::InputCmdPort *const cmdIn
    )
  {
    FW_ASSERT(portNum < this->getNum_to_cmdIn(),static_cast<AssertArg>(portNum));
    this->m_to_cmdIn[portNum].addCallPort(cmdIn);
  }

  void SPWManagerTesterBase ::
    connect_to_write(
        const NATIVE_INT_TYPE portNum,
        Drv::InputSphinxSPW_SendRequestPort *const write
    )
  {
    FW_ASSERT(portNum < this->getNum_to_write(),static_cast<AssertArg>(portNum));
    this->m_to_write[portNum].addCallPort(write);
  }

  void SPWManagerTesterBase ::
    connect_to_readAsync(
        const NATIVE_INT_TYPE portNum,
        Drv::InputSphinxSPW_SendRequestPort *const readAsync
    )
  {
    FW_ASSERT(portNum < this->getNum_to_readAsync(),static_cast<AssertArg>(portNum));
    this->m_to_readAsync[portNum].addCallPort(readAsync);
  }


  // ----------------------------------------------------------------------
  // Invocation functions for to ports
  // ----------------------------------------------------------------------

  I32 SPWManagerTesterBase ::
    invoke_to_read(
        const NATIVE_INT_TYPE portNum,
        U32 addr,
        U32 num_bytes,
        U8 *buf,
        U32 buf_size,
        U32 timeout
    )
  {
    FW_ASSERT(portNum < this->getNum_to_read(),static_cast<AssertArg>(portNum));
    FW_ASSERT(portNum < this->getNum_to_read(),static_cast<AssertArg>(portNum));
    return this->m_to_read[portNum].invoke(
        addr, num_bytes, buf, buf_size, timeout
    );
  }

  I32 SPWManagerTesterBase ::
    invoke_to_readAsyncDMA(
        const NATIVE_INT_TYPE portNum,
        U32 addr,
        U32 num_bytes,
        U8 *buf,
        U32 buf_size,
        U32 timeout
    )
  {
    FW_ASSERT(portNum < this->getNum_to_readAsyncDMA(),static_cast<AssertArg>(portNum));
    FW_ASSERT(portNum < this->getNum_to_readAsyncDMA(),static_cast<AssertArg>(portNum));
    return this->m_to_readAsyncDMA[portNum].invoke(
        addr, num_bytes, buf, buf_size, timeout
    );
  }

  I32 SPWManagerTesterBase ::
    invoke_to_setParam(
        const NATIVE_INT_TYPE portNum,
        U8 dest_addr,
        U8 dest_key,
        U8 increment,
        U8 verify,
        U8 acknowledge
    )
  {
    FW_ASSERT(portNum < this->getNum_to_setParam(),static_cast<AssertArg>(portNum));
    FW_ASSERT(portNum < this->getNum_to_setParam(),static_cast<AssertArg>(portNum));
    return this->m_to_setParam[portNum].invoke(
        dest_addr, dest_key, increment, verify, acknowledge
    );
  }

  void SPWManagerTesterBase ::
    invoke_to_PingRecv(
        const NATIVE_INT_TYPE portNum,
        U32 key
    )
  {
    FW_ASSERT(portNum < this->getNum_to_PingRecv(),static_cast<AssertArg>(portNum));
    FW_ASSERT(portNum < this->getNum_to_PingRecv(),static_cast<AssertArg>(portNum));
    this->m_to_PingRecv[portNum].invoke(
        key
    );
  }

  I32 SPWManagerTesterBase ::
    invoke_to_writeAsync(
        const NATIVE_INT_TYPE portNum,
        U32 addr,
        U32 num_bytes,
        U8 *buf,
        U32 buf_size,
        U32 timeout
    )
  {
    FW_ASSERT(portNum < this->getNum_to_writeAsync(),static_cast<AssertArg>(portNum));
    FW_ASSERT(portNum < this->getNum_to_writeAsync(),static_cast<AssertArg>(portNum));
    return this->m_to_writeAsync[portNum].invoke(
        addr, num_bytes, buf, buf_size, timeout
    );
  }

  void SPWManagerTesterBase ::
    invoke_to_resetLink(
        const NATIVE_INT_TYPE portNum
    )
  {
    FW_ASSERT(portNum < this->getNum_to_resetLink(),static_cast<AssertArg>(portNum));
    FW_ASSERT(portNum < this->getNum_to_resetLink(),static_cast<AssertArg>(portNum));
    this->m_to_resetLink[portNum].invoke(

    );
  }

  void SPWManagerTesterBase ::
    invoke_to_schedIn(
        const NATIVE_INT_TYPE portNum,
        NATIVE_UINT_TYPE context
    )
  {
    FW_ASSERT(portNum < this->getNum_to_schedIn(),static_cast<AssertArg>(portNum));
    FW_ASSERT(portNum < this->getNum_to_schedIn(),static_cast<AssertArg>(portNum));
    this->m_to_schedIn[portNum].invoke(
        context
    );
  }

  I32 SPWManagerTesterBase ::
    invoke_to_write(
        const NATIVE_INT_TYPE portNum,
        U32 addr,
        U32 num_bytes,
        U8 *buf,
        U32 buf_size,
        U32 timeout
    )
  {
    FW_ASSERT(portNum < this->getNum_to_write(),static_cast<AssertArg>(portNum));
    FW_ASSERT(portNum < this->getNum_to_write(),static_cast<AssertArg>(portNum));
    return this->m_to_write[portNum].invoke(
        addr, num_bytes, buf, buf_size, timeout
    );
  }

  I32 SPWManagerTesterBase ::
    invoke_to_readAsync(
        const NATIVE_INT_TYPE portNum,
        U32 addr,
        U32 num_bytes,
        U8 *buf,
        U32 buf_size,
        U32 timeout
    )
  {
    FW_ASSERT(portNum < this->getNum_to_readAsync(),static_cast<AssertArg>(portNum));
    FW_ASSERT(portNum < this->getNum_to_readAsync(),static_cast<AssertArg>(portNum));
    return this->m_to_readAsync[portNum].invoke(
        addr, num_bytes, buf, buf_size, timeout
    );
  }

  // ----------------------------------------------------------------------
  // Connection status for to ports
  // ----------------------------------------------------------------------

  bool SPWManagerTesterBase ::
    isConnected_to_read(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_to_read(), static_cast<AssertArg>(portNum));
    return this->m_to_read[portNum].isConnected();
  }

  bool SPWManagerTesterBase ::
    isConnected_to_readAsyncDMA(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_to_readAsyncDMA(), static_cast<AssertArg>(portNum));
    return this->m_to_readAsyncDMA[portNum].isConnected();
  }

  bool SPWManagerTesterBase ::
    isConnected_to_setParam(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_to_setParam(), static_cast<AssertArg>(portNum));
    return this->m_to_setParam[portNum].isConnected();
  }

  bool SPWManagerTesterBase ::
    isConnected_to_PingRecv(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_to_PingRecv(), static_cast<AssertArg>(portNum));
    return this->m_to_PingRecv[portNum].isConnected();
  }

  bool SPWManagerTesterBase ::
    isConnected_to_writeAsync(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_to_writeAsync(), static_cast<AssertArg>(portNum));
    return this->m_to_writeAsync[portNum].isConnected();
  }

  bool SPWManagerTesterBase ::
    isConnected_to_resetLink(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_to_resetLink(), static_cast<AssertArg>(portNum));
    return this->m_to_resetLink[portNum].isConnected();
  }

  bool SPWManagerTesterBase ::
    isConnected_to_schedIn(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_to_schedIn(), static_cast<AssertArg>(portNum));
    return this->m_to_schedIn[portNum].isConnected();
  }

  bool SPWManagerTesterBase ::
    isConnected_to_cmdIn(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_to_cmdIn(), static_cast<AssertArg>(portNum));
    return this->m_to_cmdIn[portNum].isConnected();
  }

  bool SPWManagerTesterBase ::
    isConnected_to_write(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_to_write(), static_cast<AssertArg>(portNum));
    return this->m_to_write[portNum].isConnected();
  }

  bool SPWManagerTesterBase ::
    isConnected_to_readAsync(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_to_readAsync(), static_cast<AssertArg>(portNum));
    return this->m_to_readAsync[portNum].isConnected();
  }

  // ----------------------------------------------------------------------
  // Getters for from ports
  // ----------------------------------------------------------------------

  Drv::InputSphinxSPW_WriteRMAPPort *SPWManagerTesterBase ::
    get_from_driverWriteRMAP(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_from_driverWriteRMAP(),static_cast<AssertArg>(portNum));
    return &this->m_from_driverWriteRMAP[portNum];
  }

  Fw::InputCmdRegPort *SPWManagerTesterBase ::
    get_from_cmdRegOut(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_from_cmdRegOut(),static_cast<AssertArg>(portNum));
    return &this->m_from_cmdRegOut[portNum];
  }

  Drv::InputSphinxSPW_StatusOutPort *SPWManagerTesterBase ::
    get_from_statusOut(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_from_statusOut(),static_cast<AssertArg>(portNum));
    return &this->m_from_statusOut[portNum];
  }

  Fw::InputLogPort *SPWManagerTesterBase ::
    get_from_eventOut(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_from_eventOut(),static_cast<AssertArg>(portNum));
    return &this->m_from_eventOut[portNum];
  }

  Svc::InputPingPort *SPWManagerTesterBase ::
    get_from_PingResponse(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_from_PingResponse(),static_cast<AssertArg>(portNum));
    return &this->m_from_PingResponse[portNum];
  }

  Fw::InputCmdResponsePort *SPWManagerTesterBase ::
    get_from_cmdResponseOut(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_from_cmdResponseOut(),static_cast<AssertArg>(portNum));
    return &this->m_from_cmdResponseOut[portNum];
  }

  Drv::InputSphinxSPW_StatusPort *SPWManagerTesterBase ::
    get_from_driverReset(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_from_driverReset(),static_cast<AssertArg>(portNum));
    return &this->m_from_driverReset[portNum];
  }

  Drv::InputSphinxSPW_ReadRMAPPort *SPWManagerTesterBase ::
    get_from_driverReadRMAP(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_from_driverReadRMAP(),static_cast<AssertArg>(portNum));
    return &this->m_from_driverReadRMAP[portNum];
  }

  Fw::InputTimePort *SPWManagerTesterBase ::
    get_from_timeCaller(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_from_timeCaller(),static_cast<AssertArg>(portNum));
    return &this->m_from_timeCaller[portNum];
  }

  Drv::InputSphinxSPW_StatusPort *SPWManagerTesterBase ::
    get_from_driverGetStatus(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_from_driverGetStatus(),static_cast<AssertArg>(portNum));
    return &this->m_from_driverGetStatus[portNum];
  }

#if FW_ENABLE_TEXT_LOGGING == 1
  Fw::InputLogTextPort *SPWManagerTesterBase ::
    get_from_LogText(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_from_LogText(),static_cast<AssertArg>(portNum));
    return &this->m_from_LogText[portNum];
  }
#endif

  // ----------------------------------------------------------------------
  // Static functions for from ports
  // ----------------------------------------------------------------------

  I32 SPWManagerTesterBase ::
    from_driverWriteRMAP_static(
        Fw::PassiveComponentBase *const callComp,
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
    FW_ASSERT(callComp);
    SPWManagerTesterBase* _testerBase =
      static_cast<SPWManagerTesterBase*>(callComp);
    return _testerBase->from_driverWriteRMAP_handlerBase(
        portNum,
        dest_addr, dest_key, write_addr, buf_ptr, num_bytes, increment, verify, acknowledge
    );
  }

  void SPWManagerTesterBase ::
    from_statusOut_static(
        Fw::PassiveComponentBase *const callComp,
        const NATIVE_INT_TYPE portNum,
        I32 spwStatus
    )
  {
    FW_ASSERT(callComp);
    SPWManagerTesterBase* _testerBase =
      static_cast<SPWManagerTesterBase*>(callComp);
    _testerBase->from_statusOut_handlerBase(
        portNum,
        spwStatus
    );
  }

  void SPWManagerTesterBase ::
    from_PingResponse_static(
        Fw::PassiveComponentBase *const callComp,
        const NATIVE_INT_TYPE portNum,
        U32 key
    )
  {
    FW_ASSERT(callComp);
    SPWManagerTesterBase* _testerBase =
      static_cast<SPWManagerTesterBase*>(callComp);
    _testerBase->from_PingResponse_handlerBase(
        portNum,
        key
    );
  }

  I32 SPWManagerTesterBase ::
    from_driverReset_static(
        Fw::PassiveComponentBase *const callComp,
        const NATIVE_INT_TYPE portNum
    )
  {
    FW_ASSERT(callComp);
    SPWManagerTesterBase* _testerBase =
      static_cast<SPWManagerTesterBase*>(callComp);
    return _testerBase->from_driverReset_handlerBase(portNum);
  }

  I32 SPWManagerTesterBase ::
    from_driverReadRMAP_static(
        Fw::PassiveComponentBase *const callComp,
        const NATIVE_INT_TYPE portNum,
        U8 dest_addr,
        U8 dest_key,
        U32 read_addr,
        U8 *buf_ptr,
        U32 num_bytes,
        U8 increment
    )
  {
    FW_ASSERT(callComp);
    SPWManagerTesterBase* _testerBase =
      static_cast<SPWManagerTesterBase*>(callComp);
    return _testerBase->from_driverReadRMAP_handlerBase(
        portNum,
        dest_addr, dest_key, read_addr, buf_ptr, num_bytes, increment
    );
  }

  I32 SPWManagerTesterBase ::
    from_driverGetStatus_static(
        Fw::PassiveComponentBase *const callComp,
        const NATIVE_INT_TYPE portNum
    )
  {
    FW_ASSERT(callComp);
    SPWManagerTesterBase* _testerBase =
      static_cast<SPWManagerTesterBase*>(callComp);
    return _testerBase->from_driverGetStatus_handlerBase(portNum);
  }

  void SPWManagerTesterBase ::
    from_cmdResponseOut_static(
        Fw::PassiveComponentBase *const component,
        const NATIVE_INT_TYPE portNum,
        const FwOpcodeType opCode,
        const U32 cmdSeq,
        const Fw::CommandResponse response
    )
  {
    SPWManagerTesterBase* _testerBase =
      static_cast<SPWManagerTesterBase*>(component);
    _testerBase->cmdResponseIn(opCode, cmdSeq, response);
  }

  void SPWManagerTesterBase ::
    from_cmdRegOut_static(
        Fw::PassiveComponentBase *const component,
        const NATIVE_INT_TYPE portNum,
        const FwOpcodeType opCode
    )
  {

  }

  void SPWManagerTesterBase ::
    from_eventOut_static(
        Fw::PassiveComponentBase *const component,
        const NATIVE_INT_TYPE portNum,
        FwEventIdType id,
        Fw::Time &timeTag,
        Fw::LogSeverity severity,
        Fw::LogBuffer &args
    )
  {
    SPWManagerTesterBase* _testerBase =
      static_cast<SPWManagerTesterBase*>(component);
    _testerBase->dispatchEvents(id, timeTag, severity, args);
  }

#if FW_ENABLE_TEXT_LOGGING == 1
  void SPWManagerTesterBase ::
    from_LogText_static(
        Fw::PassiveComponentBase *const component,
        const NATIVE_INT_TYPE portNum,
        FwEventIdType id,
        Fw::Time &timeTag,
        Fw::TextLogSeverity severity,
        Fw::TextLogString &text
    )
  {
    SPWManagerTesterBase* _testerBase =
      static_cast<SPWManagerTesterBase*>(component);
    _testerBase->textLogIn(id,timeTag,severity,text);
  }
#endif

  void SPWManagerTesterBase ::
    from_timeCaller_static(
        Fw::PassiveComponentBase *const component,
        const NATIVE_INT_TYPE portNum,
        Fw::Time& time
    )
  {
    SPWManagerTesterBase* _testerBase =
      static_cast<SPWManagerTesterBase*>(component);
    time = _testerBase->m_testTime;
  }

  // ----------------------------------------------------------------------
  // Histories for typed from ports
  // ----------------------------------------------------------------------

  void SPWManagerTesterBase ::
    clearFromPortHistory(void)
  {
    this->fromPortHistorySize = 0;
    this->fromPortHistory_driverWriteRMAP->clear();
    this->fromPortHistory_statusOut->clear();
    this->fromPortHistory_PingResponse->clear();
    this->fromPortHistorySize_driverReset = 0;
    this->fromPortHistory_driverReadRMAP->clear();
    this->fromPortHistorySize_driverGetStatus = 0;
  }

  // ----------------------------------------------------------------------
  // From port: driverWriteRMAP
  // ----------------------------------------------------------------------

  void SPWManagerTesterBase ::
    pushFromPortEntry_driverWriteRMAP(
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
    FromPortEntry_driverWriteRMAP _e = {
      dest_addr, dest_key, write_addr, buf_ptr, num_bytes, increment, verify, acknowledge
    };
    this->fromPortHistory_driverWriteRMAP->push_back(_e);
    ++this->fromPortHistorySize;
  }

  // ----------------------------------------------------------------------
  // From port: statusOut
  // ----------------------------------------------------------------------

  void SPWManagerTesterBase ::
    pushFromPortEntry_statusOut(
        I32 spwStatus
    )
  {
    FromPortEntry_statusOut _e = {
      spwStatus
    };
    this->fromPortHistory_statusOut->push_back(_e);
    ++this->fromPortHistorySize;
  }

  // ----------------------------------------------------------------------
  // From port: PingResponse
  // ----------------------------------------------------------------------

  void SPWManagerTesterBase ::
    pushFromPortEntry_PingResponse(
        U32 key
    )
  {
    FromPortEntry_PingResponse _e = {
      key
    };
    this->fromPortHistory_PingResponse->push_back(_e);
    ++this->fromPortHistorySize;
  }

  // ----------------------------------------------------------------------
  // From port: driverReset
  // ----------------------------------------------------------------------

  void SPWManagerTesterBase ::
    pushFromPortEntry_driverReset(
        void
    )
  {
    ++this->fromPortHistorySize_driverReset;
    ++this->fromPortHistorySize;
  }

  // ----------------------------------------------------------------------
  // From port: driverReadRMAP
  // ----------------------------------------------------------------------

  void SPWManagerTesterBase ::
    pushFromPortEntry_driverReadRMAP(
        U8 dest_addr,
        U8 dest_key,
        U32 read_addr,
        U8 *buf_ptr,
        U32 num_bytes,
        U8 increment
    )
  {
    FromPortEntry_driverReadRMAP _e = {
      dest_addr, dest_key, read_addr, buf_ptr, num_bytes, increment
    };
    this->fromPortHistory_driverReadRMAP->push_back(_e);
    ++this->fromPortHistorySize;
  }

  // ----------------------------------------------------------------------
  // From port: driverGetStatus
  // ----------------------------------------------------------------------

  void SPWManagerTesterBase ::
    pushFromPortEntry_driverGetStatus(
        void
    )
  {
    ++this->fromPortHistorySize_driverGetStatus;
    ++this->fromPortHistorySize;
  }

  // ----------------------------------------------------------------------
  // Handler base functions for from ports
  // ----------------------------------------------------------------------

  I32 SPWManagerTesterBase ::
    from_driverWriteRMAP_handlerBase(
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
    FW_ASSERT(portNum < this->getNum_from_driverWriteRMAP(),static_cast<AssertArg>(portNum));
    return this->from_driverWriteRMAP_handler(
        portNum,
        dest_addr, dest_key, write_addr, buf_ptr, num_bytes, increment, verify, acknowledge
    );
  }

  void SPWManagerTesterBase ::
    from_statusOut_handlerBase(
        const NATIVE_INT_TYPE portNum,
        I32 spwStatus
    )
  {
    FW_ASSERT(portNum < this->getNum_from_statusOut(),static_cast<AssertArg>(portNum));
    this->from_statusOut_handler(
        portNum,
        spwStatus
    );
  }

  void SPWManagerTesterBase ::
    from_PingResponse_handlerBase(
        const NATIVE_INT_TYPE portNum,
        U32 key
    )
  {
    FW_ASSERT(portNum < this->getNum_from_PingResponse(),static_cast<AssertArg>(portNum));
    this->from_PingResponse_handler(
        portNum,
        key
    );
  }

  I32 SPWManagerTesterBase ::
    from_driverReset_handlerBase(
        const NATIVE_INT_TYPE portNum
    )
  {
    FW_ASSERT(portNum < this->getNum_from_driverReset(),static_cast<AssertArg>(portNum));
    return this->from_driverReset_handler(portNum);
  }

  I32 SPWManagerTesterBase ::
    from_driverReadRMAP_handlerBase(
        const NATIVE_INT_TYPE portNum,
        U8 dest_addr,
        U8 dest_key,
        U32 read_addr,
        U8 *buf_ptr,
        U32 num_bytes,
        U8 increment
    )
  {
    FW_ASSERT(portNum < this->getNum_from_driverReadRMAP(),static_cast<AssertArg>(portNum));
    return this->from_driverReadRMAP_handler(
        portNum,
        dest_addr, dest_key, read_addr, buf_ptr, num_bytes, increment
    );
  }

  I32 SPWManagerTesterBase ::
    from_driverGetStatus_handlerBase(
        const NATIVE_INT_TYPE portNum
    )
  {
    FW_ASSERT(portNum < this->getNum_from_driverGetStatus(),static_cast<AssertArg>(portNum));
    return this->from_driverGetStatus_handler(portNum);
  }

  // ----------------------------------------------------------------------
  // Command response handling
  // ----------------------------------------------------------------------

  void SPWManagerTesterBase ::
    cmdResponseIn(
        const FwOpcodeType opCode,
        const U32 seq,
        const Fw::CommandResponse response
    )
  {
    CmdResponse e = { opCode, seq, response };
    this->cmdResponseHistory->push_back(e);
  }

  // ----------------------------------------------------------------------
  // Command: SPWMGR_RMAP_WRITE_WORD
  // ----------------------------------------------------------------------

  void SPWManagerTesterBase ::
    sendCmd_SPWMGR_RMAP_WRITE_WORD(
        const NATIVE_INT_TYPE instance,
        const U32 cmdSeq,
        U32 targetAddress,
        U32 value,
        U32 timeout
    )
  {

    // Serialize arguments

    Fw::CmdArgBuffer buff;
    Fw::SerializeStatus _status;
    _status = buff.serialize(targetAddress);
    FW_ASSERT(_status == Fw::FW_SERIALIZE_OK,static_cast<AssertArg>(_status));
    _status = buff.serialize(value);
    FW_ASSERT(_status == Fw::FW_SERIALIZE_OK,static_cast<AssertArg>(_status));
    _status = buff.serialize(timeout);
    FW_ASSERT(_status == Fw::FW_SERIALIZE_OK,static_cast<AssertArg>(_status));

    // Call output command port

    FwOpcodeType _opcode;
    const U32 idBase = this->getIdBase();
    _opcode = SPWManagerComponentBase::OPCODE_SPWMGR_RMAP_WRITE_WORD + idBase;

    if (this->m_to_cmdIn[0].isConnected()) {
      this->m_to_cmdIn[0].invoke(
          _opcode,
          cmdSeq,
          buff
      );
    }
    else {
      printf("Test Command Output port not connected!\n");
    }

  }

  // ----------------------------------------------------------------------
  // Command: SPWMGR_RMAP_READ_WORD
  // ----------------------------------------------------------------------

  void SPWManagerTesterBase ::
    sendCmd_SPWMGR_RMAP_READ_WORD(
        const NATIVE_INT_TYPE instance,
        const U32 cmdSeq,
        U32 targetAddress,
        U32 timeout
    )
  {

    // Serialize arguments

    Fw::CmdArgBuffer buff;
    Fw::SerializeStatus _status;
    _status = buff.serialize(targetAddress);
    FW_ASSERT(_status == Fw::FW_SERIALIZE_OK,static_cast<AssertArg>(_status));
    _status = buff.serialize(timeout);
    FW_ASSERT(_status == Fw::FW_SERIALIZE_OK,static_cast<AssertArg>(_status));

    // Call output command port

    FwOpcodeType _opcode;
    const U32 idBase = this->getIdBase();
    _opcode = SPWManagerComponentBase::OPCODE_SPWMGR_RMAP_READ_WORD + idBase;

    if (this->m_to_cmdIn[0].isConnected()) {
      this->m_to_cmdIn[0].invoke(
          _opcode,
          cmdSeq,
          buff
      );
    }
    else {
      printf("Test Command Output port not connected!\n");
    }

  }

  // ----------------------------------------------------------------------
  // Command: SPWMGR_RESET_LINK
  // ----------------------------------------------------------------------

  void SPWManagerTesterBase ::
    sendCmd_SPWMGR_RESET_LINK(
        const NATIVE_INT_TYPE instance,
        const U32 cmdSeq
    )
  {

    // Serialize arguments

    Fw::CmdArgBuffer buff;

    // Call output command port

    FwOpcodeType _opcode;
    const U32 idBase = this->getIdBase();
    _opcode = SPWManagerComponentBase::OPCODE_SPWMGR_RESET_LINK + idBase;

    if (this->m_to_cmdIn[0].isConnected()) {
      this->m_to_cmdIn[0].invoke(
          _opcode,
          cmdSeq,
          buff
      );
    }
    else {
      printf("Test Command Output port not connected!\n");
    }

  }

  // ----------------------------------------------------------------------
  // Command: SPWMGR_SET_PARAMS
  // ----------------------------------------------------------------------

  void SPWManagerTesterBase ::
    sendCmd_SPWMGR_SET_PARAMS(
        const NATIVE_INT_TYPE instance,
        const U32 cmdSeq,
        U8 destinationAddress,
        U8 destinationKey,
        U8 increment,
        U8 verify,
        U8 acknowledge
    )
  {

    // Serialize arguments

    Fw::CmdArgBuffer buff;
    Fw::SerializeStatus _status;
    _status = buff.serialize(destinationAddress);
    FW_ASSERT(_status == Fw::FW_SERIALIZE_OK,static_cast<AssertArg>(_status));
    _status = buff.serialize(destinationKey);
    FW_ASSERT(_status == Fw::FW_SERIALIZE_OK,static_cast<AssertArg>(_status));
    _status = buff.serialize(increment);
    FW_ASSERT(_status == Fw::FW_SERIALIZE_OK,static_cast<AssertArg>(_status));
    _status = buff.serialize(verify);
    FW_ASSERT(_status == Fw::FW_SERIALIZE_OK,static_cast<AssertArg>(_status));
    _status = buff.serialize(acknowledge);
    FW_ASSERT(_status == Fw::FW_SERIALIZE_OK,static_cast<AssertArg>(_status));

    // Call output command port

    FwOpcodeType _opcode;
    const U32 idBase = this->getIdBase();
    _opcode = SPWManagerComponentBase::OPCODE_SPWMGR_SET_PARAMS + idBase;

    if (this->m_to_cmdIn[0].isConnected()) {
      this->m_to_cmdIn[0].invoke(
          _opcode,
          cmdSeq,
          buff
      );
    }
    else {
      printf("Test Command Output port not connected!\n");
    }

  }


  void SPWManagerTesterBase ::
    sendRawCmd(FwOpcodeType opcode, U32 cmdSeq, Fw::CmdArgBuffer& args) {

    const U32 idBase = this->getIdBase();
    FwOpcodeType _opcode = opcode + idBase;
    if (this->m_to_cmdIn[0].isConnected()) {
      this->m_to_cmdIn[0].invoke(
          _opcode,
          cmdSeq,
          args
      );
    }
    else {
      printf("Test Command Output port not connected!\n");
    }

  }

  // ----------------------------------------------------------------------
  // History
  // ----------------------------------------------------------------------

  void SPWManagerTesterBase ::
    clearHistory()
  {
    this->cmdResponseHistory->clear();
    this->textLogHistory->clear();
    this->clearEvents();
    this->clearFromPortHistory();
  }

  // ----------------------------------------------------------------------
  // Time
  // ----------------------------------------------------------------------

  void SPWManagerTesterBase ::
    setTestTime(const Fw::Time& time)
  {
    this->m_testTime = time;
  }

  // ----------------------------------------------------------------------
  // Event dispatch
  // ----------------------------------------------------------------------

  void SPWManagerTesterBase ::
    dispatchEvents(
        const FwEventIdType id,
        Fw::Time &timeTag,
        const Fw::LogSeverity severity,
        Fw::LogBuffer &args
    )
  {

    args.resetDeser();

    const U32 idBase = this->getIdBase();
    FW_ASSERT(id >= idBase, id, idBase);
    switch (id - idBase) {

      case SPWManagerComponentBase::EVENTID_SPWMANAGER_SPACEWIREINITIALIZATIONERROR:
      {

        Fw::SerializeStatus _status = Fw::FW_SERIALIZE_OK;
#if FW_AMPCS_COMPATIBLE
        // Deserialize the number of arguments.
        U8 _numArgs;
        _status = args.deserialize(_numArgs);
        FW_ASSERT(
          _status == Fw::FW_SERIALIZE_OK,
          static_cast<AssertArg>(_status)
        );
        // verify they match expected.
        FW_ASSERT(_numArgs == 1,_numArgs,1);

#endif
        I32 status;
#if FW_AMPCS_COMPATIBLE
        {
          // Deserialize the argument size
          U8 _argSize;
          _status = args.deserialize(_argSize);
          FW_ASSERT(
            _status == Fw::FW_SERIALIZE_OK,
            static_cast<AssertArg>(_status)
          );
          FW_ASSERT(_argSize == sizeof(I32),_argSize,sizeof(I32));
        }
#endif
        _status = args.deserialize(status);
        FW_ASSERT(
            _status == Fw::FW_SERIALIZE_OK,
            static_cast<AssertArg>(_status)
        );

        this->logIn_WARNING_HI_SPWManager_SpaceWireInitializationError(status);

        break;

      }

      case SPWManagerComponentBase::EVENTID_SPWMANAGER_SPACEWIRELINKDISCONNECTED:
      {

#if FW_AMPCS_COMPATIBLE
        // For AMPCS, decode zero arguments
        Fw::SerializeStatus _zero_status = Fw::FW_SERIALIZE_OK;
        U8 _noArgs;
        _zero_status = args.deserialize(_noArgs);
        FW_ASSERT(
            _zero_status == Fw::FW_SERIALIZE_OK,
            static_cast<AssertArg>(_zero_status)
        );
#endif
        this->logIn_WARNING_HI_SPWManager_SpaceWireLinkDisconnected();

        break;

      }

      case SPWManagerComponentBase::EVENTID_SPWMANAGER_SPACEWIREERROR:
      {

        Fw::SerializeStatus _status = Fw::FW_SERIALIZE_OK;
#if FW_AMPCS_COMPATIBLE
        // Deserialize the number of arguments.
        U8 _numArgs;
        _status = args.deserialize(_numArgs);
        FW_ASSERT(
          _status == Fw::FW_SERIALIZE_OK,
          static_cast<AssertArg>(_status)
        );
        // verify they match expected.
        FW_ASSERT(_numArgs == 2,_numArgs,2);

#endif
#if FW_AMPCS_COMPATIBLE
        {
          // Deserialize the argument size
          U8 _argSize;
          _status = args.deserialize(_argSize);
          FW_ASSERT(
            _status == Fw::FW_SERIALIZE_OK,
            static_cast<AssertArg>(_status)
          );
          FW_ASSERT(_argSize == sizeof(FwEnumStoreType),_argSize,sizeof(FwEnumStoreType));
        }
#endif
        FwEnumStoreType statusInt;
        _status = args.deserialize(statusInt);
        SPWManagerComponentBase::SpaceWireError_status status = static_cast<SPWManagerComponentBase::SpaceWireError_status>(statusInt);
        FW_ASSERT(
            _status == Fw::FW_SERIALIZE_OK,
            static_cast<AssertArg>(_status)
        );

        I32 statusCode;
#if FW_AMPCS_COMPATIBLE
        {
          // Deserialize the argument size
          U8 _argSize;
          _status = args.deserialize(_argSize);
          FW_ASSERT(
            _status == Fw::FW_SERIALIZE_OK,
            static_cast<AssertArg>(_status)
          );
          FW_ASSERT(_argSize == sizeof(I32),_argSize,sizeof(I32));
        }
#endif
        _status = args.deserialize(statusCode);
        FW_ASSERT(
            _status == Fw::FW_SERIALIZE_OK,
            static_cast<AssertArg>(_status)
        );

        this->logIn_WARNING_HI_SPWManager_SpaceWireError(status, statusCode);

        break;

      }

      case SPWManagerComponentBase::EVENTID_SPWMANAGER_SPACEWIRETRANSACTIONTIMEOUT:
      {

        Fw::SerializeStatus _status = Fw::FW_SERIALIZE_OK;
#if FW_AMPCS_COMPATIBLE
        // Deserialize the number of arguments.
        U8 _numArgs;
        _status = args.deserialize(_numArgs);
        FW_ASSERT(
          _status == Fw::FW_SERIALIZE_OK,
          static_cast<AssertArg>(_status)
        );
        // verify they match expected.
        FW_ASSERT(_numArgs == 4,_numArgs,4);

#endif
        U32 timeout;
#if FW_AMPCS_COMPATIBLE
        {
          // Deserialize the argument size
          U8 _argSize;
          _status = args.deserialize(_argSize);
          FW_ASSERT(
            _status == Fw::FW_SERIALIZE_OK,
            static_cast<AssertArg>(_status)
          );
          FW_ASSERT(_argSize == sizeof(U32),_argSize,sizeof(U32));
        }
#endif
        _status = args.deserialize(timeout);
        FW_ASSERT(
            _status == Fw::FW_SERIALIZE_OK,
            static_cast<AssertArg>(_status)
        );

#if FW_AMPCS_COMPATIBLE
        {
          // Deserialize the argument size
          U8 _argSize;
          _status = args.deserialize(_argSize);
          FW_ASSERT(
            _status == Fw::FW_SERIALIZE_OK,
            static_cast<AssertArg>(_status)
          );
          FW_ASSERT(_argSize == sizeof(FwEnumStoreType),_argSize,sizeof(FwEnumStoreType));
        }
#endif
        FwEnumStoreType commandInt;
        _status = args.deserialize(commandInt);
        SPWManagerComponentBase::SpaceWireTransactionTimeout_command command = static_cast<SPWManagerComponentBase::SpaceWireTransactionTimeout_command>(commandInt);
        FW_ASSERT(
            _status == Fw::FW_SERIALIZE_OK,
            static_cast<AssertArg>(_status)
        );

        U32 address;
#if FW_AMPCS_COMPATIBLE
        {
          // Deserialize the argument size
          U8 _argSize;
          _status = args.deserialize(_argSize);
          FW_ASSERT(
            _status == Fw::FW_SERIALIZE_OK,
            static_cast<AssertArg>(_status)
          );
          FW_ASSERT(_argSize == sizeof(U32),_argSize,sizeof(U32));
        }
#endif
        _status = args.deserialize(address);
        FW_ASSERT(
            _status == Fw::FW_SERIALIZE_OK,
            static_cast<AssertArg>(_status)
        );

#if FW_AMPCS_COMPATIBLE
        {
          // Deserialize the argument size
          U8 _argSize;
          _status = args.deserialize(_argSize);
          FW_ASSERT(
            _status == Fw::FW_SERIALIZE_OK,
            static_cast<AssertArg>(_status)
          );
          FW_ASSERT(_argSize == sizeof(FwEnumStoreType),_argSize,sizeof(FwEnumStoreType));
        }
#endif
        FwEnumStoreType statusInt;
        _status = args.deserialize(statusInt);
        SPWManagerComponentBase::SpaceWireTransactionTimeout_status status = static_cast<SPWManagerComponentBase::SpaceWireTransactionTimeout_status>(statusInt);
        FW_ASSERT(
            _status == Fw::FW_SERIALIZE_OK,
            static_cast<AssertArg>(_status)
        );

        this->logIn_WARNING_HI_SPWManager_SpaceWireTransactionTimeout(timeout, command, address, status);

        break;

      }

      case SPWManagerComponentBase::EVENTID_SPWMANAGER_RMAPWRITERESULT:
      {

        Fw::SerializeStatus _status = Fw::FW_SERIALIZE_OK;
#if FW_AMPCS_COMPATIBLE
        // Deserialize the number of arguments.
        U8 _numArgs;
        _status = args.deserialize(_numArgs);
        FW_ASSERT(
          _status == Fw::FW_SERIALIZE_OK,
          static_cast<AssertArg>(_status)
        );
        // verify they match expected.
        FW_ASSERT(_numArgs == 1,_numArgs,1);

#endif
        U32 address;
#if FW_AMPCS_COMPATIBLE
        {
          // Deserialize the argument size
          U8 _argSize;
          _status = args.deserialize(_argSize);
          FW_ASSERT(
            _status == Fw::FW_SERIALIZE_OK,
            static_cast<AssertArg>(_status)
          );
          FW_ASSERT(_argSize == sizeof(U32),_argSize,sizeof(U32));
        }
#endif
        _status = args.deserialize(address);
        FW_ASSERT(
            _status == Fw::FW_SERIALIZE_OK,
            static_cast<AssertArg>(_status)
        );

        this->logIn_ACTIVITY_LO_SPWManager_RMAPWriteResult(address);

        break;

      }

      case SPWManagerComponentBase::EVENTID_SPWMANAGER_RMAPREADRESULT:
      {

        Fw::SerializeStatus _status = Fw::FW_SERIALIZE_OK;
#if FW_AMPCS_COMPATIBLE
        // Deserialize the number of arguments.
        U8 _numArgs;
        _status = args.deserialize(_numArgs);
        FW_ASSERT(
          _status == Fw::FW_SERIALIZE_OK,
          static_cast<AssertArg>(_status)
        );
        // verify they match expected.
        FW_ASSERT(_numArgs == 2,_numArgs,2);

#endif
        U32 address;
#if FW_AMPCS_COMPATIBLE
        {
          // Deserialize the argument size
          U8 _argSize;
          _status = args.deserialize(_argSize);
          FW_ASSERT(
            _status == Fw::FW_SERIALIZE_OK,
            static_cast<AssertArg>(_status)
          );
          FW_ASSERT(_argSize == sizeof(U32),_argSize,sizeof(U32));
        }
#endif
        _status = args.deserialize(address);
        FW_ASSERT(
            _status == Fw::FW_SERIALIZE_OK,
            static_cast<AssertArg>(_status)
        );

        U32 value;
#if FW_AMPCS_COMPATIBLE
        {
          // Deserialize the argument size
          U8 _argSize;
          _status = args.deserialize(_argSize);
          FW_ASSERT(
            _status == Fw::FW_SERIALIZE_OK,
            static_cast<AssertArg>(_status)
          );
          FW_ASSERT(_argSize == sizeof(U32),_argSize,sizeof(U32));
        }
#endif
        _status = args.deserialize(value);
        FW_ASSERT(
            _status == Fw::FW_SERIALIZE_OK,
            static_cast<AssertArg>(_status)
        );

        this->logIn_ACTIVITY_LO_SPWManager_RMAPReadResult(address, value);

        break;

      }

      case SPWManagerComponentBase::EVENTID_SPWMANAGER_BUSY:
      {

#if FW_AMPCS_COMPATIBLE
        // For AMPCS, decode zero arguments
        Fw::SerializeStatus _zero_status = Fw::FW_SERIALIZE_OK;
        U8 _noArgs;
        _zero_status = args.deserialize(_noArgs);
        FW_ASSERT(
            _zero_status == Fw::FW_SERIALIZE_OK,
            static_cast<AssertArg>(_zero_status)
        );
#endif
        this->logIn_WARNING_LO_SPWManager_Busy();

        break;

      }

      case SPWManagerComponentBase::EVENTID_SPWMANAGER_RESETLINK:
      {

        Fw::SerializeStatus _status = Fw::FW_SERIALIZE_OK;
#if FW_AMPCS_COMPATIBLE
        // Deserialize the number of arguments.
        U8 _numArgs;
        _status = args.deserialize(_numArgs);
        FW_ASSERT(
          _status == Fw::FW_SERIALIZE_OK,
          static_cast<AssertArg>(_status)
        );
        // verify they match expected.
        FW_ASSERT(_numArgs == 1,_numArgs,1);

#endif
        U32 numAborted;
#if FW_AMPCS_COMPATIBLE
        {
          // Deserialize the argument size
          U8 _argSize;
          _status = args.deserialize(_argSize);
          FW_ASSERT(
            _status == Fw::FW_SERIALIZE_OK,
            static_cast<AssertArg>(_status)
          );
          FW_ASSERT(_argSize == sizeof(U32),_argSize,sizeof(U32));
        }
#endif
        _status = args.deserialize(numAborted);
        FW_ASSERT(
            _status == Fw::FW_SERIALIZE_OK,
            static_cast<AssertArg>(_status)
        );

        this->logIn_ACTIVITY_LO_SPWManager_ResetLink(numAborted);

        break;

      }

      default: {
        FW_ASSERT(0, id);
        break;
      }

    }

  }

  void SPWManagerTesterBase ::
    clearEvents(void)
  {
    this->eventsSize = 0;
    this->eventHistory_SPWManager_SpaceWireInitializationError->clear();
    this->eventsSize_SPWManager_SpaceWireLinkDisconnected = 0;
    this->eventHistory_SPWManager_SpaceWireError->clear();
    this->eventHistory_SPWManager_SpaceWireTransactionTimeout->clear();
    this->eventHistory_SPWManager_RMAPWriteResult->clear();
    this->eventHistory_SPWManager_RMAPReadResult->clear();
    this->eventsSize_SPWManager_Busy = 0;
    this->eventHistory_SPWManager_ResetLink->clear();
  }

#if FW_ENABLE_TEXT_LOGGING

  // ----------------------------------------------------------------------
  // Text events
  // ----------------------------------------------------------------------

  void SPWManagerTesterBase ::
    textLogIn(
        const U32 id,
        Fw::Time &timeTag,
        const Fw::TextLogSeverity severity,
        const Fw::TextLogString &text
    )
  {
    TextLogEntry e = { id, timeTag, severity, text };
    textLogHistory->push_back(e);
  }

  void SPWManagerTesterBase ::
    printTextLogHistoryEntry(
        const TextLogEntry& e,
        FILE* file
    )
  {
    const char *severityString = "UNKNOWN";
    switch (e.severity) {
      case Fw::LOG_FATAL:
        severityString = "FATAL";
        break;
      case Fw::LOG_WARNING_HI:
        severityString = "WARNING_HI";
        break;
      case Fw::LOG_WARNING_LO:
        severityString = "WARNING_LO";
        break;
      case Fw::LOG_COMMAND:
        severityString = "COMMAND";
        break;
      case Fw::LOG_ACTIVITY_HI:
        severityString = "ACTIVITY_HI";
        break;
      case Fw::LOG_ACTIVITY_LO:
        severityString = "ACTIVITY_LO";
        break;
      case Fw::LOG_DIAGNOSTIC:
       severityString = "DIAGNOSTIC";
        break;
      default:
        severityString = "SEVERITY ERROR";
        break;
    }

    fprintf(
        file,
        "EVENT: (%d) (%d:%d,%d) %s: %s\n",
        e.id,
        const_cast<TextLogEntry&>(e).timeTag.getTimeBase(),
        const_cast<TextLogEntry&>(e).timeTag.getSeconds(),
        const_cast<TextLogEntry&>(e).timeTag.getUSeconds(),
        severityString,
        e.text.toChar()
    );

  }

  void SPWManagerTesterBase ::
    printTextLogHistory(FILE *file)
  {
    for (U32 i = 0; i < this->textLogHistory->size(); ++i) {
      this->printTextLogHistoryEntry(
          this->textLogHistory->at(i),
          file
      );
    }
  }

#endif

  // ----------------------------------------------------------------------
  // Event: SPWManager_SpaceWireInitializationError
  // ----------------------------------------------------------------------

  void SPWManagerTesterBase ::
    logIn_WARNING_HI_SPWManager_SpaceWireInitializationError(
        I32 status
    )
  {
    EventEntry_SPWManager_SpaceWireInitializationError e = {
      status
    };
    eventHistory_SPWManager_SpaceWireInitializationError->push_back(e);
    ++this->eventsSize;
  }

  // ----------------------------------------------------------------------
  // Event: SPWManager_SpaceWireLinkDisconnected
  // ----------------------------------------------------------------------

  void SPWManagerTesterBase ::
    logIn_WARNING_HI_SPWManager_SpaceWireLinkDisconnected(
        void
    )
  {
    ++this->eventsSize_SPWManager_SpaceWireLinkDisconnected;
    ++this->eventsSize;
  }

  // ----------------------------------------------------------------------
  // Event: SPWManager_SpaceWireError
  // ----------------------------------------------------------------------

  void SPWManagerTesterBase ::
    logIn_WARNING_HI_SPWManager_SpaceWireError(
        SPWManagerComponentBase::SpaceWireError_status status,
        I32 statusCode
    )
  {
    EventEntry_SPWManager_SpaceWireError e = {
      status, statusCode
    };
    eventHistory_SPWManager_SpaceWireError->push_back(e);
    ++this->eventsSize;
  }

  // ----------------------------------------------------------------------
  // Event: SPWManager_SpaceWireTransactionTimeout
  // ----------------------------------------------------------------------

  void SPWManagerTesterBase ::
    logIn_WARNING_HI_SPWManager_SpaceWireTransactionTimeout(
        U32 timeout,
        SPWManagerComponentBase::SpaceWireTransactionTimeout_command command,
        U32 address,
        SPWManagerComponentBase::SpaceWireTransactionTimeout_status status
    )
  {
    EventEntry_SPWManager_SpaceWireTransactionTimeout e = {
      timeout, command, address, status
    };
    eventHistory_SPWManager_SpaceWireTransactionTimeout->push_back(e);
    ++this->eventsSize;
  }

  // ----------------------------------------------------------------------
  // Event: SPWManager_RMAPWriteResult
  // ----------------------------------------------------------------------

  void SPWManagerTesterBase ::
    logIn_ACTIVITY_LO_SPWManager_RMAPWriteResult(
        U32 address
    )
  {
    EventEntry_SPWManager_RMAPWriteResult e = {
      address
    };
    eventHistory_SPWManager_RMAPWriteResult->push_back(e);
    ++this->eventsSize;
  }

  // ----------------------------------------------------------------------
  // Event: SPWManager_RMAPReadResult
  // ----------------------------------------------------------------------

  void SPWManagerTesterBase ::
    logIn_ACTIVITY_LO_SPWManager_RMAPReadResult(
        U32 address,
        U32 value
    )
  {
    EventEntry_SPWManager_RMAPReadResult e = {
      address, value
    };
    eventHistory_SPWManager_RMAPReadResult->push_back(e);
    ++this->eventsSize;
  }

  // ----------------------------------------------------------------------
  // Event: SPWManager_Busy
  // ----------------------------------------------------------------------

  void SPWManagerTesterBase ::
    logIn_WARNING_LO_SPWManager_Busy(
        void
    )
  {
    ++this->eventsSize_SPWManager_Busy;
    ++this->eventsSize;
  }

  // ----------------------------------------------------------------------
  // Event: SPWManager_ResetLink
  // ----------------------------------------------------------------------

  void SPWManagerTesterBase ::
    logIn_ACTIVITY_LO_SPWManager_ResetLink(
        U32 numAborted
    )
  {
    EventEntry_SPWManager_ResetLink e = {
      numAborted
    };
    eventHistory_SPWManager_ResetLink->push_back(e);
    ++this->eventsSize;
  }

} // end namespace Drv
