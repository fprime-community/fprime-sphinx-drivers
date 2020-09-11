// ====================================================================== 
// \title  FPGADriver.hpp
// \author ciankc
// \brief  cpp file for FPGADriver test harness implementation class
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
      FPGADriverGTestBase("Tester", MAX_HISTORY_SIZE),
      component("FPGADriver")
#else
      FPGADriverGTestBase(MAX_HISTORY_SIZE),
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
  // Handlers for typed from ports
  // ----------------------------------------------------------------------

  void Tester ::
    from_timeRTIOut_handler(
        const NATIVE_INT_TYPE portNum,
        NATIVE_UINT_TYPE context
    )
  {
    this->pushFromPortEntry_timeRTIOut(context);
  }

  void Tester ::
    from_cycleOut_handler(
        const NATIVE_INT_TYPE portNum,
        Svc::TimerVal &cycleStart
    )
  {
    this->pushFromPortEntry_cycleOut(cycleStart);
  }

  // ----------------------------------------------------------------------
  // Helper methods 
  // ----------------------------------------------------------------------

  void Tester ::
    connectPorts(void) 
  {

    // read_reg
    this->connect_to_read_reg(
        0,
        this->component.get_read_reg_InputPort(0)
    );

    // write_reg
    this->connect_to_write_reg(
        0,
        this->component.get_write_reg_InputPort(0)
    );

    // timeRTIOut
    this->component.set_timeRTIOut_OutputPort(
        0, 
        this->get_from_timeRTIOut(0)
    );

    // cycleOut
    this->component.set_cycleOut_OutputPort(
        0, 
        this->get_from_cycleOut(0)
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
