// ======================================================================
// \title  SPWDriver/test/ut/TesterBase.hpp
// \author Auto-generated
// \brief  hpp file for SPWDriver component test harness base class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
// ======================================================================

#ifndef SPWDriver_TESTER_BASE_HPP
#define SPWDriver_TESTER_BASE_HPP

#include <fprime-sphinx-drivers/SPWDriver/SPWDriverComponentAc.hpp>
#include <Fw/Types/Assert.hpp>
#include <Fw/Comp/PassiveComponentBase.hpp>
#include <stdio.h>
#include <Fw/Port/InputSerializePort.hpp>

namespace Drv {

  //! \class SPWDriverTesterBase
  //! \brief Auto-generated base class for SPWDriver component test harness
  //!
  class SPWDriverTesterBase :
    public Fw::PassiveComponentBase
  {

    public:

      // ----------------------------------------------------------------------
      // Initialization
      // ----------------------------------------------------------------------

      //! Initialize object SPWDriverTesterBase
      //!
      virtual void init(
          const NATIVE_INT_TYPE instance = 0 /*!< The instance number*/
      );

    public:

      // ----------------------------------------------------------------------
      // Connectors for 'to' ports
      // Connect these output ports to the input ports under test
      // ----------------------------------------------------------------------

      //! Connect writeRMAP to to_writeRMAP[portNum]
      //!
      void connect_to_writeRMAP(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          Drv::InputSphinxSPW_WriteRMAPPort *const writeRMAP /*!< The port*/
      );

      //! Connect readRMAP to to_readRMAP[portNum]
      //!
      void connect_to_readRMAP(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          Drv::InputSphinxSPW_ReadRMAPPort *const readRMAP /*!< The port*/
      );

      //! Connect reset to to_reset[portNum]
      //!
      void connect_to_reset(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          Drv::InputSphinxSPW_StatusPort *const reset /*!< The port*/
      );

      //! Connect getStatus to to_getStatus[portNum]
      //!
      void connect_to_getStatus(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          Drv::InputSphinxSPW_StatusPort *const getStatus /*!< The port*/
      );

    protected:

      // ----------------------------------------------------------------------
      // Construction and destruction
      // ----------------------------------------------------------------------

      //! Construct object SPWDriverTesterBase
      //!
      SPWDriverTesterBase(
#if FW_OBJECT_NAMES == 1
          const char *const compName, /*!< The component name*/
          const U32 maxHistorySize /*!< The maximum size of each history*/
#else
          const U32 maxHistorySize /*!< The maximum size of each history*/
#endif
      );

      //! Destroy object SPWDriverTesterBase
      //!
      virtual ~SPWDriverTesterBase(void);

    protected:

      // ----------------------------------------------------------------------
      // Invocation functions for to ports
      // ----------------------------------------------------------------------

      //! Invoke the to port connected to writeRMAP
      //!
      I32 invoke_to_writeRMAP(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          U8 dest_addr, 
          U8 dest_key, 
          U32 write_addr, 
          U8 *buf_ptr, 
          U32 num_bytes, 
          U8 increment, 
          U8 verify, 
          U8 acknowledge 
      );

      //! Invoke the to port connected to readRMAP
      //!
      I32 invoke_to_readRMAP(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          U8 dest_addr, 
          U8 dest_key, 
          U32 read_addr, 
          U8 *buf_ptr, 
          U32 num_bytes, 
          U8 increment 
      );

      //! Invoke the to port connected to reset
      //!
      I32 invoke_to_reset(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

      //! Invoke the to port connected to getStatus
      //!
      I32 invoke_to_getStatus(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

    public:

      // ----------------------------------------------------------------------
      // Getters for port counts
      // ----------------------------------------------------------------------

      //! Get the number of to_writeRMAP ports
      //!
      //! \return The number of to_writeRMAP ports
      //!
      NATIVE_INT_TYPE getNum_to_writeRMAP(void) const;

      //! Get the number of to_readRMAP ports
      //!
      //! \return The number of to_readRMAP ports
      //!
      NATIVE_INT_TYPE getNum_to_readRMAP(void) const;

      //! Get the number of to_reset ports
      //!
      //! \return The number of to_reset ports
      //!
      NATIVE_INT_TYPE getNum_to_reset(void) const;

      //! Get the number of to_getStatus ports
      //!
      //! \return The number of to_getStatus ports
      //!
      NATIVE_INT_TYPE getNum_to_getStatus(void) const;

    protected:

      // ----------------------------------------------------------------------
      // Connection status for to ports
      // ----------------------------------------------------------------------

      //! Check whether port is connected
      //!
      //! Whether to_writeRMAP[portNum] is connected
      //!
      bool isConnected_to_writeRMAP(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

      //! Check whether port is connected
      //!
      //! Whether to_readRMAP[portNum] is connected
      //!
      bool isConnected_to_readRMAP(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

      //! Check whether port is connected
      //!
      //! Whether to_reset[portNum] is connected
      //!
      bool isConnected_to_reset(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

      //! Check whether port is connected
      //!
      //! Whether to_getStatus[portNum] is connected
      //!
      bool isConnected_to_getStatus(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

    private:

      // ----------------------------------------------------------------------
      // To ports
      // ----------------------------------------------------------------------

      //! To port connected to writeRMAP
      //!
      Drv::OutputSphinxSPW_WriteRMAPPort m_to_writeRMAP[1];

      //! To port connected to readRMAP
      //!
      Drv::OutputSphinxSPW_ReadRMAPPort m_to_readRMAP[1];

      //! To port connected to reset
      //!
      Drv::OutputSphinxSPW_StatusPort m_to_reset[1];

      //! To port connected to getStatus
      //!
      Drv::OutputSphinxSPW_StatusPort m_to_getStatus[1];

  };

} // end namespace Drv

#endif
