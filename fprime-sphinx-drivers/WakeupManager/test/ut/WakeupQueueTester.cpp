// File: WakeupQueueTester.cpp
// Author: Nathan Serafin (nathan.serafin@jpl.nasa.gov)
// Date: 31 July, 2018
//
// Implementation of tests for the WakeupQueue

#include "WakeupQueueTester.hpp"

namespace Drv
{
    WakeupQueueTester::WakeupQueueTester(void) {};
    WakeupQueueTester::~WakeupQueueTester(void) {};

    void WakeupQueueTester::enqEmpty(void)
    {
        WakeupQueue q;
        // -|

        WakeupQueue::Status status;

        status = q.enq(Fw::Time(0U, 1U));
        ASSERT_EQ(WakeupQueue::WQ_OK, status);
        // 1 -|


        Fw::Time time;
        status = q.peek(time);
        ASSERT_EQ(WakeupQueue::WQ_OK, status);
        ASSERT_EQ(Fw::Time(0U, 1U), time);
    }

    void WakeupQueueTester::enqHead(void)
    {
        WakeupQueue q;
        // -|

        WakeupQueue::Status status;

        status = q.enq(Fw::Time(0U, 2U));
        ASSERT_EQ(WakeupQueue::WQ_OK, status);
        // 2 -|

        status = q.enq(Fw::Time(0U, 1U));
        ASSERT_EQ(WakeupQueue::WQ_OK, status);
        // 1 -> 2 -|

        Fw::Time time;
        status = q.peek(time);
        ASSERT_EQ(WakeupQueue::WQ_OK, status);
        ASSERT_EQ(Fw::Time(0U, 1U), time);
    }

    void WakeupQueueTester::enqTail(void)
    {
        WakeupQueue q;
        // -|

        WakeupQueue::Status status;

        status = q.enq(Fw::Time(0U, 1U));
        ASSERT_EQ(WakeupQueue::WQ_OK, status);
        // 1 -|

        status = q.enq(Fw::Time(0U, 2U));
        ASSERT_EQ(WakeupQueue::WQ_OK, status);
        // 1 -> 2 -|

        Fw::Time time;
        status = q.peek(time);
        ASSERT_EQ(WakeupQueue::WQ_OK, status);
        ASSERT_EQ(Fw::Time(0U, 1U), time);
    }

    void WakeupQueueTester::deqEmpty(void)
    {
        WakeupQueue q;
        // -|

        WakeupQueue::Status status;

        Os::TaskId tid;

        status = q.deq(Fw::Time(0U, 1U), tid);
        ASSERT_EQ(WakeupQueue::WQ_EMPTY, status);
        // -|
    }

    void WakeupQueueTester::deqNotYet(void)
    {
        WakeupQueue q;
        // -|

        WakeupQueue::Status status;

        Os::TaskId tid;

        status = q.enq(Fw::Time(0U, 1U));
        ASSERT_EQ(WakeupQueue::WQ_OK, status);
        // 1 -|
        status = q.enq(Fw::Time(0U, 2U));
        ASSERT_EQ(WakeupQueue::WQ_OK, status);
        // 1 -> 2 -|

        status = q.deq(Fw::Time(0U, 0U), tid);
        ASSERT_EQ(WakeupQueue::WQ_NOT_YET, status);
        // 1 -> 2 -|
    }

    void WakeupQueueTester::peekEmpty(void)
    {
        WakeupQueue q;
        // -|

        WakeupQueue::Status status;

        Fw::Time time;

        status = q.peek(time);
        ASSERT_EQ(WakeupQueue::WQ_EMPTY, status);
    }

    void WakeupQueueTester::enqDeqLoopSing(void)
    {
        WakeupQueue q;
        // -|

        WakeupQueue::Status status;

        Os::TaskId tid;

        status = q.enq(Fw::Time(0U, 1U));
        ASSERT_EQ(WakeupQueue::WQ_OK, status);
        // 1 -|

        int i;
        for (i = 0; i < WakeupQueue::maxQSize; ++i) {
            status = q.deq(Fw::Time(0U, 2U), tid);
            if (status == WakeupQueue::WQ_OK) {
                ASSERT_EQ(Os::Task::getOsIdentifier(), tid);
            }
            else if (status == WakeupQueue::WQ_EMPTY) {
                break;
            }
            else {
                FAIL() << "Bad status from deq\n";
            }
        }
        // -|

        ASSERT_EQ(1, i);
    }

    void WakeupQueueTester::enqDeqLoopMult(void)
    {
        WakeupQueue q;
        // -|

        WakeupQueue::Status status;

        Os::TaskId tid;

        int i;

        status = q.enq(Fw::Time(0U, 1U));
        ASSERT_EQ(WakeupQueue::WQ_OK, status);
        // 1 -|

        status = q.enq(Fw::Time(0U, 1U));
        ASSERT_EQ(WakeupQueue::WQ_OK, status);
        // 1 -> 1 -|

        status = q.enq(Fw::Time(0U, 2U));
        ASSERT_EQ(WakeupQueue::WQ_OK, status);
        // 1 -> 1 -> 2 -|

        status = q.deq(Fw::Time(0U, 2U), tid);
        ASSERT_EQ(WakeupQueue::WQ_OK, status);
        ASSERT_EQ(Os::Task::getOsIdentifier(), tid);
        // 1 -> 2 -|

        status = q.enq(Fw::Time(0U, 2U));
        ASSERT_EQ(WakeupQueue::WQ_OK, status);
        // 1 -> 2 -> 2 -|

        status = q.enq(Fw::Time(0U, 3U));
        ASSERT_EQ(WakeupQueue::WQ_OK, status);
        // 1 -> 2 -> 2 -> 3 -|

        for (i = 0; i < WakeupQueue::maxQSize; ++i) {
            status = q.deq(Fw::Time(0U, 4U), tid);
            if (status == WakeupQueue::WQ_OK) {
                ASSERT_EQ(Os::Task::getOsIdentifier(), tid);
            }
            else if (status == WakeupQueue::WQ_EMPTY) {
                break;
            }
            else {
                FAIL() << "Bad status from deq\n";
            }
        }
        // -|

        ASSERT_EQ(4, i);

        status = q.enq(Fw::Time(0U, 4U));
        ASSERT_EQ(WakeupQueue::WQ_OK, status);
        // 4 -|

        status = q.enq(Fw::Time(0U, 5U));
        ASSERT_EQ(WakeupQueue::WQ_OK, status);
        // 4 -> 5 -|

        for (i = 0; i < WakeupQueue::maxQSize; ++i) {
            status = q.deq(Fw::Time(0U, 6U), tid);
            if (status == WakeupQueue::WQ_OK) {
                ASSERT_EQ(Os::Task::getOsIdentifier(), tid);
            }
            else if (status == WakeupQueue::WQ_EMPTY) {
                break;
            }
            else {
                FAIL() << "Bad status from deq\n";
            }
        }
        // -|

        ASSERT_EQ(2, i);
    }

    void WakeupQueueTester::enqDeqLoopFull(void)
    {
        WakeupQueue q;
        // -|

        WakeupQueue::Status status;

        Os::TaskId tid;

        int i;

        for (i = 0; i < WakeupQueue::maxQSize; ++i) {
            status = q.enq(Fw::Time(0U, 1U));
            ASSERT_EQ(WakeupQueue::WQ_OK, status);
        }

        for (i = 0; i < WakeupQueue::maxQSize; ++i) {
            status = q.deq(Fw::Time(0U, 1U), tid);
            if (status == WakeupQueue::WQ_OK) {
                ASSERT_EQ(Os::Task::getOsIdentifier(), tid);
            }
            else if (status == WakeupQueue::WQ_EMPTY) {
                break;
            }
            else {
                FAIL() << "Bad status from deq\n";
            }
        }
        // -|

        ASSERT_EQ(WakeupQueue::maxQSize, i);
    }

    void WakeupQueueTester::enqDeqSym(void)
    {
        WakeupQueue q;
        // -|

        WakeupQueue::Status status;

        status = q.enq(Fw::Time(0U, 1U));
        ASSERT_EQ(WakeupQueue::WQ_OK, status);
        // 1 -|

        status = q.enq(Fw::Time(0U, 1U));
        ASSERT_EQ(WakeupQueue::WQ_OK, status);
        // 1 -> 1 -|

        status = q.enq(Fw::Time(0U, 1U));
        ASSERT_EQ(WakeupQueue::WQ_OK, status);
        // 1 -> 1 -> 1 -|

        status = q.enq(Fw::Time(0U, 1U));
        ASSERT_EQ(WakeupQueue::WQ_OK, status);
        // 1 -> 1 -> 1 -> 1 -|

        status = q.enq(Fw::Time(0U, 1U));
        ASSERT_EQ(WakeupQueue::WQ_OK, status);
        // 1 -> 1 -> 1 -> 1 -> 1 -|

        Os::TaskId tid;

        status = q.deq(Fw::Time(0U, 2U), tid);
        ASSERT_EQ(WakeupQueue::WQ_OK, status);
        ASSERT_EQ(Os::Task::getOsIdentifier(), tid);
        // 1 -> 1 -> 1 -> 1 -|

        status = q.deq(Fw::Time(0U, 2U), tid);
        ASSERT_EQ(WakeupQueue::WQ_OK, status);
        ASSERT_EQ(Os::Task::getOsIdentifier(), tid);
        // 1 -> 1 -> 1 -|

        status = q.deq(Fw::Time(0U, 2U), tid);
        ASSERT_EQ(WakeupQueue::WQ_OK, status);
        ASSERT_EQ(Os::Task::getOsIdentifier(), tid);
        // 1 -> 1 -|

        status = q.deq(Fw::Time(0U, 2U), tid);
        ASSERT_EQ(WakeupQueue::WQ_OK, status);
        ASSERT_EQ(Os::Task::getOsIdentifier(), tid);
        // 1 -|

        status = q.deq(Fw::Time(0U, 2U), tid);
        ASSERT_EQ(WakeupQueue::WQ_OK, status);
        ASSERT_EQ(Os::Task::getOsIdentifier(), tid);
        // -|
    }

    void WakeupQueueTester::enqDeqAsym(void)
    {
        WakeupQueue q;
        // -|

        WakeupQueue::Status status;

        Os::TaskId tid;

        status = q.enq(Fw::Time(0U, 6U));
        ASSERT_EQ(WakeupQueue::WQ_OK, status);
        // 6 -|

        status = q.enq(Fw::Time(0U, 5U));
        ASSERT_EQ(WakeupQueue::WQ_OK, status);
        // 5 -> 6 -|

        status = q.enq(Fw::Time(0U, 7U));
        ASSERT_EQ(WakeupQueue::WQ_OK, status);
        // 5 -> 6 -> 7 -|

        status = q.deq(Fw::Time(0U, 4U), tid);
        ASSERT_EQ(WakeupQueue::WQ_NOT_YET, status);
        // 5 -> 6 -> 7 -|

        status = q.deq(Fw::Time(0U, 5U), tid);
        ASSERT_EQ(WakeupQueue::WQ_OK, status);
        ASSERT_EQ(Os::Task::getOsIdentifier(), tid);
        // 6 -> 7 -|

        status = q.deq(Fw::Time(0U, 5U), tid);
        ASSERT_EQ(WakeupQueue::WQ_NOT_YET, status);
        // 6 -> 7 -|

        status = q.deq(Fw::Time(0U, 6U), tid);
        ASSERT_EQ(WakeupQueue::WQ_OK, status);
        ASSERT_EQ(Os::Task::getOsIdentifier(), tid);
        // 7 -|

        status = q.deq(Fw::Time(0U, 6U), tid);
        ASSERT_EQ(WakeupQueue::WQ_NOT_YET, status);
        // 7 -|

        status = q.enq(Fw::Time(0U, 9U));
        ASSERT_EQ(WakeupQueue::WQ_OK, status);
        // 7 -> 9 -|

        status = q.enq(Fw::Time(0U, 8U));
        ASSERT_EQ(WakeupQueue::WQ_OK, status);
        // 7 -> 8 -> 9 -|

        status = q.deq(Fw::Time(0U, 6U), tid);
        ASSERT_EQ(WakeupQueue::WQ_NOT_YET, status);
        // 7 -> 8 -> 9 -|

        status = q.deq(Fw::Time(0U, 7U), tid);
        ASSERT_EQ(WakeupQueue::WQ_OK, status);
        ASSERT_EQ(Os::Task::getOsIdentifier(), tid);
        // 8 -> 9 -|

        status = q.deq(Fw::Time(0U, 7U), tid);
        ASSERT_EQ(WakeupQueue::WQ_NOT_YET, status);
        // 8 -> 9 -|

        status = q.deq(Fw::Time(0U, 8U), tid);
        ASSERT_EQ(WakeupQueue::WQ_OK, status);
        ASSERT_EQ(Os::Task::getOsIdentifier(), tid);
        // 9 -|

        status = q.deq(Fw::Time(0U, 8U), tid);
        ASSERT_EQ(WakeupQueue::WQ_NOT_YET, status);
        // 9 -|

        status = q.deq(Fw::Time(0U, 9U), tid);
        ASSERT_EQ(WakeupQueue::WQ_OK, status);
        ASSERT_EQ(Os::Task::getOsIdentifier(), tid);
        // -|

        status = q.deq(Fw::Time(0U, 9U), tid);
        ASSERT_EQ(WakeupQueue::WQ_EMPTY, status);
        // -|
    }

    void WakeupQueueTester::qMaxLen(void)
    {
        WakeupQueue q;

        WakeupQueue::Status status;

        Os::TaskId tid;

        for (int i = 0; i < WakeupQueue::maxQSize; ++i) {
            status = q.enq(Fw::Time(0U, 1U));
            ASSERT_EQ(WakeupQueue::WQ_OK, status);
        }

        status = q.enq(Fw::Time(0U, 1U));
        ASSERT_EQ(WakeupQueue::WQ_FULL, status);

        status = q.deq(Fw::Time(0U, 1U), tid);
        ASSERT_EQ(WakeupQueue::WQ_OK, status);
        ASSERT_EQ(Os::Task::getOsIdentifier(), tid);

        status = q.enq(Fw::Time(0U, 1U));
        ASSERT_EQ(WakeupQueue::WQ_OK, status);
    }
}
