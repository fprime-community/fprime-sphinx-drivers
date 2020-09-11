// ======================================================================
// \title  SPIDriverGeneric/test/ut/GTestBase.hpp
// \author Auto-generated
// \brief  hpp file for SPIDriverGeneric component Google Test harness base class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
// ======================================================================

#ifndef SPIDriverGeneric_GTEST_BASE_HPP
#define SPIDriverGeneric_GTEST_BASE_HPP

#include "TesterBase.hpp"
#include "gtest/gtest.h"

// ----------------------------------------------------------------------
// Macros for typed user from port history assertions
// ----------------------------------------------------------------------

#define ASSERT_FROM_PORT_HISTORY_SIZE(size) \
  this->assertFromPortHistory_size(__FILE__, __LINE__, size)

#define ASSERT_from_timeCaller_SIZE(size) \
  this->assert_from_timeCaller_size(__FILE__, __LINE__, size)

#define ASSERT_from_timeCaller(index, _time) \
  { \
    ASSERT_GT(this->fromPortHistory_timeCaller->size(), static_cast<U32>(index)) \
    << "\n" \
    << "  File:     " << __FILE__ << "\n" \
    << "  Line:     " << __LINE__ << "\n" \
    << "  Value:    Index into history of from_timeCaller\n" \
    << "  Expected: Less than size of history (" \
    << this->fromPortHistory_timeCaller->size() << ")\n" \
    << "  Actual:   " << index << "\n"; \
    const FromPortEntry_timeCaller& _e = \
      this->fromPortHistory_timeCaller->at(index); \
    ASSERT_EQ(_time, _e.time) \
    << "\n" \
    << "  File:     " << __FILE__ << "\n" \
    << "  Line:     " << __LINE__ << "\n" \
    << "  Value:    Value of argument time at index " \
    << index \
    << " in history of from_timeCaller\n" \
    << "  Expected: " << _time << "\n" \
    << "  Actual:   " << _e.time << "\n"; \
  }

namespace Drv {

  //! \class SPIDriverGenericGTestBase
  //! \brief Auto-generated base class for SPIDriverGeneric component Google Test harness
  //!
  class SPIDriverGenericGTestBase :
    public SPIDriverGenericTesterBase
  {

    protected:

      // ----------------------------------------------------------------------
      // Construction and destruction
      // ----------------------------------------------------------------------

      //! Construct object SPIDriverGenericGTestBase
      //!
      SPIDriverGenericGTestBase(
#if FW_OBJECT_NAMES == 1
          const char *const compName, /*!< The component name*/
          const U32 maxHistorySize /*!< The maximum size of each history*/
#else
          const U32 maxHistorySize /*!< The maximum size of each history*/
#endif
      );

      //! Destroy object SPIDriverGenericGTestBase
      //!
      virtual ~SPIDriverGenericGTestBase(void);

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
      // From port: timeCaller 
      // ----------------------------------------------------------------------

      void assert_from_timeCaller_size(
          const char *const __ISF_callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __ISF_callSiteLineNumber, /*!< The line number of the call site*/
          const U32 size /*!< The asserted size*/
      ) const;

  };

} // end namespace Drv

#endif
