Drv::SPWManager Component
===

## 1. Introduction

`Drv::SPWManager` is an active F' component that provides a convenience
interface to the SPWDriver, including timeouts, fragmenting, and asynchronous
status reporting for large requests.

## 2. Design

#### 2.1 Component Diagram

The `Drv::SPWManager` component has the following component block description
diagram (BDD) diagram:

![`Drv::SPWManager` Diagram](img/SPWManagerBDD.jpg "Drv::SPWManager")

#### 2.2 Ports

The `Drv::SPWManager` component uses the following port types:

| Port Data Type                    | Name            | Direction | Kind          | Usage                                                          |
|-----------------------------------|-----------------|-----------|---------------|----------------------------------------------------------------|
| `Drv::SphinxSPW_SetParam`         | setParam        | input     | guarded_input | Sets SpaceWire and RMAP parameters                             |
| `Drv::SphinxSPW_SendRequest`      | write           | input     | guarded_input | Performs an RMAP write synchronously                           |
| `Drv::SphinxSPW_SendRequest`      | read            | input     | guarded_input | Performs an RMAP read synchronously                            |
| `Drv::SphinxSPW_SendRequestAsync` | writeAsync      | input     | async_input   | Performs an RMAP write asynchronously                          |
| `Drv::SphinxSPW_SendRequestAsync` | readAsync       | input     | async_input   | Performs an RMAP read asynchronously                           |
| `Drv::SphinxSPW_Trigger`          | resetLink       | input     | async_input   | Reset the spacewire link and abort all existing async requests |
| `Drv::SphinxSPW_StatusOut`        | statusOut       | output    | output        | Report a change in status of most recent request               |
| `Drv::SphinxSPW_Status`           | driverGetStatus | output    | output        | Retrieve status of transaction from SPWDriver                  |
| `Drv::SphinxSPW_WriteRMAP`        | driverWriteRMAP | output    | output        | Tell SPWDriver to send an RMAP write request                   |
| `Drv::SphinxSPW_ReadRMAP`         | driverReadRMAP  | output    | output        | Tell SPWdriver to send an RMAP read request                    |
| `Drv::SphinxSPW_Status`           | driverReset     | output    | output        | Tell SPWdriver to reset the link                               |

It also has the following role ports:

| Port Data Type                                      | Name           | Direction | Role            |
|-----------------------------------------------------|----------------|-----------|-----------------|
| [`Fw::Cmd`](../../../../Fw/Cmd/docs/sdd.md)         | cmdIn          | input     | Cmd             |
| [`Fw::CmdReg`](../../../../Fw/Cmd/docs/sdd.md)      | cmdReg         | output    | CmdRegistration |
| [`Fw::CmdResponse`](..././../../Fw/Cmd/docs/sdd.md) | cmdResponseOut | output    | CmdResponse     |
| [`Fw::Log`](../../../../Fw/Log/docs/sdd.md)         | eventOut       | output    | Log             |
| [`Fw::Time`](../../../../Fw/Time/docs/sdd.md)       | timeCaller     | output    | TimeGet         |
| [`Svc::Sched`](../../../../Svc/Sched/docs/sdd.md)   | schedIn        | input     | Sched           |

### 2.3 Functional Description

#### 2.3.1 setParam Port

Configures several parameters for the SPWManager, including the address and
RMAP key of the node to send requests to, and the increment, verify, and
acknowledge flags of each request.

#### 2.3.2 write Port

Synchronously writes to the address of the destination node. The function will
not return until the entire request is fulfilled, encountered an error, or
timed out. The timeout argument is an implementation-dependent value that
specifies how many busy checks should be made.

This port call will only proceed if the manager is idle and is not serving any
other requests; otherwise, it will return with a busy status code.

For this and all other SpaceWire requests to the driver, SPWManager will first
check if the driver status is fine. If it is in some error or active state,
SPWManager will reset the link before issuing the new request.

#### 2.3.3 read Port

Synchronously reads from the address of the destination node. Behaves the same
as the write() port.

#### 2.3.4 writeAsync Port

Asynchronously writes to the address of the destination node. Once initiated,
the status of the request will be checked once per iteration cycle. When the
request has finished, errored, or timed out, the status will be reported via
the statusOut() port. The timeout argument is the number of ticks the request
can use in total before aborting.

If the manager is busy, this port call will queue the request. However, if the
max queue length is reached, the request will be rejected, and a busy message
will be sent out via statusOut().

#### 2.3.5 readAsync Port

Asynchronously reads from the address of the destination node. Behaves the same
as the writeAsync() port.

#### 2.3.6 resetLink Port

Triggers a resetLink on the SPWDriver, and aborts all of the async requests in
the queue including the current one.

#### 2.3.7 statusOut Port

Sends out the change in status of the asynchronous read/write request. The
status codes are defined in SPWRequestStatus.hpp.
