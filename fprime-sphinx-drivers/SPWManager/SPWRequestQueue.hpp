/*
 * SPWRequestQueue.hpp
 *
 *  Created on: January 09, 2017
 *      Author: Vincent Wong
 */

#ifndef SPWREQUESTQUEUE_HPP_
#define SPWREQUESTQUEUE_HPP_

#include "Fw/Types/BasicTypes.hpp"
#include "Os/Mutex.hpp"
#include "fprime-sphinx-drivers/SPWManager/SPWRequest.hpp"

#define SPW_REQUEST_QUEUE_SIZE 16

namespace Drv {

  /**
   * SPWRequestQueue is a multiple-producer, single-consumer queue of SPWRequests
   *
   * It is thread-safe, as long as there is only ever one consumer
   */
  class SPWRequestQueue
  {
    public:
      SPWRequestQueue();

      /**
       * Returns the front element in the queue
       *
       * Asserts that the queue is not empty
       */
      SPWRequest& top();

      /**
       * Enqueue an element
       *
       * Returns 1 if queue is already full
       */
      I32 push(const SPWRequest& req);

      /**
       * Dequeues an element
       *
       * Returns 1 if queue is already empty
       */
      I32 pop();

      /**
       * Checks whether queue is empty
       */
      bool isEmpty() const;

    private:
      // head/tail circular buffer with one empty slot
      static const U32 MAX_QUEUE_SIZE = SPW_REQUEST_QUEUE_SIZE+1;

      U32 m_head;
      U32 m_tail;
      SPWRequest m_queue[MAX_QUEUE_SIZE];
      Os::Mutex m_mutex;
  };
}

#endif
