// ======================================================================
// \title  NORFlashMgrWorker/test/ut/GTestBase.hpp
// \author Auto-generated
// \brief  hpp file for NORFlashMgrWorker component Google Test harness base class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
// ======================================================================

#ifndef NORFlashMgrWorker_GTEST_BASE_HPP
#define NORFlashMgrWorker_GTEST_BASE_HPP

#include "TesterBase.hpp"
#include "gtest/gtest.h"

// ----------------------------------------------------------------------
// Macros for typed user from port history assertions
// ----------------------------------------------------------------------

#define ASSERT_FROM_PORT_HISTORY_SIZE(size) \
  this->assertFromPortHistory_size(__FILE__, __LINE__, size)

#define ASSERT_from_read_SIZE(size) \
  this->assert_from_read_size(__FILE__, __LINE__, size)

#define ASSERT_from_read(index, _dest, _data) \
  { \
    ASSERT_GT(this->fromPortHistory_read->size(), static_cast<U32>(index)) \
    << "\n" \
    << "  File:     " << __FILE__ << "\n" \
    << "  Line:     " << __LINE__ << "\n" \
    << "  Value:    Index into history of from_read\n" \
    << "  Expected: Less than size of history (" \
    << this->fromPortHistory_read->size() << ")\n" \
    << "  Actual:   " << index << "\n"; \
    const FromPortEntry_read& _e = \
      this->fromPortHistory_read->at(index); \
    ASSERT_EQ(_dest, _e.dest) \
    << "\n" \
    << "  File:     " << __FILE__ << "\n" \
    << "  Line:     " << __LINE__ << "\n" \
    << "  Value:    Value of argument dest at index " \
    << index \
    << " in history of from_read\n" \
    << "  Expected: " << _dest << "\n" \
    << "  Actual:   " << _e.dest << "\n"; \
    ASSERT_EQ(_data, _e.data) \
    << "\n" \
    << "  File:     " << __FILE__ << "\n" \
    << "  Line:     " << __LINE__ << "\n" \
    << "  Value:    Value of argument data at index " \
    << index \
    << " in history of from_read\n" \
    << "  Expected: " << _data << "\n" \
    << "  Actual:   " << _e.data << "\n"; \
  }

#define ASSERT_from_statusOut_SIZE(size) \
  this->assert_from_statusOut_size(__FILE__, __LINE__, size)

#define ASSERT_from_statusOut(index, _done, _context1, _context2) \
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
    ASSERT_EQ(_done, _e.done) \
    << "\n" \
    << "  File:     " << __FILE__ << "\n" \
    << "  Line:     " << __LINE__ << "\n" \
    << "  Value:    Value of argument done at index " \
    << index \
    << " in history of from_statusOut\n" \
    << "  Expected: " << _done << "\n" \
    << "  Actual:   " << _e.done << "\n"; \
    ASSERT_EQ(_context1, _e.context1) \
    << "\n" \
    << "  File:     " << __FILE__ << "\n" \
    << "  Line:     " << __LINE__ << "\n" \
    << "  Value:    Value of argument context1 at index " \
    << index \
    << " in history of from_statusOut\n" \
    << "  Expected: " << _context1 << "\n" \
    << "  Actual:   " << _e.context1 << "\n"; \
    ASSERT_EQ(_context2, _e.context2) \
    << "\n" \
    << "  File:     " << __FILE__ << "\n" \
    << "  Line:     " << __LINE__ << "\n" \
    << "  Value:    Value of argument context2 at index " \
    << index \
    << " in history of from_statusOut\n" \
    << "  Expected: " << _context2 << "\n" \
    << "  Actual:   " << _e.context2 << "\n"; \
  }

#define ASSERT_from_write_SIZE(size) \
  this->assert_from_write_size(__FILE__, __LINE__, size)

#define ASSERT_from_write(index, _dest_addr, _src) \
  { \
    ASSERT_GT(this->fromPortHistory_write->size(), static_cast<U32>(index)) \
    << "\n" \
    << "  File:     " << __FILE__ << "\n" \
    << "  Line:     " << __LINE__ << "\n" \
    << "  Value:    Index into history of from_write\n" \
    << "  Expected: Less than size of history (" \
    << this->fromPortHistory_write->size() << ")\n" \
    << "  Actual:   " << index << "\n"; \
    const FromPortEntry_write& _e = \
      this->fromPortHistory_write->at(index); \
    ASSERT_EQ(_dest_addr, _e.dest_addr) \
    << "\n" \
    << "  File:     " << __FILE__ << "\n" \
    << "  Line:     " << __LINE__ << "\n" \
    << "  Value:    Value of argument dest_addr at index " \
    << index \
    << " in history of from_write\n" \
    << "  Expected: " << _dest_addr << "\n" \
    << "  Actual:   " << _e.dest_addr << "\n"; \
    ASSERT_EQ(_src, _e.src) \
    << "\n" \
    << "  File:     " << __FILE__ << "\n" \
    << "  Line:     " << __LINE__ << "\n" \
    << "  Value:    Value of argument src at index " \
    << index \
    << " in history of from_write\n" \
    << "  Expected: " << _src << "\n" \
    << "  Actual:   " << _e.src << "\n"; \
  }

namespace Drv {

  //! \class NORFlashMgrWorkerGTestBase
  //! \brief Auto-generated base class for NORFlashMgrWorker component Google Test harness
  //!
  class NORFlashMgrWorkerGTestBase :
    public NORFlashMgrWorkerTesterBase
  {

    protected:

      // ----------------------------------------------------------------------
      // Construction and destruction
      // ----------------------------------------------------------------------

      //! Construct object NORFlashMgrWorkerGTestBase
      //!
      NORFlashMgrWorkerGTestBase(
#if FW_OBJECT_NAMES == 1
          const char *const compName, /*!< The component name*/
          const U32 maxHistorySize /*!< The maximum size of each history*/
#else
          const U32 maxHistorySize /*!< The maximum size of each history*/
#endif
      );

      //! Destroy object NORFlashMgrWorkerGTestBase
      //!
      virtual ~NORFlashMgrWorkerGTestBase(void);

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
      // From port: read 
      // ----------------------------------------------------------------------

      void assert_from_read_size(
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
      // From port: write 
      // ----------------------------------------------------------------------

      void assert_from_write_size(
          const char *const __ISF_callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __ISF_callSiteLineNumber, /*!< The line number of the call site*/
          const U32 size /*!< The asserted size*/
      ) const;

  };

} // end namespace Drv

#endif
