// ======================================================================
// \title  SPIDriverGeneric/test/ut/Tester.hpp
// \author bsoudry
// \brief  hpp file for SPIDriverGeneric test harness implementation class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
// ======================================================================

#ifndef TESTER_HPP
#define TESTER_HPP

#include "GTestBase.hpp"
#include "fprime-sphinx-drivers/SPIDriverGeneric/SPIDriverGenericComponentImpl.hpp"
#include "fprime-sphinx-drivers/SPIDriverGeneric/SPIDriverGenericErrorCodes.hpp"
#include "fprime-sphinx-drivers/Random/Random.hpp"

namespace Drv {

  class Tester :
    public SPIDriverGenericGTestBase
  {

      // ----------------------------------------------------------------------
      // Construction and destruction
      // ----------------------------------------------------------------------

    public:

      //! Construct object Tester
      //!
      Tester(void);
      Tester(const char* compName,
	   U8 loopback_mode,
	   U8 clock_polarity,
	   U8 clock_phase,
	   U8 div_clock_16,
	   U8 reverse_mode,
	   U8 word_len,
	   U8 prescale_modulus,
	   U8 prescale_modulus_factor,
	   U8 clock_gap);

      //! Destroy object Tester
      //!
      ~Tester(void);

    public:

      // ----------------------------------------------------------------------
      // Tests
      // ----------------------------------------------------------------------
      void testClaimUnclaimOK(void);
      void testDoubleClaim(void);
      void testDoubleUnclaim(void);
      void testInitOK(void);
      void testConfigureOK(void);
      void testConfigureNotOwner(void);
      void testRWNotOwner(void);
      void testConstructor(void);

    private:

      // ----------------------------------------------------------------------
      // Handlers for typed from ports
      // ----------------------------------------------------------------------

      //! Handler for from_timeCaller
      //!
      void from_timeCaller_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          Fw::Time &time /*!< The U32 cmd argument*/
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
      SPIDriverGenericComponentImpl component;
  };

} // end namespace Drv

#endif
