// File: main.cpp
// Author: Nathan Serafin (nathan.serafin@jpl.nasa.gov)
// Date: 27 June, 2018
//
// Functions for GTest.

#include "AtomicBitTwiddleTester.hpp"
#include "AtomicUtilTester.hpp"

TEST(AtomicBitTwiddleTest, TestAllBits)
{
    Drv::AtomicBitTwiddleTester tester;
    tester.testAllBits();
}

TEST(AtomicBitTwiddleTest, TestAllBitsAtomic)
{
    Drv::AtomicBitTwiddleTester tester;
    tester.testAllBitsAtomic();
}

TEST(AtomicBitTwiddleDeathTest, TestOutOfRangeSet)
{
    Drv::AtomicBitTwiddleTester tester;
    tester.testOutOfRangeSet();
}

TEST(AtomicBitTwiddleDeathTest, TestOutOfRangeClear)
{
    Drv::AtomicBitTwiddleTester tester;
    tester.testOutOfRangeClear();
}

TEST(AtomicUtilTester, TestAddition)
{
    Drv::AtomicUtilTester tester;
    tester.testAddition();
}

TEST(AtomicUtilTester, TestSubtraction)
{
    Drv::AtomicUtilTester tester;
    tester.testSubtraction();
}

TEST(AtomicUtilTester, TestAnd)
{
    Drv::AtomicUtilTester tester;
    tester.testAnd();
}

TEST(AtomicUtilTester, TestOr)
{
    Drv::AtomicUtilTester tester;
    tester.testOr();
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
