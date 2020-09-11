// ======================================================================
// \title  ADC/test/ut/GTestBase.cpp
// \author Auto-generated
// \brief  cpp file for ADC component Google Test harness base class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
//
// ======================================================================

#include "GTestBase.hpp"

namespace Drv {

  // ----------------------------------------------------------------------
  // Construction and destruction
  // ----------------------------------------------------------------------

  ADCGTestBase ::
    ADCGTestBase(
#if FW_OBJECT_NAMES == 1
        const char *const compName,
        const U32 maxHistorySize
#else
        const U32 maxHistorySize
#endif
    ) :
        ADCTesterBase (
#if FW_OBJECT_NAMES == 1
            compName,
#endif
            maxHistorySize
        )
  {

  }

  ADCGTestBase ::
    ~ADCGTestBase(void)
  {

  }

  // ----------------------------------------------------------------------
  // Commands
  // ----------------------------------------------------------------------

  void ADCGTestBase ::
    assertCmdResponse_size(
        const char *const __callSiteFileName,
        const U32 __callSiteLineNumber,
        const U32 size
    ) const
  {
    ASSERT_EQ((unsigned long) size, this->cmdResponseHistory->size())
      << "\n"
      << "  File:     " << __callSiteFileName << "\n"
      << "  Line:     " << __callSiteLineNumber << "\n"
      << "  Value:    Size of command response history\n"
      << "  Expected: " << size << "\n"
      << "  Actual:   " << this->cmdResponseHistory->size() << "\n";
  }

  void ADCGTestBase ::
    assertCmdResponse(
        const char *const __callSiteFileName,
        const U32 __callSiteLineNumber,
        const U32 __index,
        const FwOpcodeType opCode,
        const U32 cmdSeq,
        const Fw::CommandResponse response
    )
    const
  {
    ASSERT_LT(__index, this->cmdResponseHistory->size())
      << "\n"
      << "  File:     " << __callSiteFileName << "\n"
      << "  Line:     " << __callSiteLineNumber << "\n"
      << "  Value:    Index into command response history\n"
      << "  Expected: Less than size of command response history ("
      << this->cmdResponseHistory->size() << ")\n"
      << "  Actual:   " << __index << "\n";
    const CmdResponse& e = this->cmdResponseHistory->at(__index);
    ASSERT_EQ(opCode, e.opCode)
      << "\n"
      << "  File:     " << __callSiteFileName << "\n"
      << "  Line:     " << __callSiteLineNumber << "\n"
      << "  Value:    Opcode at index "
      << __index
      << " in command response history\n"
      << "  Expected: " << opCode << "\n"
      << "  Actual:   " << e.opCode << "\n";
    ASSERT_EQ(cmdSeq, e.cmdSeq)
      << "\n"
      << "  File:     " << __callSiteFileName << "\n"
      << "  Line:     " << __callSiteLineNumber << "\n"
      << "  Value:    Command sequence number at index "
      << __index
      << " in command response history\n"
      << "  Expected: " << cmdSeq << "\n"
      << "  Actual:   " << e.cmdSeq << "\n";
    ASSERT_EQ(response, e.response)
      << "\n"
      << "  File:     " << __callSiteFileName << "\n"
      << "  Line:     " << __callSiteLineNumber << "\n"
      << "  Value:    Command response at index "
      << __index
      << " in command response history\n"
      << "  Expected: " << response << "\n"
      << "  Actual:   " << e.response << "\n";
  }

  // ----------------------------------------------------------------------
  // Telemetry
  // ----------------------------------------------------------------------

  void ADCGTestBase ::
    assertTlm_size(
        const char *const __callSiteFileName,
        const U32 __callSiteLineNumber,
        const U32 size
    ) const
  {
    ASSERT_EQ(size, this->tlmSize)
      << "\n"
      << "  File:     " << __callSiteFileName << "\n"
      << "  Line:     " << __callSiteLineNumber << "\n"
      << "  Value:    Total size of all telemetry histories\n"
      << "  Expected: " << size << "\n"
      << "  Actual:   " << this->tlmSize << "\n";
  }

  // ----------------------------------------------------------------------
  // Channel: ADC_o_a2d_tlm0
  // ----------------------------------------------------------------------

  void ADCGTestBase ::
    assertTlm_ADC_o_a2d_tlm0_size(
        const char *const __callSiteFileName,
        const U32 __callSiteLineNumber,
        const U32 size
    ) const
  {
    ASSERT_EQ(this->tlmHistory_ADC_o_a2d_tlm0->size(), size)
      << "\n"
      << "  File:     " << __callSiteFileName << "\n"
      << "  Line:     " << __callSiteLineNumber << "\n"
      << "  Value:    Size of history for telemetry channel ADC_o_a2d_tlm0\n"
      << "  Expected: " << size << "\n"
      << "  Actual:   " << this->tlmHistory_ADC_o_a2d_tlm0->size() << "\n";
  }

  void ADCGTestBase ::
    assertTlm_ADC_o_a2d_tlm0(
        const char *const __callSiteFileName,
        const U32 __callSiteLineNumber,
        const U32 __index,
        const U32& val
    )
    const
  {
    ASSERT_LT(__index, this->tlmHistory_ADC_o_a2d_tlm0->size())
      << "\n"
      << "  File:     " << __callSiteFileName << "\n"
      << "  Line:     " << __callSiteLineNumber << "\n"
      << "  Value:    Index into history of telemetry channel ADC_o_a2d_tlm0\n"
      << "  Expected: Less than size of history ("
      << this->tlmHistory_ADC_o_a2d_tlm0->size() << ")\n"
      << "  Actual:   " << __index << "\n";
    const TlmEntry_ADC_o_a2d_tlm0& e =
      this->tlmHistory_ADC_o_a2d_tlm0->at(__index);
    ASSERT_EQ(val, e.arg)
      << "\n"
      << "  File:     " << __callSiteFileName << "\n"
      << "  Line:     " << __callSiteLineNumber << "\n"
      << "  Value:    Value at index "
      << __index
      << " on telmetry channel ADC_o_a2d_tlm0\n"
      << "  Expected: " << val << "\n"
      << "  Actual:   " << e.arg << "\n";
  }

  // ----------------------------------------------------------------------
  // Channel: ADC_o_a2d_tlm1
  // ----------------------------------------------------------------------

  void ADCGTestBase ::
    assertTlm_ADC_o_a2d_tlm1_size(
        const char *const __callSiteFileName,
        const U32 __callSiteLineNumber,
        const U32 size
    ) const
  {
    ASSERT_EQ(this->tlmHistory_ADC_o_a2d_tlm1->size(), size)
      << "\n"
      << "  File:     " << __callSiteFileName << "\n"
      << "  Line:     " << __callSiteLineNumber << "\n"
      << "  Value:    Size of history for telemetry channel ADC_o_a2d_tlm1\n"
      << "  Expected: " << size << "\n"
      << "  Actual:   " << this->tlmHistory_ADC_o_a2d_tlm1->size() << "\n";
  }

  void ADCGTestBase ::
    assertTlm_ADC_o_a2d_tlm1(
        const char *const __callSiteFileName,
        const U32 __callSiteLineNumber,
        const U32 __index,
        const U32& val
    )
    const
  {
    ASSERT_LT(__index, this->tlmHistory_ADC_o_a2d_tlm1->size())
      << "\n"
      << "  File:     " << __callSiteFileName << "\n"
      << "  Line:     " << __callSiteLineNumber << "\n"
      << "  Value:    Index into history of telemetry channel ADC_o_a2d_tlm1\n"
      << "  Expected: Less than size of history ("
      << this->tlmHistory_ADC_o_a2d_tlm1->size() << ")\n"
      << "  Actual:   " << __index << "\n";
    const TlmEntry_ADC_o_a2d_tlm1& e =
      this->tlmHistory_ADC_o_a2d_tlm1->at(__index);
    ASSERT_EQ(val, e.arg)
      << "\n"
      << "  File:     " << __callSiteFileName << "\n"
      << "  Line:     " << __callSiteLineNumber << "\n"
      << "  Value:    Value at index "
      << __index
      << " on telmetry channel ADC_o_a2d_tlm1\n"
      << "  Expected: " << val << "\n"
      << "  Actual:   " << e.arg << "\n";
  }

  // ----------------------------------------------------------------------
  // Channel: ADC_o_a2d_tlm2
  // ----------------------------------------------------------------------

  void ADCGTestBase ::
    assertTlm_ADC_o_a2d_tlm2_size(
        const char *const __callSiteFileName,
        const U32 __callSiteLineNumber,
        const U32 size
    ) const
  {
    ASSERT_EQ(this->tlmHistory_ADC_o_a2d_tlm2->size(), size)
      << "\n"
      << "  File:     " << __callSiteFileName << "\n"
      << "  Line:     " << __callSiteLineNumber << "\n"
      << "  Value:    Size of history for telemetry channel ADC_o_a2d_tlm2\n"
      << "  Expected: " << size << "\n"
      << "  Actual:   " << this->tlmHistory_ADC_o_a2d_tlm2->size() << "\n";
  }

  void ADCGTestBase ::
    assertTlm_ADC_o_a2d_tlm2(
        const char *const __callSiteFileName,
        const U32 __callSiteLineNumber,
        const U32 __index,
        const U32& val
    )
    const
  {
    ASSERT_LT(__index, this->tlmHistory_ADC_o_a2d_tlm2->size())
      << "\n"
      << "  File:     " << __callSiteFileName << "\n"
      << "  Line:     " << __callSiteLineNumber << "\n"
      << "  Value:    Index into history of telemetry channel ADC_o_a2d_tlm2\n"
      << "  Expected: Less than size of history ("
      << this->tlmHistory_ADC_o_a2d_tlm2->size() << ")\n"
      << "  Actual:   " << __index << "\n";
    const TlmEntry_ADC_o_a2d_tlm2& e =
      this->tlmHistory_ADC_o_a2d_tlm2->at(__index);
    ASSERT_EQ(val, e.arg)
      << "\n"
      << "  File:     " << __callSiteFileName << "\n"
      << "  Line:     " << __callSiteLineNumber << "\n"
      << "  Value:    Value at index "
      << __index
      << " on telmetry channel ADC_o_a2d_tlm2\n"
      << "  Expected: " << val << "\n"
      << "  Actual:   " << e.arg << "\n";
  }

  // ----------------------------------------------------------------------
  // Channel: ADC_o_a2d_tlm3
  // ----------------------------------------------------------------------

  void ADCGTestBase ::
    assertTlm_ADC_o_a2d_tlm3_size(
        const char *const __callSiteFileName,
        const U32 __callSiteLineNumber,
        const U32 size
    ) const
  {
    ASSERT_EQ(this->tlmHistory_ADC_o_a2d_tlm3->size(), size)
      << "\n"
      << "  File:     " << __callSiteFileName << "\n"
      << "  Line:     " << __callSiteLineNumber << "\n"
      << "  Value:    Size of history for telemetry channel ADC_o_a2d_tlm3\n"
      << "  Expected: " << size << "\n"
      << "  Actual:   " << this->tlmHistory_ADC_o_a2d_tlm3->size() << "\n";
  }

  void ADCGTestBase ::
    assertTlm_ADC_o_a2d_tlm3(
        const char *const __callSiteFileName,
        const U32 __callSiteLineNumber,
        const U32 __index,
        const U32& val
    )
    const
  {
    ASSERT_LT(__index, this->tlmHistory_ADC_o_a2d_tlm3->size())
      << "\n"
      << "  File:     " << __callSiteFileName << "\n"
      << "  Line:     " << __callSiteLineNumber << "\n"
      << "  Value:    Index into history of telemetry channel ADC_o_a2d_tlm3\n"
      << "  Expected: Less than size of history ("
      << this->tlmHistory_ADC_o_a2d_tlm3->size() << ")\n"
      << "  Actual:   " << __index << "\n";
    const TlmEntry_ADC_o_a2d_tlm3& e =
      this->tlmHistory_ADC_o_a2d_tlm3->at(__index);
    ASSERT_EQ(val, e.arg)
      << "\n"
      << "  File:     " << __callSiteFileName << "\n"
      << "  Line:     " << __callSiteLineNumber << "\n"
      << "  Value:    Value at index "
      << __index
      << " on telmetry channel ADC_o_a2d_tlm3\n"
      << "  Expected: " << val << "\n"
      << "  Actual:   " << e.arg << "\n";
  }

  // ----------------------------------------------------------------------
  // Channel: ADC_o_a2d_tlm4
  // ----------------------------------------------------------------------

  void ADCGTestBase ::
    assertTlm_ADC_o_a2d_tlm4_size(
        const char *const __callSiteFileName,
        const U32 __callSiteLineNumber,
        const U32 size
    ) const
  {
    ASSERT_EQ(this->tlmHistory_ADC_o_a2d_tlm4->size(), size)
      << "\n"
      << "  File:     " << __callSiteFileName << "\n"
      << "  Line:     " << __callSiteLineNumber << "\n"
      << "  Value:    Size of history for telemetry channel ADC_o_a2d_tlm4\n"
      << "  Expected: " << size << "\n"
      << "  Actual:   " << this->tlmHistory_ADC_o_a2d_tlm4->size() << "\n";
  }

  void ADCGTestBase ::
    assertTlm_ADC_o_a2d_tlm4(
        const char *const __callSiteFileName,
        const U32 __callSiteLineNumber,
        const U32 __index,
        const U32& val
    )
    const
  {
    ASSERT_LT(__index, this->tlmHistory_ADC_o_a2d_tlm4->size())
      << "\n"
      << "  File:     " << __callSiteFileName << "\n"
      << "  Line:     " << __callSiteLineNumber << "\n"
      << "  Value:    Index into history of telemetry channel ADC_o_a2d_tlm4\n"
      << "  Expected: Less than size of history ("
      << this->tlmHistory_ADC_o_a2d_tlm4->size() << ")\n"
      << "  Actual:   " << __index << "\n";
    const TlmEntry_ADC_o_a2d_tlm4& e =
      this->tlmHistory_ADC_o_a2d_tlm4->at(__index);
    ASSERT_EQ(val, e.arg)
      << "\n"
      << "  File:     " << __callSiteFileName << "\n"
      << "  Line:     " << __callSiteLineNumber << "\n"
      << "  Value:    Value at index "
      << __index
      << " on telmetry channel ADC_o_a2d_tlm4\n"
      << "  Expected: " << val << "\n"
      << "  Actual:   " << e.arg << "\n";
  }

  // ----------------------------------------------------------------------
  // Channel: ADC_o_a2d_tlm5
  // ----------------------------------------------------------------------

  void ADCGTestBase ::
    assertTlm_ADC_o_a2d_tlm5_size(
        const char *const __callSiteFileName,
        const U32 __callSiteLineNumber,
        const U32 size
    ) const
  {
    ASSERT_EQ(this->tlmHistory_ADC_o_a2d_tlm5->size(), size)
      << "\n"
      << "  File:     " << __callSiteFileName << "\n"
      << "  Line:     " << __callSiteLineNumber << "\n"
      << "  Value:    Size of history for telemetry channel ADC_o_a2d_tlm5\n"
      << "  Expected: " << size << "\n"
      << "  Actual:   " << this->tlmHistory_ADC_o_a2d_tlm5->size() << "\n";
  }

  void ADCGTestBase ::
    assertTlm_ADC_o_a2d_tlm5(
        const char *const __callSiteFileName,
        const U32 __callSiteLineNumber,
        const U32 __index,
        const U32& val
    )
    const
  {
    ASSERT_LT(__index, this->tlmHistory_ADC_o_a2d_tlm5->size())
      << "\n"
      << "  File:     " << __callSiteFileName << "\n"
      << "  Line:     " << __callSiteLineNumber << "\n"
      << "  Value:    Index into history of telemetry channel ADC_o_a2d_tlm5\n"
      << "  Expected: Less than size of history ("
      << this->tlmHistory_ADC_o_a2d_tlm5->size() << ")\n"
      << "  Actual:   " << __index << "\n";
    const TlmEntry_ADC_o_a2d_tlm5& e =
      this->tlmHistory_ADC_o_a2d_tlm5->at(__index);
    ASSERT_EQ(val, e.arg)
      << "\n"
      << "  File:     " << __callSiteFileName << "\n"
      << "  Line:     " << __callSiteLineNumber << "\n"
      << "  Value:    Value at index "
      << __index
      << " on telmetry channel ADC_o_a2d_tlm5\n"
      << "  Expected: " << val << "\n"
      << "  Actual:   " << e.arg << "\n";
  }

  // ----------------------------------------------------------------------
  // Channel: ADC_o_a2d_tlm6
  // ----------------------------------------------------------------------

  void ADCGTestBase ::
    assertTlm_ADC_o_a2d_tlm6_size(
        const char *const __callSiteFileName,
        const U32 __callSiteLineNumber,
        const U32 size
    ) const
  {
    ASSERT_EQ(this->tlmHistory_ADC_o_a2d_tlm6->size(), size)
      << "\n"
      << "  File:     " << __callSiteFileName << "\n"
      << "  Line:     " << __callSiteLineNumber << "\n"
      << "  Value:    Size of history for telemetry channel ADC_o_a2d_tlm6\n"
      << "  Expected: " << size << "\n"
      << "  Actual:   " << this->tlmHistory_ADC_o_a2d_tlm6->size() << "\n";
  }

  void ADCGTestBase ::
    assertTlm_ADC_o_a2d_tlm6(
        const char *const __callSiteFileName,
        const U32 __callSiteLineNumber,
        const U32 __index,
        const U32& val
    )
    const
  {
    ASSERT_LT(__index, this->tlmHistory_ADC_o_a2d_tlm6->size())
      << "\n"
      << "  File:     " << __callSiteFileName << "\n"
      << "  Line:     " << __callSiteLineNumber << "\n"
      << "  Value:    Index into history of telemetry channel ADC_o_a2d_tlm6\n"
      << "  Expected: Less than size of history ("
      << this->tlmHistory_ADC_o_a2d_tlm6->size() << ")\n"
      << "  Actual:   " << __index << "\n";
    const TlmEntry_ADC_o_a2d_tlm6& e =
      this->tlmHistory_ADC_o_a2d_tlm6->at(__index);
    ASSERT_EQ(val, e.arg)
      << "\n"
      << "  File:     " << __callSiteFileName << "\n"
      << "  Line:     " << __callSiteLineNumber << "\n"
      << "  Value:    Value at index "
      << __index
      << " on telmetry channel ADC_o_a2d_tlm6\n"
      << "  Expected: " << val << "\n"
      << "  Actual:   " << e.arg << "\n";
  }

  // ----------------------------------------------------------------------
  // Channel: ADC_o_a2d_tlm7
  // ----------------------------------------------------------------------

  void ADCGTestBase ::
    assertTlm_ADC_o_a2d_tlm7_size(
        const char *const __callSiteFileName,
        const U32 __callSiteLineNumber,
        const U32 size
    ) const
  {
    ASSERT_EQ(this->tlmHistory_ADC_o_a2d_tlm7->size(), size)
      << "\n"
      << "  File:     " << __callSiteFileName << "\n"
      << "  Line:     " << __callSiteLineNumber << "\n"
      << "  Value:    Size of history for telemetry channel ADC_o_a2d_tlm7\n"
      << "  Expected: " << size << "\n"
      << "  Actual:   " << this->tlmHistory_ADC_o_a2d_tlm7->size() << "\n";
  }

  void ADCGTestBase ::
    assertTlm_ADC_o_a2d_tlm7(
        const char *const __callSiteFileName,
        const U32 __callSiteLineNumber,
        const U32 __index,
        const U32& val
    )
    const
  {
    ASSERT_LT(__index, this->tlmHistory_ADC_o_a2d_tlm7->size())
      << "\n"
      << "  File:     " << __callSiteFileName << "\n"
      << "  Line:     " << __callSiteLineNumber << "\n"
      << "  Value:    Index into history of telemetry channel ADC_o_a2d_tlm7\n"
      << "  Expected: Less than size of history ("
      << this->tlmHistory_ADC_o_a2d_tlm7->size() << ")\n"
      << "  Actual:   " << __index << "\n";
    const TlmEntry_ADC_o_a2d_tlm7& e =
      this->tlmHistory_ADC_o_a2d_tlm7->at(__index);
    ASSERT_EQ(val, e.arg)
      << "\n"
      << "  File:     " << __callSiteFileName << "\n"
      << "  Line:     " << __callSiteLineNumber << "\n"
      << "  Value:    Value at index "
      << __index
      << " on telmetry channel ADC_o_a2d_tlm7\n"
      << "  Expected: " << val << "\n"
      << "  Actual:   " << e.arg << "\n";
  }

  // ----------------------------------------------------------------------
  // Channel: ADC_a2d_stat
  // ----------------------------------------------------------------------

  void ADCGTestBase ::
    assertTlm_ADC_a2d_stat_size(
        const char *const __callSiteFileName,
        const U32 __callSiteLineNumber,
        const U32 size
    ) const
  {
    ASSERT_EQ(this->tlmHistory_ADC_a2d_stat->size(), size)
      << "\n"
      << "  File:     " << __callSiteFileName << "\n"
      << "  Line:     " << __callSiteLineNumber << "\n"
      << "  Value:    Size of history for telemetry channel ADC_a2d_stat\n"
      << "  Expected: " << size << "\n"
      << "  Actual:   " << this->tlmHistory_ADC_a2d_stat->size() << "\n";
  }

  void ADCGTestBase ::
    assertTlm_ADC_a2d_stat(
        const char *const __callSiteFileName,
        const U32 __callSiteLineNumber,
        const U32 __index,
        const U32& val
    )
    const
  {
    ASSERT_LT(__index, this->tlmHistory_ADC_a2d_stat->size())
      << "\n"
      << "  File:     " << __callSiteFileName << "\n"
      << "  Line:     " << __callSiteLineNumber << "\n"
      << "  Value:    Index into history of telemetry channel ADC_a2d_stat\n"
      << "  Expected: Less than size of history ("
      << this->tlmHistory_ADC_a2d_stat->size() << ")\n"
      << "  Actual:   " << __index << "\n";
    const TlmEntry_ADC_a2d_stat& e =
      this->tlmHistory_ADC_a2d_stat->at(__index);
    ASSERT_EQ(val, e.arg)
      << "\n"
      << "  File:     " << __callSiteFileName << "\n"
      << "  Line:     " << __callSiteLineNumber << "\n"
      << "  Value:    Value at index "
      << __index
      << " on telmetry channel ADC_a2d_stat\n"
      << "  Expected: " << val << "\n"
      << "  Actual:   " << e.arg << "\n";
  }

  // ----------------------------------------------------------------------
  // Events
  // ----------------------------------------------------------------------

  void ADCGTestBase ::
    assertEvents_size(
        const char *const __callSiteFileName,
        const U32 __callSiteLineNumber,
        const U32 size
    ) const
  {
    ASSERT_EQ(size, this->eventsSize)
      << "\n"
      << "  File:     " << __callSiteFileName << "\n"
      << "  Line:     " << __callSiteLineNumber << "\n"
      << "  Value:    Total size of all event histories\n"
      << "  Expected: " << size << "\n"
      << "  Actual:   " << this->eventsSize << "\n";
  }

  // ----------------------------------------------------------------------
  // Event: ADC_SOC_SetRate
  // ----------------------------------------------------------------------

  void ADCGTestBase ::
    assertEvents_ADC_SOC_SetRate_size(
        const char *const __callSiteFileName,
        const U32 __callSiteLineNumber,
        const U32 size
    ) const
  {
    ASSERT_EQ(size, this->eventHistory_ADC_SOC_SetRate->size())
      << "\n"
      << "  File:     " << __callSiteFileName << "\n"
      << "  Line:     " << __callSiteLineNumber << "\n"
      << "  Value:    Size of history for event ADC_SOC_SetRate\n"
      << "  Expected: " << size << "\n"
      << "  Actual:   " << this->eventHistory_ADC_SOC_SetRate->size() << "\n";
  }

  void ADCGTestBase ::
    assertEvents_ADC_SOC_SetRate(
        const char *const __callSiteFileName,
        const U32 __callSiteLineNumber,
        const U32 __index,
        const U8 rate,
        const U8 rate_bit
    ) const
  {
    ASSERT_GT(this->eventHistory_ADC_SOC_SetRate->size(), __index)
      << "\n"
      << "  File:     " << __callSiteFileName << "\n"
      << "  Line:     " << __callSiteLineNumber << "\n"
      << "  Value:    Index into history of event ADC_SOC_SetRate\n"
      << "  Expected: Less than size of history ("
      << this->eventHistory_ADC_SOC_SetRate->size() << ")\n"
      << "  Actual:   " << __index << "\n";
    const EventEntry_ADC_SOC_SetRate& e =
      this->eventHistory_ADC_SOC_SetRate->at(__index);
    ASSERT_EQ(rate, e.rate)
      << "\n"
      << "  File:     " << __callSiteFileName << "\n"
      << "  Line:     " << __callSiteLineNumber << "\n"
      << "  Value:    Value of argument rate at index "
      << __index
      << " in history of event ADC_SOC_SetRate\n"
      << "  Expected: " << rate << "\n"
      << "  Actual:   " << e.rate << "\n";
    ASSERT_EQ(rate_bit, e.rate_bit)
      << "\n"
      << "  File:     " << __callSiteFileName << "\n"
      << "  Line:     " << __callSiteLineNumber << "\n"
      << "  Value:    Value of argument rate_bit at index "
      << __index
      << " in history of event ADC_SOC_SetRate\n"
      << "  Expected: " << rate_bit << "\n"
      << "  Actual:   " << e.rate_bit << "\n";
  }

  // ----------------------------------------------------------------------
  // Event: ADC_SOC_SetRun
  // ----------------------------------------------------------------------

  void ADCGTestBase ::
    assertEvents_ADC_SOC_SetRun_size(
        const char *const __callSiteFileName,
        const U32 __callSiteLineNumber,
        const U32 size
    ) const
  {
    ASSERT_EQ(size, this->eventHistory_ADC_SOC_SetRun->size())
      << "\n"
      << "  File:     " << __callSiteFileName << "\n"
      << "  Line:     " << __callSiteLineNumber << "\n"
      << "  Value:    Size of history for event ADC_SOC_SetRun\n"
      << "  Expected: " << size << "\n"
      << "  Actual:   " << this->eventHistory_ADC_SOC_SetRun->size() << "\n";
  }

  void ADCGTestBase ::
    assertEvents_ADC_SOC_SetRun(
        const char *const __callSiteFileName,
        const U32 __callSiteLineNumber,
        const U32 __index,
        const U8 run
    ) const
  {
    ASSERT_GT(this->eventHistory_ADC_SOC_SetRun->size(), __index)
      << "\n"
      << "  File:     " << __callSiteFileName << "\n"
      << "  Line:     " << __callSiteLineNumber << "\n"
      << "  Value:    Index into history of event ADC_SOC_SetRun\n"
      << "  Expected: Less than size of history ("
      << this->eventHistory_ADC_SOC_SetRun->size() << ")\n"
      << "  Actual:   " << __index << "\n";
    const EventEntry_ADC_SOC_SetRun& e =
      this->eventHistory_ADC_SOC_SetRun->at(__index);
    ASSERT_EQ(run, e.run)
      << "\n"
      << "  File:     " << __callSiteFileName << "\n"
      << "  Line:     " << __callSiteLineNumber << "\n"
      << "  Value:    Value of argument run at index "
      << __index
      << " in history of event ADC_SOC_SetRun\n"
      << "  Expected: " << run << "\n"
      << "  Actual:   " << e.run << "\n";
  }

  // ----------------------------------------------------------------------
  // Event: ADC_SOC_SetPwrCtrl
  // ----------------------------------------------------------------------

  void ADCGTestBase ::
    assertEvents_ADC_SOC_SetPwrCtrl_size(
        const char *const __callSiteFileName,
        const U32 __callSiteLineNumber,
        const U32 size
    ) const
  {
    ASSERT_EQ(size, this->eventHistory_ADC_SOC_SetPwrCtrl->size())
      << "\n"
      << "  File:     " << __callSiteFileName << "\n"
      << "  Line:     " << __callSiteLineNumber << "\n"
      << "  Value:    Size of history for event ADC_SOC_SetPwrCtrl\n"
      << "  Expected: " << size << "\n"
      << "  Actual:   " << this->eventHistory_ADC_SOC_SetPwrCtrl->size() << "\n";
  }

  void ADCGTestBase ::
    assertEvents_ADC_SOC_SetPwrCtrl(
        const char *const __callSiteFileName,
        const U32 __callSiteLineNumber,
        const U32 __index,
        const U8 pwr_ctrl
    ) const
  {
    ASSERT_GT(this->eventHistory_ADC_SOC_SetPwrCtrl->size(), __index)
      << "\n"
      << "  File:     " << __callSiteFileName << "\n"
      << "  Line:     " << __callSiteLineNumber << "\n"
      << "  Value:    Index into history of event ADC_SOC_SetPwrCtrl\n"
      << "  Expected: Less than size of history ("
      << this->eventHistory_ADC_SOC_SetPwrCtrl->size() << ")\n"
      << "  Actual:   " << __index << "\n";
    const EventEntry_ADC_SOC_SetPwrCtrl& e =
      this->eventHistory_ADC_SOC_SetPwrCtrl->at(__index);
    ASSERT_EQ(pwr_ctrl, e.pwr_ctrl)
      << "\n"
      << "  File:     " << __callSiteFileName << "\n"
      << "  Line:     " << __callSiteLineNumber << "\n"
      << "  Value:    Value of argument pwr_ctrl at index "
      << __index
      << " in history of event ADC_SOC_SetPwrCtrl\n"
      << "  Expected: " << pwr_ctrl << "\n"
      << "  Actual:   " << e.pwr_ctrl << "\n";
  }

  // ----------------------------------------------------------------------
  // Event: ADC_SOC_CouldNotSetPwrCtrlBit
  // ----------------------------------------------------------------------

  void ADCGTestBase ::
    assertEvents_ADC_SOC_CouldNotSetPwrCtrlBit_size(
        const char *const __callSiteFileName,
        const U32 __callSiteLineNumber,
        const U32 size
    ) const
  {
    ASSERT_EQ(size, this->eventsSize_ADC_SOC_CouldNotSetPwrCtrlBit)
      << "\n"
      << "  File:     " << __callSiteFileName << "\n"
      << "  Line:     " << __callSiteLineNumber << "\n"
      << "  Value:    Size of history for event ADC_SOC_CouldNotSetPwrCtrlBit\n"
      << "  Expected: " << size << "\n"
      << "  Actual:   " << this->eventsSize_ADC_SOC_CouldNotSetPwrCtrlBit << "\n";
  }

  // ----------------------------------------------------------------------
  // Event: ADC_SOC_CouldNotSetRunBit
  // ----------------------------------------------------------------------

  void ADCGTestBase ::
    assertEvents_ADC_SOC_CouldNotSetRunBit_size(
        const char *const __callSiteFileName,
        const U32 __callSiteLineNumber,
        const U32 size
    ) const
  {
    ASSERT_EQ(size, this->eventsSize_ADC_SOC_CouldNotSetRunBit)
      << "\n"
      << "  File:     " << __callSiteFileName << "\n"
      << "  Line:     " << __callSiteLineNumber << "\n"
      << "  Value:    Size of history for event ADC_SOC_CouldNotSetRunBit\n"
      << "  Expected: " << size << "\n"
      << "  Actual:   " << this->eventsSize_ADC_SOC_CouldNotSetRunBit << "\n";
  }

  // ----------------------------------------------------------------------
  // Event: ADC_SOC_CouldNotSetRate
  // ----------------------------------------------------------------------

  void ADCGTestBase ::
    assertEvents_ADC_SOC_CouldNotSetRate_size(
        const char *const __callSiteFileName,
        const U32 __callSiteLineNumber,
        const U32 size
    ) const
  {
    ASSERT_EQ(size, this->eventsSize_ADC_SOC_CouldNotSetRate)
      << "\n"
      << "  File:     " << __callSiteFileName << "\n"
      << "  Line:     " << __callSiteLineNumber << "\n"
      << "  Value:    Size of history for event ADC_SOC_CouldNotSetRate\n"
      << "  Expected: " << size << "\n"
      << "  Actual:   " << this->eventsSize_ADC_SOC_CouldNotSetRate << "\n";
  }

  // ----------------------------------------------------------------------
  // Event: ADC_SOC_TimedOut
  // ----------------------------------------------------------------------

  void ADCGTestBase ::
    assertEvents_ADC_SOC_TimedOut_size(
        const char *const __callSiteFileName,
        const U32 __callSiteLineNumber,
        const U32 size
    ) const
  {
    ASSERT_EQ(size, this->eventHistory_ADC_SOC_TimedOut->size())
      << "\n"
      << "  File:     " << __callSiteFileName << "\n"
      << "  Line:     " << __callSiteLineNumber << "\n"
      << "  Value:    Size of history for event ADC_SOC_TimedOut\n"
      << "  Expected: " << size << "\n"
      << "  Actual:   " << this->eventHistory_ADC_SOC_TimedOut->size() << "\n";
  }

  void ADCGTestBase ::
    assertEvents_ADC_SOC_TimedOut(
        const char *const __callSiteFileName,
        const U32 __callSiteLineNumber,
        const U32 __index,
        const U32 ticks
    ) const
  {
    ASSERT_GT(this->eventHistory_ADC_SOC_TimedOut->size(), __index)
      << "\n"
      << "  File:     " << __callSiteFileName << "\n"
      << "  Line:     " << __callSiteLineNumber << "\n"
      << "  Value:    Index into history of event ADC_SOC_TimedOut\n"
      << "  Expected: Less than size of history ("
      << this->eventHistory_ADC_SOC_TimedOut->size() << ")\n"
      << "  Actual:   " << __index << "\n";
    const EventEntry_ADC_SOC_TimedOut& e =
      this->eventHistory_ADC_SOC_TimedOut->at(__index);
    ASSERT_EQ(ticks, e.ticks)
      << "\n"
      << "  File:     " << __callSiteFileName << "\n"
      << "  Line:     " << __callSiteLineNumber << "\n"
      << "  Value:    Value of argument ticks at index "
      << __index
      << " in history of event ADC_SOC_TimedOut\n"
      << "  Expected: " << ticks << "\n"
      << "  Actual:   " << e.ticks << "\n";
  }

  // ----------------------------------------------------------------------
  // Event: ADC_SOC_SetTimeout
  // ----------------------------------------------------------------------

  void ADCGTestBase ::
    assertEvents_ADC_SOC_SetTimeout_size(
        const char *const __callSiteFileName,
        const U32 __callSiteLineNumber,
        const U32 size
    ) const
  {
    ASSERT_EQ(size, this->eventHistory_ADC_SOC_SetTimeout->size())
      << "\n"
      << "  File:     " << __callSiteFileName << "\n"
      << "  Line:     " << __callSiteLineNumber << "\n"
      << "  Value:    Size of history for event ADC_SOC_SetTimeout\n"
      << "  Expected: " << size << "\n"
      << "  Actual:   " << this->eventHistory_ADC_SOC_SetTimeout->size() << "\n";
  }

  void ADCGTestBase ::
    assertEvents_ADC_SOC_SetTimeout(
        const char *const __callSiteFileName,
        const U32 __callSiteLineNumber,
        const U32 __index,
        const U32 timeout
    ) const
  {
    ASSERT_GT(this->eventHistory_ADC_SOC_SetTimeout->size(), __index)
      << "\n"
      << "  File:     " << __callSiteFileName << "\n"
      << "  Line:     " << __callSiteLineNumber << "\n"
      << "  Value:    Index into history of event ADC_SOC_SetTimeout\n"
      << "  Expected: Less than size of history ("
      << this->eventHistory_ADC_SOC_SetTimeout->size() << ")\n"
      << "  Actual:   " << __index << "\n";
    const EventEntry_ADC_SOC_SetTimeout& e =
      this->eventHistory_ADC_SOC_SetTimeout->at(__index);
    ASSERT_EQ(timeout, e.timeout)
      << "\n"
      << "  File:     " << __callSiteFileName << "\n"
      << "  Line:     " << __callSiteLineNumber << "\n"
      << "  Value:    Value of argument timeout at index "
      << __index
      << " in history of event ADC_SOC_SetTimeout\n"
      << "  Expected: " << timeout << "\n"
      << "  Actual:   " << e.timeout << "\n";
  }

  // ----------------------------------------------------------------------
  // From ports
  // ----------------------------------------------------------------------

  void ADCGTestBase ::
    assertFromPortHistory_size(
        const char *const __callSiteFileName,
        const U32 __callSiteLineNumber,
        const U32 size
    ) const
  {
    ASSERT_EQ(size, this->fromPortHistorySize)
      << "\n"
      << "  File:     " << __callSiteFileName << "\n"
      << "  Line:     " << __callSiteLineNumber << "\n"
      << "  Value:    Total size of all from port histories\n"
      << "  Expected: " << size << "\n"
      << "  Actual:   " << this->fromPortHistorySize << "\n";
  }

  // ----------------------------------------------------------------------
  // From port: PingResponse
  // ----------------------------------------------------------------------

  void ADCGTestBase ::
    assert_from_PingResponse_size(
        const char *const __callSiteFileName,
        const U32 __callSiteLineNumber,
        const U32 size
    ) const
  {
    ASSERT_EQ(size, this->fromPortHistory_PingResponse->size())
      << "\n"
      << "  File:     " << __callSiteFileName << "\n"
      << "  Line:     " << __callSiteLineNumber << "\n"
      << "  Value:    Size of history for from_PingResponse\n"
      << "  Expected: " << size << "\n"
      << "  Actual:   " << this->fromPortHistory_PingResponse->size() << "\n";
  }

  // ----------------------------------------------------------------------
  // From port: adcOut
  // ----------------------------------------------------------------------

  void ADCGTestBase ::
    assert_from_adcOut_size(
        const char *const __callSiteFileName,
        const U32 __callSiteLineNumber,
        const U32 size
    ) const
  {
    ASSERT_EQ(size, this->fromPortHistory_adcOut->size())
      << "\n"
      << "  File:     " << __callSiteFileName << "\n"
      << "  Line:     " << __callSiteLineNumber << "\n"
      << "  Value:    Size of history for from_adcOut\n"
      << "  Expected: " << size << "\n"
      << "  Actual:   " << this->fromPortHistory_adcOut->size() << "\n";
  }

} // end namespace Drv
