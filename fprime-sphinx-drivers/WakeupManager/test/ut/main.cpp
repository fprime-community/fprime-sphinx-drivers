// File: main.cpp
// Author: Nathan Serafin (nathan.serafin@jpl.nasa.gov)
// Date: 31 July, 2018
//
// Definitions of GTest tests

#include "WakeupQueueTester.hpp"

TEST(WakeupQueueTest, EnqEmpty)
{
    Drv::WakeupQueueTester tester;
    tester.enqEmpty();
}

TEST(WakeupQueueTest, EnqHead)
{
    Drv::WakeupQueueTester tester;
    tester.enqHead();
}

TEST(WakeupQueueTest, EnqTail)
{
    Drv::WakeupQueueTester tester;
    tester.enqTail();
}

TEST(WakeupQueueTest, deqEmpty)
{
    Drv::WakeupQueueTester tester;
    tester.deqEmpty();
}

TEST(WakeupQueueTest, deqNotYet)
{
    Drv::WakeupQueueTester tester;
    tester.deqNotYet();
}

TEST(WakeupQueueTest, peekEmpty)
{
    Drv::WakeupQueueTester tester;
    tester.peekEmpty();
}

TEST(WakeupQueueTest, enqDeqLoopSing)
{
    Drv::WakeupQueueTester tester;
    tester.enqDeqLoopSing();
}

TEST(WakeupQueueTest, enqDeqLoopMult)
{
    Drv::WakeupQueueTester tester;
    tester.enqDeqLoopMult();
}

TEST(WakeupQueueTest, enqDeqLoopFull)
{
    Drv::WakeupQueueTester tester;
    tester.enqDeqLoopFull();
}

TEST(WakeupQueueTest, enqDeqSym)
{
    Drv::WakeupQueueTester tester;
    tester.enqDeqSym();
}

TEST(WakeupQueueTest, enqDeqAsym)
{
    Drv::WakeupQueueTester tester;
    tester.enqDeqAsym();
}

TEST(WakeupQueueTest, qMaxLen)
{
    Drv::WakeupQueueTester tester;
    tester.qMaxLen();
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
