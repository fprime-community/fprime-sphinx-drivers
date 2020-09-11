// File: WakeupQueue.cpp
// Author: Nathan Serafin (nathan.serafin@jpl.nasa.gov)
// Date: 31 July, 2018
//
// Implementation of wakeup queue

#include <cstdlib>

#include <fprime-sphinx-drivers/WakeupManager/WakeupQueue.hpp>

#include <Fw/Types/Assert.hpp>

#include <Os/Task.hpp>

namespace Drv
{
    //
    // Definition of static data members
    //

    const NATIVE_INT_TYPE WakeupQueue::maxQSize;
    WakeupQueue::Node WakeupQueue::pool[WakeupQueue::maxQSize];

    //
    // Definition of member functions
    //

    WakeupQueue::WakeupQueue(void)
    {
        this->freeList = &this->pool[0];

        Node* runner = this->freeList;
        for (NATIVE_INT_TYPE i = 1; i < this->maxQSize; ++i) {
            runner->next = &(this->pool[i]);
            runner = runner->next;
        }
        runner->next = NULL;

        this->queue = NULL;
    }

    WakeupQueue::~WakeupQueue(void)
    {
        this->freeList = NULL;
        this->queue = NULL;
    }

    WakeupQueue::Status WakeupQueue::enq(Fw::Time wakeupTime)
    {
        Node* node = this->alloc();
        if (node == NULL) {
            return WQ_FULL;
        }

        node->wakeupTime = wakeupTime;
        node->tid = Os::Task::getOsIdentifier();

        if ((this->queue == NULL) ||
            (node->wakeupTime < this->queue->wakeupTime)) {
            node->next = this->queue;
            this->queue = node;
            return WQ_OK;
        }

        Node* here = this->queue->next;
        Node* there = this->queue;
        NATIVE_INT_TYPE count;
        for (count = 1; count < WakeupQueue::maxQSize; ++count) {
            if ((here == NULL) ||
                (node->wakeupTime < here->wakeupTime)) {
                node->next = here;
                there->next = node;
                return WQ_OK;
            }

            there = here;
            here = here->next;
        }

        FW_ASSERT(0);
        return WQ_ERR;
    }

    WakeupQueue::Status WakeupQueue::deq(Fw::Time time, Os::TaskId& tid)
    {
        if (this->queue == NULL) {
            return WQ_EMPTY;
        }

        if (this->queue->wakeupTime > time) {
            return WQ_NOT_YET;
        }

        Node* node = this->queue;
        this->queue = this->queue->next;

        tid = node->tid;

        this->free(node);

        return WQ_OK;
    }

    WakeupQueue::Status WakeupQueue::peek(Fw::Time& time)
    {
        if (this->queue == NULL) {
            return WQ_EMPTY;
        }

        time = this->queue->wakeupTime;

        return WQ_OK;
    }

    WakeupQueue::Node* WakeupQueue::alloc(void)
    {
        if (this->freeList == NULL) {
            return NULL;
        }

        Node* node = this->freeList;
        this->freeList = this->freeList->next;

        return node;
    }

    void WakeupQueue::free(WakeupQueue::Node* node)
    {
        FW_ASSERT(node != NULL);

        node->next = this->freeList;
        this->freeList = node;
    }
}
