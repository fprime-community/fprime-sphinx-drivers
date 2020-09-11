// ====================================================================== 
// \title  WakeupManagerComponentImpl.cpp
// \author nserafin
// \brief  cpp file for WakeupManager component implementation class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
// ====================================================================== 


#include <fprime-sphinx-drivers/WakeupManager/WakeupManagerComponentImpl.hpp>
#include <fprime-sphinx-drivers/Util/SphinxDrvIntUtil.hpp>
#include <Fw/Types/BasicTypes.hpp>
#include <Fw/Types/Assert.hpp>
#include <Os/Event.hpp>

#ifdef TGT_OS_TYPE_VXWORKS

extern "C" {
#include <intLib.h>
#include <iv.h>
}

#endif

namespace Drv {

  // ----------------------------------------------------------------------
  // Helper functions
  // ----------------------------------------------------------------------

  void WakeupManagerComponentImpl ::
    safeTimer(void)
  {
      GPTimer::CtlReg ctlReg = 0U;
      GPTimer::ctlRegBuild(ctlReg,
                           GPTimer::DH_CLEAR, GPTimer::CH_CLEAR,
                           GPTimer::IP_CLEAR, GPTimer::IE_CLEAR,
                           GPTimer::LD_CLEAR, GPTimer::RS_CLEAR,
                           GPTimer::EN_CLEAR);
      writeReg(GPTimer::timerAddr[this->timer].ctlRegAddr, ctlReg);
  }

  void WakeupManagerComponentImpl ::
    setTimer(U32 time)
  {
      writeReg(GPTimer::timerAddr[this->timer].rldRegAddr, time);

      GPTimer::CtlReg ctlReg = 0U;
      GPTimer::ctlRegBuild(ctlReg,
                           GPTimer::IE_SET, GPTimer::LD_SET, GPTimer::EN_SET);
      writeReg(GPTimer::timerAddr[this->timer].ctlRegAddr, ctlReg);
  }

  // ----------------------------------------------------------------------
  // Construction, initialization, and destruction 
  // ----------------------------------------------------------------------

  WakeupManagerComponentImpl ::
#if FW_OBJECT_NAMES == 1
    WakeupManagerComponentImpl(
        const char *const compName,
        I8 timer
    ) :
      WakeupManagerComponentBase(compName)
#else // Broken! See FPRIME issue #114.
    WakeupManagerImpl(void)
#endif
  {
      // Record the assigned timer
      this->timer = timer;

      // Initialize member variable for IRQ
      this->irq = IRQ1;

      // Find the assigned IRQ
      switch (timer) {
          case GPTimer::TIMER1:
              this->irq = IRQ8;
              break;
          case GPTimer::TIMER2:
              this->irq = IRQ9;
              break;
          case GPTimer::TIMER3:
              this->irq = IRQ10;
              break;
          case GPTimer::TIMER4:
              this->irq = IRQ11;
              break;
          default:
              FW_ASSERT(0);
      }
  }

  void WakeupManagerComponentImpl ::
    init(
        const NATIVE_INT_TYPE queueDepth,
        const NATIVE_INT_TYPE instance
    ) 
  {
      WakeupManagerComponentBase::init(queueDepth, instance);

      // Make sure the timer is off
      this->safeTimer();

      // Disable timer interrupts
      clearPendingInt(this->irq);
      maskInt(PROC0, this->irq);

      // Register the ISR
#ifdef TGT_OS_TYPE_VXWORKS
      I32 status = intConnect(INUM_TO_IVEC(this->irq),
                              (VOIDFUNCPTR) WakeupManagerComponentImpl::interruptHandler,
                              (I32) this);
      FW_ASSERT(status == 0);
#endif

      // Enable timer interrupts
      unmaskInt(PROC0, this->irq);
  }

  WakeupManagerComponentImpl ::
    ~WakeupManagerComponentImpl(void)
  {
      // Make sure the timer is off
      this->safeTimer();

      // Disable timer interrupts
      maskInt(PROC0, this->irq);

      // Deregister the ISR
#ifdef TGT_OS_TYPE_VXWORKS
      I32 status = intDisconnect(INUM_TO_IVEC(this->irq),
                                 (VOIDFUNCPTR) WakeupManagerComponentImpl::interruptHandler,
                                 (I32) this);
      FW_ASSERT(status == 0);
#endif
  }

  // ----------------------------------------------------------------------
  // Handler implementations for user-defined typed input ports
  // ----------------------------------------------------------------------

  void WakeupManagerComponentImpl ::
    wakeupManager_Sleep_handler(
        const NATIVE_INT_TYPE portNum,
        U32 time
    )
  {
      WakeupQueue::Status wqStatus;

      this->queueLock.lock();

      // Find the new wakeup time
      Fw::Time fwNow;
      this->time_out(0, fwNow);
      Fw::Time fwTime(0, time);
      fwTime = Fw::Time::add(fwTime, fwNow);

      // Reset the timer, if necessary
      Fw::Time fwFrontTime;
      wqStatus = this->queue.peek(fwFrontTime);
      if ((wqStatus != WakeupQueue::WQ_OK) ||
          ((wqStatus == WakeupQueue::WQ_OK) && (fwTime < fwFrontTime))) {
          this->setTimer(time);
      }

      // Enqueue the new wakeup time
      wqStatus = this->queue.enq(fwTime);
      FW_ASSERT(wqStatus == WakeupQueue::WQ_OK);

      this->queueLock.unLock();

      I32 eStatus = Os::Event::receive(this->event,
                                       Os::Event::EV_EVENTS_WAIT_ANY,
                                       Os::Event::EV_WAIT_FOREVER,
                                       NULL);
      FW_ASSERT(eStatus == 0);
  }

  // ----------------------------------------------------------------------
  // Handler implementations for internal interfaces
  // ----------------------------------------------------------------------

  void WakeupManagerComponentImpl ::
    wakeupHandler_internalInterfaceHandler(void)
  {
      I32 status;

      this->queueLock.lock();

      Fw::Time fwNow;
      this->time_out(0, fwNow);

      // Wake up all due tasks
      Os::TaskId tid;
      for (int i = 0; i < WakeupQueue::maxQSize; ++i) {
          if (this->queue.deq(fwNow, tid) == WakeupQueue::WQ_OK) {
              status = Os::Event::send(tid, this->event);
              FW_ASSERT(status == 0);
          }
          else {
              break;
          }
      }

      // Reset the timer, if necessary
      Fw::Time fwNextTime;
      if (this->queue.peek(fwNextTime) == WakeupQueue::WQ_OK) {
          fwNextTime = Fw::Time::sub(fwNextTime, fwNow);

          U32 nextTime = fwNextTime.getSeconds()*usPerS +
                         fwNextTime.getUSeconds();

          this->setTimer(nextTime);
      }

      this->queueLock.unLock();
  }

  // ----------------------------------------------------------------------
  // Interrupt service routines
  // ----------------------------------------------------------------------

  void WakeupManagerComponentImpl ::
    interruptHandler(int objAddr)
  {
      WakeupManagerComponentImpl* obj =
        reinterpret_cast<WakeupManagerComponentImpl*>(objAddr);

      obj->wakeupHandler_internalInterfaceInvoke();
  }

} // end namespace Drv
