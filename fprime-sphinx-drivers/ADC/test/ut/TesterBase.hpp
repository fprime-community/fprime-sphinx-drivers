// ======================================================================
// \title  ADC/test/ut/TesterBase.hpp
// \author Auto-generated
// \brief  hpp file for ADC component test harness base class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
//
// ======================================================================

#ifndef ADC_TESTER_BASE_HPP
#define ADC_TESTER_BASE_HPP

#include <fprime-sphinx-drivers/ADC/ADCComponentAc.hpp>
#include <Fw/Types/Assert.hpp>
#include <Fw/Comp/PassiveComponentBase.hpp>
#include <stdio.h>
#include <Fw/Port/InputSerializePort.hpp>

namespace Drv {

  //! \class ADCTesterBase
  //! \brief Auto-generated base class for ADC component test harness
  //!
  class ADCTesterBase :
    public Fw::PassiveComponentBase
  {

    public:

      // ----------------------------------------------------------------------
      // Initialization
      // ----------------------------------------------------------------------

      //! Initialize object ADCTesterBase
      //!
      virtual void init(
          const NATIVE_INT_TYPE instance = 0 /*!< The instance number*/
      );

    public:

      // ----------------------------------------------------------------------
      // Connectors for 'to' ports
      // Connect these output ports to the input ports under test
      // ----------------------------------------------------------------------

      //! Connect schedIn to to_schedIn[portNum]
      //!
      void connect_to_schedIn(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          Svc::InputSchedPort *const schedIn /*!< The port*/
      );

      //! Connect cmdIn to to_cmdIn[portNum]
      //!
      void connect_to_cmdIn(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          Fw::InputCmdPort *const cmdIn /*!< The port*/
      );

      //! Connect PingRecv to to_PingRecv[portNum]
      //!
      void connect_to_PingRecv(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          Svc::InputPingPort *const PingRecv /*!< The port*/
      );

    public:

      // ----------------------------------------------------------------------
      // Getters for 'from' ports
      // Connect these input ports to the output ports under test
      // ----------------------------------------------------------------------

      //! Get the port that receives input from cmdReg
      //!
      //! \return from_cmdReg[portNum]
      //!
      Fw::InputCmdRegPort* get_from_cmdReg(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

      //! Get the port that receives input from timeCaller
      //!
      //! \return from_timeCaller[portNum]
      //!
      Fw::InputTimePort* get_from_timeCaller(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

      //! Get the port that receives input from eventOut
      //!
      //! \return from_eventOut[portNum]
      //!
      Fw::InputLogPort* get_from_eventOut(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

      //! Get the port that receives input from cmdResponse
      //!
      //! \return from_cmdResponse[portNum]
      //!
      Fw::InputCmdResponsePort* get_from_cmdResponse(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

      //! Get the port that receives input from PingResponse
      //!
      //! \return from_PingResponse[portNum]
      //!
      Svc::InputPingPort* get_from_PingResponse(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

      //! Get the port that receives input from adcOut
      //!
      //! \return from_adcOut[portNum]
      //!
      Drv::InputApidPort* get_from_adcOut(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

      //! Get the port that receives input from tlmOut
      //!
      //! \return from_tlmOut[portNum]
      //!
      Fw::InputTlmPort* get_from_tlmOut(
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

      //! Construct object ADCTesterBase
      //!
      ADCTesterBase(
#if FW_OBJECT_NAMES == 1
          const char *const compName, /*!< The component name*/
          const U32 maxHistorySize /*!< The maximum size of each history*/
#else
          const U32 maxHistorySize /*!< The maximum size of each history*/
#endif
      );

      //! Destroy object ADCTesterBase
      //!
      virtual ~ADCTesterBase(void);

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
      // Handler prototypes for typed from ports
      // ----------------------------------------------------------------------

      //! Handler prototype for from_PingResponse
      //!
      virtual void from_PingResponse_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          U32 key /*!< Value to return to pinger*/
      ) = 0;

      //! Handler base function for from_PingResponse
      //!
      void from_PingResponse_handlerBase(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          U32 key /*!< Value to return to pinger*/
      );

      //! Handler prototype for from_adcOut
      //!
      virtual void from_adcOut_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          Fw::Time timetag, 
          U16 apid, 
          Fw::FileBuffer &data, 
          U16 apid_rec 
      ) = 0;

      //! Handler base function for from_adcOut
      //!
      void from_adcOut_handlerBase(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          Fw::Time timetag, 
          U16 apid, 
          Fw::FileBuffer &data, 
          U16 apid_rec 
      );

    protected:

      // ----------------------------------------------------------------------
      // Histories for typed from ports
      // ----------------------------------------------------------------------

      //! Clear from port history
      //!
      void clearFromPortHistory(void);

      //! The total number of from port entries
      //!
      U32 fromPortHistorySize;

      //! Push an entry on the history for from_PingResponse
      void pushFromPortEntry_PingResponse(
          U32 key /*!< Value to return to pinger*/
      );

      //! A history entry for from_PingResponse
      //!
      typedef struct {
        U32 key;
      } FromPortEntry_PingResponse;

      //! The history for from_PingResponse
      //!
      History<FromPortEntry_PingResponse>
        *fromPortHistory_PingResponse;

      //! Push an entry on the history for from_adcOut
      void pushFromPortEntry_adcOut(
          Fw::Time timetag, 
          U16 apid, 
          Fw::FileBuffer &data, 
          U16 apid_rec 
      );

      //! A history entry for from_adcOut
      //!
      typedef struct {
        Fw::Time timetag;
        U16 apid;
        Fw::FileBuffer data;
        U16 apid_rec;
      } FromPortEntry_adcOut;

      //! The history for from_adcOut
      //!
      History<FromPortEntry_adcOut>
        *fromPortHistory_adcOut;

    protected:

      // ----------------------------------------------------------------------
      // Invocation functions for to ports
      // ----------------------------------------------------------------------

      //! Invoke the to port connected to schedIn
      //!
      void invoke_to_schedIn(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          NATIVE_UINT_TYPE context /*!< The call order*/
      );

      //! Invoke the to port connected to PingRecv
      //!
      void invoke_to_PingRecv(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          U32 key /*!< Value to return to pinger*/
      );

    public:

      // ----------------------------------------------------------------------
      // Getters for port counts
      // ----------------------------------------------------------------------

      //! Get the number of from_cmdReg ports
      //!
      //! \return The number of from_cmdReg ports
      //!
      NATIVE_INT_TYPE getNum_from_cmdReg(void) const;

      //! Get the number of from_timeCaller ports
      //!
      //! \return The number of from_timeCaller ports
      //!
      NATIVE_INT_TYPE getNum_from_timeCaller(void) const;

      //! Get the number of from_eventOut ports
      //!
      //! \return The number of from_eventOut ports
      //!
      NATIVE_INT_TYPE getNum_from_eventOut(void) const;

      //! Get the number of from_cmdResponse ports
      //!
      //! \return The number of from_cmdResponse ports
      //!
      NATIVE_INT_TYPE getNum_from_cmdResponse(void) const;

      //! Get the number of to_schedIn ports
      //!
      //! \return The number of to_schedIn ports
      //!
      NATIVE_INT_TYPE getNum_to_schedIn(void) const;

      //! Get the number of to_cmdIn ports
      //!
      //! \return The number of to_cmdIn ports
      //!
      NATIVE_INT_TYPE getNum_to_cmdIn(void) const;

      //! Get the number of from_PingResponse ports
      //!
      //! \return The number of from_PingResponse ports
      //!
      NATIVE_INT_TYPE getNum_from_PingResponse(void) const;

      //! Get the number of from_adcOut ports
      //!
      //! \return The number of from_adcOut ports
      //!
      NATIVE_INT_TYPE getNum_from_adcOut(void) const;

      //! Get the number of to_PingRecv ports
      //!
      //! \return The number of to_PingRecv ports
      //!
      NATIVE_INT_TYPE getNum_to_PingRecv(void) const;

      //! Get the number of from_tlmOut ports
      //!
      //! \return The number of from_tlmOut ports
      //!
      NATIVE_INT_TYPE getNum_from_tlmOut(void) const;

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
      //! Whether to_schedIn[portNum] is connected
      //!
      bool isConnected_to_schedIn(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

      //! Check whether port is connected
      //!
      //! Whether to_cmdIn[portNum] is connected
      //!
      bool isConnected_to_cmdIn(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

      //! Check whether port is connected
      //!
      //! Whether to_PingRecv[portNum] is connected
      //!
      bool isConnected_to_PingRecv(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

      // ----------------------------------------------------------------------
      // Functions for sending commands
      // ----------------------------------------------------------------------

    protected:

      // send command buffers directly - used for intentional command encoding errors
      void sendRawCmd(FwOpcodeType opcode, U32 cmdSeq, Fw::CmdArgBuffer& args);

      //! Send a ADC_SOC_SET_RATE command
      //!
      void sendCmd_ADC_SOC_SET_RATE(
          const NATIVE_INT_TYPE instance, /*!< The instance number*/
          const U32 cmdSeq, /*!< The command sequence number*/
          U8 rate /*!<  Rate of acquisition. Rate of 0 will set ADC to 0.1Hz, anything else will set it to 1Hz */
      );

      //! Send a ADC_SOC_SET_RUN command
      //!
      void sendCmd_ADC_SOC_SET_RUN(
          const NATIVE_INT_TYPE instance, /*!< The instance number*/
          const U32 cmdSeq, /*!< The command sequence number*/
          U8 run_mode /*!<  Set run mode. 0 will stop ADC. Anything else will have ADC running. */
      );

      //! Send a ADC_SOC_SET_PWR_CTRL command
      //!
      void sendCmd_ADC_SOC_SET_PWR_CTRL(
          const NATIVE_INT_TYPE instance, /*!< The instance number*/
          const U32 cmdSeq, /*!< The command sequence number*/
          U8 pwr_ctrl /*!<  Set power mode. 0 will disable power. Anything else will enable power. */
      );

      //! Send a ADC_SOC_SET_TLM_TIMEOUT command
      //!
      void sendCmd_ADC_SOC_SET_TLM_TIMEOUT(
          const NATIVE_INT_TYPE instance, /*!< The instance number*/
          const U32 cmdSeq, /*!< The command sequence number*/
          U32 timeout /*!<  Timeout value in tick units -- based on connected rategroup connection. */
      );

    protected:

      // ----------------------------------------------------------------------
      // Command response handling
      // ----------------------------------------------------------------------

      //! Handle a command response
      //!
      virtual void cmdResponseIn(
          const FwOpcodeType opCode, /*!< The opcode*/
          const U32 cmdSeq, /*!< The command sequence number*/
          const Fw::CommandResponse response /*!< The command response*/
      );

      //! A type representing a command response
      //!
      typedef struct {
        FwOpcodeType opCode;
        U32 cmdSeq;
        Fw::CommandResponse response;
      } CmdResponse;

      //! The command response history
      //!
      History<CmdResponse> *cmdResponseHistory;

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
      // Event: ADC_SOC_SetRate
      // ----------------------------------------------------------------------

      //! Handle event ADC_SOC_SetRate
      //!
      virtual void logIn_ACTIVITY_HI_ADC_SOC_SetRate(
          U8 rate, /*!< The rate ground sent up*/
          U8 rate_bit /*!< The rate to set ADC SOC*/
      );

      //! A history entry for event ADC_SOC_SetRate
      //!
      typedef struct {
        U8 rate;
        U8 rate_bit;
      } EventEntry_ADC_SOC_SetRate;

      //! The history of ADC_SOC_SetRate events
      //!
      History<EventEntry_ADC_SOC_SetRate>
        *eventHistory_ADC_SOC_SetRate;

    protected:

      // ----------------------------------------------------------------------
      // Event: ADC_SOC_SetRun
      // ----------------------------------------------------------------------

      //! Handle event ADC_SOC_SetRun
      //!
      virtual void logIn_ACTIVITY_HI_ADC_SOC_SetRun(
          U8 run /*!< The run to set ADC SOC*/
      );

      //! A history entry for event ADC_SOC_SetRun
      //!
      typedef struct {
        U8 run;
      } EventEntry_ADC_SOC_SetRun;

      //! The history of ADC_SOC_SetRun events
      //!
      History<EventEntry_ADC_SOC_SetRun>
        *eventHistory_ADC_SOC_SetRun;

    protected:

      // ----------------------------------------------------------------------
      // Event: ADC_SOC_SetPwrCtrl
      // ----------------------------------------------------------------------

      //! Handle event ADC_SOC_SetPwrCtrl
      //!
      virtual void logIn_ACTIVITY_HI_ADC_SOC_SetPwrCtrl(
          U8 pwr_ctrl /*!< The power control to set ADC SOC*/
      );

      //! A history entry for event ADC_SOC_SetPwrCtrl
      //!
      typedef struct {
        U8 pwr_ctrl;
      } EventEntry_ADC_SOC_SetPwrCtrl;

      //! The history of ADC_SOC_SetPwrCtrl events
      //!
      History<EventEntry_ADC_SOC_SetPwrCtrl>
        *eventHistory_ADC_SOC_SetPwrCtrl;

    protected:

      // ----------------------------------------------------------------------
      // Event: ADC_SOC_CouldNotSetPwrCtrlBit
      // ----------------------------------------------------------------------

      //! Handle event ADC_SOC_CouldNotSetPwrCtrlBit
      //!
      virtual void logIn_ACTIVITY_HI_ADC_SOC_CouldNotSetPwrCtrlBit(
          void
      );

      //! Size of history for event ADC_SOC_CouldNotSetPwrCtrlBit
      //!
      U32 eventsSize_ADC_SOC_CouldNotSetPwrCtrlBit;

    protected:

      // ----------------------------------------------------------------------
      // Event: ADC_SOC_CouldNotSetRunBit
      // ----------------------------------------------------------------------

      //! Handle event ADC_SOC_CouldNotSetRunBit
      //!
      virtual void logIn_ACTIVITY_HI_ADC_SOC_CouldNotSetRunBit(
          void
      );

      //! Size of history for event ADC_SOC_CouldNotSetRunBit
      //!
      U32 eventsSize_ADC_SOC_CouldNotSetRunBit;

    protected:

      // ----------------------------------------------------------------------
      // Event: ADC_SOC_CouldNotSetRate
      // ----------------------------------------------------------------------

      //! Handle event ADC_SOC_CouldNotSetRate
      //!
      virtual void logIn_ACTIVITY_HI_ADC_SOC_CouldNotSetRate(
          void
      );

      //! Size of history for event ADC_SOC_CouldNotSetRate
      //!
      U32 eventsSize_ADC_SOC_CouldNotSetRate;

    protected:

      // ----------------------------------------------------------------------
      // Event: ADC_SOC_TimedOut
      // ----------------------------------------------------------------------

      //! Handle event ADC_SOC_TimedOut
      //!
      virtual void logIn_WARNING_HI_ADC_SOC_TimedOut(
          U32 ticks /*!< The number of ticks until ADC SOC times out*/
      );

      //! A history entry for event ADC_SOC_TimedOut
      //!
      typedef struct {
        U32 ticks;
      } EventEntry_ADC_SOC_TimedOut;

      //! The history of ADC_SOC_TimedOut events
      //!
      History<EventEntry_ADC_SOC_TimedOut>
        *eventHistory_ADC_SOC_TimedOut;

    protected:

      // ----------------------------------------------------------------------
      // Event: ADC_SOC_SetTimeout
      // ----------------------------------------------------------------------

      //! Handle event ADC_SOC_SetTimeout
      //!
      virtual void logIn_ACTIVITY_HI_ADC_SOC_SetTimeout(
          U32 timeout /*!< The ADC's Telemetry timeout value*/
      );

      //! A history entry for event ADC_SOC_SetTimeout
      //!
      typedef struct {
        U32 timeout;
      } EventEntry_ADC_SOC_SetTimeout;

      //! The history of ADC_SOC_SetTimeout events
      //!
      History<EventEntry_ADC_SOC_SetTimeout>
        *eventHistory_ADC_SOC_SetTimeout;

    protected:

      // ----------------------------------------------------------------------
      // Telemetry dispatch
      // ----------------------------------------------------------------------

      //! Dispatch telemetry
      //!
      void dispatchTlm(
          const FwChanIdType id, /*!< The channel ID*/
          const Fw::Time& timeTag, /*!< The time*/
          Fw::TlmBuffer& val /*!< The channel value*/
      );

      //! Clear telemetry history
      //!
      void clearTlm(void);

      //! The total number of telemetry inputs seen
      //!
      U32 tlmSize;

    protected:

      // ----------------------------------------------------------------------
      // Channel: ADC_o_a2d_tlm0
      // ----------------------------------------------------------------------

      //! Handle channel ADC_o_a2d_tlm0
      //!
      virtual void tlmInput_ADC_o_a2d_tlm0(
          const Fw::Time& timeTag, /*!< The time*/
          const U32& val /*!< The channel value*/
      );

      //! A telemetry entry for channel ADC_o_a2d_tlm0
      //!
      typedef struct {
        Fw::Time timeTag;
        U32 arg;
      } TlmEntry_ADC_o_a2d_tlm0;

      //! The history of ADC_o_a2d_tlm0 values
      //!
      History<TlmEntry_ADC_o_a2d_tlm0>
        *tlmHistory_ADC_o_a2d_tlm0;

    protected:

      // ----------------------------------------------------------------------
      // Channel: ADC_o_a2d_tlm1
      // ----------------------------------------------------------------------

      //! Handle channel ADC_o_a2d_tlm1
      //!
      virtual void tlmInput_ADC_o_a2d_tlm1(
          const Fw::Time& timeTag, /*!< The time*/
          const U32& val /*!< The channel value*/
      );

      //! A telemetry entry for channel ADC_o_a2d_tlm1
      //!
      typedef struct {
        Fw::Time timeTag;
        U32 arg;
      } TlmEntry_ADC_o_a2d_tlm1;

      //! The history of ADC_o_a2d_tlm1 values
      //!
      History<TlmEntry_ADC_o_a2d_tlm1>
        *tlmHistory_ADC_o_a2d_tlm1;

    protected:

      // ----------------------------------------------------------------------
      // Channel: ADC_o_a2d_tlm2
      // ----------------------------------------------------------------------

      //! Handle channel ADC_o_a2d_tlm2
      //!
      virtual void tlmInput_ADC_o_a2d_tlm2(
          const Fw::Time& timeTag, /*!< The time*/
          const U32& val /*!< The channel value*/
      );

      //! A telemetry entry for channel ADC_o_a2d_tlm2
      //!
      typedef struct {
        Fw::Time timeTag;
        U32 arg;
      } TlmEntry_ADC_o_a2d_tlm2;

      //! The history of ADC_o_a2d_tlm2 values
      //!
      History<TlmEntry_ADC_o_a2d_tlm2>
        *tlmHistory_ADC_o_a2d_tlm2;

    protected:

      // ----------------------------------------------------------------------
      // Channel: ADC_o_a2d_tlm3
      // ----------------------------------------------------------------------

      //! Handle channel ADC_o_a2d_tlm3
      //!
      virtual void tlmInput_ADC_o_a2d_tlm3(
          const Fw::Time& timeTag, /*!< The time*/
          const U32& val /*!< The channel value*/
      );

      //! A telemetry entry for channel ADC_o_a2d_tlm3
      //!
      typedef struct {
        Fw::Time timeTag;
        U32 arg;
      } TlmEntry_ADC_o_a2d_tlm3;

      //! The history of ADC_o_a2d_tlm3 values
      //!
      History<TlmEntry_ADC_o_a2d_tlm3>
        *tlmHistory_ADC_o_a2d_tlm3;

    protected:

      // ----------------------------------------------------------------------
      // Channel: ADC_o_a2d_tlm4
      // ----------------------------------------------------------------------

      //! Handle channel ADC_o_a2d_tlm4
      //!
      virtual void tlmInput_ADC_o_a2d_tlm4(
          const Fw::Time& timeTag, /*!< The time*/
          const U32& val /*!< The channel value*/
      );

      //! A telemetry entry for channel ADC_o_a2d_tlm4
      //!
      typedef struct {
        Fw::Time timeTag;
        U32 arg;
      } TlmEntry_ADC_o_a2d_tlm4;

      //! The history of ADC_o_a2d_tlm4 values
      //!
      History<TlmEntry_ADC_o_a2d_tlm4>
        *tlmHistory_ADC_o_a2d_tlm4;

    protected:

      // ----------------------------------------------------------------------
      // Channel: ADC_o_a2d_tlm5
      // ----------------------------------------------------------------------

      //! Handle channel ADC_o_a2d_tlm5
      //!
      virtual void tlmInput_ADC_o_a2d_tlm5(
          const Fw::Time& timeTag, /*!< The time*/
          const U32& val /*!< The channel value*/
      );

      //! A telemetry entry for channel ADC_o_a2d_tlm5
      //!
      typedef struct {
        Fw::Time timeTag;
        U32 arg;
      } TlmEntry_ADC_o_a2d_tlm5;

      //! The history of ADC_o_a2d_tlm5 values
      //!
      History<TlmEntry_ADC_o_a2d_tlm5>
        *tlmHistory_ADC_o_a2d_tlm5;

    protected:

      // ----------------------------------------------------------------------
      // Channel: ADC_o_a2d_tlm6
      // ----------------------------------------------------------------------

      //! Handle channel ADC_o_a2d_tlm6
      //!
      virtual void tlmInput_ADC_o_a2d_tlm6(
          const Fw::Time& timeTag, /*!< The time*/
          const U32& val /*!< The channel value*/
      );

      //! A telemetry entry for channel ADC_o_a2d_tlm6
      //!
      typedef struct {
        Fw::Time timeTag;
        U32 arg;
      } TlmEntry_ADC_o_a2d_tlm6;

      //! The history of ADC_o_a2d_tlm6 values
      //!
      History<TlmEntry_ADC_o_a2d_tlm6>
        *tlmHistory_ADC_o_a2d_tlm6;

    protected:

      // ----------------------------------------------------------------------
      // Channel: ADC_o_a2d_tlm7
      // ----------------------------------------------------------------------

      //! Handle channel ADC_o_a2d_tlm7
      //!
      virtual void tlmInput_ADC_o_a2d_tlm7(
          const Fw::Time& timeTag, /*!< The time*/
          const U32& val /*!< The channel value*/
      );

      //! A telemetry entry for channel ADC_o_a2d_tlm7
      //!
      typedef struct {
        Fw::Time timeTag;
        U32 arg;
      } TlmEntry_ADC_o_a2d_tlm7;

      //! The history of ADC_o_a2d_tlm7 values
      //!
      History<TlmEntry_ADC_o_a2d_tlm7>
        *tlmHistory_ADC_o_a2d_tlm7;

    protected:

      // ----------------------------------------------------------------------
      // Channel: ADC_a2d_stat
      // ----------------------------------------------------------------------

      //! Handle channel ADC_a2d_stat
      //!
      virtual void tlmInput_ADC_a2d_stat(
          const Fw::Time& timeTag, /*!< The time*/
          const U32& val /*!< The channel value*/
      );

      //! A telemetry entry for channel ADC_a2d_stat
      //!
      typedef struct {
        Fw::Time timeTag;
        U32 arg;
      } TlmEntry_ADC_a2d_stat;

      //! The history of ADC_a2d_stat values
      //!
      History<TlmEntry_ADC_a2d_stat>
        *tlmHistory_ADC_a2d_stat;

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

      //! To port connected to schedIn
      //!
      Svc::OutputSchedPort m_to_schedIn[1];

      //! To port connected to cmdIn
      //!
      Fw::OutputCmdPort m_to_cmdIn[1];

      //! To port connected to PingRecv
      //!
      Svc::OutputPingPort m_to_PingRecv[1];

    private:

      // ----------------------------------------------------------------------
      // From ports
      // ----------------------------------------------------------------------

      //! From port connected to cmdReg
      //!
      Fw::InputCmdRegPort m_from_cmdReg[1];

      //! From port connected to timeCaller
      //!
      Fw::InputTimePort m_from_timeCaller[1];

      //! From port connected to eventOut
      //!
      Fw::InputLogPort m_from_eventOut[1];

      //! From port connected to cmdResponse
      //!
      Fw::InputCmdResponsePort m_from_cmdResponse[1];

      //! From port connected to PingResponse
      //!
      Svc::InputPingPort m_from_PingResponse[1];

      //! From port connected to adcOut
      //!
      Drv::InputApidPort m_from_adcOut[1];

      //! From port connected to tlmOut
      //!
      Fw::InputTlmPort m_from_tlmOut[1];

#if FW_ENABLE_TEXT_LOGGING == 1
      //! From port connected to LogText
      //!
      Fw::InputLogTextPort m_from_LogText[1];
#endif

    private:

      // ----------------------------------------------------------------------
      // Static functions for output ports
      // ----------------------------------------------------------------------

      //! Static function for port from_cmdReg
      //!
      static void from_cmdReg_static(
          Fw::PassiveComponentBase *const callComp, /*!< The component instance*/
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          FwOpcodeType opCode /*!< Command Op Code*/
      );

      //! Static function for port from_timeCaller
      //!
      static void from_timeCaller_static(
          Fw::PassiveComponentBase *const callComp, /*!< The component instance*/
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          Fw::Time &time /*!< The U32 cmd argument*/
      );

      //! Static function for port from_eventOut
      //!
      static void from_eventOut_static(
          Fw::PassiveComponentBase *const callComp, /*!< The component instance*/
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          FwEventIdType id, /*!< Log ID*/
          Fw::Time &timeTag, /*!< Time Tag*/
          Fw::LogSeverity severity, /*!< The severity argument*/
          Fw::LogBuffer &args /*!< Buffer containing serialized log entry*/
      );

      //! Static function for port from_cmdResponse
      //!
      static void from_cmdResponse_static(
          Fw::PassiveComponentBase *const callComp, /*!< The component instance*/
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          FwOpcodeType opCode, /*!< Command Op Code*/
          U32 cmdSeq, /*!< Command Sequence*/
          Fw::CommandResponse response /*!< The command response argument*/
      );

      //! Static function for port from_PingResponse
      //!
      static void from_PingResponse_static(
          Fw::PassiveComponentBase *const callComp, /*!< The component instance*/
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          U32 key /*!< Value to return to pinger*/
      );

      //! Static function for port from_adcOut
      //!
      static void from_adcOut_static(
          Fw::PassiveComponentBase *const callComp, /*!< The component instance*/
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          Fw::Time timetag, 
          U16 apid, 
          Fw::FileBuffer &data, 
          U16 apid_rec 
      );

      //! Static function for port from_tlmOut
      //!
      static void from_tlmOut_static(
          Fw::PassiveComponentBase *const callComp, /*!< The component instance*/
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          FwChanIdType id, /*!< Telemetry Channel ID*/
          Fw::Time &timeTag, /*!< Time Tag*/
          Fw::TlmBuffer &val /*!< Buffer containing serialized telemetry value*/
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
