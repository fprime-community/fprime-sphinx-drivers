// ====================================================================== 
// \title  SPWManager/test/ut/Tester.hpp
// \author vwong
// \brief  hpp file for SPWManager test harness implementation class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
// ====================================================================== 

#ifndef TESTER_HPP
#define TESTER_HPP

#include "GTestBase.hpp"
#include "fprime-sphinx-drivers/SPWManager/SPWManagerComponentImpl.hpp"
#include "fprime-sphinx-drivers/Util/SphinxDrvReg.hpp"

namespace Drv {

  class Tester :
    public SPWManagerGTestBase
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

      void testPing(void);
      void testSyncReadWrite(void);
      void testAsyncReadWrite(void);
      void testAsyncDmaRead(void);
      void testHugeRead(void);
      void testHugeWrite(void);
      void testMiscRmapSettings(void);
      void testMiscErrors(void);
      void testSPWErrors(void);
      void testRmapCommands(void);
      void testRmapSetParamCommand(void);
      void testRmapSetParamCommandErrors(void);
      void testResetLinkCommand(void);
      void testResetLinkPort(void);

    private:

      // ----------------------------------------------------------------------
      // Handlers for typed from ports
      // ----------------------------------------------------------------------

      //! Handler for from_driverWriteRMAP
      //!
      I32 from_driverWriteRMAP_handler(
          const NATIVE_INT_TYPE portNum, //!< The port number
          U8 dest_addr, 
          U8 dest_key, 
          U32 write_addr, 
          U8 *buf_ptr, 
          U32 num_bytes, 
          U8 increment, 
          U8 verify, 
          U8 acknowledge 
      );

      //! Handler for from_statusOut
      //!
      void from_statusOut_handler(
          const NATIVE_INT_TYPE portNum, //!< The port number
          I32 spwStatus 
      );

      //! Handler for from_PingResponse
      //!
      void from_PingResponse_handler(
          const NATIVE_INT_TYPE portNum, //!< The port number
          U32 key //!< Value to return to pinger
      );

      //! Handler for from_driverReset
      //!
      I32 from_driverReset_handler(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

      //! Handler for from_driverReadRMAP
      //!
      I32 from_driverReadRMAP_handler(
          const NATIVE_INT_TYPE portNum, //!< The port number
          U8 dest_addr, 
          U8 dest_key, 
          U32 read_addr, 
          U8 *buf_ptr, 
          U32 num_bytes, 
          U8 increment 
      );

      //! Handler for from_driverGetStatus
      //!
      I32 from_driverGetStatus_handler(
          const NATIVE_INT_TYPE portNum //!< The port number
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

      //! Sets the amount of cycles needed to complete a spacewire command
      //!
      void setSpacewireDelay(const U32 send, const U32 receive);

    private:

      // ----------------------------------------------------------------------
      // Variables
      // ----------------------------------------------------------------------

      //! The component under test
      //!
      SPWManagerComponentImpl component;

      //! Settings
      //!
      static const U32 pingKey;
      static const U8 spwAddr;
      static const U8 spwKey;

      //! Variables
      //!
      U32 pingResponses;
      bool spwDriverExecuting;
      bool spwDriverReceivedReset;
      U32 spwDriverSendCounter;
      U32 spwDriverReceiveCounter;
      U32 spwDriverSendBound;
      U32 spwDriverReceiveBound;
      bool spwDriverEEPError;
      bool spwDriverInitError;
      bool spwDriverDiscError;

      //! Buffers and their true address map (needed for after truncation to U32)
      U8 buf1[1024];
      U8 buf2[1024];
      U8 buf3[1024];
      U32 val1;
      U32 val2;
      U32 val3;
      POINTER_CAST addressPrefix;

  };

} // end namespace Drv

#endif
