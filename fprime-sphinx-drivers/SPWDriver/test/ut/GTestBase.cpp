// ======================================================================
// \title  SPWDriver/test/ut/GTestBase.cpp
// \author Auto-generated
// \brief  cpp file for SPWDriver component Google Test harness base class
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

  SPWDriverGTestBase ::
    SPWDriverGTestBase(
#if FW_OBJECT_NAMES == 1
        const char *const compName,
        const U32 maxHistorySize
#else
        const U32 maxHistorySize
#endif
    ) : 
        SPWDriverTesterBase (
#if FW_OBJECT_NAMES == 1
            compName,
#endif
            maxHistorySize
        )
  {

  }

  SPWDriverGTestBase ::
    ~SPWDriverGTestBase(void)
  {

  }

} // end namespace Drv
