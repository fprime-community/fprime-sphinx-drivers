// ====================================================================== 
// \title  GPTimerDriverImpl.cpp
// \author nserafin
// \brief  cpp file for GPTimerDriver component implementation class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
// ====================================================================== 


#include <fprime-sphinx-drivers/GPTimerDriver/GPTimerDriverComponentImpl.hpp>

#include <Fw/Types/BasicTypes.hpp>
#include <Fw/Types/Assert.hpp>
#include <Os/Task.hpp>

namespace Drv {

  using namespace GPTimer;

  // ----------------------------------------------------------------------
  // Definitions of static members
  // ----------------------------------------------------------------------

  bool GPTimerDriverComponentImpl::reservedTimers[NTIMERS];
  bool GPTimerDriverComponentImpl::freeTimers[NTIMERS];
  Os::TaskId GPTimerDriverComponentImpl::owners[NTIMERS];

  // ----------------------------------------------------------------------
  // Helper functions
  // ----------------------------------------------------------------------

  void GPTimerDriverComponentImpl::
      initTimerOwners(void)
  {
      for (NATIVE_INT_TYPE i = 0; i < NTIMERS; ++i) {
          this->reservedTimers[i] = false;
          this->freeTimers[i] = true;
      }
  }

  void GPTimerDriverComponentImpl::
      cfgTimer(I8 timer,
               const bool reserved, const bool usrConfig,
               const U32 cntReg, const U32 rldReg, const U32 ctlReg)
  {
      if (reserved) {
          this->reservedTimers[timer] = true;
          this->freeTimers[timer] = false;
      }
      else if (usrConfig) {
          writeReg(timerAddr[timer].cntRegAddr, cntReg);
          writeReg(timerAddr[timer].rldRegAddr, rldReg);
          writeReg(timerAddr[timer].ctlRegAddr, ctlReg);
      }
      else {
          writeReg(timerAddr[timer].cntRegAddr, DFL_CNT_REG);
          writeReg(timerAddr[timer].rldRegAddr, DFL_RLD_REG);
          writeReg(timerAddr[timer].ctlRegAddr, DFL_CTL_REG);
      }
  }

  // ----------------------------------------------------------------------
  // Construction, initialization, and destruction 
  // ----------------------------------------------------------------------

  GPTimerDriverComponentImpl ::
#if FW_OBJECT_NAMES == 1
    GPTimerDriverComponentImpl(
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
        const U32 timer4CtlReg
    ) :
      GPTimerDriverComponentBase(compName)
#else
    GPTimerDriverImpl(void)
#endif
  {
      initTimerOwners();

      writeReg(prescalerAddr.cntRegAddr, prescalerValue);
      writeReg(prescalerAddr.rldRegAddr, prescalerReload);

      cfgTimer(TIMER1,
               timer1Reserved, timer1UsrConfig,
               timer1CntReg, timer1RldReg, timer1CtlReg);
      cfgTimer(TIMER2,
               timer2Reserved, timer2UsrConfig,
               timer2CntReg, timer2RldReg, timer2CtlReg);
      cfgTimer(TIMER3,
               timer3Reserved, timer3UsrConfig,
               timer3CntReg, timer3RldReg, timer3CtlReg);
      cfgTimer(TIMER4,
               timer4Reserved, timer4UsrConfig,
               timer4CntReg, timer4RldReg, timer4CtlReg);
  }

  void GPTimerDriverComponentImpl ::
    init(
        const NATIVE_INT_TYPE instance
    ) 
  {
    GPTimerDriverComponentBase::init(instance);
  }

  GPTimerDriverComponentImpl ::
    ~GPTimerDriverComponentImpl(void)
  {
      // De-configure non-reserved timers
      for (NATIVE_INT_TYPE i = 0; i < NTIMERS; ++i) {
          if (reservedTimers[i] == false) {
              FW_ASSERT(freeTimers[i] == true);
              cfgTimer(i, false, true, 0U, 0U, 0U);
          }
      }
  }

  // ----------------------------------------------------------------------
  // Handler implementations for user-defined typed input ports
  // ----------------------------------------------------------------------

  void GPTimerDriverComponentImpl ::
    gPTimerDriver_Unclaim_handler(
        const NATIVE_INT_TYPE portNum,
        I8 timer
    )
  {
      FW_ASSERT(timer == TIMER1 ||
                timer == TIMER2 ||
                timer == TIMER3 ||
                timer == TIMER4);
      FW_ASSERT(Os::Task::getOsIdentifier() == this->owners[timer]);

      this->freeTimers[timer] = true;
  }

  I8 GPTimerDriverComponentImpl ::
    gPTimerDriver_Claim_handler(
        const NATIVE_INT_TYPE portNum,
        I8 timer
    )
  {
      FW_ASSERT(timer == TIMER1 ||
                timer == TIMER2 ||
                timer == TIMER3 ||
                timer == TIMER4 ||
                timer == TIMER_ANY);

      if (timer == TIMER_ANY) {
          for (NATIVE_INT_TYPE i = 0; i < NTIMERS; ++i) {
              if (this->freeTimers[i]) {
                  this->freeTimers[i] = false;
                  this->owners[i] = Os::Task::getOsIdentifier();
                  return i;
              }
          }
      }
      else {
          if (this->freeTimers[timer]) {
              this->freeTimers[timer] = false;
              this->owners[timer] = Os::Task::getOsIdentifier();
              return timer;
          }
      }

      return NOT_AVAILABLE;
  }

  U32 GPTimerDriverComponentImpl ::
    gPTimerDriver_ReadControl_handler(
        const NATIVE_INT_TYPE portNum,
        I8 timer
    )
  {
      FW_ASSERT(timer == TIMER1 ||
                timer == TIMER2 ||
                timer == TIMER3 ||
                timer == TIMER4);
      FW_ASSERT(Os::Task::getOsIdentifier() == this->owners[timer]);
      
      return readReg(timerAddr[timer].ctlRegAddr);  
  }

  void GPTimerDriverComponentImpl ::
    gPTimerDriver_WriteCounter_handler(
        const NATIVE_INT_TYPE portNum,
        I8 timer,
        U32 counter
    )
  {
      FW_ASSERT(timer == TIMER1 ||
                timer == TIMER2 ||
                timer == TIMER3 ||
                timer == TIMER4);
      FW_ASSERT(Os::Task::getOsIdentifier() == this->owners[timer]);

      writeReg(timerAddr[timer].cntRegAddr, counter);
  }

  void GPTimerDriverComponentImpl ::
    gPTimerDriver_WriteControl_handler(
        const NATIVE_INT_TYPE portNum,
        I8 timer,
        U32 control
    )
  {
      FW_ASSERT(timer == TIMER1 ||
                timer == TIMER2 ||
                timer == TIMER3 ||
                timer == TIMER4);
      FW_ASSERT(Os::Task::getOsIdentifier() == this->owners[timer]);

      control &= CONTROL_BITS_MASK;

      writeReg(timerAddr[timer].ctlRegAddr, control);
  }

  U32 GPTimerDriverComponentImpl ::
    gPTimerDriver_ReadCounter_handler(
        const NATIVE_INT_TYPE portNum,
        I8 timer
    )
  {
      FW_ASSERT(timer == TIMER1 ||
                timer == TIMER2 ||
                timer == TIMER3 ||
                timer == TIMER4);
      FW_ASSERT(Os::Task::getOsIdentifier() == this->owners[timer]);

      return readReg(timerAddr[timer].cntRegAddr);
  }

  U32 GPTimerDriverComponentImpl ::
    gPTimerDriver_ReadReload_handler(
        const NATIVE_INT_TYPE portNum,
        I8 timer
    )
  {
      FW_ASSERT(timer == TIMER1 ||
                timer == TIMER2 ||
                timer == TIMER3 ||
                timer == TIMER4);
      FW_ASSERT(Os::Task::getOsIdentifier() == this->owners[timer]);

      return readReg(timerAddr[timer].rldRegAddr);
  }

  void GPTimerDriverComponentImpl ::
    gPTimerDriver_WriteReload_handler(
        const NATIVE_INT_TYPE portNum,
        I8 timer,
        U32 reload
    )
  {
      FW_ASSERT(timer == TIMER1 ||
                timer == TIMER2 ||
                timer == TIMER3 ||
                timer == TIMER4);
      FW_ASSERT(Os::Task::getOsIdentifier() == this->owners[timer]);

      writeReg(timerAddr[timer].rldRegAddr, reload);
  }

} // end namespace Drv
