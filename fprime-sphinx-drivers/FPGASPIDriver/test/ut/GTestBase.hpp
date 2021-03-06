// ======================================================================
// \title  FPGASPIDriver/test/ut/GTestBase.hpp
// \author Auto-generated
// \brief  hpp file for FPGASPIDriver component Google Test harness base class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
// ======================================================================

#ifndef FPGASPIDriver_GTEST_BASE_HPP
#define FPGASPIDriver_GTEST_BASE_HPP

#include "TesterBase.hpp"
#include "gtest/gtest.h"

// ----------------------------------------------------------------------
// Macros for typed user from port history assertions
// ----------------------------------------------------------------------

#define ASSERT_FROM_PORT_HISTORY_SIZE(size) \
  this->assertFromPortHistory_size(__FILE__, __LINE__, size)

#define ASSERT_from_Time_SIZE(size) \
  this->assert_from_Time_size(__FILE__, __LINE__, size)

#define ASSERT_from_Time(index, _time) \
  { \
    ASSERT_GT(this->fromPortHistory_Time->size(), static_cast<U32>(index)) \
    << "\n" \
    << "  File:     " << __FILE__ << "\n" \
    << "  Line:     " << __LINE__ << "\n" \
    << "  Value:    Index into history of from_Time\n" \
    << "  Expected: Less than size of history (" \
    << this->fromPortHistory_Time->size() << ")\n" \
    << "  Actual:   " << index << "\n"; \
    const FromPortEntry_Time& _e = \
      this->fromPortHistory_Time->at(index); \
    ASSERT_EQ(_time, _e.time) \
    << "\n" \
    << "  File:     " << __FILE__ << "\n" \
    << "  Line:     " << __LINE__ << "\n" \
    << "  Value:    Value of argument time at index " \
    << index \
    << " in history of from_Time\n" \
    << "  Expected: " << _time << "\n" \
    << "  Actual:   " << _e.time << "\n"; \
  }

namespace Drv {

  //! \class FPGASPIDriverGTestBase
  //! \brief Auto-generated base class for FPGASPIDriver component Google Test harness
  //!
  class FPGASPIDriverGTestBase :
    public FPGASPIDriverTesterBase
  {

    protected:

      // ----------------------------------------------------------------------
      // Construction and destruction
      // ----------------------------------------------------------------------

      //! Construct object FPGASPIDriverGTestBase
      //!
      FPGASPIDriverGTestBase(
#if FW_OBJECT_NAMES == 1
          const char *const compName, /*!< The component name*/
          const U32 maxHistorySize /*!< The maximum size of each history*/
#else
          const U32 maxHistorySize /*!< The maximum size of each history*/
#endif
      );

      //! Destroy object FPGASPIDriverGTestBase
      //!
      virtual ~FPGASPIDriverGTestBase(void);

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
      // From port: Time 
      // ----------------------------------------------------------------------

      void assert_from_Time_size(
          const char *const __ISF_callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __ISF_callSiteLineNumber, /*!< The line number of the call site*/
          const U32 size /*!< The asserted size*/
      ) const;

  };

} // end namespace Drv

#endif
