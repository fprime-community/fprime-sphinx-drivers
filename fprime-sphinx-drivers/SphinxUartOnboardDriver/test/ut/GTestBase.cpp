// ======================================================================
// \title  SphinxUartOnboardDriver/test/ut/GTestBase.cpp
// \author Auto-generated
// \brief  cpp file for SphinxUartOnboardDriver component Google Test harness base class
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

  SphinxUartOnboardDriverGTestBase ::
    SphinxUartOnboardDriverGTestBase(
#if FW_OBJECT_NAMES == 1
        const char *const compName,
        const U32 maxHistorySize
#else
        const U32 maxHistorySize
#endif
    ) :
        SphinxUartOnboardDriverTesterBase (
#if FW_OBJECT_NAMES == 1
            compName,
#endif
            maxHistorySize
        )
  {

  }

  SphinxUartOnboardDriverGTestBase ::
    ~SphinxUartOnboardDriverGTestBase(void)
  {

  }

  // ----------------------------------------------------------------------
  // Events
  // ----------------------------------------------------------------------

  void SphinxUartOnboardDriverGTestBase ::
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
  // Event: UOBD_HardwareInitStatusError
  // ----------------------------------------------------------------------

  void SphinxUartOnboardDriverGTestBase ::
    assertEvents_UOBD_HardwareInitStatusError_size(
        const char *const __callSiteFileName,
        const U32 __callSiteLineNumber,
        const U32 size
    ) const
  {
    ASSERT_EQ(size, this->eventHistory_UOBD_HardwareInitStatusError->size())
      << "\n"
      << "  File:     " << __callSiteFileName << "\n"
      << "  Line:     " << __callSiteLineNumber << "\n"
      << "  Value:    Size of history for event UOBD_HardwareInitStatusError\n"
      << "  Expected: " << size << "\n"
      << "  Actual:   " << this->eventHistory_UOBD_HardwareInitStatusError->size() << "\n";
  }

  void SphinxUartOnboardDriverGTestBase ::
    assertEvents_UOBD_HardwareInitStatusError(
        const char *const __callSiteFileName,
        const U32 __callSiteLineNumber,
        const U32 __index,
        const U8 bitIndex,
        const U8 reported,
        const U8 expected,
        const char *const bitName
    ) const
  {
    ASSERT_GT(this->eventHistory_UOBD_HardwareInitStatusError->size(), __index)
      << "\n"
      << "  File:     " << __callSiteFileName << "\n"
      << "  Line:     " << __callSiteLineNumber << "\n"
      << "  Value:    Index into history of event UOBD_HardwareInitStatusError\n"
      << "  Expected: Less than size of history ("
      << this->eventHistory_UOBD_HardwareInitStatusError->size() << ")\n"
      << "  Actual:   " << __index << "\n";
    const EventEntry_UOBD_HardwareInitStatusError& e =
      this->eventHistory_UOBD_HardwareInitStatusError->at(__index);
    ASSERT_EQ(bitIndex, e.bitIndex)
      << "\n"
      << "  File:     " << __callSiteFileName << "\n"
      << "  Line:     " << __callSiteLineNumber << "\n"
      << "  Value:    Value of argument bitIndex at index "
      << __index
      << " in history of event UOBD_HardwareInitStatusError\n"
      << "  Expected: " << bitIndex << "\n"
      << "  Actual:   " << e.bitIndex << "\n";
    ASSERT_EQ(reported, e.reported)
      << "\n"
      << "  File:     " << __callSiteFileName << "\n"
      << "  Line:     " << __callSiteLineNumber << "\n"
      << "  Value:    Value of argument reported at index "
      << __index
      << " in history of event UOBD_HardwareInitStatusError\n"
      << "  Expected: " << reported << "\n"
      << "  Actual:   " << e.reported << "\n";
    ASSERT_EQ(expected, e.expected)
      << "\n"
      << "  File:     " << __callSiteFileName << "\n"
      << "  Line:     " << __callSiteLineNumber << "\n"
      << "  Value:    Value of argument expected at index "
      << __index
      << " in history of event UOBD_HardwareInitStatusError\n"
      << "  Expected: " << expected << "\n"
      << "  Actual:   " << e.expected << "\n";
    ASSERT_STREQ(bitName, e.bitName.toChar())
      << "\n"
      << "  File:     " << __callSiteFileName << "\n"
      << "  Line:     " << __callSiteLineNumber << "\n"
      << "  Value:    Value of argument bitName at index "
      << __index
      << " in history of event UOBD_HardwareInitStatusError\n"
      << "  Expected: " << bitName << "\n"
      << "  Actual:   " << e.bitName.toChar() << "\n";
  }

  // ----------------------------------------------------------------------
  // Event: UOBD_HardwareInitPurgeError
  // ----------------------------------------------------------------------

  void SphinxUartOnboardDriverGTestBase ::
    assertEvents_UOBD_HardwareInitPurgeError_size(
        const char *const __callSiteFileName,
        const U32 __callSiteLineNumber,
        const U32 size
    ) const
  {
    ASSERT_EQ(size, this->eventsSize_UOBD_HardwareInitPurgeError)
      << "\n"
      << "  File:     " << __callSiteFileName << "\n"
      << "  Line:     " << __callSiteLineNumber << "\n"
      << "  Value:    Size of history for event UOBD_HardwareInitPurgeError\n"
      << "  Expected: " << size << "\n"
      << "  Actual:   " << this->eventsSize_UOBD_HardwareInitPurgeError << "\n";
  }

  // ----------------------------------------------------------------------
  // Event: UOBD_BUFF_WRAP
  // ----------------------------------------------------------------------

  void SphinxUartOnboardDriverGTestBase ::
    assertEvents_UOBD_BUFF_WRAP_size(
        const char *const __callSiteFileName,
        const U32 __callSiteLineNumber,
        const U32 size
    ) const
  {
    ASSERT_EQ(size, this->eventsSize_UOBD_BUFF_WRAP)
      << "\n"
      << "  File:     " << __callSiteFileName << "\n"
      << "  Line:     " << __callSiteLineNumber << "\n"
      << "  Value:    Size of history for event UOBD_BUFF_WRAP\n"
      << "  Expected: " << size << "\n"
      << "  Actual:   " << this->eventsSize_UOBD_BUFF_WRAP << "\n";
  }

} // end namespace Drv
