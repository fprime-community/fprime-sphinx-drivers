// File: WakeupQueue.hpp
// Author: Nathan Serafin (nathan.serafin@jpl.nasa.gov)
// Date: 31 July, 2018
//
// Class for the wakeup queue.

#ifndef WakeupQueue_HPP
#define WakeupQueue_HPP

#include <Fw/Types/BasicTypes.hpp>
#include <Fw/Time/Time.hpp>

#include <Os/TaskId.hpp>

namespace Drv
{
  //! The wakeup queue

  //! Implements a queue that maintains nodes in order of increasing
  //! wakeup time. Only one of these should be instantiated. All
  //! sequences of calls to member functions should be protected
  //! by the mutex in the WakeupManager.
  //!
  //! Occurences like being out of nodes will be responded to by
  //! returning an error code. The WakeupManager considers these
  //! to be fatal conditions, and asserts if they happen, but
  //! a different use case might need to handle them.
  //!
  class WakeupQueue
  {
      public:

        //! Construct the wakeup queue

        //! The free list and queue will be initialized.
        //!
        WakeupQueue(void);

        //! Destruct the wakeup queue

        //! Nothing is freed here, as the storage is statically
        //! allocated.
        //!
        ~WakeupQueue(void);

        //! Maximum size of the queue
        //!
        static const NATIVE_INT_TYPE maxQSize = 10;

        //! Enumerate returns
        //!
        enum Status {
            WQ_OK           =  0,
            WQ_FULL         = -1,
            WQ_NOT_YET      = -2,
            WQ_EMPTY        = -3,
            WQ_ERR          = -4,
        };

        //! Sort a new wakeup time into the queue

        //! The new wakeup time will be placed just before the
        //! first wakeup time that is the same or later.
        //! Returns WQ_OK on success, or WQ_FULL if the queue
        //! is full.
        //!
        //! Note that if assertions are turned off, WQ_ERR could
        //! be returned.
        //!
        Status enq(Fw::Time wakeupTime);

        //! Get a thread ID off the queue

        //! If the head of the queue has a wakeup time before or at
        //! the given time, it will be removed from the queue, its
        //! TID will be given through the provided reference, and
        //! WQ_OK will be returned. If the head of the queue has a wakeup
        //! time after the given time, WQ_NOT_YET will be returned,
        //! and if the queue is empty, WQ_EMPTY will be returned.
        //!
        Status deq(Fw::Time time, Os::TaskId& tid);

        //! Get the wakeup time of the head of the queue without removing it

        //! The wakeup time at the head of the queue will be returned
        //! through the provided reference. If the operation was
        //! successful WQ_OK is returned, but if the queue is empty
        //! WQ_EMPTY is returned.
        //!
        Status peek(Fw::Time& time);

      PRIVATE:

        //! Type of a queue node
        //!
        struct Node {
            Node* next;
            Fw::Time wakeupTime;
            Os::TaskId tid;
        };

        //! Statically allocated memory for the queue
        //!
        static Node pool[maxQSize];

        //! Free list
        //!
        Node* freeList;

        //! The queue itself
        //!
        Node* queue;

        //! Allocate a node out of the static pool

        //! This is a constant-time operation. Returns the address
        //! of the node, or NULL if none are available. No initialization
        //! is done on the node.
        //!
        Node* alloc(void);

        //! Release a node back in to the static pool

        //! This is a constant-time operation.
        //!
        void free(Node* node);
  };

}

#endif
