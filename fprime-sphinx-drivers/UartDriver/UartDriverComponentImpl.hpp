// ====================================================================== 
// \title  UartDriverImpl.hpp
// \author ortega
// \brief  hpp file for UartDriver component implementation class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
// ====================================================================== 

#ifndef UartDriver_HPP
#define UartDriver_HPP

#include "fprime-sphinx-drivers/UartDriver/UartDriverComponentAc.hpp"
#include <Fw/Types/EightyCharString.hpp>

extern "C" {
#ifdef TGT_OS_TYPE_VXWORKS
#include <selectLib.h>
#elif TGT_OS_TYPE_LINUX || TGT_OS_TYPE_DARWIN
#include <sys/select.h>
#endif
}

namespace Drv {

  class UartDriverComponentImpl :
    public UartDriverComponentBase
  {

    public:

      // ----------------------------------------------------------------------
      // Construction, initialization, and destruction
      // ----------------------------------------------------------------------

      //! Construct object UartDriver
      //!
      UartDriverComponentImpl(
#if FW_OBJECT_NAMES == 1
          const char *const compName, //!< The component name
          const char *deviceName,
          const U32 baudrate
#else
          const char *deviceName,
          const U32 baudrate
#endif
      );

      //! Initialize object UartDriver
      //!
      void init(
          const NATIVE_INT_TYPE instance = 0 //!< The instance number
      );

      //! Destroy object UartDriver
      //!
      ~UartDriverComponentImpl(void);

    PRIVATE:

      struct timeval ts;
      fd_set readfds;

      //! Handler implementation for WriteSerial
      //!
      void WriteSerial_handler(
          const NATIVE_INT_TYPE portNum, //!< The port number
          Fw::Buffer &fwBuffer
      );

      void ReadSerial_handler(
          const NATIVE_INT_TYPE portNum, //!< The port number
          Fw::Buffer &fwBuffer
      );

        NATIVE_INT_TYPE m_serialFd;
        U32 m_baudrate;
        Fw::EightyCharString m_deviceName;
    };

} // end namespace Drv

#endif
