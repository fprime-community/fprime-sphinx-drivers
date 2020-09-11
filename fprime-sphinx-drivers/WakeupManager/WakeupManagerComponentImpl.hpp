// ====================================================================== 
// \title  WakeupManagerComponentImpl.hpp
// \author nserafin
// \brief  hpp file for WakeupManager component implementation class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
// ====================================================================== 

#ifndef WakeupManager_HPP
#define WakeupManager_HPP

#include "fprime-sphinx-drivers/WakeupManager/WakeupManagerComponentAc.hpp"
#include "fprime-sphinx-drivers/WakeupManager/WakeupQueue.hpp"
#include "fprime-sphinx-drivers/Util/SphinxDrvIntUtil.hpp"

#include <Fw/Types/BasicTypes.hpp>
#include <Os/TaskId.hpp>
#include <Os/Mutex.hpp>

namespace Drv {

  class WakeupManagerComponentImpl :
    public WakeupManagerComponentBase
  {

    public:
      static const U32 usPerS = 1000000;
      // ----------------------------------------------------------------------
      // Construction, initialization, and destruction
      // ----------------------------------------------------------------------

      //! Construct object WakeupManager
      //!
      //! The wakeup queue will be initialized, and the propoer IRQ determined.
      //!
      WakeupManagerComponentImpl(
#if FW_OBJECT_NAMES == 1
          const char *const compName, /*!< The component name*/
#endif
          I8 timer /*!< The timer to use*/
      );

      //! Initialize object WakeupManager
      //!
      //! The timer will be put in to a safe state (i.e. not going to go off
      //! unexpectedly), the interrupt handler registered, and timer
      //! interrupts enabled.
      //!
      void init(
          const NATIVE_INT_TYPE queueDepth, /*!< The queue depth*/
          const NATIVE_INT_TYPE instance = 0 /*!< The instance number*/
      );

      //! Destroy object WakeupManager

      //! The timer will be put into a safe state (i.e. not going to go off
      //! unexpectedly), the interrupt handler deregistered, and timer
      //! interrupts disabled.
      //!
      ~WakeupManagerComponentImpl(void);

      // ----------------------------------------------------------------------
      // Interrupt service routines
      // ----------------------------------------------------------------------

      //! Handle timer interrupts

      //! Call the internal interface to queue work for the thread to go
      //! through the wakeup queue.
      //!
      //! This must be static for it to be connected to a VxWorks interrupt.
      //! See section 7.21.5 of ``The VxWorks Kernel Programmer's Guide''
      //! for VxWorks 6.7.
      //!
      //! The static handler must know where the WakeupManager object is
      //! in order to poke its internal interface: this is done by casting
      //! the address of the object to an int and back. Depending on the size
      //! of pointers and integers on the target system, that may chop the
      //! pointer and break.
      //!
      static void interruptHandler(int objAddr);

    PRIVATE:

      // ----------------------------------------------------------------------
      // Handler implementations for user-defined typed input ports
      // ----------------------------------------------------------------------

      //! Handler implementation for wakeupManager_Sleep

      //! The new task will always be sorted in to the queue, and if the
      //! new wakeup time is before the timer goes off (which is true both
      //! if the timer is running but will go off after the new wakeup time
      //! has arrived or if the timer is not running), then the timer will
      //! be changed to the sooner time.
      //!
      void wakeupManager_Sleep_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          U32 time /*!< Time to sleep for*/
      );

      // ----------------------------------------------------------------------
      // Handler implementations for internal interfaces
      // ----------------------------------------------------------------------

      //! Handle pending wakeups indicated by the interrupt handler.

      //! Every waiting thread is on the queue, so this simply walks down
      //! the queue waking up every thread whose time has passed. Once it
      //! finds a wakeup time that is in the future, it restarts the timer
      //! for then; if there are no times in the future it stops after
      //! sending wakeups to everyone.
      //!
      void wakeupHandler_internalInterfaceHandler(void);

      // ----------------------------------------------------------------------
      // Private data
      // ----------------------------------------------------------------------

      //! The wakeup queue
      //!
      WakeupQueue queue;

      //! The wakeup queue lock

      //! This should be held during any sequence of operations on the queue.
      //!
      Os::Mutex queueLock;

      //! The assigned timer
      //!
      I8 timer;

      //! The assigned interrupt
      //!
      Irq irq;

      //! The event that is sent and received
      //!
      static const U32 event = 1U;

      // ----------------------------------------------------------------------
      // Helper functions
      // ----------------------------------------------------------------------

      //! Put the assigned timer in to a safe state (i.e not going to go off)
      //!
      void safeTimer(void);

      //! Set the assigned timer to go off at the given time
      //!
      void setTimer(U32 time);

    };

} // end namespace Drv

#endif
