// ======================================================================
// \title  GPIODriverImpl.hpp
// \author arizvi
// \brief  hpp file for GPIODriver component implementation class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
// ======================================================================

#ifndef GPIODriver_HPP
#define GPIODriver_HPP

#include "fprime-sphinx-drivers/GPIODriver/GPIODriverComponentAc.hpp"
#include "fprime-sphinx-drivers/GPIOInterruptRouter/GPIOInterruptRouter.hpp"
#include "fprime-sphinx-drivers/GPIODriver/test/ut/GPIODriverInterrupt.hpp"
#include <fprime-sphinx-drivers/Util/SphinxDrvBitUtil.hpp>
#include <stdio.h>
#ifdef TGT_OS_TYPE_VXWORKS
extern "C" {
#include <intLib.h>
#include <iv.h>
}
#endif

#define SPHINX_MAX_NUM_GPIOs            64

#define GPIO_APB_1_ADDR                 0x80000900
#define GPIO_APB_2_ADDR                 0x80000A00
#define IRQMP_BASE_ADDR                 0x80000200


#define GPIO_DATA_OFFSET                0x0
#define GPIO_OUT_OFFSET                 0x4
#define GPIO_DIR_OFFSET                 0x8
#define GPIO_INT_MASK_OFFSET            0xC
#define GPIO_INT_POL_OFFSET             0x10
#define GPIO_INT_EDGE_OFFSET            0x14

#define IRQMP_CLEAR_OFFSET              0x0C
#define IRQMP_PROCESSOR0_MASK_OFFSET    0x40

#define GPIO_OUT  1
#define GPIO_IN   0

#define GPIO_MAX_LOOPS 10


namespace Drv {

  class GPIODriverComponentImpl :
    public GPIODriverComponentBase
  {

    public:

      // ----------------------------------------------------------------------
      // Construction, initialization, and destruction
      // ----------------------------------------------------------------------

      //! Construct object GPIODriver
      //!
      GPIODriverComponentImpl(
#if FW_OBJECT_NAMES == 1
          const char *const compName //!< The component name
#endif
      );

      //! Initialize object GPIODriver
      //!
      void init(
          const NATIVE_INT_TYPE instance = 0 //!< The instance number
      );

      //! Destroy object GPIODriver
      //!
      ~GPIODriverComponentImpl(void);


      void init_comp(
            NATIVE_UINT_TYPE pin_nums[],
            NATIVE_UINT_TYPE n_pin_nums,
            NATIVE_UINT_TYPE pin_dir[],
            NATIVE_UINT_TYPE n_pin_dir,
            NATIVE_UINT_TYPE pin_int[],
            NATIVE_UINT_TYPE n_pin_int,
            NATIVE_UINT_TYPE pin_pol[],
            NATIVE_UINT_TYPE n_pin_pol,
            NATIVE_UINT_TYPE pin_edge[],
            NATIVE_UINT_TYPE n_pin_edge,
            GPIOInterruptRouter * int_router = NULL, // default value
            U32 flag = 0
      );

      // Maintain a pointer to an interrupt router
      GPIOInterruptRouter * m_intRouter_p;

      // GPIO Function pointer type; used to point to interrupt handlers
      typedef void (*GPIO_FP)
                   #ifdef TGT_OS_TYPE_VXWORKS
                     (I32 arg);
                   #else 
                     (I64 arg);
                   #endif

    PRIVATE:

      // ----------------------------------------------------------------------
      // Handler implementations for user-defined typed input ports
      // ----------------------------------------------------------------------

      //! Handler implementation for gpio_pin_setup
      //!
      void gpio_pin_setup(
          U32 pin_num,
          U32 direction,
          U32 interrupt,
          U32 polarity,
          U32 edge,
          U32 flag = 0
      );

      U32 gpio_readPin(U32 pin_num);

      //! Handler implementation for gpio_readPin
      //!
      U32 gpio_readPin_handler(
          const NATIVE_INT_TYPE portNum, //!< The port number
          U32 pin_num
      );

      //! Handler implementation for gpio_setPin
      //!
      I32 gpio_setPin_handler(
          const NATIVE_INT_TYPE portNum, //!< The port number
          U32 pin_num
      );

      //! Handler implementation for gpio_clearPin
      //!
      I32 gpio_clearPin_handler(
          const NATIVE_INT_TYPE portNum, //!< The port number
          U32 pin_num
      );

      // Maintain array of function pointers
      static const GPIO_FP m_gpioFuncs[GPIOInterruptRouter::NUM_GPIO_INTS];

    };


    typedef struct gpioPin_t
    {
      NATIVE_UINT_TYPE pin_num;
      NATIVE_UINT_TYPE direction;
      NATIVE_UINT_TYPE interrupt;
      NATIVE_UINT_TYPE polarity;
      NATIVE_UINT_TYPE edge;
    } gpioPin;


    // ----------------------------------------------------------------------
    // Interrupt handling for GPIO interrupts
    // ----------------------------------------------------------------------

    #ifdef TGT_OS_TYPE_VXWORKS
      void GPIOintHandler_Master(I32 arg, GPIOInterruptRouter::GPIOIntNum int_num);
      void GPIOintHandler_1(I32 arg);
      void GPIOintHandler_2(I32 arg);
      void GPIOintHandler_3(I32 arg);
      void GPIOintHandler_4(I32 arg);
      void GPIOintHandler_5(I32 arg);
      void GPIOintHandler_6(I32 arg);
      void GPIOintHandler_7(I32 arg);
      void GPIOintHandler_8(I32 arg);
      void GPIOintHandler_9(I32 arg);
      void GPIOintHandler_10(I32 arg);
      void GPIOintHandler_11(I32 arg);
      void GPIOintHandler_12(I32 arg);
      void GPIOintHandler_13(I32 arg);
      void GPIOintHandler_14(I32 arg);
      void GPIOintHandler_15(I32 arg);
    #else
      void GPIOintHandler_Master(I64 arg, GPIOInterruptRouter::GPIOIntNum int_num);
      void GPIOintHandler_1(I64 arg);
      void GPIOintHandler_2(I64 arg);
      void GPIOintHandler_3(I64 arg);
      void GPIOintHandler_4(I64 arg);
      void GPIOintHandler_5(I64 arg);
      void GPIOintHandler_6(I64 arg);
      void GPIOintHandler_7(I64 arg);
      void GPIOintHandler_8(I64 arg);
      void GPIOintHandler_9(I64 arg);
      void GPIOintHandler_10(I64 arg);
      void GPIOintHandler_11(I64 arg);
      void GPIOintHandler_12(I64 arg);
      void GPIOintHandler_13(I64 arg);
      void GPIOintHandler_14(I64 arg);
      void GPIOintHandler_15(I64 arg);
    #endif

} // end namespace Drv

#endif
