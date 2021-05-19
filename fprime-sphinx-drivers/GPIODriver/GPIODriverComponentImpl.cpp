// ======================================================================
// \title  GPIODriverImpl.cpp
// \author arizvi, amand
// \brief  cpp file for GPIODriver component implementation class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
// ======================================================================


#include <fprime-sphinx-drivers/GPIODriver/GPIODriverComponentImpl.hpp>
#include "Fw/Types/BasicTypes.hpp"
#include "Fw/Types/Assert.hpp"
#include <Os/Log.hpp>

namespace Drv {

  // ----------------------------------------------------------------------
  // Construction, initialization, and destruction
  // ----------------------------------------------------------------------

  GPIODriverComponentImpl ::
#if FW_OBJECT_NAMES == 1
    GPIODriverComponentImpl(
        const char *const compName
    ) :
      GPIODriverComponentBase(compName)
#else
    GPIODriverImpl() :
#endif
  {
    this->m_intRouter_p = 0;
  }


  void GPIODriverComponentImpl ::
    init(
        const NATIVE_INT_TYPE instance
    )
  {
    GPIODriverComponentBase::init(instance);

  }


  GPIODriverComponentImpl ::
    ~GPIODriverComponentImpl(void)
  {

  }


  void GPIODriverComponentImpl :: init_comp(
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
        GPIOInterruptRouter * int_router,
        U32 flag
      )
  {
    FW_ASSERT(n_pin_nums == n_pin_dir);
    FW_ASSERT(n_pin_dir == n_pin_int);
    FW_ASSERT(n_pin_int == n_pin_pol);
    FW_ASSERT(n_pin_pol == n_pin_edge);
    FW_ASSERT(int_router != NULL);

    this->m_intRouter_p = int_router;
    for(U32 i = 0; i < n_pin_nums; i++)
    {
        gpio_pin_setup(pin_nums[i],
                       pin_dir[i],
                       pin_int[i],
                       pin_pol[i],
                       pin_edge[i],
		       flag);
    }
  }


  // ----------------------------------------------------------------------
  // Handler implementations for user-defined typed input ports
  // ----------------------------------------------------------------------

  void GPIODriverComponentImpl ::
    gpio_pin_setup(
        U32 pin_num,
        U32 direction,
        U32 interrupt,
        U32 polarity,
        U32 edge,
        U32 flag
    )
  {
    U32 addr;

    //Check inputs are valid
    FW_ASSERT(pin_num < SPHINX_MAX_NUM_GPIOs);

    // 0=input, 1=output
    FW_ASSERT(direction <= 1);

    // 0=interrupt masked, 1=interrupt enabled
    FW_ASSERT(interrupt <= 1);

    // Interrupts can only be configured as inputs
    if (interrupt) {
      FW_ASSERT(direction == 0);
    }

    // 0=low/falling, 1=high/rising
    FW_ASSERT(polarity <= 1);

    // 0=level, 1=edge
    FW_ASSERT(edge <= 1);

    // Configure pin number
    if (pin_num < SPHINX_MAX_NUM_GPIOs/2) {
      // Use APB1
      addr = GPIO_APB_1_ADDR;
    } else {
      // Use APB2
      addr = GPIO_APB_2_ADDR;
      // Adjust pin_num to be in range
      pin_num -= (SPHINX_MAX_NUM_GPIOs/2);
    }

    // Check pin_num is valid
    FW_ASSERT(pin_num < 32);

    //Set direction (0=input, 1=output)
    if (direction) {
      Drv::setBit(addr + GPIO_DIR_OFFSET, pin_num);
    } else {
      Drv::clearBit(addr + GPIO_DIR_OFFSET, pin_num);
    }

    // Set interrupt (0=interrupt masked, 1=interrupt enabled)
    if (interrupt) {

      // Interrupts should only be setup if a router was passed in
      FW_ASSERT(this->m_intRouter_p != NULL);

      // There are only 15 Interrupt Handlers
      FW_ASSERT((pin_num >= 1) && (pin_num <= 15));

      // Setup interrupt
      Drv::setBit(addr + GPIO_INT_MASK_OFFSET, pin_num);

      // Configure interrupt polarity (0=low/falling, 1=high/rising)
      if (polarity) {
        Drv::setBit(addr + GPIO_INT_POL_OFFSET, pin_num);
      } else {
        Drv::clearBit(addr + GPIO_INT_POL_OFFSET, pin_num);
      }

      // Configure interrupt edge (0=level, 1=high/rising)
      if (edge) {
        Drv::setBit(addr + GPIO_INT_EDGE_OFFSET, pin_num);
      } else {
        Drv::clearBit(addr + GPIO_INT_EDGE_OFFSET, pin_num);
      }

      // Register Interrupt Handler. [pin_num - 1] because pin_num 0 isn't an interrupt
      #ifdef TGT_OS_TYPE_VXWORKS
      I32 status = intConnect(INUM_TO_IVEC(pin_num), (VOIDFUNCPTR)GPIODriverComponentImpl::m_gpioFuncs[pin_num], (I32)this);
      FW_ASSERT(status != ERROR);
      #endif

      // Enable Interrupt
      if(!flag)
      {
        Drv::setBitAtomic(IRQMP_BASE_ADDR + IRQMP_CLEAR_OFFSET, pin_num); // Clear any pending interrupts
        Drv::setBitAtomic(IRQMP_BASE_ADDR + IRQMP_PROCESSOR0_MASK_OFFSET, pin_num); // Enable interrupt
      }

    } else {
      Drv::clearBit(addr + GPIO_INT_MASK_OFFSET, pin_num);
    }

  }

  U32 GPIODriverComponentImpl ::
    gpio_readPin(
        U32 pin_num
    )
  {
    U32 addr;
    U32 read_val;

    //Check inputs are valid
    FW_ASSERT(pin_num < SPHINX_MAX_NUM_GPIOs);

    // Configure pin number
    if (pin_num < SPHINX_MAX_NUM_GPIOs/2) {
      // Use APB1
      addr = GPIO_APB_1_ADDR;
    } else {
      // Use APB2
      addr = GPIO_APB_2_ADDR;
      // Adjust pin_num to be in range
      pin_num -= (SPHINX_MAX_NUM_GPIOs/2);
    }

    // Check pin_num is valid
    FW_ASSERT(pin_num < 32);

    bool isInputPin = Drv::readBit(addr + GPIO_DIR_OFFSET, pin_num) == 0;
    if (isInputPin) {
      // input pin values are read from data reg
      read_val = Drv::readBit(addr + GPIO_DATA_OFFSET, pin_num);
    } else {
      // output pin values are read from output reg
      read_val = Drv::readBit(addr + GPIO_OUT_OFFSET, pin_num);
    }

    return read_val;
  }

  U32 GPIODriverComponentImpl ::
    gpio_readPin_handler(
        const NATIVE_INT_TYPE portNum,
        U32 pin_num
    )
  {
    U32 read_val;

    read_val = this->gpio_readPin(pin_num);

    return read_val;
  }

  I32 GPIODriverComponentImpl ::
    gpio_setPin_handler(
        const NATIVE_INT_TYPE portNum,
        U32 pin_num
    )
  {
    U32 addr;
    U32 read_val;
    U32 i;
    bool second_bank=false;

    //Check inputs are valid
    FW_ASSERT(pin_num < SPHINX_MAX_NUM_GPIOs);

    // Configure pin number
    if (pin_num < SPHINX_MAX_NUM_GPIOs/2) {
      // Use APB1
      addr = GPIO_APB_1_ADDR;
    } else {
      // Use APB2
      addr = GPIO_APB_2_ADDR;
      // Adjust pin_num to be in range
      pin_num -= (SPHINX_MAX_NUM_GPIOs/2);
      // set second_bank to true to be used
      // for read-back verify
      second_bank = true;
    }

    // Check pin_num is valid
    FW_ASSERT(pin_num < 32);

    // Set output pin
    Drv::setBit(addr + GPIO_OUT_OFFSET, pin_num);

    // Adjust pin_num before read-back verification
    if (second_bank) {
      pin_num += (SPHINX_MAX_NUM_GPIOs/2);
    }

    // Verify pin value by read-back
    for(i=0; i<GPIO_MAX_LOOPS; i++) {
      read_val = this->gpio_readPin(pin_num);
      if (read_val == 1) {
        // Successfully set pin
        return 0;
      }
    }

    // Failed to set pin
    return -1;
  }

  I32 GPIODriverComponentImpl ::
    gpio_clearPin_handler(
        const NATIVE_INT_TYPE portNum,
        U32 pin_num
    )
  {
    U32 addr;
    U32 read_val;
    U32 i;
    bool second_bank = false;

    //Check inputs are valid
    FW_ASSERT(pin_num < SPHINX_MAX_NUM_GPIOs);

    // Configure pin number
    if (pin_num < SPHINX_MAX_NUM_GPIOs/2) {
      // Use APB1
      addr = GPIO_APB_1_ADDR;
    } else {
      // Use APB2
      addr = GPIO_APB_2_ADDR;
      // Adjust pin_num to be in range
      pin_num -= (SPHINX_MAX_NUM_GPIOs/2);
      // set second_bank to true to be used
      // for read-back verify
      second_bank = true;
    }

    // Check pin_num is valid
    FW_ASSERT(pin_num < 32);

    // Clear output pin
    Drv::clearBit(addr + GPIO_OUT_OFFSET, pin_num);

    // Adjust pin_num before read-back verification
    if (second_bank) {
      pin_num += (SPHINX_MAX_NUM_GPIOs/2);
    }

    // Verify pin value by read-back
    for(i=0; i<GPIO_MAX_LOOPS; i++) {
      read_val = this->gpio_readPin(pin_num);
      if (read_val == 0) {
        // Successfully cleared pin
        return 0;
      }
    }

    // Failed to clear pin
    return -1;
  }


  // Function called by all GPIO interrupt vectors
  void
  #ifdef TGT_OS_TYPE_VXWORKS
    GPIOintHandler_Master(I32 arg, GPIOInterruptRouter::GPIOIntNum int_num)
  #else
    GPIOintHandler_Master(I64 arg, GPIOInterruptRouter::GPIOIntNum int_num)
  #endif
  {
      GPIODriverComponentImpl* comp_ptr = reinterpret_cast<Drv::GPIODriverComponentImpl*>(arg);
      FW_ASSERT(comp_ptr != NULL);
      FW_ASSERT(comp_ptr->m_intRouter_p != NULL);
      comp_ptr->m_intRouter_p->RouteInterrupt(int_num);
  }


  // All interrupt handlers end up calling same central interrupt handler
  #ifdef TGT_OS_TYPE_VXWORKS
    void GPIOintHandler_1(I32 arg)  {GPIOintHandler_Master(arg, GPIOInterruptRouter::GPIO_INT_1);}
    void GPIOintHandler_2(I32 arg)  {GPIOintHandler_Master(arg, GPIOInterruptRouter::GPIO_INT_2);}
    void GPIOintHandler_3(I32 arg)  {GPIOintHandler_Master(arg, GPIOInterruptRouter::GPIO_INT_3);}
    void GPIOintHandler_4(I32 arg)  {GPIOintHandler_Master(arg, GPIOInterruptRouter::GPIO_INT_4);}
    void GPIOintHandler_5(I32 arg)  {GPIOintHandler_Master(arg, GPIOInterruptRouter::GPIO_INT_5);}
    void GPIOintHandler_6(I32 arg)  {GPIOintHandler_Master(arg, GPIOInterruptRouter::GPIO_INT_6);}
    void GPIOintHandler_7(I32 arg)  {GPIOintHandler_Master(arg, GPIOInterruptRouter::GPIO_INT_7);}
    void GPIOintHandler_8(I32 arg)  {GPIOintHandler_Master(arg, GPIOInterruptRouter::GPIO_INT_8);}
    void GPIOintHandler_9(I32 arg)  {GPIOintHandler_Master(arg, GPIOInterruptRouter::GPIO_INT_9);}
    void GPIOintHandler_10(I32 arg) {GPIOintHandler_Master(arg, GPIOInterruptRouter::GPIO_INT_10);}
    void GPIOintHandler_11(I32 arg) {GPIOintHandler_Master(arg, GPIOInterruptRouter::GPIO_INT_11);}
    void GPIOintHandler_12(I32 arg) {GPIOintHandler_Master(arg, GPIOInterruptRouter::GPIO_INT_12);}
    void GPIOintHandler_13(I32 arg) {GPIOintHandler_Master(arg, GPIOInterruptRouter::GPIO_INT_13);}
    void GPIOintHandler_14(I32 arg) {GPIOintHandler_Master(arg, GPIOInterruptRouter::GPIO_INT_14);}
    void GPIOintHandler_15(I32 arg) {GPIOintHandler_Master(arg, GPIOInterruptRouter::GPIO_INT_15);}
  #else
    void GPIOintHandler_1(I64 arg)  {GPIOintHandler_Master(arg, GPIOInterruptRouter::GPIO_INT_1);}
    void GPIOintHandler_2(I64 arg)  {GPIOintHandler_Master(arg, GPIOInterruptRouter::GPIO_INT_2);}
    void GPIOintHandler_3(I64 arg)  {GPIOintHandler_Master(arg, GPIOInterruptRouter::GPIO_INT_3);}
    void GPIOintHandler_4(I64 arg)  {GPIOintHandler_Master(arg, GPIOInterruptRouter::GPIO_INT_4);}
    void GPIOintHandler_5(I64 arg)  {GPIOintHandler_Master(arg, GPIOInterruptRouter::GPIO_INT_5);}
    void GPIOintHandler_6(I64 arg)  {GPIOintHandler_Master(arg, GPIOInterruptRouter::GPIO_INT_6);}
    void GPIOintHandler_7(I64 arg)  {GPIOintHandler_Master(arg, GPIOInterruptRouter::GPIO_INT_7);}
    void GPIOintHandler_8(I64 arg)  {GPIOintHandler_Master(arg, GPIOInterruptRouter::GPIO_INT_8);}
    void GPIOintHandler_9(I64 arg)  {GPIOintHandler_Master(arg, GPIOInterruptRouter::GPIO_INT_9);}
    void GPIOintHandler_10(I64 arg) {GPIOintHandler_Master(arg, GPIOInterruptRouter::GPIO_INT_10);}
    void GPIOintHandler_11(I64 arg) {GPIOintHandler_Master(arg, GPIOInterruptRouter::GPIO_INT_11);}
    void GPIOintHandler_12(I64 arg) {GPIOintHandler_Master(arg, GPIOInterruptRouter::GPIO_INT_12);}
    void GPIOintHandler_13(I64 arg) {GPIOintHandler_Master(arg, GPIOInterruptRouter::GPIO_INT_13);}
    void GPIOintHandler_14(I64 arg) {GPIOintHandler_Master(arg, GPIOInterruptRouter::GPIO_INT_14);}
    void GPIOintHandler_15(I64 arg) {GPIOintHandler_Master(arg, GPIOInterruptRouter::GPIO_INT_15);}
  #endif


  // Create array pointing to every interrupt handler
  const GPIODriverComponentImpl::GPIO_FP GPIODriverComponentImpl::m_gpioFuncs[GPIOInterruptRouter::NUM_GPIO_INTS] = {
    NULL,
    GPIOintHandler_1,
    GPIOintHandler_2,
    GPIOintHandler_3,
    GPIOintHandler_4,
    GPIOintHandler_5,
    GPIOintHandler_6,
    GPIOintHandler_7,
    GPIOintHandler_8,
    GPIOintHandler_9,
    GPIOintHandler_10,
    GPIOintHandler_11,
    GPIOintHandler_12,
    GPIOintHandler_13,
    GPIOintHandler_14,
    GPIOintHandler_15
  };




} // end namespace Drv
