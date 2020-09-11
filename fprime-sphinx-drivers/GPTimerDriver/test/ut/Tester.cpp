// ====================================================================== 
// \title  GPTimerDriver.hpp
// \author ciankc
// \brief  cpp file for GPTimerDriver test harness implementation class
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
    Tester(
	 const char *const compName,

	 const U32 prescalerReload,
	 const U32 prescalerValue,

	 // Timer 1
	 const bool timer1Reserved,
	 const bool timer1UsrConfig,
	 const U32 timer1CntReg,
	 const U32 timer1RldReg,
	 const U32 timer1CtlReg,

	 // Timer 2
	 const bool timer2Reserved,
	 const bool timer2UsrConfig,
	 const U32 timer2CntReg,
	 const U32 timer2RldReg,
	 const U32 timer2CtlReg,

	 // Timer 3
	 const bool timer3Reserved,
	 const bool timer3UsrConfig,
	 const U32 timer3CntReg,
	 const U32 timer3RldReg,
	 const U32 timer3CtlReg,

	 // Timer 4
	 const bool timer4Reserved,
	 const bool timer4UsrConfig,
	 const U32 timer4CntReg,
	 const U32 timer4RldReg,
	 const U32 timer4CtlReg) : 
#if FW_OBJECT_NAMES == 1
      GPTimerDriverGTestBase("Tester", MAX_HISTORY_SIZE),
    component(compName, prescalerReload, prescalerValue, 
	    timer1Reserved, timer1UsrConfig, timer1CntReg, timer1RldReg, timer1CtlReg,
	    timer2Reserved, timer2UsrConfig, timer2CntReg, timer2RldReg, timer2CtlReg,
	    timer3Reserved, timer3UsrConfig, timer3CntReg, timer3RldReg, timer3CtlReg,
	    timer4Reserved, timer4UsrConfig, timer4CntReg, timer4RldReg, timer4CtlReg)
#else
      GPTimerDriverGTestBase(MAX_HISTORY_SIZE),
      component()
#endif
  {
    this->initComponents();
    this->connectPorts();
  }

  Tester ::
    ~Tester(void) 
  {
    //set all freeTimers to true
    for(U32 i = 0; i < 4; i++)
      {
        this->component.freeTimers[i] = true;
      }
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

    // gPTimerDriver_Unclaim
    this->connect_to_gPTimerDriver_Unclaim(
        0,
        this->component.get_gPTimerDriver_Unclaim_InputPort(0)
    );

    // gPTimerDriver_Claim
    this->connect_to_gPTimerDriver_Claim(
        0,
        this->component.get_gPTimerDriver_Claim_InputPort(0)
    );

    // gPTimerDriver_ReadControl
    this->connect_to_gPTimerDriver_ReadControl(
        0,
        this->component.get_gPTimerDriver_ReadControl_InputPort(0)
    );

    // gPTimerDriver_WriteCounter
    this->connect_to_gPTimerDriver_WriteCounter(
        0,
        this->component.get_gPTimerDriver_WriteCounter_InputPort(0)
    );

    // gPTimerDriver_WriteControl
    this->connect_to_gPTimerDriver_WriteControl(
        0,
        this->component.get_gPTimerDriver_WriteControl_InputPort(0)
    );

    // gPTimerDriver_ReadCounter
    this->connect_to_gPTimerDriver_ReadCounter(
        0,
        this->component.get_gPTimerDriver_ReadCounter_InputPort(0)
    );

    // gPTimerDriver_ReadReload
    this->connect_to_gPTimerDriver_ReadReload(
        0,
        this->component.get_gPTimerDriver_ReadReload_InputPort(0)
    );

    // gPTimerDriver_WriteReload
    this->connect_to_gPTimerDriver_WriteReload(
        0,
        this->component.get_gPTimerDriver_WriteReload_InputPort(0)
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
