// ======================================================================
// \title  SphinxTimeComponentImpl.cpp
//  *  Created on: Mar 28, 2014
// *      Author: ortega, arizvi
// \brief  cpp file for SphinxTime component implementation class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
//
// ======================================================================


#include <fprime-sphinx-drivers/SphinxTime/SphinxTimeComponentImpl.hpp>
#include "Fw/Types/BasicTypes.hpp"
#include <Fw/Time/Time.hpp>
#include <Fw/Types/Assert.hpp>
#include <fprime-sphinx-drivers/Util/SphinxDrvUtil.hpp>
#include <fprime-sphinx-drivers/UtilityFunctions/UtilityFunctions.hpp>

extern "C" {
#include <time.h>
}

namespace Drv {

  // ----------------------------------------------------------------------
  // Construction, initialization, and destruction
  // ----------------------------------------------------------------------

  SphinxTimeComponentImpl ::
#if FW_OBJECT_NAMES == 1
    SphinxTimeComponentImpl(
        const char *const compName
    ) :
      SphinxTimeComponentBase(compName)
#else
    SphinxTimeComponentImpl(void)
#endif
  {
      this->m_first_cycle = true;
  }

  void SphinxTimeComponentImpl ::
    init(
        const NATIVE_INT_TYPE instance
    )
  {
    SphinxTimeComponentBase::init(instance);

      /* Setup watchdog first */
      /* Reload value for watchdog = 0xf423f * 60 = 999,999 * 60 = 59999940 */
      /* Timer4 is used for CDH watchdog */
      Drv::writeReg(WATCHDOG_CNT_REG, WATCHDOG_CNT_VAL);
      Drv::writeReg(WATCHDOG_RLD_REG, WATCHDOG_RLD_VAL);
      Drv::writeReg(WATCHDOG_CTRL_REG, WATCHDOG_CTRL_VAL);

      /* Set up the pre-scalar registers. */
      /* Reload value for pre-scalar = 0x27 = 39 */
      /* The pre-scaler value is decremented by 1 each system clock cycle */
      /* The system clock cycle rate is 40 MHz, which means a pre-scaler */
      /* value of 39 results in a trigger to the GP timers every 1 usec. */
      Drv::writeReg(GR712_SCALER_CNT_REG, GR712_SCALER_CNT_VAL);
      Drv::writeReg(GR712_SCALER_RLD_REG, GR712_SCALER_RLD_VAL);

      /* Set up the latching timer pre-scaler register */
      /* This should match the regular pre-scaler register configuration */
      /* to keep the two sets of timer on the same scale */
      Drv::writeReg(GR712_LATCH_SCALER_CNT_REG, GR712_LATCH_SCALER_CNT_VAL);
      Drv::writeReg(GR712_LATCH_SCALER_RLD_REG, GR712_LATCH_SCALER_RLD_VAL);

      /* Set up the TSTMP_LO registers. */
      /* Reload value for TSTMP_LO = 0xf423f = 999,999 */
      /* Latching timer 1 is used for usec */
      Drv::writeReg(TSTMP_LO_CNT_REG, TSTMP_LO_CNT_VAL);
      Drv::writeReg(TSTMP_LO_RLD_REG, TSTMP_LO_RLD_VAL);
      Drv::writeReg(TSTMP_LO_CTRL_REG, TSTMP_LO_CTRL_VAL);

      /* Set up the TSTMP_HI registers. */
      /* Reload value for TSTMP_HI = 0xffffffff */
      /* Latching timer 2 is used for whole sec */
      /* TSTMP_HI is chained to TSTMP_LO such that an underflow */
      /* for TSTMP_LO results in a decrement for TSTMP_HI */
      Drv::writeReg(TSTMP_HI_CNT_REG, TSTMP_HI_CNT_VAL);
      Drv::writeReg(TSTMP_HI_RLD_REG, TSTMP_HI_RLD_VAL);
      Drv::writeReg(TSTMP_HI_CTRL_REG, TSTMP_HI_CTRL_VAL);
  }

  SphinxTimeComponentImpl ::
    ~SphinxTimeComponentImpl(void)
  {

  }

  // ----------------------------------------------------------------------
  // Handler implementations for user-defined typed input ports
  // ----------------------------------------------------------------------

  void SphinxTimeComponentImpl ::
    timeInREL_handler(
        const NATIVE_INT_TYPE portNum,
        U32 SC_Time_Secs,
        U32 SC_Time_uSecs
    )
  {
      Fw::Time oldTime;
      Fw::Time newTime;
      time_source src = SPHINX_SC;

#if defined(BUILD_GR712_DEV)
      src = GR712;
#endif

      // Get SCLk value before update
      this->get_time(oldTime, src);

      // Add relative offset to current time value
      newTime.set(SC_Time_Secs, SC_Time_uSecs);
      newTime = Fw::Time::add(newTime, oldTime);

      // Write time to Sphinx FPGA
      this->update_time(newTime.getSeconds(), newTime.getUSeconds());

      // Get latest SCLK value after update
      this->get_time(newTime, src);

      this->log_ACTIVITY_HI_SphinxTime_Update(oldTime.getSeconds(), oldTime.getUSeconds(), newTime.getSeconds(), newTime.getUSeconds());
  }

  void SphinxTimeComponentImpl ::
    timeInABS_handler(
        const NATIVE_INT_TYPE portNum,
        U32 SC_Time_Secs,
        U32 SC_Time_uSecs
    )
  {
      Fw::Time oldTime;
      Fw::Time newTime;
      time_source src = SPHINX_SC;

#if defined(BUILD_GR712_DEV)
      src = GR712;
#endif

      // Get time before updating it
      this->get_time(oldTime, src);

      // Write time to Sphinx FPGA
      this->update_time(SC_Time_Secs, SC_Time_uSecs);

      // Get latest SCLK value after update
      this->get_time(newTime, src);

      this->log_ACTIVITY_HI_SphinxTime_Update(oldTime.getSeconds(), oldTime.getUSeconds(), newTime.getSeconds(), newTime.getUSeconds());
  }

    void SphinxTimeComponentImpl ::
    read_sphinx_uptime(void)
    {
        Fw::Time uptime;
        time_source src = SPHINX_UPTIME;

#if defined(BUILD_GR712_DEV)
        src = GR712;
#endif

        // Get uptime
        this->get_time(uptime, src);

        this->log_ACTIVITY_LO_SphinxTime_TimeSince_CDH_Boot(uptime.getSeconds(), uptime.getUSeconds());
    }

  void SphinxTimeComponentImpl ::
    schedIn_handler(
        const NATIVE_INT_TYPE portNum,
        NATIVE_UINT_TYPE context
    )
  {

      // Stroke CDH watchdog each schedIn
      Drv::writeReg(WATCHDOG_RLD_REG, WATCHDOG_RLD_VAL);
      Drv::writeReg(WATCHDOG_CTRL_REG, WATCHDOG_CTRL_VAL);
      Drv::writeReg(WATCHDOG_FW_REG, WATCHDOG_FW_VAL);

      if (this->m_first_cycle) {
          /* read and telemeter elapsed time since Sphinx power reset/boot-up */
          this->read_sphinx_uptime();
          this->m_first_cycle = false;
      }
  }

  void SphinxTimeComponentImpl ::
    timeGetPort_handler(
        const NATIVE_INT_TYPE portNum,
        Fw::Time &time
    )
  {
      time_source src = SPHINX_SC;

#if defined(BUILD_GR712_DEV)
      src = GR712;
#endif

      this->get_time(time, src);
  }

    void SphinxTimeComponentImpl ::
    update_time(U32 secs, U32 uSecs)
    {
        Fw::Time time1;
        Fw::Time time2;
        Fw::Time diff_time(0, 3); // 3 usec
        U32 cnt = 0;

#if defined(BUILD_SPHINX)
        // Write new time register values to Sphinx
    Drv::writeReg(SPHINX_SC_TIME_HI_SET, secs);
    Drv::writeReg(SPHINX_SC_TIME_LO_SET, uSecs);

    // Set the load time bit high
    Drv::writeReg(SPHINX_SC_TIME_CTRL, 0x1);
#endif

        // Wait 3-usecs for new values to load in
        // firmware SC time registers.
        // Use GR712 timers as source for wait counting
        // while time updates on Sphinx
        this->get_time(time1, GR712);

        do {
            this->get_time(time2, GR712);
            cnt++;
        } while((Fw::Time::sub(time2, time1) < diff_time) && (cnt < 1000));

        // make sure above loop iterated less than 1000 times
        FW_ASSERT(cnt < 1000);
    }

    void SphinxTimeComponentImpl ::
    get_time(Fw::Time &time, time_source src)
    {
        U32 usec_val;
        U32 sec_val;
        U32 secs_offset=0;
        U32 usecs_offset=0;

        switch (src) {
            case SPHINX_SC:
                secs_offset = SPHINX_SC_TIME_HI;
                usecs_offset = SPHINX_SC_TIME_LO;
                break;
            case SPHINX_UPTIME:
                secs_offset = SPHINX_UP_TIME_HI;
                usecs_offset = SPHINX_UP_TIME_LO;
                break;
            case GR712:
                secs_offset = TSTMP_HI_CNT_REG;
                usecs_offset = TSTMP_LO_CNT_REG;
                break;
            default:
                // Unknown time source
                FW_ASSERT(0);
                break;
        }
        //Generic roll-over atomic counter read algorithm
        Utils::read_U64_counter(reinterpret_cast<volatile U32*>(secs_offset), reinterpret_cast<volatile U32*>(usecs_offset), sec_val, usec_val);

        if (src == GR712) {
            time.set((TSTMP_HI_RLD_VAL - sec_val), (TSTMP_LO_RLD_VAL - usec_val));
        } else {
            time.set(sec_val, usec_val);
        }
    }

} // end namespace Drv
