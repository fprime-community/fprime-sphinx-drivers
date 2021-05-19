// ====================================================================== 
// \title  SphinxDrvUtil.hpp
// \author arizvi
// \brief  hpp file for Sphinx Util 
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
// ====================================================================== 

#ifndef SPHINX_DRV_UTIL_HPP
#define SPHINX_DRV_UTIL_HPP

#include "Fw/Types/BasicTypes.hpp"
#include "SphinxDrvTimerUtil.hpp"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifndef TGT_OS_TYPE_VXWORKS
#include <map>
#endif

#define U32_MAX (0xffffffff)
#define I32_MAX (0x7fffffff)
#define I32_MIN (0x80000000)
#define BITS_PER_BYTE 8

namespace Drv {
#ifndef TGT_OS_TYPE_VXWORKS
  /* Emulated register memory for unit tests */
  extern std::map<U32, U32> emuRegMap;
#endif

  /**
   * type manipulation functions
   */

  /* Converts a buffer address into a U32 for writes
   *
   * NB: this will chop off a pointer in 64-bit architectures. Only use if
   * you're sure you want exactly 4 bytes from the pointer, but may need to
   * cross-compile in different architectures.
   */
  U32 ptrToU32(U8* ptr);

  /* Converts a word address into a U32
   *
   * NB: this will chop off a pointer in 64-bit architectures. Only use if
   * you're sure you want exactly 4 bytes from the pointer, but may need to
   * cross-compile in different architectures.
   */
  U32 ptrToU32(U32* ptr);

  /* Takes the address of the word as a U8* buf
   */
  U8* wordAsBuf(U32& word);

  /**
   * Memory manipulation functions
   */

  /* Writes one bit at a given address */
  void writeMemBit(U8* mem, U32 bit, U32 val);

  /* Reads one bit at a given address */
  U32 readMemBit(U8* mem, U32 bit);

  /**
   * Register manipulation functions
   */

  /* Reads the register of a given address */
  U32 readReg(U32 reg);

  /* Writes to the register of a given address */
  void writeReg(U32 reg, U32 val, U32 flag = 0);
  /* Reads a bitrange of the register of a given address
   *
   * Imagine scanning from right (LSB) to left (MSB), extracting `count` bits
   * starting at bit `start`
   *
   * e.g. readRegPartial(reg, 0, 32) is the entire word
   *      readRegPartial(reg, 5, 1) is bit 5's value
   *      readRegPartial(reg, 8, 8) is the 2nd LSB byte's value
   */
  U32 readRegPartial(U32 reg, U32 start, U32 count);

  /* Writes a bitrange of the register of a given address
   *
   * Imagine scanning from right (LSB) to left (MSB), overwriting `count` bits
   * starting at bit `start`
   *
   * NB: Functions like a read-modify-write, but is not atomic
   *
   * e.g. num = 0xf00
   *      writeRegPartial((U32)(&num), 0, 4, 0xf); num == 0xf0f
   *      writeRegPartial((U32)(&num), 4, 4, 0xe); num == 0xfef
   *      writeRegPartial((U32)(&num), 8, 8, 0xbe); num == 0xbeef
   */
  void writeRegPartial(U32 reg, U32 start, U32 count, U32 val);

  /* Reads one bit value at a given register */
  U32 readBit(U32 reg, U32 bit);
}

#endif

