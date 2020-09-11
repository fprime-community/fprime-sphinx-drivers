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
#include <Fw/Types/BasicTypes.hpp>
#include <Fw/Types/Assert.hpp>

#include <FpConfig.hpp>

#include <Os/InterruptLock.hpp>
#include <Os/TaskLock.hpp>


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
   * With synchronization suitable for a shared resource in an interrupt
   * context, clear the bit offset-many bits from the right in the word
   * at memory location addr.
   *
   * Task rescheduling will not occur until after an ISR completes, so
   * Os::TaskLock() is not required (and is, in fact, forbidden). The
   * ISR author could have re-enabled interrupts, however, so those must
   * be disabled.
   */
  inline void clearBitAtomicInt(POINTER_CAST uaddr, NATIVE_UINT_TYPE offset)
  {
    Os::InterruptLock iLock;

    iLock.lock();

    clearBit(uaddr, offset);

    iLock.unLock();
  }

  /*
   * With synchronization suitable for a shared resource in an interrupt
   * context, set the bit offset-many bits from the right in the word
   * at memory location addr.
   *
   * Task rescheduling will not occur until after an ISR completes, so
   * Os::TaskLock() is not required (and is, in fact, forbidden). The
   * ISR author could have re-enabled interrupts, however, so those must
   * be disabled.
   */
  inline void setBitAtomicInt(POINTER_CAST uaddr, NATIVE_UINT_TYPE offset)
  {
    Os::InterruptLock iLock;

    iLock.lock();

    setBit(uaddr, offset);

    iLock.unLock();
  }

  /*
   * With synchronization suitable for a shared resource in a non-interrupt
   * context, clear the bit offset-many bits from the right in the word at
   * memory location addr.
   *
   * Both task rescheduling and interrupts must be locked out to ensure
   * that preemption will not occur.
   */
  inline void clearBitAtomic(POINTER_CAST uaddr, NATIVE_UINT_TYPE offset)
  {
    NATIVE_INT_TYPE status;

    status = Os::TaskLock::lock();
    FW_ASSERT(status == 0);

    clearBitAtomicInt(uaddr, offset);

    status = Os::TaskLock::unLock();
    FW_ASSERT(status == 0);
  }

  /*
   * With synchronization suitable for a shared resource in a non-interrupt
   * context, set the bit offset-many bits from the right in the word at
   * memory location addr.
   *
   * Both task rescheduling and interrupts must be locked out to ensure
   * that preemption will not occur.
   */
  inline void setBitAtomic(POINTER_CAST uaddr, NATIVE_UINT_TYPE offset)
  {
    NATIVE_INT_TYPE status;

    status = Os::TaskLock::lock();
    FW_ASSERT(status == 0);

    setBitAtomicInt(uaddr, offset);

    status = Os::TaskLock::unLock();
    FW_ASSERT(status == 0);
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
