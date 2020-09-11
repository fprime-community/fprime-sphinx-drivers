// ======================================================================
// \title  NORFlashMgrWorker/test/ut/TesterBase.cpp
// \author Auto-generated
// \brief  cpp file for NORFlashMgrWorker component test harness base class
//
// \copyright
// Copyright 2009-2016, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
// ======================================================================

#include <stdlib.h>
#include <string.h>
#include "TesterBase.hpp"

namespace Drv {

  // ----------------------------------------------------------------------
  // Construction, initialization, and destruction
  // ----------------------------------------------------------------------

  NORFlashMgrWorkerTesterBase ::
    NORFlashMgrWorkerTesterBase(
#if FW_OBJECT_NAMES == 1
        const char *const compName,
        const U32 maxHistorySize
#else
        const U32 maxHistorySize
#endif
    ) :
#if FW_OBJECT_NAMES == 1
      Fw::PassiveComponentBase(compName)
#else
      Fw::PassiveComponentBase()
#endif
  {
    // Initialize histories for typed user output ports
    this->fromPortHistory_read =
      new History<FromPortEntry_read>(maxHistorySize);
    this->fromPortHistory_statusOut =
      new History<FromPortEntry_statusOut>(maxHistorySize);
    this->fromPortHistory_write =
      new History<FromPortEntry_write>(maxHistorySize);
    // Clear history
    this->clearHistory();
  }

  NORFlashMgrWorkerTesterBase ::
    ~NORFlashMgrWorkerTesterBase(void) 
  {
  }

  void NORFlashMgrWorkerTesterBase ::
    init(
        const NATIVE_INT_TYPE instance
    )
  {

    // Initialize base class

		Fw::PassiveComponentBase::init(instance);

    // Attach input port read

    for (
        NATIVE_INT_TYPE _port = 0;
        _port < this->getNum_from_read();
        ++_port
    ) {

      this->m_from_read[_port].init();
      this->m_from_read[_port].addCallComp(
          this,
          from_read_static
      );
      this->m_from_read[_port].setPortNum(_port);

#if FW_OBJECT_NAMES == 1
      char _portName[80];
      (void) snprintf(
          _portName,
          sizeof(_portName),
          "%s_from_read[%d]",
          this->m_objName,
          _port
      );
      this->m_from_read[_port].setObjName(_portName);
#endif

    }

    // Attach input port statusOut

    for (
        NATIVE_INT_TYPE _port = 0;
        _port < this->getNum_from_statusOut();
        ++_port
    ) {

      this->m_from_statusOut[_port].init();
      this->m_from_statusOut[_port].addCallComp(
          this,
          from_statusOut_static
      );
      this->m_from_statusOut[_port].setPortNum(_port);

#if FW_OBJECT_NAMES == 1
      char _portName[80];
      (void) snprintf(
          _portName,
          sizeof(_portName),
          "%s_from_statusOut[%d]",
          this->m_objName,
          _port
      );
      this->m_from_statusOut[_port].setObjName(_portName);
#endif

    }

    // Attach input port write

    for (
        NATIVE_INT_TYPE _port = 0;
        _port < this->getNum_from_write();
        ++_port
    ) {

      this->m_from_write[_port].init();
      this->m_from_write[_port].addCallComp(
          this,
          from_write_static
      );
      this->m_from_write[_port].setPortNum(_port);

#if FW_OBJECT_NAMES == 1
      char _portName[80];
      (void) snprintf(
          _portName,
          sizeof(_portName),
          "%s_from_write[%d]",
          this->m_objName,
          _port
      );
      this->m_from_write[_port].setObjName(_portName);
#endif

    }

    // Initialize output port cancel

    for (
        NATIVE_INT_TYPE _port = 0;
        _port < this->getNum_to_cancel();
        ++_port
    ) {
      this->m_to_cancel[_port].init();

#if FW_OBJECT_NAMES == 1
      char _portName[80];
      snprintf(
          _portName,
          sizeof(_portName),
          "%s_to_cancel[%d]",
          this->m_objName,
          _port
      );
      this->m_to_cancel[_port].setObjName(_portName);
#endif

    }

    // Initialize output port erase

    for (
        NATIVE_INT_TYPE _port = 0;
        _port < this->getNum_to_erase();
        ++_port
    ) {
      this->m_to_erase[_port].init();

#if FW_OBJECT_NAMES == 1
      char _portName[80];
      snprintf(
          _portName,
          sizeof(_portName),
          "%s_to_erase[%d]",
          this->m_objName,
          _port
      );
      this->m_to_erase[_port].setObjName(_portName);
#endif

    }

    // Initialize output port reset

    for (
        NATIVE_INT_TYPE _port = 0;
        _port < this->getNum_to_reset();
        ++_port
    ) {
      this->m_to_reset[_port].init();

#if FW_OBJECT_NAMES == 1
      char _portName[80];
      snprintf(
          _portName,
          sizeof(_portName),
          "%s_to_reset[%d]",
          this->m_objName,
          _port
      );
      this->m_to_reset[_port].setObjName(_portName);
#endif

    }

    // Initialize output port verify

    for (
        NATIVE_INT_TYPE _port = 0;
        _port < this->getNum_to_verify();
        ++_port
    ) {
      this->m_to_verify[_port].init();

#if FW_OBJECT_NAMES == 1
      char _portName[80];
      snprintf(
          _portName,
          sizeof(_portName),
          "%s_to_verify[%d]",
          this->m_objName,
          _port
      );
      this->m_to_verify[_port].setObjName(_portName);
#endif

    }

    // Initialize output port write_block

    for (
        NATIVE_INT_TYPE _port = 0;
        _port < this->getNum_to_write_block();
        ++_port
    ) {
      this->m_to_write_block[_port].init();

#if FW_OBJECT_NAMES == 1
      char _portName[80];
      snprintf(
          _portName,
          sizeof(_portName),
          "%s_to_write_block[%d]",
          this->m_objName,
          _port
      );
      this->m_to_write_block[_port].setObjName(_portName);
#endif

    }

    // Initialize output port read_block

    for (
        NATIVE_INT_TYPE _port = 0;
        _port < this->getNum_to_read_block();
        ++_port
    ) {
      this->m_to_read_block[_port].init();

#if FW_OBJECT_NAMES == 1
      char _portName[80];
      snprintf(
          _portName,
          sizeof(_portName),
          "%s_to_read_block[%d]",
          this->m_objName,
          _port
      );
      this->m_to_read_block[_port].setObjName(_portName);
#endif

    }

  }

  // ----------------------------------------------------------------------
  // Getters for port counts
  // ----------------------------------------------------------------------

  NATIVE_INT_TYPE NORFlashMgrWorkerTesterBase ::
    getNum_to_cancel(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_to_cancel);
  }

  NATIVE_INT_TYPE NORFlashMgrWorkerTesterBase ::
    getNum_to_erase(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_to_erase);
  }

  NATIVE_INT_TYPE NORFlashMgrWorkerTesterBase ::
    getNum_from_read(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_from_read);
  }

  NATIVE_INT_TYPE NORFlashMgrWorkerTesterBase ::
    getNum_from_statusOut(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_from_statusOut);
  }

  NATIVE_INT_TYPE NORFlashMgrWorkerTesterBase ::
    getNum_to_reset(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_to_reset);
  }

  NATIVE_INT_TYPE NORFlashMgrWorkerTesterBase ::
    getNum_to_verify(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_to_verify);
  }

  NATIVE_INT_TYPE NORFlashMgrWorkerTesterBase ::
    getNum_to_write_block(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_to_write_block);
  }

  NATIVE_INT_TYPE NORFlashMgrWorkerTesterBase ::
    getNum_from_write(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_from_write);
  }

  NATIVE_INT_TYPE NORFlashMgrWorkerTesterBase ::
    getNum_to_read_block(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_to_read_block);
  }

  // ----------------------------------------------------------------------
  // Connectors for to ports 
  // ----------------------------------------------------------------------

  void NORFlashMgrWorkerTesterBase ::
    connect_to_cancel(
        const NATIVE_INT_TYPE portNum,
        Drv::InputNORFlash_CancelPort *const cancel
    ) 
  {
    FW_ASSERT(portNum < this->getNum_to_cancel(),static_cast<AssertArg>(portNum));
    this->m_to_cancel[portNum].addCallPort(cancel);
  }

  void NORFlashMgrWorkerTesterBase ::
    connect_to_erase(
        const NATIVE_INT_TYPE portNum,
        Drv::InputNORFlash_EraseBankAddrPort *const erase
    ) 
  {
    FW_ASSERT(portNum < this->getNum_to_erase(),static_cast<AssertArg>(portNum));
    this->m_to_erase[portNum].addCallPort(erase);
  }

  void NORFlashMgrWorkerTesterBase ::
    connect_to_reset(
        const NATIVE_INT_TYPE portNum,
        Drv::InputNORFlash_ResetPort *const reset
    ) 
  {
    FW_ASSERT(portNum < this->getNum_to_reset(),static_cast<AssertArg>(portNum));
    this->m_to_reset[portNum].addCallPort(reset);
  }

  void NORFlashMgrWorkerTesterBase ::
    connect_to_verify(
        const NATIVE_INT_TYPE portNum,
        Drv::InputNORFlash_VerifyPort *const verify
    ) 
  {
    FW_ASSERT(portNum < this->getNum_to_verify(),static_cast<AssertArg>(portNum));
    this->m_to_verify[portNum].addCallPort(verify);
  }

  void NORFlashMgrWorkerTesterBase ::
    connect_to_write_block(
        const NATIVE_INT_TYPE portNum,
        Drv::InputNORFlash_BWPort *const write_block
    ) 
  {
    FW_ASSERT(portNum < this->getNum_to_write_block(),static_cast<AssertArg>(portNum));
    this->m_to_write_block[portNum].addCallPort(write_block);
  }

  void NORFlashMgrWorkerTesterBase ::
    connect_to_read_block(
        const NATIVE_INT_TYPE portNum,
        Drv::InputNORFlash_BRPort *const read_block
    ) 
  {
    FW_ASSERT(portNum < this->getNum_to_read_block(),static_cast<AssertArg>(portNum));
    this->m_to_read_block[portNum].addCallPort(read_block);
  }


  // ----------------------------------------------------------------------
  // Invocation functions for to ports
  // ----------------------------------------------------------------------

  void NORFlashMgrWorkerTesterBase ::
    invoke_to_cancel(
        const NATIVE_INT_TYPE portNum
    )
  {
    FW_ASSERT(portNum < this->getNum_to_cancel(),static_cast<AssertArg>(portNum));
    FW_ASSERT(portNum < this->getNum_to_cancel(),static_cast<AssertArg>(portNum));
    this->m_to_cancel[portNum].invoke(
        
    );
  }

  void NORFlashMgrWorkerTesterBase ::
    invoke_to_erase(
        const NATIVE_INT_TYPE portNum,
        U32 bank_addr
    )
  {
    FW_ASSERT(portNum < this->getNum_to_erase(),static_cast<AssertArg>(portNum));
    FW_ASSERT(portNum < this->getNum_to_erase(),static_cast<AssertArg>(portNum));
    this->m_to_erase[portNum].invoke(
        bank_addr
    );
  }

  void NORFlashMgrWorkerTesterBase ::
    invoke_to_reset(
        const NATIVE_INT_TYPE portNum,
        U32 dontcare_addr
    )
  {
    FW_ASSERT(portNum < this->getNum_to_reset(),static_cast<AssertArg>(portNum));
    FW_ASSERT(portNum < this->getNum_to_reset(),static_cast<AssertArg>(portNum));
    this->m_to_reset[portNum].invoke(
        dontcare_addr
    );
  }

  void NORFlashMgrWorkerTesterBase ::
    invoke_to_verify(
        const NATIVE_INT_TYPE portNum,
        U32 blc_filesize,
        U32 fsw_filesize
    )
  {
    FW_ASSERT(portNum < this->getNum_to_verify(),static_cast<AssertArg>(portNum));
    FW_ASSERT(portNum < this->getNum_to_verify(),static_cast<AssertArg>(portNum));
    this->m_to_verify[portNum].invoke(
        blc_filesize, fsw_filesize
    );
  }

  void NORFlashMgrWorkerTesterBase ::
    invoke_to_write_block(
        const NATIVE_INT_TYPE portNum,
        U32 dest,
        U8 *src,
        U32 count,
        U32 bank
    )
  {
    FW_ASSERT(portNum < this->getNum_to_write_block(),static_cast<AssertArg>(portNum));
    FW_ASSERT(portNum < this->getNum_to_write_block(),static_cast<AssertArg>(portNum));
    this->m_to_write_block[portNum].invoke(
        dest, src, count, bank
    );
  }

  void NORFlashMgrWorkerTesterBase ::
    invoke_to_read_block(
        const NATIVE_INT_TYPE portNum,
        U8 *dest,
        U32 src,
        U32 count,
        U32 bank
    )
  {
    FW_ASSERT(portNum < this->getNum_to_read_block(),static_cast<AssertArg>(portNum));
    FW_ASSERT(portNum < this->getNum_to_read_block(),static_cast<AssertArg>(portNum));
    this->m_to_read_block[portNum].invoke(
        dest, src, count, bank
    );
  }

  // ----------------------------------------------------------------------
  // Connection status for to ports
  // ----------------------------------------------------------------------

  bool NORFlashMgrWorkerTesterBase ::
    isConnected_to_cancel(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_to_cancel(), static_cast<AssertArg>(portNum));
    return this->m_to_cancel[portNum].isConnected();
  }

  bool NORFlashMgrWorkerTesterBase ::
    isConnected_to_erase(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_to_erase(), static_cast<AssertArg>(portNum));
    return this->m_to_erase[portNum].isConnected();
  }

  bool NORFlashMgrWorkerTesterBase ::
    isConnected_to_reset(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_to_reset(), static_cast<AssertArg>(portNum));
    return this->m_to_reset[portNum].isConnected();
  }

  bool NORFlashMgrWorkerTesterBase ::
    isConnected_to_verify(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_to_verify(), static_cast<AssertArg>(portNum));
    return this->m_to_verify[portNum].isConnected();
  }

  bool NORFlashMgrWorkerTesterBase ::
    isConnected_to_write_block(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_to_write_block(), static_cast<AssertArg>(portNum));
    return this->m_to_write_block[portNum].isConnected();
  }

  bool NORFlashMgrWorkerTesterBase ::
    isConnected_to_read_block(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_to_read_block(), static_cast<AssertArg>(portNum));
    return this->m_to_read_block[portNum].isConnected();
  }

  // ----------------------------------------------------------------------
  // Getters for from ports
  // ----------------------------------------------------------------------
 
  Drv::InputNORFlash_ReadBPort *NORFlashMgrWorkerTesterBase ::
    get_from_read(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_from_read(),static_cast<AssertArg>(portNum));
    return &this->m_from_read[portNum];
  }

  Drv::InputNOR_donePort *NORFlashMgrWorkerTesterBase ::
    get_from_statusOut(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_from_statusOut(),static_cast<AssertArg>(portNum));
    return &this->m_from_statusOut[portNum];
  }

  Drv::InputNORFlash_WriteBPort *NORFlashMgrWorkerTesterBase ::
    get_from_write(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_from_write(),static_cast<AssertArg>(portNum));
    return &this->m_from_write[portNum];
  }

  // ----------------------------------------------------------------------
  // Static functions for from ports
  // ----------------------------------------------------------------------

  I8 NORFlashMgrWorkerTesterBase ::
    from_read_static(
        Fw::PassiveComponentBase *const callComp,
        const NATIVE_INT_TYPE portNum,
        U32 dest,
        U8 *data
    )
  {
    FW_ASSERT(callComp);
    NORFlashMgrWorkerTesterBase* _testerBase = 
      static_cast<NORFlashMgrWorkerTesterBase*>(callComp);
    return _testerBase->from_read_handlerBase(
        portNum,
        dest, data
    );
  }

  void NORFlashMgrWorkerTesterBase ::
    from_statusOut_static(
        Fw::PassiveComponentBase *const callComp,
        const NATIVE_INT_TYPE portNum,
        I8 done,
        U32 context1,
        U32 context2
    )
  {
    FW_ASSERT(callComp);
    NORFlashMgrWorkerTesterBase* _testerBase = 
      static_cast<NORFlashMgrWorkerTesterBase*>(callComp);
    _testerBase->from_statusOut_handlerBase(
        portNum,
        done, context1, context2
    );
  }

  I8 NORFlashMgrWorkerTesterBase ::
    from_write_static(
        Fw::PassiveComponentBase *const callComp,
        const NATIVE_INT_TYPE portNum,
        U32 dest_addr,
        U8 src
    )
  {
    FW_ASSERT(callComp);
    NORFlashMgrWorkerTesterBase* _testerBase = 
      static_cast<NORFlashMgrWorkerTesterBase*>(callComp);
    return _testerBase->from_write_handlerBase(
        portNum,
        dest_addr, src
    );
  }

  // ----------------------------------------------------------------------
  // Histories for typed from ports
  // ----------------------------------------------------------------------

  void NORFlashMgrWorkerTesterBase ::
    clearFromPortHistory(void)
  {
    this->fromPortHistorySize = 0;
    this->fromPortHistory_read->clear();
    this->fromPortHistory_statusOut->clear();
    this->fromPortHistory_write->clear();
  }

  // ---------------------------------------------------------------------- 
  // From port: read
  // ---------------------------------------------------------------------- 

  void NORFlashMgrWorkerTesterBase ::
    pushFromPortEntry_read(
        U32 dest,
        U8 *data
    )
  {
    FromPortEntry_read _e = {
      dest, data
    };
    this->fromPortHistory_read->push_back(_e);
    ++this->fromPortHistorySize;
  }

  // ---------------------------------------------------------------------- 
  // From port: statusOut
  // ---------------------------------------------------------------------- 

  void NORFlashMgrWorkerTesterBase ::
    pushFromPortEntry_statusOut(
        I8 done,
        U32 context1,
        U32 context2
    )
  {
    FromPortEntry_statusOut _e = {
      done, context1, context2
    };
    this->fromPortHistory_statusOut->push_back(_e);
    ++this->fromPortHistorySize;
  }

  // ---------------------------------------------------------------------- 
  // From port: write
  // ---------------------------------------------------------------------- 

  void NORFlashMgrWorkerTesterBase ::
    pushFromPortEntry_write(
        U32 dest_addr,
        U8 src
    )
  {
    FromPortEntry_write _e = {
      dest_addr, src
    };
    this->fromPortHistory_write->push_back(_e);
    ++this->fromPortHistorySize;
  }

  // ----------------------------------------------------------------------
  // Handler base functions for from ports
  // ----------------------------------------------------------------------

  I8 NORFlashMgrWorkerTesterBase ::
    from_read_handlerBase(
        const NATIVE_INT_TYPE portNum,
        U32 dest,
        U8 *data
    )
  {
    FW_ASSERT(portNum < this->getNum_from_read(),static_cast<AssertArg>(portNum));
    return this->from_read_handler(
        portNum,
        dest, data
    );
  }

  void NORFlashMgrWorkerTesterBase ::
    from_statusOut_handlerBase(
        const NATIVE_INT_TYPE portNum,
        I8 done,
        U32 context1,
        U32 context2
    )
  {
    FW_ASSERT(portNum < this->getNum_from_statusOut(),static_cast<AssertArg>(portNum));
    this->from_statusOut_handler(
        portNum,
        done, context1, context2
    );
  }

  I8 NORFlashMgrWorkerTesterBase ::
    from_write_handlerBase(
        const NATIVE_INT_TYPE portNum,
        U32 dest_addr,
        U8 src
    )
  {
    FW_ASSERT(portNum < this->getNum_from_write(),static_cast<AssertArg>(portNum));
    return this->from_write_handler(
        portNum,
        dest_addr, src
    );
  }

  // ----------------------------------------------------------------------
  // History 
  // ----------------------------------------------------------------------

  void NORFlashMgrWorkerTesterBase ::
    clearHistory()
  {
    this->clearFromPortHistory();
  }

} // end namespace Drv
