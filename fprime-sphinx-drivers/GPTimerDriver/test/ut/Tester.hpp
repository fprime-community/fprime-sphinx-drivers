// ====================================================================== 
// \title  GPTimerDriver/test/ut/Tester.hpp
// \author ciankc
// \brief  hpp file for GPTimerDriver test harness implementation class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
// ====================================================================== 

#ifndef TESTER_HPP
#define TESTER_HPP

#include "GTestBase.hpp"
#include "fprime-sphinx-drivers/GPTimerDriver/GPTimerDriverComponentImpl.hpp"
#include "fprime-sphinx-drivers/Util/SphinxDrvReg.hpp"

namespace Drv {

  class Tester :
    public GPTimerDriverGTestBase
  {

      // ----------------------------------------------------------------------
      // Construction and destruction
      // ----------------------------------------------------------------------

    public:

      //! Construct object Tester
      //!
      Tester(const char*, U32, U32, 
	   bool, bool, U32, U32, U32, 
	   bool, bool, U32, U32, U32, 
	   bool, bool, U32, U32, U32, 
	   bool, bool, U32, U32, U32);

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
      GPTimerDriverComponentImpl component;

  };

} // end namespace Drv

#endif
