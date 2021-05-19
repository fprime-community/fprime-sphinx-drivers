// File: AtomicBitTwiddleTester.hpp
// Author: Nathan Serafin (nathan.serafin@jpl.nasa.gov)
// Date: 27 June, 2018
//
// Test for the atomic bit-twiddling functions actually twiddling bits.
//
// Since the tests are run on Linux, it is not possible to test the
// atomicity of the operations.  Thus, the correctness of the bit-level
// operations is the only thing tested.

#ifndef ATOMICBITTWIDDLETESTER_HPP
#define ATOMICBITTWIDDLETESTER_HPP

#include <fprime-sphinx-drivers/Util/SphinxDrvBitUtil.hpp>
#include <Fw/Types/BasicTypes.hpp>
#include <FpConfig.hpp>
#include <gtest/gtest.h>

namespace Drv {

    class AtomicBitTwiddleTester
    {
        public:

            AtomicBitTwiddleTester(void);
            ~AtomicBitTwiddleTester(void);

            // Check that all bits can be set and cleared
            void testAllBits(void);

            // Check that all bits can be set and cleared atomically
            void testAllBitsAtomic(void);

            // Check that an out-of-range offset results in a failure for setBit
            void testOutOfRangeSet(void);

            // Check that an out-of-range offset results in a failure for clearBit
            void testOutOfRangeClear(void);
    };

}

#endif
