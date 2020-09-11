// ======================================================================
// \title  SphinxUartOnboardDriver/test/ut/TesterBase.hpp
// \author Auto-generated
// \brief  hpp file for SphinxUartOnboardDriver component test harness base class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
//
// ======================================================================

#ifndef SphinxUartOnboardDriver_TESTER_BASE_HPP
#define SphinxUartOnboardDriver_TESTER_BASE_HPP

#include <fprime-sphinx-drivers/SphinxUartOnboardDriver/SphinxUartOnboardDriverComponentAc.hpp>
#include <Fw/Types/Assert.hpp>
#include <Fw/Comp/PassiveComponentBase.hpp>
#include <stdio.h>
#include <Fw/Port/InputSerializePort.hpp>

namespace Drv {

  //! \class SphinxUartOnboardDriverTesterBase
  //! \brief Auto-generated base class for SphinxUartOnboardDriver component test harness
  //!
  class SphinxUartOnboardDriverTesterBase :
    public Fw::PassiveComponentBase
  {

    public:

      // ----------------------------------------------------------------------
      // Initialization
      // ----------------------------------------------------------------------

      //! Initialize object SphinxUartOnboardDriverTesterBase
      //!
      virtual void init(
          const NATIVE_INT_TYPE instance = 0 /*!< The instance number*/
      );

    public:

      // ----------------------------------------------------------------------
      // Connectors for 'to' ports
      // Connect these output ports to the input ports under test
      // ----------------------------------------------------------------------

      //! Connect bytesUsed to to_bytesUsed[portNum]
      //!
      void connect_to_bytesUsed(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          Drv::InputSphinxUart_bytesUsedPortPort *const bytesUsed /*!< The port*/
      );

      //! Connect read to to_read[portNum]
      //!
      void connect_to_read(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          Drv::InputSphinxUart_readPortPort *const read /*!< The port*/
      );

      //! Connect write to to_write[portNum]
      //!
      void connect_to_write(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          Drv::InputSphinxUart_writePortPort *const write /*!< The port*/
      );

    public:

      // ----------------------------------------------------------------------
      // Getters for 'from' ports
      // Connect these input ports to the output ports under test
      // ----------------------------------------------------------------------

      //! Get the port that receives input from timeCaller
      //!
      //! \return from_timeCaller[portNum]
      //!
      Fw::InputTimePort* get_from_timeCaller(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

      //! Get the port that receives input from logOut
      //!
      //! \return from_logOut[portNum]
      //!
      Fw::InputLogPort* get_from_logOut(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

#if FW_ENABLE_TEXT_LOGGING == 1
      //! Get the port that receives input from LogText
      //!
      //! \return from_LogText[portNum]
      //!
      Fw::InputLogTextPort* get_from_LogText(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );
#endif

    protected:

      // ----------------------------------------------------------------------
      // Construction and destruction
      // ----------------------------------------------------------------------

      //! Construct object SphinxUartOnboardDriverTesterBase
      //!
      SphinxUartOnboardDriverTesterBase(
#if FW_OBJECT_NAMES == 1
          const char *const compName, /*!< The component name*/
          const U32 maxHistorySize /*!< The maximum size of each history*/
#else
          const U32 maxHistorySize /*!< The maximum size of each history*/
#endif
      );

      //! Destroy object SphinxUartOnboardDriverTesterBase
      //!
      virtual ~SphinxUartOnboardDriverTesterBase(void);

      // ----------------------------------------------------------------------
      // Test history
      // ----------------------------------------------------------------------

    protected:

      //! \class History
      //! \brief A history of port inputs
      //!
      template <typename T> class History {

        public:

          //! Create a History
          //!
          History(
              const U32 maxSize /*!< The maximum history size*/
          ) :
              numEntries(0),
              maxSize(maxSize)
          {
            this->entries = new T[maxSize];
          }

          //! Destroy a History
          //!
          ~History() {
            delete[] this->entries;
          }

          //! Clear the history
          //!
          void clear() { this->numEntries = 0; }

          //! Push an item onto the history
          //!
          void push_back(
              T entry /*!< The item*/
          ) {
            FW_ASSERT(this->numEntries < this->maxSize);
            entries[this->numEntries++] = entry;
          }

          //! Get an item at an index
          //!
          //! \return The item at index i
          //!
          T at(
              const U32 i /*!< The index*/
          ) const {
            FW_ASSERT(i < this->numEntries);
            return entries[i];
          }

          //! Get the number of entries in the history
          //!
          //! \return The number of entries in the history
          //!
          U32 size(void) const { return this->numEntries; }

        private:

          //! The number of entries in the history
          //!
          U32 numEntries;

          //! The maximum history size
          //!
          const U32 maxSize;

          //! The entries
          //!
          T *entries;

      };

      //! Clear all history
      //!
      void clearHistory(void);

    protected:

      // ----------------------------------------------------------------------
      // Invocation functions for to ports
      // ----------------------------------------------------------------------

      //! Invoke the to port connected to bytesUsed
      //!
      U32 invoke_to_bytesUsed(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

      //! Invoke the to port connected to read
      //!
      I32 invoke_to_read(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          U8 *read_buf_ptr, 
          U32 nBytes, 
          U32 timeout 
      );

      //! Invoke the to port connected to write
      //!
      I32 invoke_to_write(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          U8 *write_buf_ptr, 
          U32 nBytes, 
          U32 timeout 
      );

    public:

      // ----------------------------------------------------------------------
      // Getters for port counts
      // ----------------------------------------------------------------------

      //! Get the number of to_bytesUsed ports
      //!
      //! \return The number of to_bytesUsed ports
      //!
      NATIVE_INT_TYPE getNum_to_bytesUsed(void) const;

      //! Get the number of to_read ports
      //!
      //! \return The number of to_read ports
      //!
      NATIVE_INT_TYPE getNum_to_read(void) const;

      //! Get the number of from_timeCaller ports
      //!
      //! \return The number of from_timeCaller ports
      //!
      NATIVE_INT_TYPE getNum_from_timeCaller(void) const;

      //! Get the number of to_write ports
      //!
      //! \return The number of to_write ports
      //!
      NATIVE_INT_TYPE getNum_to_write(void) const;

      //! Get the number of from_logOut ports
      //!
      //! \return The number of from_logOut ports
      //!
      NATIVE_INT_TYPE getNum_from_logOut(void) const;

#if FW_ENABLE_TEXT_LOGGING == 1
      //! Get the number of from_LogText ports
      //!
      //! \return The number of from_LogText ports
      //!
      NATIVE_INT_TYPE getNum_from_LogText(void) const;
#endif

    protected:

      // ----------------------------------------------------------------------
      // Connection status for to ports
      // ----------------------------------------------------------------------

      //! Check whether port is connected
      //!
      //! Whether to_bytesUsed[portNum] is connected
      //!
      bool isConnected_to_bytesUsed(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

      //! Check whether port is connected
      //!
      //! Whether to_read[portNum] is connected
      //!
      bool isConnected_to_read(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

      //! Check whether port is connected
      //!
      //! Whether to_write[portNum] is connected
      //!
      bool isConnected_to_write(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

    protected:

      // ----------------------------------------------------------------------
      // Event dispatch
      // ----------------------------------------------------------------------

      //! Dispatch an event
      //!
      void dispatchEvents(
          const FwEventIdType id, /*!< The event ID*/
          Fw::Time& timeTag, /*!< The time*/
          const Fw::LogSeverity severity, /*!< The severity*/
          Fw::LogBuffer& args /*!< The serialized arguments*/
      );

      //! Clear event history
      //!
      void clearEvents(void);

      //! The total number of events seen
      //!
      U32 eventsSize;

#if FW_ENABLE_TEXT_LOGGING

    protected:

      // ----------------------------------------------------------------------
      // Text events
      // ----------------------------------------------------------------------

      //! Handle a text event
      //!
      virtual void textLogIn(
          const FwEventIdType id, /*!< The event ID*/
          Fw::Time& timeTag, /*!< The time*/
          const Fw::TextLogSeverity severity, /*!< The severity*/
          const Fw::TextLogString& text /*!< The event string*/
      );

      //! A history entry for the text log
      //!
      typedef struct {
        U32 id;
        Fw::Time timeTag;
        Fw::TextLogSeverity severity;
        Fw::TextLogString text;
      } TextLogEntry;

      //! The history of text log events
      //!
      History<TextLogEntry> *textLogHistory;

      //! Print a text log history entry
      //!
      static void printTextLogHistoryEntry(
          const TextLogEntry& e,
          FILE* file
      );

      //! Print the text log history
      //!
      void printTextLogHistory(FILE *const file);

#endif

    protected:

      // ----------------------------------------------------------------------
      // Event: UOBD_HardwareInitStatusError
      // ----------------------------------------------------------------------

      //! Handle event UOBD_HardwareInitStatusError
      //!
      virtual void logIn_WARNING_HI_UOBD_HardwareInitStatusError(
          U8 bitIndex, /*!< A zero-indexed bit in the status register*/
          U8 reported, /*!< Reported condition*/
          U8 expected, /*!< Expected condition*/
          Fw::LogStringArg& bitName /*!< The name of the bit*/
      );

      //! A history entry for event UOBD_HardwareInitStatusError
      //!
      typedef struct {
        U8 bitIndex;
        U8 reported;
        U8 expected;
        Fw::LogStringArg bitName;
      } EventEntry_UOBD_HardwareInitStatusError;

      //! The history of UOBD_HardwareInitStatusError events
      //!
      History<EventEntry_UOBD_HardwareInitStatusError>
        *eventHistory_UOBD_HardwareInitStatusError;

    protected:

      // ----------------------------------------------------------------------
      // Event: UOBD_HardwareInitPurgeError
      // ----------------------------------------------------------------------

      //! Handle event UOBD_HardwareInitPurgeError
      //!
      virtual void logIn_WARNING_HI_UOBD_HardwareInitPurgeError(
          void
      );

      //! Size of history for event UOBD_HardwareInitPurgeError
      //!
      U32 eventsSize_UOBD_HardwareInitPurgeError;

    protected:

      // ----------------------------------------------------------------------
      // Event: UOBD_BUFF_WRAP
      // ----------------------------------------------------------------------

      //! Handle event UOBD_BUFF_WRAP
      //!
      virtual void logIn_WARNING_HI_UOBD_BUFF_WRAP(
          void
      );

      //! Size of history for event UOBD_BUFF_WRAP
      //!
      U32 eventsSize_UOBD_BUFF_WRAP;

    protected:

      // ----------------------------------------------------------------------
      // Test time
      // ----------------------------------------------------------------------

      //! Set the test time for events and telemetry
      //!
      void setTestTime(
          const Fw::Time& timeTag /*!< The time*/
      );

    private:

      // ----------------------------------------------------------------------
      // To ports
      // ----------------------------------------------------------------------

      //! To port connected to bytesUsed
      //!
      Drv::OutputSphinxUart_bytesUsedPortPort m_to_bytesUsed[1];

      //! To port connected to read
      //!
      Drv::OutputSphinxUart_readPortPort m_to_read[1];

      //! To port connected to write
      //!
      Drv::OutputSphinxUart_writePortPort m_to_write[1];

    private:

      // ----------------------------------------------------------------------
      // From ports
      // ----------------------------------------------------------------------

      //! From port connected to timeCaller
      //!
      Fw::InputTimePort m_from_timeCaller[1];

      //! From port connected to logOut
      //!
      Fw::InputLogPort m_from_logOut[1];

#if FW_ENABLE_TEXT_LOGGING == 1
      //! From port connected to LogText
      //!
      Fw::InputLogTextPort m_from_LogText[1];
#endif

    private:

      // ----------------------------------------------------------------------
      // Static functions for output ports
      // ----------------------------------------------------------------------

      //! Static function for port from_timeCaller
      //!
      static void from_timeCaller_static(
          Fw::PassiveComponentBase *const callComp, /*!< The component instance*/
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          Fw::Time &time /*!< The U32 cmd argument*/
      );

      //! Static function for port from_logOut
      //!
      static void from_logOut_static(
          Fw::PassiveComponentBase *const callComp, /*!< The component instance*/
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          FwEventIdType id, /*!< Log ID*/
          Fw::Time &timeTag, /*!< Time Tag*/
          Fw::LogSeverity severity, /*!< The severity argument*/
          Fw::LogBuffer &args /*!< Buffer containing serialized log entry*/
      );

#if FW_ENABLE_TEXT_LOGGING == 1
      //! Static function for port from_LogText
      //!
      static void from_LogText_static(
          Fw::PassiveComponentBase *const callComp, /*!< The component instance*/
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          FwEventIdType id, /*!< Log ID*/
          Fw::Time &timeTag, /*!< Time Tag*/
          Fw::TextLogSeverity severity, /*!< The severity argument*/
          Fw::TextLogString &text /*!< Text of log message*/
      );
#endif

    private:

      // ----------------------------------------------------------------------
      // Test time
      // ----------------------------------------------------------------------

      //! Test time stamp
      //!
      Fw::Time m_testTime;

  };

} // end namespace Drv

#endif
