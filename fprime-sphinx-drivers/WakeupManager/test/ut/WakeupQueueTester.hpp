// File: WakeupQueueTester.hpp
// Author: Nathan Serafin (nathan.serafin@jpl.nasa.gov)
// Date: 31 July, 2018
//
// Tests for the WakeupQueue class

#ifndef WAKEUPQUEUETESTER_HPP
#define WAKEUPQUEUETESTER_HPP

#include "fprime-sphinx-drivers/WakeupManager/WakeupQueue.hpp"
#include <Os/Task.hpp>
#include <Os/TaskId.hpp>
#include <gtest/gtest.h>
#include "fprime-sphinx-drivers/Util/SphinxDrvReg.hpp"

namespace Drv
{
    class WakeupQueueTester
    {
        public:

            WakeupQueueTester();
            ~WakeupQueueTester();

            //
            // enq tests
            //

            // Check that enq properly handles the empty queue
            void enqEmpty(void);

            // Check that enq properly handles inserting a node at the head
            void enqHead(void);

            // Check that enq properly handles inserting a node at the tail
            void enqTail(void);

            //
            // deq tests
            //

            // Check that deq properly handles the empty queue
            void deqEmpty(void);

            // Check that deq properly handles a later wakeup time
            void deqNotYet(void);

            //
            // peek tests
            //

            // Check that peek properly handles the empty queue
            void peekEmpty(void);

            //
            // Combined tests
            //

            // Check that a single enq followed by repeated dequeueing until
            // the queue is empty works
            void enqDeqLoopSing(void);

            // Check that multiple enqs and deqs followed by repeated dequeueing
            // until the queue is empty works
            void enqDeqLoopMult(void);

            // Check that repeated dequeueing until a full queue is empty works
            void enqDeqLoopFull(void);

            // Check that enqs followed by an equal number of deqs works
            void enqDeqSym(void);

            // Check that interspersed enqs and deqs work
            void enqDeqAsym(void);

            //
            // Node allocator tests
            //

            // Check that there is an error for a more-than-maximally-sized queue
            void qMaxLen(void);
    };
}

#endif
