// File: main.cpp
// Author: Nathan Serafin (nathan.serafin@jpl.nasa.gov)
// Date: 27 June, 2018
//
// Functions for GTest.

#include "AtomicBitTwiddleTester.hpp"

TEST(AtomicBitTwiddleTest, TestAllBits)
{
    Drv::AtomicBitTwiddleTester tester;
    tester.testAllBits();
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

TEST(Teardown, OK) {
    Drv::SphinxDrvReg::clearFiles();
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
