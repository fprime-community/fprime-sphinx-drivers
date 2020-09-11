// ======================================================================
// \title  FlightDrvReg/SphinxDrvReg.cpp
// \author ciankc
// \brief  cpp file for Sphinx Flight Registers
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
// ======================================================================     

#include <fprime-sphinx-drivers/Util/SphinxDrvReg.hpp>

#define MAX_NUM_REGISTERS 20

namespace Drv{

  SphinxDrvReg ::
  SphinxDrvReg(fileEntry* msg, U32 length)
  {
    FW_ASSERT(msg != NULL);
    this->regPair = msg;
    this->regLength = length;
  }

  SphinxDrvReg ::
  ~SphinxDrvReg(void) 
  {

  }

  void SphinxDrvReg::writeFile(void)
  {
    return;
  }

  void SphinxDrvReg::clearFiles(void)
  {
    return;
  }

}
