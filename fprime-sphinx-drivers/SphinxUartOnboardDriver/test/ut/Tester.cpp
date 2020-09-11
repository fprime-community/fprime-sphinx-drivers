// ====================================================================== 
// \title  Tester.cpp
// \author ciankc
// \brief  cpp file for SphinxUartOnboardDriver test harness implementation class
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
      SphinxUartOnboardDriverGTestBase("Tester", MAX_HISTORY_SIZE),
      component("SphinxUartOnboardDriver")
#else
      SphinxUartOnboardDriverGTestBase(MAX_HISTORY_SIZE),
      component()
#endif
  {
    this->initComponents();
    this->connectPorts();
    this->statusQuery();
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

    // bytesUsed
    this->connect_to_bytesUsed(
        0,
        this->component.get_bytesUsed_InputPort(0)
    );

    // read
    this->connect_to_read(
        0,
        this->component.get_read_InputPort(0)
    );

    // write
    this->connect_to_write(
        0,
        this->component.get_write_InputPort(0)
    );

    // timeCaller
    this->component.set_timeCaller_OutputPort(
        0, 
        this->get_from_timeCaller(0)
    );

    // logOut
    this->component.set_logOut_OutputPort(
        0, 
        this->get_from_logOut(0)
    );

    // LogText
    this->component.set_LogText_OutputPort(
        0, 
        this->get_from_LogText(0)
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

  void Tester ::
  statusQuery(void)
  {
    ASSERT_EQ(this->component.isConnected_timeCaller_OutputPort(0), true);
    ASSERT_EQ(this->component.isConnected_logOut_OutputPort(0), true);
    ASSERT_EQ(this->component.isConnected_LogText_OutputPort(0), true);    
  }

} // end namespace Drv
