#ifndef GPIOInterruptHandler_HPP
#define GPIOInterruptHandler_HPP


namespace Drv {

  class GPIOInterruptHandler {
  public:

    GPIOInterruptHandler(){};
    virtual ~GPIOInterruptHandler(){};
    virtual void HandleGPIOInterrupt() = 0; // Virtual function
  };

} //end namespace
#endif
