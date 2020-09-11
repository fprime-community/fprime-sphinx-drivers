// ======================================================================
// \title  NORFlashDriver/test/ut/TesterBase.hpp
// \author Auto-generated
// \brief  hpp file for NORFlashDriver component test harness base class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
// ======================================================================

#ifndef NORFlashDriver_TESTER_BASE_HPP
#define NORFlashDriver_TESTER_BASE_HPP

#include <fprime-sphinx-drivers/NORFlashDriver/NORFlashDriverComponentAc.hpp>
#include <Fw/Types/Assert.hpp>
#include <Fw/Comp/PassiveComponentBase.hpp>
#include <stdio.h>
#include <Fw/Port/InputSerializePort.hpp>

namespace Drv {

  //! \class NORFlashDriverTesterBase
  //! \brief Auto-generated base class for NORFlashDriver component test harness
  //!
  class NORFlashDriverTesterBase :
    public Fw::PassiveComponentBase
  {

    public:

      // ----------------------------------------------------------------------
      // Initialization
      // ----------------------------------------------------------------------

      //! Initialize object NORFlashDriverTesterBase
      //!
      virtual void init(
          const NATIVE_INT_TYPE instance = 0 /*!< The instance number*/
      );

    public:

      // ----------------------------------------------------------------------
      // Connectors for 'to' ports
      // Connect these output ports to the input ports under test
      // ----------------------------------------------------------------------

      //! Connect read to to_read[portNum]
      //!
      void connect_to_read(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          Drv::InputNORFlash_ReadBPort *const read /*!< The port*/
      );

      //! Connect write to to_write[portNum]
      //!
      void connect_to_write(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          Drv::InputNORFlash_WriteBPort *const write /*!< The port*/
      );

    protected:

      // ----------------------------------------------------------------------
      // Construction and destruction
      // ----------------------------------------------------------------------

      //! Construct object NORFlashDriverTesterBase
      //!
      NORFlashDriverTesterBase(
#if FW_OBJECT_NAMES == 1
          const char *const compName, /*!< The component name*/
          const U32 maxHistorySize /*!< The maximum size of each history*/
#else
          const U32 maxHistorySize /*!< The maximum size of each history*/
#endif
      );

      //! Destroy object NORFlashDriverTesterBase
      //!
      virtual ~NORFlashDriverTesterBase(void);

    protected:

      // ----------------------------------------------------------------------
      // Invocation functions for to ports
      // ----------------------------------------------------------------------

      //! Invoke the to port connected to read
      //!
      I8 invoke_to_read(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          U32 dest, 
          U8 *data 
      );

      //! Invoke the to port connected to write
      //!
      I8 invoke_to_write(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          U32 dest_addr, 
          U8 src 
      );

    public:

      // ----------------------------------------------------------------------
      // Getters for port counts
      // ----------------------------------------------------------------------

      //! Get the number of to_read ports
      //!
      //! \return The number of to_read ports
      //!
      NATIVE_INT_TYPE getNum_to_read(void) const;

      //! Get the number of to_write ports
      //!
      //! \return The number of to_write ports
      //!
      NATIVE_INT_TYPE getNum_to_write(void) const;

    protected:

      // ----------------------------------------------------------------------
      // Connection status for to ports
      // ----------------------------------------------------------------------

      //! Check whether port is connected
      //!
      //! Whether to_read[portNum] is connected
      //!
      bool isConnected_to_read(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

      //! Check whether port is connected
      //!
      //! Whether to_write[portNum] is connected
      //!
      bool isConnected_to_write(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

    private:

      // ----------------------------------------------------------------------
      // To ports
      // ----------------------------------------------------------------------

      //! To port connected to read
      //!
      Drv::OutputNORFlash_ReadBPort m_to_read[1];

      //! To port connected to write
      //!
      Drv::OutputNORFlash_WriteBPort m_to_write[1];

  };

} // end namespace Drv

#endif
