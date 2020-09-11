#ifndef SPHINX_TIME_WD_HPP

#include <wdLib.h>
#include <Fw/Types/BasicTypes.hpp>
#include <fprime-sphinx-drivers/FPGADriver/FPGADriverComponentImpl.hpp>

namespace Drv
{
  void FPGADriverComponentImpl::sphinx_time_rti_handlr(FPGADriverComponentImpl *comp);
  int FPGADriverComponentImpl::sphinx_time_go(FPGADriverComponentImpl *comp);
};
#endif
