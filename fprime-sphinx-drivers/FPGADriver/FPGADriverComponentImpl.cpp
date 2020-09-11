// ====================================================================== 
// \title  FPGADriverImpl.cpp
// \author ortega
// \brief  cpp file for FPGADriver component implementation class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
// ====================================================================== 


#include <fprime-sphinx-drivers/FPGADriver/FPGADriverComponentImpl.hpp>
#include <Fw/Types/Assert.hpp>
#include "Fw/Types/BasicTypes.hpp"
#include <fprime-sphinx-drivers/Util/SphinxDrvUtil.hpp>

#ifdef TGT_OS_TYPE_VXWORKS
extern "C" {
#include <wdLib.h>
#include <sysLib.h>
#include <logLib.h>
#include <taskLib.h>
}
#elif TGT_OS_TYPE_LINUX || TGT_OS_TYPE_DARWIN
#define OK 0
#endif

namespace Drv {

  /* Global variables for the use in watchdog */
#ifdef TGT_OS_TYPE_VXWORKS
  WDOG_ID sphinx_time_rti_wd;
#endif
  volatile U32 sphinx_time_num_rti;

  // ----------------------------------------------------------------------
  // Construction, initialization, and destruction 
  // ----------------------------------------------------------------------

  FPGADriverComponentImpl ::
#if FW_OBJECT_NAMES == 1
    FPGADriverComponentImpl(
        const char *const compName
    ) :
      FPGADriverComponentBase(compName)
#else
    FPGADriverImpl(void)
#endif
  {

  }

  void FPGADriverComponentImpl ::
    init(
        const NATIVE_INT_TYPE instance
    ) 
  {
    int status;

    FPGADriverComponentBase::init(instance);
    status = this->sphinx_time_go();
    FW_ASSERT(status == OK);
  }

  FPGADriverComponentImpl ::
    ~FPGADriverComponentImpl(void)
  {

  }


#ifdef TGT_OS_TYPE_VXWORKS
    void FPGADriverComponentImpl::sphinx_time_rti_handlr(I32 arg)
    {
      I32 status;
#else
    void FPGADriverComponentImpl::sphinx_time_rti_handlr(I64 arg)
    {
#endif
      Svc::TimerVal timer;
      I32 clkrate = 10;

      FW_ASSERT(arg != 0);
      Drv::FPGADriverComponentImpl *comp = reinterpret_cast<Drv::FPGADriverComponentImpl*>(arg);

      FW_ASSERT(comp != NULL);

      /* Call Time component */
      sphinx_time_num_rti++;
      clkrate = MAX_DRIVING_RATE;

      if(sphinx_time_num_rti % clkrate == 0)
      {
        /* TODO: Call SphinxTime at 1 HZ to update onboard time */
        comp->timeRTIOut_out(0,0);
      }

      /* Send out cycle */
      timer.take();
      comp->cycleOut_out(0,timer);
      
      /* Watchdog is called every sys clk tick. */ 
#ifdef TGT_OS_TYPE_VXWORKS
      status = wdStart(sphinx_time_rti_wd, RTI_HANDLR_RATE, (FUNCPTR)&sphinx_time_rti_handlr, arg);
      FW_ASSERT(status != ERROR);
#endif

  }
  
  int FPGADriverComponentImpl::sphinx_time_go(void)
  {
#ifdef TGT_OS_TYPE_VXWORKS
      STATUS status;

      /* Set clock rate */
      status = sysClkRateSet(SYS_CLK_RATE_HZ);
      FW_ASSERT(status == OK, status);

      /* Create Watch-Dog Timer */
      sphinx_time_rti_wd = wdCreate();
      FW_ASSERT(sphinx_time_rti_wd != NULL);
#endif
      /* Set the RTI counter to 0 */
      sphinx_time_num_rti = 0;

      return OK;
  }

  // ----------------------------------------------------------------------
  // Handler implementations for user-defined typed input ports
  // ----------------------------------------------------------------------

  I32 FPGADriverComponentImpl ::
    read_reg_handler(
        const NATIVE_INT_TYPE portNum,
        U32 offset,
        U32 &value
    )
  {
    value = readReg(offset);
    return OK;
  }

  I32 FPGADriverComponentImpl ::
    write_reg_handler(
        const NATIVE_INT_TYPE portNum,
        U32 offset,
        U32 value
    )
  {
    writeReg(offset, value);
    return OK;
  }

} // end namespace Drv
