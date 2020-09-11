Drv::WakeupManager Component SDD
===

## 1. Introduction

`Drv::WakeupManager` is an active F' component that allow clients to request
that they be woken up after a specified time, and block until that time
elapses.

## 2. Requirements

1. The manager shall wake a task no earlier than its requested wakeup time.
2. The manager shall accept wakeup times at microsecond granularity.
3. The manager shall accept wakeup times at least 2^32 microseconds forward in time.
4. The manager shall implement an absolute maximum on the number of tasks that may
   simultaneously request wakeups.

## 3. Design

### 3.1 Component Diagram

![`Drv::WakeupManager` Diagram](./img/WakeupManagerBDD.jpg "Drv::WakeupManager")

### 3.2 Ports

| Port Data Type           | Name                | Direction | Kind       | Usage                                                         |
|--------------------------|---------------------|-----------|------------|---------------------------------------------------------------|
| Drv::WakeupManager_Sleep | wakeupManager_Sleep | input     | sync_input | Request to be put to sleep for a given number of microseconds |
| Fw::Time                 | time                | output    | output     | Get the system time                                           |

### 3.3 Functional Description

#### 3.3.1 wakeupManager_Sleep

Request to be put to sleep for at least the given number of microseconds.
The actual amount of time spent asleep may be longer than requested,
especially for low-priority tasks.

Port calls will assert if more than the maximum number of tasks are
attempting to use the service.

### 3.4 Usage Notes

If a component is sleeping, it will not respond to any calls to its own ports.
Thus, it is important to ensure that a component does not put itself to sleep
during a large number of input port calls, as that will fill the message queue
and cause an assertion.  For example, a component in a rate group should not
sleep across its rate group tick.  It may be helpful to consider whether it
would be appropriate to busy-wait in a given situation:  if it would not be,
than it is also not appropriate to use this component.
