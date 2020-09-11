// ====================================================================== 
// \title  SPWDriver.hpp
// \author vwong
// \brief  cpp file for SPWDriver test harness implementation class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
// ====================================================================== 

#include "Tester.hpp"
#include "fprime-sphinx-drivers/SPWDriver/SPWStatus.hpp"

// defined in spwapi_stubs.c
extern struct spwregs core0default;

#define INSTANCE 0
#define MAX_HISTORY_SIZE 10

namespace Drv {

  // ----------------------------------------------------------------------
  // Construction and destruction 
  // ----------------------------------------------------------------------

  Tester ::
    Tester(void) : 
#if FW_OBJECT_NAMES == 1
      SPWDriverGTestBase("Tester", MAX_HISTORY_SIZE),
      component("SPWDriver", 0, 0x20, 100)
#else
      SPWDriverGTestBase(MAX_HISTORY_SIZE),
      component(0, 0)
#endif
  {
    this->initComponents();
    this->connectPorts();
  }

  Tester ::
    ~Tester(void) 
  {
    
  }

  // ----------------------------------------------------------------------
  // Tests 
  // ----------------------------------------------------------------------

  void Tester ::
    testRandomRMAPCommandHeaders(U32 count) 
  {
    // seed
    time_t seed = time(0);
    srand(seed);
    std::cout << "seed: " << seed << "\n";

    // iterate
    for (U32 i = 0; i < count; i++) {
      RMAPSettings rs;
      rs.iscmd = 1;
      rs.iswrite = rand() & 0x1;
      rs.verify = rs.iswrite ? (rand() & 0x1) : 0;
      rs.ack = rs.iswrite ? (rand() & 0x1) : 1;
      rs.incr = rand() & 0x1;
      rs.dest_addr = rand() & 0xff;
      rs.dest_key = rand() & 0xff;
      rs.src_addr = rand() & 0xff;
      rs.tid = rand() & 0xffff;
      rs.addr = rand();
      rs.len = rand() & 0xffffff;

      // build header from vendor API
      U32 vHdrSize = 0;
      U8 vHdrBuf[1024];
      ASSERT_NO_FATAL_FAILURE(buildRMAPHeaderFromVendorAPI(rs, vHdrBuf, vHdrSize));

      // test that values are as expected
      ASSERT_NO_FATAL_FAILURE(verifyRMAPHeader(rs, vHdrBuf, vHdrSize));
      ASSERT_NO_FATAL_FAILURE(verifyRMAPHeaderWithVendorAPI(rs, vHdrBuf, vHdrSize));
      ASSERT_NO_FATAL_FAILURE(verifyRMAPHeaderWithCustomSerializable(rs, vHdrBuf, vHdrSize));

      // build header from custom serializable
      U32 cHdrSize = 0;
      U8 cHdrBuf[1024];
      ASSERT_NO_FATAL_FAILURE(buildRMAPHeaderFromCustomSerializable(rs, cHdrBuf, cHdrSize));

      // test that values are as expected
      ASSERT_NO_FATAL_FAILURE(verifyRMAPHeader(rs, cHdrBuf, cHdrSize));
      ASSERT_NO_FATAL_FAILURE(verifyRMAPHeaderWithVendorAPI(rs, cHdrBuf, cHdrSize));
      ASSERT_NO_FATAL_FAILURE(verifyRMAPHeaderWithCustomSerializable(rs, cHdrBuf, cHdrSize));

      // two headers should be exactly the same
      ASSERT_EQ(vHdrSize, cHdrSize);
      for (U32 i = 0; i < vHdrSize; i++) {
        ASSERT_EQ(vHdrBuf[i], cHdrBuf[i]) << "byte: " << i;
      }
    }
  }

  void Tester ::
    testRandomRMAPReplyHeaders(U32 count) 
  {
    // seed
    time_t seed = time(0);
    srand(seed);
    std::cout << "seed: " << seed << "\n";

    // iterate
    for (U32 i = 0; i < count; i++) {
      RMAPSettings rs;
      rs.iscmd = 0;
      rs.iswrite = rand() & 0x1;
      rs.verify = rs.iswrite ? (rand() & 0x1) : 0;
      rs.ack = 1;
      rs.incr = rand() & 0x1;
      rs.status = rand() % 13;
      rs.dest_addr = rand() & 0xff;
      rs.src_addr = rand() & 0xff;
      rs.tid = rand() & 0xffff;
      rs.len = rand() & 0xffffff;

      // build header from vendor API
      U32 vHdrSize = 0;
      U8 vHdrBuf[1024];
      ASSERT_NO_FATAL_FAILURE(buildRMAPHeaderFromVendorAPI(rs, vHdrBuf, vHdrSize));

      // test that values are as expected
      ASSERT_NO_FATAL_FAILURE(verifyRMAPHeader(rs, vHdrBuf, vHdrSize));
      ASSERT_NO_FATAL_FAILURE(verifyRMAPHeaderWithVendorAPI(rs, vHdrBuf, vHdrSize));
      ASSERT_NO_FATAL_FAILURE(verifyRMAPHeaderWithCustomSerializable(rs, vHdrBuf, vHdrSize));

      // build header from custom serializable
      U32 cHdrSize = 0;
      U8 cHdrBuf[1024];
      ASSERT_NO_FATAL_FAILURE(buildRMAPHeaderFromCustomSerializable(rs, cHdrBuf, cHdrSize));

      // test that values are as expected
      ASSERT_NO_FATAL_FAILURE(verifyRMAPHeader(rs, cHdrBuf, cHdrSize));
      ASSERT_NO_FATAL_FAILURE(verifyRMAPHeaderWithVendorAPI(rs, cHdrBuf, cHdrSize));
      ASSERT_NO_FATAL_FAILURE(verifyRMAPHeaderWithCustomSerializable(rs, cHdrBuf, cHdrSize));

      // two headers should be exactly the same
      ASSERT_EQ(vHdrSize, cHdrSize);
      for (U32 i = 0; i < vHdrSize; i++) {
        ASSERT_EQ(vHdrBuf[i], cHdrBuf[i]) << "byte: " << i;
      }
    }
  }

  void Tester ::
    testWriteRMAP(void) 
  {
    const U8 destAddr = 0x80;
    const U8 destKey = 0x12;
    const U8 targetAddr = 0x30;
    const U8 increment = 1;
    const U8 verify = 0;
    const U8 acknowledge = 1;
    U8 data[] = {1,2,3,4};
    U8 reply[13];

    I32 status = 0;

    // invoke write, only sends command so shouldn't fail
    status = this->invoke_to_writeRMAP(0, destAddr, destKey, targetAddr, data, sizeof(data), increment, verify, acknowledge);
    ASSERT_EQ(status, 0) << status;

    // status should be sending
    status = this->invoke_to_getStatus(0);
    ASSERT_EQ(status, SPW_STATUS_SENDING) << status;

    // complete the tx
    completeTx(false);

    // status should be receiving (write reply)
    status = this->invoke_to_getStatus(0);
    ASSERT_EQ(status, SPW_STATUS_RECEIVING) << status;

    // complete the rx
    makeReplyPacket(reply, NULL, this->component.m_transaction);
    completeRx(reply, sizeof(reply), false, false, false, false);

    // status should be done
    status = this->invoke_to_getStatus(0);
    ASSERT_EQ(status, SPW_STATUS_SUCCESS) << status;

    // invoking another write should still succeed
    U16 prevTransactionID = this->component.m_tid;
    status = this->invoke_to_writeRMAP(0, destAddr, destKey, targetAddr, data, sizeof(data), increment, verify, acknowledge);
    ASSERT_EQ(status, 0) << status;
    completeTx(false);
    makeReplyPacket(reply, NULL, this->component.m_transaction);
    completeRx(reply, sizeof(reply), false, false, false, false);
    status = this->invoke_to_getStatus(0);
    ASSERT_EQ(status, SPW_STATUS_SUCCESS) << status;
    ASSERT_NE(prevTransactionID, this->component.m_tid); // should change transaction id
  }

  void Tester ::
    testReadRMAP(void) 
  {
    const U8 destAddr = 0x80;
    const U8 destKey = 0x12;
    const U8 targetAddr = 0x30;
    const U8 increment = 1;
    U8 data[] = {1,2,3,4};
    U8 buf[13 + sizeof(data)];
    U8 reply[13 + sizeof(data)];

    I32 status = 0;

    // invoke read, only sends command so shouldn't fail
    status = this->invoke_to_readRMAP(0, destAddr, destKey, targetAddr, buf, sizeof(data), increment);
    ASSERT_EQ(status, 0) << status;

    // status should be sending
    status = this->invoke_to_getStatus(0);
    ASSERT_EQ(status, SPW_STATUS_SENDING) << status;

    // complete the tx
    completeTx(false);

    // status should be receiving
    status = this->invoke_to_getStatus(0);
    ASSERT_EQ(status, SPW_STATUS_RECEIVING) << status;

    // complete the rx
    makeReplyPacket(reply, data, this->component.m_transaction);
    completeRx(reply, sizeof(reply), false, false, false, false);

    // status should be done
    status = this->invoke_to_getStatus(0);
    ASSERT_EQ(status, SPW_STATUS_SUCCESS) << status;

    // data should be as expected
    I32 cmp = memcmp(buf, reply, sizeof(reply));
    ASSERT_EQ(cmp, 0);

    // invoking another read should still succeed
    U16 prevTransactionID = this->component.m_tid;
    status = this->invoke_to_readRMAP(0, destAddr, destKey, targetAddr, buf, sizeof(data), increment);
    ASSERT_EQ(status, 0) << status;
    completeTx(false);
    makeReplyPacket(reply, data, this->component.m_transaction);
    completeRx(reply, sizeof(reply), false, false, false, false);
    status = this->invoke_to_getStatus(0);
    ASSERT_EQ(status, SPW_STATUS_SUCCESS) << status;
    ASSERT_NE(prevTransactionID, this->component.m_tid); // should change transaction id
  }

  void Tester ::
    testRMAPErrors(void) 
  {
    const U8 destAddr = 0x80;
    const U8 destKey = 0x12;
    const U8 targetAddr = 0x30;
    const U8 increment = 1;
    U8 data[] = {1,2,3,4};
    U8 buf[13 + sizeof(data)];
    U8 reply[13 + sizeof(data)];

    I32 status = 0;

    // tx error
    status = this->invoke_to_readRMAP(0, destAddr, destKey, targetAddr, buf, sizeof(data), increment);
    ASSERT_EQ(status, 0) << status;
    completeTx(true);
    status = this->invoke_to_getStatus(0);
    ASSERT_EQ(status, SPW_STATUS_ERR_TX_LINK);
    status = this->invoke_to_reset(0);
    ASSERT_EQ(status, SPW_STATUS_SUCCESS);

    // rx error - truncated
    status = this->invoke_to_readRMAP(0, destAddr, destKey, targetAddr, buf, sizeof(data), increment);
    ASSERT_EQ(status, 0) << status;
    completeTx(false);
    completeRx(reply, sizeof(reply), true, false, false, false);
    status = this->invoke_to_getStatus(0);
    ASSERT_EQ(status, SPW_STATUS_ERR_RX_TRUNCATED);
    status = this->invoke_to_reset(0);
    ASSERT_EQ(status, SPW_STATUS_SUCCESS);

    // rx error - data crc error
    status = this->invoke_to_readRMAP(0, destAddr, destKey, targetAddr, buf, sizeof(data), increment);
    ASSERT_EQ(status, 0) << status;
    completeTx(false);
    completeRx(reply, sizeof(reply), false, true, false, false);
    status = this->invoke_to_getStatus(0);
    ASSERT_EQ(status, SPW_STATUS_ERR_RX_DATA_CRC);
    status = this->invoke_to_reset(0);
    ASSERT_EQ(status, SPW_STATUS_SUCCESS);

    // rx error - header crc error
    status = this->invoke_to_readRMAP(0, destAddr, destKey, targetAddr, buf, sizeof(data), increment);
    ASSERT_EQ(status, 0) << status;
    completeTx(false);
    completeRx(reply, sizeof(reply), false, false, true, false);
    status = this->invoke_to_getStatus(0);
    ASSERT_EQ(status, SPW_STATUS_ERR_RX_HDR_CRC);
    status = this->invoke_to_reset(0);
    ASSERT_EQ(status, SPW_STATUS_SUCCESS);

    // rx error - eep
    status = this->invoke_to_readRMAP(0, destAddr, destKey, targetAddr, buf, sizeof(data), increment);
    ASSERT_EQ(status, 0) << status;
    completeTx(false);
    completeRx(reply, sizeof(reply), false, false, false, true);
    status = this->invoke_to_getStatus(0);
    ASSERT_EQ(status, SPW_STATUS_ERR_RX_EEP);
    status = this->invoke_to_reset(0);
    ASSERT_EQ(status, SPW_STATUS_SUCCESS);

    // rx error - cannot deserialize into RMAP packet
    status = this->invoke_to_readRMAP(0, destAddr, destKey, targetAddr, buf, sizeof(data), increment);
    ASSERT_EQ(status, 0) << status;
    completeTx(false);
    makeReplyPacket(reply, data, this->component.m_transaction);
    reply[1] = 0; // invalid RMAP flag
    completeRx(reply, sizeof(reply), false, false, false, false);
    status = this->invoke_to_getStatus(0);
    ASSERT_EQ(status, SPW_STATUS_ERR_RX_DESERIALIZATION);
    status = this->invoke_to_reset(0);
    ASSERT_EQ(status, SPW_STATUS_SUCCESS);

    // rx error - wrong rmap type
    status = this->invoke_to_readRMAP(0, destAddr, destKey, targetAddr, buf, sizeof(data), increment);
    ASSERT_EQ(status, 0) << status;
    completeTx(false);
    makeReplyPacket(reply, data, this->component.m_transaction);
    reply[2] = 0x40; // command
    completeRx(reply, sizeof(reply), false, false, false, false);
    status = this->invoke_to_getStatus(0);
    ASSERT_EQ(status, SPW_STATUS_ERR_RX_UNEXPECTED_REPLY);
    status = this->invoke_to_reset(0);
    ASSERT_EQ(status, SPW_STATUS_SUCCESS);

    // rmap error - wrong transaction id
    status = this->invoke_to_readRMAP(0, destAddr, destKey, targetAddr, buf, sizeof(data), increment);
    ASSERT_EQ(status, 0) << status;
    completeTx(false);
    makeReplyPacket(reply, data, this->component.m_transaction);
    reply[5] = 0xff; // transaction id MS
    completeRx(reply, sizeof(reply), false, false, false, false);
    status = this->invoke_to_getStatus(0);
    ASSERT_EQ(status, SPW_STATUS_ERR_RMAP_TRANS_ID_MISMATCH);
    status = this->invoke_to_reset(0);
    ASSERT_EQ(status, SPW_STATUS_SUCCESS);

    // rmap error - wrong data len
    status = this->invoke_to_readRMAP(0, destAddr, destKey, targetAddr, buf, sizeof(data), increment);
    ASSERT_EQ(status, 0) << status;
    completeTx(false);
    makeReplyPacket(reply, data, this->component.m_transaction);
    reply[8] = 0xff; // data len MS
    completeRx(reply, sizeof(reply), false, false, false, false);
    status = this->invoke_to_getStatus(0);
    ASSERT_EQ(status, SPW_STATUS_ERR_RMAP_DATA_LEN_MISMATCH);
    status = this->invoke_to_reset(0);
    ASSERT_EQ(status, SPW_STATUS_SUCCESS);

    // rmap error - stat
    for (U32 code = 1; code <= 13; code++) {
      status = this->invoke_to_readRMAP(0, destAddr, destKey, targetAddr, buf, sizeof(data), increment);
      ASSERT_EQ(status, 0) << status;
      completeTx(false);
      makeReplyPacket(reply, data, this->component.m_transaction);
      reply[3] = code; // rmap status byte
      completeRx(reply, sizeof(reply), false, false, false, false);
      status = this->invoke_to_getStatus(0);
      switch (code) {
        case 1: ASSERT_EQ(status, SPW_STATUS_ERR_RMAP_STAT_GENERAL); break;
        case 2: ASSERT_EQ(status, SPW_STATUS_ERR_RMAP_STAT_UNUSED_TYPE); break;
        case 3: ASSERT_EQ(status, SPW_STATUS_ERR_RMAP_STAT_INVALID_KEY); break;
        case 4: ASSERT_EQ(status, SPW_STATUS_ERR_RMAP_STAT_INVALID_DATA_CRC); break;
        case 5: ASSERT_EQ(status, SPW_STATUS_ERR_RMAP_STAT_EARLY_EOP); break;
        case 6: ASSERT_EQ(status, SPW_STATUS_ERR_RMAP_STAT_CARGO_TOO_LARGE); break;
        case 7: ASSERT_EQ(status, SPW_STATUS_ERR_RMAP_STAT_EEP); break;
        case 8: ASSERT_EQ(status, SPW_STATUS_ERR_RMAP_STAT_UNKNOWN); break;
        case 9: ASSERT_EQ(status, SPW_STATUS_ERR_RMAP_STAT_VERIFY_BUFFER_OVERRUN); break;
        case 10: ASSERT_EQ(status, SPW_STATUS_ERR_RMAP_STAT_CMD_UNAUTHORIZED); break;
        case 11: ASSERT_EQ(status, SPW_STATUS_ERR_RMAP_STAT_DATA_LEN_ERR); break;
        case 12: ASSERT_EQ(status, SPW_STATUS_ERR_RMAP_STAT_INVALID_DEST_ADDR); break;
        case 13: ASSERT_EQ(status, SPW_STATUS_ERR_RMAP_STAT_UNKNOWN); break;
        default: break;
      }
      status = this->invoke_to_reset(0);
      ASSERT_EQ(status, SPW_STATUS_SUCCESS);
    }

    // after all of that, a normal run should still work
    status = this->invoke_to_readRMAP(0, destAddr, destKey, targetAddr, buf, sizeof(data), increment);
    ASSERT_EQ(status, 0) << status;
    completeTx(false);
    makeReplyPacket(reply, data, this->component.m_transaction);
    completeRx(reply, sizeof(reply), false, false, false, false);
    status = this->invoke_to_getStatus(0);
    ASSERT_EQ(status, SPW_STATUS_SUCCESS);
  }

  void Tester ::
    testSPWConnectionErrors(void) 
  {
    U8 dummy[4] = {0};

    I32 status = 0;

    // something really wrong with the hardware
    core0default.status = 0xffffffff;

    // everything fails in this state
    this->component.init();
    status = this->invoke_to_getStatus(0);
    ASSERT_EQ(status, SPW_STATUS_ERR_INIT);
    status = this->invoke_to_readRMAP(0, 0, 0, 0, dummy, sizeof(dummy), 0);
    ASSERT_EQ(status, SPW_STATUS_ERR_INIT);
    status = this->invoke_to_writeRMAP(0, 0, 0, 0, dummy, sizeof(dummy), 0, 0, 0);
    ASSERT_EQ(status, SPW_STATUS_ERR_INIT);

    // unable to get to connected state
    core0default.status = 0x00400000;

    // everything fails in this state
    this->component.init();
    status = this->invoke_to_getStatus(0);
    ASSERT_EQ(status, SPW_STATUS_ERR_DISCONNECTED);
    status = this->invoke_to_readRMAP(0, 0, 0, 0, dummy, sizeof(dummy), 0);
    ASSERT_EQ(status, SPW_STATUS_ERR_DISCONNECTED);
    status = this->invoke_to_writeRMAP(0, 0, 0, 0, dummy, sizeof(dummy), 0, 0, 0);
    ASSERT_EQ(status, SPW_STATUS_ERR_DISCONNECTED);
  }


  // ----------------------------------------------------------------------
  // Helper methods 
  // ----------------------------------------------------------------------

  void Tester ::
    connectPorts(void) 
  {

    // writeRMAP
    this->connect_to_writeRMAP(
        0,
        this->component.get_writeRMAP_InputPort(0)
    );

    // readRMAP
    this->connect_to_readRMAP(
        0,
        this->component.get_readRMAP_InputPort(0)
    );

    // reset
    this->connect_to_reset(
        0,
        this->component.get_reset_InputPort(0)
    );

    // getStatus
    this->connect_to_getStatus(
        0,
        this->component.get_getStatus_InputPort(0)
    );

  }

  void Tester ::
    initComponents(void) 
  {
    this->init();
    this->component.init(
        INSTANCE
    );
  }

  void Tester ::
    completeTx(bool linkerr)
  {
    struct spwvars* spw = &this->component.m_spwcore;
    struct txdescriptor* txdesc = &(spw->dma[0].txd[spw->dma[0].txchkpnt]);

    // clear EN bit
    txdesc->ctrl &= ~(1<<12);

    // set error
    txdesc->ctrl |= (linkerr<<15);
  }

  void Tester ::
    completeRx(const U8* data, const U32 dataSize, bool truncated, bool dcrc, bool hcrc, bool eep)
  {
    struct spwvars* spw = &this->component.m_spwcore;
    struct rxdescriptor* rxdesc = &(spw->dma[0].rxd[spw->dma[0].rxchkpnt]);

    // clear EN bit
    rxdesc->ctrl &= ~(1<<25);

    // transfer data
    U8* origAddr = (U8*)(((POINTER_CAST)(&this->component) & ~0xffffffffL) | ((POINTER_CAST)(rxdesc->daddr) & 0xffffffff));
    memcpy(origAddr, data, dataSize);

    // set recv size
    rxdesc->ctrl &= ~(0x1ffffff);
    rxdesc->ctrl |= dataSize;

    // set error
    rxdesc->ctrl |= (truncated<<31);
    rxdesc->ctrl |= (dcrc<<30);
    rxdesc->ctrl |= (hcrc<<29);
    rxdesc->ctrl |= (eep<<28);
  }

  void Tester ::
    makeReplyPacket(U8* buf, const U8* data, const RMAPTransaction& t)
  {
    const bool w = (t.pkt.type == writecmd);

    buf[0] = t.pkt.srcaddr;
    buf[1] = 1;
    buf[2] = (w<<5) | (t.pkt.verify<<4) | (t.pkt.ack<<3) | (t.pkt.incr<<2);
    buf[3] = 0;
    buf[4] = t.pkt.destaddr;
    buf[5] = t.pkt.tid >> 8;
    buf[6] = t.pkt.tid & 0xff;
    buf[7] = 0;

    if (!w) {
      buf[8] = (t.pkt.len >> 16) & 0xff;
      buf[9] = (t.pkt.len >> 8) & 0xff;
      buf[10] = (t.pkt.len >> 0) & 0xff;
      buf[11] = 0;
      memcpy(buf+12, data, t.pkt.len);
      buf[12+t.pkt.len] = 0;
    }
  }

  void Tester ::
    buildRMAPHeaderFromVendorAPI(
      const RMAPSettings& settings,
      U8* buf,
      U32& resultSize
    )
  {
    struct rmap_pkt pkt;
    if (settings.iscmd) {
      pkt.type = settings.iswrite ? writecmd : readcmd;
      pkt.verify = settings.verify ? yes : no;
      pkt.ack = settings.ack ? yes : no;
      pkt.incr = settings.incr ? yes : no;
      pkt.status = 0;
      pkt.destaddr = settings.dest_addr;
      pkt.destkey = settings.dest_key;
      pkt.srcaddr = settings.src_addr;
      pkt.tid = settings.tid;
      pkt.addr = settings.addr;
      pkt.len = settings.len;
    } else {
      pkt.type = settings.iswrite ? writerep : readrep;
      pkt.verify = settings.verify ? yes : no;
      pkt.ack = settings.ack ? yes : no;
      pkt.incr = settings.incr ? yes : no;
      pkt.status = settings.status;
      pkt.destaddr = settings.dest_addr;
      pkt.destkey = 0;
      pkt.srcaddr = settings.src_addr;
      pkt.tid = settings.tid;
      pkt.len = settings.len;
    }
    pkt.dstspalen = 0;
    pkt.dstspa  = (char *)NULL;
    pkt.srcspalen = 0;
    pkt.srcspa = (char *)NULL;
    int cmdsize = 0;
    int rc = build_rmap_hdr(&pkt, reinterpret_cast<char*>(buf), &cmdsize);
    ASSERT_EQ(rc, 0);
    ASSERT_GT(cmdsize, 0);
    resultSize = static_cast<U32>(cmdsize);
  }

  void Tester ::
    buildRMAPHeaderFromCustomSerializable(
      const RMAPSettings& settings,
      U8* buf,
      U32& resultSize
    )
  {
    RMAPHeader hdr;

    if (settings.iscmd) {
      hdr.setPacketType(RMAPHeader::RMAP_COMMAND);
      hdr.setDestLogicalAddr(settings.dest_addr);
      hdr.setCommandType(settings.iswrite ? RMAPHeader::RMAP_WRITE : RMAPHeader::RMAP_READ);
      hdr.setVerify(settings.verify);
      hdr.setAcknowledge(settings.ack);
      hdr.setIncrement(settings.incr);
      hdr.setDestKey(settings.dest_key);
      hdr.setSrcLogicalAddr(settings.src_addr);
      hdr.setTransactionID(settings.tid);
      hdr.setAddr(settings.addr);
      hdr.setDataLen(settings.len);
    } else {
      hdr.setPacketType(RMAPHeader::RMAP_RESPONSE);
      hdr.setStatus(settings.status);
      hdr.setDestLogicalAddr(settings.src_addr);
      hdr.setCommandType(settings.iswrite ? RMAPHeader::RMAP_WRITE : RMAPHeader::RMAP_READ);
      hdr.setVerify(settings.verify);
      hdr.setAcknowledge(settings.ack);
      hdr.setIncrement(settings.incr);
      hdr.setSrcLogicalAddr(settings.dest_addr);
      hdr.setTransactionID(settings.tid);
      if (!settings.iswrite) {
        hdr.setDataLen(settings.len);
      }
    }

    Fw::ComBuffer combuf;
    combuf.resetSer();
    Fw::SerializeStatus stat = hdr.serialize(combuf, false);
    ASSERT_EQ(stat, Fw::FW_SERIALIZE_OK);

    memcpy(buf, combuf.getBuffAddr(), combuf.getBuffLength());
    resultSize = combuf.getBuffLength();
  }

  void Tester ::
    verifyRMAPHeader(
      const RMAPSettings& rs,
      const U8* hdr,
      const U32 hdrSize
    )
  {
    // test that values are as expected
    if (rs.iscmd) {
      ASSERT_EQ(hdrSize, 15);
      ASSERT_EQ(hdr[0], rs.dest_addr);
      ASSERT_EQ(hdr[1], 1);
      ASSERT_EQ(hdr[2], 0x40 + (rs.iswrite << 5) + (rs.verify<<4) + (rs.ack<<3) + (rs.incr<<2));
      ASSERT_EQ(hdr[3], rs.dest_key);
      ASSERT_EQ(hdr[4], rs.src_addr);
      ASSERT_EQ(hdr[5], rs.tid >> 8);
      ASSERT_EQ(hdr[6], rs.tid & 0xff);
      ASSERT_EQ(hdr[7], 0);
      ASSERT_EQ(hdr[8], (rs.addr >> 24) & 0xff);
      ASSERT_EQ(hdr[9], (rs.addr >> 16) & 0xff);
      ASSERT_EQ(hdr[10], (rs.addr >> 8) & 0xff);
      ASSERT_EQ(hdr[11], (rs.addr >> 0) & 0xff);
      ASSERT_EQ(hdr[12], (rs.len >> 16) & 0xff);
      ASSERT_EQ(hdr[13], (rs.len >> 8) & 0xff);
      ASSERT_EQ(hdr[14], (rs.len >> 0) & 0xff);
    } else {
      ASSERT_EQ(hdr[0], rs.src_addr);
      ASSERT_EQ(hdr[1], 1);
      ASSERT_EQ(hdr[2], 0x00 + (rs.iswrite << 5) + (rs.verify<<4) + (rs.ack<<3) + (rs.incr<<2));
      ASSERT_EQ(hdr[3], rs.status);
      ASSERT_EQ(hdr[4], rs.dest_addr);
      ASSERT_EQ(hdr[5], rs.tid >> 8);
      ASSERT_EQ(hdr[6], rs.tid & 0xff);
      if (rs.iswrite) {
        ASSERT_EQ(hdrSize, 7);
      } else {
        ASSERT_EQ(hdrSize, 11);
        ASSERT_EQ(hdr[7], 0);
        ASSERT_EQ(hdr[8], (rs.len >> 16) & 0xff);
        ASSERT_EQ(hdr[9], (rs.len >> 8) & 0xff);
        ASSERT_EQ(hdr[10], (rs.len >> 0) & 0xff);
      }
    }
  }

  void Tester ::
    verifyRMAPHeaderWithVendorAPI(
      const RMAPSettings& rs,
      const U8* hdr,
      const U32 hdrSize
    )
  {
    struct rmap_pkt pkt;
    int size;
    I32 status = parse_rmap_pkt(&pkt, reinterpret_cast<char*>(const_cast<U8*>(hdr)), &size);
    ASSERT_EQ(status, 0);
    if (rs.iscmd) {
      ASSERT_EQ(size, hdrSize);
      ASSERT_EQ(pkt.destaddr, rs.dest_addr);
      ASSERT_EQ(pkt.type, (rs.iswrite ? writecmd : readcmd));
      ASSERT_EQ(pkt.verify, rs.verify);
      ASSERT_EQ(pkt.ack, rs.ack);
      ASSERT_EQ(pkt.incr, rs.incr);
      ASSERT_EQ(pkt.destkey, rs.dest_key);
      ASSERT_EQ(pkt.srcaddr, rs.src_addr);
      ASSERT_EQ(pkt.tid, rs.tid);
      ASSERT_EQ(pkt.addr, rs.addr);
      ASSERT_EQ(pkt.len, rs.len);
    } else {
      ASSERT_EQ(size, hdrSize);
      ASSERT_EQ(pkt.status, rs.status);
      ASSERT_EQ(pkt.destaddr, rs.dest_addr);
      ASSERT_EQ(pkt.type, (rs.iswrite ? writerep : readrep));
      ASSERT_EQ(pkt.verify, rs.verify);
      ASSERT_EQ(pkt.ack, rs.ack);
      ASSERT_EQ(pkt.incr, rs.incr);
      ASSERT_EQ(pkt.srcaddr, rs.src_addr);
      ASSERT_EQ(pkt.tid, rs.tid);
      if (!rs.iswrite) {
        ASSERT_EQ(pkt.len, rs.len);
      }
    }
  }

  void Tester ::
    verifyRMAPHeaderWithCustomSerializable(
      const RMAPSettings& rs,
      const U8* hdr,
      const U32 hdrSize
    )
  {
    // deserialize the RMAP reply header to check for errors
    Fw::ComBuffer hdrBuf(hdr, hdrSize);
    RMAPHeader h;
    Fw::SerializeStatus deserializeStatus = h.deserialize(hdrBuf, false);
    ASSERT_EQ(deserializeStatus, Fw::FW_SERIALIZE_OK);
    if (rs.iscmd) {
      ASSERT_EQ(h.getPacketType(), RMAPHeader::RMAP_COMMAND);
      ASSERT_EQ(h.getDestLogicalAddr(), rs.dest_addr);
      ASSERT_EQ(h.getCommandType(), (rs.iswrite ? RMAPHeader::RMAP_WRITE : RMAPHeader::RMAP_READ));
      ASSERT_EQ(h.getVerify(), rs.verify);
      ASSERT_EQ(h.getAcknowledge(), rs.ack);
      ASSERT_EQ(h.getIncrement(), rs.incr);
      ASSERT_EQ(h.getDestKey(), rs.dest_key);
      ASSERT_EQ(h.getSrcLogicalAddr(), rs.src_addr);
      ASSERT_EQ(h.getTransactionID(), rs.tid);
      ASSERT_EQ(h.getAddr(), rs.addr);
      ASSERT_EQ(h.getDataLen(), rs.len);
    } else {
      ASSERT_EQ(h.getPacketType(), RMAPHeader::RMAP_RESPONSE);
      ASSERT_EQ(h.getStatus(), rs.status);
      ASSERT_EQ(h.getSrcLogicalAddr(), rs.dest_addr); // custom serializable is reversed for replies
      ASSERT_EQ(h.getCommandType(), (rs.iswrite ? RMAPHeader::RMAP_WRITE : RMAPHeader::RMAP_READ));
      ASSERT_EQ(h.getVerify(), rs.verify);
      ASSERT_EQ(h.getAcknowledge(), rs.ack);
      ASSERT_EQ(h.getIncrement(), rs.incr);
      ASSERT_EQ(h.getDestLogicalAddr(), rs.src_addr);
      ASSERT_EQ(h.getTransactionID(), rs.tid);
      if (!rs.iswrite) {
        ASSERT_EQ(h.getDataLen(), rs.len);
      }
    }
  }


} // end namespace Drv

