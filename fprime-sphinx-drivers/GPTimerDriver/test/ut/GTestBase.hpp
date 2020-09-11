// ======================================================================
// \title  GPTimerDriver/test/ut/GTestBase.hpp
// \author Auto-generated
// \brief  hpp file for GPTimerDriver component Google Test harness base class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
// ======================================================================

#ifndef GPTimerDriver_GTEST_BASE_HPP
#define GPTimerDriver_GTEST_BASE_HPP

#include "TesterBase.hpp"
#include "gtest/gtest.h"

namespace Drv {

  //! \class GPTimerDriverGTestBase
  //! \brief Auto-generated base class for GPTimerDriver component Google Test harness
  //!
  class GPTimerDriverGTestBase :
    public GPTimerDriverTesterBase
  {

    protected:

      // ----------------------------------------------------------------------
      // Construction and destruction
      // ----------------------------------------------------------------------

      //! Construct object GPTimerDriverGTestBase
      //!
      GPTimerDriverGTestBase(
#if FW_OBJECT_NAMES == 1
          const char *const compName, /*!< The component name*/
          const U32 maxHistorySize /*!< The maximum size of each history*/
#else
          const U32 maxHistorySize /*!< The maximum size of each history*/
#endif
      );

      //! Destroy object GPTimerDriverGTestBase
      //!
      virtual ~GPTimerDriverGTestBase(void);

  };

} // end namespace Drv

#endif
