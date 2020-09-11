// ======================================================================
// \title  SphinxUartOnboardDriver/test/ut/GTestBase.hpp
// \author Auto-generated
// \brief  hpp file for SphinxUartOnboardDriver component Google Test harness base class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
//
// ======================================================================

#ifndef SphinxUartOnboardDriver_GTEST_BASE_HPP
#define SphinxUartOnboardDriver_GTEST_BASE_HPP

#include "TesterBase.hpp"
#include "gtest/gtest.h"

// ----------------------------------------------------------------------
// Macros for event history assertions
// ----------------------------------------------------------------------

#define ASSERT_EVENTS_SIZE(size) \
  this->assertEvents_size(__FILE__, __LINE__, size)

#define ASSERT_EVENTS_UOBD_HardwareInitStatusError_SIZE(size) \
  this->assertEvents_UOBD_HardwareInitStatusError_size(__FILE__, __LINE__, size)

#define ASSERT_EVENTS_UOBD_HardwareInitStatusError(index, _bitIndex, _reported, _expected, _bitName) \
  this->assertEvents_UOBD_HardwareInitStatusError(__FILE__, __LINE__, index, _bitIndex, _reported, _expected, _bitName)

#define ASSERT_EVENTS_UOBD_HardwareInitPurgeError_SIZE(size) \
  this->assertEvents_UOBD_HardwareInitPurgeError_size(__FILE__, __LINE__, size)

#define ASSERT_EVENTS_UOBD_BUFF_WRAP_SIZE(size) \
  this->assertEvents_UOBD_BUFF_WRAP_size(__FILE__, __LINE__, size)

namespace Drv {

  //! \class SphinxUartOnboardDriverGTestBase
  //! \brief Auto-generated base class for SphinxUartOnboardDriver component Google Test harness
  //!
  class SphinxUartOnboardDriverGTestBase :
    public SphinxUartOnboardDriverTesterBase
  {

    protected:

      // ----------------------------------------------------------------------
      // Construction and destruction
      // ----------------------------------------------------------------------

      //! Construct object SphinxUartOnboardDriverGTestBase
      //!
      SphinxUartOnboardDriverGTestBase(
#if FW_OBJECT_NAMES == 1
          const char *const compName, /*!< The component name*/
          const U32 maxHistorySize /*!< The maximum size of each history*/
#else
          const U32 maxHistorySize /*!< The maximum size of each history*/
#endif
      );

      //! Destroy object SphinxUartOnboardDriverGTestBase
      //!
      virtual ~SphinxUartOnboardDriverGTestBase(void);

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
      // Event: UOBD_HardwareInitStatusError
      // ----------------------------------------------------------------------

      void assertEvents_UOBD_HardwareInitStatusError_size(
          const char *const __callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __callSiteLineNumber, /*!< The line number of the call site*/
          const U32 size /*!< The asserted size*/
      ) const;

      void assertEvents_UOBD_HardwareInitStatusError(
          const char *const __callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __callSiteLineNumber, /*!< The line number of the call site*/
          const U32 __index, /*!< The index*/
          const U8 bitIndex, /*!< A zero-indexed bit in the status register*/
          const U8 reported, /*!< Reported condition*/
          const U8 expected, /*!< Expected condition*/
          const char *const bitName /*!< The name of the bit*/
      ) const;

    protected:

      // ----------------------------------------------------------------------
      // Event: UOBD_HardwareInitPurgeError
      // ----------------------------------------------------------------------

      void assertEvents_UOBD_HardwareInitPurgeError_size(
          const char *const __callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __callSiteLineNumber, /*!< The line number of the call site*/
          const U32 size /*!< The asserted size*/
      ) const;

    protected:

      // ----------------------------------------------------------------------
      // Event: UOBD_BUFF_WRAP
      // ----------------------------------------------------------------------

      void assertEvents_UOBD_BUFF_WRAP_size(
          const char *const __callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __callSiteLineNumber, /*!< The line number of the call site*/
          const U32 size /*!< The asserted size*/
      ) const;

  };

} // end namespace Drv

#endif
