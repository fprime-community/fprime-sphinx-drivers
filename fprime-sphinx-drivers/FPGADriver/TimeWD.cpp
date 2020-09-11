#include "TimeWD.hpp"
#include <Fw/Types/Assert.hpp>
#include <fprime-sphinx-drivers/SphinxTime/SphinxTimeComponentImpl.hpp>

extern "C" {
#include <sysLib.h>
#include <logLib.h>
#include <taskLib.h>
}

namespace Drv
{
  WDOG_ID sphinx_time_rti_wd;
  volatile U32 sphinx_time_num_rti;

  void FPGADriverComponentImpl::sphinx_time_rti_handlr(FPGADriverComponentImpl *comp)
  {
      I32 status;
      Svc::TimerVal timer;

      FW_ASSERT(comp != NULL);

      /* Call Time component */
      sphinx_time_num_rti++;
      if(sphinx_time_num_rti % sysClkRateGet() == 0)
      {
        /* TODO: Call SphinxTime at 1 HZ to update onboard time */
        comp->timeRTIOut_out(0,0);
      }

      /* Send out cycle */
      timer.take();
      comp->cycleOut_out(0,timer);
      
      /* Watchdog is called every sys clk tick. */ 
      status = wdStart(sphinx_time_rti_wd, 1, (FUNCPTR)sphinx_time_rti_handlr, (int)comp);
      FW_ASSERT(status != ERROR);
  }
  
  int FPGADriverComponentImpl::sphinx_time_go(FPGADriverComponentImpl *comp)
  {
      FW_ASSERT(comp != NULL);
 
      /* Create Watch-Dog Timer */
      sphinx_time_rti_wd = wdCreate();
      FW_ASSERT(sphinx_time_rti_wd != NULL);
  
      /* Set the RTI counter to 0 */
      sphinx_time_num_rti = 0;
  
      sphinx_time_rti_handlr(comp);

      return OK;
  }

};
