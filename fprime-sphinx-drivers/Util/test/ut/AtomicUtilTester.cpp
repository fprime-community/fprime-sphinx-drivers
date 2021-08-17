#include "AtomicUtilTester.hpp"

namespace Drv {

    AtomicUtilTester::AtomicUtilTester(void) {};
    AtomicUtilTester::~AtomicUtilTester(void) {};

    void AtomicUtilTester::testAddition(void)
    {
        I32 test = 1;
        AtomicUtil::Add(&test, 2);
        ASSERT_EQ(3, test);
    }

    void AtomicUtilTester::testSubtraction(void)
    {
        I32 test = 3;
        AtomicUtil::Subtract(&test, 2);
        ASSERT_EQ(1, test);
    }

    void AtomicUtilTester::testAnd(void)
    {
        U32 test = 3;
        AtomicUtil::And(&test, 2);
        ASSERT_EQ(2, test);
    }

    void AtomicUtilTester::testOr(void)
    {
        U32 test = 3;
        AtomicUtil::Or(&test, 5);
        ASSERT_EQ(7 , test);
    }
}
