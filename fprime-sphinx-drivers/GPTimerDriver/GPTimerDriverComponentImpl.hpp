// ====================================================================== 
// \title  GPTimerDriverImpl.hpp
// \author nserafin
// \brief  hpp file for GPTimerDriver component implementation class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
// ====================================================================== 

#ifndef GPTimerDriver_HPP
#define GPTimerDriver_HPP

#include <fprime-sphinx-drivers/GPTimerDriver/GPTimerDriverComponentAc.hpp>
#include <fprime-sphinx-drivers/GPTimerDriver/GPTimerDriverPriv.hpp>

#include <fprime-sphinx-drivers/Util/SphinxDrvUtil.hpp>

#include <Os/TaskId.hpp>

namespace Drv {

  class GPTimerDriverComponentImpl :
    public GPTimerDriverComponentBase
  {

    public:

      // ----------------------------------------------------------------------
      // Construction, initialization, and destruction
      // ----------------------------------------------------------------------

      //! Constructor for configuring everything for the timer.
      //!
      //! The prescaler must be fully configured, and cannot be reconfigured
      //! after the constructor has run. Configuration parameters must also
      //! be provided for each timer. If the timer is marked as reserved, then
      //! the values of the remaining parameters are unimportant, and if the
      //! timer is not reserved but is marked for default configuration, the
      //! register values are unimportant.
      //!
      GPTimerDriverComponentImpl(
#if FW_OBJECT_NAMES ==1
          const char *const compName, /*!< The component name*/
#endif
          const U32 prescalerReload, /*!< Value to load into prescaler on
                                          underflow*/
          const U32 prescalerValue, /*!< Initial value of prescaler*/

          // Timer 1
          const bool timer1Reserved, /*!< Indicate timer 1 is not owned
                                          by GPTimerDriver*/
          const bool timer1UsrConfig, /*!< Indicate timer 1 is to be
                                           user-configured*/
          const U32 timer1CntReg, /*!< Value for timer 1's count register*/
          const U32 timer1RldReg, /*!< Value for timer 1's reload register*/
          const U32 timer1CtlReg, /*!< Value for timer 1's control register*/

          // Timer 2
          const bool timer2Reserved, /*!< Indicate timer 2 is not owned
                                          by GPTimerDriver*/
          const bool timer2UsrConfig, /*!< Indicate timer 2 is to be
                                           user-configured*/
          const U32 timer2CntReg, /*!< Value for timer 2's count register*/
          const U32 timer2RldReg, /*!< Value for timer 2's reload register*/
          const U32 timer2CtlReg, /*!< Value for timer 2's control register*/

          // Timer 3
          const bool timer3Reserved, /*!< Indicate timer 3 is not owned
                                          by GPTimerDriver*/
          const bool timer3UsrConfig, /*!< Indicate timer 3 is to be
                                           user-configured*/
          const U32 timer3CntReg, /*!< Value for timer 3's count register*/
          const U32 timer3RldReg, /*!< Value for timer 3's reload register*/
          const U32 timer3CtlReg, /*!< Value for timer 3's control register*/

          // Timer 4
          const bool timer4Reserved, /*!< Indicate timer 4 is not owned
                                          by GPTimerDriver*/
          const bool timer4UsrConfig, /*!< Indicate timer 4 is to be
                                           user-configured*/
          const U32 timer4CntReg, /*!< Value for timer 4's count register*/
          const U32 timer4RldReg, /*!< Value for timer 4's reload register*/
          const U32 timer4CtlReg  /*!< Value for timer 4's control register*/
      );

      //! Initialize object GPTimerDriver
      //!
      void init(
          const NATIVE_INT_TYPE instance = 0 /*!< The instance number*/
      );

      //! Destroy object GPTimerDriver
      //!
      //! De-configures non-reserved timers into the default timer state.
      //!
      //! Asserts that all non-reserved timers are free.
      //!
      ~GPTimerDriverComponentImpl(void);

    PRIVATE:

      // ----------------------------------------------------------------------
      // Handler implementations for user-defined typed input ports
      // ----------------------------------------------------------------------

      //! Handler implementation for gPTimerDriver_Unclaim
      //!
      //! This should be provided with a timer identifier that was returned by
      //! a previous call to gPTimerDriver_Claim.
      //!
      //! Port calls will assert if the provided timer identifier does not
      //! correspond to a timer that is claimed by the calling client.
      //!
      void gPTimerDriver_Unclaim_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          I8 timer /*!< Which timer to unclaim*/
      );

      //! Handler implementation for gPTimerDriver_Claim
      //!
      //! Attempt to claim a timer.  If the timer code is a particular timer,
      //! the port call will attempt to acquire that timer, and will return
      //! either that timer's code if the acquisition was successful,
      //! or NOT_AVAILABLE. If the timer code is TIMER_ANY, than the
      //! port call will attempt to acquire any free timer, and will return
      //! either the code for the granted timer if a timer was free, or
      //! NOT_AVAILABLE if all timers were in use. Requests for reserved
      //! timers will be denied.
      //!
      //! Port calls will assert if the request is not for a non-error-code
      //! member of Drv::GPTimer::Code.
      //!
      I8 gPTimerDriver_Claim_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          I8 timer /*!< Which timer to attempt to claim*/
      );

      //! Handler implementation for gPTimerDriver_ReadControl
      //!
      //! Reads and returns the control register of the specified
      //! timer.
      //!
      //! Port calls will assert if the given timer is not owned by the
      //! calling client, or if the given timer is not valid.
      //!
      U32 gPTimerDriver_ReadControl_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          I8 timer /*!< Which timer's control register to read*/
      );

      //! Handler implementation for gPTimerDriver_WriteCounter
      //!
      //! Writes the counter register of the specified timer.
      //!
      //! Port calls will assert if the given timer is not owned by the
      //! calling client, or if the given timer is not valid.
      //!
      void gPTimerDriver_WriteCounter_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          I8 timer, /*!< Which timer's counter register to write*/
          U32 counter /*!< New value of counter register to write*/
      );

      //! Handler implementation for gPTimerDriver_WriteControl
      //!
      //! Writes the control register of the specified timer.
      //!
      //! Port calls will assert if the given timer is not owned by the
      //! calling client, or if the given timer is not valid.
      //!
      void gPTimerDriver_WriteControl_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          I8 timer, /*!< Which timer's control register to write*/
          U32 control /*!< New value of control register to write*/
      );

      //! Handler implementation for gPTimerDriver_ReadCounter
      //!
      //! Read and return the counter register of the specified
      //! timer.
      //!
      //! Port calls will assert if the given timer is not owned by the
      //! calling client, or if the given timer is not valid.
      //!
      U32 gPTimerDriver_ReadCounter_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          I8 timer /*!< Which timer's counter register to read*/
      );

      //! Handler implementation for gPTimerDriver_ReadReload
      //!
      //! Read and return the reload register of the specified
      //! timer.
      //!
      //! Port calls will assert if the given timer is not owned by the
      //! calling client, or if the given timer is not valid.
      //!
      U32 gPTimerDriver_ReadReload_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          I8 timer /*!< Which timer's reload register to read*/
      );

      //! Handler implementation for gPTimerDriver_WriteReload
      //!
      //! Write the reload register of the specified timer.
      //!
      //! Port calls will assert if the given timer is not owned by the
      //! calling client, or if the given timer is not valid.
      //!
      void gPTimerDriver_WriteReload_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          I8 timer, /*!< Which timer's reload register to write*/
          U32 reload /*!< New value of reload register to write*/
      );

      // ----------------------------------------------------------------------
      // Private data members
      // ----------------------------------------------------------------------

      //! Keep track of which timers are reserved
      //!
      static bool reservedTimers[GPTimer::NTIMERS];

      //! Keep track of which timers are free
      //!
      static bool freeTimers[GPTimer::NTIMERS];

      //! Keep track of who owns which timer.
      //!
      static Os::TaskId owners[GPTimer::NTIMERS];

      // ----------------------------------------------------------------------
      // Helper functions
      // ----------------------------------------------------------------------

      //! Initialize the members for tracking timer ownership
      //!
      void initTimerOwners(void);

      //! Configure a timer. The parameters correspond to those of the constructor;
      //! documentation can be found in the SDD.
      //!
      void cfgTimer(I8 timer,
                    const bool reserved, const bool usrConfig,
                    const U32 cntReg, const U32 rldReg, const U32 ctlReg);
  };

} // end namespace Drv

#endif
