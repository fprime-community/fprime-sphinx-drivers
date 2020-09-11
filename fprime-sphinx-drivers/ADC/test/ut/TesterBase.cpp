// ======================================================================
// \title  ADC/test/ut/TesterBase.cpp
// \author Auto-generated
// \brief  cpp file for ADC component test harness base class
//
// \copyright
// Copyright 2009-2016, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
//
// ======================================================================

#include <stdlib.h>
#include <string.h>
#include "TesterBase.hpp"

namespace Drv {

  // ----------------------------------------------------------------------
  // Construction, initialization, and destruction
  // ----------------------------------------------------------------------

  ADCTesterBase ::
    ADCTesterBase(
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
    // Initialize telemetry histories
    this->tlmHistory_ADC_o_a2d_tlm0 =
      new History<TlmEntry_ADC_o_a2d_tlm0>(maxHistorySize);
    this->tlmHistory_ADC_o_a2d_tlm1 =
      new History<TlmEntry_ADC_o_a2d_tlm1>(maxHistorySize);
    this->tlmHistory_ADC_o_a2d_tlm2 =
      new History<TlmEntry_ADC_o_a2d_tlm2>(maxHistorySize);
    this->tlmHistory_ADC_o_a2d_tlm3 =
      new History<TlmEntry_ADC_o_a2d_tlm3>(maxHistorySize);
    this->tlmHistory_ADC_o_a2d_tlm4 =
      new History<TlmEntry_ADC_o_a2d_tlm4>(maxHistorySize);
    this->tlmHistory_ADC_o_a2d_tlm5 =
      new History<TlmEntry_ADC_o_a2d_tlm5>(maxHistorySize);
    this->tlmHistory_ADC_o_a2d_tlm6 =
      new History<TlmEntry_ADC_o_a2d_tlm6>(maxHistorySize);
    this->tlmHistory_ADC_o_a2d_tlm7 =
      new History<TlmEntry_ADC_o_a2d_tlm7>(maxHistorySize);
    this->tlmHistory_ADC_a2d_stat =
      new History<TlmEntry_ADC_a2d_stat>(maxHistorySize);
    // Initialize event histories
#if FW_ENABLE_TEXT_LOGGING
    this->textLogHistory = new History<TextLogEntry>(maxHistorySize);
#endif
    this->eventHistory_ADC_SOC_SetRate =
      new History<EventEntry_ADC_SOC_SetRate>(maxHistorySize);
    this->eventHistory_ADC_SOC_SetRun =
      new History<EventEntry_ADC_SOC_SetRun>(maxHistorySize);
    this->eventHistory_ADC_SOC_SetPwrCtrl =
      new History<EventEntry_ADC_SOC_SetPwrCtrl>(maxHistorySize);
    this->eventHistory_ADC_SOC_TimedOut =
      new History<EventEntry_ADC_SOC_TimedOut>(maxHistorySize);
    this->eventHistory_ADC_SOC_SetTimeout =
      new History<EventEntry_ADC_SOC_SetTimeout>(maxHistorySize);
    // Initialize histories for typed user output ports
    this->fromPortHistory_PingResponse =
      new History<FromPortEntry_PingResponse>(maxHistorySize);
    this->fromPortHistory_adcOut =
      new History<FromPortEntry_adcOut>(maxHistorySize);
    // Clear history
    this->clearHistory();
  }

  ADCTesterBase ::
    ~ADCTesterBase(void)
  {
    // Destroy command history
    delete this->cmdResponseHistory;
    // Destroy telemetry histories
    delete this->tlmHistory_ADC_o_a2d_tlm0;
    delete this->tlmHistory_ADC_o_a2d_tlm1;
    delete this->tlmHistory_ADC_o_a2d_tlm2;
    delete this->tlmHistory_ADC_o_a2d_tlm3;
    delete this->tlmHistory_ADC_o_a2d_tlm4;
    delete this->tlmHistory_ADC_o_a2d_tlm5;
    delete this->tlmHistory_ADC_o_a2d_tlm6;
    delete this->tlmHistory_ADC_o_a2d_tlm7;
    delete this->tlmHistory_ADC_a2d_stat;
    // Destroy event histories
#if FW_ENABLE_TEXT_LOGGING
    delete this->textLogHistory;
#endif
    delete this->eventHistory_ADC_SOC_SetRate;
    delete this->eventHistory_ADC_SOC_SetRun;
    delete this->eventHistory_ADC_SOC_SetPwrCtrl;
    delete this->eventHistory_ADC_SOC_TimedOut;
    delete this->eventHistory_ADC_SOC_SetTimeout;
  }

  void ADCTesterBase ::
    init(
        const NATIVE_INT_TYPE instance
    )
  {

    // Initialize base class

		Fw::PassiveComponentBase::init(instance);

    // Attach input port cmdReg

    for (
        NATIVE_INT_TYPE _port = 0;
        _port < this->getNum_from_cmdReg();
        ++_port
    ) {

      this->m_from_cmdReg[_port].init();
      this->m_from_cmdReg[_port].addCallComp(
          this,
          from_cmdReg_static
      );
      this->m_from_cmdReg[_port].setPortNum(_port);

#if FW_OBJECT_NAMES == 1
      char _portName[120];
      (void) snprintf(
          _portName,
          sizeof(_portName),
          "%s_from_cmdReg[%d]",
          this->m_objName,
          _port
      );
      this->m_from_cmdReg[_port].setObjName(_portName);
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
      char _portName[120];
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
      char _portName[120];
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

    // Attach input port cmdResponse

    for (
        NATIVE_INT_TYPE _port = 0;
        _port < this->getNum_from_cmdResponse();
        ++_port
    ) {

      this->m_from_cmdResponse[_port].init();
      this->m_from_cmdResponse[_port].addCallComp(
          this,
          from_cmdResponse_static
      );
      this->m_from_cmdResponse[_port].setPortNum(_port);

#if FW_OBJECT_NAMES == 1
      char _portName[120];
      (void) snprintf(
          _portName,
          sizeof(_portName),
          "%s_from_cmdResponse[%d]",
          this->m_objName,
          _port
      );
      this->m_from_cmdResponse[_port].setObjName(_portName);
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
      char _portName[120];
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

    // Attach input port adcOut

    for (
        NATIVE_INT_TYPE _port = 0;
        _port < this->getNum_from_adcOut();
        ++_port
    ) {

      this->m_from_adcOut[_port].init();
      this->m_from_adcOut[_port].addCallComp(
          this,
          from_adcOut_static
      );
      this->m_from_adcOut[_port].setPortNum(_port);

#if FW_OBJECT_NAMES == 1
      char _portName[120];
      (void) snprintf(
          _portName,
          sizeof(_portName),
          "%s_from_adcOut[%d]",
          this->m_objName,
          _port
      );
      this->m_from_adcOut[_port].setObjName(_portName);
#endif

    }

    // Attach input port tlmOut

    for (
        NATIVE_INT_TYPE _port = 0;
        _port < this->getNum_from_tlmOut();
        ++_port
    ) {

      this->m_from_tlmOut[_port].init();
      this->m_from_tlmOut[_port].addCallComp(
          this,
          from_tlmOut_static
      );
      this->m_from_tlmOut[_port].setPortNum(_port);

#if FW_OBJECT_NAMES == 1
      char _portName[120];
      (void) snprintf(
          _portName,
          sizeof(_portName),
          "%s_from_tlmOut[%d]",
          this->m_objName,
          _port
      );
      this->m_from_tlmOut[_port].setObjName(_portName);
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
      char _portName[120];
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

    // Initialize output port schedIn

    for (
        NATIVE_INT_TYPE _port = 0;
        _port < this->getNum_to_schedIn();
        ++_port
    ) {
      this->m_to_schedIn[_port].init();

#if FW_OBJECT_NAMES == 1
      char _portName[120];
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

    // Initialize output port PingRecv

    for (
        NATIVE_INT_TYPE _port = 0;
        _port < this->getNum_to_PingRecv();
        ++_port
    ) {
      this->m_to_PingRecv[_port].init();

#if FW_OBJECT_NAMES == 1
      char _portName[120];
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

  }

  // ----------------------------------------------------------------------
  // Getters for port counts
  // ----------------------------------------------------------------------

  NATIVE_INT_TYPE ADCTesterBase ::
    getNum_from_cmdReg(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_from_cmdReg);
  }

  NATIVE_INT_TYPE ADCTesterBase ::
    getNum_from_timeCaller(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_from_timeCaller);
  }

  NATIVE_INT_TYPE ADCTesterBase ::
    getNum_from_eventOut(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_from_eventOut);
  }

  NATIVE_INT_TYPE ADCTesterBase ::
    getNum_from_cmdResponse(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_from_cmdResponse);
  }

  NATIVE_INT_TYPE ADCTesterBase ::
    getNum_to_schedIn(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_to_schedIn);
  }

  NATIVE_INT_TYPE ADCTesterBase ::
    getNum_to_cmdIn(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_to_cmdIn);
  }

  NATIVE_INT_TYPE ADCTesterBase ::
    getNum_from_PingResponse(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_from_PingResponse);
  }

  NATIVE_INT_TYPE ADCTesterBase ::
    getNum_from_adcOut(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_from_adcOut);
  }

  NATIVE_INT_TYPE ADCTesterBase ::
    getNum_to_PingRecv(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_to_PingRecv);
  }

  NATIVE_INT_TYPE ADCTesterBase ::
    getNum_from_tlmOut(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_from_tlmOut);
  }

#if FW_ENABLE_TEXT_LOGGING == 1
  NATIVE_INT_TYPE ADCTesterBase ::
    getNum_from_LogText(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_from_LogText);
  }
#endif

  // ----------------------------------------------------------------------
  // Connectors for to ports
  // ----------------------------------------------------------------------

  void ADCTesterBase ::
    connect_to_schedIn(
        const NATIVE_INT_TYPE portNum,
        Svc::InputSchedPort *const schedIn
    )
  {
    FW_ASSERT(portNum < this->getNum_to_schedIn(),static_cast<AssertArg>(portNum));
    this->m_to_schedIn[portNum].addCallPort(schedIn);
  }

  void ADCTesterBase ::
    connect_to_cmdIn(
        const NATIVE_INT_TYPE portNum,
        Fw::InputCmdPort *const cmdIn
    )
  {
    FW_ASSERT(portNum < this->getNum_to_cmdIn(),static_cast<AssertArg>(portNum));
    this->m_to_cmdIn[portNum].addCallPort(cmdIn);
  }

  void ADCTesterBase ::
    connect_to_PingRecv(
        const NATIVE_INT_TYPE portNum,
        Svc::InputPingPort *const PingRecv
    )
  {
    FW_ASSERT(portNum < this->getNum_to_PingRecv(),static_cast<AssertArg>(portNum));
    this->m_to_PingRecv[portNum].addCallPort(PingRecv);
  }


  // ----------------------------------------------------------------------
  // Invocation functions for to ports
  // ----------------------------------------------------------------------

  void ADCTesterBase ::
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

  void ADCTesterBase ::
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

  // ----------------------------------------------------------------------
  // Connection status for to ports
  // ----------------------------------------------------------------------

  bool ADCTesterBase ::
    isConnected_to_schedIn(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_to_schedIn(), static_cast<AssertArg>(portNum));
    return this->m_to_schedIn[portNum].isConnected();
  }

  bool ADCTesterBase ::
    isConnected_to_cmdIn(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_to_cmdIn(), static_cast<AssertArg>(portNum));
    return this->m_to_cmdIn[portNum].isConnected();
  }

  bool ADCTesterBase ::
    isConnected_to_PingRecv(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_to_PingRecv(), static_cast<AssertArg>(portNum));
    return this->m_to_PingRecv[portNum].isConnected();
  }

  // ----------------------------------------------------------------------
  // Getters for from ports
  // ----------------------------------------------------------------------

  Fw::InputCmdRegPort *ADCTesterBase ::
    get_from_cmdReg(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_from_cmdReg(),static_cast<AssertArg>(portNum));
    return &this->m_from_cmdReg[portNum];
  }

  Fw::InputTimePort *ADCTesterBase ::
    get_from_timeCaller(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_from_timeCaller(),static_cast<AssertArg>(portNum));
    return &this->m_from_timeCaller[portNum];
  }

  Fw::InputLogPort *ADCTesterBase ::
    get_from_eventOut(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_from_eventOut(),static_cast<AssertArg>(portNum));
    return &this->m_from_eventOut[portNum];
  }

  Fw::InputCmdResponsePort *ADCTesterBase ::
    get_from_cmdResponse(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_from_cmdResponse(),static_cast<AssertArg>(portNum));
    return &this->m_from_cmdResponse[portNum];
  }

  Svc::InputPingPort *ADCTesterBase ::
    get_from_PingResponse(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_from_PingResponse(),static_cast<AssertArg>(portNum));
    return &this->m_from_PingResponse[portNum];
  }

  Drv::InputApidPort *ADCTesterBase ::
    get_from_adcOut(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_from_adcOut(),static_cast<AssertArg>(portNum));
    return &this->m_from_adcOut[portNum];
  }

  Fw::InputTlmPort *ADCTesterBase ::
    get_from_tlmOut(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_from_tlmOut(),static_cast<AssertArg>(portNum));
    return &this->m_from_tlmOut[portNum];
  }

#if FW_ENABLE_TEXT_LOGGING == 1
  Fw::InputLogTextPort *ADCTesterBase ::
    get_from_LogText(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_from_LogText(),static_cast<AssertArg>(portNum));
    return &this->m_from_LogText[portNum];
  }
#endif

  // ----------------------------------------------------------------------
  // Static functions for from ports
  // ----------------------------------------------------------------------

  void ADCTesterBase ::
    from_PingResponse_static(
        Fw::PassiveComponentBase *const callComp,
        const NATIVE_INT_TYPE portNum,
        U32 key
    )
  {
    FW_ASSERT(callComp);
    ADCTesterBase* _testerBase =
      static_cast<ADCTesterBase*>(callComp);
    _testerBase->from_PingResponse_handlerBase(
        portNum,
        key
    );
  }

  void ADCTesterBase ::
    from_adcOut_static(
        Fw::PassiveComponentBase *const callComp,
        const NATIVE_INT_TYPE portNum,
        Fw::Time timetag,
        U16 apid,
        Fw::FileBuffer &data,
        U16 apid_rec
    )
  {
    FW_ASSERT(callComp);
    ADCTesterBase* _testerBase =
      static_cast<ADCTesterBase*>(callComp);
    _testerBase->from_adcOut_handlerBase(
        portNum,
        timetag, apid, data, apid_rec
    );
  }

  void ADCTesterBase ::
    from_cmdResponse_static(
        Fw::PassiveComponentBase *const component,
        const NATIVE_INT_TYPE portNum,
        const FwOpcodeType opCode,
        const U32 cmdSeq,
        const Fw::CommandResponse response
    )
  {
    ADCTesterBase* _testerBase =
      static_cast<ADCTesterBase*>(component);
    _testerBase->cmdResponseIn(opCode, cmdSeq, response);
  }

  void ADCTesterBase ::
    from_cmdReg_static(
        Fw::PassiveComponentBase *const component,
        const NATIVE_INT_TYPE portNum,
        const FwOpcodeType opCode
    )
  {

  }

  void ADCTesterBase ::
    from_tlmOut_static(
        Fw::PassiveComponentBase *const component,
        NATIVE_INT_TYPE portNum,
        FwChanIdType id,
        Fw::Time &timeTag,
        Fw::TlmBuffer &val
    )
  {
    ADCTesterBase* _testerBase =
      static_cast<ADCTesterBase*>(component);
    _testerBase->dispatchTlm(id, timeTag, val);
  }

  void ADCTesterBase ::
    from_eventOut_static(
        Fw::PassiveComponentBase *const component,
        const NATIVE_INT_TYPE portNum,
        FwEventIdType id,
        Fw::Time &timeTag,
        Fw::LogSeverity severity,
        Fw::LogBuffer &args
    )
  {
    ADCTesterBase* _testerBase =
      static_cast<ADCTesterBase*>(component);
    _testerBase->dispatchEvents(id, timeTag, severity, args);
  }

#if FW_ENABLE_TEXT_LOGGING == 1
  void ADCTesterBase ::
    from_LogText_static(
        Fw::PassiveComponentBase *const component,
        const NATIVE_INT_TYPE portNum,
        FwEventIdType id,
        Fw::Time &timeTag,
        Fw::TextLogSeverity severity,
        Fw::TextLogString &text
    )
  {
    ADCTesterBase* _testerBase =
      static_cast<ADCTesterBase*>(component);
    _testerBase->textLogIn(id,timeTag,severity,text);
  }
#endif

  void ADCTesterBase ::
    from_timeCaller_static(
        Fw::PassiveComponentBase *const component,
        const NATIVE_INT_TYPE portNum,
        Fw::Time& time
    )
  {
    ADCTesterBase* _testerBase =
      static_cast<ADCTesterBase*>(component);
    time = _testerBase->m_testTime;
  }

  // ----------------------------------------------------------------------
  // Histories for typed from ports
  // ----------------------------------------------------------------------

  void ADCTesterBase ::
    clearFromPortHistory(void)
  {
    this->fromPortHistorySize = 0;
    this->fromPortHistory_PingResponse->clear();
    this->fromPortHistory_adcOut->clear();
  }

  // ----------------------------------------------------------------------
  // From port: PingResponse
  // ----------------------------------------------------------------------

  void ADCTesterBase ::
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
  // From port: adcOut
  // ----------------------------------------------------------------------

  void ADCTesterBase ::
    pushFromPortEntry_adcOut(
        Fw::Time timetag,
        U16 apid,
        Fw::FileBuffer &data,
        U16 apid_rec
    )
  {
    FromPortEntry_adcOut _e = {
      timetag, apid, data, apid_rec
    };
    this->fromPortHistory_adcOut->push_back(_e);
    ++this->fromPortHistorySize;
  }

  // ----------------------------------------------------------------------
  // Handler base functions for from ports
  // ----------------------------------------------------------------------

  void ADCTesterBase ::
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

  void ADCTesterBase ::
    from_adcOut_handlerBase(
        const NATIVE_INT_TYPE portNum,
        Fw::Time timetag,
        U16 apid,
        Fw::FileBuffer &data,
        U16 apid_rec
    )
  {
    FW_ASSERT(portNum < this->getNum_from_adcOut(),static_cast<AssertArg>(portNum));
    this->from_adcOut_handler(
        portNum,
        timetag, apid, data, apid_rec
    );
  }

  // ----------------------------------------------------------------------
  // Command response handling
  // ----------------------------------------------------------------------

  void ADCTesterBase ::
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
  // Command: ADC_SOC_SET_RATE
  // ----------------------------------------------------------------------

  void ADCTesterBase ::
    sendCmd_ADC_SOC_SET_RATE(
        const NATIVE_INT_TYPE instance,
        const U32 cmdSeq,
        U8 rate
    )
  {

    // Serialize arguments

    Fw::CmdArgBuffer buff;
    Fw::SerializeStatus _status;
    _status = buff.serialize(rate);
    FW_ASSERT(_status == Fw::FW_SERIALIZE_OK,static_cast<AssertArg>(_status));

    // Call output command port

    FwOpcodeType _opcode;
    const U32 idBase = this->getIdBase();
    _opcode = ADCComponentBase::OPCODE_ADC_SOC_SET_RATE + idBase;

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
  // Command: ADC_SOC_SET_RUN
  // ----------------------------------------------------------------------

  void ADCTesterBase ::
    sendCmd_ADC_SOC_SET_RUN(
        const NATIVE_INT_TYPE instance,
        const U32 cmdSeq,
        U8 run_mode
    )
  {

    // Serialize arguments

    Fw::CmdArgBuffer buff;
    Fw::SerializeStatus _status;
    _status = buff.serialize(run_mode);
    FW_ASSERT(_status == Fw::FW_SERIALIZE_OK,static_cast<AssertArg>(_status));

    // Call output command port

    FwOpcodeType _opcode;
    const U32 idBase = this->getIdBase();
    _opcode = ADCComponentBase::OPCODE_ADC_SOC_SET_RUN + idBase;

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
  // Command: ADC_SOC_SET_PWR_CTRL
  // ----------------------------------------------------------------------

  void ADCTesterBase ::
    sendCmd_ADC_SOC_SET_PWR_CTRL(
        const NATIVE_INT_TYPE instance,
        const U32 cmdSeq,
        U8 pwr_ctrl
    )
  {

    // Serialize arguments

    Fw::CmdArgBuffer buff;
    Fw::SerializeStatus _status;
    _status = buff.serialize(pwr_ctrl);
    FW_ASSERT(_status == Fw::FW_SERIALIZE_OK,static_cast<AssertArg>(_status));

    // Call output command port

    FwOpcodeType _opcode;
    const U32 idBase = this->getIdBase();
    _opcode = ADCComponentBase::OPCODE_ADC_SOC_SET_PWR_CTRL + idBase;

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
  // Command: ADC_SOC_SET_TLM_TIMEOUT
  // ----------------------------------------------------------------------

  void ADCTesterBase ::
    sendCmd_ADC_SOC_SET_TLM_TIMEOUT(
        const NATIVE_INT_TYPE instance,
        const U32 cmdSeq,
        U32 timeout
    )
  {

    // Serialize arguments

    Fw::CmdArgBuffer buff;
    Fw::SerializeStatus _status;
    _status = buff.serialize(timeout);
    FW_ASSERT(_status == Fw::FW_SERIALIZE_OK,static_cast<AssertArg>(_status));

    // Call output command port

    FwOpcodeType _opcode;
    const U32 idBase = this->getIdBase();
    _opcode = ADCComponentBase::OPCODE_ADC_SOC_SET_TLM_TIMEOUT + idBase;

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


  void ADCTesterBase ::
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

  void ADCTesterBase ::
    clearHistory()
  {
    this->cmdResponseHistory->clear();
    this->clearTlm();
    this->textLogHistory->clear();
    this->clearEvents();
    this->clearFromPortHistory();
  }

  // ----------------------------------------------------------------------
  // Time
  // ----------------------------------------------------------------------

  void ADCTesterBase ::
    setTestTime(const Fw::Time& time)
  {
    this->m_testTime = time;
  }

  // ----------------------------------------------------------------------
  // Telemetry dispatch
  // ----------------------------------------------------------------------

  void ADCTesterBase ::
    dispatchTlm(
        const FwChanIdType id,
        const Fw::Time &timeTag,
        Fw::TlmBuffer &val
    )
  {

    val.resetDeser();

    const U32 idBase = this->getIdBase();
    FW_ASSERT(id >= idBase, id, idBase);

    switch (id - idBase) {

      case ADCComponentBase::CHANNELID_ADC_O_A2D_TLM0:
      {
        U32 arg;
        const Fw::SerializeStatus _status = val.deserialize(arg);
        if (_status != Fw::FW_SERIALIZE_OK) {
          printf("Error deserializing ADC_o_a2d_tlm0: %d\n", _status);
          return;
        }
        this->tlmInput_ADC_o_a2d_tlm0(timeTag, arg);
        break;
      }

      case ADCComponentBase::CHANNELID_ADC_O_A2D_TLM1:
      {
        U32 arg;
        const Fw::SerializeStatus _status = val.deserialize(arg);
        if (_status != Fw::FW_SERIALIZE_OK) {
          printf("Error deserializing ADC_o_a2d_tlm1: %d\n", _status);
          return;
        }
        this->tlmInput_ADC_o_a2d_tlm1(timeTag, arg);
        break;
      }

      case ADCComponentBase::CHANNELID_ADC_O_A2D_TLM2:
      {
        U32 arg;
        const Fw::SerializeStatus _status = val.deserialize(arg);
        if (_status != Fw::FW_SERIALIZE_OK) {
          printf("Error deserializing ADC_o_a2d_tlm2: %d\n", _status);
          return;
        }
        this->tlmInput_ADC_o_a2d_tlm2(timeTag, arg);
        break;
      }

      case ADCComponentBase::CHANNELID_ADC_O_A2D_TLM3:
      {
        U32 arg;
        const Fw::SerializeStatus _status = val.deserialize(arg);
        if (_status != Fw::FW_SERIALIZE_OK) {
          printf("Error deserializing ADC_o_a2d_tlm3: %d\n", _status);
          return;
        }
        this->tlmInput_ADC_o_a2d_tlm3(timeTag, arg);
        break;
      }

      case ADCComponentBase::CHANNELID_ADC_O_A2D_TLM4:
      {
        U32 arg;
        const Fw::SerializeStatus _status = val.deserialize(arg);
        if (_status != Fw::FW_SERIALIZE_OK) {
          printf("Error deserializing ADC_o_a2d_tlm4: %d\n", _status);
          return;
        }
        this->tlmInput_ADC_o_a2d_tlm4(timeTag, arg);
        break;
      }

      case ADCComponentBase::CHANNELID_ADC_O_A2D_TLM5:
      {
        U32 arg;
        const Fw::SerializeStatus _status = val.deserialize(arg);
        if (_status != Fw::FW_SERIALIZE_OK) {
          printf("Error deserializing ADC_o_a2d_tlm5: %d\n", _status);
          return;
        }
        this->tlmInput_ADC_o_a2d_tlm5(timeTag, arg);
        break;
      }

      case ADCComponentBase::CHANNELID_ADC_O_A2D_TLM6:
      {
        U32 arg;
        const Fw::SerializeStatus _status = val.deserialize(arg);
        if (_status != Fw::FW_SERIALIZE_OK) {
          printf("Error deserializing ADC_o_a2d_tlm6: %d\n", _status);
          return;
        }
        this->tlmInput_ADC_o_a2d_tlm6(timeTag, arg);
        break;
      }

      case ADCComponentBase::CHANNELID_ADC_O_A2D_TLM7:
      {
        U32 arg;
        const Fw::SerializeStatus _status = val.deserialize(arg);
        if (_status != Fw::FW_SERIALIZE_OK) {
          printf("Error deserializing ADC_o_a2d_tlm7: %d\n", _status);
          return;
        }
        this->tlmInput_ADC_o_a2d_tlm7(timeTag, arg);
        break;
      }

      case ADCComponentBase::CHANNELID_ADC_A2D_STAT:
      {
        U32 arg;
        const Fw::SerializeStatus _status = val.deserialize(arg);
        if (_status != Fw::FW_SERIALIZE_OK) {
          printf("Error deserializing ADC_a2d_stat: %d\n", _status);
          return;
        }
        this->tlmInput_ADC_a2d_stat(timeTag, arg);
        break;
      }

      default: {
        FW_ASSERT(0, id);
        break;
      }

    }

  }

  void ADCTesterBase ::
    clearTlm(void)
  {
    this->tlmSize = 0;
    this->tlmHistory_ADC_o_a2d_tlm0->clear();
    this->tlmHistory_ADC_o_a2d_tlm1->clear();
    this->tlmHistory_ADC_o_a2d_tlm2->clear();
    this->tlmHistory_ADC_o_a2d_tlm3->clear();
    this->tlmHistory_ADC_o_a2d_tlm4->clear();
    this->tlmHistory_ADC_o_a2d_tlm5->clear();
    this->tlmHistory_ADC_o_a2d_tlm6->clear();
    this->tlmHistory_ADC_o_a2d_tlm7->clear();
    this->tlmHistory_ADC_a2d_stat->clear();
  }

  // ----------------------------------------------------------------------
  // Channel: ADC_o_a2d_tlm0
  // ----------------------------------------------------------------------

  void ADCTesterBase ::
    tlmInput_ADC_o_a2d_tlm0(
        const Fw::Time& timeTag,
        const U32& val
    )
  {
    TlmEntry_ADC_o_a2d_tlm0 e = { timeTag, val };
    this->tlmHistory_ADC_o_a2d_tlm0->push_back(e);
    ++this->tlmSize;
  }

  // ----------------------------------------------------------------------
  // Channel: ADC_o_a2d_tlm1
  // ----------------------------------------------------------------------

  void ADCTesterBase ::
    tlmInput_ADC_o_a2d_tlm1(
        const Fw::Time& timeTag,
        const U32& val
    )
  {
    TlmEntry_ADC_o_a2d_tlm1 e = { timeTag, val };
    this->tlmHistory_ADC_o_a2d_tlm1->push_back(e);
    ++this->tlmSize;
  }

  // ----------------------------------------------------------------------
  // Channel: ADC_o_a2d_tlm2
  // ----------------------------------------------------------------------

  void ADCTesterBase ::
    tlmInput_ADC_o_a2d_tlm2(
        const Fw::Time& timeTag,
        const U32& val
    )
  {
    TlmEntry_ADC_o_a2d_tlm2 e = { timeTag, val };
    this->tlmHistory_ADC_o_a2d_tlm2->push_back(e);
    ++this->tlmSize;
  }

  // ----------------------------------------------------------------------
  // Channel: ADC_o_a2d_tlm3
  // ----------------------------------------------------------------------

  void ADCTesterBase ::
    tlmInput_ADC_o_a2d_tlm3(
        const Fw::Time& timeTag,
        const U32& val
    )
  {
    TlmEntry_ADC_o_a2d_tlm3 e = { timeTag, val };
    this->tlmHistory_ADC_o_a2d_tlm3->push_back(e);
    ++this->tlmSize;
  }

  // ----------------------------------------------------------------------
  // Channel: ADC_o_a2d_tlm4
  // ----------------------------------------------------------------------

  void ADCTesterBase ::
    tlmInput_ADC_o_a2d_tlm4(
        const Fw::Time& timeTag,
        const U32& val
    )
  {
    TlmEntry_ADC_o_a2d_tlm4 e = { timeTag, val };
    this->tlmHistory_ADC_o_a2d_tlm4->push_back(e);
    ++this->tlmSize;
  }

  // ----------------------------------------------------------------------
  // Channel: ADC_o_a2d_tlm5
  // ----------------------------------------------------------------------

  void ADCTesterBase ::
    tlmInput_ADC_o_a2d_tlm5(
        const Fw::Time& timeTag,
        const U32& val
    )
  {
    TlmEntry_ADC_o_a2d_tlm5 e = { timeTag, val };
    this->tlmHistory_ADC_o_a2d_tlm5->push_back(e);
    ++this->tlmSize;
  }

  // ----------------------------------------------------------------------
  // Channel: ADC_o_a2d_tlm6
  // ----------------------------------------------------------------------

  void ADCTesterBase ::
    tlmInput_ADC_o_a2d_tlm6(
        const Fw::Time& timeTag,
        const U32& val
    )
  {
    TlmEntry_ADC_o_a2d_tlm6 e = { timeTag, val };
    this->tlmHistory_ADC_o_a2d_tlm6->push_back(e);
    ++this->tlmSize;
  }

  // ----------------------------------------------------------------------
  // Channel: ADC_o_a2d_tlm7
  // ----------------------------------------------------------------------

  void ADCTesterBase ::
    tlmInput_ADC_o_a2d_tlm7(
        const Fw::Time& timeTag,
        const U32& val
    )
  {
    TlmEntry_ADC_o_a2d_tlm7 e = { timeTag, val };
    this->tlmHistory_ADC_o_a2d_tlm7->push_back(e);
    ++this->tlmSize;
  }

  // ----------------------------------------------------------------------
  // Channel: ADC_a2d_stat
  // ----------------------------------------------------------------------

  void ADCTesterBase ::
    tlmInput_ADC_a2d_stat(
        const Fw::Time& timeTag,
        const U32& val
    )
  {
    TlmEntry_ADC_a2d_stat e = { timeTag, val };
    this->tlmHistory_ADC_a2d_stat->push_back(e);
    ++this->tlmSize;
  }

  // ----------------------------------------------------------------------
  // Event dispatch
  // ----------------------------------------------------------------------

  void ADCTesterBase ::
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

      case ADCComponentBase::EVENTID_ADC_SOC_SETRATE:
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
        U8 rate;
#if FW_AMPCS_COMPATIBLE
        {
          // Deserialize the argument size
          U8 _argSize;
          _status = args.deserialize(_argSize);
          FW_ASSERT(
            _status == Fw::FW_SERIALIZE_OK,
            static_cast<AssertArg>(_status)
          );
          FW_ASSERT(_argSize == sizeof(U8),_argSize,sizeof(U8));
        }
#endif
        _status = args.deserialize(rate);
        FW_ASSERT(
            _status == Fw::FW_SERIALIZE_OK,
            static_cast<AssertArg>(_status)
        );

        U8 rate_bit;
#if FW_AMPCS_COMPATIBLE
        {
          // Deserialize the argument size
          U8 _argSize;
          _status = args.deserialize(_argSize);
          FW_ASSERT(
            _status == Fw::FW_SERIALIZE_OK,
            static_cast<AssertArg>(_status)
          );
          FW_ASSERT(_argSize == sizeof(U8),_argSize,sizeof(U8));
        }
#endif
        _status = args.deserialize(rate_bit);
        FW_ASSERT(
            _status == Fw::FW_SERIALIZE_OK,
            static_cast<AssertArg>(_status)
        );

        this->logIn_ACTIVITY_HI_ADC_SOC_SetRate(rate, rate_bit);

        break;

      }

      case ADCComponentBase::EVENTID_ADC_SOC_SETRUN:
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
        U8 run;
#if FW_AMPCS_COMPATIBLE
        {
          // Deserialize the argument size
          U8 _argSize;
          _status = args.deserialize(_argSize);
          FW_ASSERT(
            _status == Fw::FW_SERIALIZE_OK,
            static_cast<AssertArg>(_status)
          );
          FW_ASSERT(_argSize == sizeof(U8),_argSize,sizeof(U8));
        }
#endif
        _status = args.deserialize(run);
        FW_ASSERT(
            _status == Fw::FW_SERIALIZE_OK,
            static_cast<AssertArg>(_status)
        );

        this->logIn_ACTIVITY_HI_ADC_SOC_SetRun(run);

        break;

      }

      case ADCComponentBase::EVENTID_ADC_SOC_SETPWRCTRL:
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
        U8 pwr_ctrl;
#if FW_AMPCS_COMPATIBLE
        {
          // Deserialize the argument size
          U8 _argSize;
          _status = args.deserialize(_argSize);
          FW_ASSERT(
            _status == Fw::FW_SERIALIZE_OK,
            static_cast<AssertArg>(_status)
          );
          FW_ASSERT(_argSize == sizeof(U8),_argSize,sizeof(U8));
        }
#endif
        _status = args.deserialize(pwr_ctrl);
        FW_ASSERT(
            _status == Fw::FW_SERIALIZE_OK,
            static_cast<AssertArg>(_status)
        );

        this->logIn_ACTIVITY_HI_ADC_SOC_SetPwrCtrl(pwr_ctrl);

        break;

      }

      case ADCComponentBase::EVENTID_ADC_SOC_COULDNOTSETPWRCTRLBIT:
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
        this->logIn_ACTIVITY_HI_ADC_SOC_CouldNotSetPwrCtrlBit();

        break;

      }

      case ADCComponentBase::EVENTID_ADC_SOC_COULDNOTSETRUNBIT:
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
        this->logIn_ACTIVITY_HI_ADC_SOC_CouldNotSetRunBit();

        break;

      }

      case ADCComponentBase::EVENTID_ADC_SOC_COULDNOTSETRATE:
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
        this->logIn_ACTIVITY_HI_ADC_SOC_CouldNotSetRate();

        break;

      }

      case ADCComponentBase::EVENTID_ADC_SOC_TIMEDOUT:
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
        U32 ticks;
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
        _status = args.deserialize(ticks);
        FW_ASSERT(
            _status == Fw::FW_SERIALIZE_OK,
            static_cast<AssertArg>(_status)
        );

        this->logIn_WARNING_HI_ADC_SOC_TimedOut(ticks);

        break;

      }

      case ADCComponentBase::EVENTID_ADC_SOC_SETTIMEOUT:
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

        this->logIn_ACTIVITY_HI_ADC_SOC_SetTimeout(timeout);

        break;

      }

      default: {
        FW_ASSERT(0, id);
        break;
      }

    }

  }

  void ADCTesterBase ::
    clearEvents(void)
  {
    this->eventsSize = 0;
    this->eventHistory_ADC_SOC_SetRate->clear();
    this->eventHistory_ADC_SOC_SetRun->clear();
    this->eventHistory_ADC_SOC_SetPwrCtrl->clear();
    this->eventsSize_ADC_SOC_CouldNotSetPwrCtrlBit = 0;
    this->eventsSize_ADC_SOC_CouldNotSetRunBit = 0;
    this->eventsSize_ADC_SOC_CouldNotSetRate = 0;
    this->eventHistory_ADC_SOC_TimedOut->clear();
    this->eventHistory_ADC_SOC_SetTimeout->clear();
  }

#if FW_ENABLE_TEXT_LOGGING

  // ----------------------------------------------------------------------
  // Text events
  // ----------------------------------------------------------------------

  void ADCTesterBase ::
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

  void ADCTesterBase ::
    printTextLogHistoryEntry(
        const TextLogEntry& e,
        FILE* file
    )
  {
    const char *severityString = "UNKNOWN";
    switch (e.severity) {
      case Fw::TEXT_LOG_FATAL:
        severityString = "FATAL";
        break;
      case Fw::TEXT_LOG_WARNING_HI:
        severityString = "WARNING_HI";
        break;
      case Fw::TEXT_LOG_WARNING_LO:
        severityString = "WARNING_LO";
        break;
      case Fw::TEXT_LOG_COMMAND:
        severityString = "COMMAND";
        break;
      case Fw::TEXT_LOG_ACTIVITY_HI:
        severityString = "ACTIVITY_HI";
        break;
      case Fw::TEXT_LOG_ACTIVITY_LO:
        severityString = "ACTIVITY_LO";
        break;
      case Fw::TEXT_LOG_DIAGNOSTIC:
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

  void ADCTesterBase ::
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
  // Event: ADC_SOC_SetRate
  // ----------------------------------------------------------------------

  void ADCTesterBase ::
    logIn_ACTIVITY_HI_ADC_SOC_SetRate(
        U8 rate,
        U8 rate_bit
    )
  {
    EventEntry_ADC_SOC_SetRate e = {
      rate, rate_bit
    };
    eventHistory_ADC_SOC_SetRate->push_back(e);
    ++this->eventsSize;
  }

  // ----------------------------------------------------------------------
  // Event: ADC_SOC_SetRun
  // ----------------------------------------------------------------------

  void ADCTesterBase ::
    logIn_ACTIVITY_HI_ADC_SOC_SetRun(
        U8 run
    )
  {
    EventEntry_ADC_SOC_SetRun e = {
      run
    };
    eventHistory_ADC_SOC_SetRun->push_back(e);
    ++this->eventsSize;
  }

  // ----------------------------------------------------------------------
  // Event: ADC_SOC_SetPwrCtrl
  // ----------------------------------------------------------------------

  void ADCTesterBase ::
    logIn_ACTIVITY_HI_ADC_SOC_SetPwrCtrl(
        U8 pwr_ctrl
    )
  {
    EventEntry_ADC_SOC_SetPwrCtrl e = {
      pwr_ctrl
    };
    eventHistory_ADC_SOC_SetPwrCtrl->push_back(e);
    ++this->eventsSize;
  }

  // ----------------------------------------------------------------------
  // Event: ADC_SOC_CouldNotSetPwrCtrlBit
  // ----------------------------------------------------------------------

  void ADCTesterBase ::
    logIn_ACTIVITY_HI_ADC_SOC_CouldNotSetPwrCtrlBit(
        void
    )
  {
    ++this->eventsSize_ADC_SOC_CouldNotSetPwrCtrlBit;
    ++this->eventsSize;
  }

  // ----------------------------------------------------------------------
  // Event: ADC_SOC_CouldNotSetRunBit
  // ----------------------------------------------------------------------

  void ADCTesterBase ::
    logIn_ACTIVITY_HI_ADC_SOC_CouldNotSetRunBit(
        void
    )
  {
    ++this->eventsSize_ADC_SOC_CouldNotSetRunBit;
    ++this->eventsSize;
  }

  // ----------------------------------------------------------------------
  // Event: ADC_SOC_CouldNotSetRate
  // ----------------------------------------------------------------------

  void ADCTesterBase ::
    logIn_ACTIVITY_HI_ADC_SOC_CouldNotSetRate(
        void
    )
  {
    ++this->eventsSize_ADC_SOC_CouldNotSetRate;
    ++this->eventsSize;
  }

  // ----------------------------------------------------------------------
  // Event: ADC_SOC_TimedOut
  // ----------------------------------------------------------------------

  void ADCTesterBase ::
    logIn_WARNING_HI_ADC_SOC_TimedOut(
        U32 ticks
    )
  {
    EventEntry_ADC_SOC_TimedOut e = {
      ticks
    };
    eventHistory_ADC_SOC_TimedOut->push_back(e);
    ++this->eventsSize;
  }

  // ----------------------------------------------------------------------
  // Event: ADC_SOC_SetTimeout
  // ----------------------------------------------------------------------

  void ADCTesterBase ::
    logIn_ACTIVITY_HI_ADC_SOC_SetTimeout(
        U32 timeout
    )
  {
    EventEntry_ADC_SOC_SetTimeout e = {
      timeout
    };
    eventHistory_ADC_SOC_SetTimeout->push_back(e);
    ++this->eventsSize;
  }

} // end namespace Drv
