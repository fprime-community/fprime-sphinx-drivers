// ====================================================================== 
// \title  NORFlashDriverImpl.hpp
// \author ortega
// \brief  hpp file for NORFlashDriver component implementation class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
// ====================================================================== 

#ifndef NORFlashDriver_HPP
#define NORFlashDriver_HPP

#include "fprime-sphinx-drivers/NORFlashDriver/NORFlashDriverComponentAc.hpp"
#include "fprime-sphinx-drivers/Include/config.hpp"

namespace Drv {


  class NORFlashDriverComponentImpl :
    public NORFlashDriverComponentBase
  {


    public:

      const static I8 NOR_OK = 0;
      const static I8 NOR_FAILED = 1;

      // ----------------------------------------------------------------------
      // Construction, initialization, and destruction
      // ----------------------------------------------------------------------

      //! Construct object NORFlashDriver
      //!
      NORFlashDriverComponentImpl(
#if FW_OBJECT_NAMES == 1
          const char *const compName //!< The component name
#else
          void
#endif
      );

      //! Initialize object NORFlashDriver
      //!
      void init(
          const NATIVE_INT_TYPE instance = 0 //!< The instance number
      );

      //! Destroy object NORFlashDriver
      //!
      ~NORFlashDriverComponentImpl(void);

    PRIVATE:
      inline I8 write8(U32 address, U8 data);
      inline I8 read8_nocache(U32 address, U8 *data);

      // ----------------------------------------------------------------------
      // Handler implementations for user-defined typed input ports
      // ----------------------------------------------------------------------

      //! Handler implementation for read
      //! Note: synchronous input, call with 1 client only
      I8 read_handler(
          const NATIVE_INT_TYPE portNum, //!< The port number
          U32 dest, 
          U8 *data
      );

      //! Handler implementation for write
      //! Note: synchronous input, call with 1 client only
      I8 write_handler(
          const NATIVE_INT_TYPE portNum, //!< The port number
          U32 dest_addr, 
          U8 src
      );

    };

} // end namespace Drv

#endif
