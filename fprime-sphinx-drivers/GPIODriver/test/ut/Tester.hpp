// ====================================================================== 
// \title  GPIODriver/test/ut/Tester.hpp
// \author ciankc
// \brief  hpp file for GPIODriver test harness implementation class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
// ====================================================================== 

#ifndef TESTER_HPP
#define TESTER_HPP

#include "GTestBase.hpp"
#include "fprime-sphinx-drivers/GPIODriver/GPIODriverComponentImpl.hpp"
#include "fprime-sphinx-drivers/GPIODriver/test/ut/GPIODriverInterrupt.hpp"
#include "fprime-sphinx-drivers/Util/SphinxDrvReg.hpp"

namespace Drv {

  class Tester :
    public GPIODriverGTestBase
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

    protected:

      // ----------------------------------------------------------------------
      // Variables
      // ----------------------------------------------------------------------

      //! The component under test
      //!
      GPIODriverComponentImpl component;
      GPIODriverInterrupt handler;

  };

} // end namespace Drv

#endif
