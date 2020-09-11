// ======================================================================
// \title  SphinxUartOnboardDriver/test/ut/TesterBase.cpp
// \author Auto-generated
// \brief  cpp file for SphinxUartOnboardDriver component test harness base class
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

  SphinxUartOnboardDriverTesterBase ::
    SphinxUartOnboardDriverTesterBase(
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
    // Initialize event histories
#if FW_ENABLE_TEXT_LOGGING
    this->textLogHistory = new History<TextLogEntry>(maxHistorySize);
#endif
    this->eventHistory_UOBD_HardwareInitStatusError =
      new History<EventEntry_UOBD_HardwareInitStatusError>(maxHistorySize);
    // Clear history
    this->clearHistory();
  }

  SphinxUartOnboardDriverTesterBase ::
    ~SphinxUartOnboardDriverTesterBase(void)
  {
    // Destroy event histories
#if FW_ENABLE_TEXT_LOGGING
    delete this->textLogHistory;
#endif
    delete this->eventHistory_UOBD_HardwareInitStatusError;
  }

  void SphinxUartOnboardDriverTesterBase ::
    init(
        const NATIVE_INT_TYPE instance
    )
  {

    // Initialize base class

		Fw::PassiveComponentBase::init(instance);

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

    // Attach input port logOut

    for (
        NATIVE_INT_TYPE _port = 0;
        _port < this->getNum_from_logOut();
        ++_port
    ) {

      this->m_from_logOut[_port].init();
      this->m_from_logOut[_port].addCallComp(
          this,
          from_logOut_static
      );
      this->m_from_logOut[_port].setPortNum(_port);

#if FW_OBJECT_NAMES == 1
      char _portName[120];
      (void) snprintf(
          _portName,
          sizeof(_portName),
          "%s_from_logOut[%d]",
          this->m_objName,
          _port
      );
      this->m_from_logOut[_port].setObjName(_portName);
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

    // Initialize output port bytesUsed

    for (
        NATIVE_INT_TYPE _port = 0;
        _port < this->getNum_to_bytesUsed();
        ++_port
    ) {
      this->m_to_bytesUsed[_port].init();

#if FW_OBJECT_NAMES == 1
      char _portName[120];
      snprintf(
          _portName,
          sizeof(_portName),
          "%s_to_bytesUsed[%d]",
          this->m_objName,
          _port
      );
      this->m_to_bytesUsed[_port].setObjName(_portName);
#endif

    }

    // Initialize output port read

    for (
        NATIVE_INT_TYPE _port = 0;
        _port < this->getNum_to_read();
        ++_port
    ) {
      this->m_to_read[_port].init();

#if FW_OBJECT_NAMES == 1
      char _portName[120];
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
      char _portName[120];
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

  NATIVE_INT_TYPE SphinxUartOnboardDriverTesterBase ::
    getNum_to_bytesUsed(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_to_bytesUsed);
  }

  NATIVE_INT_TYPE SphinxUartOnboardDriverTesterBase ::
    getNum_to_read(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_to_read);
  }

  NATIVE_INT_TYPE SphinxUartOnboardDriverTesterBase ::
    getNum_from_timeCaller(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_from_timeCaller);
  }

  NATIVE_INT_TYPE SphinxUartOnboardDriverTesterBase ::
    getNum_to_write(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_to_write);
  }

  NATIVE_INT_TYPE SphinxUartOnboardDriverTesterBase ::
    getNum_from_logOut(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_from_logOut);
  }

#if FW_ENABLE_TEXT_LOGGING == 1
  NATIVE_INT_TYPE SphinxUartOnboardDriverTesterBase ::
    getNum_from_LogText(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_from_LogText);
  }
#endif

  // ----------------------------------------------------------------------
  // Connectors for to ports
  // ----------------------------------------------------------------------

  void SphinxUartOnboardDriverTesterBase ::
    connect_to_bytesUsed(
        const NATIVE_INT_TYPE portNum,
        Drv::InputSphinxUart_bytesUsedPortPort *const bytesUsed
    )
  {
    FW_ASSERT(portNum < this->getNum_to_bytesUsed(),static_cast<AssertArg>(portNum));
    this->m_to_bytesUsed[portNum].addCallPort(bytesUsed);
  }

  void SphinxUartOnboardDriverTesterBase ::
    connect_to_read(
        const NATIVE_INT_TYPE portNum,
        Drv::InputSphinxUart_readPortPort *const read
    )
  {
    FW_ASSERT(portNum < this->getNum_to_read(),static_cast<AssertArg>(portNum));
    this->m_to_read[portNum].addCallPort(read);
  }

  void SphinxUartOnboardDriverTesterBase ::
    connect_to_write(
        const NATIVE_INT_TYPE portNum,
        Drv::InputSphinxUart_writePortPort *const write
    )
  {
    FW_ASSERT(portNum < this->getNum_to_write(),static_cast<AssertArg>(portNum));
    this->m_to_write[portNum].addCallPort(write);
  }


  // ----------------------------------------------------------------------
  // Invocation functions for to ports
  // ----------------------------------------------------------------------

  U32 SphinxUartOnboardDriverTesterBase ::
    invoke_to_bytesUsed(
        const NATIVE_INT_TYPE portNum
    )
  {
    FW_ASSERT(portNum < this->getNum_to_bytesUsed(),static_cast<AssertArg>(portNum));
    FW_ASSERT(portNum < this->getNum_to_bytesUsed(),static_cast<AssertArg>(portNum));
    return this->m_to_bytesUsed[portNum].invoke(
        
    );
  }

  I32 SphinxUartOnboardDriverTesterBase ::
    invoke_to_read(
        const NATIVE_INT_TYPE portNum,
        U8 *read_buf_ptr,
        U32 nBytes,
        U32 timeout
    )
  {
    FW_ASSERT(portNum < this->getNum_to_read(),static_cast<AssertArg>(portNum));
    FW_ASSERT(portNum < this->getNum_to_read(),static_cast<AssertArg>(portNum));
    return this->m_to_read[portNum].invoke(
        read_buf_ptr, nBytes, timeout
    );
  }

  I32 SphinxUartOnboardDriverTesterBase ::
    invoke_to_write(
        const NATIVE_INT_TYPE portNum,
        U8 *write_buf_ptr,
        U32 nBytes,
        U32 timeout
    )
  {
    FW_ASSERT(portNum < this->getNum_to_write(),static_cast<AssertArg>(portNum));
    FW_ASSERT(portNum < this->getNum_to_write(),static_cast<AssertArg>(portNum));
    return this->m_to_write[portNum].invoke(
        write_buf_ptr, nBytes, timeout
    );
  }

  // ----------------------------------------------------------------------
  // Connection status for to ports
  // ----------------------------------------------------------------------

  bool SphinxUartOnboardDriverTesterBase ::
    isConnected_to_bytesUsed(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_to_bytesUsed(), static_cast<AssertArg>(portNum));
    return this->m_to_bytesUsed[portNum].isConnected();
  }

  bool SphinxUartOnboardDriverTesterBase ::
    isConnected_to_read(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_to_read(), static_cast<AssertArg>(portNum));
    return this->m_to_read[portNum].isConnected();
  }

  bool SphinxUartOnboardDriverTesterBase ::
    isConnected_to_write(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_to_write(), static_cast<AssertArg>(portNum));
    return this->m_to_write[portNum].isConnected();
  }

  // ----------------------------------------------------------------------
  // Getters for from ports
  // ----------------------------------------------------------------------

  Fw::InputTimePort *SphinxUartOnboardDriverTesterBase ::
    get_from_timeCaller(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_from_timeCaller(),static_cast<AssertArg>(portNum));
    return &this->m_from_timeCaller[portNum];
  }

  Fw::InputLogPort *SphinxUartOnboardDriverTesterBase ::
    get_from_logOut(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_from_logOut(),static_cast<AssertArg>(portNum));
    return &this->m_from_logOut[portNum];
  }

#if FW_ENABLE_TEXT_LOGGING == 1
  Fw::InputLogTextPort *SphinxUartOnboardDriverTesterBase ::
    get_from_LogText(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_from_LogText(),static_cast<AssertArg>(portNum));
    return &this->m_from_LogText[portNum];
  }
#endif

  // ----------------------------------------------------------------------
  // Static functions for from ports
  // ----------------------------------------------------------------------

  void SphinxUartOnboardDriverTesterBase ::
    from_logOut_static(
        Fw::PassiveComponentBase *const component,
        const NATIVE_INT_TYPE portNum,
        FwEventIdType id,
        Fw::Time &timeTag,
        Fw::LogSeverity severity,
        Fw::LogBuffer &args
    )
  {
    SphinxUartOnboardDriverTesterBase* _testerBase =
      static_cast<SphinxUartOnboardDriverTesterBase*>(component);
    _testerBase->dispatchEvents(id, timeTag, severity, args);
  }

#if FW_ENABLE_TEXT_LOGGING == 1
  void SphinxUartOnboardDriverTesterBase ::
    from_LogText_static(
        Fw::PassiveComponentBase *const component,
        const NATIVE_INT_TYPE portNum,
        FwEventIdType id,
        Fw::Time &timeTag,
        Fw::TextLogSeverity severity,
        Fw::TextLogString &text
    )
  {
    SphinxUartOnboardDriverTesterBase* _testerBase =
      static_cast<SphinxUartOnboardDriverTesterBase*>(component);
    _testerBase->textLogIn(id,timeTag,severity,text);
  }
#endif

  void SphinxUartOnboardDriverTesterBase ::
    from_timeCaller_static(
        Fw::PassiveComponentBase *const component,
        const NATIVE_INT_TYPE portNum,
        Fw::Time& time
    )
  {
    SphinxUartOnboardDriverTesterBase* _testerBase =
      static_cast<SphinxUartOnboardDriverTesterBase*>(component);
    time = _testerBase->m_testTime;
  }

  // ----------------------------------------------------------------------
  // History
  // ----------------------------------------------------------------------

  void SphinxUartOnboardDriverTesterBase ::
    clearHistory()
  {
    this->textLogHistory->clear();
    this->clearEvents();
  }

  // ----------------------------------------------------------------------
  // Time
  // ----------------------------------------------------------------------

  void SphinxUartOnboardDriverTesterBase ::
    setTestTime(const Fw::Time& time)
  {
    this->m_testTime = time;
  }

  // ----------------------------------------------------------------------
  // Event dispatch
  // ----------------------------------------------------------------------

  void SphinxUartOnboardDriverTesterBase ::
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

      case SphinxUartOnboardDriverComponentBase::EVENTID_UOBD_HARDWAREINITSTATUSERROR:
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
        U8 bitIndex;
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
        _status = args.deserialize(bitIndex);
        FW_ASSERT(
            _status == Fw::FW_SERIALIZE_OK,
            static_cast<AssertArg>(_status)
        );

        U8 reported;
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
        _status = args.deserialize(reported);
        FW_ASSERT(
            _status == Fw::FW_SERIALIZE_OK,
            static_cast<AssertArg>(_status)
        );

        U8 expected;
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
        _status = args.deserialize(expected);
        FW_ASSERT(
            _status == Fw::FW_SERIALIZE_OK,
            static_cast<AssertArg>(_status)
        );

        Fw::LogStringArg bitName;
        _status = args.deserialize(bitName);
        FW_ASSERT(
            _status == Fw::FW_SERIALIZE_OK,
            static_cast<AssertArg>(_status)
        );

        this->logIn_WARNING_HI_UOBD_HardwareInitStatusError(bitIndex, reported, expected, bitName);

        break;

      }

      case SphinxUartOnboardDriverComponentBase::EVENTID_UOBD_HARDWAREINITPURGEERROR:
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
        this->logIn_WARNING_HI_UOBD_HardwareInitPurgeError();

        break;

      }

      case SphinxUartOnboardDriverComponentBase::EVENTID_UOBD_BUFF_WRAP:
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
        this->logIn_WARNING_HI_UOBD_BUFF_WRAP();

        break;

      }

      default: {
        FW_ASSERT(0, id);
        break;
      }

    }

  }

  void SphinxUartOnboardDriverTesterBase ::
    clearEvents(void)
  {
    this->eventsSize = 0;
    this->eventHistory_UOBD_HardwareInitStatusError->clear();
    this->eventsSize_UOBD_HardwareInitPurgeError = 0;
    this->eventsSize_UOBD_BUFF_WRAP = 0;
  }

#if FW_ENABLE_TEXT_LOGGING

  // ----------------------------------------------------------------------
  // Text events
  // ----------------------------------------------------------------------

  void SphinxUartOnboardDriverTesterBase ::
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

  void SphinxUartOnboardDriverTesterBase ::
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

  void SphinxUartOnboardDriverTesterBase ::
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
  // Event: UOBD_HardwareInitStatusError
  // ----------------------------------------------------------------------

  void SphinxUartOnboardDriverTesterBase ::
    logIn_WARNING_HI_UOBD_HardwareInitStatusError(
        U8 bitIndex,
        U8 reported,
        U8 expected,
        Fw::LogStringArg& bitName
    )
  {
    EventEntry_UOBD_HardwareInitStatusError e = {
      bitIndex, reported, expected, bitName
    };
    eventHistory_UOBD_HardwareInitStatusError->push_back(e);
    ++this->eventsSize;
  }

  // ----------------------------------------------------------------------
  // Event: UOBD_HardwareInitPurgeError
  // ----------------------------------------------------------------------

  void SphinxUartOnboardDriverTesterBase ::
    logIn_WARNING_HI_UOBD_HardwareInitPurgeError(
        void
    )
  {
    ++this->eventsSize_UOBD_HardwareInitPurgeError;
    ++this->eventsSize;
  }

  // ----------------------------------------------------------------------
  // Event: UOBD_BUFF_WRAP
  // ----------------------------------------------------------------------

  void SphinxUartOnboardDriverTesterBase ::
    logIn_WARNING_HI_UOBD_BUFF_WRAP(
        void
    )
  {
    ++this->eventsSize_UOBD_BUFF_WRAP;
    ++this->eventsSize;
  }

} // end namespace Drv
