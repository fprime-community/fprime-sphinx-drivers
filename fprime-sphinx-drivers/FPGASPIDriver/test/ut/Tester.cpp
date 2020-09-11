// ====================================================================== 
// \title  Tester.cpp
// \author ciankc
// \brief  cpp file for FPGASPIDriver test harness implementation class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
// ====================================================================== 

#include "Tester.hpp"

#define INSTANCE 0
#define MAX_HISTORY_SIZE 200

namespace Drv {

  // ----------------------------------------------------------------------
  // Construction and destruction 
  // ----------------------------------------------------------------------

  Tester ::
  Tester(const char* compName,
         U32 spiNumber,
         U32 spiWidth) : 
#if FW_OBJECT_NAMES == 1
      FPGASPIDriverGTestBase("Tester", MAX_HISTORY_SIZE),
      component(compName, spiNumber, spiWidth)
#else
      FPGASPIDriverGTestBase(MAX_HISTORY_SIZE),
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


  // ----------------------------------------------------------------------
  // Handlers for typed from ports
  // ----------------------------------------------------------------------

  void Tester ::
    from_Time_handler(
        const NATIVE_INT_TYPE portNum,
        Fw::Time &time
    )
  {
    this->pushFromPortEntry_Time(time);
  }

  // ----------------------------------------------------------------------
  // Helper methods 
  // ----------------------------------------------------------------------

  void Tester ::
    connectPorts(void) 
  {

    // read_write
    this->connect_to_read_write(
        0,
        this->component.get_read_write_InputPort(0)
    );

    // Time
    this->component.set_Time_OutputPort(
        0, 
        this->get_from_Time(0)
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
