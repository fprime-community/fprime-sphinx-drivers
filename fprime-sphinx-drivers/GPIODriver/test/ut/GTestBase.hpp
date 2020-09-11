// ======================================================================
// \title  GPIODriver/test/ut/GTestBase.hpp
// \author Auto-generated
// \brief  hpp file for GPIODriver component Google Test harness base class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
// ======================================================================

#ifndef GPIODriver_GTEST_BASE_HPP
#define GPIODriver_GTEST_BASE_HPP

#include "TesterBase.hpp"
#include "gtest/gtest.h"

namespace Drv {

  //! \class GPIODriverGTestBase
  //! \brief Auto-generated base class for GPIODriver component Google Test harness
  //!
  class GPIODriverGTestBase :
    public GPIODriverTesterBase
  {

    protected:

      // ----------------------------------------------------------------------
      // Construction and destruction
      // ----------------------------------------------------------------------

      //! Construct object GPIODriverGTestBase
      //!
      GPIODriverGTestBase(
#if FW_OBJECT_NAMES == 1
          const char *const compName, /*!< The component name*/
          const U32 maxHistorySize /*!< The maximum size of each history*/
#else
          const U32 maxHistorySize /*!< The maximum size of each history*/
#endif
      );

      //! Destroy object GPIODriverGTestBase
      //!
      virtual ~GPIODriverGTestBase(void);

  };

} // end namespace Drv

#endif
