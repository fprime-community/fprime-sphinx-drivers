// ======================================================================
// \title  FPGADriver/test/ut/GTestBase.hpp
// \author Auto-generated
// \brief  hpp file for FPGADriver component Google Test harness base class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
// ======================================================================

#ifndef FPGADriver_GTEST_BASE_HPP
#define FPGADriver_GTEST_BASE_HPP

#include "TesterBase.hpp"
#include "gtest/gtest.h"

// ----------------------------------------------------------------------
// Macros for typed user from port history assertions
// ----------------------------------------------------------------------

#define ASSERT_FROM_PORT_HISTORY_SIZE(size) \
  this->assertFromPortHistory_size(__FILE__, __LINE__, size)

#define ASSERT_from_timeRTIOut_SIZE(size) \
  this->assert_from_timeRTIOut_size(__FILE__, __LINE__, size)

#define ASSERT_from_timeRTIOut(index, _context) \
  { \
    ASSERT_GT(this->fromPortHistory_timeRTIOut->size(), static_cast<U32>(index)) \
    << "\n" \
    << "  File:     " << __FILE__ << "\n" \
    << "  Line:     " << __LINE__ << "\n" \
    << "  Value:    Index into history of from_timeRTIOut\n" \
    << "  Expected: Less than size of history (" \
    << this->fromPortHistory_timeRTIOut->size() << ")\n" \
    << "  Actual:   " << index << "\n"; \
    const FromPortEntry_timeRTIOut& _e = \
      this->fromPortHistory_timeRTIOut->at(index); \
    ASSERT_EQ(_context, _e.context) \
    << "\n" \
    << "  File:     " << __FILE__ << "\n" \
    << "  Line:     " << __LINE__ << "\n" \
    << "  Value:    Value of argument context at index " \
    << index \
    << " in history of from_timeRTIOut\n" \
    << "  Expected: " << _context << "\n" \
    << "  Actual:   " << _e.context << "\n"; \
  }

#define ASSERT_from_cycleOut_SIZE(size) \
  this->assert_from_cycleOut_size(__FILE__, __LINE__, size)

#define ASSERT_from_cycleOut(index, _cycleStart) \
  { \
    ASSERT_GT(this->fromPortHistory_cycleOut->size(), static_cast<U32>(index)) \
    << "\n" \
    << "  File:     " << __FILE__ << "\n" \
    << "  Line:     " << __LINE__ << "\n" \
    << "  Value:    Index into history of from_cycleOut\n" \
    << "  Expected: Less than size of history (" \
    << this->fromPortHistory_cycleOut->size() << ")\n" \
    << "  Actual:   " << index << "\n"; \
    const FromPortEntry_cycleOut& _e = \
      this->fromPortHistory_cycleOut->at(index); \
    ASSERT_EQ(_cycleStart, _e.cycleStart) \
    << "\n" \
    << "  File:     " << __FILE__ << "\n" \
    << "  Line:     " << __LINE__ << "\n" \
    << "  Value:    Value of argument cycleStart at index " \
    << index \
    << " in history of from_cycleOut\n" \
    << "  Expected: " << _cycleStart << "\n" \
    << "  Actual:   " << _e.cycleStart << "\n"; \
  }

namespace Drv {

  //! \class FPGADriverGTestBase
  //! \brief Auto-generated base class for FPGADriver component Google Test harness
  //!
  class FPGADriverGTestBase :
    public FPGADriverTesterBase
  {

    protected:

      // ----------------------------------------------------------------------
      // Construction and destruction
      // ----------------------------------------------------------------------

      //! Construct object FPGADriverGTestBase
      //!
      FPGADriverGTestBase(
#if FW_OBJECT_NAMES == 1
          const char *const compName, /*!< The component name*/
          const U32 maxHistorySize /*!< The maximum size of each history*/
#else
          const U32 maxHistorySize /*!< The maximum size of each history*/
#endif
      );

      //! Destroy object FPGADriverGTestBase
      //!
      virtual ~FPGADriverGTestBase(void);

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
      // From port: timeRTIOut 
      // ----------------------------------------------------------------------

      void assert_from_timeRTIOut_size(
          const char *const __ISF_callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __ISF_callSiteLineNumber, /*!< The line number of the call site*/
          const U32 size /*!< The asserted size*/
      ) const;

    protected:

      // ----------------------------------------------------------------------
      // From port: cycleOut 
      // ----------------------------------------------------------------------

      void assert_from_cycleOut_size(
          const char *const __ISF_callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __ISF_callSiteLineNumber, /*!< The line number of the call site*/
          const U32 size /*!< The asserted size*/
      ) const;

  };

} // end namespace Drv

#endif
