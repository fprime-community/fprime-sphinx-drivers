// ====================================================================== 
// \title  SPWManager.hpp
// \author vwong
// \brief  cpp file for SPWManager test harness implementation class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
// ====================================================================== 

#include "Tester.hpp"
#include <fprime-sphinx-drivers/SPWDriver/SPWStatus.hpp>
#include <fprime-sphinx-drivers/SPWDriver/RMAPHeader.hpp>
#include <fprime-sphinx-drivers/SPWManager/SPWRequestStatus.hpp>
#include <fprime-sphinx-drivers/SPWManager/SPWRequestQueue.hpp>
#include <fprime-sphinx-drivers/Util/SphinxDrvUtil.hpp>

#define INSTANCE 0
#define CMD_SEQ 0
#define MAX_HISTORY_SIZE 1000
#define QUEUE_DEPTH 10

namespace Drv {

  // ----------------------------------------------------------------------
  // Construction and destruction 
  // ----------------------------------------------------------------------

  const U32 Tester::pingKey = 0x58CD;
  const U8 Tester::spwAddr = 0x31;
  const U8 Tester::spwKey = 0xA6;

  Tester ::
    Tester(void) : 
#if FW_OBJECT_NAMES == 1
      SPWManagerGTestBase("Tester", MAX_HISTORY_SIZE),
      component("SPWManager"),
#else
      SPWManagerGTestBase(MAX_HISTORY_SIZE),
      component(),
#endif
      pingResponses(0),
      spwDriverExecuting(false),
      spwDriverReceivedReset(false),
      spwDriverSendCounter(0),
      spwDriverReceiveCounter(0),
      spwDriverSendBound(0),
      spwDriverReceiveBound(0),
      spwDriverEEPError(false),
      spwDriverInitError(false),
      spwDriverDiscError(false)
  {
    this->initComponents();
    this->connectPorts();

    this->addressPrefix = reinterpret_cast<POINTER_CAST>(this->buf1) >> 32L;
  }

  Tester ::
    ~Tester(void) 
  {
    
  }

  // ----------------------------------------------------------------------
  // Tests 
  // ----------------------------------------------------------------------

  void Tester ::
    testPing(void) 
  {
    U32 numPings = this->pingResponses;

    this->invoke_to_PingRecv(0, this->pingKey);
    this->component.doDispatch();
    ASSERT_GT(this->pingResponses, numPings);
  }

  void Tester ::
    testSyncReadWrite(void) 
  {
    I32 status;
    U32 timeout = 30;

    // set param
    status = this->invoke_to_setParam(0, this->spwAddr, this->spwKey, 1, 1, 1); // incr, verify, ack
    ASSERT_EQ(status, 0);

    // writes
    this->val1 = 0x3814FA1C;
    for (U32 i = 0; i < 64; i++) {
      this->val1 = this->val1 * 17;
      this->val2 = 0x0;
      this->val3 = this->val1;
      status = this->invoke_to_write(0, Drv::ptrToU32(&this->val2), sizeof(this->val1), Drv::wordAsBuf(this->val1), sizeof(this->val1), timeout);
      ASSERT_EQ(status, SPW_REQUEST_STATUS_DONE);
      ASSERT_EQ(this->val1, this->val3);
      ASSERT_EQ(this->val2, this->val3);
      this->clearHistory();
    }

    // reads
    this->val1 = 0xA24BFE19;
    for (U32 i = 0; i < 64; i++) {
      this->val1 = this->val1 * 19;
      this->val2 = 0x0;
      this->val3 = this->val1;
      status = this->invoke_to_read(0, Drv::ptrToU32(&this->val1), sizeof(this->val2), Drv::wordAsBuf(this->val2), sizeof(this->val2), timeout);
      ASSERT_EQ(status, SPW_REQUEST_STATUS_DONE);
      ASSERT_EQ(this->val1, this->val3);
      ASSERT_EQ(this->val2, this->val3);
      this->clearHistory();
    }
  }

  void Tester ::
    testAsyncReadWrite(void) 
  {
    I32 status;

    // initialize buf1
    U32 seed = 0xAE787749;
    for (U32 i = 0; i < sizeof(this->buf1); i++) {
      seed = seed * 29;
      this->buf1[i] = (seed >> 24);
    }
    memset(this->buf2, 0, sizeof(this->buf2));
    memset(this->buf3, 0, sizeof(this->buf3));

    // disable verify for buf write
    this->invoke_to_setParam(0, this->spwAddr, this->spwKey, 1, 0, 1); // incr, no verify, ack

    // read from buf1 to buf2
    status = this->invoke_to_readAsync(0, Drv::ptrToU32(this->buf1), sizeof(this->buf2), this->buf2, sizeof(this->buf2), 10);
    ASSERT_EQ(status, SPW_REQUEST_STATUS_ACCEPTED);
    // write from buf2 to buf3
    status = this->invoke_to_writeAsync(0, Drv::ptrToU32(this->buf3), sizeof(this->buf2), this->buf2, sizeof(this->buf2), 10);
    ASSERT_EQ(status, SPW_REQUEST_STATUS_ACCEPTED);

    // advance time
    this->invoke_to_schedIn(0, 0);
    this->component.doDispatch();

    // check statuses
    ASSERT_from_statusOut_SIZE(2);
    ASSERT_from_statusOut(0, SPW_REQUEST_STATUS_DONE);
    ASSERT_from_statusOut(1, SPW_REQUEST_STATUS_DONE);

    // compare
    status = memcmp(this->buf1, this->buf3, sizeof(this->buf1));
    ASSERT_EQ(status, 0);
  }

  void Tester ::
    testAsyncDmaRead(void) 
  {
    U8 buf4[SPW_WORK_BUF_MAX_SIZE+4];
    U8 buf5[SPW_WORK_BUF_MAX_SIZE+4+20];

    I32 status;

    // initialize buf4
    U32 seed = 0xB37F958;
    for (U32 i = 0; i < sizeof(buf4); i++) {
      seed = seed * 41;
      buf4[i] = (seed >> 24);
    }
    memset(buf5, 0, sizeof(buf5));

    // disable verify for buf write
    this->invoke_to_setParam(0, this->spwAddr, this->spwKey, 1, 0, 1); // incr, no verify, ack

    // perform an async read that can't finish in one transfer
    this->setSpacewireDelay(0, SPW_ASYNC_TIMEOUT-1);
    status = this->invoke_to_readAsync(0, Drv::ptrToU32(buf4), sizeof(buf4), buf5, sizeof(buf5), 10);
    ASSERT_EQ(status, SPW_REQUEST_STATUS_ACCEPTED);
    this->invoke_to_schedIn(0, 0);
    this->component.doDispatch();
    ASSERT_from_statusOut_SIZE(0);
    this->invoke_to_schedIn(0, 0);
    this->component.doDispatch();
    ASSERT_from_statusOut_SIZE(1);
    ASSERT_from_statusOut(0, SPW_REQUEST_STATUS_DONE);
    this->clearHistory();

    // compare
    status = memcmp(buf4, buf5, sizeof(buf4));
    ASSERT_EQ(status, 0);

    // dma async read _can_ finish in one transfer
    this->setSpacewireDelay(0, 1);
    status = this->invoke_to_readAsyncDMA(0, Drv::ptrToU32(buf4), sizeof(buf4), buf5, sizeof(buf5), 10);
    ASSERT_EQ(status, SPW_REQUEST_STATUS_ACCEPTED);
    this->invoke_to_schedIn(0, 0);
    this->component.doDispatch();
    ASSERT_from_statusOut_SIZE(1);

    // compare
    status = memcmp(buf4, buf5 + SPW_REQUEST_DMA_HDR_SIZE, sizeof(buf4));
    ASSERT_EQ(status, 0);
  }

  void Tester ::
    testHugeRead(void) 
  {
    const U32 buf6Size = MAX_RMAP_PACKET_SIZE+4;
    const U32 buf7Size = MAX_RMAP_PACKET_SIZE+4+20;
    U8* buf6 = new U8[buf6Size];
    U8* buf7 = new U8[buf7Size];
    FW_ASSERT(buf6 != NULL);
    FW_ASSERT(buf7 != NULL);
    memset(buf6, 0, buf6Size);
    memset(buf6, 0, buf6Size);
    this->addressPrefix = reinterpret_cast<POINTER_CAST>(buf6) >> 32L;

    FW_ASSERT(buf7Size >= buf6Size);

    I32 status;

    // make buf6 distinguishable from buf7
    for (U32 i = 0; i < 32; i++) {
      buf6[i] = i;
    }
    for (U32 i = 0; i < 32; i++) {
      buf6[buf6Size-1-i] = i;
    }

    // basic param
    status = this->invoke_to_setParam(0, this->spwAddr, this->spwKey, 1, 0, 1); // no incr, verify, ack

    // perform a long sync read
    status = this->invoke_to_read(0, Drv::ptrToU32(buf6), buf6Size, buf7, buf7Size, 100000);
    ASSERT_EQ(status, SPW_REQUEST_STATUS_DONE);
    status = memcmp(buf6, buf7, buf6Size);
    ASSERT_EQ(status, 0);
    this->clearHistory();
    memset(buf7, 0, buf7Size);

    // perform a long async read
    this->setSpacewireDelay(0, 1);
    status = this->invoke_to_readAsync(0, Drv::ptrToU32(buf6), buf6Size, buf7, buf7Size, 30);
    ASSERT_EQ(status, SPW_REQUEST_STATUS_ACCEPTED);
    for (U32 i = 0; i < 30; i++) {
      this->invoke_to_schedIn(0, 0);
      this->component.doDispatch();
    }
    ASSERT_from_statusOut_SIZE(1);
    ASSERT_from_statusOut(0, SPW_REQUEST_STATUS_DONE);
    status = memcmp(buf6, buf7, buf6Size);
    ASSERT_EQ(status, 0);
    this->clearHistory();
    memset(buf7, 0, buf7Size);

    // perform a long async dma read (limited to MAX_RMAP_PACKET_SIZE)
    this->setSpacewireDelay(0, 1);
    status = this->invoke_to_readAsyncDMA(0, Drv::ptrToU32(buf6), MAX_RMAP_PACKET_SIZE, buf7, buf7Size, 4);
    ASSERT_EQ(status, SPW_REQUEST_STATUS_ACCEPTED);
    for (U32 i = 0; i < 4; i++) {
      this->invoke_to_schedIn(0, 0);
      this->component.doDispatch();
    }
    ASSERT_from_statusOut_SIZE(1);
    ASSERT_from_statusOut(0, SPW_REQUEST_STATUS_DONE);
    status = memcmp(buf6, buf7 + SPW_REQUEST_DMA_HDR_SIZE, MAX_RMAP_PACKET_SIZE);
    ASSERT_EQ(status, 0);
    this->clearHistory();
    memset(buf7, 0, buf7Size);

    delete [] buf6;
    delete [] buf7;
  }

  void Tester ::
    testHugeWrite(void) 
  {
    const U32 buf6Size = MAX_RMAP_PACKET_SIZE+4;
    const U32 buf7Size = MAX_RMAP_PACKET_SIZE+4+20;
    U8* buf6 = new U8[buf6Size];
    U8* buf7 = new U8[buf7Size];
    FW_ASSERT(buf6 != NULL);
    FW_ASSERT(buf7 != NULL);
    memset(buf6, 0, buf6Size);
    memset(buf7, 0, buf7Size);
    this->addressPrefix = reinterpret_cast<POINTER_CAST>(buf6) >> 32L;

    FW_ASSERT(buf7Size >= buf6Size);

    I32 status;

    // make buf6 distinguishable from buf7
    for (U32 i = 0; i < 32; i++) {
      buf6[i] = i;
    }
    for (U32 i = 0; i < 32; i++) {
      buf6[buf6Size-1-i] = i;
    }

    // basic param
    status = this->invoke_to_setParam(0, this->spwAddr, this->spwKey, 1, 0, 1); // no incr, verify, ack

    // perform a long sync write
    status = this->invoke_to_write(0, Drv::ptrToU32(buf6), buf6Size, buf7, buf7Size, 100000);
    ASSERT_EQ(status, SPW_REQUEST_STATUS_DONE);
    status = memcmp(buf6, buf7, buf6Size);
    ASSERT_EQ(status, 0);
    this->clearHistory();
    memset(buf7, 0, buf7Size);

    // perform a long async write
    this->setSpacewireDelay(1, 0);
    status = this->invoke_to_writeAsync(0, Drv::ptrToU32(buf6), buf6Size, buf7, buf7Size, 30);
    ASSERT_EQ(status, SPW_REQUEST_STATUS_ACCEPTED);
    for (U32 i = 0; i < 30; i++) {
      this->invoke_to_schedIn(0, 0);
      this->component.doDispatch();
    }
    ASSERT_from_statusOut_SIZE(1);
    ASSERT_from_statusOut(0, SPW_REQUEST_STATUS_DONE);
    status = memcmp(buf6, buf7, buf6Size);
    ASSERT_EQ(status, 0);
    this->clearHistory();
    memset(buf7, 0, buf7Size);

    delete [] buf6;
    delete [] buf7;
  }

  void Tester ::
    testMiscRmapSettings(void) 
  {
    I32 status;
    U32 timeout = 0;

    // no increment read
    status = this->invoke_to_setParam(0, this->spwAddr, this->spwKey, 0, 1, 1); // no incr, verify, ack
    ASSERT_EQ(status, 0);
    memset(this->buf1, 0, 8);
    this->buf1[0] = 0x44;
    this->buf1[1] = 0x55;
    this->buf1[2] = 0x77;
    this->buf1[3] = 0x4B;
    memset(this->buf2, 0, 8);
    memcpy(this->buf3, this->buf1, 4);
    memcpy(this->buf3+4, this->buf1, 4);
    status = this->invoke_to_read(0, Drv::ptrToU32(this->buf1), 8, this->buf2, 8, timeout);
    ASSERT_EQ(status, SPW_REQUEST_STATUS_DONE);
    status = memcmp(this->buf2, this->buf3, 8);
    ASSERT_EQ(status, 0);

    // no increment no verify write
    status = this->invoke_to_setParam(0, this->spwAddr, this->spwKey, 0, 0, 1); // no incr, no verify, ack
    ASSERT_EQ(status, 0);
    memset(this->buf1, 0, 8);
    this->buf1[4] = 0xD6;
    this->buf1[5] = 0x73;
    this->buf1[6] = 0x1E;
    this->buf1[7] = 0x9A;
    memset(this->buf2, 0, 8);
    memset(this->buf3, 0, 8);
    memcpy(this->buf3, this->buf1+4, 4);
    status = this->invoke_to_write(0, Drv::ptrToU32(this->buf2), 8, this->buf1, 8, timeout);
    ASSERT_EQ(status, SPW_REQUEST_STATUS_DONE);
    status = memcmp(this->buf2, this->buf3, 8);
    ASSERT_EQ(status, 0);

    // no verify write
    status = this->invoke_to_setParam(0, this->spwAddr, this->spwKey, 1, 0, 1); // incr, no verify, ack
    ASSERT_EQ(status, 0);
    this->val1 = 0x18957A83;
    this->val2 = 0x0;
    status = this->invoke_to_write(0, Drv::ptrToU32(&this->val2), sizeof(this->val2), Drv::wordAsBuf(this->val1), sizeof(this->val2), timeout);
    ASSERT_EQ(status, SPW_REQUEST_STATUS_DONE);
    ASSERT_EQ(this->val1, this->val2);

    // no acknowledge write
    status = this->invoke_to_setParam(0, this->spwAddr, this->spwKey, 1, 1, 0); // incr, verify, no ack
    ASSERT_EQ(status, 0);
    // not guaranteed to be written w/o ack, so just exercise some code paths
    status = this->invoke_to_write(0, Drv::ptrToU32(&this->val2), sizeof(this->val2), Drv::wordAsBuf(this->val1), sizeof(this->val2), timeout);
    ASSERT_EQ(status, SPW_REQUEST_STATUS_DONE);
  }

  void Tester ::
    testMiscErrors(void) 
  {
    I32 status;

    // basic param
    status = this->invoke_to_setParam(0, this->spwAddr, this->spwKey, 1, 0, 1); // incr, no verify, ack
    ASSERT_EQ(status, 0);

    // sync timeout
    U32 timeout = 5;
    // sync read
    this->setSpacewireDelay(0,timeout+1);
    status = this->invoke_to_read(0, Drv::ptrToU32(this->buf1), 4, this->buf2, 4, timeout);
    ASSERT_EQ(status, SPW_REQUEST_STATUS_TIMEDOUT);
    ASSERT_EVENTS_SPWManager_SpaceWireError_SIZE(0);
    ASSERT_EVENTS_SPWManager_SpaceWireTransactionTimeout_SIZE(1);
    ASSERT_EVENTS_SPWManager_SpaceWireTransactionTimeout(0, timeout, SPWManagerComponentImpl::SYNC_RMAP_READ, Drv::ptrToU32(this->buf1), SPWManagerComponentImpl::TRANSACTION_RECEIVING);
    // sync write
    this->setSpacewireDelay(timeout+1,0);
    status = this->invoke_to_write(0, Drv::ptrToU32(this->buf1), 4, this->buf2, 4, timeout);
    ASSERT_EQ(status, SPW_REQUEST_STATUS_TIMEDOUT);
    ASSERT_EVENTS_SPWManager_SpaceWireError_SIZE(0);
    ASSERT_EVENTS_SPWManager_SpaceWireTransactionTimeout_SIZE(2);
    ASSERT_EVENTS_SPWManager_SpaceWireTransactionTimeout(1, timeout, SPWManagerComponentImpl::SYNC_RMAP_WRITE, Drv::ptrToU32(this->buf1), SPWManagerComponentImpl::TRANSACTION_SENDING);
    this->clearHistory();

    // async timeout
    this->setSpacewireDelay(0,timeout * SPW_ASYNC_TIMEOUT + 1);
    status = this->invoke_to_readAsync(0, Drv::ptrToU32(this->buf1), 4, this->buf2, 4, timeout);
    ASSERT_EQ(status, SPW_REQUEST_STATUS_ACCEPTED);
    for (U32 i = 0; i < timeout; i++) {
      this->invoke_to_schedIn(0, 0);
      this->component.doDispatch();
    }
    ASSERT_from_statusOut_SIZE(1);
    ASSERT_from_statusOut(0, SPW_REQUEST_STATUS_TIMEDOUT);
    ASSERT_EVENTS_SPWManager_SpaceWireError_SIZE(0);
    ASSERT_EVENTS_SPWManager_SpaceWireTransactionTimeout_SIZE(1);
    this->clearHistory();

    // full queue
    for (U32 i = 0; i < SPW_REQUEST_QUEUE_SIZE; i++) {
      status = this->invoke_to_writeAsync(0, Drv::ptrToU32(this->buf1), 4, this->buf2, sizeof(this->buf2), timeout);
      ASSERT_EQ(status, SPW_REQUEST_STATUS_ACCEPTED);
    }
    status = this->invoke_to_readAsync(0, Drv::ptrToU32(this->buf1), 4, this->buf2, sizeof(this->buf2), timeout);
    ASSERT_EQ(status, SPW_REQUEST_STATUS_QUEUE_FULL);
    status = this->invoke_to_writeAsync(0, Drv::ptrToU32(this->buf1), 4, this->buf2, sizeof(this->buf2), timeout);
    ASSERT_EQ(status, SPW_REQUEST_STATUS_QUEUE_FULL);
    status = this->invoke_to_readAsyncDMA(0, Drv::ptrToU32(this->buf1), 4, this->buf2, sizeof(this->buf2), timeout);
    ASSERT_EQ(status, SPW_REQUEST_STATUS_QUEUE_FULL);
    this->setSpacewireDelay(0, 0);
    for (U32 i = 0; i < SPW_REQUEST_QUEUE_SIZE; i++) { // drain it
      this->invoke_to_schedIn(0, 0);
      this->component.doDispatch();
    }
    this->clearHistory();

    // can't do sync requests and various commands during async request
    this->setSpacewireDelay(SPW_ASYNC_TIMEOUT+1, 0);
    status = this->invoke_to_writeAsync(0, Drv::ptrToU32(this->buf1), 4, this->buf2, 4, timeout);
    ASSERT_EQ(status, SPW_REQUEST_STATUS_ACCEPTED);
    this->invoke_to_schedIn(0, 0);
    this->component.doDispatch();
    ASSERT_from_statusOut_SIZE(0);
    // sync read
    status = this->invoke_to_read(0, Drv::ptrToU32(this->buf1), 4, this->buf2, 4, timeout);
    ASSERT_EQ(status, SPW_REQUEST_STATUS_BUSY);
    // sync write
    status = this->invoke_to_write(0, Drv::ptrToU32(this->buf1), 4, this->buf2, 4, timeout);
    ASSERT_EQ(status, SPW_REQUEST_STATUS_BUSY);
    // read cmd
    this->sendCmd_SPWMGR_RMAP_READ_WORD(INSTANCE, CMD_SEQ, Drv::ptrToU32(this->buf1), timeout);
    this->component.doDispatch();
    ASSERT_CMD_RESPONSE(0, SPWManagerComponentImpl::OPCODE_SPWMGR_RMAP_READ_WORD, CMD_SEQ, Fw::COMMAND_EXECUTION_ERROR);
    ASSERT_EVENTS_SPWManager_Busy_SIZE(1);
    // write cmd
    this->sendCmd_SPWMGR_RMAP_WRITE_WORD(INSTANCE, CMD_SEQ, Drv::ptrToU32(this->buf1), 0, timeout);
    this->component.doDispatch();
    ASSERT_CMD_RESPONSE(1, SPWManagerComponentImpl::OPCODE_SPWMGR_RMAP_WRITE_WORD, CMD_SEQ, Fw::COMMAND_EXECUTION_ERROR);
    ASSERT_EVENTS_SPWManager_Busy_SIZE(2);
  }

  void Tester ::
    testSPWErrors(void) 
  {
    I32 status;

    // basic param
    status = this->invoke_to_setParam(0, this->spwAddr, this->spwKey, 1, 0, 1); // incr, no verify, ack
    ASSERT_EQ(status, 0);

    // init error
    this->spwDriverInitError = true;
    // sync read
    status = this->invoke_to_read(0, Drv::ptrToU32(this->buf1), 4, this->buf2, 4, 0);
    ASSERT_EQ(status, SPW_REQUEST_STATUS_ERROR);
    ASSERT_EVENTS_SPWManager_SpaceWireInitializationError_SIZE(1);
    // sync write
    status = this->invoke_to_write(0, Drv::ptrToU32(this->buf1), 4, this->buf2, 4, 0);
    ASSERT_EQ(status, SPW_REQUEST_STATUS_ERROR);
    ASSERT_EVENTS_SPWManager_SpaceWireInitializationError_SIZE(2);
    // async write
    status = this->invoke_to_writeAsync(0, Drv::ptrToU32(this->buf3), sizeof(this->buf2), this->buf2, sizeof(this->buf2), 10);
    ASSERT_EQ(status, SPW_REQUEST_STATUS_ACCEPTED);
    this->invoke_to_schedIn(0, 0);
    this->component.doDispatch();
    ASSERT_from_statusOut_SIZE(1);
    ASSERT_from_statusOut(0, SPW_REQUEST_STATUS_ERROR);
    ASSERT_EVENTS_SPWManager_SpaceWireInitializationError_SIZE(3);
    // reset command
    this->sendCmd_SPWMGR_RESET_LINK(INSTANCE, CMD_SEQ);
    this->component.doDispatch();
    ASSERT_CMD_RESPONSE(0, SPWManagerComponentImpl::OPCODE_SPWMGR_RESET_LINK, CMD_SEQ, Fw::COMMAND_EXECUTION_ERROR);
    ASSERT_EVENTS_SPWManager_SpaceWireInitializationError_SIZE(4);
    // reset port
    this->invoke_to_resetLink(0);
    this->component.doDispatch();
    ASSERT_EVENTS_SPWManager_SpaceWireInitializationError_SIZE(5);
    // done
    this->spwDriverInitError = false;
    this->clearHistory();

    // init error
    this->setTestTime(Fw::Time(100, 0));
    this->spwDriverDiscError = true;
    // sync read
    status = this->invoke_to_read(0, Drv::ptrToU32(this->buf1), 4, this->buf2, 4, 0);
    ASSERT_EQ(status, SPW_REQUEST_STATUS_ERROR);
    ASSERT_EVENTS_SPWManager_SpaceWireLinkDisconnected_SIZE(1);
    // sync write
    status = this->invoke_to_write(0, Drv::ptrToU32(this->buf1), 4, this->buf2, 4, 0);
    ASSERT_EQ(status, SPW_REQUEST_STATUS_ERROR);
    ASSERT_EVENTS_SPWManager_SpaceWireLinkDisconnected_SIZE(2);
    // async write
    status = this->invoke_to_writeAsync(0, Drv::ptrToU32(this->buf3), sizeof(this->buf2), this->buf2, sizeof(this->buf2), 10);
    ASSERT_EQ(status, SPW_REQUEST_STATUS_ACCEPTED);
    this->invoke_to_schedIn(0, 0);
    this->component.doDispatch();
    ASSERT_from_statusOut_SIZE(1);
    ASSERT_from_statusOut(0, SPW_REQUEST_STATUS_ERROR);
    ASSERT_EVENTS_SPWManager_SpaceWireLinkDisconnected_SIZE(3);
    // reset command
    this->sendCmd_SPWMGR_RESET_LINK(INSTANCE, CMD_SEQ);
    this->component.doDispatch();
    ASSERT_CMD_RESPONSE(0, SPWManagerComponentImpl::OPCODE_SPWMGR_RESET_LINK, CMD_SEQ, Fw::COMMAND_EXECUTION_ERROR);
    ASSERT_EVENTS_SPWManager_SpaceWireLinkDisconnected_SIZE(4);
    // reset port
    this->invoke_to_resetLink(0);
    this->component.doDispatch();
    ASSERT_EVENTS_SPWManager_SpaceWireLinkDisconnected_SIZE(5);
    // done
    this->spwDriverDiscError = false;
    this->clearHistory();

    // EEP error
    this->setTestTime(Fw::Time(200, 0));
    this->spwDriverEEPError = true;
    // sync read
    status = this->invoke_to_read(0, Drv::ptrToU32(this->buf1), 4, this->buf2, 4, 0);
    ASSERT_EQ(status, SPW_REQUEST_STATUS_ERROR);
    ASSERT_EVENTS_SPWManager_SpaceWireError_SIZE(1);
    ASSERT_EVENTS_SPWManager_SpaceWireError(0, component.toSpaceWireError_status(SPW_STATUS_ERR_RX_EEP), SPW_STATUS_ERR_RX_EEP);
    // sync write
    status = this->invoke_to_write(0, Drv::ptrToU32(this->buf1), 4, this->buf2, 4, 0);
    ASSERT_EQ(status, SPW_REQUEST_STATUS_ERROR);
    ASSERT_EVENTS_SPWManager_SpaceWireError_SIZE(2);
    ASSERT_EVENTS_SPWManager_SpaceWireError(1, component.toSpaceWireError_status(SPW_STATUS_ERR_RX_EEP), SPW_STATUS_ERR_RX_EEP);
    // async write
    status = this->invoke_to_writeAsync(0, Drv::ptrToU32(this->buf3), sizeof(this->buf2), this->buf2, sizeof(this->buf2), 10);
    ASSERT_EQ(status, SPW_REQUEST_STATUS_ACCEPTED);
    this->invoke_to_schedIn(0, 0);
    this->component.doDispatch();
    ASSERT_from_statusOut_SIZE(1);
    ASSERT_from_statusOut(0, SPW_REQUEST_STATUS_ERROR);
    ASSERT_EVENTS_SPWManager_SpaceWireError_SIZE(3);
    ASSERT_EVENTS_SPWManager_SpaceWireError(2, component.toSpaceWireError_status(SPW_STATUS_ERR_RX_EEP), SPW_STATUS_ERR_RX_EEP);
    // reset is FINE
    this->sendCmd_SPWMGR_RESET_LINK(INSTANCE, CMD_SEQ);
    this->component.doDispatch();
    ASSERT_CMD_RESPONSE(0, SPWManagerComponentImpl::OPCODE_SPWMGR_RESET_LINK, CMD_SEQ, Fw::COMMAND_OK);
    // done
    this->spwDriverEEPError = false;
    this->clearHistory();
  }

  void Tester ::
    testRmapCommands(void) 
  {
    I32 status;
    U32 timeout = 30;

    // basic param
    status = this->invoke_to_setParam(0, this->spwAddr, this->spwKey, 1, 1, 1); // incr, verify, ack
    ASSERT_EQ(status, 0);

    // writes
    this->val1 = 0x9C955654;
    for (U32 i = 0; i < 64; i++) {
      this->val1 = this->val1 * 17;
      this->val2 = 0x0;
      this->val3 = this->val1;
      this->sendCmd_SPWMGR_RMAP_WRITE_WORD(INSTANCE, CMD_SEQ, Drv::ptrToU32(&this->val2), this->val1, timeout);
      this->component.doDispatch();
      ASSERT_CMD_RESPONSE(0, SPWManagerComponentImpl::OPCODE_SPWMGR_RMAP_WRITE_WORD, CMD_SEQ, Fw::COMMAND_OK);
      ASSERT_EVENTS_SPWManager_RMAPWriteResult_SIZE(1);
      ASSERT_EQ(this->val1, this->val3);
      ASSERT_EQ(this->val2, this->val3);
      this->clearHistory();
    }

    // reads
    this->val1 = 0x203E6E9C;
    for (U32 i = 0; i < 64; i++) {
      this->val1 = this->val1 * 19;
      this->sendCmd_SPWMGR_RMAP_READ_WORD(INSTANCE, CMD_SEQ, Drv::ptrToU32(&this->val1), timeout);
      this->component.doDispatch();
      ASSERT_CMD_RESPONSE(0, SPWManagerComponentImpl::OPCODE_SPWMGR_RMAP_READ_WORD, CMD_SEQ, Fw::COMMAND_OK);
      ASSERT_EVENTS_SPWManager_RMAPReadResult_SIZE(1);
      ASSERT_EVENTS_SPWManager_RMAPReadResult(0, Drv::ptrToU32(&this->val1), this->val1);
      this->clearHistory();
    }
  }

  void Tester ::
    testRmapSetParamCommand(void) 
  {
    I32 status;
    U32 timeout = 0;

    // no increment read
    this->sendCmd_SPWMGR_SET_PARAMS(INSTANCE, CMD_SEQ, this->spwAddr, this->spwKey, 0, 1, 1); // no incr, verify, ack
    this->component.doDispatch();
    memset(this->buf1, 0, 8);
    this->buf1[0] = 0x44;
    this->buf1[1] = 0x55;
    this->buf1[2] = 0x77;
    this->buf1[3] = 0x4B;
    memset(this->buf2, 0, 8);
    memcpy(this->buf3, this->buf1, 4);
    memcpy(this->buf3+4, this->buf1, 4);
    status = this->invoke_to_read(0, Drv::ptrToU32(this->buf1), 8, this->buf2, 8, timeout);
    ASSERT_EQ(status, SPW_REQUEST_STATUS_DONE);
    status = memcmp(this->buf2, this->buf3, 8);
    ASSERT_EQ(status, 0);

    // no increment no verify write
    this->sendCmd_SPWMGR_SET_PARAMS(INSTANCE, CMD_SEQ, this->spwAddr, this->spwKey, 0, 0, 1); // no incr, no verify, ack
    this->component.doDispatch();
    memset(this->buf1, 0, 8);
    this->buf1[4] = 0xD6;
    this->buf1[5] = 0x73;
    this->buf1[6] = 0x1E;
    this->buf1[7] = 0x9A;
    memset(this->buf2, 0, 8);
    memset(this->buf3, 0, 8);
    memcpy(this->buf3, this->buf1+4, 4);
    status = this->invoke_to_write(0, Drv::ptrToU32(this->buf2), 8, this->buf1, 8, timeout);
    ASSERT_EQ(status, SPW_REQUEST_STATUS_DONE);
    status = memcmp(this->buf2, this->buf3, 8);
    ASSERT_EQ(status, 0);

    // no verify write
    this->sendCmd_SPWMGR_SET_PARAMS(INSTANCE, CMD_SEQ, this->spwAddr, this->spwKey, 1, 0, 1); // incr, no verify, ack
    this->component.doDispatch();
    this->val1 = 0x18957A83;
    this->val2 = 0x0;
    status = this->invoke_to_write(0, Drv::ptrToU32(&this->val2), sizeof(this->val2), Drv::wordAsBuf(this->val1), sizeof(this->val2), timeout);
    ASSERT_EQ(status, SPW_REQUEST_STATUS_DONE);
    ASSERT_EQ(this->val1, this->val2);

    // no acknowledge write
    this->sendCmd_SPWMGR_SET_PARAMS(INSTANCE, CMD_SEQ, this->spwAddr, this->spwKey, 1, 1, 0); // incr, verify, no ack
    this->component.doDispatch();
    // not guaranteed to be written w/o ack, so just exercise some code paths
    status = this->invoke_to_write(0, Drv::ptrToU32(&this->val2), sizeof(this->val2), Drv::wordAsBuf(this->val1), sizeof(this->val2), timeout);
    ASSERT_EQ(status, SPW_REQUEST_STATUS_DONE);
  }

  void Tester ::
    testRmapSetParamCommandErrors(void) 
  {
    // illegal param value
    this->sendCmd_SPWMGR_SET_PARAMS(INSTANCE, CMD_SEQ, this->spwAddr, this->spwKey, 2, 1, 0);
    this->component.doDispatch();
    ASSERT_CMD_RESPONSE(0, SPWManagerComponentImpl::OPCODE_SPWMGR_SET_PARAMS, CMD_SEQ, Fw::COMMAND_VALIDATION_ERROR);
  }

  void Tester ::
    testResetLinkCommand(void) 
  {
    I32 status;

    // basic param
    status = this->invoke_to_setParam(0, this->spwAddr, this->spwKey, 1, 0, 1); // incr, no verify, ack
    ASSERT_EQ(status, 0);

    // normal reset command
    this->spwDriverReceivedReset = false;
    this->sendCmd_SPWMGR_RESET_LINK(INSTANCE, CMD_SEQ);
    this->component.doDispatch();
    ASSERT_CMD_RESPONSE(0, SPWManagerComponentImpl::OPCODE_SPWMGR_RESET_LINK, CMD_SEQ, Fw::COMMAND_OK);
    ASSERT_EVENTS_SPWManager_ResetLink_SIZE(1);
    ASSERT_EVENTS_SPWManager_ResetLink(0, 0);
    ASSERT_TRUE(this->spwDriverReceivedReset);

    // send long async write
    this->spwDriverSendBound = 100;
    status = this->invoke_to_writeAsync(0, Drv::ptrToU32(this->buf3), sizeof(this->buf2), this->buf2, sizeof(this->buf2), 10);
    ASSERT_EQ(status, SPW_REQUEST_STATUS_ACCEPTED);
    this->invoke_to_schedIn(0, 0);
    this->component.doDispatch();
    ASSERT_from_statusOut_SIZE(0); // not done yet

    // send reset
    this->spwDriverReceivedReset = false;
    this->sendCmd_SPWMGR_RESET_LINK(INSTANCE, CMD_SEQ);
    this->component.doDispatch();
    ASSERT_CMD_RESPONSE(1, SPWManagerComponentImpl::OPCODE_SPWMGR_RESET_LINK, CMD_SEQ, Fw::COMMAND_OK);
    ASSERT_EVENTS_SPWManager_ResetLink_SIZE(2);
    ASSERT_EVENTS_SPWManager_ResetLink(1, 1);
    ASSERT_TRUE(this->spwDriverReceivedReset);

    // request was aborted
    ASSERT_from_statusOut_SIZE(1);
    ASSERT_from_statusOut(0, SPW_REQUEST_STATUS_ABORTED);
    for (U32 i = 0; i < 100; i++) {
    this->invoke_to_schedIn(0, 0);
      this->component.doDispatch();
    }
    ASSERT_from_statusOut_SIZE(1); // no new statuses
  }

  void Tester ::
    testResetLinkPort(void) 
  {
    I32 status;

    // basic param
    status = this->invoke_to_setParam(0, this->spwAddr, this->spwKey, 1, 0, 1); // incr, no verify, ack
    ASSERT_EQ(status, 0);

    // normal reset command
    this->spwDriverReceivedReset = false;
    this->invoke_to_resetLink(0);
    this->component.doDispatch();
    ASSERT_EVENTS_SPWManager_ResetLink_SIZE(1);
    ASSERT_EVENTS_SPWManager_ResetLink(0, 0);
    ASSERT_TRUE(this->spwDriverReceivedReset);

    // send long async write
    this->spwDriverSendBound = 100;
    status = this->invoke_to_writeAsync(0, Drv::ptrToU32(this->buf3), sizeof(this->buf2), this->buf2, sizeof(this->buf2), 10);
    ASSERT_EQ(status, SPW_REQUEST_STATUS_ACCEPTED);
    this->invoke_to_schedIn(0, 0);
    this->component.doDispatch();
    ASSERT_from_statusOut_SIZE(0); // not done yet

    // send reset
    this->spwDriverReceivedReset = false;
    this->invoke_to_resetLink(0);
    this->component.doDispatch();
    ASSERT_EVENTS_SPWManager_ResetLink_SIZE(2);
    ASSERT_EVENTS_SPWManager_ResetLink(1, 1);
    ASSERT_TRUE(this->spwDriverReceivedReset);

    // request was aborted
    ASSERT_from_statusOut_SIZE(1);
    ASSERT_from_statusOut(0, SPW_REQUEST_STATUS_ABORTED);
    for (U32 i = 0; i < 100; i++) {
    this->invoke_to_schedIn(0, 0);
      this->component.doDispatch();
    }
    ASSERT_from_statusOut_SIZE(1); // no new statuses
  }

  // ----------------------------------------------------------------------
  // Handlers for typed from ports
  // ----------------------------------------------------------------------

  I32 Tester ::
    from_driverWriteRMAP_handler(
        const NATIVE_INT_TYPE portNum,
        U8 dest_addr,
        U8 dest_key,
        U32 write_addr,
        U8 *buf_ptr,
        U32 num_bytes,
        U8 increment,
        U8 verify,
        U8 acknowledge
    )
  {
    this->pushFromPortEntry_driverWriteRMAP(dest_addr, dest_key, write_addr, buf_ptr, num_bytes, increment, verify, acknowledge);

    EXPECT_EQ(dest_addr, this->spwAddr);
    EXPECT_EQ(dest_key, this->spwKey);
    if (verify) {
      EXPECT_LE(num_bytes, 4);
    }
    if (increment) {
      EXPECT_EQ(num_bytes % 4, 0);
    }
    EXPECT_GT(num_bytes, 0);

    U32* addr = reinterpret_cast<U32*>((this->addressPrefix << 32L) | write_addr);
    if (increment) {
      memcpy(addr, buf_ptr, num_bytes);
    } else {
      *addr = *reinterpret_cast<U32*>(buf_ptr + (num_bytes - 4));
    }

    this->spwDriverExecuting = true;
    return SPW_STATUS_SUCCESS;
  }

  void Tester ::
    from_statusOut_handler(
        const NATIVE_INT_TYPE portNum,
        I32 spwStatus
    )
  {
    this->pushFromPortEntry_statusOut(spwStatus);
  }

  void Tester ::
    from_PingResponse_handler(
        const NATIVE_INT_TYPE portNum,
        U32 key
    )
  {
    this->pushFromPortEntry_PingResponse(key);
    ASSERT_EQ(key, this->pingKey);
    this->pingResponses++;
  }

  I32 Tester ::
    from_driverReset_handler(
        const NATIVE_INT_TYPE portNum
    )
  {
    this->pushFromPortEntry_driverReset();
    this->spwDriverReceivedReset = true;

    if (this->spwDriverInitError) {
      return SPW_STATUS_ERR_INIT;
    }
    if (this->spwDriverDiscError) {
      return SPW_STATUS_ERR_DISCONNECTED;
    }

    this->spwDriverSendCounter = 0;
    this->spwDriverReceiveCounter = 0;
    return SPW_STATUS_SUCCESS;
  }

  I32 Tester ::
    from_driverReadRMAP_handler(
        const NATIVE_INT_TYPE portNum,
        U8 dest_addr,
        U8 dest_key,
        U32 read_addr,
        U8 *buf_ptr,
        U32 num_bytes,
        U8 increment
    )
  {
    this->pushFromPortEntry_driverReadRMAP(dest_addr, dest_key, read_addr, buf_ptr, num_bytes, increment);

    EXPECT_EQ(dest_addr, this->spwAddr);
    EXPECT_EQ(dest_key, this->spwKey);
    if (increment) {
      EXPECT_EQ(num_bytes % 4, 0);
    }
    EXPECT_GT(num_bytes, 0);

    U32* addr = reinterpret_cast<U32*>((this->addressPrefix << 32L) | read_addr);
    if (increment) {
      memcpy(buf_ptr + RMAP_READ_RESPONSE_HDR_SIZE, addr, num_bytes);
    } else {
      U32* buf_ptr_32 = reinterpret_cast<U32*>(buf_ptr + RMAP_READ_RESPONSE_HDR_SIZE);
      for (U32 i = 0; i < num_bytes/4; i++) {
        buf_ptr_32[i] = addr[0];
      }
    }

    this->spwDriverExecuting = true;
    return SPW_STATUS_SUCCESS;
  }

  I32 Tester ::
    from_driverGetStatus_handler(
        const NATIVE_INT_TYPE portNum
    )
  {
    this->pushFromPortEntry_driverGetStatus();

    if (this->spwDriverInitError) {
      return SPW_STATUS_ERR_INIT;
    }
    if (this->spwDriverDiscError) {
      return SPW_STATUS_ERR_DISCONNECTED;
    }
    if (this->spwDriverEEPError) {
      return SPW_STATUS_ERR_RX_EEP;
    }
    if (this->spwDriverExecuting) {
      if (this->spwDriverSendCounter < this->spwDriverSendBound) {
        this->spwDriverSendCounter++;
        return SPW_STATUS_SENDING;
      }
      if (this->spwDriverReceiveCounter < this->spwDriverReceiveBound) {
        this->spwDriverReceiveCounter++;
        return SPW_STATUS_RECEIVING;
      }
      this->spwDriverSendCounter = 0;
      this->spwDriverReceiveCounter = 0;
      this->spwDriverExecuting = false;
      return SPW_STATUS_SUCCESS;
    }

    return SPW_STATUS_SUCCESS;
  }

  // ----------------------------------------------------------------------
  // Helper methods 
  // ----------------------------------------------------------------------

  void Tester ::
    connectPorts(void) 
  {

    // read
    this->connect_to_read(
        0,
        this->component.get_read_InputPort(0)
    );

    // readAsyncDMA
    this->connect_to_readAsyncDMA(
        0,
        this->component.get_readAsyncDMA_InputPort(0)
    );

    // setParam
    this->connect_to_setParam(
        0,
        this->component.get_setParam_InputPort(0)
    );

    // PingRecv
    this->connect_to_PingRecv(
        0,
        this->component.get_PingRecv_InputPort(0)
    );

    // writeAsync
    this->connect_to_writeAsync(
        0,
        this->component.get_writeAsync_InputPort(0)
    );

    // resetLink
    this->connect_to_resetLink(
        0,
        this->component.get_resetLink_InputPort(0)
    );

    // schedIn
    this->connect_to_schedIn(
        0,
        this->component.get_schedIn_InputPort(0)
    );

    // cmdIn
    this->connect_to_cmdIn(
        0,
        this->component.get_cmdIn_InputPort(0)
    );

    // write
    this->connect_to_write(
        0,
        this->component.get_write_InputPort(0)
    );

    // readAsync
    this->connect_to_readAsync(
        0,
        this->component.get_readAsync_InputPort(0)
    );

    // driverWriteRMAP
    this->component.set_driverWriteRMAP_OutputPort(
        0, 
        this->get_from_driverWriteRMAP(0)
    );

    // cmdRegOut
    this->component.set_cmdRegOut_OutputPort(
        0, 
        this->get_from_cmdRegOut(0)
    );

    // statusOut
    this->component.set_statusOut_OutputPort(
        0, 
        this->get_from_statusOut(0)
    );

    // eventOut
    this->component.set_eventOut_OutputPort(
        0, 
        this->get_from_eventOut(0)
    );

    // PingResponse
    this->component.set_PingResponse_OutputPort(
        0, 
        this->get_from_PingResponse(0)
    );

    // cmdResponseOut
    this->component.set_cmdResponseOut_OutputPort(
        0, 
        this->get_from_cmdResponseOut(0)
    );

    // driverReset
    this->component.set_driverReset_OutputPort(
        0, 
        this->get_from_driverReset(0)
    );

    // driverReadRMAP
    this->component.set_driverReadRMAP_OutputPort(
        0, 
        this->get_from_driverReadRMAP(0)
    );

    // timeCaller
    this->component.set_timeCaller_OutputPort(
        0, 
        this->get_from_timeCaller(0)
    );

    // driverGetStatus
    this->component.set_driverGetStatus_OutputPort(
        0, 
        this->get_from_driverGetStatus(0)
    );

  }

  void Tester ::
    initComponents(void) 
  {
    this->init();
    this->component.init(
        QUEUE_DEPTH, INSTANCE
    );
  }

  void Tester ::
    setSpacewireDelay(const U32 send, const U32 receive) 
  {
    this->spwDriverSendBound = send,
    this->spwDriverSendCounter = 0;
    this->spwDriverReceiveBound = receive,
    this->spwDriverReceiveCounter = 0;
  }

} // end namespace Drv
