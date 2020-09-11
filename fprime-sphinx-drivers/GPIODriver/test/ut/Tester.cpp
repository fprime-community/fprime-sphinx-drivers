// ====================================================================== 
// \title  GPIODriver.hpp
// \author ciankc
// \brief  cpp file for GPIODriver test harness implementation class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
// ====================================================================== 

#include "Tester.hpp"

#define INSTANCE 0
#define MAX_HISTORY_SIZE 10

namespace Drv {

  // ----------------------------------------------------------------------
  // Construction and destruction 
  // ----------------------------------------------------------------------

  Tester ::
    Tester(void) : 
#if FW_OBJECT_NAMES == 1
      GPIODriverGTestBase("Tester", MAX_HISTORY_SIZE),
      component("GPIODriver")
#else
      GPIODriverGTestBase(MAX_HISTORY_SIZE),
      component()
#endif
  {
    this->initComponents();
    this->connectPorts();
  }

  Tester ::
    ~Tester(void) 
  {
    
  }

  // ----------------------------------------------------------------------
  // Tests 
  // ----------------------------------------------------------------------

  void Tester ::
    toDo(void) 
  {
    // TODO
  }

  // ----------------------------------------------------------------------
  // Helper methods 
  // ----------------------------------------------------------------------

  void Tester ::
    connectPorts(void) 
  {

    // gpio_readPin
    for (NATIVE_INT_TYPE i = 0; i < 10; ++i) {
      this->connect_to_gpio_readPin(
          i,
          this->component.get_gpio_readPin_InputPort(i)
      );
    }

    // gpio_setPin
    for (NATIVE_INT_TYPE i = 0; i < 10; ++i) {
      this->connect_to_gpio_setPin(
          i,
          this->component.get_gpio_setPin_InputPort(i)
      );
    }

    // gpio_clearPin
    for (NATIVE_INT_TYPE i = 0; i < 10; ++i) {
      this->connect_to_gpio_clearPin(
          i,
          this->component.get_gpio_clearPin_InputPort(i)
      );
    }

  }

  void Tester ::
    initComponents(void) 
  {
    this->init();
    this->component.init(
        INSTANCE
    );
  }

} // end namespace Drv
