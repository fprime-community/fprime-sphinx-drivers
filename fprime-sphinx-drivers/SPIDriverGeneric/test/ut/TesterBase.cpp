// ======================================================================
// \title  SPIDriverGeneric/test/ut/TesterBase.cpp
// \author Auto-generated
// \brief  cpp file for SPIDriverGeneric component test harness base class
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

  SPIDriverGenericTesterBase ::
    SPIDriverGenericTesterBase(
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
    this->fromPortHistory_timeCaller =
      new History<FromPortEntry_timeCaller>(maxHistorySize);
    // Clear history
    this->clearHistory();
  }

  SPIDriverGenericTesterBase ::
    ~SPIDriverGenericTesterBase(void) 
  {
  }

  void SPIDriverGenericTesterBase ::
    init(
        const NATIVE_INT_TYPE instance
    )
  {

    // Initialize base class

		Fw::PassiveComponentBase::init(instance);

    // Attach input port timeCaller

    for (
        NATIVE_INT_TYPE _port = 0;
        _port < this->getNum_from_timeCaller();
        ++_port
    ) {

      this->m_from_timeCaller[_port].init();
      this->m_from_timeCaller[_port].addCallComp(
          this,
          from_timeCaller_static
      );
      this->m_from_timeCaller[_port].setPortNum(_port);

#if FW_OBJECT_NAMES == 1
      char _portName[80];
      (void) snprintf(
          _portName,
          sizeof(_portName),
          "%s_from_timeCaller[%d]",
          this->m_objName,
          _port
      );
      this->m_from_timeCaller[_port].setObjName(_portName);
#endif

    }

    // Initialize output port spi_unclaim

    for (
        NATIVE_INT_TYPE _port = 0;
        _port < this->getNum_to_spi_unclaim();
        ++_port
    ) {
      this->m_to_spi_unclaim[_port].init();

#if FW_OBJECT_NAMES == 1
      char _portName[80];
      snprintf(
          _portName,
          sizeof(_portName),
          "%s_to_spi_unclaim[%d]",
          this->m_objName,
          _port
      );
      this->m_to_spi_unclaim[_port].setObjName(_portName);
#endif

    }

    // Initialize output port read_write_16

    for (
        NATIVE_INT_TYPE _port = 0;
        _port < this->getNum_to_read_write_16();
        ++_port
    ) {
      this->m_to_read_write_16[_port].init();

#if FW_OBJECT_NAMES == 1
      char _portName[80];
      snprintf(
          _portName,
          sizeof(_portName),
          "%s_to_read_write_16[%d]",
          this->m_objName,
          _port
      );
      this->m_to_read_write_16[_port].setObjName(_portName);
#endif

    }

    // Initialize output port read_write_32

    for (
        NATIVE_INT_TYPE _port = 0;
        _port < this->getNum_to_read_write_32();
        ++_port
    ) {
      this->m_to_read_write_32[_port].init();

#if FW_OBJECT_NAMES == 1
      char _portName[80];
      snprintf(
          _portName,
          sizeof(_portName),
          "%s_to_read_write_32[%d]",
          this->m_objName,
          _port
      );
      this->m_to_read_write_32[_port].setObjName(_portName);
#endif

    }

    // Initialize output port spi_claim

    for (
        NATIVE_INT_TYPE _port = 0;
        _port < this->getNum_to_spi_claim();
        ++_port
    ) {
      this->m_to_spi_claim[_port].init();

#if FW_OBJECT_NAMES == 1
      char _portName[80];
      snprintf(
          _portName,
          sizeof(_portName),
          "%s_to_spi_claim[%d]",
          this->m_objName,
          _port
      );
      this->m_to_spi_claim[_port].setObjName(_portName);
#endif

    }

    // Initialize output port spi_configure

    for (
        NATIVE_INT_TYPE _port = 0;
        _port < this->getNum_to_spi_configure();
        ++_port
    ) {
      this->m_to_spi_configure[_port].init();

#if FW_OBJECT_NAMES == 1
      char _portName[80];
      snprintf(
          _portName,
          sizeof(_portName),
          "%s_to_spi_configure[%d]",
          this->m_objName,
          _port
      );
      this->m_to_spi_configure[_port].setObjName(_portName);
#endif

    }

    // Initialize output port read_write_8

    for (
        NATIVE_INT_TYPE _port = 0;
        _port < this->getNum_to_read_write_8();
        ++_port
    ) {
      this->m_to_read_write_8[_port].init();

#if FW_OBJECT_NAMES == 1
      char _portName[80];
      snprintf(
          _portName,
          sizeof(_portName),
          "%s_to_read_write_8[%d]",
          this->m_objName,
          _port
      );
      this->m_to_read_write_8[_port].setObjName(_portName);
#endif

    }

  }

  // ----------------------------------------------------------------------
  // Getters for port counts
  // ----------------------------------------------------------------------

  NATIVE_INT_TYPE SPIDriverGenericTesterBase ::
    getNum_to_spi_unclaim(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_to_spi_unclaim);
  }

  NATIVE_INT_TYPE SPIDriverGenericTesterBase ::
    getNum_to_read_write_16(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_to_read_write_16);
  }

  NATIVE_INT_TYPE SPIDriverGenericTesterBase ::
    getNum_from_timeCaller(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_from_timeCaller);
  }

  NATIVE_INT_TYPE SPIDriverGenericTesterBase ::
    getNum_to_read_write_32(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_to_read_write_32);
  }

  NATIVE_INT_TYPE SPIDriverGenericTesterBase ::
    getNum_to_spi_claim(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_to_spi_claim);
  }

  NATIVE_INT_TYPE SPIDriverGenericTesterBase ::
    getNum_to_spi_configure(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_to_spi_configure);
  }

  NATIVE_INT_TYPE SPIDriverGenericTesterBase ::
    getNum_to_read_write_8(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_to_read_write_8);
  }

  // ----------------------------------------------------------------------
  // Connectors for to ports 
  // ----------------------------------------------------------------------

  void SPIDriverGenericTesterBase ::
    connect_to_spi_unclaim(
        const NATIVE_INT_TYPE portNum,
        Drv::InputSphinxSPI_UnclaimPort *const spi_unclaim
    ) 
  {
    FW_ASSERT(portNum < this->getNum_to_spi_unclaim(),static_cast<AssertArg>(portNum));
    this->m_to_spi_unclaim[portNum].addCallPort(spi_unclaim);
  }

  void SPIDriverGenericTesterBase ::
    connect_to_read_write_16(
        const NATIVE_INT_TYPE portNum,
        Drv::InputSphinxSPI_RW16_GenericPort *const read_write_16
    ) 
  {
    FW_ASSERT(portNum < this->getNum_to_read_write_16(),static_cast<AssertArg>(portNum));
    this->m_to_read_write_16[portNum].addCallPort(read_write_16);
  }

  void SPIDriverGenericTesterBase ::
    connect_to_read_write_32(
        const NATIVE_INT_TYPE portNum,
        Drv::InputSphinxSPI_RW32_GenericPort *const read_write_32
    ) 
  {
    FW_ASSERT(portNum < this->getNum_to_read_write_32(),static_cast<AssertArg>(portNum));
    this->m_to_read_write_32[portNum].addCallPort(read_write_32);
  }

  void SPIDriverGenericTesterBase ::
    connect_to_spi_claim(
        const NATIVE_INT_TYPE portNum,
        Drv::InputSphinxSPI_ClaimPort *const spi_claim
    ) 
  {
    FW_ASSERT(portNum < this->getNum_to_spi_claim(),static_cast<AssertArg>(portNum));
    this->m_to_spi_claim[portNum].addCallPort(spi_claim);
  }

  void SPIDriverGenericTesterBase ::
    connect_to_spi_configure(
        const NATIVE_INT_TYPE portNum,
        Drv::InputSphinxSPI_ConfigurePort *const spi_configure
    ) 
  {
    FW_ASSERT(portNum < this->getNum_to_spi_configure(),static_cast<AssertArg>(portNum));
    this->m_to_spi_configure[portNum].addCallPort(spi_configure);
  }

  void SPIDriverGenericTesterBase ::
    connect_to_read_write_8(
        const NATIVE_INT_TYPE portNum,
        Drv::InputSphinxSPI_RW_GenericPort *const read_write_8
    ) 
  {
    FW_ASSERT(portNum < this->getNum_to_read_write_8(),static_cast<AssertArg>(portNum));
    this->m_to_read_write_8[portNum].addCallPort(read_write_8);
  }


  // ----------------------------------------------------------------------
  // Invocation functions for to ports
  // ----------------------------------------------------------------------

  I32 SPIDriverGenericTesterBase ::
    invoke_to_spi_unclaim(
        const NATIVE_INT_TYPE portNum
    )
  {
    FW_ASSERT(portNum < this->getNum_to_spi_unclaim(),static_cast<AssertArg>(portNum));
    FW_ASSERT(portNum < this->getNum_to_spi_unclaim(),static_cast<AssertArg>(portNum));
    return this->m_to_spi_unclaim[portNum].invoke(
        
    );
  }

  I32 SPIDriverGenericTesterBase ::
    invoke_to_read_write_16(
        const NATIVE_INT_TYPE portNum,
        U16 *write_buf_ptr,
        U16 *read_buf_ptr,
        U32 nWords,
        U32 timeout_uS
    )
  {
    FW_ASSERT(portNum < this->getNum_to_read_write_16(),static_cast<AssertArg>(portNum));
    FW_ASSERT(portNum < this->getNum_to_read_write_16(),static_cast<AssertArg>(portNum));
    return this->m_to_read_write_16[portNum].invoke(
        write_buf_ptr, read_buf_ptr, nWords, timeout_uS
    );
  }

  I32 SPIDriverGenericTesterBase ::
    invoke_to_read_write_32(
        const NATIVE_INT_TYPE portNum,
        U32 *write_buf_ptr,
        U32 *read_buf_ptr,
        U32 nWords,
        U32 timeout_uS
    )
  {
    FW_ASSERT(portNum < this->getNum_to_read_write_32(),static_cast<AssertArg>(portNum));
    FW_ASSERT(portNum < this->getNum_to_read_write_32(),static_cast<AssertArg>(portNum));
    return this->m_to_read_write_32[portNum].invoke(
        write_buf_ptr, read_buf_ptr, nWords, timeout_uS
    );
  }

  I32 SPIDriverGenericTesterBase ::
    invoke_to_spi_claim(
        const NATIVE_INT_TYPE portNum
    )
  {
    FW_ASSERT(portNum < this->getNum_to_spi_claim(),static_cast<AssertArg>(portNum));
    FW_ASSERT(portNum < this->getNum_to_spi_claim(),static_cast<AssertArg>(portNum));
    return this->m_to_spi_claim[portNum].invoke(
        
    );
  }

  I32 SPIDriverGenericTesterBase ::
    invoke_to_spi_configure(
        const NATIVE_INT_TYPE portNum,
        U8 loopback_mode,
        U8 clock_polarity,
        U8 clock_phase,
        U8 div_clock_16,
        U8 reverse_mode,
        U8 word_len,
        U8 prescale_modulus,
        U8 prescale_modulus_factor,
        U8 clock_gap
    )
  {
    FW_ASSERT(portNum < this->getNum_to_spi_configure(),static_cast<AssertArg>(portNum));
    FW_ASSERT(portNum < this->getNum_to_spi_configure(),static_cast<AssertArg>(portNum));
    return this->m_to_spi_configure[portNum].invoke(
        loopback_mode, clock_polarity, clock_phase, div_clock_16, reverse_mode, word_len, prescale_modulus, prescale_modulus_factor, clock_gap
    );
  }

  I32 SPIDriverGenericTesterBase ::
    invoke_to_read_write_8(
        const NATIVE_INT_TYPE portNum,
        U8 *write_buf_ptr,
        U8 *read_buf_ptr,
        U32 nWords,
        U32 timeout_uS
    )
  {
    FW_ASSERT(portNum < this->getNum_to_read_write_8(),static_cast<AssertArg>(portNum));
    FW_ASSERT(portNum < this->getNum_to_read_write_8(),static_cast<AssertArg>(portNum));
    return this->m_to_read_write_8[portNum].invoke(
        write_buf_ptr, read_buf_ptr, nWords, timeout_uS
    );
  }

  // ----------------------------------------------------------------------
  // Connection status for to ports
  // ----------------------------------------------------------------------

  bool SPIDriverGenericTesterBase ::
    isConnected_to_spi_unclaim(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_to_spi_unclaim(), static_cast<AssertArg>(portNum));
    return this->m_to_spi_unclaim[portNum].isConnected();
  }

  bool SPIDriverGenericTesterBase ::
    isConnected_to_read_write_16(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_to_read_write_16(), static_cast<AssertArg>(portNum));
    return this->m_to_read_write_16[portNum].isConnected();
  }

  bool SPIDriverGenericTesterBase ::
    isConnected_to_read_write_32(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_to_read_write_32(), static_cast<AssertArg>(portNum));
    return this->m_to_read_write_32[portNum].isConnected();
  }

  bool SPIDriverGenericTesterBase ::
    isConnected_to_spi_claim(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_to_spi_claim(), static_cast<AssertArg>(portNum));
    return this->m_to_spi_claim[portNum].isConnected();
  }

  bool SPIDriverGenericTesterBase ::
    isConnected_to_spi_configure(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_to_spi_configure(), static_cast<AssertArg>(portNum));
    return this->m_to_spi_configure[portNum].isConnected();
  }

  bool SPIDriverGenericTesterBase ::
    isConnected_to_read_write_8(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_to_read_write_8(), static_cast<AssertArg>(portNum));
    return this->m_to_read_write_8[portNum].isConnected();
  }

  // ----------------------------------------------------------------------
  // Getters for from ports
  // ----------------------------------------------------------------------
 
  Fw::InputTimePort *SPIDriverGenericTesterBase ::
    get_from_timeCaller(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_from_timeCaller(),static_cast<AssertArg>(portNum));
    return &this->m_from_timeCaller[portNum];
  }

  // ----------------------------------------------------------------------
  // Static functions for from ports
  // ----------------------------------------------------------------------

  void SPIDriverGenericTesterBase ::
    from_timeCaller_static(
        Fw::PassiveComponentBase *const callComp,
        const NATIVE_INT_TYPE portNum,
        Fw::Time &time
    )
  {
    FW_ASSERT(callComp);
    SPIDriverGenericTesterBase* _testerBase = 
      static_cast<SPIDriverGenericTesterBase*>(callComp);
    _testerBase->from_timeCaller_handlerBase(
        portNum,
        time
    );
  }

  // ----------------------------------------------------------------------
  // Histories for typed from ports
  // ----------------------------------------------------------------------

  void SPIDriverGenericTesterBase ::
    clearFromPortHistory(void)
  {
    this->fromPortHistorySize = 0;
    this->fromPortHistory_timeCaller->clear();
  }

  // ---------------------------------------------------------------------- 
  // From port: timeCaller
  // ---------------------------------------------------------------------- 

  void SPIDriverGenericTesterBase ::
    pushFromPortEntry_timeCaller(
        Fw::Time &time
    )
  {
    FromPortEntry_timeCaller _e = {
      time
    };
    this->fromPortHistory_timeCaller->push_back(_e);
    ++this->fromPortHistorySize;
  }

  // ----------------------------------------------------------------------
  // Handler base functions for from ports
  // ----------------------------------------------------------------------

  void SPIDriverGenericTesterBase ::
    from_timeCaller_handlerBase(
        const NATIVE_INT_TYPE portNum,
        Fw::Time &time
    )
  {
    FW_ASSERT(portNum < this->getNum_from_timeCaller(),static_cast<AssertArg>(portNum));
    this->from_timeCaller_handler(
        portNum,
        time
    );
  }

  // ----------------------------------------------------------------------
  // History 
  // ----------------------------------------------------------------------

  void SPIDriverGenericTesterBase ::
    clearHistory()
  {
    this->clearFromPortHistory();
  }

} // end namespace Drv
