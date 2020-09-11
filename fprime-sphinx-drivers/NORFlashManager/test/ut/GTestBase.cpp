// ======================================================================
// \title  NORFlashManager/test/ut/GTestBase.cpp
// \author Auto-generated
// \brief  cpp file for NORFlashManager component Google Test harness base class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
// ======================================================================

#include "GTestBase.hpp"

namespace Drv {

  // ----------------------------------------------------------------------
  // Construction and destruction
  // ----------------------------------------------------------------------

  NORFlashManagerGTestBase ::
    NORFlashManagerGTestBase(
#if FW_OBJECT_NAMES == 1
        const char *const compName,
        const U32 maxHistorySize
#else
        const U32 maxHistorySize
#endif
    ) : 
        NORFlashManagerTesterBase (
#if FW_OBJECT_NAMES == 1
            compName,
#endif
            maxHistorySize
        )
  {

  }

  NORFlashManagerGTestBase ::
    ~NORFlashManagerGTestBase(void)
  {

  }

  // ----------------------------------------------------------------------
  // Commands
  // ----------------------------------------------------------------------

  void NORFlashManagerGTestBase ::
    assertCmdResponse_size(
        const char *const __ISF_callSiteFileName,
        const U32 __ISF_callSiteLineNumber,
        const U32 size
    ) const
  {
    ASSERT_EQ((unsigned long) size, this->cmdResponseHistory->size())
      << "\n"
      << "  File:     " << __ISF_callSiteFileName << "\n"
      << "  Line:     " << __ISF_callSiteLineNumber << "\n"
      << "  Value:    Size of command response history\n"
      << "  Expected: " << size << "\n"
      << "  Actual:   " << this->cmdResponseHistory->size() << "\n";
  }

  void NORFlashManagerGTestBase ::
    assertCmdResponse(
        const char *const __ISF_callSiteFileName,
        const U32 __ISF_callSiteLineNumber,
        const U32 index,
        const FwOpcodeType opCode,
        const U32 cmdSeq,
        const Fw::CommandResponse response
    )
    const
  {
    ASSERT_LT(index, this->cmdResponseHistory->size())
      << "\n"
      << "  File:     " << __ISF_callSiteFileName << "\n"
      << "  Line:     " << __ISF_callSiteLineNumber << "\n"
      << "  Value:    Index into command response history\n"
      << "  Expected: Less than size of command response history (" 
      << this->cmdResponseHistory->size() << ")\n"
      << "  Actual:   " << index << "\n";
    const CmdResponse& e = this->cmdResponseHistory->at(index);
    ASSERT_EQ(opCode, e.opCode)
      << "\n"
      << "  File:     " << __ISF_callSiteFileName << "\n"
      << "  Line:     " << __ISF_callSiteLineNumber << "\n"
      << "  Value:    Opcode at index "
      << index
      << " in command response history\n"
      << "  Expected: " << opCode << "\n"
      << "  Actual:   " << e.opCode << "\n";
    ASSERT_EQ(cmdSeq, e.cmdSeq)
      << "\n"
      << "  File:     " << __ISF_callSiteFileName << "\n"
      << "  Line:     " << __ISF_callSiteLineNumber << "\n"
      << "  Value:    Command sequence number at index "
      << index
      << " in command response history\n"
      << "  Expected: " << cmdSeq << "\n"
      << "  Actual:   " << e.cmdSeq << "\n";
    ASSERT_EQ(response, e.response)
      << "\n"
      << "  File:     " << __ISF_callSiteFileName << "\n"
      << "  Line:     " << __ISF_callSiteLineNumber << "\n"
      << "  Value:    Command response at index "
      << index
      << " in command resopnse history\n"
      << "  Expected: " << response << "\n"
      << "  Actual:   " << e.response << "\n";
  }

  // ----------------------------------------------------------------------
  // Events
  // ----------------------------------------------------------------------

  void NORFlashManagerGTestBase ::
    assertEvents_size(
        const char *const __ISF_callSiteFileName,
        const U32 __ISF_callSiteLineNumber,
        const U32 size
    ) const
  {
    ASSERT_EQ(size, this->eventsSize)
      << "\n"
      << "  File:     " << __ISF_callSiteFileName << "\n"
      << "  Line:     " << __ISF_callSiteLineNumber << "\n"
      << "  Value:    Total size of all event histories\n"
      << "  Expected: " << size << "\n"
      << "  Actual:   " << this->eventsSize << "\n";
  }

  // ----------------------------------------------------------------------
  // Event: NOR_ERASE_BUSY
  // ----------------------------------------------------------------------

  void NORFlashManagerGTestBase ::
    assertEvents_NOR_ERASE_BUSY_size(
        const char *const __ISF_callSiteFileName,
        const U32 __ISF_callSiteLineNumber,
        const U32 size
    ) const
  {
    ASSERT_EQ(size, this->eventHistory_NOR_ERASE_BUSY->size())
      << "\n"
      << "  File:     " << __ISF_callSiteFileName << "\n"
      << "  Line:     " << __ISF_callSiteLineNumber << "\n"
      << "  Value:    Size of history for event NOR_ERASE_BUSY\n"
      << "  Expected: " << size << "\n"
      << "  Actual:   " << this->eventHistory_NOR_ERASE_BUSY->size() << "\n";
  }

  void NORFlashManagerGTestBase ::
    assertEvents_NOR_ERASE_BUSY(
        const char *const __ISF_callSiteFileName,
        const U32 __ISF_callSiteLineNumber,
        const U32 index,
        const U32 actual_state,
        const U32 expected_state,
        const U32 error_status
    ) const
  {
    ASSERT_GT(this->eventHistory_NOR_ERASE_BUSY->size(), index)
      << "\n"
      << "  File:     " << __ISF_callSiteFileName << "\n"
      << "  Line:     " << __ISF_callSiteLineNumber << "\n"
      << "  Value:    Index into history of event NOR_ERASE_BUSY\n"
      << "  Expected: Less than size of history (" 
      << this->eventHistory_NOR_ERASE_BUSY->size() << ")\n"
      << "  Actual:   " << index << "\n";
    const EventEntry_NOR_ERASE_BUSY& e =
      this->eventHistory_NOR_ERASE_BUSY->at(index);
    ASSERT_EQ(actual_state, e.actual_state)
      << "\n"
      << "  File:     " << __ISF_callSiteFileName << "\n"
      << "  Line:     " << __ISF_callSiteLineNumber << "\n"
      << "  Value:    Value of argument actual_state at index "
      << index
      << " in history of event NOR_ERASE_BUSY\n"
      << "  Expected: " << actual_state << "\n"
      << "  Actual:   " << e.actual_state << "\n";
    ASSERT_EQ(expected_state, e.expected_state)
      << "\n"
      << "  File:     " << __ISF_callSiteFileName << "\n"
      << "  Line:     " << __ISF_callSiteLineNumber << "\n"
      << "  Value:    Value of argument expected_state at index "
      << index
      << " in history of event NOR_ERASE_BUSY\n"
      << "  Expected: " << expected_state << "\n"
      << "  Actual:   " << e.expected_state << "\n";
    ASSERT_EQ(error_status, e.error_status)
      << "\n"
      << "  File:     " << __ISF_callSiteFileName << "\n"
      << "  Line:     " << __ISF_callSiteLineNumber << "\n"
      << "  Value:    Value of argument error_status at index "
      << index
      << " in history of event NOR_ERASE_BUSY\n"
      << "  Expected: " << error_status << "\n"
      << "  Actual:   " << e.error_status << "\n";
  }

  // ----------------------------------------------------------------------
  // Event: NOR_ERASE_FAIL
  // ----------------------------------------------------------------------

  void NORFlashManagerGTestBase ::
    assertEvents_NOR_ERASE_FAIL_size(
        const char *const __ISF_callSiteFileName,
        const U32 __ISF_callSiteLineNumber,
        const U32 size
    ) const
  {
    ASSERT_EQ(size, this->eventHistory_NOR_ERASE_FAIL->size())
      << "\n"
      << "  File:     " << __ISF_callSiteFileName << "\n"
      << "  Line:     " << __ISF_callSiteLineNumber << "\n"
      << "  Value:    Size of history for event NOR_ERASE_FAIL\n"
      << "  Expected: " << size << "\n"
      << "  Actual:   " << this->eventHistory_NOR_ERASE_FAIL->size() << "\n";
  }

  void NORFlashManagerGTestBase ::
    assertEvents_NOR_ERASE_FAIL(
        const char *const __ISF_callSiteFileName,
        const U32 __ISF_callSiteLineNumber,
        const U32 index,
        const U32 error_status
    ) const
  {
    ASSERT_GT(this->eventHistory_NOR_ERASE_FAIL->size(), index)
      << "\n"
      << "  File:     " << __ISF_callSiteFileName << "\n"
      << "  Line:     " << __ISF_callSiteLineNumber << "\n"
      << "  Value:    Index into history of event NOR_ERASE_FAIL\n"
      << "  Expected: Less than size of history (" 
      << this->eventHistory_NOR_ERASE_FAIL->size() << ")\n"
      << "  Actual:   " << index << "\n";
    const EventEntry_NOR_ERASE_FAIL& e =
      this->eventHistory_NOR_ERASE_FAIL->at(index);
    ASSERT_EQ(error_status, e.error_status)
      << "\n"
      << "  File:     " << __ISF_callSiteFileName << "\n"
      << "  Line:     " << __ISF_callSiteLineNumber << "\n"
      << "  Value:    Value of argument error_status at index "
      << index
      << " in history of event NOR_ERASE_FAIL\n"
      << "  Expected: " << error_status << "\n"
      << "  Actual:   " << e.error_status << "\n";
  }

  // ----------------------------------------------------------------------
  // Event: NOR_ERASING
  // ----------------------------------------------------------------------

  void NORFlashManagerGTestBase ::
    assertEvents_NOR_ERASING_size(
        const char *const __ISF_callSiteFileName,
        const U32 __ISF_callSiteLineNumber,
        const U32 size
    ) const
  {
    ASSERT_EQ(size, this->eventsSize_NOR_ERASING)
      << "\n"
      << "  File:     " << __ISF_callSiteFileName << "\n"
      << "  Line:     " << __ISF_callSiteLineNumber << "\n"
      << "  Value:    Size of history for event NOR_ERASING\n"
      << "  Expected: " << size << "\n"
      << "  Actual:   " << this->eventsSize_NOR_ERASING << "\n";
  }

  // ----------------------------------------------------------------------
  // Event: NOR_ERASE_TIMEOUT
  // ----------------------------------------------------------------------

  void NORFlashManagerGTestBase ::
    assertEvents_NOR_ERASE_TIMEOUT_size(
        const char *const __ISF_callSiteFileName,
        const U32 __ISF_callSiteLineNumber,
        const U32 size
    ) const
  {
    ASSERT_EQ(size, this->eventsSize_NOR_ERASE_TIMEOUT)
      << "\n"
      << "  File:     " << __ISF_callSiteFileName << "\n"
      << "  Line:     " << __ISF_callSiteLineNumber << "\n"
      << "  Value:    Size of history for event NOR_ERASE_TIMEOUT\n"
      << "  Expected: " << size << "\n"
      << "  Actual:   " << this->eventsSize_NOR_ERASE_TIMEOUT << "\n";
  }

  // ----------------------------------------------------------------------
  // Event: NOR_ERASE_DONE
  // ----------------------------------------------------------------------

  void NORFlashManagerGTestBase ::
    assertEvents_NOR_ERASE_DONE_size(
        const char *const __ISF_callSiteFileName,
        const U32 __ISF_callSiteLineNumber,
        const U32 size
    ) const
  {
    ASSERT_EQ(size, this->eventsSize_NOR_ERASE_DONE)
      << "\n"
      << "  File:     " << __ISF_callSiteFileName << "\n"
      << "  Line:     " << __ISF_callSiteLineNumber << "\n"
      << "  Value:    Size of history for event NOR_ERASE_DONE\n"
      << "  Expected: " << size << "\n"
      << "  Actual:   " << this->eventsSize_NOR_ERASE_DONE << "\n";
  }

  // ----------------------------------------------------------------------
  // Event: NOR_RESET_FAIL
  // ----------------------------------------------------------------------

  void NORFlashManagerGTestBase ::
    assertEvents_NOR_RESET_FAIL_size(
        const char *const __ISF_callSiteFileName,
        const U32 __ISF_callSiteLineNumber,
        const U32 size
    ) const
  {
    ASSERT_EQ(size, this->eventHistory_NOR_RESET_FAIL->size())
      << "\n"
      << "  File:     " << __ISF_callSiteFileName << "\n"
      << "  Line:     " << __ISF_callSiteLineNumber << "\n"
      << "  Value:    Size of history for event NOR_RESET_FAIL\n"
      << "  Expected: " << size << "\n"
      << "  Actual:   " << this->eventHistory_NOR_RESET_FAIL->size() << "\n";
  }

  void NORFlashManagerGTestBase ::
    assertEvents_NOR_RESET_FAIL(
        const char *const __ISF_callSiteFileName,
        const U32 __ISF_callSiteLineNumber,
        const U32 index,
        const U32 actual_state,
        const U32 expected_state
    ) const
  {
    ASSERT_GT(this->eventHistory_NOR_RESET_FAIL->size(), index)
      << "\n"
      << "  File:     " << __ISF_callSiteFileName << "\n"
      << "  Line:     " << __ISF_callSiteLineNumber << "\n"
      << "  Value:    Index into history of event NOR_RESET_FAIL\n"
      << "  Expected: Less than size of history (" 
      << this->eventHistory_NOR_RESET_FAIL->size() << ")\n"
      << "  Actual:   " << index << "\n";
    const EventEntry_NOR_RESET_FAIL& e =
      this->eventHistory_NOR_RESET_FAIL->at(index);
    ASSERT_EQ(actual_state, e.actual_state)
      << "\n"
      << "  File:     " << __ISF_callSiteFileName << "\n"
      << "  Line:     " << __ISF_callSiteLineNumber << "\n"
      << "  Value:    Value of argument actual_state at index "
      << index
      << " in history of event NOR_RESET_FAIL\n"
      << "  Expected: " << actual_state << "\n"
      << "  Actual:   " << e.actual_state << "\n";
    ASSERT_EQ(expected_state, e.expected_state)
      << "\n"
      << "  File:     " << __ISF_callSiteFileName << "\n"
      << "  Line:     " << __ISF_callSiteLineNumber << "\n"
      << "  Value:    Value of argument expected_state at index "
      << index
      << " in history of event NOR_RESET_FAIL\n"
      << "  Expected: " << expected_state << "\n"
      << "  Actual:   " << e.expected_state << "\n";
  }

  // ----------------------------------------------------------------------
  // Event: NOR_RESETTING
  // ----------------------------------------------------------------------

  void NORFlashManagerGTestBase ::
    assertEvents_NOR_RESETTING_size(
        const char *const __ISF_callSiteFileName,
        const U32 __ISF_callSiteLineNumber,
        const U32 size
    ) const
  {
    ASSERT_EQ(size, this->eventsSize_NOR_RESETTING)
      << "\n"
      << "  File:     " << __ISF_callSiteFileName << "\n"
      << "  Line:     " << __ISF_callSiteLineNumber << "\n"
      << "  Value:    Size of history for event NOR_RESETTING\n"
      << "  Expected: " << size << "\n"
      << "  Actual:   " << this->eventsSize_NOR_RESETTING << "\n";
  }

  // ----------------------------------------------------------------------
  // Event: NOR_UNLOCK_BYPASS_FAILED
  // ----------------------------------------------------------------------

  void NORFlashManagerGTestBase ::
    assertEvents_NOR_UNLOCK_BYPASS_FAILED_size(
        const char *const __ISF_callSiteFileName,
        const U32 __ISF_callSiteLineNumber,
        const U32 size
    ) const
  {
    ASSERT_EQ(size, this->eventsSize_NOR_UNLOCK_BYPASS_FAILED)
      << "\n"
      << "  File:     " << __ISF_callSiteFileName << "\n"
      << "  Line:     " << __ISF_callSiteLineNumber << "\n"
      << "  Value:    Size of history for event NOR_UNLOCK_BYPASS_FAILED\n"
      << "  Expected: " << size << "\n"
      << "  Actual:   " << this->eventsSize_NOR_UNLOCK_BYPASS_FAILED << "\n";
  }

  // ----------------------------------------------------------------------
  // Event: NOR_UNLOCK_BYPASS_PROGRAM_FAILED
  // ----------------------------------------------------------------------

  void NORFlashManagerGTestBase ::
    assertEvents_NOR_UNLOCK_BYPASS_PROGRAM_FAILED_size(
        const char *const __ISF_callSiteFileName,
        const U32 __ISF_callSiteLineNumber,
        const U32 size
    ) const
  {
    ASSERT_EQ(size, this->eventsSize_NOR_UNLOCK_BYPASS_PROGRAM_FAILED)
      << "\n"
      << "  File:     " << __ISF_callSiteFileName << "\n"
      << "  Line:     " << __ISF_callSiteLineNumber << "\n"
      << "  Value:    Size of history for event NOR_UNLOCK_BYPASS_PROGRAM_FAILED\n"
      << "  Expected: " << size << "\n"
      << "  Actual:   " << this->eventsSize_NOR_UNLOCK_BYPASS_PROGRAM_FAILED << "\n";
  }

  // ----------------------------------------------------------------------
  // Event: NOR_UNLOCK_BYPASS_RESET_FAILED
  // ----------------------------------------------------------------------

  void NORFlashManagerGTestBase ::
    assertEvents_NOR_UNLOCK_BYPASS_RESET_FAILED_size(
        const char *const __ISF_callSiteFileName,
        const U32 __ISF_callSiteLineNumber,
        const U32 size
    ) const
  {
    ASSERT_EQ(size, this->eventsSize_NOR_UNLOCK_BYPASS_RESET_FAILED)
      << "\n"
      << "  File:     " << __ISF_callSiteFileName << "\n"
      << "  Line:     " << __ISF_callSiteLineNumber << "\n"
      << "  Value:    Size of history for event NOR_UNLOCK_BYPASS_RESET_FAILED\n"
      << "  Expected: " << size << "\n"
      << "  Actual:   " << this->eventsSize_NOR_UNLOCK_BYPASS_RESET_FAILED << "\n";
  }

  // ----------------------------------------------------------------------
  // Event: NOR_FAILED_TO_VERIFY_DATA
  // ----------------------------------------------------------------------

  void NORFlashManagerGTestBase ::
    assertEvents_NOR_FAILED_TO_VERIFY_DATA_size(
        const char *const __ISF_callSiteFileName,
        const U32 __ISF_callSiteLineNumber,
        const U32 size
    ) const
  {
    ASSERT_EQ(size, this->eventHistory_NOR_FAILED_TO_VERIFY_DATA->size())
      << "\n"
      << "  File:     " << __ISF_callSiteFileName << "\n"
      << "  Line:     " << __ISF_callSiteLineNumber << "\n"
      << "  Value:    Size of history for event NOR_FAILED_TO_VERIFY_DATA\n"
      << "  Expected: " << size << "\n"
      << "  Actual:   " << this->eventHistory_NOR_FAILED_TO_VERIFY_DATA->size() << "\n";
  }

  void NORFlashManagerGTestBase ::
    assertEvents_NOR_FAILED_TO_VERIFY_DATA(
        const char *const __ISF_callSiteFileName,
        const U32 __ISF_callSiteLineNumber,
        const U32 index,
        const U32 dest_addr,
        const U8 source
    ) const
  {
    ASSERT_GT(this->eventHistory_NOR_FAILED_TO_VERIFY_DATA->size(), index)
      << "\n"
      << "  File:     " << __ISF_callSiteFileName << "\n"
      << "  Line:     " << __ISF_callSiteLineNumber << "\n"
      << "  Value:    Index into history of event NOR_FAILED_TO_VERIFY_DATA\n"
      << "  Expected: Less than size of history (" 
      << this->eventHistory_NOR_FAILED_TO_VERIFY_DATA->size() << ")\n"
      << "  Actual:   " << index << "\n";
    const EventEntry_NOR_FAILED_TO_VERIFY_DATA& e =
      this->eventHistory_NOR_FAILED_TO_VERIFY_DATA->at(index);
    ASSERT_EQ(dest_addr, e.dest_addr)
      << "\n"
      << "  File:     " << __ISF_callSiteFileName << "\n"
      << "  Line:     " << __ISF_callSiteLineNumber << "\n"
      << "  Value:    Value of argument dest_addr at index "
      << index
      << " in history of event NOR_FAILED_TO_VERIFY_DATA\n"
      << "  Expected: " << dest_addr << "\n"
      << "  Actual:   " << e.dest_addr << "\n";
    ASSERT_EQ(source, e.source)
      << "\n"
      << "  File:     " << __ISF_callSiteFileName << "\n"
      << "  Line:     " << __ISF_callSiteLineNumber << "\n"
      << "  Value:    Value of argument source at index "
      << index
      << " in history of event NOR_FAILED_TO_VERIFY_DATA\n"
      << "  Expected: " << source << "\n"
      << "  Actual:   " << e.source << "\n";
  }

  // ----------------------------------------------------------------------
  // Event: NOR_UNLOCK_BYPASS_RESET_DURING_ERASE
  // ----------------------------------------------------------------------

  void NORFlashManagerGTestBase ::
    assertEvents_NOR_UNLOCK_BYPASS_RESET_DURING_ERASE_size(
        const char *const __ISF_callSiteFileName,
        const U32 __ISF_callSiteLineNumber,
        const U32 size
    ) const
  {
    ASSERT_EQ(size, this->eventsSize_NOR_UNLOCK_BYPASS_RESET_DURING_ERASE)
      << "\n"
      << "  File:     " << __ISF_callSiteFileName << "\n"
      << "  Line:     " << __ISF_callSiteLineNumber << "\n"
      << "  Value:    Size of history for event NOR_UNLOCK_BYPASS_RESET_DURING_ERASE\n"
      << "  Expected: " << size << "\n"
      << "  Actual:   " << this->eventsSize_NOR_UNLOCK_BYPASS_RESET_DURING_ERASE << "\n";
  }

  // ----------------------------------------------------------------------
  // Event: NOR_FAILED_TO_RESET
  // ----------------------------------------------------------------------

  void NORFlashManagerGTestBase ::
    assertEvents_NOR_FAILED_TO_RESET_size(
        const char *const __ISF_callSiteFileName,
        const U32 __ISF_callSiteLineNumber,
        const U32 size
    ) const
  {
    ASSERT_EQ(size, this->eventsSize_NOR_FAILED_TO_RESET)
      << "\n"
      << "  File:     " << __ISF_callSiteFileName << "\n"
      << "  Line:     " << __ISF_callSiteLineNumber << "\n"
      << "  Value:    Size of history for event NOR_FAILED_TO_RESET\n"
      << "  Expected: " << size << "\n"
      << "  Actual:   " << this->eventsSize_NOR_FAILED_TO_RESET << "\n";
  }

  // ----------------------------------------------------------------------
  // Event: NOR_WRITE_TIMEOUT
  // ----------------------------------------------------------------------

  void NORFlashManagerGTestBase ::
    assertEvents_NOR_WRITE_TIMEOUT_size(
        const char *const __ISF_callSiteFileName,
        const U32 __ISF_callSiteLineNumber,
        const U32 size
    ) const
  {
    ASSERT_EQ(size, this->eventsSize_NOR_WRITE_TIMEOUT)
      << "\n"
      << "  File:     " << __ISF_callSiteFileName << "\n"
      << "  Line:     " << __ISF_callSiteLineNumber << "\n"
      << "  Value:    Size of history for event NOR_WRITE_TIMEOUT\n"
      << "  Expected: " << size << "\n"
      << "  Actual:   " << this->eventsSize_NOR_WRITE_TIMEOUT << "\n";
  }

  // ----------------------------------------------------------------------
  // Event: NOR_FAILED_TO_VERIFY_CHECKSUM
  // ----------------------------------------------------------------------

  void NORFlashManagerGTestBase ::
    assertEvents_NOR_FAILED_TO_VERIFY_CHECKSUM_size(
        const char *const __ISF_callSiteFileName,
        const U32 __ISF_callSiteLineNumber,
        const U32 size
    ) const
  {
    ASSERT_EQ(size, this->eventsSize_NOR_FAILED_TO_VERIFY_CHECKSUM)
      << "\n"
      << "  File:     " << __ISF_callSiteFileName << "\n"
      << "  Line:     " << __ISF_callSiteLineNumber << "\n"
      << "  Value:    Size of history for event NOR_FAILED_TO_VERIFY_CHECKSUM\n"
      << "  Expected: " << size << "\n"
      << "  Actual:   " << this->eventsSize_NOR_FAILED_TO_VERIFY_CHECKSUM << "\n";
  }

  // ----------------------------------------------------------------------
  // Event: NOR_CHECKSUM_VERIFY_DONE
  // ----------------------------------------------------------------------

  void NORFlashManagerGTestBase ::
    assertEvents_NOR_CHECKSUM_VERIFY_DONE_size(
        const char *const __ISF_callSiteFileName,
        const U32 __ISF_callSiteLineNumber,
        const U32 size
    ) const
  {
    ASSERT_EQ(size, this->eventsSize_NOR_CHECKSUM_VERIFY_DONE)
      << "\n"
      << "  File:     " << __ISF_callSiteFileName << "\n"
      << "  Line:     " << __ISF_callSiteLineNumber << "\n"
      << "  Value:    Size of history for event NOR_CHECKSUM_VERIFY_DONE\n"
      << "  Expected: " << size << "\n"
      << "  Actual:   " << this->eventsSize_NOR_CHECKSUM_VERIFY_DONE << "\n";
  }

  // ----------------------------------------------------------------------
  // Event: NOR_VERIFY_BUSY
  // ----------------------------------------------------------------------

  void NORFlashManagerGTestBase ::
    assertEvents_NOR_VERIFY_BUSY_size(
        const char *const __ISF_callSiteFileName,
        const U32 __ISF_callSiteLineNumber,
        const U32 size
    ) const
  {
    ASSERT_EQ(size, this->eventHistory_NOR_VERIFY_BUSY->size())
      << "\n"
      << "  File:     " << __ISF_callSiteFileName << "\n"
      << "  Line:     " << __ISF_callSiteLineNumber << "\n"
      << "  Value:    Size of history for event NOR_VERIFY_BUSY\n"
      << "  Expected: " << size << "\n"
      << "  Actual:   " << this->eventHistory_NOR_VERIFY_BUSY->size() << "\n";
  }

  void NORFlashManagerGTestBase ::
    assertEvents_NOR_VERIFY_BUSY(
        const char *const __ISF_callSiteFileName,
        const U32 __ISF_callSiteLineNumber,
        const U32 index,
        const U32 actual_state,
        const U32 expected_state
    ) const
  {
    ASSERT_GT(this->eventHistory_NOR_VERIFY_BUSY->size(), index)
      << "\n"
      << "  File:     " << __ISF_callSiteFileName << "\n"
      << "  Line:     " << __ISF_callSiteLineNumber << "\n"
      << "  Value:    Index into history of event NOR_VERIFY_BUSY\n"
      << "  Expected: Less than size of history (" 
      << this->eventHistory_NOR_VERIFY_BUSY->size() << ")\n"
      << "  Actual:   " << index << "\n";
    const EventEntry_NOR_VERIFY_BUSY& e =
      this->eventHistory_NOR_VERIFY_BUSY->at(index);
    ASSERT_EQ(actual_state, e.actual_state)
      << "\n"
      << "  File:     " << __ISF_callSiteFileName << "\n"
      << "  Line:     " << __ISF_callSiteLineNumber << "\n"
      << "  Value:    Value of argument actual_state at index "
      << index
      << " in history of event NOR_VERIFY_BUSY\n"
      << "  Expected: " << actual_state << "\n"
      << "  Actual:   " << e.actual_state << "\n";
    ASSERT_EQ(expected_state, e.expected_state)
      << "\n"
      << "  File:     " << __ISF_callSiteFileName << "\n"
      << "  Line:     " << __ISF_callSiteLineNumber << "\n"
      << "  Value:    Value of argument expected_state at index "
      << index
      << " in history of event NOR_VERIFY_BUSY\n"
      << "  Expected: " << expected_state << "\n"
      << "  Actual:   " << e.expected_state << "\n";
  }

  // ----------------------------------------------------------------------
  // Event: NOR_FAILED_TO_READ_DATA
  // ----------------------------------------------------------------------

  void NORFlashManagerGTestBase ::
    assertEvents_NOR_FAILED_TO_READ_DATA_size(
        const char *const __ISF_callSiteFileName,
        const U32 __ISF_callSiteLineNumber,
        const U32 size
    ) const
  {
    ASSERT_EQ(size, this->eventHistory_NOR_FAILED_TO_READ_DATA->size())
      << "\n"
      << "  File:     " << __ISF_callSiteFileName << "\n"
      << "  Line:     " << __ISF_callSiteLineNumber << "\n"
      << "  Value:    Size of history for event NOR_FAILED_TO_READ_DATA\n"
      << "  Expected: " << size << "\n"
      << "  Actual:   " << this->eventHistory_NOR_FAILED_TO_READ_DATA->size() << "\n";
  }

  void NORFlashManagerGTestBase ::
    assertEvents_NOR_FAILED_TO_READ_DATA(
        const char *const __ISF_callSiteFileName,
        const U32 __ISF_callSiteLineNumber,
        const U32 index,
        const U32 nor_addr,
        const U32 dest
    ) const
  {
    ASSERT_GT(this->eventHistory_NOR_FAILED_TO_READ_DATA->size(), index)
      << "\n"
      << "  File:     " << __ISF_callSiteFileName << "\n"
      << "  Line:     " << __ISF_callSiteLineNumber << "\n"
      << "  Value:    Index into history of event NOR_FAILED_TO_READ_DATA\n"
      << "  Expected: Less than size of history (" 
      << this->eventHistory_NOR_FAILED_TO_READ_DATA->size() << ")\n"
      << "  Actual:   " << index << "\n";
    const EventEntry_NOR_FAILED_TO_READ_DATA& e =
      this->eventHistory_NOR_FAILED_TO_READ_DATA->at(index);
    ASSERT_EQ(nor_addr, e.nor_addr)
      << "\n"
      << "  File:     " << __ISF_callSiteFileName << "\n"
      << "  Line:     " << __ISF_callSiteLineNumber << "\n"
      << "  Value:    Value of argument nor_addr at index "
      << index
      << " in history of event NOR_FAILED_TO_READ_DATA\n"
      << "  Expected: " << nor_addr << "\n"
      << "  Actual:   " << e.nor_addr << "\n";
    ASSERT_EQ(dest, e.dest)
      << "\n"
      << "  File:     " << __ISF_callSiteFileName << "\n"
      << "  Line:     " << __ISF_callSiteLineNumber << "\n"
      << "  Value:    Value of argument dest at index "
      << index
      << " in history of event NOR_FAILED_TO_READ_DATA\n"
      << "  Expected: " << dest << "\n"
      << "  Actual:   " << e.dest << "\n";
  }

  // ----------------------------------------------------------------------
  // Event: NOR_READ_TIMEOUT
  // ----------------------------------------------------------------------

  void NORFlashManagerGTestBase ::
    assertEvents_NOR_READ_TIMEOUT_size(
        const char *const __ISF_callSiteFileName,
        const U32 __ISF_callSiteLineNumber,
        const U32 size
    ) const
  {
    ASSERT_EQ(size, this->eventsSize_NOR_READ_TIMEOUT)
      << "\n"
      << "  File:     " << __ISF_callSiteFileName << "\n"
      << "  Line:     " << __ISF_callSiteLineNumber << "\n"
      << "  Value:    Size of history for event NOR_READ_TIMEOUT\n"
      << "  Expected: " << size << "\n"
      << "  Actual:   " << this->eventsSize_NOR_READ_TIMEOUT << "\n";
  }

  // ----------------------------------------------------------------------
  // Event: NOR_ALREADY_ERASING
  // ----------------------------------------------------------------------

  void NORFlashManagerGTestBase ::
    assertEvents_NOR_ALREADY_ERASING_size(
        const char *const __ISF_callSiteFileName,
        const U32 __ISF_callSiteLineNumber,
        const U32 size
    ) const
  {
    ASSERT_EQ(size, this->eventsSize_NOR_ALREADY_ERASING)
      << "\n"
      << "  File:     " << __ISF_callSiteFileName << "\n"
      << "  Line:     " << __ISF_callSiteLineNumber << "\n"
      << "  Value:    Size of history for event NOR_ALREADY_ERASING\n"
      << "  Expected: " << size << "\n"
      << "  Actual:   " << this->eventsSize_NOR_ALREADY_ERASING << "\n";
  }

  // ----------------------------------------------------------------------
  // From ports
  // ----------------------------------------------------------------------

  void NORFlashManagerGTestBase ::
    assertFromPortHistory_size(
        const char *const __ISF_callSiteFileName,
        const U32 __ISF_callSiteLineNumber,
        const U32 size
    ) const
  {
    ASSERT_EQ(size, this->fromPortHistorySize)
      << "\n"
      << "  File:     " << __ISF_callSiteFileName << "\n"
      << "  Line:     " << __ISF_callSiteLineNumber << "\n"
      << "  Value:    Total size of all from port histories\n"
      << "  Expected: " << size << "\n"
      << "  Actual:   " << this->fromPortHistorySize << "\n";
  }

  // ----------------------------------------------------------------------
  // From port: PingResponse
  // ----------------------------------------------------------------------

  void NORFlashManagerGTestBase ::
    assert_from_PingResponse_size(
        const char *const __ISF_callSiteFileName,
        const U32 __ISF_callSiteLineNumber,
        const U32 size
    ) const
  {
    ASSERT_EQ(size, this->fromPortHistory_PingResponse->size())
      << "\n"
      << "  File:     " << __ISF_callSiteFileName << "\n"
      << "  Line:     " << __ISF_callSiteLineNumber << "\n"
      << "  Value:    Size of history for from_PingResponse\n"
      << "  Expected: " << size << "\n"
      << "  Actual:   " << this->fromPortHistory_PingResponse->size() << "\n";
  }

  // ----------------------------------------------------------------------
  // From port: verification_done
  // ----------------------------------------------------------------------

  void NORFlashManagerGTestBase ::
    assert_from_verification_done_size(
        const char *const __ISF_callSiteFileName,
        const U32 __ISF_callSiteLineNumber,
        const U32 size
    ) const
  {
    ASSERT_EQ(size, this->fromPortHistory_verification_done->size())
      << "\n"
      << "  File:     " << __ISF_callSiteFileName << "\n"
      << "  Line:     " << __ISF_callSiteLineNumber << "\n"
      << "  Value:    Size of history for from_verification_done\n"
      << "  Expected: " << size << "\n"
      << "  Actual:   " << this->fromPortHistory_verification_done->size() << "\n";
  }

  // ----------------------------------------------------------------------
  // From port: erase_done
  // ----------------------------------------------------------------------

  void NORFlashManagerGTestBase ::
    assert_from_erase_done_size(
        const char *const __ISF_callSiteFileName,
        const U32 __ISF_callSiteLineNumber,
        const U32 size
    ) const
  {
    ASSERT_EQ(size, this->fromPortHistory_erase_done->size())
      << "\n"
      << "  File:     " << __ISF_callSiteFileName << "\n"
      << "  Line:     " << __ISF_callSiteLineNumber << "\n"
      << "  Value:    Size of history for from_erase_done\n"
      << "  Expected: " << size << "\n"
      << "  Actual:   " << this->fromPortHistory_erase_done->size() << "\n";
  }

  // ----------------------------------------------------------------------
  // From port: read_done
  // ----------------------------------------------------------------------

  void NORFlashManagerGTestBase ::
    assert_from_read_done_size(
        const char *const __ISF_callSiteFileName,
        const U32 __ISF_callSiteLineNumber,
        const U32 size
    ) const
  {
    ASSERT_EQ(size, this->fromPortHistory_read_done->size())
      << "\n"
      << "  File:     " << __ISF_callSiteFileName << "\n"
      << "  Line:     " << __ISF_callSiteLineNumber << "\n"
      << "  Value:    Size of history for from_read_done\n"
      << "  Expected: " << size << "\n"
      << "  Actual:   " << this->fromPortHistory_read_done->size() << "\n";
  }

  // ----------------------------------------------------------------------
  // From port: worker_verify
  // ----------------------------------------------------------------------

  void NORFlashManagerGTestBase ::
    assert_from_worker_verify_size(
        const char *const __ISF_callSiteFileName,
        const U32 __ISF_callSiteLineNumber,
        const U32 size
    ) const
  {
    ASSERT_EQ(size, this->fromPortHistory_worker_verify->size())
      << "\n"
      << "  File:     " << __ISF_callSiteFileName << "\n"
      << "  Line:     " << __ISF_callSiteLineNumber << "\n"
      << "  Value:    Size of history for from_worker_verify\n"
      << "  Expected: " << size << "\n"
      << "  Actual:   " << this->fromPortHistory_worker_verify->size() << "\n";
  }

  // ----------------------------------------------------------------------
  // From port: worker_write
  // ----------------------------------------------------------------------

  void NORFlashManagerGTestBase ::
    assert_from_worker_write_size(
        const char *const __ISF_callSiteFileName,
        const U32 __ISF_callSiteLineNumber,
        const U32 size
    ) const
  {
    ASSERT_EQ(size, this->fromPortHistory_worker_write->size())
      << "\n"
      << "  File:     " << __ISF_callSiteFileName << "\n"
      << "  Line:     " << __ISF_callSiteLineNumber << "\n"
      << "  Value:    Size of history for from_worker_write\n"
      << "  Expected: " << size << "\n"
      << "  Actual:   " << this->fromPortHistory_worker_write->size() << "\n";
  }

  // ----------------------------------------------------------------------
  // From port: write_done
  // ----------------------------------------------------------------------

  void NORFlashManagerGTestBase ::
    assert_from_write_done_size(
        const char *const __ISF_callSiteFileName,
        const U32 __ISF_callSiteLineNumber,
        const U32 size
    ) const
  {
    ASSERT_EQ(size, this->fromPortHistory_write_done->size())
      << "\n"
      << "  File:     " << __ISF_callSiteFileName << "\n"
      << "  Line:     " << __ISF_callSiteLineNumber << "\n"
      << "  Value:    Size of history for from_write_done\n"
      << "  Expected: " << size << "\n"
      << "  Actual:   " << this->fromPortHistory_write_done->size() << "\n";
  }

  // ----------------------------------------------------------------------
  // From port: worker_erase
  // ----------------------------------------------------------------------

  void NORFlashManagerGTestBase ::
    assert_from_worker_erase_size(
        const char *const __ISF_callSiteFileName,
        const U32 __ISF_callSiteLineNumber,
        const U32 size
    ) const
  {
    ASSERT_EQ(size, this->fromPortHistory_worker_erase->size())
      << "\n"
      << "  File:     " << __ISF_callSiteFileName << "\n"
      << "  Line:     " << __ISF_callSiteLineNumber << "\n"
      << "  Value:    Size of history for from_worker_erase\n"
      << "  Expected: " << size << "\n"
      << "  Actual:   " << this->fromPortHistory_worker_erase->size() << "\n";
  }

  // ----------------------------------------------------------------------
  // From port: worker_cancel
  // ----------------------------------------------------------------------

  void NORFlashManagerGTestBase ::
    assert_from_worker_cancel_size(
        const char *const __ISF_callSiteFileName,
        const U32 __ISF_callSiteLineNumber,
        const U32 size
    ) const
  {
    ASSERT_EQ(size, this->fromPortHistorySize_worker_cancel)
      << "\n"
      << "  File:     " << __ISF_callSiteFileName << "\n"
      << "  Line:     " << __ISF_callSiteLineNumber << "\n"
      << "  Value:    Size of history for from_worker_cancel\n"
      << "  Expected: " << size << "\n"
      << "  Actual:   " << this->fromPortHistorySize_worker_cancel << "\n";
  }

  // ----------------------------------------------------------------------
  // From port: worker_reset
  // ----------------------------------------------------------------------

  void NORFlashManagerGTestBase ::
    assert_from_worker_reset_size(
        const char *const __ISF_callSiteFileName,
        const U32 __ISF_callSiteLineNumber,
        const U32 size
    ) const
  {
    ASSERT_EQ(size, this->fromPortHistory_worker_reset->size())
      << "\n"
      << "  File:     " << __ISF_callSiteFileName << "\n"
      << "  Line:     " << __ISF_callSiteLineNumber << "\n"
      << "  Value:    Size of history for from_worker_reset\n"
      << "  Expected: " << size << "\n"
      << "  Actual:   " << this->fromPortHistory_worker_reset->size() << "\n";
  }

  // ----------------------------------------------------------------------
  // From port: worker_read
  // ----------------------------------------------------------------------

  void NORFlashManagerGTestBase ::
    assert_from_worker_read_size(
        const char *const __ISF_callSiteFileName,
        const U32 __ISF_callSiteLineNumber,
        const U32 size
    ) const
  {
    ASSERT_EQ(size, this->fromPortHistory_worker_read->size())
      << "\n"
      << "  File:     " << __ISF_callSiteFileName << "\n"
      << "  Line:     " << __ISF_callSiteLineNumber << "\n"
      << "  Value:    Size of history for from_worker_read\n"
      << "  Expected: " << size << "\n"
      << "  Actual:   " << this->fromPortHistory_worker_read->size() << "\n";
  }

} // end namespace Drv
