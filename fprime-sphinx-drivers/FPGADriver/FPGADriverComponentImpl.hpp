// ====================================================================== 
// \title  FPGADriverImpl.hpp
// \author ortega
// \brief  hpp file for FPGADriver component implementation class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
// ====================================================================== 

#ifndef FPGADriver_HPP
#define FPGADriver_HPP

#include "fprime-sphinx-drivers/FPGADriver/FPGADriverComponentAc.hpp"

#define SYS_CLK_RATE_HZ 100
#define MAX_DRIVING_RATE 10
#define RTI_HANDLR_RATE SYS_CLK_RATE_HZ/MAX_DRIVING_RATE

namespace Drv {

  class FPGADriverComponentImpl :
    public FPGADriverComponentBase
  {

    public:

      // ----------------------------------------------------------------------
      // Construction, initialization, and destruction
      // ----------------------------------------------------------------------

      //! Construct object FPGADriver
      //!
      FPGADriverComponentImpl(
#if FW_OBJECT_NAMES == 1
          const char *const compName //!< The component name
#else
          void
#endif
      );

      //! Initialize object FPGADriver
      //!
      void init(
          const NATIVE_INT_TYPE instance = 0 //!< The instance number
      );

      //! Destroy object FPGADriver
      //!
      ~FPGADriverComponentImpl(void);

#ifdef TGT_OS_TYPE_VXWORKS
      static void sphinx_time_rti_handlr(I32 arg);
#else
      static void sphinx_time_rti_handlr(I64 arg);
#endif

    PRIVATE:

      int sphinx_time_go(void);

      // ----------------------------------------------------------------------
      // Handler implementations for user-defined typed input ports
      // ----------------------------------------------------------------------

      //! Handler implementation for read_reg
      //!
      I32 read_reg_handler(
          const NATIVE_INT_TYPE portNum, //!< The port number
          U32 offset, 
          U32 &value 
      );

      //! Handler implementation for write_reg
      //!
      I32 write_reg_handler(
          const NATIVE_INT_TYPE portNum, //!< The port number
          U32 offset, 
          U32 value 
      );
    };

} // end namespace Drv

#endif
