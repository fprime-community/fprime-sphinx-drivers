// ======================================================================
// \title  FpgaGpioDriver/test/ut/TesterBase.hpp
// \author Auto-generated
// \brief  hpp file for FpgaGpioDriver component test harness base class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
// ======================================================================

#ifndef FpgaGpioDriver_TESTER_BASE_HPP
#define FpgaGpioDriver_TESTER_BASE_HPP

#include <fprime-sphinx-drivers/FpgaGpioDriver/FpgaGpioDriverComponentAc.hpp>
#include <Fw/Types/Assert.hpp>
#include <Fw/Comp/PassiveComponentBase.hpp>
#include <stdio.h>
#include <Fw/Port/InputSerializePort.hpp>

namespace Drv {

  //! \class FpgaGpioDriverTesterBase
  //! \brief Auto-generated base class for FpgaGpioDriver component test harness
  //!
  class FpgaGpioDriverTesterBase :
    public Fw::PassiveComponentBase
  {

    public:

      // ----------------------------------------------------------------------
      // Initialization
      // ----------------------------------------------------------------------

      //! Initialize object FpgaGpioDriverTesterBase
      //!
      virtual void init(
          const NATIVE_INT_TYPE instance = 0 /*!< The instance number*/
      );

    public:

      // ----------------------------------------------------------------------
      // Connectors for 'to' ports
      // Connect these output ports to the input ports under test
      // ----------------------------------------------------------------------

      //! Connect setPin to to_setPin[portNum]
      //!
      void connect_to_setPin(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          Drv::InputSphinxGPIO_WritePinPort *const setPin /*!< The port*/
      );

      //! Connect clearPin to to_clearPin[portNum]
      //!
      void connect_to_clearPin(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          Drv::InputSphinxGPIO_WritePinPort *const clearPin /*!< The port*/
      );

      //! Connect readPin to to_readPin[portNum]
      //!
      void connect_to_readPin(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          Drv::InputSphinxGPIO_ReadPinPort *const readPin /*!< The port*/
      );

      //! Connect enablePin to to_enablePin[portNum]
      //!
      void connect_to_enablePin(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          Drv::InputSphinxGPIO_WritePinPort *const enablePin /*!< The port*/
      );

      //! Connect disablePin to to_disablePin[portNum]
      //!
      void connect_to_disablePin(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          Drv::InputSphinxGPIO_WritePinPort *const disablePin /*!< The port*/
      );

    protected:

      // ----------------------------------------------------------------------
      // Construction and destruction
      // ----------------------------------------------------------------------

      //! Construct object FpgaGpioDriverTesterBase
      //!
      FpgaGpioDriverTesterBase(
#if FW_OBJECT_NAMES == 1
          const char *const compName, /*!< The component name*/
          const U32 maxHistorySize /*!< The maximum size of each history*/
#else
          const U32 maxHistorySize /*!< The maximum size of each history*/
#endif
      );

      //! Destroy object FpgaGpioDriverTesterBase
      //!
      virtual ~FpgaGpioDriverTesterBase(void);

    protected:

      // ----------------------------------------------------------------------
      // Invocation functions for to ports
      // ----------------------------------------------------------------------

      //! Invoke the to port connected to setPin
      //!
      I32 invoke_to_setPin(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          U32 pin_num 
      );

      //! Invoke the to port connected to clearPin
      //!
      I32 invoke_to_clearPin(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          U32 pin_num 
      );

      //! Invoke the to port connected to readPin
      //!
      U32 invoke_to_readPin(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          U32 pin_num 
      );

      //! Invoke the to port connected to enablePin
      //!
      I32 invoke_to_enablePin(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          U32 pin_num 
      );

      //! Invoke the to port connected to disablePin
      //!
      I32 invoke_to_disablePin(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          U32 pin_num 
      );

    public:

      // ----------------------------------------------------------------------
      // Getters for port counts
      // ----------------------------------------------------------------------

      //! Get the number of to_setPin ports
      //!
      //! \return The number of to_setPin ports
      //!
      NATIVE_INT_TYPE getNum_to_setPin(void) const;

      //! Get the number of to_clearPin ports
      //!
      //! \return The number of to_clearPin ports
      //!
      NATIVE_INT_TYPE getNum_to_clearPin(void) const;

      //! Get the number of to_readPin ports
      //!
      //! \return The number of to_readPin ports
      //!
      NATIVE_INT_TYPE getNum_to_readPin(void) const;

      //! Get the number of to_enablePin ports
      //!
      //! \return The number of to_enablePin ports
      //!
      NATIVE_INT_TYPE getNum_to_enablePin(void) const;

      //! Get the number of to_disablePin ports
      //!
      //! \return The number of to_disablePin ports
      //!
      NATIVE_INT_TYPE getNum_to_disablePin(void) const;

    protected:

      // ----------------------------------------------------------------------
      // Connection status for to ports
      // ----------------------------------------------------------------------

      //! Check whether port is connected
      //!
      //! Whether to_setPin[portNum] is connected
      //!
      bool isConnected_to_setPin(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

      //! Check whether port is connected
      //!
      //! Whether to_clearPin[portNum] is connected
      //!
      bool isConnected_to_clearPin(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

      //! Check whether port is connected
      //!
      //! Whether to_readPin[portNum] is connected
      //!
      bool isConnected_to_readPin(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

      //! Check whether port is connected
      //!
      //! Whether to_enablePin[portNum] is connected
      //!
      bool isConnected_to_enablePin(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

      //! Check whether port is connected
      //!
      //! Whether to_disablePin[portNum] is connected
      //!
      bool isConnected_to_disablePin(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

    private:

      // ----------------------------------------------------------------------
      // To ports
      // ----------------------------------------------------------------------

      //! To port connected to setPin
      //!
      Drv::OutputSphinxGPIO_WritePinPort m_to_setPin[10];

      //! To port connected to clearPin
      //!
      Drv::OutputSphinxGPIO_WritePinPort m_to_clearPin[10];

      //! To port connected to readPin
      //!
      Drv::OutputSphinxGPIO_ReadPinPort m_to_readPin[10];

      //! To port connected to enablePin
      //!
      Drv::OutputSphinxGPIO_WritePinPort m_to_enablePin[10];

      //! To port connected to disablePin
      //!
      Drv::OutputSphinxGPIO_WritePinPort m_to_disablePin[10];

  };

} // end namespace Drv

#endif
