// ====================================================================== 
// \title  FpgaGpioDriver.hpp
// \author vwong
// \brief  cpp file for FpgaGpioDriver test harness implementation class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
// ====================================================================== 

#include "Tester.hpp"

#define INSTANCE 0
#define MAX_HISTORY_SIZE 10

NATIVE_UINT_TYPE componentTotalAvailPins = 8;
NATIVE_UINT_TYPE componentInitPins[] = { 0 };

namespace Drv {

  // ----------------------------------------------------------------------
  // Construction and destruction 
  // ----------------------------------------------------------------------

  Tester ::
    Tester(void) : 
#if FW_OBJECT_NAMES == 1
      FpgaGpioDriverGTestBase("Tester", MAX_HISTORY_SIZE),
      component("FpgaGpioDriver", componentTotalAvailPins, componentInitPins, FW_NUM_ARRAY_ELEMENTS(componentInitPins))
#else
      FpgaGpioDriverGTestBase(MAX_HISTORY_SIZE),
      component(componentTotalAvailPins, componentInitPins, FW_NUM_ARRAY_ELEMENTS(componentInitPins))
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
    testBasicReadWrite(void) 
  {
    I32 status = 0;
    for (U32 i = 0; i < componentTotalAvailPins; i++) {
      status = this->invoke_to_enablePin(0, i);
      ASSERT_EQ(status, 0);
      status = this->invoke_to_setPin(0, i);
      // above setPin call performs a read-back verification check
      ASSERT_LE(status, 0); // NB: can't assert exct value in linux UT for read-back

      U32 val = this->invoke_to_readPin(0, i);
      ASSERT_LE(val, 1); // NB: can't assert exact value in a linux UT

      status = this->invoke_to_clearPin(0, i);
      // above clearPin call performs a read-back verification check
      ASSERT_LE(status, 0); // NB: can't assert exact value in a linux UT
      status = this->invoke_to_disablePin(0, i);
      ASSERT_EQ(status, 0);
    }
  }

  // ----------------------------------------------------------------------
  // Helper methods 
  // ----------------------------------------------------------------------

  void Tester ::
    connectPorts(void) 
  {

    // setPin
    this->connect_to_setPin(
        0,
        this->component.get_setPin_InputPort(0)
    );

    // clearPin
    this->connect_to_clearPin(
        0,
        this->component.get_clearPin_InputPort(0)
    );

    // readPin
    this->connect_to_readPin(
        0,
        this->component.get_readPin_InputPort(0)
    );

    // enablePin
    this->connect_to_enablePin(
        0,
        this->component.get_enablePin_InputPort(0)
    );

    // disablePin
    this->connect_to_disablePin(
        0,
        this->component.get_disablePin_InputPort(0)
    );

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
