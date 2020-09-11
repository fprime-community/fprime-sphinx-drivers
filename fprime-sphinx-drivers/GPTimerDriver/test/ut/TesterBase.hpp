// ======================================================================
// \title  GPTimerDriver/test/ut/TesterBase.hpp
// \author Auto-generated
// \brief  hpp file for GPTimerDriver component test harness base class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
// ======================================================================

#ifndef GPTimerDriver_TESTER_BASE_HPP
#define GPTimerDriver_TESTER_BASE_HPP

#include <fprime-sphinx-drivers/GPTimerDriver/GPTimerDriverComponentAc.hpp>
#include <Fw/Types/Assert.hpp>
#include <Fw/Comp/PassiveComponentBase.hpp>
#include <stdio.h>
#include <Fw/Port/InputSerializePort.hpp>

namespace Drv {

  //! \class GPTimerDriverTesterBase
  //! \brief Auto-generated base class for GPTimerDriver component test harness
  //!
  class GPTimerDriverTesterBase :
    public Fw::PassiveComponentBase
  {

    public:

      // ----------------------------------------------------------------------
      // Initialization
      // ----------------------------------------------------------------------

      //! Initialize object GPTimerDriverTesterBase
      //!
      virtual void init(
          const NATIVE_INT_TYPE instance = 0 /*!< The instance number*/
      );

    public:

      // ----------------------------------------------------------------------
      // Connectors for 'to' ports
      // Connect these output ports to the input ports under test
      // ----------------------------------------------------------------------

      //! Connect gPTimerDriver_Unclaim to to_gPTimerDriver_Unclaim[portNum]
      //!
      void connect_to_gPTimerDriver_Unclaim(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          Drv::InputGPTimerDriver_UnclaimPort *const gPTimerDriver_Unclaim /*!< The port*/
      );

      //! Connect gPTimerDriver_Claim to to_gPTimerDriver_Claim[portNum]
      //!
      void connect_to_gPTimerDriver_Claim(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          Drv::InputGPTimerDriver_ClaimPort *const gPTimerDriver_Claim /*!< The port*/
      );

      //! Connect gPTimerDriver_ReadControl to to_gPTimerDriver_ReadControl[portNum]
      //!
      void connect_to_gPTimerDriver_ReadControl(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          Drv::InputGPTimerDriver_ReadControlPort *const gPTimerDriver_ReadControl /*!< The port*/
      );

      //! Connect gPTimerDriver_WriteCounter to to_gPTimerDriver_WriteCounter[portNum]
      //!
      void connect_to_gPTimerDriver_WriteCounter(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          Drv::InputGPTimerDriver_WriteCounterPort *const gPTimerDriver_WriteCounter /*!< The port*/
      );

      //! Connect gPTimerDriver_WriteControl to to_gPTimerDriver_WriteControl[portNum]
      //!
      void connect_to_gPTimerDriver_WriteControl(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          Drv::InputGPTimerDriver_WriteControlPort *const gPTimerDriver_WriteControl /*!< The port*/
      );

      //! Connect gPTimerDriver_ReadCounter to to_gPTimerDriver_ReadCounter[portNum]
      //!
      void connect_to_gPTimerDriver_ReadCounter(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          Drv::InputGPTimerDriver_ReadCounterPort *const gPTimerDriver_ReadCounter /*!< The port*/
      );

      //! Connect gPTimerDriver_ReadReload to to_gPTimerDriver_ReadReload[portNum]
      //!
      void connect_to_gPTimerDriver_ReadReload(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          Drv::InputGPTimerDriver_ReadReloadPort *const gPTimerDriver_ReadReload /*!< The port*/
      );

      //! Connect gPTimerDriver_WriteReload to to_gPTimerDriver_WriteReload[portNum]
      //!
      void connect_to_gPTimerDriver_WriteReload(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          Drv::InputGPTimerDriver_WriteReloadPort *const gPTimerDriver_WriteReload /*!< The port*/
      );

    protected:

      // ----------------------------------------------------------------------
      // Construction and destruction
      // ----------------------------------------------------------------------

      //! Construct object GPTimerDriverTesterBase
      //!
      GPTimerDriverTesterBase(
#if FW_OBJECT_NAMES == 1
          const char *const compName, /*!< The component name*/
          const U32 maxHistorySize /*!< The maximum size of each history*/
#else
          const U32 maxHistorySize /*!< The maximum size of each history*/
#endif
      );

      //! Destroy object GPTimerDriverTesterBase
      //!
      virtual ~GPTimerDriverTesterBase(void);

    protected:

      // ----------------------------------------------------------------------
      // Invocation functions for to ports
      // ----------------------------------------------------------------------

      //! Invoke the to port connected to gPTimerDriver_Unclaim
      //!
      void invoke_to_gPTimerDriver_Unclaim(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          I8 timer 
      );

      //! Invoke the to port connected to gPTimerDriver_Claim
      //!
      I8 invoke_to_gPTimerDriver_Claim(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          I8 timer 
      );

      //! Invoke the to port connected to gPTimerDriver_ReadControl
      //!
      U32 invoke_to_gPTimerDriver_ReadControl(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          I8 timer 
      );

      //! Invoke the to port connected to gPTimerDriver_WriteCounter
      //!
      void invoke_to_gPTimerDriver_WriteCounter(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          I8 timer, 
          U32 counter 
      );

      //! Invoke the to port connected to gPTimerDriver_WriteControl
      //!
      void invoke_to_gPTimerDriver_WriteControl(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          I8 timer, 
          U32 control 
      );

      //! Invoke the to port connected to gPTimerDriver_ReadCounter
      //!
      U32 invoke_to_gPTimerDriver_ReadCounter(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          I8 timer 
      );

      //! Invoke the to port connected to gPTimerDriver_ReadReload
      //!
      U32 invoke_to_gPTimerDriver_ReadReload(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          I8 timer 
      );

      //! Invoke the to port connected to gPTimerDriver_WriteReload
      //!
      void invoke_to_gPTimerDriver_WriteReload(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          I8 timer, 
          U32 reload 
      );

    public:

      // ----------------------------------------------------------------------
      // Getters for port counts
      // ----------------------------------------------------------------------

      //! Get the number of to_gPTimerDriver_Unclaim ports
      //!
      //! \return The number of to_gPTimerDriver_Unclaim ports
      //!
      NATIVE_INT_TYPE getNum_to_gPTimerDriver_Unclaim(void) const;

      //! Get the number of to_gPTimerDriver_Claim ports
      //!
      //! \return The number of to_gPTimerDriver_Claim ports
      //!
      NATIVE_INT_TYPE getNum_to_gPTimerDriver_Claim(void) const;

      //! Get the number of to_gPTimerDriver_ReadControl ports
      //!
      //! \return The number of to_gPTimerDriver_ReadControl ports
      //!
      NATIVE_INT_TYPE getNum_to_gPTimerDriver_ReadControl(void) const;

      //! Get the number of to_gPTimerDriver_WriteCounter ports
      //!
      //! \return The number of to_gPTimerDriver_WriteCounter ports
      //!
      NATIVE_INT_TYPE getNum_to_gPTimerDriver_WriteCounter(void) const;

      //! Get the number of to_gPTimerDriver_WriteControl ports
      //!
      //! \return The number of to_gPTimerDriver_WriteControl ports
      //!
      NATIVE_INT_TYPE getNum_to_gPTimerDriver_WriteControl(void) const;

      //! Get the number of to_gPTimerDriver_ReadCounter ports
      //!
      //! \return The number of to_gPTimerDriver_ReadCounter ports
      //!
      NATIVE_INT_TYPE getNum_to_gPTimerDriver_ReadCounter(void) const;

      //! Get the number of to_gPTimerDriver_ReadReload ports
      //!
      //! \return The number of to_gPTimerDriver_ReadReload ports
      //!
      NATIVE_INT_TYPE getNum_to_gPTimerDriver_ReadReload(void) const;

      //! Get the number of to_gPTimerDriver_WriteReload ports
      //!
      //! \return The number of to_gPTimerDriver_WriteReload ports
      //!
      NATIVE_INT_TYPE getNum_to_gPTimerDriver_WriteReload(void) const;

    protected:

      // ----------------------------------------------------------------------
      // Connection status for to ports
      // ----------------------------------------------------------------------

      //! Check whether port is connected
      //!
      //! Whether to_gPTimerDriver_Unclaim[portNum] is connected
      //!
      bool isConnected_to_gPTimerDriver_Unclaim(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

      //! Check whether port is connected
      //!
      //! Whether to_gPTimerDriver_Claim[portNum] is connected
      //!
      bool isConnected_to_gPTimerDriver_Claim(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

      //! Check whether port is connected
      //!
      //! Whether to_gPTimerDriver_ReadControl[portNum] is connected
      //!
      bool isConnected_to_gPTimerDriver_ReadControl(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

      //! Check whether port is connected
      //!
      //! Whether to_gPTimerDriver_WriteCounter[portNum] is connected
      //!
      bool isConnected_to_gPTimerDriver_WriteCounter(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

      //! Check whether port is connected
      //!
      //! Whether to_gPTimerDriver_WriteControl[portNum] is connected
      //!
      bool isConnected_to_gPTimerDriver_WriteControl(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

      //! Check whether port is connected
      //!
      //! Whether to_gPTimerDriver_ReadCounter[portNum] is connected
      //!
      bool isConnected_to_gPTimerDriver_ReadCounter(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

      //! Check whether port is connected
      //!
      //! Whether to_gPTimerDriver_ReadReload[portNum] is connected
      //!
      bool isConnected_to_gPTimerDriver_ReadReload(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

      //! Check whether port is connected
      //!
      //! Whether to_gPTimerDriver_WriteReload[portNum] is connected
      //!
      bool isConnected_to_gPTimerDriver_WriteReload(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

    private:

      // ----------------------------------------------------------------------
      // To ports
      // ----------------------------------------------------------------------

      //! To port connected to gPTimerDriver_Unclaim
      //!
      Drv::OutputGPTimerDriver_UnclaimPort m_to_gPTimerDriver_Unclaim[1];

      //! To port connected to gPTimerDriver_Claim
      //!
      Drv::OutputGPTimerDriver_ClaimPort m_to_gPTimerDriver_Claim[1];

      //! To port connected to gPTimerDriver_ReadControl
      //!
      Drv::OutputGPTimerDriver_ReadControlPort m_to_gPTimerDriver_ReadControl[1];

      //! To port connected to gPTimerDriver_WriteCounter
      //!
      Drv::OutputGPTimerDriver_WriteCounterPort m_to_gPTimerDriver_WriteCounter[1];

      //! To port connected to gPTimerDriver_WriteControl
      //!
      Drv::OutputGPTimerDriver_WriteControlPort m_to_gPTimerDriver_WriteControl[1];

      //! To port connected to gPTimerDriver_ReadCounter
      //!
      Drv::OutputGPTimerDriver_ReadCounterPort m_to_gPTimerDriver_ReadCounter[1];

      //! To port connected to gPTimerDriver_ReadReload
      //!
      Drv::OutputGPTimerDriver_ReadReloadPort m_to_gPTimerDriver_ReadReload[1];

      //! To port connected to gPTimerDriver_WriteReload
      //!
      Drv::OutputGPTimerDriver_WriteReloadPort m_to_gPTimerDriver_WriteReload[1];

  };

} // end namespace Drv

#endif
