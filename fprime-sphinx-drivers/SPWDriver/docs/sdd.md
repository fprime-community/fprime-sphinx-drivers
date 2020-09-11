Drv::SPWDriver Component
===

## 1. Introduction

`Drv::SPWDriver` is a passive F' component that provides application level
software interface to the GR712 on-chip SpaceWire core. Specifically, it
handles the sending of SpaceWire packets using RMAP.

## 2. Design

#### 2.1 Component Diagram

The `Drv::SPWDriver` component has the following component block description
diagram (BDD) diagram:

![`Drv::SPWDriver` Diagram](img/SPWDriverBDD.jpg "Drv::SPWDriver")

#### 2.2 Ports

The `Drv::SPWDriver` component uses the following port types:

| Port Data Type             | Name      | Direction | Kind          | Usage                                                    |
|----------------------------|-----------|-----------|---------------|----------------------------------------------------------|
| `Drv::SphinxSPW_WriteRMAP` | writeRMAP | input     | guarded_input | Sends an RMAP write request to a specified node          |
| `Drv::SphinxSPW_ReadRMAP`  | readRMAP  | input     | guarded_input | Sends an RMAP read request to a specified node           |
| `Drv::SphinxSPW_Status`    | getStatus | input     | guarded_input | Checks the status of the most recently sent RMAP request |
| `Drv::SphinxSPW_Status`    | reset     | input     | guarded_input | Resets the SpaceWire link                                |

### 2.3 Functional Description

#### 2.3.1 writeRMAP Port

Initiates an RMAP write transaction to the node specified in the arguments,
sending data from the provided memory buffer. There can only be at most one
outstanding transaction the status of which can be queried via the getStatus()
port. If another transaction is requested before the current one is finished,
then the current one will be aborted no matter what state it is in.
(Transmissions aborted in the middle of sending will likely send an EEP
indicating to the other node to ignore the sent data, but there is no way to
rescind a fully-sent write request).

If the acknowledge argument is 1, the driver will also listen for a reply to
the write request before certifying completion. 

#### 2.3.2 readRMAP Port

Same as writeRMAP(), except this sends an RMAP read request, writing the
returned data into the provided memory buffer. 

The data written to the buffer _will include the SpaceWire and RMAP header_,
which the application can ignore by offsetting by `READ_RESPONSE_HDR_SIZE`
defined in RMAPHeader.hpp, plus 4 (for the data CRC)

#### 2.3.3 getStatus Port

Returns the status of the calling component's most recent transaction. Status
codes can be found in SPWStatus.hpp.

#### 2.3.4 reset Port

Resets the SpaceWire link and returns the current state of the link. The state
will be one of SPW_STATUS_SUCCESS, SPW_STATUS_ERR_INIT, or
SPW_STATUS_ERR_DISCONNECTED.
