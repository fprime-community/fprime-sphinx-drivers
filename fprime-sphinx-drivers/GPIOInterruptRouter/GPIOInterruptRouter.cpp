#include "GPIOInterruptRouter.hpp"
#include "fprime-sphinx-drivers/GPIOInterruptHandler/GPIOInterruptHandler.hpp"


namespace Drv {


  //-------------------------------------------------------------------
  // Router Interrupt Handlers
  // (User changes here)
  //-------------------------------------------------------------------

  //// User added initialization code ////
  void GPIOInterruptRouter::UserInit(){
    // Intentionally writing to register with mask
    // Enable firmware interrupt, then clear it
    Drv::writeReg(REG_IRQ_GPIO11_BASE + IRQ_GPIO11_MASK_OFFSET, UART6_INT_MASK );
    Drv::writeReg(REG_IRQ_GPIO11_BASE + IRQ_GPIO11_STATE_OFFSET, UART6_INT_MASK );
  }


  //// User implementations of router handlers ////
  void GPIOInterruptRouter::RouterIntHandler_1(){}
  void GPIOInterruptRouter::RouterIntHandler_2(){}
  void GPIOInterruptRouter::RouterIntHandler_3(){}
  void GPIOInterruptRouter::RouterIntHandler_4(){}
  void GPIOInterruptRouter::RouterIntHandler_5(){}
  void GPIOInterruptRouter::RouterIntHandler_6(){}
  void GPIOInterruptRouter::RouterIntHandler_7(){}
  void GPIOInterruptRouter::RouterIntHandler_8(){}
  void GPIOInterruptRouter::RouterIntHandler_9(){}
  void GPIOInterruptRouter::RouterIntHandler_10(){}

  void GPIOInterruptRouter::RouterIntHandler_11(){
    // Read register and decide what to do
    U32 irqState = Drv::readReg(REG_IRQ_GPIO11_BASE + IRQ_GPIO11_STATE_OFFSET);
    if (irqState & UART6_INT_MASK){
      HandleInterrupt(UART6_HANDLER);
    }
    // Clear all interrupts
    Drv::writeReg(REG_IRQ_GPIO11_BASE + IRQ_GPIO11_STATE_OFFSET, 0xFFFFFFFF);
  }

  void GPIOInterruptRouter::RouterIntHandler_12(){}
  void GPIOInterruptRouter::RouterIntHandler_13(){}
  void GPIOInterruptRouter::RouterIntHandler_14(){}
  void GPIOInterruptRouter::RouterIntHandler_15(){}


  //-------------------------------------------------------------------
  //-------------------------------------------------------------------
  //-------------------------------------------------------------------







  //----------------------------------------------
  // GPIOInterruptRouter Implementation
  //----------------------------------------------

  // Constructor initializes array of interrupt handlers to NULL
  GPIOInterruptRouter::GPIOInterruptRouter()
  {
    memset(this->int_handlers, 0, NUM_GPIO_INTS);
  }


  GPIOInterruptRouter::~GPIOInterruptRouter(){
  }


  void GPIOInterruptRouter::RegisterHandler(IntHandlerNum num, GPIOInterruptHandler *int_handler){
    FW_ASSERT((num >= NUM_HANDLERS_START) && (num < NUM_HANDLERS));
    FW_ASSERT(int_handler != NULL);
    int_handlers[num] = int_handler;
  }


  void GPIOInterruptRouter::init(){
    UserInit();
  }

  // Function that is called by GPIO Driver. Calls proper interrupt handler
  void GPIOInterruptRouter::RouteInterrupt(GPIOIntNum int_num){
    FW_ASSERT((int_num >= GPIO_INT_1) && (int_num < NUM_GPIO_INTS));
    FW_ASSERT(this->GPIOInterruptRouter::router_handlers[int_num] != NULL);
    (this->*GPIOInterruptRouter::router_handlers[int_num])();
  }


  void GPIOInterruptRouter::HandleInterrupt(IntHandlerNum num){
    FW_ASSERT((num >= NUM_HANDLERS_START) && (num < NUM_HANDLERS));
    FW_ASSERT(GPIOInterruptRouter::int_handlers[num] != NULL);
    int_handlers[num]->HandleGPIOInterrupt();
  }

  // Array of interrupt handlers
  const GPIOInterruptRouter::RouterHandler GPIOInterruptRouter::router_handlers[NUM_GPIO_INTS] = {
    NULL,
    &GPIOInterruptRouter::RouterIntHandler_1,
    &GPIOInterruptRouter::RouterIntHandler_2,
    &GPIOInterruptRouter::RouterIntHandler_3,
    &GPIOInterruptRouter::RouterIntHandler_4,
    &GPIOInterruptRouter::RouterIntHandler_5,
    &GPIOInterruptRouter::RouterIntHandler_6,
    &GPIOInterruptRouter::RouterIntHandler_7,
    &GPIOInterruptRouter::RouterIntHandler_8,
    &GPIOInterruptRouter::RouterIntHandler_9,
    &GPIOInterruptRouter::RouterIntHandler_10,
    &GPIOInterruptRouter::RouterIntHandler_11,
    &GPIOInterruptRouter::RouterIntHandler_12,
    &GPIOInterruptRouter::RouterIntHandler_13,
    &GPIOInterruptRouter::RouterIntHandler_14,
    &GPIOInterruptRouter::RouterIntHandler_15
  };

}
