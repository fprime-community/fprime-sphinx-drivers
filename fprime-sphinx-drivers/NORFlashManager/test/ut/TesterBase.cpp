// ======================================================================
// \title  NORFlashManager/test/ut/TesterBase.cpp
// \author Auto-generated
// \brief  cpp file for NORFlashManager component test harness base class
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

  NORFlashManagerTesterBase ::
    NORFlashManagerTesterBase(
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
    this->eventHistory_NOR_ERASE_BUSY =
      new History<EventEntry_NOR_ERASE_BUSY>(maxHistorySize);
    this->eventHistory_NOR_ERASE_FAIL =
      new History<EventEntry_NOR_ERASE_FAIL>(maxHistorySize);
    this->eventHistory_NOR_RESET_FAIL =
      new History<EventEntry_NOR_RESET_FAIL>(maxHistorySize);
    this->eventHistory_NOR_FAILED_TO_VERIFY_DATA =
      new History<EventEntry_NOR_FAILED_TO_VERIFY_DATA>(maxHistorySize);
    this->eventHistory_NOR_VERIFY_BUSY =
      new History<EventEntry_NOR_VERIFY_BUSY>(maxHistorySize);
    this->eventHistory_NOR_FAILED_TO_READ_DATA =
      new History<EventEntry_NOR_FAILED_TO_READ_DATA>(maxHistorySize);
    // Initialize histories for typed user output ports
    this->fromPortHistory_PingResponse =
      new History<FromPortEntry_PingResponse>(maxHistorySize);
    this->fromPortHistory_verification_done =
      new History<FromPortEntry_verification_done>(maxHistorySize);
    this->fromPortHistory_erase_done =
      new History<FromPortEntry_erase_done>(maxHistorySize);
    this->fromPortHistory_read_done =
      new History<FromPortEntry_read_done>(maxHistorySize);
    this->fromPortHistory_worker_verify =
      new History<FromPortEntry_worker_verify>(maxHistorySize);
    this->fromPortHistory_worker_write =
      new History<FromPortEntry_worker_write>(maxHistorySize);
    this->fromPortHistory_write_done =
      new History<FromPortEntry_write_done>(maxHistorySize);
    this->fromPortHistory_worker_erase =
      new History<FromPortEntry_worker_erase>(maxHistorySize);
    this->fromPortHistory_worker_reset =
      new History<FromPortEntry_worker_reset>(maxHistorySize);
    this->fromPortHistory_worker_read =
      new History<FromPortEntry_worker_read>(maxHistorySize);
    // Clear history
    this->clearHistory();
  }

  NORFlashManagerTesterBase ::
    ~NORFlashManagerTesterBase(void) 
  {
    // Destroy command history
    delete this->cmdResponseHistory;
    // Destroy event histories
#if FW_ENABLE_TEXT_LOGGING
    delete this->textLogHistory;
#endif
    delete this->eventHistory_NOR_ERASE_BUSY;
    delete this->eventHistory_NOR_ERASE_FAIL;
    delete this->eventHistory_NOR_RESET_FAIL;
    delete this->eventHistory_NOR_FAILED_TO_VERIFY_DATA;
    delete this->eventHistory_NOR_VERIFY_BUSY;
    delete this->eventHistory_NOR_FAILED_TO_READ_DATA;
  }

  void NORFlashManagerTesterBase ::
    init(
        const NATIVE_INT_TYPE instance
    )
  {

    // Initialize base class

		Fw::PassiveComponentBase::init(instance);

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
      char _portName[80];
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
      char _portName[80];
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

    // Attach input port verification_done

    for (
        NATIVE_INT_TYPE _port = 0;
        _port < this->getNum_from_verification_done();
        ++_port
    ) {

      this->m_from_verification_done[_port].init();
      this->m_from_verification_done[_port].addCallComp(
          this,
          from_verification_done_static
      );
      this->m_from_verification_done[_port].setPortNum(_port);

#if FW_OBJECT_NAMES == 1
      char _portName[80];
      (void) snprintf(
          _portName,
          sizeof(_portName),
          "%s_from_verification_done[%d]",
          this->m_objName,
          _port
      );
      this->m_from_verification_done[_port].setObjName(_portName);
#endif

    }

    // Attach input port erase_done

    for (
        NATIVE_INT_TYPE _port = 0;
        _port < this->getNum_from_erase_done();
        ++_port
    ) {

      this->m_from_erase_done[_port].init();
      this->m_from_erase_done[_port].addCallComp(
          this,
          from_erase_done_static
      );
      this->m_from_erase_done[_port].setPortNum(_port);

#if FW_OBJECT_NAMES == 1
      char _portName[80];
      (void) snprintf(
          _portName,
          sizeof(_portName),
          "%s_from_erase_done[%d]",
          this->m_objName,
          _port
      );
      this->m_from_erase_done[_port].setObjName(_portName);
#endif

    }

    // Attach input port read_done

    for (
        NATIVE_INT_TYPE _port = 0;
        _port < this->getNum_from_read_done();
        ++_port
    ) {

      this->m_from_read_done[_port].init();
      this->m_from_read_done[_port].addCallComp(
          this,
          from_read_done_static
      );
      this->m_from_read_done[_port].setPortNum(_port);

#if FW_OBJECT_NAMES == 1
      char _portName[80];
      (void) snprintf(
          _portName,
          sizeof(_portName),
          "%s_from_read_done[%d]",
          this->m_objName,
          _port
      );
      this->m_from_read_done[_port].setObjName(_portName);
#endif

    }

    // Attach input port worker_verify

    for (
        NATIVE_INT_TYPE _port = 0;
        _port < this->getNum_from_worker_verify();
        ++_port
    ) {

      this->m_from_worker_verify[_port].init();
      this->m_from_worker_verify[_port].addCallComp(
          this,
          from_worker_verify_static
      );
      this->m_from_worker_verify[_port].setPortNum(_port);

#if FW_OBJECT_NAMES == 1
      char _portName[80];
      (void) snprintf(
          _portName,
          sizeof(_portName),
          "%s_from_worker_verify[%d]",
          this->m_objName,
          _port
      );
      this->m_from_worker_verify[_port].setObjName(_portName);
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
      char _portName[80];
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
      char _portName[80];
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

    // Attach input port worker_write

    for (
        NATIVE_INT_TYPE _port = 0;
        _port < this->getNum_from_worker_write();
        ++_port
    ) {

      this->m_from_worker_write[_port].init();
      this->m_from_worker_write[_port].addCallComp(
          this,
          from_worker_write_static
      );
      this->m_from_worker_write[_port].setPortNum(_port);

#if FW_OBJECT_NAMES == 1
      char _portName[80];
      (void) snprintf(
          _portName,
          sizeof(_portName),
          "%s_from_worker_write[%d]",
          this->m_objName,
          _port
      );
      this->m_from_worker_write[_port].setObjName(_portName);
#endif

    }

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
      char _portName[80];
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

    // Attach input port write_done

    for (
        NATIVE_INT_TYPE _port = 0;
        _port < this->getNum_from_write_done();
        ++_port
    ) {

      this->m_from_write_done[_port].init();
      this->m_from_write_done[_port].addCallComp(
          this,
          from_write_done_static
      );
      this->m_from_write_done[_port].setPortNum(_port);

#if FW_OBJECT_NAMES == 1
      char _portName[80];
      (void) snprintf(
          _portName,
          sizeof(_portName),
          "%s_from_write_done[%d]",
          this->m_objName,
          _port
      );
      this->m_from_write_done[_port].setObjName(_portName);
#endif

    }

    // Attach input port worker_erase

    for (
        NATIVE_INT_TYPE _port = 0;
        _port < this->getNum_from_worker_erase();
        ++_port
    ) {

      this->m_from_worker_erase[_port].init();
      this->m_from_worker_erase[_port].addCallComp(
          this,
          from_worker_erase_static
      );
      this->m_from_worker_erase[_port].setPortNum(_port);

#if FW_OBJECT_NAMES == 1
      char _portName[80];
      (void) snprintf(
          _portName,
          sizeof(_portName),
          "%s_from_worker_erase[%d]",
          this->m_objName,
          _port
      );
      this->m_from_worker_erase[_port].setObjName(_portName);
#endif

    }

    // Attach input port worker_cancel

    for (
        NATIVE_INT_TYPE _port = 0;
        _port < this->getNum_from_worker_cancel();
        ++_port
    ) {

      this->m_from_worker_cancel[_port].init();
      this->m_from_worker_cancel[_port].addCallComp(
          this,
          from_worker_cancel_static
      );
      this->m_from_worker_cancel[_port].setPortNum(_port);

#if FW_OBJECT_NAMES == 1
      char _portName[80];
      (void) snprintf(
          _portName,
          sizeof(_portName),
          "%s_from_worker_cancel[%d]",
          this->m_objName,
          _port
      );
      this->m_from_worker_cancel[_port].setObjName(_portName);
#endif

    }

    // Attach input port worker_reset

    for (
        NATIVE_INT_TYPE _port = 0;
        _port < this->getNum_from_worker_reset();
        ++_port
    ) {

      this->m_from_worker_reset[_port].init();
      this->m_from_worker_reset[_port].addCallComp(
          this,
          from_worker_reset_static
      );
      this->m_from_worker_reset[_port].setPortNum(_port);

#if FW_OBJECT_NAMES == 1
      char _portName[80];
      (void) snprintf(
          _portName,
          sizeof(_portName),
          "%s_from_worker_reset[%d]",
          this->m_objName,
          _port
      );
      this->m_from_worker_reset[_port].setObjName(_portName);
#endif

    }

    // Attach input port worker_read

    for (
        NATIVE_INT_TYPE _port = 0;
        _port < this->getNum_from_worker_read();
        ++_port
    ) {

      this->m_from_worker_read[_port].init();
      this->m_from_worker_read[_port].addCallComp(
          this,
          from_worker_read_static
      );
      this->m_from_worker_read[_port].setPortNum(_port);

#if FW_OBJECT_NAMES == 1
      char _portName[80];
      (void) snprintf(
          _portName,
          sizeof(_portName),
          "%s_from_worker_read[%d]",
          this->m_objName,
          _port
      );
      this->m_from_worker_read[_port].setObjName(_portName);
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
      char _portName[80];
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

    // Initialize output port get_bl_size

    for (
        NATIVE_INT_TYPE _port = 0;
        _port < this->getNum_to_get_bl_size();
        ++_port
    ) {
      this->m_to_get_bl_size[_port].init();

#if FW_OBJECT_NAMES == 1
      char _portName[80];
      snprintf(
          _portName,
          sizeof(_portName),
          "%s_to_get_bl_size[%d]",
          this->m_objName,
          _port
      );
      this->m_to_get_bl_size[_port].setObjName(_portName);
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
      char _portName[80];
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

    // Initialize output port request_verification

    for (
        NATIVE_INT_TYPE _port = 0;
        _port < this->getNum_to_request_verification();
        ++_port
    ) {
      this->m_to_request_verification[_port].init();

#if FW_OBJECT_NAMES == 1
      char _portName[80];
      snprintf(
          _portName,
          sizeof(_portName),
          "%s_to_request_verification[%d]",
          this->m_objName,
          _port
      );
      this->m_to_request_verification[_port].setObjName(_portName);
#endif

    }

    // Initialize output port get_fsw_size

    for (
        NATIVE_INT_TYPE _port = 0;
        _port < this->getNum_to_get_fsw_size();
        ++_port
    ) {
      this->m_to_get_fsw_size[_port].init();

#if FW_OBJECT_NAMES == 1
      char _portName[80];
      snprintf(
          _portName,
          sizeof(_portName),
          "%s_to_get_fsw_size[%d]",
          this->m_objName,
          _port
      );
      this->m_to_get_fsw_size[_port].setObjName(_portName);
#endif

    }

    // Initialize output port request_write

    for (
        NATIVE_INT_TYPE _port = 0;
        _port < this->getNum_to_request_write();
        ++_port
    ) {
      this->m_to_request_write[_port].init();

#if FW_OBJECT_NAMES == 1
      char _portName[80];
      snprintf(
          _portName,
          sizeof(_portName),
          "%s_to_request_write[%d]",
          this->m_objName,
          _port
      );
      this->m_to_request_write[_port].setObjName(_portName);
#endif

    }

    // Initialize output port worker_done

    for (
        NATIVE_INT_TYPE _port = 0;
        _port < this->getNum_to_worker_done();
        ++_port
    ) {
      this->m_to_worker_done[_port].init();

#if FW_OBJECT_NAMES == 1
      char _portName[80];
      snprintf(
          _portName,
          sizeof(_portName),
          "%s_to_worker_done[%d]",
          this->m_objName,
          _port
      );
      this->m_to_worker_done[_port].setObjName(_portName);
#endif

    }

    // Initialize output port request_read

    for (
        NATIVE_INT_TYPE _port = 0;
        _port < this->getNum_to_request_read();
        ++_port
    ) {
      this->m_to_request_read[_port].init();

#if FW_OBJECT_NAMES == 1
      char _portName[80];
      snprintf(
          _portName,
          sizeof(_portName),
          "%s_to_request_read[%d]",
          this->m_objName,
          _port
      );
      this->m_to_request_read[_port].setObjName(_portName);
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
      char _portName[80];
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

    // Initialize output port request_erase

    for (
        NATIVE_INT_TYPE _port = 0;
        _port < this->getNum_to_request_erase();
        ++_port
    ) {
      this->m_to_request_erase[_port].init();

#if FW_OBJECT_NAMES == 1
      char _portName[80];
      snprintf(
          _portName,
          sizeof(_portName),
          "%s_to_request_erase[%d]",
          this->m_objName,
          _port
      );
      this->m_to_request_erase[_port].setObjName(_portName);
#endif

    }

  }

  // ----------------------------------------------------------------------
  // Getters for port counts
  // ----------------------------------------------------------------------

  NATIVE_INT_TYPE NORFlashManagerTesterBase ::
    getNum_to_get_bl_size(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_to_get_bl_size);
  }

  NATIVE_INT_TYPE NORFlashManagerTesterBase ::
    getNum_from_eventOut(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_from_eventOut);
  }

  NATIVE_INT_TYPE NORFlashManagerTesterBase ::
    getNum_from_PingResponse(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_from_PingResponse);
  }

  NATIVE_INT_TYPE NORFlashManagerTesterBase ::
    getNum_from_verification_done(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_from_verification_done);
  }

  NATIVE_INT_TYPE NORFlashManagerTesterBase ::
    getNum_to_PingRecv(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_to_PingRecv);
  }

  NATIVE_INT_TYPE NORFlashManagerTesterBase ::
    getNum_from_erase_done(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_from_erase_done);
  }

  NATIVE_INT_TYPE NORFlashManagerTesterBase ::
    getNum_from_read_done(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_from_read_done);
  }

  NATIVE_INT_TYPE NORFlashManagerTesterBase ::
    getNum_from_worker_verify(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_from_worker_verify);
  }

  NATIVE_INT_TYPE NORFlashManagerTesterBase ::
    getNum_from_timeCaller(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_from_timeCaller);
  }

  NATIVE_INT_TYPE NORFlashManagerTesterBase ::
    getNum_from_cmdResponse(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_from_cmdResponse);
  }

  NATIVE_INT_TYPE NORFlashManagerTesterBase ::
    getNum_to_request_verification(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_to_request_verification);
  }

  NATIVE_INT_TYPE NORFlashManagerTesterBase ::
    getNum_to_cmdIn(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_to_cmdIn);
  }

  NATIVE_INT_TYPE NORFlashManagerTesterBase ::
    getNum_from_worker_write(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_from_worker_write);
  }

  NATIVE_INT_TYPE NORFlashManagerTesterBase ::
    getNum_to_get_fsw_size(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_to_get_fsw_size);
  }

  NATIVE_INT_TYPE NORFlashManagerTesterBase ::
    getNum_to_request_write(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_to_request_write);
  }

  NATIVE_INT_TYPE NORFlashManagerTesterBase ::
    getNum_from_cmdReg(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_from_cmdReg);
  }

  NATIVE_INT_TYPE NORFlashManagerTesterBase ::
    getNum_to_worker_done(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_to_worker_done);
  }

  NATIVE_INT_TYPE NORFlashManagerTesterBase ::
    getNum_to_request_read(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_to_request_read);
  }

  NATIVE_INT_TYPE NORFlashManagerTesterBase ::
    getNum_from_write_done(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_from_write_done);
  }

  NATIVE_INT_TYPE NORFlashManagerTesterBase ::
    getNum_from_worker_erase(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_from_worker_erase);
  }

  NATIVE_INT_TYPE NORFlashManagerTesterBase ::
    getNum_from_worker_cancel(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_from_worker_cancel);
  }

  NATIVE_INT_TYPE NORFlashManagerTesterBase ::
    getNum_from_worker_reset(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_from_worker_reset);
  }

  NATIVE_INT_TYPE NORFlashManagerTesterBase ::
    getNum_to_schedIn(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_to_schedIn);
  }

  NATIVE_INT_TYPE NORFlashManagerTesterBase ::
    getNum_to_request_erase(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_to_request_erase);
  }

  NATIVE_INT_TYPE NORFlashManagerTesterBase ::
    getNum_from_worker_read(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_from_worker_read);
  }

#if FW_ENABLE_TEXT_LOGGING == 1
  NATIVE_INT_TYPE NORFlashManagerTesterBase ::
    getNum_from_LogText(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_from_LogText);
  }
#endif

  // ----------------------------------------------------------------------
  // Connectors for to ports 
  // ----------------------------------------------------------------------

  void NORFlashManagerTesterBase ::
    connect_to_get_bl_size(
        const NATIVE_INT_TYPE portNum,
        Drv::InputNORFlash_GetSizePort *const get_bl_size
    ) 
  {
    FW_ASSERT(portNum < this->getNum_to_get_bl_size(),static_cast<AssertArg>(portNum));
    this->m_to_get_bl_size[portNum].addCallPort(get_bl_size);
  }

  void NORFlashManagerTesterBase ::
    connect_to_PingRecv(
        const NATIVE_INT_TYPE portNum,
        Svc::InputPingPort *const PingRecv
    ) 
  {
    FW_ASSERT(portNum < this->getNum_to_PingRecv(),static_cast<AssertArg>(portNum));
    this->m_to_PingRecv[portNum].addCallPort(PingRecv);
  }

  void NORFlashManagerTesterBase ::
    connect_to_request_verification(
        const NATIVE_INT_TYPE portNum,
        Drv::InputNORFlash_VerifyPort *const request_verification
    ) 
  {
    FW_ASSERT(portNum < this->getNum_to_request_verification(),static_cast<AssertArg>(portNum));
    this->m_to_request_verification[portNum].addCallPort(request_verification);
  }

  void NORFlashManagerTesterBase ::
    connect_to_cmdIn(
        const NATIVE_INT_TYPE portNum,
        Fw::InputCmdPort *const cmdIn
    ) 
  {
    FW_ASSERT(portNum < this->getNum_to_cmdIn(),static_cast<AssertArg>(portNum));
    this->m_to_cmdIn[portNum].addCallPort(cmdIn);
  }

  void NORFlashManagerTesterBase ::
    connect_to_get_fsw_size(
        const NATIVE_INT_TYPE portNum,
        Drv::InputNORFlash_GetSizePort *const get_fsw_size
    ) 
  {
    FW_ASSERT(portNum < this->getNum_to_get_fsw_size(),static_cast<AssertArg>(portNum));
    this->m_to_get_fsw_size[portNum].addCallPort(get_fsw_size);
  }

  void NORFlashManagerTesterBase ::
    connect_to_request_write(
        const NATIVE_INT_TYPE portNum,
        Drv::InputNORFlash_RWPort *const request_write
    ) 
  {
    FW_ASSERT(portNum < this->getNum_to_request_write(),static_cast<AssertArg>(portNum));
    this->m_to_request_write[portNum].addCallPort(request_write);
  }

  void NORFlashManagerTesterBase ::
    connect_to_worker_done(
        const NATIVE_INT_TYPE portNum,
        Drv::InputNOR_donePort *const worker_done
    ) 
  {
    FW_ASSERT(portNum < this->getNum_to_worker_done(),static_cast<AssertArg>(portNum));
    this->m_to_worker_done[portNum].addCallPort(worker_done);
  }

  void NORFlashManagerTesterBase ::
    connect_to_request_read(
        const NATIVE_INT_TYPE portNum,
        Drv::InputNORFlash_RWPort *const request_read
    ) 
  {
    FW_ASSERT(portNum < this->getNum_to_request_read(),static_cast<AssertArg>(portNum));
    this->m_to_request_read[portNum].addCallPort(request_read);
  }

  void NORFlashManagerTesterBase ::
    connect_to_schedIn(
        const NATIVE_INT_TYPE portNum,
        Svc::InputSchedPort *const schedIn
    ) 
  {
    FW_ASSERT(portNum < this->getNum_to_schedIn(),static_cast<AssertArg>(portNum));
    this->m_to_schedIn[portNum].addCallPort(schedIn);
  }

  void NORFlashManagerTesterBase ::
    connect_to_request_erase(
        const NATIVE_INT_TYPE portNum,
        Drv::InputNORFlash_EraseBankNumberPort *const request_erase
    ) 
  {
    FW_ASSERT(portNum < this->getNum_to_request_erase(),static_cast<AssertArg>(portNum));
    this->m_to_request_erase[portNum].addCallPort(request_erase);
  }


  // ----------------------------------------------------------------------
  // Invocation functions for to ports
  // ----------------------------------------------------------------------

  I32 NORFlashManagerTesterBase ::
    invoke_to_get_bl_size(
        const NATIVE_INT_TYPE portNum,
        U32 &size
    )
  {
    FW_ASSERT(portNum < this->getNum_to_get_bl_size(),static_cast<AssertArg>(portNum));
    FW_ASSERT(portNum < this->getNum_to_get_bl_size(),static_cast<AssertArg>(portNum));
    return this->m_to_get_bl_size[portNum].invoke(
        size
    );
  }

  void NORFlashManagerTesterBase ::
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

  void NORFlashManagerTesterBase ::
    invoke_to_request_verification(
        const NATIVE_INT_TYPE portNum,
        U32 blc_filesize,
        U32 fsw_filesize
    )
  {
    FW_ASSERT(portNum < this->getNum_to_request_verification(),static_cast<AssertArg>(portNum));
    FW_ASSERT(portNum < this->getNum_to_request_verification(),static_cast<AssertArg>(portNum));
    this->m_to_request_verification[portNum].invoke(
        blc_filesize, fsw_filesize
    );
  }

  I32 NORFlashManagerTesterBase ::
    invoke_to_get_fsw_size(
        const NATIVE_INT_TYPE portNum,
        U32 &size
    )
  {
    FW_ASSERT(portNum < this->getNum_to_get_fsw_size(),static_cast<AssertArg>(portNum));
    FW_ASSERT(portNum < this->getNum_to_get_fsw_size(),static_cast<AssertArg>(portNum));
    return this->m_to_get_fsw_size[portNum].invoke(
        size
    );
  }

  void NORFlashManagerTesterBase ::
    invoke_to_request_write(
        const NATIVE_INT_TYPE portNum,
        U32 dest,
        U8 *src,
        U32 count,
        bool disable_edac
    )
  {
    FW_ASSERT(portNum < this->getNum_to_request_write(),static_cast<AssertArg>(portNum));
    FW_ASSERT(portNum < this->getNum_to_request_write(),static_cast<AssertArg>(portNum));
    this->m_to_request_write[portNum].invoke(
        dest, src, count, disable_edac
    );
  }

  void NORFlashManagerTesterBase ::
    invoke_to_worker_done(
        const NATIVE_INT_TYPE portNum,
        I8 done,
        U32 context1,
        U32 context2
    )
  {
    FW_ASSERT(portNum < this->getNum_to_worker_done(),static_cast<AssertArg>(portNum));
    FW_ASSERT(portNum < this->getNum_to_worker_done(),static_cast<AssertArg>(portNum));
    this->m_to_worker_done[portNum].invoke(
        done, context1, context2
    );
  }

  void NORFlashManagerTesterBase ::
    invoke_to_request_read(
        const NATIVE_INT_TYPE portNum,
        U32 dest,
        U8 *src,
        U32 count,
        bool disable_edac
    )
  {
    FW_ASSERT(portNum < this->getNum_to_request_read(),static_cast<AssertArg>(portNum));
    FW_ASSERT(portNum < this->getNum_to_request_read(),static_cast<AssertArg>(portNum));
    this->m_to_request_read[portNum].invoke(
        dest, src, count, disable_edac
    );
  }

  void NORFlashManagerTesterBase ::
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

  void NORFlashManagerTesterBase ::
    invoke_to_request_erase(
        const NATIVE_INT_TYPE portNum,
        U8 bank_number
    )
  {
    FW_ASSERT(portNum < this->getNum_to_request_erase(),static_cast<AssertArg>(portNum));
    FW_ASSERT(portNum < this->getNum_to_request_erase(),static_cast<AssertArg>(portNum));
    this->m_to_request_erase[portNum].invoke(
        bank_number
    );
  }

  // ----------------------------------------------------------------------
  // Connection status for to ports
  // ----------------------------------------------------------------------

  bool NORFlashManagerTesterBase ::
    isConnected_to_get_bl_size(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_to_get_bl_size(), static_cast<AssertArg>(portNum));
    return this->m_to_get_bl_size[portNum].isConnected();
  }

  bool NORFlashManagerTesterBase ::
    isConnected_to_PingRecv(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_to_PingRecv(), static_cast<AssertArg>(portNum));
    return this->m_to_PingRecv[portNum].isConnected();
  }

  bool NORFlashManagerTesterBase ::
    isConnected_to_request_verification(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_to_request_verification(), static_cast<AssertArg>(portNum));
    return this->m_to_request_verification[portNum].isConnected();
  }

  bool NORFlashManagerTesterBase ::
    isConnected_to_cmdIn(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_to_cmdIn(), static_cast<AssertArg>(portNum));
    return this->m_to_cmdIn[portNum].isConnected();
  }

  bool NORFlashManagerTesterBase ::
    isConnected_to_get_fsw_size(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_to_get_fsw_size(), static_cast<AssertArg>(portNum));
    return this->m_to_get_fsw_size[portNum].isConnected();
  }

  bool NORFlashManagerTesterBase ::
    isConnected_to_request_write(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_to_request_write(), static_cast<AssertArg>(portNum));
    return this->m_to_request_write[portNum].isConnected();
  }

  bool NORFlashManagerTesterBase ::
    isConnected_to_worker_done(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_to_worker_done(), static_cast<AssertArg>(portNum));
    return this->m_to_worker_done[portNum].isConnected();
  }

  bool NORFlashManagerTesterBase ::
    isConnected_to_request_read(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_to_request_read(), static_cast<AssertArg>(portNum));
    return this->m_to_request_read[portNum].isConnected();
  }

  bool NORFlashManagerTesterBase ::
    isConnected_to_schedIn(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_to_schedIn(), static_cast<AssertArg>(portNum));
    return this->m_to_schedIn[portNum].isConnected();
  }

  bool NORFlashManagerTesterBase ::
    isConnected_to_request_erase(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_to_request_erase(), static_cast<AssertArg>(portNum));
    return this->m_to_request_erase[portNum].isConnected();
  }

  // ----------------------------------------------------------------------
  // Getters for from ports
  // ----------------------------------------------------------------------
 
  Fw::InputLogPort *NORFlashManagerTesterBase ::
    get_from_eventOut(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_from_eventOut(),static_cast<AssertArg>(portNum));
    return &this->m_from_eventOut[portNum];
  }

  Svc::InputPingPort *NORFlashManagerTesterBase ::
    get_from_PingResponse(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_from_PingResponse(),static_cast<AssertArg>(portNum));
    return &this->m_from_PingResponse[portNum];
  }

  Drv::InputNORFlash_ChecksumDonePort *NORFlashManagerTesterBase ::
    get_from_verification_done(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_from_verification_done(),static_cast<AssertArg>(portNum));
    return &this->m_from_verification_done[portNum];
  }

  Drv::InputNOR_donePort *NORFlashManagerTesterBase ::
    get_from_erase_done(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_from_erase_done(),static_cast<AssertArg>(portNum));
    return &this->m_from_erase_done[portNum];
  }

  Drv::InputNOR_donePort *NORFlashManagerTesterBase ::
    get_from_read_done(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_from_read_done(),static_cast<AssertArg>(portNum));
    return &this->m_from_read_done[portNum];
  }

  Drv::InputNORFlash_VerifyPort *NORFlashManagerTesterBase ::
    get_from_worker_verify(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_from_worker_verify(),static_cast<AssertArg>(portNum));
    return &this->m_from_worker_verify[portNum];
  }

  Fw::InputTimePort *NORFlashManagerTesterBase ::
    get_from_timeCaller(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_from_timeCaller(),static_cast<AssertArg>(portNum));
    return &this->m_from_timeCaller[portNum];
  }

  Fw::InputCmdResponsePort *NORFlashManagerTesterBase ::
    get_from_cmdResponse(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_from_cmdResponse(),static_cast<AssertArg>(portNum));
    return &this->m_from_cmdResponse[portNum];
  }

  Drv::InputNORFlash_BWPort *NORFlashManagerTesterBase ::
    get_from_worker_write(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_from_worker_write(),static_cast<AssertArg>(portNum));
    return &this->m_from_worker_write[portNum];
  }

  Fw::InputCmdRegPort *NORFlashManagerTesterBase ::
    get_from_cmdReg(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_from_cmdReg(),static_cast<AssertArg>(portNum));
    return &this->m_from_cmdReg[portNum];
  }

  Drv::InputNOR_donePort *NORFlashManagerTesterBase ::
    get_from_write_done(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_from_write_done(),static_cast<AssertArg>(portNum));
    return &this->m_from_write_done[portNum];
  }

  Drv::InputNORFlash_EraseBankAddrPort *NORFlashManagerTesterBase ::
    get_from_worker_erase(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_from_worker_erase(),static_cast<AssertArg>(portNum));
    return &this->m_from_worker_erase[portNum];
  }

  Drv::InputNORFlash_CancelPort *NORFlashManagerTesterBase ::
    get_from_worker_cancel(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_from_worker_cancel(),static_cast<AssertArg>(portNum));
    return &this->m_from_worker_cancel[portNum];
  }

  Drv::InputNORFlash_ResetPort *NORFlashManagerTesterBase ::
    get_from_worker_reset(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_from_worker_reset(),static_cast<AssertArg>(portNum));
    return &this->m_from_worker_reset[portNum];
  }

  Drv::InputNORFlash_BRPort *NORFlashManagerTesterBase ::
    get_from_worker_read(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_from_worker_read(),static_cast<AssertArg>(portNum));
    return &this->m_from_worker_read[portNum];
  }

#if FW_ENABLE_TEXT_LOGGING == 1
  Fw::InputLogTextPort *NORFlashManagerTesterBase ::
    get_from_LogText(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_from_LogText(),static_cast<AssertArg>(portNum));
    return &this->m_from_LogText[portNum];
  }
#endif

  // ----------------------------------------------------------------------
  // Static functions for from ports
  // ----------------------------------------------------------------------

  void NORFlashManagerTesterBase ::
    from_PingResponse_static(
        Fw::PassiveComponentBase *const callComp,
        const NATIVE_INT_TYPE portNum,
        U32 key
    )
  {
    FW_ASSERT(callComp);
    NORFlashManagerTesterBase* _testerBase = 
      static_cast<NORFlashManagerTesterBase*>(callComp);
    _testerBase->from_PingResponse_handlerBase(
        portNum,
        key
    );
  }

  void NORFlashManagerTesterBase ::
    from_verification_done_static(
        Fw::PassiveComponentBase *const callComp,
        const NATIVE_INT_TYPE portNum,
        I32 valid_nor,
        U32 read_blc_checksum,
        U32 read_fsw_checksum,
        U32 cptd_blc_checksum,
        U32 cptd_fsw_checksum
    )
  {
    FW_ASSERT(callComp);
    NORFlashManagerTesterBase* _testerBase = 
      static_cast<NORFlashManagerTesterBase*>(callComp);
    _testerBase->from_verification_done_handlerBase(
        portNum,
        valid_nor, read_blc_checksum, read_fsw_checksum, cptd_blc_checksum, cptd_fsw_checksum
    );
  }

  void NORFlashManagerTesterBase ::
    from_erase_done_static(
        Fw::PassiveComponentBase *const callComp,
        const NATIVE_INT_TYPE portNum,
        I8 done,
        U32 context1,
        U32 context2
    )
  {
    FW_ASSERT(callComp);
    NORFlashManagerTesterBase* _testerBase = 
      static_cast<NORFlashManagerTesterBase*>(callComp);
    _testerBase->from_erase_done_handlerBase(
        portNum,
        done, context1, context2
    );
  }

  void NORFlashManagerTesterBase ::
    from_read_done_static(
        Fw::PassiveComponentBase *const callComp,
        const NATIVE_INT_TYPE portNum,
        I8 done,
        U32 context1,
        U32 context2
    )
  {
    FW_ASSERT(callComp);
    NORFlashManagerTesterBase* _testerBase = 
      static_cast<NORFlashManagerTesterBase*>(callComp);
    _testerBase->from_read_done_handlerBase(
        portNum,
        done, context1, context2
    );
  }

  void NORFlashManagerTesterBase ::
    from_worker_verify_static(
        Fw::PassiveComponentBase *const callComp,
        const NATIVE_INT_TYPE portNum,
        U32 blc_filesize,
        U32 fsw_filesize
    )
  {
    FW_ASSERT(callComp);
    NORFlashManagerTesterBase* _testerBase = 
      static_cast<NORFlashManagerTesterBase*>(callComp);
    _testerBase->from_worker_verify_handlerBase(
        portNum,
        blc_filesize, fsw_filesize
    );
  }

  void NORFlashManagerTesterBase ::
    from_worker_write_static(
        Fw::PassiveComponentBase *const callComp,
        const NATIVE_INT_TYPE portNum,
        U32 dest,
        U8 *src,
        U32 count,
        U32 bank
    )
  {
    FW_ASSERT(callComp);
    NORFlashManagerTesterBase* _testerBase = 
      static_cast<NORFlashManagerTesterBase*>(callComp);
    _testerBase->from_worker_write_handlerBase(
        portNum,
        dest, src, count, bank
    );
  }

  void NORFlashManagerTesterBase ::
    from_write_done_static(
        Fw::PassiveComponentBase *const callComp,
        const NATIVE_INT_TYPE portNum,
        I8 done,
        U32 context1,
        U32 context2
    )
  {
    FW_ASSERT(callComp);
    NORFlashManagerTesterBase* _testerBase = 
      static_cast<NORFlashManagerTesterBase*>(callComp);
    _testerBase->from_write_done_handlerBase(
        portNum,
        done, context1, context2
    );
  }

  void NORFlashManagerTesterBase ::
    from_worker_erase_static(
        Fw::PassiveComponentBase *const callComp,
        const NATIVE_INT_TYPE portNum,
        U32 bank_addr
    )
  {
    FW_ASSERT(callComp);
    NORFlashManagerTesterBase* _testerBase = 
      static_cast<NORFlashManagerTesterBase*>(callComp);
    _testerBase->from_worker_erase_handlerBase(
        portNum,
        bank_addr
    );
  }

  void NORFlashManagerTesterBase ::
    from_worker_cancel_static(
        Fw::PassiveComponentBase *const callComp,
        const NATIVE_INT_TYPE portNum
    )
  {
    FW_ASSERT(callComp);
    NORFlashManagerTesterBase* _testerBase = 
      static_cast<NORFlashManagerTesterBase*>(callComp);
    _testerBase->from_worker_cancel_handlerBase(portNum);
  }

  void NORFlashManagerTesterBase ::
    from_worker_reset_static(
        Fw::PassiveComponentBase *const callComp,
        const NATIVE_INT_TYPE portNum,
        U32 dontcare_addr
    )
  {
    FW_ASSERT(callComp);
    NORFlashManagerTesterBase* _testerBase = 
      static_cast<NORFlashManagerTesterBase*>(callComp);
    _testerBase->from_worker_reset_handlerBase(
        portNum,
        dontcare_addr
    );
  }

  void NORFlashManagerTesterBase ::
    from_worker_read_static(
        Fw::PassiveComponentBase *const callComp,
        const NATIVE_INT_TYPE portNum,
        U8 *dest,
        U32 src,
        U32 count,
        U32 bank
    )
  {
    FW_ASSERT(callComp);
    NORFlashManagerTesterBase* _testerBase = 
      static_cast<NORFlashManagerTesterBase*>(callComp);
    _testerBase->from_worker_read_handlerBase(
        portNum,
        dest, src, count, bank
    );
  }

  void NORFlashManagerTesterBase ::
    from_cmdResponse_static(
        Fw::PassiveComponentBase *const component,
        const NATIVE_INT_TYPE portNum,
        const FwOpcodeType opCode,
        const U32 cmdSeq,
        const Fw::CommandResponse response
    )
  {
    NORFlashManagerTesterBase* _testerBase =
      static_cast<NORFlashManagerTesterBase*>(component);
    _testerBase->cmdResponseIn(opCode, cmdSeq, response);
  }

  void NORFlashManagerTesterBase ::
    from_cmdReg_static(
        Fw::PassiveComponentBase *const component,
        const NATIVE_INT_TYPE portNum,
        const FwOpcodeType opCode
    )
  {

  }

  void NORFlashManagerTesterBase ::
    from_eventOut_static(
        Fw::PassiveComponentBase *const component,
        const NATIVE_INT_TYPE portNum,
        FwEventIdType id,
        Fw::Time &timeTag,
        Fw::LogSeverity severity,
        Fw::LogBuffer &args
    )
  {
    NORFlashManagerTesterBase* _testerBase =
      static_cast<NORFlashManagerTesterBase*>(component);
    _testerBase->dispatchEvents(id, timeTag, severity, args);
  }

#if FW_ENABLE_TEXT_LOGGING == 1
  void NORFlashManagerTesterBase ::
    from_LogText_static(
        Fw::PassiveComponentBase *const component,
        const NATIVE_INT_TYPE portNum,
        FwEventIdType id,
        Fw::Time &timeTag,
        Fw::TextLogSeverity severity,
        Fw::TextLogString &text
    )
  {
    NORFlashManagerTesterBase* _testerBase =
      static_cast<NORFlashManagerTesterBase*>(component);
    _testerBase->textLogIn(id,timeTag,severity,text);
  }
#endif

  void NORFlashManagerTesterBase ::
    from_timeCaller_static(
        Fw::PassiveComponentBase *const component,
        const NATIVE_INT_TYPE portNum,
        Fw::Time& time
    )
  {
    NORFlashManagerTesterBase* _testerBase =
      static_cast<NORFlashManagerTesterBase*>(component);
    time = _testerBase->m_testTime;
  }

  // ----------------------------------------------------------------------
  // Histories for typed from ports
  // ----------------------------------------------------------------------

  void NORFlashManagerTesterBase ::
    clearFromPortHistory(void)
  {
    this->fromPortHistorySize = 0;
    this->fromPortHistory_PingResponse->clear();
    this->fromPortHistory_verification_done->clear();
    this->fromPortHistory_erase_done->clear();
    this->fromPortHistory_read_done->clear();
    this->fromPortHistory_worker_verify->clear();
    this->fromPortHistory_worker_write->clear();
    this->fromPortHistory_write_done->clear();
    this->fromPortHistory_worker_erase->clear();
    this->fromPortHistorySize_worker_cancel = 0;
    this->fromPortHistory_worker_reset->clear();
    this->fromPortHistory_worker_read->clear();
  }

  // ---------------------------------------------------------------------- 
  // From port: PingResponse
  // ---------------------------------------------------------------------- 

  void NORFlashManagerTesterBase ::
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
  // From port: verification_done
  // ---------------------------------------------------------------------- 

  void NORFlashManagerTesterBase ::
    pushFromPortEntry_verification_done(
        I32 valid_nor,
        U32 read_blc_checksum,
        U32 read_fsw_checksum,
        U32 cptd_blc_checksum,
        U32 cptd_fsw_checksum
    )
  {
    FromPortEntry_verification_done _e = {
      valid_nor, read_blc_checksum, read_fsw_checksum, cptd_blc_checksum, cptd_fsw_checksum
    };
    this->fromPortHistory_verification_done->push_back(_e);
    ++this->fromPortHistorySize;
  }

  // ---------------------------------------------------------------------- 
  // From port: erase_done
  // ---------------------------------------------------------------------- 

  void NORFlashManagerTesterBase ::
    pushFromPortEntry_erase_done(
        I8 done,
        U32 context1,
        U32 context2
    )
  {
    FromPortEntry_erase_done _e = {
      done, context1, context2
    };
    this->fromPortHistory_erase_done->push_back(_e);
    ++this->fromPortHistorySize;
  }

  // ---------------------------------------------------------------------- 
  // From port: read_done
  // ---------------------------------------------------------------------- 

  void NORFlashManagerTesterBase ::
    pushFromPortEntry_read_done(
        I8 done,
        U32 context1,
        U32 context2
    )
  {
    FromPortEntry_read_done _e = {
      done, context1, context2
    };
    this->fromPortHistory_read_done->push_back(_e);
    ++this->fromPortHistorySize;
  }

  // ---------------------------------------------------------------------- 
  // From port: worker_verify
  // ---------------------------------------------------------------------- 

  void NORFlashManagerTesterBase ::
    pushFromPortEntry_worker_verify(
        U32 blc_filesize,
        U32 fsw_filesize
    )
  {
    FromPortEntry_worker_verify _e = {
      blc_filesize, fsw_filesize
    };
    this->fromPortHistory_worker_verify->push_back(_e);
    ++this->fromPortHistorySize;
  }

  // ---------------------------------------------------------------------- 
  // From port: worker_write
  // ---------------------------------------------------------------------- 

  void NORFlashManagerTesterBase ::
    pushFromPortEntry_worker_write(
        U32 dest,
        U8 *src,
        U32 count,
        U32 bank
    )
  {
    FromPortEntry_worker_write _e = {
      dest, src, count, bank
    };
    this->fromPortHistory_worker_write->push_back(_e);
    ++this->fromPortHistorySize;
  }

  // ---------------------------------------------------------------------- 
  // From port: write_done
  // ---------------------------------------------------------------------- 

  void NORFlashManagerTesterBase ::
    pushFromPortEntry_write_done(
        I8 done,
        U32 context1,
        U32 context2
    )
  {
    FromPortEntry_write_done _e = {
      done, context1, context2
    };
    this->fromPortHistory_write_done->push_back(_e);
    ++this->fromPortHistorySize;
  }

  // ---------------------------------------------------------------------- 
  // From port: worker_erase
  // ---------------------------------------------------------------------- 

  void NORFlashManagerTesterBase ::
    pushFromPortEntry_worker_erase(
        U32 bank_addr
    )
  {
    FromPortEntry_worker_erase _e = {
      bank_addr
    };
    this->fromPortHistory_worker_erase->push_back(_e);
    ++this->fromPortHistorySize;
  }

  // ---------------------------------------------------------------------- 
  // From port: worker_cancel
  // ---------------------------------------------------------------------- 

  void NORFlashManagerTesterBase ::
    pushFromPortEntry_worker_cancel(
        void
    )
  {
    ++this->fromPortHistorySize_worker_cancel;
    ++this->fromPortHistorySize;
  }

  // ---------------------------------------------------------------------- 
  // From port: worker_reset
  // ---------------------------------------------------------------------- 

  void NORFlashManagerTesterBase ::
    pushFromPortEntry_worker_reset(
        U32 dontcare_addr
    )
  {
    FromPortEntry_worker_reset _e = {
      dontcare_addr
    };
    this->fromPortHistory_worker_reset->push_back(_e);
    ++this->fromPortHistorySize;
  }

  // ---------------------------------------------------------------------- 
  // From port: worker_read
  // ---------------------------------------------------------------------- 

  void NORFlashManagerTesterBase ::
    pushFromPortEntry_worker_read(
        U8 *dest,
        U32 src,
        U32 count,
        U32 bank
    )
  {
    FromPortEntry_worker_read _e = {
      dest, src, count, bank
    };
    this->fromPortHistory_worker_read->push_back(_e);
    ++this->fromPortHistorySize;
  }

  // ----------------------------------------------------------------------
  // Handler base functions for from ports
  // ----------------------------------------------------------------------

  void NORFlashManagerTesterBase ::
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

  void NORFlashManagerTesterBase ::
    from_verification_done_handlerBase(
        const NATIVE_INT_TYPE portNum,
        I32 valid_nor,
        U32 read_blc_checksum,
        U32 read_fsw_checksum,
        U32 cptd_blc_checksum,
        U32 cptd_fsw_checksum
    )
  {
    FW_ASSERT(portNum < this->getNum_from_verification_done(),static_cast<AssertArg>(portNum));
    this->from_verification_done_handler(
        portNum,
        valid_nor, read_blc_checksum, read_fsw_checksum, cptd_blc_checksum, cptd_fsw_checksum
    );
  }

  void NORFlashManagerTesterBase ::
    from_erase_done_handlerBase(
        const NATIVE_INT_TYPE portNum,
        I8 done,
        U32 context1,
        U32 context2
    )
  {
    FW_ASSERT(portNum < this->getNum_from_erase_done(),static_cast<AssertArg>(portNum));
    this->from_erase_done_handler(
        portNum,
        done, context1, context2
    );
  }

  void NORFlashManagerTesterBase ::
    from_read_done_handlerBase(
        const NATIVE_INT_TYPE portNum,
        I8 done,
        U32 context1,
        U32 context2
    )
  {
    FW_ASSERT(portNum < this->getNum_from_read_done(),static_cast<AssertArg>(portNum));
    this->from_read_done_handler(
        portNum,
        done, context1, context2
    );
  }

  void NORFlashManagerTesterBase ::
    from_worker_verify_handlerBase(
        const NATIVE_INT_TYPE portNum,
        U32 blc_filesize,
        U32 fsw_filesize
    )
  {
    FW_ASSERT(portNum < this->getNum_from_worker_verify(),static_cast<AssertArg>(portNum));
    this->from_worker_verify_handler(
        portNum,
        blc_filesize, fsw_filesize
    );
  }

  void NORFlashManagerTesterBase ::
    from_worker_write_handlerBase(
        const NATIVE_INT_TYPE portNum,
        U32 dest,
        U8 *src,
        U32 count,
        U32 bank
    )
  {
    FW_ASSERT(portNum < this->getNum_from_worker_write(),static_cast<AssertArg>(portNum));
    this->from_worker_write_handler(
        portNum,
        dest, src, count, bank
    );
  }

  void NORFlashManagerTesterBase ::
    from_write_done_handlerBase(
        const NATIVE_INT_TYPE portNum,
        I8 done,
        U32 context1,
        U32 context2
    )
  {
    FW_ASSERT(portNum < this->getNum_from_write_done(),static_cast<AssertArg>(portNum));
    this->from_write_done_handler(
        portNum,
        done, context1, context2
    );
  }

  void NORFlashManagerTesterBase ::
    from_worker_erase_handlerBase(
        const NATIVE_INT_TYPE portNum,
        U32 bank_addr
    )
  {
    FW_ASSERT(portNum < this->getNum_from_worker_erase(),static_cast<AssertArg>(portNum));
    this->from_worker_erase_handler(
        portNum,
        bank_addr
    );
  }

  void NORFlashManagerTesterBase ::
    from_worker_cancel_handlerBase(
        const NATIVE_INT_TYPE portNum
    )
  {
    FW_ASSERT(portNum < this->getNum_from_worker_cancel(),static_cast<AssertArg>(portNum));
    this->from_worker_cancel_handler(portNum);
  }

  void NORFlashManagerTesterBase ::
    from_worker_reset_handlerBase(
        const NATIVE_INT_TYPE portNum,
        U32 dontcare_addr
    )
  {
    FW_ASSERT(portNum < this->getNum_from_worker_reset(),static_cast<AssertArg>(portNum));
    this->from_worker_reset_handler(
        portNum,
        dontcare_addr
    );
  }

  void NORFlashManagerTesterBase ::
    from_worker_read_handlerBase(
        const NATIVE_INT_TYPE portNum,
        U8 *dest,
        U32 src,
        U32 count,
        U32 bank
    )
  {
    FW_ASSERT(portNum < this->getNum_from_worker_read(),static_cast<AssertArg>(portNum));
    this->from_worker_read_handler(
        portNum,
        dest, src, count, bank
    );
  }

  // ----------------------------------------------------------------------
  // Command response handling
  // ----------------------------------------------------------------------

  void NORFlashManagerTesterBase ::
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
  // Command: NOR_FLASH_RESET
  // ---------------------------------------------------------------------- 

  void NORFlashManagerTesterBase ::
    sendCmd_NOR_FLASH_RESET(
        const NATIVE_INT_TYPE instance,
        const U32 cmdSeq,
        U8 bank_number
    )
  {

    // Serialize arguments

    Fw::CmdArgBuffer buff;
    Fw::SerializeStatus _status;
    _status = buff.serialize(bank_number);
    FW_ASSERT(_status == Fw::FW_SERIALIZE_OK,static_cast<AssertArg>(_status));

    // Call output command port
    
    FwOpcodeType _opcode;
    const U32 idBase = this->getIdBase();
    _opcode = NORFlashManagerComponentBase::OPCODE_NOR_FLASH_RESET + idBase;

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
  // Command: NOR_FLASH_SET_WRITE_TIMEOUT
  // ---------------------------------------------------------------------- 

  void NORFlashManagerTesterBase ::
    sendCmd_NOR_FLASH_SET_WRITE_TIMEOUT(
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
    _opcode = NORFlashManagerComponentBase::OPCODE_NOR_FLASH_SET_WRITE_TIMEOUT + idBase;

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
  // Command: NOR_FLASH_SET_ERASE_TIMEOUT
  // ---------------------------------------------------------------------- 

  void NORFlashManagerTesterBase ::
    sendCmd_NOR_FLASH_SET_ERASE_TIMEOUT(
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
    _opcode = NORFlashManagerComponentBase::OPCODE_NOR_FLASH_SET_ERASE_TIMEOUT + idBase;

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
  // Command: NOR_FLASH_SET_VERIFY_TIMEOUT
  // ---------------------------------------------------------------------- 

  void NORFlashManagerTesterBase ::
    sendCmd_NOR_FLASH_SET_VERIFY_TIMEOUT(
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
    _opcode = NORFlashManagerComponentBase::OPCODE_NOR_FLASH_SET_VERIFY_TIMEOUT + idBase;

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

  
  void NORFlashManagerTesterBase ::
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

  void NORFlashManagerTesterBase ::
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

  void NORFlashManagerTesterBase ::
    setTestTime(const Fw::Time& time)
  {
    this->m_testTime = time;
  }

  // ----------------------------------------------------------------------
  // Event dispatch
  // ----------------------------------------------------------------------

  void NORFlashManagerTesterBase ::
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

      case NORFlashManagerComponentBase::EVENTID_NOR_ERASE_BUSY: 
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
        FW_ASSERT(_numArgs == 3,_numArgs,3);
        
#endif    
        U32 actual_state;
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
        _status = args.deserialize(actual_state);
        FW_ASSERT(
            _status == Fw::FW_SERIALIZE_OK,
            static_cast<AssertArg>(_status)
        );

        U32 expected_state;
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
        _status = args.deserialize(expected_state);
        FW_ASSERT(
            _status == Fw::FW_SERIALIZE_OK,
            static_cast<AssertArg>(_status)
        );

        U32 error_status;
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
        _status = args.deserialize(error_status);
        FW_ASSERT(
            _status == Fw::FW_SERIALIZE_OK,
            static_cast<AssertArg>(_status)
        );

        this->logIn_WARNING_HI_NOR_ERASE_BUSY(actual_state, expected_state, error_status);

        break;

      }

      case NORFlashManagerComponentBase::EVENTID_NOR_ERASE_FAIL: 
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
        U32 error_status;
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
        _status = args.deserialize(error_status);
        FW_ASSERT(
            _status == Fw::FW_SERIALIZE_OK,
            static_cast<AssertArg>(_status)
        );

        this->logIn_WARNING_HI_NOR_ERASE_FAIL(error_status);

        break;

      }

      case NORFlashManagerComponentBase::EVENTID_NOR_ERASING: 
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
        this->logIn_ACTIVITY_LO_NOR_ERASING();

        break;

      }

      case NORFlashManagerComponentBase::EVENTID_NOR_ERASE_TIMEOUT: 
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
        this->logIn_WARNING_HI_NOR_ERASE_TIMEOUT();

        break;

      }

      case NORFlashManagerComponentBase::EVENTID_NOR_ERASE_DONE: 
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
        this->logIn_ACTIVITY_LO_NOR_ERASE_DONE();

        break;

      }

      case NORFlashManagerComponentBase::EVENTID_NOR_RESET_FAIL: 
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
        U32 actual_state;
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
        _status = args.deserialize(actual_state);
        FW_ASSERT(
            _status == Fw::FW_SERIALIZE_OK,
            static_cast<AssertArg>(_status)
        );

        U32 expected_state;
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
        _status = args.deserialize(expected_state);
        FW_ASSERT(
            _status == Fw::FW_SERIALIZE_OK,
            static_cast<AssertArg>(_status)
        );

        this->logIn_WARNING_HI_NOR_RESET_FAIL(actual_state, expected_state);

        break;

      }

      case NORFlashManagerComponentBase::EVENTID_NOR_RESETTING: 
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
        this->logIn_ACTIVITY_LO_NOR_RESETTING();

        break;

      }

      case NORFlashManagerComponentBase::EVENTID_NOR_UNLOCK_BYPASS_FAILED: 
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
        this->logIn_WARNING_HI_NOR_UNLOCK_BYPASS_FAILED();

        break;

      }

      case NORFlashManagerComponentBase::EVENTID_NOR_UNLOCK_BYPASS_PROGRAM_FAILED: 
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
        this->logIn_WARNING_HI_NOR_UNLOCK_BYPASS_PROGRAM_FAILED();

        break;

      }

      case NORFlashManagerComponentBase::EVENTID_NOR_UNLOCK_BYPASS_RESET_FAILED: 
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
        this->logIn_WARNING_HI_NOR_UNLOCK_BYPASS_RESET_FAILED();

        break;

      }

      case NORFlashManagerComponentBase::EVENTID_NOR_FAILED_TO_VERIFY_DATA: 
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
        U32 dest_addr;
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
        _status = args.deserialize(dest_addr);
        FW_ASSERT(
            _status == Fw::FW_SERIALIZE_OK,
            static_cast<AssertArg>(_status)
        );

        U8 source;
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
        _status = args.deserialize(source);
        FW_ASSERT(
            _status == Fw::FW_SERIALIZE_OK,
            static_cast<AssertArg>(_status)
        );

        this->logIn_WARNING_HI_NOR_FAILED_TO_VERIFY_DATA(dest_addr, source);

        break;

      }

      case NORFlashManagerComponentBase::EVENTID_NOR_UNLOCK_BYPASS_RESET_DURING_ERASE: 
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
        this->logIn_WARNING_HI_NOR_UNLOCK_BYPASS_RESET_DURING_ERASE();

        break;

      }

      case NORFlashManagerComponentBase::EVENTID_NOR_FAILED_TO_RESET: 
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
        this->logIn_WARNING_HI_NOR_FAILED_TO_RESET();

        break;

      }

      case NORFlashManagerComponentBase::EVENTID_NOR_WRITE_TIMEOUT: 
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
        this->logIn_WARNING_HI_NOR_WRITE_TIMEOUT();

        break;

      }

      case NORFlashManagerComponentBase::EVENTID_NOR_FAILED_TO_VERIFY_CHECKSUM: 
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
        this->logIn_WARNING_HI_NOR_FAILED_TO_VERIFY_CHECKSUM();

        break;

      }

      case NORFlashManagerComponentBase::EVENTID_NOR_CHECKSUM_VERIFY_DONE: 
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
        this->logIn_ACTIVITY_LO_NOR_CHECKSUM_VERIFY_DONE();

        break;

      }

      case NORFlashManagerComponentBase::EVENTID_NOR_VERIFY_BUSY: 
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
        U32 actual_state;
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
        _status = args.deserialize(actual_state);
        FW_ASSERT(
            _status == Fw::FW_SERIALIZE_OK,
            static_cast<AssertArg>(_status)
        );

        U32 expected_state;
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
        _status = args.deserialize(expected_state);
        FW_ASSERT(
            _status == Fw::FW_SERIALIZE_OK,
            static_cast<AssertArg>(_status)
        );

        this->logIn_WARNING_HI_NOR_VERIFY_BUSY(actual_state, expected_state);

        break;

      }

      case NORFlashManagerComponentBase::EVENTID_NOR_FAILED_TO_READ_DATA: 
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
        U32 nor_addr;
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
        _status = args.deserialize(nor_addr);
        FW_ASSERT(
            _status == Fw::FW_SERIALIZE_OK,
            static_cast<AssertArg>(_status)
        );

        U32 dest;
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
        _status = args.deserialize(dest);
        FW_ASSERT(
            _status == Fw::FW_SERIALIZE_OK,
            static_cast<AssertArg>(_status)
        );

        this->logIn_WARNING_HI_NOR_FAILED_TO_READ_DATA(nor_addr, dest);

        break;

      }

      case NORFlashManagerComponentBase::EVENTID_NOR_READ_TIMEOUT: 
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
        this->logIn_WARNING_HI_NOR_READ_TIMEOUT();

        break;

      }

      case NORFlashManagerComponentBase::EVENTID_NOR_ALREADY_ERASING: 
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
        this->logIn_WARNING_HI_NOR_ALREADY_ERASING();

        break;

      }

      default: {
        FW_ASSERT(0, id);
        break;
      }

    }

  }

  void NORFlashManagerTesterBase ::
    clearEvents(void)
  {
    this->eventsSize = 0;
    this->eventHistory_NOR_ERASE_BUSY->clear();
    this->eventHistory_NOR_ERASE_FAIL->clear();
    this->eventsSize_NOR_ERASING = 0;
    this->eventsSize_NOR_ERASE_TIMEOUT = 0;
    this->eventsSize_NOR_ERASE_DONE = 0;
    this->eventHistory_NOR_RESET_FAIL->clear();
    this->eventsSize_NOR_RESETTING = 0;
    this->eventsSize_NOR_UNLOCK_BYPASS_FAILED = 0;
    this->eventsSize_NOR_UNLOCK_BYPASS_PROGRAM_FAILED = 0;
    this->eventsSize_NOR_UNLOCK_BYPASS_RESET_FAILED = 0;
    this->eventHistory_NOR_FAILED_TO_VERIFY_DATA->clear();
    this->eventsSize_NOR_UNLOCK_BYPASS_RESET_DURING_ERASE = 0;
    this->eventsSize_NOR_FAILED_TO_RESET = 0;
    this->eventsSize_NOR_WRITE_TIMEOUT = 0;
    this->eventsSize_NOR_FAILED_TO_VERIFY_CHECKSUM = 0;
    this->eventsSize_NOR_CHECKSUM_VERIFY_DONE = 0;
    this->eventHistory_NOR_VERIFY_BUSY->clear();
    this->eventHistory_NOR_FAILED_TO_READ_DATA->clear();
    this->eventsSize_NOR_READ_TIMEOUT = 0;
    this->eventsSize_NOR_ALREADY_ERASING = 0;
  }

#if FW_ENABLE_TEXT_LOGGING

  // ----------------------------------------------------------------------
  // Text events 
  // ----------------------------------------------------------------------

  void NORFlashManagerTesterBase ::
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

  void NORFlashManagerTesterBase ::
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

  void NORFlashManagerTesterBase ::
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
  // Event: NOR_ERASE_BUSY 
  // ----------------------------------------------------------------------

  void NORFlashManagerTesterBase ::
    logIn_WARNING_HI_NOR_ERASE_BUSY(
        U32 actual_state,
        U32 expected_state,
        U32 error_status
    )
  {
    EventEntry_NOR_ERASE_BUSY e = {
      actual_state, expected_state, error_status
    };
    eventHistory_NOR_ERASE_BUSY->push_back(e);
    ++this->eventsSize;
  }

  // ----------------------------------------------------------------------
  // Event: NOR_ERASE_FAIL 
  // ----------------------------------------------------------------------

  void NORFlashManagerTesterBase ::
    logIn_WARNING_HI_NOR_ERASE_FAIL(
        U32 error_status
    )
  {
    EventEntry_NOR_ERASE_FAIL e = {
      error_status
    };
    eventHistory_NOR_ERASE_FAIL->push_back(e);
    ++this->eventsSize;
  }

  // ----------------------------------------------------------------------
  // Event: NOR_ERASING 
  // ----------------------------------------------------------------------

  void NORFlashManagerTesterBase ::
    logIn_ACTIVITY_LO_NOR_ERASING(
        void
    )
  {
    ++this->eventsSize_NOR_ERASING;
    ++this->eventsSize;
  }

  // ----------------------------------------------------------------------
  // Event: NOR_ERASE_TIMEOUT 
  // ----------------------------------------------------------------------

  void NORFlashManagerTesterBase ::
    logIn_WARNING_HI_NOR_ERASE_TIMEOUT(
        void
    )
  {
    ++this->eventsSize_NOR_ERASE_TIMEOUT;
    ++this->eventsSize;
  }

  // ----------------------------------------------------------------------
  // Event: NOR_ERASE_DONE 
  // ----------------------------------------------------------------------

  void NORFlashManagerTesterBase ::
    logIn_ACTIVITY_LO_NOR_ERASE_DONE(
        void
    )
  {
    ++this->eventsSize_NOR_ERASE_DONE;
    ++this->eventsSize;
  }

  // ----------------------------------------------------------------------
  // Event: NOR_RESET_FAIL 
  // ----------------------------------------------------------------------

  void NORFlashManagerTesterBase ::
    logIn_WARNING_HI_NOR_RESET_FAIL(
        U32 actual_state,
        U32 expected_state
    )
  {
    EventEntry_NOR_RESET_FAIL e = {
      actual_state, expected_state
    };
    eventHistory_NOR_RESET_FAIL->push_back(e);
    ++this->eventsSize;
  }

  // ----------------------------------------------------------------------
  // Event: NOR_RESETTING 
  // ----------------------------------------------------------------------

  void NORFlashManagerTesterBase ::
    logIn_ACTIVITY_LO_NOR_RESETTING(
        void
    )
  {
    ++this->eventsSize_NOR_RESETTING;
    ++this->eventsSize;
  }

  // ----------------------------------------------------------------------
  // Event: NOR_UNLOCK_BYPASS_FAILED 
  // ----------------------------------------------------------------------

  void NORFlashManagerTesterBase ::
    logIn_WARNING_HI_NOR_UNLOCK_BYPASS_FAILED(
        void
    )
  {
    ++this->eventsSize_NOR_UNLOCK_BYPASS_FAILED;
    ++this->eventsSize;
  }

  // ----------------------------------------------------------------------
  // Event: NOR_UNLOCK_BYPASS_PROGRAM_FAILED 
  // ----------------------------------------------------------------------

  void NORFlashManagerTesterBase ::
    logIn_WARNING_HI_NOR_UNLOCK_BYPASS_PROGRAM_FAILED(
        void
    )
  {
    ++this->eventsSize_NOR_UNLOCK_BYPASS_PROGRAM_FAILED;
    ++this->eventsSize;
  }

  // ----------------------------------------------------------------------
  // Event: NOR_UNLOCK_BYPASS_RESET_FAILED 
  // ----------------------------------------------------------------------

  void NORFlashManagerTesterBase ::
    logIn_WARNING_HI_NOR_UNLOCK_BYPASS_RESET_FAILED(
        void
    )
  {
    ++this->eventsSize_NOR_UNLOCK_BYPASS_RESET_FAILED;
    ++this->eventsSize;
  }

  // ----------------------------------------------------------------------
  // Event: NOR_FAILED_TO_VERIFY_DATA 
  // ----------------------------------------------------------------------

  void NORFlashManagerTesterBase ::
    logIn_WARNING_HI_NOR_FAILED_TO_VERIFY_DATA(
        U32 dest_addr,
        U8 source
    )
  {
    EventEntry_NOR_FAILED_TO_VERIFY_DATA e = {
      dest_addr, source
    };
    eventHistory_NOR_FAILED_TO_VERIFY_DATA->push_back(e);
    ++this->eventsSize;
  }

  // ----------------------------------------------------------------------
  // Event: NOR_UNLOCK_BYPASS_RESET_DURING_ERASE 
  // ----------------------------------------------------------------------

  void NORFlashManagerTesterBase ::
    logIn_WARNING_HI_NOR_UNLOCK_BYPASS_RESET_DURING_ERASE(
        void
    )
  {
    ++this->eventsSize_NOR_UNLOCK_BYPASS_RESET_DURING_ERASE;
    ++this->eventsSize;
  }

  // ----------------------------------------------------------------------
  // Event: NOR_FAILED_TO_RESET 
  // ----------------------------------------------------------------------

  void NORFlashManagerTesterBase ::
    logIn_WARNING_HI_NOR_FAILED_TO_RESET(
        void
    )
  {
    ++this->eventsSize_NOR_FAILED_TO_RESET;
    ++this->eventsSize;
  }

  // ----------------------------------------------------------------------
  // Event: NOR_WRITE_TIMEOUT 
  // ----------------------------------------------------------------------

  void NORFlashManagerTesterBase ::
    logIn_WARNING_HI_NOR_WRITE_TIMEOUT(
        void
    )
  {
    ++this->eventsSize_NOR_WRITE_TIMEOUT;
    ++this->eventsSize;
  }

  // ----------------------------------------------------------------------
  // Event: NOR_FAILED_TO_VERIFY_CHECKSUM 
  // ----------------------------------------------------------------------

  void NORFlashManagerTesterBase ::
    logIn_WARNING_HI_NOR_FAILED_TO_VERIFY_CHECKSUM(
        void
    )
  {
    ++this->eventsSize_NOR_FAILED_TO_VERIFY_CHECKSUM;
    ++this->eventsSize;
  }

  // ----------------------------------------------------------------------
  // Event: NOR_CHECKSUM_VERIFY_DONE 
  // ----------------------------------------------------------------------

  void NORFlashManagerTesterBase ::
    logIn_ACTIVITY_LO_NOR_CHECKSUM_VERIFY_DONE(
        void
    )
  {
    ++this->eventsSize_NOR_CHECKSUM_VERIFY_DONE;
    ++this->eventsSize;
  }

  // ----------------------------------------------------------------------
  // Event: NOR_VERIFY_BUSY 
  // ----------------------------------------------------------------------

  void NORFlashManagerTesterBase ::
    logIn_WARNING_HI_NOR_VERIFY_BUSY(
        U32 actual_state,
        U32 expected_state
    )
  {
    EventEntry_NOR_VERIFY_BUSY e = {
      actual_state, expected_state
    };
    eventHistory_NOR_VERIFY_BUSY->push_back(e);
    ++this->eventsSize;
  }

  // ----------------------------------------------------------------------
  // Event: NOR_FAILED_TO_READ_DATA 
  // ----------------------------------------------------------------------

  void NORFlashManagerTesterBase ::
    logIn_WARNING_HI_NOR_FAILED_TO_READ_DATA(
        U32 nor_addr,
        U32 dest
    )
  {
    EventEntry_NOR_FAILED_TO_READ_DATA e = {
      nor_addr, dest
    };
    eventHistory_NOR_FAILED_TO_READ_DATA->push_back(e);
    ++this->eventsSize;
  }

  // ----------------------------------------------------------------------
  // Event: NOR_READ_TIMEOUT 
  // ----------------------------------------------------------------------

  void NORFlashManagerTesterBase ::
    logIn_WARNING_HI_NOR_READ_TIMEOUT(
        void
    )
  {
    ++this->eventsSize_NOR_READ_TIMEOUT;
    ++this->eventsSize;
  }

  // ----------------------------------------------------------------------
  // Event: NOR_ALREADY_ERASING 
  // ----------------------------------------------------------------------

  void NORFlashManagerTesterBase ::
    logIn_WARNING_HI_NOR_ALREADY_ERASING(
        void
    )
  {
    ++this->eventsSize_NOR_ALREADY_ERASING;
    ++this->eventsSize;
  }

} // end namespace Drv
