// ====================================================================== 
// \title  NORFlashMgrWorker/test/ut/Tester.hpp
// \author ciankc
// \brief  hpp file for NORFlashMgrWorker test harness implementation class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
// ====================================================================== 

#ifndef TESTER_HPP
#define TESTER_HPP

#include "GTestBase.hpp"
#include "fprime-sphinx-drivers/NORFlashMgrWorker/NORFlashMgrWorkerComponentImpl.hpp"
#include "fprime-sphinx-drivers/Util/SphinxDrvUtil.hpp"
#include "fprime-sphinx-drivers/Util/SphinxDrvReg.hpp"
#include <fprime-sphinx-drivers/NORFlashManager/bootloader_defs.hpp>

namespace Drv {

  class Tester :
    public NORFlashMgrWorkerGTestBase
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
      // Handlers for typed from ports
      // ----------------------------------------------------------------------

      //! Handler for from_read
      //!
      I8 from_read_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          U32 dest, 
          U8 *data 
      );

      //! Handler for from_statusOut
      //!
      void from_statusOut_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          I8 done, 
          U32 context1, 
          U32 context2 
      );

      //! Handler for from_write
      //!
      I8 from_write_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          U32 dest_addr, 
          U8 src 
      );

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
      NORFlashMgrWorkerComponentImpl component;

  };

} // end namespace Drv

#endif
