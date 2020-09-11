// ======================================================================
// \title  SPWDriver/test/ut/GTestBase.hpp
// \author Auto-generated
// \brief  hpp file for SPWDriver component Google Test harness base class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
// ======================================================================

#ifndef SPWDriver_GTEST_BASE_HPP
#define SPWDriver_GTEST_BASE_HPP

#include "TesterBase.hpp"
#include "gtest/gtest.h"

namespace Drv {

  //! \class SPWDriverGTestBase
  //! \brief Auto-generated base class for SPWDriver component Google Test harness
  //!
  class SPWDriverGTestBase :
    public SPWDriverTesterBase
  {

    protected:

      // ----------------------------------------------------------------------
      // Construction and destruction
      // ----------------------------------------------------------------------

      //! Construct object SPWDriverGTestBase
      //!
      SPWDriverGTestBase(
#if FW_OBJECT_NAMES == 1
          const char *const compName, /*!< The component name*/
          const U32 maxHistorySize /*!< The maximum size of each history*/
#else
          const U32 maxHistorySize /*!< The maximum size of each history*/
#endif
      );

      //! Destroy object SPWDriverGTestBase
      //!
      virtual ~SPWDriverGTestBase(void);

  };

} // end namespace Drv

#endif
