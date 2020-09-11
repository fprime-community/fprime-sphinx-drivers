// ======================================================================
// \title  ADC/test/ut/GTestBase.hpp
// \author Auto-generated
// \brief  hpp file for ADC component Google Test harness base class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
//
// ======================================================================

#ifndef ADC_GTEST_BASE_HPP
#define ADC_GTEST_BASE_HPP

#include "TesterBase.hpp"
#include "gtest/gtest.h"

// ----------------------------------------------------------------------
// Macros for command history assertions
// ----------------------------------------------------------------------

#define ASSERT_CMD_RESPONSE_SIZE(size) \
  this->assertCmdResponse_size(__FILE__, __LINE__, size)

#define ASSERT_CMD_RESPONSE(index, opCode, cmdSeq, response) \
  this->assertCmdResponse(__FILE__, __LINE__, index, opCode, cmdSeq, response)

// ----------------------------------------------------------------------
// Macros for telemetry history assertions
// ----------------------------------------------------------------------

#define ASSERT_TLM_SIZE(size) \
  this->assertTlm_size(__FILE__, __LINE__, size)

#define ASSERT_TLM_ADC_o_a2d_tlm0_SIZE(size) \
  this->assertTlm_ADC_o_a2d_tlm0_size(__FILE__, __LINE__, size)

#define ASSERT_TLM_ADC_o_a2d_tlm0(index, value) \
  this->assertTlm_ADC_o_a2d_tlm0(__FILE__, __LINE__, index, value)

#define ASSERT_TLM_ADC_o_a2d_tlm1_SIZE(size) \
  this->assertTlm_ADC_o_a2d_tlm1_size(__FILE__, __LINE__, size)

#define ASSERT_TLM_ADC_o_a2d_tlm1(index, value) \
  this->assertTlm_ADC_o_a2d_tlm1(__FILE__, __LINE__, index, value)

#define ASSERT_TLM_ADC_o_a2d_tlm2_SIZE(size) \
  this->assertTlm_ADC_o_a2d_tlm2_size(__FILE__, __LINE__, size)

#define ASSERT_TLM_ADC_o_a2d_tlm2(index, value) \
  this->assertTlm_ADC_o_a2d_tlm2(__FILE__, __LINE__, index, value)

#define ASSERT_TLM_ADC_o_a2d_tlm3_SIZE(size) \
  this->assertTlm_ADC_o_a2d_tlm3_size(__FILE__, __LINE__, size)

#define ASSERT_TLM_ADC_o_a2d_tlm3(index, value) \
  this->assertTlm_ADC_o_a2d_tlm3(__FILE__, __LINE__, index, value)

#define ASSERT_TLM_ADC_o_a2d_tlm4_SIZE(size) \
  this->assertTlm_ADC_o_a2d_tlm4_size(__FILE__, __LINE__, size)

#define ASSERT_TLM_ADC_o_a2d_tlm4(index, value) \
  this->assertTlm_ADC_o_a2d_tlm4(__FILE__, __LINE__, index, value)

#define ASSERT_TLM_ADC_o_a2d_tlm5_SIZE(size) \
  this->assertTlm_ADC_o_a2d_tlm5_size(__FILE__, __LINE__, size)

#define ASSERT_TLM_ADC_o_a2d_tlm5(index, value) \
  this->assertTlm_ADC_o_a2d_tlm5(__FILE__, __LINE__, index, value)

#define ASSERT_TLM_ADC_o_a2d_tlm6_SIZE(size) \
  this->assertTlm_ADC_o_a2d_tlm6_size(__FILE__, __LINE__, size)

#define ASSERT_TLM_ADC_o_a2d_tlm6(index, value) \
  this->assertTlm_ADC_o_a2d_tlm6(__FILE__, __LINE__, index, value)

#define ASSERT_TLM_ADC_o_a2d_tlm7_SIZE(size) \
  this->assertTlm_ADC_o_a2d_tlm7_size(__FILE__, __LINE__, size)

#define ASSERT_TLM_ADC_o_a2d_tlm7(index, value) \
  this->assertTlm_ADC_o_a2d_tlm7(__FILE__, __LINE__, index, value)

#define ASSERT_TLM_ADC_a2d_stat_SIZE(size) \
  this->assertTlm_ADC_a2d_stat_size(__FILE__, __LINE__, size)

#define ASSERT_TLM_ADC_a2d_stat(index, value) \
  this->assertTlm_ADC_a2d_stat(__FILE__, __LINE__, index, value)

// ----------------------------------------------------------------------
// Macros for event history assertions
// ----------------------------------------------------------------------

#define ASSERT_EVENTS_SIZE(size) \
  this->assertEvents_size(__FILE__, __LINE__, size)

#define ASSERT_EVENTS_ADC_SOC_SetRate_SIZE(size) \
  this->assertEvents_ADC_SOC_SetRate_size(__FILE__, __LINE__, size)

#define ASSERT_EVENTS_ADC_SOC_SetRate(index, _rate, _rate_bit) \
  this->assertEvents_ADC_SOC_SetRate(__FILE__, __LINE__, index, _rate, _rate_bit)

#define ASSERT_EVENTS_ADC_SOC_SetRun_SIZE(size) \
  this->assertEvents_ADC_SOC_SetRun_size(__FILE__, __LINE__, size)

#define ASSERT_EVENTS_ADC_SOC_SetRun(index, _run) \
  this->assertEvents_ADC_SOC_SetRun(__FILE__, __LINE__, index, _run)

#define ASSERT_EVENTS_ADC_SOC_SetPwrCtrl_SIZE(size) \
  this->assertEvents_ADC_SOC_SetPwrCtrl_size(__FILE__, __LINE__, size)

#define ASSERT_EVENTS_ADC_SOC_SetPwrCtrl(index, _pwr_ctrl) \
  this->assertEvents_ADC_SOC_SetPwrCtrl(__FILE__, __LINE__, index, _pwr_ctrl)

#define ASSERT_EVENTS_ADC_SOC_CouldNotSetPwrCtrlBit_SIZE(size) \
  this->assertEvents_ADC_SOC_CouldNotSetPwrCtrlBit_size(__FILE__, __LINE__, size)

#define ASSERT_EVENTS_ADC_SOC_CouldNotSetRunBit_SIZE(size) \
  this->assertEvents_ADC_SOC_CouldNotSetRunBit_size(__FILE__, __LINE__, size)

#define ASSERT_EVENTS_ADC_SOC_CouldNotSetRate_SIZE(size) \
  this->assertEvents_ADC_SOC_CouldNotSetRate_size(__FILE__, __LINE__, size)

#define ASSERT_EVENTS_ADC_SOC_TimedOut_SIZE(size) \
  this->assertEvents_ADC_SOC_TimedOut_size(__FILE__, __LINE__, size)

#define ASSERT_EVENTS_ADC_SOC_TimedOut(index, _ticks) \
  this->assertEvents_ADC_SOC_TimedOut(__FILE__, __LINE__, index, _ticks)

#define ASSERT_EVENTS_ADC_SOC_SetTimeout_SIZE(size) \
  this->assertEvents_ADC_SOC_SetTimeout_size(__FILE__, __LINE__, size)

#define ASSERT_EVENTS_ADC_SOC_SetTimeout(index, _timeout) \
  this->assertEvents_ADC_SOC_SetTimeout(__FILE__, __LINE__, index, _timeout)

// ----------------------------------------------------------------------
// Macros for typed user from port history assertions
// ----------------------------------------------------------------------

#define ASSERT_FROM_PORT_HISTORY_SIZE(size) \
  this->assertFromPortHistory_size(__FILE__, __LINE__, size)

#define ASSERT_from_PingResponse_SIZE(size) \
  this->assert_from_PingResponse_size(__FILE__, __LINE__, size)

#define ASSERT_from_PingResponse(index, _key) \
  { \
    ASSERT_GT(this->fromPortHistory_PingResponse->size(), static_cast<U32>(index)) \
    << "\n" \
    << "  File:     " << __FILE__ << "\n" \
    << "  Line:     " << __LINE__ << "\n" \
    << "  Value:    Index into history of from_PingResponse\n" \
    << "  Expected: Less than size of history (" \
    << this->fromPortHistory_PingResponse->size() << ")\n" \
    << "  Actual:   " << index << "\n"; \
    const FromPortEntry_PingResponse& _e = \
      this->fromPortHistory_PingResponse->at(index); \
    ASSERT_EQ(_key, _e.key) \
    << "\n" \
    << "  File:     " << __FILE__ << "\n" \
    << "  Line:     " << __LINE__ << "\n" \
    << "  Value:    Value of argument key at index " \
    << index \
    << " in history of from_PingResponse\n" \
    << "  Expected: " << _key << "\n" \
    << "  Actual:   " << _e.key << "\n"; \
  }

#define ASSERT_from_adcOut_SIZE(size) \
  this->assert_from_adcOut_size(__FILE__, __LINE__, size)

#define ASSERT_from_adcOut(index, _timetag, _apid, _data, _apid_rec) \
  { \
    ASSERT_GT(this->fromPortHistory_adcOut->size(), static_cast<U32>(index)) \
    << "\n" \
    << "  File:     " << __FILE__ << "\n" \
    << "  Line:     " << __LINE__ << "\n" \
    << "  Value:    Index into history of from_adcOut\n" \
    << "  Expected: Less than size of history (" \
    << this->fromPortHistory_adcOut->size() << ")\n" \
    << "  Actual:   " << index << "\n"; \
    const FromPortEntry_adcOut& _e = \
      this->fromPortHistory_adcOut->at(index); \
    ASSERT_EQ(_timetag, _e.timetag) \
    << "\n" \
    << "  File:     " << __FILE__ << "\n" \
    << "  Line:     " << __LINE__ << "\n" \
    << "  Value:    Value of argument timetag at index " \
    << index \
    << " in history of from_adcOut\n" \
    << "  Expected: " << _timetag << "\n" \
    << "  Actual:   " << _e.timetag << "\n"; \
    ASSERT_EQ(_apid, _e.apid) \
    << "\n" \
    << "  File:     " << __FILE__ << "\n" \
    << "  Line:     " << __LINE__ << "\n" \
    << "  Value:    Value of argument apid at index " \
    << index \
    << " in history of from_adcOut\n" \
    << "  Expected: " << _apid << "\n" \
    << "  Actual:   " << _e.apid << "\n"; \
    ASSERT_EQ(_data, _e.data) \
    << "\n" \
    << "  File:     " << __FILE__ << "\n" \
    << "  Line:     " << __LINE__ << "\n" \
    << "  Value:    Value of argument data at index " \
    << index \
    << " in history of from_adcOut\n" \
    << "  Expected: " << _data << "\n" \
    << "  Actual:   " << _e.data << "\n"; \
    ASSERT_EQ(_apid_rec, _e.apid_rec) \
    << "\n" \
    << "  File:     " << __FILE__ << "\n" \
    << "  Line:     " << __LINE__ << "\n" \
    << "  Value:    Value of argument apid_rec at index " \
    << index \
    << " in history of from_adcOut\n" \
    << "  Expected: " << _apid_rec << "\n" \
    << "  Actual:   " << _e.apid_rec << "\n"; \
  }

namespace Drv {

  //! \class ADCGTestBase
  //! \brief Auto-generated base class for ADC component Google Test harness
  //!
  class ADCGTestBase :
    public ADCTesterBase
  {

    protected:

      // ----------------------------------------------------------------------
      // Construction and destruction
      // ----------------------------------------------------------------------

      //! Construct object ADCGTestBase
      //!
      ADCGTestBase(
#if FW_OBJECT_NAMES == 1
          const char *const compName, /*!< The component name*/
          const U32 maxHistorySize /*!< The maximum size of each history*/
#else
          const U32 maxHistorySize /*!< The maximum size of each history*/
#endif
      );

      //! Destroy object ADCGTestBase
      //!
      virtual ~ADCGTestBase(void);

    protected:

      // ----------------------------------------------------------------------
      // Commands
      // ----------------------------------------------------------------------

      //! Assert size of command response history
      //!
      void assertCmdResponse_size(
          const char *const __callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __callSiteLineNumber, /*!< The line number of the call site*/
          const U32 size /*!< The asserted size*/
      ) const;

      //! Assert command response in history at index
      //!
      void assertCmdResponse(
          const char *const __callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __callSiteLineNumber, /*!< The line number of the call site*/
          const U32 __index, /*!< The index*/
          const FwOpcodeType opCode, /*!< The opcode*/
          const U32 cmdSeq, /*!< The command sequence number*/
          const Fw::CommandResponse response /*!< The command response*/
      ) const;

    protected:

      // ----------------------------------------------------------------------
      // Telemetry
      // ----------------------------------------------------------------------

      //! Assert size of telemetry history
      //!
      void assertTlm_size(
          const char *const __callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __callSiteLineNumber, /*!< The line number of the call site*/
          const U32 size /*!< The asserted size*/
      ) const;

    protected:

      // ----------------------------------------------------------------------
      // Channel: ADC_o_a2d_tlm0
      // ----------------------------------------------------------------------

      //! Assert telemetry value in history at index
      //!
      void assertTlm_ADC_o_a2d_tlm0_size(
          const char *const __callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __callSiteLineNumber, /*!< The line number of the call site*/
          const U32 size /*!< The asserted size*/
      ) const;

      void assertTlm_ADC_o_a2d_tlm0(
          const char *const __callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __callSiteLineNumber, /*!< The line number of the call site*/
          const U32 __index, /*!< The index*/
          const U32& val /*!< The channel value*/
      ) const;

    protected:

      // ----------------------------------------------------------------------
      // Channel: ADC_o_a2d_tlm1
      // ----------------------------------------------------------------------

      //! Assert telemetry value in history at index
      //!
      void assertTlm_ADC_o_a2d_tlm1_size(
          const char *const __callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __callSiteLineNumber, /*!< The line number of the call site*/
          const U32 size /*!< The asserted size*/
      ) const;

      void assertTlm_ADC_o_a2d_tlm1(
          const char *const __callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __callSiteLineNumber, /*!< The line number of the call site*/
          const U32 __index, /*!< The index*/
          const U32& val /*!< The channel value*/
      ) const;

    protected:

      // ----------------------------------------------------------------------
      // Channel: ADC_o_a2d_tlm2
      // ----------------------------------------------------------------------

      //! Assert telemetry value in history at index
      //!
      void assertTlm_ADC_o_a2d_tlm2_size(
          const char *const __callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __callSiteLineNumber, /*!< The line number of the call site*/
          const U32 size /*!< The asserted size*/
      ) const;

      void assertTlm_ADC_o_a2d_tlm2(
          const char *const __callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __callSiteLineNumber, /*!< The line number of the call site*/
          const U32 __index, /*!< The index*/
          const U32& val /*!< The channel value*/
      ) const;

    protected:

      // ----------------------------------------------------------------------
      // Channel: ADC_o_a2d_tlm3
      // ----------------------------------------------------------------------

      //! Assert telemetry value in history at index
      //!
      void assertTlm_ADC_o_a2d_tlm3_size(
          const char *const __callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __callSiteLineNumber, /*!< The line number of the call site*/
          const U32 size /*!< The asserted size*/
      ) const;

      void assertTlm_ADC_o_a2d_tlm3(
          const char *const __callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __callSiteLineNumber, /*!< The line number of the call site*/
          const U32 __index, /*!< The index*/
          const U32& val /*!< The channel value*/
      ) const;

    protected:

      // ----------------------------------------------------------------------
      // Channel: ADC_o_a2d_tlm4
      // ----------------------------------------------------------------------

      //! Assert telemetry value in history at index
      //!
      void assertTlm_ADC_o_a2d_tlm4_size(
          const char *const __callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __callSiteLineNumber, /*!< The line number of the call site*/
          const U32 size /*!< The asserted size*/
      ) const;

      void assertTlm_ADC_o_a2d_tlm4(
          const char *const __callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __callSiteLineNumber, /*!< The line number of the call site*/
          const U32 __index, /*!< The index*/
          const U32& val /*!< The channel value*/
      ) const;

    protected:

      // ----------------------------------------------------------------------
      // Channel: ADC_o_a2d_tlm5
      // ----------------------------------------------------------------------

      //! Assert telemetry value in history at index
      //!
      void assertTlm_ADC_o_a2d_tlm5_size(
          const char *const __callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __callSiteLineNumber, /*!< The line number of the call site*/
          const U32 size /*!< The asserted size*/
      ) const;

      void assertTlm_ADC_o_a2d_tlm5(
          const char *const __callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __callSiteLineNumber, /*!< The line number of the call site*/
          const U32 __index, /*!< The index*/
          const U32& val /*!< The channel value*/
      ) const;

    protected:

      // ----------------------------------------------------------------------
      // Channel: ADC_o_a2d_tlm6
      // ----------------------------------------------------------------------

      //! Assert telemetry value in history at index
      //!
      void assertTlm_ADC_o_a2d_tlm6_size(
          const char *const __callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __callSiteLineNumber, /*!< The line number of the call site*/
          const U32 size /*!< The asserted size*/
      ) const;

      void assertTlm_ADC_o_a2d_tlm6(
          const char *const __callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __callSiteLineNumber, /*!< The line number of the call site*/
          const U32 __index, /*!< The index*/
          const U32& val /*!< The channel value*/
      ) const;

    protected:

      // ----------------------------------------------------------------------
      // Channel: ADC_o_a2d_tlm7
      // ----------------------------------------------------------------------

      //! Assert telemetry value in history at index
      //!
      void assertTlm_ADC_o_a2d_tlm7_size(
          const char *const __callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __callSiteLineNumber, /*!< The line number of the call site*/
          const U32 size /*!< The asserted size*/
      ) const;

      void assertTlm_ADC_o_a2d_tlm7(
          const char *const __callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __callSiteLineNumber, /*!< The line number of the call site*/
          const U32 __index, /*!< The index*/
          const U32& val /*!< The channel value*/
      ) const;

    protected:

      // ----------------------------------------------------------------------
      // Channel: ADC_a2d_stat
      // ----------------------------------------------------------------------

      //! Assert telemetry value in history at index
      //!
      void assertTlm_ADC_a2d_stat_size(
          const char *const __callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __callSiteLineNumber, /*!< The line number of the call site*/
          const U32 size /*!< The asserted size*/
      ) const;

      void assertTlm_ADC_a2d_stat(
          const char *const __callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __callSiteLineNumber, /*!< The line number of the call site*/
          const U32 __index, /*!< The index*/
          const U32& val /*!< The channel value*/
      ) const;

    protected:

      // ----------------------------------------------------------------------
      // Events
      // ----------------------------------------------------------------------

      void assertEvents_size(
          const char *const __callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __callSiteLineNumber, /*!< The line number of the call site*/
          const U32 size /*!< The asserted size*/
      ) const;

    protected:

      // ----------------------------------------------------------------------
      // Event: ADC_SOC_SetRate
      // ----------------------------------------------------------------------

      void assertEvents_ADC_SOC_SetRate_size(
          const char *const __callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __callSiteLineNumber, /*!< The line number of the call site*/
          const U32 size /*!< The asserted size*/
      ) const;

      void assertEvents_ADC_SOC_SetRate(
          const char *const __callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __callSiteLineNumber, /*!< The line number of the call site*/
          const U32 __index, /*!< The index*/
          const U8 rate, /*!< The rate ground sent up*/
          const U8 rate_bit /*!< The rate to set ADC SOC*/
      ) const;

    protected:

      // ----------------------------------------------------------------------
      // Event: ADC_SOC_SetRun
      // ----------------------------------------------------------------------

      void assertEvents_ADC_SOC_SetRun_size(
          const char *const __callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __callSiteLineNumber, /*!< The line number of the call site*/
          const U32 size /*!< The asserted size*/
      ) const;

      void assertEvents_ADC_SOC_SetRun(
          const char *const __callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __callSiteLineNumber, /*!< The line number of the call site*/
          const U32 __index, /*!< The index*/
          const U8 run /*!< The run to set ADC SOC*/
      ) const;

    protected:

      // ----------------------------------------------------------------------
      // Event: ADC_SOC_SetPwrCtrl
      // ----------------------------------------------------------------------

      void assertEvents_ADC_SOC_SetPwrCtrl_size(
          const char *const __callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __callSiteLineNumber, /*!< The line number of the call site*/
          const U32 size /*!< The asserted size*/
      ) const;

      void assertEvents_ADC_SOC_SetPwrCtrl(
          const char *const __callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __callSiteLineNumber, /*!< The line number of the call site*/
          const U32 __index, /*!< The index*/
          const U8 pwr_ctrl /*!< The power control to set ADC SOC*/
      ) const;

    protected:

      // ----------------------------------------------------------------------
      // Event: ADC_SOC_CouldNotSetPwrCtrlBit
      // ----------------------------------------------------------------------

      void assertEvents_ADC_SOC_CouldNotSetPwrCtrlBit_size(
          const char *const __callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __callSiteLineNumber, /*!< The line number of the call site*/
          const U32 size /*!< The asserted size*/
      ) const;

    protected:

      // ----------------------------------------------------------------------
      // Event: ADC_SOC_CouldNotSetRunBit
      // ----------------------------------------------------------------------

      void assertEvents_ADC_SOC_CouldNotSetRunBit_size(
          const char *const __callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __callSiteLineNumber, /*!< The line number of the call site*/
          const U32 size /*!< The asserted size*/
      ) const;

    protected:

      // ----------------------------------------------------------------------
      // Event: ADC_SOC_CouldNotSetRate
      // ----------------------------------------------------------------------

      void assertEvents_ADC_SOC_CouldNotSetRate_size(
          const char *const __callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __callSiteLineNumber, /*!< The line number of the call site*/
          const U32 size /*!< The asserted size*/
      ) const;

    protected:

      // ----------------------------------------------------------------------
      // Event: ADC_SOC_TimedOut
      // ----------------------------------------------------------------------

      void assertEvents_ADC_SOC_TimedOut_size(
          const char *const __callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __callSiteLineNumber, /*!< The line number of the call site*/
          const U32 size /*!< The asserted size*/
      ) const;

      void assertEvents_ADC_SOC_TimedOut(
          const char *const __callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __callSiteLineNumber, /*!< The line number of the call site*/
          const U32 __index, /*!< The index*/
          const U32 ticks /*!< The number of ticks until ADC SOC times out*/
      ) const;

    protected:

      // ----------------------------------------------------------------------
      // Event: ADC_SOC_SetTimeout
      // ----------------------------------------------------------------------

      void assertEvents_ADC_SOC_SetTimeout_size(
          const char *const __callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __callSiteLineNumber, /*!< The line number of the call site*/
          const U32 size /*!< The asserted size*/
      ) const;

      void assertEvents_ADC_SOC_SetTimeout(
          const char *const __callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __callSiteLineNumber, /*!< The line number of the call site*/
          const U32 __index, /*!< The index*/
          const U32 timeout /*!< The ADC's Telemetry timeout value*/
      ) const;

    protected:

      // ----------------------------------------------------------------------
      // From ports
      // ----------------------------------------------------------------------

      void assertFromPortHistory_size(
          const char *const __callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __callSiteLineNumber, /*!< The line number of the call site*/
          const U32 size /*!< The asserted size*/
      ) const;

    protected:

      // ----------------------------------------------------------------------
      // From port: PingResponse
      // ----------------------------------------------------------------------

      void assert_from_PingResponse_size(
          const char *const __callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __callSiteLineNumber, /*!< The line number of the call site*/
          const U32 size /*!< The asserted size*/
      ) const;

    protected:

      // ----------------------------------------------------------------------
      // From port: adcOut
      // ----------------------------------------------------------------------

      void assert_from_adcOut_size(
          const char *const __callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __callSiteLineNumber, /*!< The line number of the call site*/
          const U32 size /*!< The asserted size*/
      ) const;

  };

} // end namespace Drv

#endif
