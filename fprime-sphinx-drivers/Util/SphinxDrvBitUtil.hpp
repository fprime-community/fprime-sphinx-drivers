// ======================================================================
// \title  SphinxDrvBitUtil.hpp
// \author nserafin
// \brief  Implementation of bit-twiddling utilities.
//
// There are three versions of each register utility: one without a postfix,
// one with the postfix AtomicInt, and one with the postfix Atomic.  The
// no-postfix version has no synchronization, and is suitable only for unshared
// resources, the AtomicInt version has synchronization suitable for usage on
// shared resources in an interrupt context, and the Atomic version has
// synchronization suitable for usage on shared resources in a non-interrupt
// context.
//
// There are also utilities for manipulating words, rather than registers.
// Since these words are local, no synchronization is necessary.
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
// ======================================================================

#ifndef SPHINXDRVBITUTIL_HPP
#define SPHINXDRVBITUTIL_HPP

#include <fprime-sphinx-drivers/Util/SphinxDrvUtil.hpp>
#include <fprime-sphinx-drivers/Util/SphinxAtomicUtil.hpp>
#include <Fw/Types/BasicTypes.hpp>
#include <Fw/Types/Assert.hpp>

#include <FpConfig.hpp>

#include <Os/InterruptLock.hpp>

namespace Drv {

  /*
   * With no synchronization, clear the bit offset-many bits from the right
   * in the word at memory location addr.
   */
  inline void clearBit(POINTER_CAST uaddr, NATIVE_UINT_TYPE offset)
  {
    FW_ASSERT(offset < (sizeof(NATIVE_UINT_TYPE) * BITS_PER_BYTE));
    writeRegPartial(uaddr, offset, 1, 0);
  }

  /*
   * With no synchronization, set the bit offset-many bits from the right
   * in the word at memory location addr.
   */
  inline void setBit(POINTER_CAST uaddr, NATIVE_UINT_TYPE offset)
  {
    FW_ASSERT(offset < (sizeof(NATIVE_UINT_TYPE) * BITS_PER_BYTE));
    writeRegPartial(uaddr, offset, 1, 1);
  }

  /*
   * Atomically clear the bit offset-many bits from the right in the word at
   * memory location addr.
   *
   * Note: On non-VxWorks platforms this function is not concurrency safe.
   * The atomic wrappers take a pointer, but pointers to maps are not
   * guaranteed to be stable (though on most implementations they are),
   * across insertions and deletions.
   */
  inline void clearBitAtomic(POINTER_CAST uaddr, NATIVE_UINT_TYPE offset)
  {
    FW_ASSERT(offset < (sizeof(NATIVE_UINT_TYPE) * BITS_PER_BYTE));

#ifdef TGT_OS_TYPE_VXWORKS
    U32* reg = reinterpret_cast<U32*>(uaddr);
#else
    if(!Drv::emuRegMap.count(uaddr)) {
      Drv::emuRegMap[uaddr] = uaddr;
    }
    U32* reg = &Drv::emuRegMap[uaddr];
#endif

    AtomicUtil::And(reg, ~(1 << offset));
  }

  /*
   * Atomically set the bit offset-many bits from the right in the word at
   * memory location addr.
   *
   * Note: On non-VxWorks platforms this function is not concurrency safe.
   * The atomic wrappers take a pointer, but pointers to maps are not
   * guaranteed to be stable (though on most implementations they are),
   * across insertions and deletions.
   */
  inline void setBitAtomic(POINTER_CAST uaddr, NATIVE_UINT_TYPE offset)
  {
    FW_ASSERT(offset < (sizeof(NATIVE_UINT_TYPE) * BITS_PER_BYTE));

#ifdef TGT_OS_TYPE_VXWORKS
    U32* reg = reinterpret_cast<U32*>(uaddr);
#else
    if(!Drv::emuRegMap.count(uaddr)) {
      Drv::emuRegMap[uaddr] = uaddr;
    }
    U32* reg = &Drv::emuRegMap[uaddr];
#endif

    AtomicUtil::Or(reg, (1 << offset));
  }

  /*
   * Set the bit offset-many bits from the right in the given word.
   */
  inline void setBitInWord(NATIVE_UINT_TYPE& word, NATIVE_UINT_TYPE offset)
  {
      FW_ASSERT(offset < (sizeof(NATIVE_UINT_TYPE) * BITS_PER_BYTE));

      NATIVE_UINT_TYPE mask = static_cast<NATIVE_UINT_TYPE>(1U) << offset;

      word |= mask;
  }

  /*
   * Clear the bit offset-many bits from the right in the given word.
   */
  inline void clearBitInWord(NATIVE_UINT_TYPE& word, NATIVE_UINT_TYPE offset)
  {
      FW_ASSERT(offset < (sizeof(NATIVE_UINT_TYPE) * BITS_PER_BYTE));

      NATIVE_UINT_TYPE mask = ~(static_cast<NATIVE_UINT_TYPE>(1U) << offset);

      word &= mask;
  }
}

#endif
