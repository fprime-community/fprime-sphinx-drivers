// ======================================================================
// \title  NORFlashDriver/test/ut/GTestBase.hpp
// \author Auto-generated
// \brief  hpp file for NORFlashDriver component Google Test harness base class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
// ======================================================================

#ifndef NORFlashDriver_GTEST_BASE_HPP
#define NORFlashDriver_GTEST_BASE_HPP

#include "TesterBase.hpp"
#include "gtest/gtest.h"

namespace Drv {

  //! \class NORFlashDriverGTestBase
  //! \brief Auto-generated base class for NORFlashDriver component Google Test harness
  //!
  class NORFlashDriverGTestBase :
    public NORFlashDriverTesterBase
  {

    protected:

      // ----------------------------------------------------------------------
      // Construction and destruction
      // ----------------------------------------------------------------------

      //! Construct object NORFlashDriverGTestBase
      //!
      NORFlashDriverGTestBase(
#if FW_OBJECT_NAMES == 1
          const char *const compName, /*!< The component name*/
          const U32 maxHistorySize /*!< The maximum size of each history*/
#else
          const U32 maxHistorySize /*!< The maximum size of each history*/
#endif
      );

      //! Destroy object NORFlashDriverGTestBase
      //!
      virtual ~NORFlashDriverGTestBase(void);

  };

} // end namespace Drv

#endif
