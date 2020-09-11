// ======================================================================
// \title  SPWManager/test/ut/GTestBase.cpp
// \author Auto-generated
// \brief  cpp file for SPWManager component Google Test harness base class
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

  SPWManagerGTestBase ::
    SPWManagerGTestBase(
#if FW_OBJECT_NAMES == 1
        const char *const compName,
        const U32 maxHistorySize
#else
        const U32 maxHistorySize
#endif
    ) : 
        SPWManagerTesterBase (
#if FW_OBJECT_NAMES == 1
            compName,
#endif
            maxHistorySize
        )
  {

  }

  SPWManagerGTestBase ::
    ~SPWManagerGTestBase(void)
  {

  }

  // ----------------------------------------------------------------------
  // Commands
  // ----------------------------------------------------------------------

  void SPWManagerGTestBase ::
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

  void SPWManagerGTestBase ::
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

  void SPWManagerGTestBase ::
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
  // Event: SPWManager_SpaceWireInitializationError
  // ----------------------------------------------------------------------

  void SPWManagerGTestBase ::
    assertEvents_SPWManager_SpaceWireInitializationError_size(
        const char *const __ISF_callSiteFileName,
        const U32 __ISF_callSiteLineNumber,
        const U32 size
    ) const
  {
    ASSERT_EQ(size, this->eventHistory_SPWManager_SpaceWireInitializationError->size())
      << "\n"
      << "  File:     " << __ISF_callSiteFileName << "\n"
      << "  Line:     " << __ISF_callSiteLineNumber << "\n"
      << "  Value:    Size of history for event SPWManager_SpaceWireInitializationError\n"
      << "  Expected: " << size << "\n"
      << "  Actual:   " << this->eventHistory_SPWManager_SpaceWireInitializationError->size() << "\n";
  }

  void SPWManagerGTestBase ::
    assertEvents_SPWManager_SpaceWireInitializationError(
        const char *const __ISF_callSiteFileName,
        const U32 __ISF_callSiteLineNumber,
        const U32 index,
        const I32 status
    ) const
  {
    ASSERT_GT(this->eventHistory_SPWManager_SpaceWireInitializationError->size(), index)
      << "\n"
      << "  File:     " << __ISF_callSiteFileName << "\n"
      << "  Line:     " << __ISF_callSiteLineNumber << "\n"
      << "  Value:    Index into history of event SPWManager_SpaceWireInitializationError\n"
      << "  Expected: Less than size of history (" 
      << this->eventHistory_SPWManager_SpaceWireInitializationError->size() << ")\n"
      << "  Actual:   " << index << "\n";
    const EventEntry_SPWManager_SpaceWireInitializationError& e =
      this->eventHistory_SPWManager_SpaceWireInitializationError->at(index);
    ASSERT_EQ(status, e.status)
      << "\n"
      << "  File:     " << __ISF_callSiteFileName << "\n"
      << "  Line:     " << __ISF_callSiteLineNumber << "\n"
      << "  Value:    Value of argument status at index "
      << index
      << " in history of event SPWManager_SpaceWireInitializationError\n"
      << "  Expected: " << status << "\n"
      << "  Actual:   " << e.status << "\n";
  }

  // ----------------------------------------------------------------------
  // Event: SPWManager_SpaceWireLinkDisconnected
  // ----------------------------------------------------------------------

  void SPWManagerGTestBase ::
    assertEvents_SPWManager_SpaceWireLinkDisconnected_size(
        const char *const __ISF_callSiteFileName,
        const U32 __ISF_callSiteLineNumber,
        const U32 size
    ) const
  {
    ASSERT_EQ(size, this->eventsSize_SPWManager_SpaceWireLinkDisconnected)
      << "\n"
      << "  File:     " << __ISF_callSiteFileName << "\n"
      << "  Line:     " << __ISF_callSiteLineNumber << "\n"
      << "  Value:    Size of history for event SPWManager_SpaceWireLinkDisconnected\n"
      << "  Expected: " << size << "\n"
      << "  Actual:   " << this->eventsSize_SPWManager_SpaceWireLinkDisconnected << "\n";
  }

  // ----------------------------------------------------------------------
  // Event: SPWManager_SpaceWireError
  // ----------------------------------------------------------------------

  void SPWManagerGTestBase ::
    assertEvents_SPWManager_SpaceWireError_size(
        const char *const __ISF_callSiteFileName,
        const U32 __ISF_callSiteLineNumber,
        const U32 size
    ) const
  {
    ASSERT_EQ(size, this->eventHistory_SPWManager_SpaceWireError->size())
      << "\n"
      << "  File:     " << __ISF_callSiteFileName << "\n"
      << "  Line:     " << __ISF_callSiteLineNumber << "\n"
      << "  Value:    Size of history for event SPWManager_SpaceWireError\n"
      << "  Expected: " << size << "\n"
      << "  Actual:   " << this->eventHistory_SPWManager_SpaceWireError->size() << "\n";
  }

  void SPWManagerGTestBase ::
    assertEvents_SPWManager_SpaceWireError(
        const char *const __ISF_callSiteFileName,
        const U32 __ISF_callSiteLineNumber,
        const U32 index,
        SPWManagerComponentBase::SpaceWireError_status status,
        const I32 statusCode
    ) const
  {
    ASSERT_GT(this->eventHistory_SPWManager_SpaceWireError->size(), index)
      << "\n"
      << "  File:     " << __ISF_callSiteFileName << "\n"
      << "  Line:     " << __ISF_callSiteLineNumber << "\n"
      << "  Value:    Index into history of event SPWManager_SpaceWireError\n"
      << "  Expected: Less than size of history (" 
      << this->eventHistory_SPWManager_SpaceWireError->size() << ")\n"
      << "  Actual:   " << index << "\n";
    const EventEntry_SPWManager_SpaceWireError& e =
      this->eventHistory_SPWManager_SpaceWireError->at(index);
    ASSERT_EQ(status, e.status)
      << "\n"
      << "  File:     " << __ISF_callSiteFileName << "\n"
      << "  Line:     " << __ISF_callSiteLineNumber << "\n"
      << "  Value:    Value of argument status at index "
      << index
      << " in history of event SPWManager_SpaceWireError\n"
      << "  Expected: " << status << "\n"
      << "  Actual:   " << e.status << "\n";
    ASSERT_EQ(statusCode, e.statusCode)
      << "\n"
      << "  File:     " << __ISF_callSiteFileName << "\n"
      << "  Line:     " << __ISF_callSiteLineNumber << "\n"
      << "  Value:    Value of argument statusCode at index "
      << index
      << " in history of event SPWManager_SpaceWireError\n"
      << "  Expected: " << statusCode << "\n"
      << "  Actual:   " << e.statusCode << "\n";
  }

  // ----------------------------------------------------------------------
  // Event: SPWManager_SpaceWireTransactionTimeout
  // ----------------------------------------------------------------------

  void SPWManagerGTestBase ::
    assertEvents_SPWManager_SpaceWireTransactionTimeout_size(
        const char *const __ISF_callSiteFileName,
        const U32 __ISF_callSiteLineNumber,
        const U32 size
    ) const
  {
    ASSERT_EQ(size, this->eventHistory_SPWManager_SpaceWireTransactionTimeout->size())
      << "\n"
      << "  File:     " << __ISF_callSiteFileName << "\n"
      << "  Line:     " << __ISF_callSiteLineNumber << "\n"
      << "  Value:    Size of history for event SPWManager_SpaceWireTransactionTimeout\n"
      << "  Expected: " << size << "\n"
      << "  Actual:   " << this->eventHistory_SPWManager_SpaceWireTransactionTimeout->size() << "\n";
  }

  void SPWManagerGTestBase ::
    assertEvents_SPWManager_SpaceWireTransactionTimeout(
        const char *const __ISF_callSiteFileName,
        const U32 __ISF_callSiteLineNumber,
        const U32 index,
        const U32 timeout,
        SPWManagerComponentBase::SpaceWireTransactionTimeout_command command,
        const U32 address,
        SPWManagerComponentBase::SpaceWireTransactionTimeout_status status
    ) const
  {
    ASSERT_GT(this->eventHistory_SPWManager_SpaceWireTransactionTimeout->size(), index)
      << "\n"
      << "  File:     " << __ISF_callSiteFileName << "\n"
      << "  Line:     " << __ISF_callSiteLineNumber << "\n"
      << "  Value:    Index into history of event SPWManager_SpaceWireTransactionTimeout\n"
      << "  Expected: Less than size of history (" 
      << this->eventHistory_SPWManager_SpaceWireTransactionTimeout->size() << ")\n"
      << "  Actual:   " << index << "\n";
    const EventEntry_SPWManager_SpaceWireTransactionTimeout& e =
      this->eventHistory_SPWManager_SpaceWireTransactionTimeout->at(index);
    ASSERT_EQ(timeout, e.timeout)
      << "\n"
      << "  File:     " << __ISF_callSiteFileName << "\n"
      << "  Line:     " << __ISF_callSiteLineNumber << "\n"
      << "  Value:    Value of argument timeout at index "
      << index
      << " in history of event SPWManager_SpaceWireTransactionTimeout\n"
      << "  Expected: " << timeout << "\n"
      << "  Actual:   " << e.timeout << "\n";
    ASSERT_EQ(command, e.command)
      << "\n"
      << "  File:     " << __ISF_callSiteFileName << "\n"
      << "  Line:     " << __ISF_callSiteLineNumber << "\n"
      << "  Value:    Value of argument command at index "
      << index
      << " in history of event SPWManager_SpaceWireTransactionTimeout\n"
      << "  Expected: " << command << "\n"
      << "  Actual:   " << e.command << "\n";
    ASSERT_EQ(address, e.address)
      << "\n"
      << "  File:     " << __ISF_callSiteFileName << "\n"
      << "  Line:     " << __ISF_callSiteLineNumber << "\n"
      << "  Value:    Value of argument address at index "
      << index
      << " in history of event SPWManager_SpaceWireTransactionTimeout\n"
      << "  Expected: " << address << "\n"
      << "  Actual:   " << e.address << "\n";
    ASSERT_EQ(status, e.status)
      << "\n"
      << "  File:     " << __ISF_callSiteFileName << "\n"
      << "  Line:     " << __ISF_callSiteLineNumber << "\n"
      << "  Value:    Value of argument status at index "
      << index
      << " in history of event SPWManager_SpaceWireTransactionTimeout\n"
      << "  Expected: " << status << "\n"
      << "  Actual:   " << e.status << "\n";
  }

  // ----------------------------------------------------------------------
  // Event: SPWManager_RMAPWriteResult
  // ----------------------------------------------------------------------

  void SPWManagerGTestBase ::
    assertEvents_SPWManager_RMAPWriteResult_size(
        const char *const __ISF_callSiteFileName,
        const U32 __ISF_callSiteLineNumber,
        const U32 size
    ) const
  {
    ASSERT_EQ(size, this->eventHistory_SPWManager_RMAPWriteResult->size())
      << "\n"
      << "  File:     " << __ISF_callSiteFileName << "\n"
      << "  Line:     " << __ISF_callSiteLineNumber << "\n"
      << "  Value:    Size of history for event SPWManager_RMAPWriteResult\n"
      << "  Expected: " << size << "\n"
      << "  Actual:   " << this->eventHistory_SPWManager_RMAPWriteResult->size() << "\n";
  }

  void SPWManagerGTestBase ::
    assertEvents_SPWManager_RMAPWriteResult(
        const char *const __ISF_callSiteFileName,
        const U32 __ISF_callSiteLineNumber,
        const U32 index,
        const U32 address
    ) const
  {
    ASSERT_GT(this->eventHistory_SPWManager_RMAPWriteResult->size(), index)
      << "\n"
      << "  File:     " << __ISF_callSiteFileName << "\n"
      << "  Line:     " << __ISF_callSiteLineNumber << "\n"
      << "  Value:    Index into history of event SPWManager_RMAPWriteResult\n"
      << "  Expected: Less than size of history (" 
      << this->eventHistory_SPWManager_RMAPWriteResult->size() << ")\n"
      << "  Actual:   " << index << "\n";
    const EventEntry_SPWManager_RMAPWriteResult& e =
      this->eventHistory_SPWManager_RMAPWriteResult->at(index);
    ASSERT_EQ(address, e.address)
      << "\n"
      << "  File:     " << __ISF_callSiteFileName << "\n"
      << "  Line:     " << __ISF_callSiteLineNumber << "\n"
      << "  Value:    Value of argument address at index "
      << index
      << " in history of event SPWManager_RMAPWriteResult\n"
      << "  Expected: " << address << "\n"
      << "  Actual:   " << e.address << "\n";
  }

  // ----------------------------------------------------------------------
  // Event: SPWManager_RMAPReadResult
  // ----------------------------------------------------------------------

  void SPWManagerGTestBase ::
    assertEvents_SPWManager_RMAPReadResult_size(
        const char *const __ISF_callSiteFileName,
        const U32 __ISF_callSiteLineNumber,
        const U32 size
    ) const
  {
    ASSERT_EQ(size, this->eventHistory_SPWManager_RMAPReadResult->size())
      << "\n"
      << "  File:     " << __ISF_callSiteFileName << "\n"
      << "  Line:     " << __ISF_callSiteLineNumber << "\n"
      << "  Value:    Size of history for event SPWManager_RMAPReadResult\n"
      << "  Expected: " << size << "\n"
      << "  Actual:   " << this->eventHistory_SPWManager_RMAPReadResult->size() << "\n";
  }

  void SPWManagerGTestBase ::
    assertEvents_SPWManager_RMAPReadResult(
        const char *const __ISF_callSiteFileName,
        const U32 __ISF_callSiteLineNumber,
        const U32 index,
        const U32 address,
        const U32 value
    ) const
  {
    ASSERT_GT(this->eventHistory_SPWManager_RMAPReadResult->size(), index)
      << "\n"
      << "  File:     " << __ISF_callSiteFileName << "\n"
      << "  Line:     " << __ISF_callSiteLineNumber << "\n"
      << "  Value:    Index into history of event SPWManager_RMAPReadResult\n"
      << "  Expected: Less than size of history (" 
      << this->eventHistory_SPWManager_RMAPReadResult->size() << ")\n"
      << "  Actual:   " << index << "\n";
    const EventEntry_SPWManager_RMAPReadResult& e =
      this->eventHistory_SPWManager_RMAPReadResult->at(index);
    ASSERT_EQ(address, e.address)
      << "\n"
      << "  File:     " << __ISF_callSiteFileName << "\n"
      << "  Line:     " << __ISF_callSiteLineNumber << "\n"
      << "  Value:    Value of argument address at index "
      << index
      << " in history of event SPWManager_RMAPReadResult\n"
      << "  Expected: " << address << "\n"
      << "  Actual:   " << e.address << "\n";
    ASSERT_EQ(value, e.value)
      << "\n"
      << "  File:     " << __ISF_callSiteFileName << "\n"
      << "  Line:     " << __ISF_callSiteLineNumber << "\n"
      << "  Value:    Value of argument value at index "
      << index
      << " in history of event SPWManager_RMAPReadResult\n"
      << "  Expected: " << value << "\n"
      << "  Actual:   " << e.value << "\n";
  }

  // ----------------------------------------------------------------------
  // Event: SPWManager_Busy
  // ----------------------------------------------------------------------

  void SPWManagerGTestBase ::
    assertEvents_SPWManager_Busy_size(
        const char *const __ISF_callSiteFileName,
        const U32 __ISF_callSiteLineNumber,
        const U32 size
    ) const
  {
    ASSERT_EQ(size, this->eventsSize_SPWManager_Busy)
      << "\n"
      << "  File:     " << __ISF_callSiteFileName << "\n"
      << "  Line:     " << __ISF_callSiteLineNumber << "\n"
      << "  Value:    Size of history for event SPWManager_Busy\n"
      << "  Expected: " << size << "\n"
      << "  Actual:   " << this->eventsSize_SPWManager_Busy << "\n";
  }

  // ----------------------------------------------------------------------
  // Event: SPWManager_ResetLink
  // ----------------------------------------------------------------------

  void SPWManagerGTestBase ::
    assertEvents_SPWManager_ResetLink_size(
        const char *const __ISF_callSiteFileName,
        const U32 __ISF_callSiteLineNumber,
        const U32 size
    ) const
  {
    ASSERT_EQ(size, this->eventHistory_SPWManager_ResetLink->size())
      << "\n"
      << "  File:     " << __ISF_callSiteFileName << "\n"
      << "  Line:     " << __ISF_callSiteLineNumber << "\n"
      << "  Value:    Size of history for event SPWManager_ResetLink\n"
      << "  Expected: " << size << "\n"
      << "  Actual:   " << this->eventHistory_SPWManager_ResetLink->size() << "\n";
  }

  void SPWManagerGTestBase ::
    assertEvents_SPWManager_ResetLink(
        const char *const __ISF_callSiteFileName,
        const U32 __ISF_callSiteLineNumber,
        const U32 index,
        const U32 numAborted
    ) const
  {
    ASSERT_GT(this->eventHistory_SPWManager_ResetLink->size(), index)
      << "\n"
      << "  File:     " << __ISF_callSiteFileName << "\n"
      << "  Line:     " << __ISF_callSiteLineNumber << "\n"
      << "  Value:    Index into history of event SPWManager_ResetLink\n"
      << "  Expected: Less than size of history (" 
      << this->eventHistory_SPWManager_ResetLink->size() << ")\n"
      << "  Actual:   " << index << "\n";
    const EventEntry_SPWManager_ResetLink& e =
      this->eventHistory_SPWManager_ResetLink->at(index);
    ASSERT_EQ(numAborted, e.numAborted)
      << "\n"
      << "  File:     " << __ISF_callSiteFileName << "\n"
      << "  Line:     " << __ISF_callSiteLineNumber << "\n"
      << "  Value:    Value of argument numAborted at index "
      << index
      << " in history of event SPWManager_ResetLink\n"
      << "  Expected: " << numAborted << "\n"
      << "  Actual:   " << e.numAborted << "\n";
  }

  // ----------------------------------------------------------------------
  // From ports
  // ----------------------------------------------------------------------

  void SPWManagerGTestBase ::
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
  // From port: driverWriteRMAP
  // ----------------------------------------------------------------------

  void SPWManagerGTestBase ::
    assert_from_driverWriteRMAP_size(
        const char *const __ISF_callSiteFileName,
        const U32 __ISF_callSiteLineNumber,
        const U32 size
    ) const
  {
    ASSERT_EQ(size, this->fromPortHistory_driverWriteRMAP->size())
      << "\n"
      << "  File:     " << __ISF_callSiteFileName << "\n"
      << "  Line:     " << __ISF_callSiteLineNumber << "\n"
      << "  Value:    Size of history for from_driverWriteRMAP\n"
      << "  Expected: " << size << "\n"
      << "  Actual:   " << this->fromPortHistory_driverWriteRMAP->size() << "\n";
  }

  // ----------------------------------------------------------------------
  // From port: statusOut
  // ----------------------------------------------------------------------

  void SPWManagerGTestBase ::
    assert_from_statusOut_size(
        const char *const __ISF_callSiteFileName,
        const U32 __ISF_callSiteLineNumber,
        const U32 size
    ) const
  {
    ASSERT_EQ(size, this->fromPortHistory_statusOut->size())
      << "\n"
      << "  File:     " << __ISF_callSiteFileName << "\n"
      << "  Line:     " << __ISF_callSiteLineNumber << "\n"
      << "  Value:    Size of history for from_statusOut\n"
      << "  Expected: " << size << "\n"
      << "  Actual:   " << this->fromPortHistory_statusOut->size() << "\n";
  }

  // ----------------------------------------------------------------------
  // From port: PingResponse
  // ----------------------------------------------------------------------

  void SPWManagerGTestBase ::
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
  // From port: driverReset
  // ----------------------------------------------------------------------

  void SPWManagerGTestBase ::
    assert_from_driverReset_size(
        const char *const __ISF_callSiteFileName,
        const U32 __ISF_callSiteLineNumber,
        const U32 size
    ) const
  {
    ASSERT_EQ(size, this->fromPortHistorySize_driverReset)
      << "\n"
      << "  File:     " << __ISF_callSiteFileName << "\n"
      << "  Line:     " << __ISF_callSiteLineNumber << "\n"
      << "  Value:    Size of history for from_driverReset\n"
      << "  Expected: " << size << "\n"
      << "  Actual:   " << this->fromPortHistorySize_driverReset << "\n";
  }

  // ----------------------------------------------------------------------
  // From port: driverReadRMAP
  // ----------------------------------------------------------------------

  void SPWManagerGTestBase ::
    assert_from_driverReadRMAP_size(
        const char *const __ISF_callSiteFileName,
        const U32 __ISF_callSiteLineNumber,
        const U32 size
    ) const
  {
    ASSERT_EQ(size, this->fromPortHistory_driverReadRMAP->size())
      << "\n"
      << "  File:     " << __ISF_callSiteFileName << "\n"
      << "  Line:     " << __ISF_callSiteLineNumber << "\n"
      << "  Value:    Size of history for from_driverReadRMAP\n"
      << "  Expected: " << size << "\n"
      << "  Actual:   " << this->fromPortHistory_driverReadRMAP->size() << "\n";
  }

  // ----------------------------------------------------------------------
  // From port: driverGetStatus
  // ----------------------------------------------------------------------

  void SPWManagerGTestBase ::
    assert_from_driverGetStatus_size(
        const char *const __ISF_callSiteFileName,
        const U32 __ISF_callSiteLineNumber,
        const U32 size
    ) const
  {
    ASSERT_EQ(size, this->fromPortHistorySize_driverGetStatus)
      << "\n"
      << "  File:     " << __ISF_callSiteFileName << "\n"
      << "  Line:     " << __ISF_callSiteLineNumber << "\n"
      << "  Value:    Size of history for from_driverGetStatus\n"
      << "  Expected: " << size << "\n"
      << "  Actual:   " << this->fromPortHistorySize_driverGetStatus << "\n";
  }

} // end namespace Drv
