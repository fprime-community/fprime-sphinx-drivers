// ====================================================================== 
// \title  SphinxDrvUtil.cpp
// \author arizvi
// \brief  cpp file for SPIDriver component implementation class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
// ====================================================================== 


#include <fprime-sphinx-drivers/Util/SphinxDrvUtil.hpp>
#include "SphinxDrvIntUtil.hpp" 
#include <fprime-sphinx-drivers/Include/utils.h>
#include "Fw/Types/BasicTypes.hpp"
#include "Fw/Types/Assert.hpp"
#include <Os/File.hpp>
#include <Os/FileSystem.hpp>

namespace Drv {
#ifndef TGT_OS_TYPE_VXWORKS
  /* Emulated register memory for unit tests */
  std::map<U32, U32> emuRegMap;
#endif

  /* Converts a buffer address into a U32 for writes */
  U32 ptrToU32(U8* ptr)
  {
    return static_cast<U32>(reinterpret_cast<POINTER_CAST>(ptr));
  }

  /* Converts a word address into a U32 */
  U32 ptrToU32(U32* ptr)
  {
    return static_cast<U32>(reinterpret_cast<POINTER_CAST>(ptr));
  }

  /* Takes the address of the word as a U8* buf */
  U8* wordAsBuf(U32& word)
  {
    return reinterpret_cast<U8*>(&word);
  }

  void writeMemBit(U8* mem, U32 bit, U32 val) {
    FW_ASSERT(val <= 1);
    FW_ASSERT(bit < 8);

    U8 mask = 1 << bit;
    val <<= bit;
    *mem = (*mem & (~mask)) | val;
  }

  U32 readMemBit(U8* mem, U32 bit) {
    FW_ASSERT(bit < 8);

    return (*mem >> bit) & 1;
  }

  /* Reads the register of a given address */
  U32 readReg(U32 reg) {
#ifdef TGT_OS_TYPE_VXWORKS
    volatile U32 * port = reinterpret_cast<U32*>(reg);
    U32 val = *port;
#else
    // Return register as value if register not set
    U32 val = reg;
    if(emuRegMap.count(reg)) {
      val = emuRegMap[reg];
    }

#endif

    return val;
  }

  /* Writes to the register of a given address */
  void writeReg(U32 reg, U32 val, U32 flag) {
#ifdef TGT_OS_TYPE_VXWORKS
    volatile U32 * port = reinterpret_cast<U32*>(reg);
    *port = val;
#else
    if(!flag) {
      emuRegMap[reg] = val;
    }
#endif
  }

  /* Reads a bitrange of the register of a given address */
  U32 readRegPartial(U32 reg, U32 start, U32 count) {
    FW_ASSERT(start < 32);
    FW_ASSERT(count <= 32 - start); // ensures start + count <= 32, overflow-safe

    U32 regVal = readReg(reg);

    return UNPACK_BITS(regVal, count, start, 0);
  }

  /* Writes a bitrange of the register of a given address */
  void writeRegPartial(U32 reg, U32 start, U32 count, U32 val) {
    FW_ASSERT(start < 32);
    FW_ASSERT(count <= 32 - start);

    if (count == 32) {
      writeReg(reg, val);
      return;
    }

    U32 countMask = ((1 << count) - 1) << start;
    val <<= start;

    // RMW
    U32 regVal = readReg(reg);
    regVal = (regVal & ~countMask) | (val & countMask);
    writeReg(reg, regVal);
  }

  /* Reads one bit value at a given register */
  U32 readBit(U32 reg, U32 bit) {
    return readRegPartial(reg, bit, 1);
  }
}
