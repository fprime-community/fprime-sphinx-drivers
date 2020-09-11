/*
 * SPWRequestQueue.cpp
 *
 *  Created on: January 09, 2017
 *      Author: Vincent Wong
 */

#include "Fw/Types/Assert.hpp"
#include "fprime-sphinx-drivers/SPWManager/SPWRequestQueue.hpp"

namespace Drv {

  SPWRequestQueue::SPWRequestQueue()
    : m_head(0), m_tail(0)
  {
    for (U32 i = 0; i < MAX_QUEUE_SIZE; i++) {
      m_queue[i] = SPWRequest();
    }
  }

  SPWRequest& SPWRequestQueue::top()
  {
    FW_ASSERT(isEmpty() == false);
    // NB: no lock, because only one producer will ever call top(), so if it's
    // not empty before, it won't be empty now
    return m_queue[m_tail];
  }

  I32 SPWRequestQueue::push(const SPWRequest& req)
  {
    m_mutex.lock();

    U32 nextHead = (m_head+1 < SPWRequestQueue::MAX_QUEUE_SIZE ? m_head+1 : 0);
    if (nextHead == m_tail) {
      // queue is full
      m_mutex.unLock();
      return 1;
    }

    // enqueue
    m_queue[m_head] = req;
    m_head = nextHead;

    m_mutex.unLock();
    return 0;
  }

  I32 SPWRequestQueue::pop()
  {
    if (isEmpty()) {
      return 1;
    }
    // NB: no lock, because only one producer will ever pop(), so if it's not
    // empty before, it won't be empty now
    m_tail = (m_tail+1 < SPWRequestQueue::MAX_QUEUE_SIZE ? m_tail+1 : 0);
    return 0;
  }

  bool SPWRequestQueue::isEmpty() const
  {
    return m_head == m_tail;
  }

}
