#ifndef GPIOInterruptRouter_HPP
#define GPIOInterruptRouter_HPP

#include "fprime-sphinx-drivers/GPIOInterruptHandler/GPIOInterruptHandler.hpp"
#include <stdio.h>
#include <cstring>
#include "Fw/Types/Assert.hpp"
#include <fprime-sphinx-drivers/Util/SphinxDrvUtil.hpp>
#include "Fw/Types/BasicTypes.hpp"


namespace Drv {

  //-------------------------------------------------------------------
  // User Defined; Add Handlers here
  //-------------------------------------------------------------------
  enum IntHandlerNum{
    NUM_HANDLERS_START = 0,
    UART7_HANDLER = NUM_HANDLERS_START,
    UART6_HANDLER,
    NUM_HANDLERS
  };

  //-------------------------------------------------------------------
  //-------------------------------------------------------------------
  //-------------------------------------------------------------------




  // GPIO11 Interrupt //
  #define REG_IRQ_GPIO11_BASE       0x20020000
  #define IRQ_GPIO11_STATE_OFFSET   0x00000000
  #define IRQ_GPIO11_MASK_OFFSET    0x00000004
  #define UART2_INT_MASK            0x01
  #define UART3_INT_MASK            0x02
  #define UART6_INT_MASK            0x04
  #define UART7_INT_MASK            0x08
  #define NAND_INT_MASK             0x10


  class GPIOInterruptRouter
  {

  public:

    enum GPIOIntNum{
      GPIO_INT_1 = 1,
      GPIO_INT_2,
      GPIO_INT_3,
      GPIO_INT_4,
      GPIO_INT_5,
      GPIO_INT_6,
      GPIO_INT_7,
      GPIO_INT_8,
      GPIO_INT_9,
      GPIO_INT_10,
      GPIO_INT_11,
      GPIO_INT_12,
      GPIO_INT_13,
      GPIO_INT_14,
      GPIO_INT_15,
      NUM_GPIO_INTS
    };

    GPIOInterruptRouter();
    ~GPIOInterruptRouter();
    void init();
    void RegisterHandler(IntHandlerNum num, GPIOInterruptHandler *int_handler);
    void RouteInterrupt(GPIOIntNum int_num);

  PRIVATE:

    void UserInit();
    void HandleInterrupt(IntHandlerNum num);
    GPIOInterruptHandler *int_handlers[NUM_HANDLERS];
    typedef void (GPIOInterruptRouter::*RouterHandler)();

    // made static so that array can be initialized
    static const RouterHandler router_handlers[NUM_GPIO_INTS];

    void RouterIntHandler_1();
    void RouterIntHandler_2();
    void RouterIntHandler_3();
    void RouterIntHandler_4();
    void RouterIntHandler_5();
    void RouterIntHandler_6();
    void RouterIntHandler_7();
    void RouterIntHandler_8();
    void RouterIntHandler_9();
    void RouterIntHandler_10();
    void RouterIntHandler_11();
    void RouterIntHandler_12();
    void RouterIntHandler_13();
    void RouterIntHandler_14();
    void RouterIntHandler_15();
  };


}
#endif
