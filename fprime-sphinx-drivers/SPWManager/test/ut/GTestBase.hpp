// ======================================================================
// \title  SPWManager/test/ut/GTestBase.hpp
// \author Auto-generated
// \brief  hpp file for SPWManager component Google Test harness base class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
// ======================================================================

#ifndef SPWManager_GTEST_BASE_HPP
#define SPWManager_GTEST_BASE_HPP

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
// Macros for event history assertions 
// ----------------------------------------------------------------------

#define ASSERT_EVENTS_SIZE(size) \
  this->assertEvents_size(__FILE__, __LINE__, size)

#define ASSERT_EVENTS_SPWManager_SpaceWireInitializationError_SIZE(size) \
  this->assertEvents_SPWManager_SpaceWireInitializationError_size(__FILE__, __LINE__, size)

#define ASSERT_EVENTS_SPWManager_SpaceWireInitializationError(index, _status) \
  this->assertEvents_SPWManager_SpaceWireInitializationError(__FILE__, __LINE__, index, _status)

#define ASSERT_EVENTS_SPWManager_SpaceWireLinkDisconnected_SIZE(size) \
  this->assertEvents_SPWManager_SpaceWireLinkDisconnected_size(__FILE__, __LINE__, size)

#define ASSERT_EVENTS_SPWManager_SpaceWireError_SIZE(size) \
  this->assertEvents_SPWManager_SpaceWireError_size(__FILE__, __LINE__, size)

#define ASSERT_EVENTS_SPWManager_SpaceWireError(index, _status, _statusCode) \
  this->assertEvents_SPWManager_SpaceWireError(__FILE__, __LINE__, index, _status, _statusCode)

#define ASSERT_EVENTS_SPWManager_SpaceWireTransactionTimeout_SIZE(size) \
  this->assertEvents_SPWManager_SpaceWireTransactionTimeout_size(__FILE__, __LINE__, size)

#define ASSERT_EVENTS_SPWManager_SpaceWireTransactionTimeout(index, _timeout, _command, _address, _status) \
  this->assertEvents_SPWManager_SpaceWireTransactionTimeout(__FILE__, __LINE__, index, _timeout, _command, _address, _status)

#define ASSERT_EVENTS_SPWManager_RMAPWriteResult_SIZE(size) \
  this->assertEvents_SPWManager_RMAPWriteResult_size(__FILE__, __LINE__, size)

#define ASSERT_EVENTS_SPWManager_RMAPWriteResult(index, _address) \
  this->assertEvents_SPWManager_RMAPWriteResult(__FILE__, __LINE__, index, _address)

#define ASSERT_EVENTS_SPWManager_RMAPReadResult_SIZE(size) \
  this->assertEvents_SPWManager_RMAPReadResult_size(__FILE__, __LINE__, size)

#define ASSERT_EVENTS_SPWManager_RMAPReadResult(index, _address, _value) \
  this->assertEvents_SPWManager_RMAPReadResult(__FILE__, __LINE__, index, _address, _value)

#define ASSERT_EVENTS_SPWManager_Busy_SIZE(size) \
  this->assertEvents_SPWManager_Busy_size(__FILE__, __LINE__, size)

#define ASSERT_EVENTS_SPWManager_ResetLink_SIZE(size) \
  this->assertEvents_SPWManager_ResetLink_size(__FILE__, __LINE__, size)

#define ASSERT_EVENTS_SPWManager_ResetLink(index, _numAborted) \
  this->assertEvents_SPWManager_ResetLink(__FILE__, __LINE__, index, _numAborted)

// ----------------------------------------------------------------------
// Macros for typed user from port history assertions
// ----------------------------------------------------------------------

#define ASSERT_FROM_PORT_HISTORY_SIZE(size) \
  this->assertFromPortHistory_size(__FILE__, __LINE__, size)

#define ASSERT_from_driverWriteRMAP_SIZE(size) \
  this->assert_from_driverWriteRMAP_size(__FILE__, __LINE__, size)

#define ASSERT_from_driverWriteRMAP(index, _dest_addr, _dest_key, _write_addr, _buf_ptr, _num_bytes, _increment, _verify, _acknowledge) \
  { \
    ASSERT_GT(this->fromPortHistory_driverWriteRMAP->size(), static_cast<U32>(index)) \
    << "\n" \
    << "  File:     " << __FILE__ << "\n" \
    << "  Line:     " << __LINE__ << "\n" \
    << "  Value:    Index into history of from_driverWriteRMAP\n" \
    << "  Expected: Less than size of history (" \
    << this->fromPortHistory_driverWriteRMAP->size() << ")\n" \
    << "  Actual:   " << index << "\n"; \
    const FromPortEntry_driverWriteRMAP& _e = \
      this->fromPortHistory_driverWriteRMAP->at(index); \
    ASSERT_EQ(_dest_addr, _e.dest_addr) \
    << "\n" \
    << "  File:     " << __FILE__ << "\n" \
    << "  Line:     " << __LINE__ << "\n" \
    << "  Value:    Value of argument dest_addr at index " \
    << index \
    << " in history of from_driverWriteRMAP\n" \
    << "  Expected: " << _dest_addr << "\n" \
    << "  Actual:   " << _e.dest_addr << "\n"; \
    ASSERT_EQ(_dest_key, _e.dest_key) \
    << "\n" \
    << "  File:     " << __FILE__ << "\n" \
    << "  Line:     " << __LINE__ << "\n" \
    << "  Value:    Value of argument dest_key at index " \
    << index \
    << " in history of from_driverWriteRMAP\n" \
    << "  Expected: " << _dest_key << "\n" \
    << "  Actual:   " << _e.dest_key << "\n"; \
    ASSERT_EQ(_write_addr, _e.write_addr) \
    << "\n" \
    << "  File:     " << __FILE__ << "\n" \
    << "  Line:     " << __LINE__ << "\n" \
    << "  Value:    Value of argument write_addr at index " \
    << index \
    << " in history of from_driverWriteRMAP\n" \
    << "  Expected: " << _write_addr << "\n" \
    << "  Actual:   " << _e.write_addr << "\n"; \
    ASSERT_EQ(_buf_ptr, _e.buf_ptr) \
    << "\n" \
    << "  File:     " << __FILE__ << "\n" \
    << "  Line:     " << __LINE__ << "\n" \
    << "  Value:    Value of argument buf_ptr at index " \
    << index \
    << " in history of from_driverWriteRMAP\n" \
    << "  Expected: " << _buf_ptr << "\n" \
    << "  Actual:   " << _e.buf_ptr << "\n"; \
    ASSERT_EQ(_num_bytes, _e.num_bytes) \
    << "\n" \
    << "  File:     " << __FILE__ << "\n" \
    << "  Line:     " << __LINE__ << "\n" \
    << "  Value:    Value of argument num_bytes at index " \
    << index \
    << " in history of from_driverWriteRMAP\n" \
    << "  Expected: " << _num_bytes << "\n" \
    << "  Actual:   " << _e.num_bytes << "\n"; \
    ASSERT_EQ(_increment, _e.increment) \
    << "\n" \
    << "  File:     " << __FILE__ << "\n" \
    << "  Line:     " << __LINE__ << "\n" \
    << "  Value:    Value of argument increment at index " \
    << index \
    << " in history of from_driverWriteRMAP\n" \
    << "  Expected: " << _increment << "\n" \
    << "  Actual:   " << _e.increment << "\n"; \
    ASSERT_EQ(_verify, _e.verify) \
    << "\n" \
    << "  File:     " << __FILE__ << "\n" \
    << "  Line:     " << __LINE__ << "\n" \
    << "  Value:    Value of argument verify at index " \
    << index \
    << " in history of from_driverWriteRMAP\n" \
    << "  Expected: " << _verify << "\n" \
    << "  Actual:   " << _e.verify << "\n"; \
    ASSERT_EQ(_acknowledge, _e.acknowledge) \
    << "\n" \
    << "  File:     " << __FILE__ << "\n" \
    << "  Line:     " << __LINE__ << "\n" \
    << "  Value:    Value of argument acknowledge at index " \
    << index \
    << " in history of from_driverWriteRMAP\n" \
    << "  Expected: " << _acknowledge << "\n" \
    << "  Actual:   " << _e.acknowledge << "\n"; \
  }

#define ASSERT_from_statusOut_SIZE(size) \
  this->assert_from_statusOut_size(__FILE__, __LINE__, size)

#define ASSERT_from_statusOut(index, _spwStatus) \
  { \
    ASSERT_GT(this->fromPortHistory_statusOut->size(), static_cast<U32>(index)) \
    << "\n" \
    << "  File:     " << __FILE__ << "\n" \
    << "  Line:     " << __LINE__ << "\n" \
    << "  Value:    Index into history of from_statusOut\n" \
    << "  Expected: Less than size of history (" \
    << this->fromPortHistory_statusOut->size() << ")\n" \
    << "  Actual:   " << index << "\n"; \
    const FromPortEntry_statusOut& _e = \
      this->fromPortHistory_statusOut->at(index); \
    ASSERT_EQ(_spwStatus, _e.spwStatus) \
    << "\n" \
    << "  File:     " << __FILE__ << "\n" \
    << "  Line:     " << __LINE__ << "\n" \
    << "  Value:    Value of argument spwStatus at index " \
    << index \
    << " in history of from_statusOut\n" \
    << "  Expected: " << _spwStatus << "\n" \
    << "  Actual:   " << _e.spwStatus << "\n"; \
  }

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

#define ASSERT_from_driverReset_SIZE(size) \
  this->assert_from_driverReset_size(__FILE__, __LINE__, size)

#define ASSERT_from_driverReadRMAP_SIZE(size) \
  this->assert_from_driverReadRMAP_size(__FILE__, __LINE__, size)

#define ASSERT_from_driverReadRMAP(index, _dest_addr, _dest_key, _read_addr, _buf_ptr, _num_bytes, _increment) \
  { \
    ASSERT_GT(this->fromPortHistory_driverReadRMAP->size(), static_cast<U32>(index)) \
    << "\n" \
    << "  File:     " << __FILE__ << "\n" \
    << "  Line:     " << __LINE__ << "\n" \
    << "  Value:    Index into history of from_driverReadRMAP\n" \
    << "  Expected: Less than size of history (" \
    << this->fromPortHistory_driverReadRMAP->size() << ")\n" \
    << "  Actual:   " << index << "\n"; \
    const FromPortEntry_driverReadRMAP& _e = \
      this->fromPortHistory_driverReadRMAP->at(index); \
    ASSERT_EQ(_dest_addr, _e.dest_addr) \
    << "\n" \
    << "  File:     " << __FILE__ << "\n" \
    << "  Line:     " << __LINE__ << "\n" \
    << "  Value:    Value of argument dest_addr at index " \
    << index \
    << " in history of from_driverReadRMAP\n" \
    << "  Expected: " << _dest_addr << "\n" \
    << "  Actual:   " << _e.dest_addr << "\n"; \
    ASSERT_EQ(_dest_key, _e.dest_key) \
    << "\n" \
    << "  File:     " << __FILE__ << "\n" \
    << "  Line:     " << __LINE__ << "\n" \
    << "  Value:    Value of argument dest_key at index " \
    << index \
    << " in history of from_driverReadRMAP\n" \
    << "  Expected: " << _dest_key << "\n" \
    << "  Actual:   " << _e.dest_key << "\n"; \
    ASSERT_EQ(_read_addr, _e.read_addr) \
    << "\n" \
    << "  File:     " << __FILE__ << "\n" \
    << "  Line:     " << __LINE__ << "\n" \
    << "  Value:    Value of argument read_addr at index " \
    << index \
    << " in history of from_driverReadRMAP\n" \
    << "  Expected: " << _read_addr << "\n" \
    << "  Actual:   " << _e.read_addr << "\n"; \
    ASSERT_EQ(_buf_ptr, _e.buf_ptr) \
    << "\n" \
    << "  File:     " << __FILE__ << "\n" \
    << "  Line:     " << __LINE__ << "\n" \
    << "  Value:    Value of argument buf_ptr at index " \
    << index \
    << " in history of from_driverReadRMAP\n" \
    << "  Expected: " << _buf_ptr << "\n" \
    << "  Actual:   " << _e.buf_ptr << "\n"; \
    ASSERT_EQ(_num_bytes, _e.num_bytes) \
    << "\n" \
    << "  File:     " << __FILE__ << "\n" \
    << "  Line:     " << __LINE__ << "\n" \
    << "  Value:    Value of argument num_bytes at index " \
    << index \
    << " in history of from_driverReadRMAP\n" \
    << "  Expected: " << _num_bytes << "\n" \
    << "  Actual:   " << _e.num_bytes << "\n"; \
    ASSERT_EQ(_increment, _e.increment) \
    << "\n" \
    << "  File:     " << __FILE__ << "\n" \
    << "  Line:     " << __LINE__ << "\n" \
    << "  Value:    Value of argument increment at index " \
    << index \
    << " in history of from_driverReadRMAP\n" \
    << "  Expected: " << _increment << "\n" \
    << "  Actual:   " << _e.increment << "\n"; \
  }

#define ASSERT_from_driverGetStatus_SIZE(size) \
  this->assert_from_driverGetStatus_size(__FILE__, __LINE__, size)

namespace Drv {

  //! \class SPWManagerGTestBase
  //! \brief Auto-generated base class for SPWManager component Google Test harness
  //!
  class SPWManagerGTestBase :
    public SPWManagerTesterBase
  {

    protected:

      // ----------------------------------------------------------------------
      // Construction and destruction
      // ----------------------------------------------------------------------

      //! Construct object SPWManagerGTestBase
      //!
      SPWManagerGTestBase(
#if FW_OBJECT_NAMES == 1
          const char *const compName, /*!< The component name*/
          const U32 maxHistorySize /*!< The maximum size of each history*/
#else
          const U32 maxHistorySize /*!< The maximum size of each history*/
#endif
      );

      //! Destroy object SPWManagerGTestBase
      //!
      virtual ~SPWManagerGTestBase(void);

    protected:

      // ----------------------------------------------------------------------
      // Commands
      // ----------------------------------------------------------------------

      //! Assert size of command response history
      //!
      void assertCmdResponse_size(
          const char *const __ISF_callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __ISF_callSiteLineNumber, /*!< The line number of the call site*/
          const U32 size /*!< The asserted size*/
      ) const;

      //! Assert command response in history at index
      //!
      void assertCmdResponse(
          const char *const __ISF_callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __ISF_callSiteLineNumber, /*!< The line number of the call site*/
          const U32 index, /*!< The index*/
          const FwOpcodeType opCode, /*!< The opcode*/
          const U32 cmdSeq, /*!< The command sequence number*/
          const Fw::CommandResponse response /*!< The command response*/
      ) const;

    protected:

      // ----------------------------------------------------------------------
      // Events
      // ----------------------------------------------------------------------

      void assertEvents_size(
          const char *const __ISF_callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __ISF_callSiteLineNumber, /*!< The line number of the call site*/
          const U32 size /*!< The asserted size*/
      ) const;

    protected:

      // ----------------------------------------------------------------------
      // Event: SPWManager_SpaceWireInitializationError
      // ----------------------------------------------------------------------

      void assertEvents_SPWManager_SpaceWireInitializationError_size(
          const char *const __ISF_callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __ISF_callSiteLineNumber, /*!< The line number of the call site*/
          const U32 size /*!< The asserted size*/
      ) const;

      void assertEvents_SPWManager_SpaceWireInitializationError(
          const char *const __ISF_callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __ISF_callSiteLineNumber, /*!< The line number of the call site*/
          const U32 index, /*!< The index*/
          const I32 status /*!< Error status from SPWDriver*/
      ) const;

    protected:

      // ----------------------------------------------------------------------
      // Event: SPWManager_SpaceWireLinkDisconnected
      // ----------------------------------------------------------------------

      void assertEvents_SPWManager_SpaceWireLinkDisconnected_size(
          const char *const __ISF_callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __ISF_callSiteLineNumber, /*!< The line number of the call site*/
          const U32 size /*!< The asserted size*/
      ) const;

    protected:

      // ----------------------------------------------------------------------
      // Event: SPWManager_SpaceWireError
      // ----------------------------------------------------------------------

      void assertEvents_SPWManager_SpaceWireError_size(
          const char *const __ISF_callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __ISF_callSiteLineNumber, /*!< The line number of the call site*/
          const U32 size /*!< The asserted size*/
      ) const;

      void assertEvents_SPWManager_SpaceWireError(
          const char *const __ISF_callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __ISF_callSiteLineNumber, /*!< The line number of the call site*/
          const U32 index, /*!< The index*/
          SPWManagerComponentBase::SpaceWireError_status status, /*!< Status enum*/
          const I32 statusCode /*!< Error status code from SPWDriver*/
      ) const;

    protected:

      // ----------------------------------------------------------------------
      // Event: SPWManager_SpaceWireTransactionTimeout
      // ----------------------------------------------------------------------

      void assertEvents_SPWManager_SpaceWireTransactionTimeout_size(
          const char *const __ISF_callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __ISF_callSiteLineNumber, /*!< The line number of the call site*/
          const U32 size /*!< The asserted size*/
      ) const;

      void assertEvents_SPWManager_SpaceWireTransactionTimeout(
          const char *const __ISF_callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __ISF_callSiteLineNumber, /*!< The line number of the call site*/
          const U32 index, /*!< The index*/
          const U32 timeout, /*!< Timeout value*/
          SPWManagerComponentBase::SpaceWireTransactionTimeout_command command, /*!< Type of command*/
          const U32 address, /*!< Target address to perform command on*/
          SPWManagerComponentBase::SpaceWireTransactionTimeout_status status /*!< State of transaction at timeout*/
      ) const;

    protected:

      // ----------------------------------------------------------------------
      // Event: SPWManager_RMAPWriteResult
      // ----------------------------------------------------------------------

      void assertEvents_SPWManager_RMAPWriteResult_size(
          const char *const __ISF_callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __ISF_callSiteLineNumber, /*!< The line number of the call site*/
          const U32 size /*!< The asserted size*/
      ) const;

      void assertEvents_SPWManager_RMAPWriteResult(
          const char *const __ISF_callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __ISF_callSiteLineNumber, /*!< The line number of the call site*/
          const U32 index, /*!< The index*/
          const U32 address /*!< Target address to perform command on*/
      ) const;

    protected:

      // ----------------------------------------------------------------------
      // Event: SPWManager_RMAPReadResult
      // ----------------------------------------------------------------------

      void assertEvents_SPWManager_RMAPReadResult_size(
          const char *const __ISF_callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __ISF_callSiteLineNumber, /*!< The line number of the call site*/
          const U32 size /*!< The asserted size*/
      ) const;

      void assertEvents_SPWManager_RMAPReadResult(
          const char *const __ISF_callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __ISF_callSiteLineNumber, /*!< The line number of the call site*/
          const U32 index, /*!< The index*/
          const U32 address, /*!< Target address to perform command on*/
          const U32 value /*!< Value returned from read*/
      ) const;

    protected:

      // ----------------------------------------------------------------------
      // Event: SPWManager_Busy
      // ----------------------------------------------------------------------

      void assertEvents_SPWManager_Busy_size(
          const char *const __ISF_callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __ISF_callSiteLineNumber, /*!< The line number of the call site*/
          const U32 size /*!< The asserted size*/
      ) const;

    protected:

      // ----------------------------------------------------------------------
      // Event: SPWManager_ResetLink
      // ----------------------------------------------------------------------

      void assertEvents_SPWManager_ResetLink_size(
          const char *const __ISF_callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __ISF_callSiteLineNumber, /*!< The line number of the call site*/
          const U32 size /*!< The asserted size*/
      ) const;

      void assertEvents_SPWManager_ResetLink(
          const char *const __ISF_callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __ISF_callSiteLineNumber, /*!< The line number of the call site*/
          const U32 index, /*!< The index*/
          const U32 numAborted /*!< Number of async requests aborted*/
      ) const;

    protected:

      // ----------------------------------------------------------------------
      // From ports 
      // ----------------------------------------------------------------------

      void assertFromPortHistory_size(
          const char *const __ISF_callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __ISF_callSiteLineNumber, /*!< The line number of the call site*/
          const U32 size /*!< The asserted size*/
      ) const;

    protected:

      // ----------------------------------------------------------------------
      // From port: driverWriteRMAP 
      // ----------------------------------------------------------------------

      void assert_from_driverWriteRMAP_size(
          const char *const __ISF_callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __ISF_callSiteLineNumber, /*!< The line number of the call site*/
          const U32 size /*!< The asserted size*/
      ) const;

    protected:

      // ----------------------------------------------------------------------
      // From port: statusOut 
      // ----------------------------------------------------------------------

      void assert_from_statusOut_size(
          const char *const __ISF_callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __ISF_callSiteLineNumber, /*!< The line number of the call site*/
          const U32 size /*!< The asserted size*/
      ) const;

    protected:

      // ----------------------------------------------------------------------
      // From port: PingResponse 
      // ----------------------------------------------------------------------

      void assert_from_PingResponse_size(
          const char *const __ISF_callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __ISF_callSiteLineNumber, /*!< The line number of the call site*/
          const U32 size /*!< The asserted size*/
      ) const;

    protected:

      // ----------------------------------------------------------------------
      // From port: driverReset 
      // ----------------------------------------------------------------------

      void assert_from_driverReset_size(
          const char *const __ISF_callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __ISF_callSiteLineNumber, /*!< The line number of the call site*/
          const U32 size /*!< The asserted size*/
      ) const;

    protected:

      // ----------------------------------------------------------------------
      // From port: driverReadRMAP 
      // ----------------------------------------------------------------------

      void assert_from_driverReadRMAP_size(
          const char *const __ISF_callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __ISF_callSiteLineNumber, /*!< The line number of the call site*/
          const U32 size /*!< The asserted size*/
      ) const;

    protected:

      // ----------------------------------------------------------------------
      // From port: driverGetStatus 
      // ----------------------------------------------------------------------

      void assert_from_driverGetStatus_size(
          const char *const __ISF_callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __ISF_callSiteLineNumber, /*!< The line number of the call site*/
          const U32 size /*!< The asserted size*/
      ) const;

  };

} // end namespace Drv

#endif
