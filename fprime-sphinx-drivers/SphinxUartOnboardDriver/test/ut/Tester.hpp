// ====================================================================== 
// \title  SphinxUartOnboardDriver/test/ut/Tester.hpp
// \author ciankc
// \brief  hpp file for SphinxUartOnboardDriver test harness implementation class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
// ====================================================================== 

#ifndef TESTER_HPP
#define TESTER_HPP

#include "GTestBase.hpp"
#include "fprime-sphinx-drivers/SphinxUartOnboardDriver/SphinxUartOnboardDriverComponentImpl.hpp"
#include "fprime-sphinx-drivers/Util/SphinxDrvReg.hpp"

namespace Drv {

  class Tester :
    public SphinxUartOnboardDriverGTestBase
  {

      // ----------------------------------------------------------------------
      // Construction and destruction
      // ----------------------------------------------------------------------

    public:

      //! Construct object Tester
      //!
      Tester(void);

      //! Destroy object Tester
      //!
      ~Tester(void);

    public:

      // ---------------------------------------------------------------------- 
      // Tests
      // ---------------------------------------------------------------------- 

      //! To do
      //!
      void toDo(void);

    private:

      // ----------------------------------------------------------------------
      // Helper methods
      // ----------------------------------------------------------------------

      //! Connect ports
      //!
      void connectPorts(void);

      //! Initialize components
      //!
      void initComponents(void);
      void statusQuery(void);

    protected:

      // ----------------------------------------------------------------------
      // Variables
      // ----------------------------------------------------------------------

      //! The component under test
      //!
      SphinxUartOnboardDriverComponentImpl component;

  };

} // end namespace Drv

#endif
