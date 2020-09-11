// ======================================================================
// \title  ADC/test/ut/Tester.hpp
// \author ortega
// \brief  hpp file for ADC test harness implementation class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
// ======================================================================

#ifndef TESTER_HPP
#define TESTER_HPP

#include "GTestBase.hpp"
#include "fprime-sphinx-drivers/ADC/ADCComponentImpl.hpp"
#include "fprime-sphinx-drivers/Util/SphinxDrvReg.hpp"

namespace Drv {

  class Tester :
    public ADCGTestBase
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

      //! test getting and sending tlm
      //!
      void testTelemetry(void);

      //! test setting rate
      //!
      void testSetRate(void);

      //! test setting run
      //!
      void testSetRun(void);

      //! test setting power ctrl
      //!
      void testSetPwrCtrl(void);

      //! test timeout of ADC tlm_rdy bit
      //!
      void testTimeOut(void);

      //! test set timeout
      //!
      void testSetTimeOut(void);

      //! test ping ports
      void pingTest(void);

    private:

      // ----------------------------------------------------------------------
      // Handlers for typed from ports
      // ----------------------------------------------------------------------

      //! Handler for from_PingResponse
      //!
      void from_PingResponse_handler(
          const NATIVE_INT_TYPE portNum, //!< The port number
          U32 key //!< Value to return to pinger
      );

      //! Handler for from_adcOut
      //!
      void from_adcOut_handler(
          const NATIVE_INT_TYPE portNum, //!< The port number
          Fw::Time timetag,
          U16 apid,
          Fw::FileBuffer &data,
          U16 apid_rec
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
      void dispatchOne(void);
      void dispatchAll(void);
      void clearAndDispatch(void);

    private:

      // ----------------------------------------------------------------------
      // Variables
      // ----------------------------------------------------------------------

      //! The component under test
      //!
      ADCComponentImpl component;

  };

} // end namespace Drv

#endif
