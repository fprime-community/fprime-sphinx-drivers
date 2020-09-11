// ====================================================================== 
// \title  GPIODriverInterrupt.cpp
// \author ciankc
// \brief  cpp file for GPIODriverInterrupt component implementation class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
// ====================================================================== 

#include <fprime-sphinx-drivers/GPIODriver/test/ut/GPIODriverInterrupt.hpp>
#include <fprime-sphinx-drivers/Util/SphinxDrvIntUtil.hpp>
#include <Fw/Types/Assert.hpp>

namespace Drv {

  GPIODriverInterrupt::GPIODriverInterrupt
    (void) : GPIOInterruptHandler()
  {

  }

  GPIODriverInterrupt::~GPIODriverInterrupt(void) 
  {

  }

  void GPIODriverInterrupt :: HandleGPIOInterrupt() {
    writeReg(0x10020000, 0xDEADBEEF);
  }

}
