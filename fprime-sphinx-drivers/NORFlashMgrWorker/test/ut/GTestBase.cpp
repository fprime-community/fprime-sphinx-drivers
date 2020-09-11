// ======================================================================
// \title  NORFlashMgrWorker/test/ut/GTestBase.cpp
// \author Auto-generated
// \brief  cpp file for NORFlashMgrWorker component Google Test harness base class
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

  NORFlashMgrWorkerGTestBase ::
    NORFlashMgrWorkerGTestBase(
#if FW_OBJECT_NAMES == 1
        const char *const compName,
        const U32 maxHistorySize
#else
        const U32 maxHistorySize
#endif
    ) : 
        NORFlashMgrWorkerTesterBase (
#if FW_OBJECT_NAMES == 1
            compName,
#endif
            maxHistorySize
        )
  {

  }

  NORFlashMgrWorkerGTestBase ::
    ~NORFlashMgrWorkerGTestBase(void)
  {

  }

  // ----------------------------------------------------------------------
  // From ports
  // ----------------------------------------------------------------------

  void NORFlashMgrWorkerGTestBase ::
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
  // From port: read
  // ----------------------------------------------------------------------

  void NORFlashMgrWorkerGTestBase ::
    assert_from_read_size(
        const char *const __ISF_callSiteFileName,
        const U32 __ISF_callSiteLineNumber,
        const U32 size
    ) const
  {
    ASSERT_EQ(size, this->fromPortHistory_read->size())
      << "\n"
      << "  File:     " << __ISF_callSiteFileName << "\n"
      << "  Line:     " << __ISF_callSiteLineNumber << "\n"
      << "  Value:    Size of history for from_read\n"
      << "  Expected: " << size << "\n"
      << "  Actual:   " << this->fromPortHistory_read->size() << "\n";
  }

  // ----------------------------------------------------------------------
  // From port: statusOut
  // ----------------------------------------------------------------------

  void NORFlashMgrWorkerGTestBase ::
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
  // From port: write
  // ----------------------------------------------------------------------

  void NORFlashMgrWorkerGTestBase ::
    assert_from_write_size(
        const char *const __ISF_callSiteFileName,
        const U32 __ISF_callSiteLineNumber,
        const U32 size
    ) const
  {
    ASSERT_EQ(size, this->fromPortHistory_write->size())
      << "\n"
      << "  File:     " << __ISF_callSiteFileName << "\n"
      << "  Line:     " << __ISF_callSiteLineNumber << "\n"
      << "  Value:    Size of history for from_write\n"
      << "  Expected: " << size << "\n"
      << "  Actual:   " << this->fromPortHistory_write->size() << "\n";
  }

} // end namespace Drv
