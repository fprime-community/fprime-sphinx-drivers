// ====================================================================== 
// \title  SphinxDrvReg.hpp
// \author ciankc
// \brief  hpp file for Sphinx Util Registers
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
// ====================================================================== 

#ifndef SPHINXDRVREG_HPP
#define SPHINXDRVREG_HPP

#include <Os/Log.hpp>
#include <Os/File.hpp>
#include <Os/FileSystem.hpp>
#include <Fw/Types/Assert.hpp>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

namespace Drv {

  class SphinxDrvReg
  {

    // ----------------------------------------------------------------------
    // Construction and destruction
    // ----------------------------------------------------------------------

  public:

    struct fileEntry {
      U32 init;
      U32 reg;
    };

    //! Construct object Tester
    //!
    SphinxDrvReg(fileEntry* msg, U32 length);

    //! Destroy object Tester
    //!
    ~SphinxDrvReg(void);

  public:

    // ---------------------------------------------------------------------- 
    // Tests
    // ---------------------------------------------------------------------- 
    void writeFile(void);

    static void clearFiles(void);

  private:

    // ----------------------------------------------------------------------
    // Variables
    // ----------------------------------------------------------------------

    fileEntry* regPair;
    U32 regLength;
  };

} // end namespace Drv

#endif
