// ======================================================================
// \title  SPWDriver/test/ut/Tester.hpp
// \author vwong
// \brief  hpp file for SPWDriver test harness implementation class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
// ======================================================================

#ifndef TESTER_HPP
#define TESTER_HPP

#include "GTestBase.hpp"
#include "fprime-sphinx-drivers/SPWDriver/SPWDriverComponentImpl.hpp"

namespace Drv {

  class Tester :
    public SPWDriverGTestBase
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

      void testRandomRMAPCommandHeaders(U32 count);
      void testRandomRMAPReplyHeaders(U32 count);

      void testWriteRMAP(void);
      void testReadRMAP(void);
      void testRMAPErrors(void);
      void testSPWConnectionErrors(void);

    private:

      // ----------------------------------------------------------------------
      // Helper methods
      // ----------------------------------------------------------------------
      //
    private: // types

      struct RMAPSettings {
        U8 iscmd;
        U8 status;
        U8 iswrite;
        U8 verify;
        U8 ack;
        U8 incr;
        U32 dest_addr;
        U32 dest_key;
        U32 src_addr;
        U32 tid;
        U32 addr;
        U32 len;
      };

    private: // methods

      void completeTx(bool linkerr);
      void completeRx(const U8* data, const U32 dataSize, bool truncated, bool dcrc, bool hcrc, bool eep);
      void makeReplyPacket(U8* buf, const U8* data, const RMAPTransaction& t);

      //! Connect ports
      //!
      void connectPorts(void);

      //! Initialize components
      //!
      void initComponents(void);

      void buildRMAPHeaderFromVendorAPI(const RMAPSettings& settings, U8* buf, U32& resultSize);
      void buildRMAPHeaderFromCustomSerializable(const RMAPSettings& settings, U8* buf, U32& resultSize);
      void verifyRMAPHeader(const RMAPSettings& settings, const U8* buf, const U32 bufSize);
      void verifyRMAPHeaderWithVendorAPI(const RMAPSettings& settings, const U8* buf, const U32 bufSize);
      void verifyRMAPHeaderWithCustomSerializable(const RMAPSettings& settings, const U8* buf, const U32 bufSize);

    private:

      // ----------------------------------------------------------------------
      // Variables
      // ----------------------------------------------------------------------

      //! The component under test
      //!
      SPWDriverComponentImpl component;

  };

} // end namespace Drv

#endif
