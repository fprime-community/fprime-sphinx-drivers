// ======================================================================
// \title  GPIODriver/test/ut/TesterBase.hpp
// \author Auto-generated
// \brief  hpp file for GPIODriver component test harness base class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
// ======================================================================

#ifndef GPIODriver_TESTER_BASE_HPP
#define GPIODriver_TESTER_BASE_HPP

#include <fprime-sphinx-drivers/GPIODriver/GPIODriverComponentAc.hpp>
#include <Fw/Types/Assert.hpp>
#include <Fw/Comp/PassiveComponentBase.hpp>
#include <stdio.h>
#include <Fw/Port/InputSerializePort.hpp>

namespace Drv {

  //! \class GPIODriverTesterBase
  //! \brief Auto-generated base class for GPIODriver component test harness
  //!
  class GPIODriverTesterBase :
    public Fw::PassiveComponentBase
  {

    public:

      // ----------------------------------------------------------------------
      // Initialization
      // ----------------------------------------------------------------------

      //! Initialize object GPIODriverTesterBase
      //!
      virtual void init(
          const NATIVE_INT_TYPE instance = 0 /*!< The instance number*/
      );

    public:

      // ----------------------------------------------------------------------
      // Connectors for 'to' ports
      // Connect these output ports to the input ports under test
      // ----------------------------------------------------------------------

      //! Connect gpio_readPin to to_gpio_readPin[portNum]
      //!
      void connect_to_gpio_readPin(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          Drv::InputSphinxGPIO_ReadPinPort *const gpio_readPin /*!< The port*/
      );

      //! Connect gpio_setPin to to_gpio_setPin[portNum]
      //!
      void connect_to_gpio_setPin(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          Drv::InputSphinxGPIO_WritePinPort *const gpio_setPin /*!< The port*/
      );

      //! Connect gpio_clearPin to to_gpio_clearPin[portNum]
      //!
      void connect_to_gpio_clearPin(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          Drv::InputSphinxGPIO_WritePinPort *const gpio_clearPin /*!< The port*/
      );

    protected:

      // ----------------------------------------------------------------------
      // Construction and destruction
      // ----------------------------------------------------------------------

      //! Construct object GPIODriverTesterBase
      //!
      GPIODriverTesterBase(
#if FW_OBJECT_NAMES == 1
          const char *const compName, /*!< The component name*/
          const U32 maxHistorySize /*!< The maximum size of each history*/
#else
          const U32 maxHistorySize /*!< The maximum size of each history*/
#endif
      );

      //! Destroy object GPIODriverTesterBase
      //!
      virtual ~GPIODriverTesterBase(void);

    protected:

      // ----------------------------------------------------------------------
      // Invocation functions for to ports
      // ----------------------------------------------------------------------

      //! Invoke the to port connected to gpio_readPin
      //!
      U32 invoke_to_gpio_readPin(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          U32 pin_num 
      );

      //! Invoke the to port connected to gpio_setPin
      //!
      I32 invoke_to_gpio_setPin(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          U32 pin_num 
      );

      //! Invoke the to port connected to gpio_clearPin
      //!
      I32 invoke_to_gpio_clearPin(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          U32 pin_num 
      );

    public:

      // ----------------------------------------------------------------------
      // Getters for port counts
      // ----------------------------------------------------------------------

      //! Get the number of to_gpio_readPin ports
      //!
      //! \return The number of to_gpio_readPin ports
      //!
      NATIVE_INT_TYPE getNum_to_gpio_readPin(void) const;

      //! Get the number of to_gpio_setPin ports
      //!
      //! \return The number of to_gpio_setPin ports
      //!
      NATIVE_INT_TYPE getNum_to_gpio_setPin(void) const;

      //! Get the number of to_gpio_clearPin ports
      //!
      //! \return The number of to_gpio_clearPin ports
      //!
      NATIVE_INT_TYPE getNum_to_gpio_clearPin(void) const;

    protected:

      // ----------------------------------------------------------------------
      // Connection status for to ports
      // ----------------------------------------------------------------------

      //! Check whether port is connected
      //!
      //! Whether to_gpio_readPin[portNum] is connected
      //!
      bool isConnected_to_gpio_readPin(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

      //! Check whether port is connected
      //!
      //! Whether to_gpio_setPin[portNum] is connected
      //!
      bool isConnected_to_gpio_setPin(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

      //! Check whether port is connected
      //!
      //! Whether to_gpio_clearPin[portNum] is connected
      //!
      bool isConnected_to_gpio_clearPin(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

    private:

      // ----------------------------------------------------------------------
      // To ports
      // ----------------------------------------------------------------------

      //! To port connected to gpio_readPin
      //!
      Drv::OutputSphinxGPIO_ReadPinPort m_to_gpio_readPin[10];

      //! To port connected to gpio_setPin
      //!
      Drv::OutputSphinxGPIO_WritePinPort m_to_gpio_setPin[10];

      //! To port connected to gpio_clearPin
      //!
      Drv::OutputSphinxGPIO_WritePinPort m_to_gpio_clearPin[10];

  };

} // end namespace Drv

#endif
