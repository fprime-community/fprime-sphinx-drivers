// ====================================================================== 
// \title  GPIODriverInterrupt.hpp
// \author ciankc
// \brief  hpp file for GPIODriverInterrupt component implementation class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
// ====================================================================== 
/** \file GPIODriverInterrupt.hpp */

#ifndef GPIODriverInterrupt_HPP
#define GPIODriverInterrupt_HPP

#include "fprime-sphinx-drivers/GPIOInterruptHandler/GPIOInterruptHandler.hpp"
#include "fprime-sphinx-drivers/GPIOInterruptRouter/GPIOInterruptRouter.hpp"

namespace Drv {
  
  class GPIODriverInterrupt :
    public GPIOInterruptHandler
  {
    public:
      GPIODriverInterrupt(void);
      ~GPIODriverInterrupt(void);

      void HandleGPIOInterrupt(void);
  };

}

#endif
