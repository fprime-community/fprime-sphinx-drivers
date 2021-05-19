#ifndef ATOMIC_UTIL_TESTER_HPP
#define ATOMIC_UTIL_TESTER_HPP

#include <fprime-sphinx-drivers/Util/SphinxAtomicUtil.hpp>
#include <gtest/gtest.h>

namespace Drv {

    class AtomicUtilTester
    {
        public:

            AtomicUtilTester(void);
            ~AtomicUtilTester(void);

            void testAddition(void);
            void testSubtraction(void);
            void testAnd(void);
            void testOr(void);
    };

}

#endif
