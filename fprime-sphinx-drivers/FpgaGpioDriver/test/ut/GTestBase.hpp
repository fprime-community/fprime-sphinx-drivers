// ======================================================================
// \title  FpgaGpioDriver/test/ut/GTestBase.hpp
// \author Auto-generated
// \brief  hpp file for FpgaGpioDriver component Google Test harness base class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
// ======================================================================

#ifndef FpgaGpioDriver_GTEST_BASE_HPP
#define FpgaGpioDriver_GTEST_BASE_HPP

#include "TesterBase.hpp"
#include "gtest/gtest.h"

namespace Drv {

  //! \class FpgaGpioDriverGTestBase
  //! \brief Auto-generated base class for FpgaGpioDriver component Google Test harness
  //!
  class FpgaGpioDriverGTestBase :
    public FpgaGpioDriverTesterBase
  {

    protected:

      // ----------------------------------------------------------------------
      // Construction and destruction
      // ----------------------------------------------------------------------

      //! Construct object FpgaGpioDriverGTestBase
      //!
      FpgaGpioDriverGTestBase(
#if FW_OBJECT_NAMES == 1
          const char *const compName, /*!< The component name*/
          const U32 maxHistorySize /*!< The maximum size of each history*/
#else
          const U32 maxHistorySize /*!< The maximum size of each history*/
#endif
      );

      //! Destroy object FpgaGpioDriverGTestBase
      //!
      virtual ~FpgaGpioDriverGTestBase(void);

  };

} // end namespace Drv

#endif
