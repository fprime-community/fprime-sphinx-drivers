Drv::NORFlashManager Component
===

## 1. Introduction

`Drv::NORFlashManager` is an active F' component that uses the `Drv::NORFlashDriver` component to interface with the NOR Chip hardware.

## 2. Design

#### 2.1 Component Diagram

The `Drv::NORFlashManager` component has the following component block description
diagram (BDD) diagram:

![`Drv::NORFlashManager` Diagram](img/NORFlashManagerBDD.jpg "Drv::NORFlashManager")

#### 2.2 Ports

The `Drv::NORFlashManager` component uses the following port types:

| Port Data Type                     | Name          | Direction | Kind          | Usage                                                    |
|------------------------------------|---------------|-----------|---------------|----------------------------------------------------------|
| `Drv::NORFlash_RW`                 | request_read  | input     | async_input   | Receive a request to read from the client. |
| `Drv::NORFlash_RW`                 | request_write | input     | async_input   | Receive a request to write from the client. |
| `Drv::NOR_done`                    | write_done    | output    | output        | Send a done signal with a status number to the client when a write is finished to the NOR. |
| `Drv::NORFlash_EraseBankNumber`    | request_erase | input     | async_input   | Receive a request to erase from the client. |
| `Drv::NOR_done`                    | erase_done    | output    | output        | Send a done signal with a status number to the client when an erase chip is done. |
| `Drv::NOR_done`                    | worker_done   | input     | async_input   | Returns the status from the worker    |
| `Drv::NORFlash_EraseBankNumber`    | worker_erase  | output    | output        | Tell the worker to erase a given bank    |
| `Drv::NORFlash_Cancel`             | worker_cancel | output    | output        | Tell the worker to cancel the active request   |
| `Drv::NORFlash_Reset`              | worker_reset  | output    | output        | Tell the nor worker to completely reset   |
| `Drv::NORFlash_BW`                 | worker_write  | output    | output        | Tell the worker to write a block of data   |
| `Svc::Ping`                        | PingResponse  | output    | output        | Respond to ping   |
| `Svc::Ping`                        | PingRecv      | input     | async_input   | Receive a ping   |
| `Drv::NORFlash_Verify`             | worker_verify | output    | output        |Tell the worker to verify FSW in NOR. |
| `Drv::NORFlash_Verify`             | request_verification  | input     | async_input   | Receive a request to verify FSW in NOR.   |
| `Drv::NORFlash_ChecksumDone`       | verification_done  | output    | output        | Send a done signal with a status number to the client when NOR verification is done. |


It also has the following role ports:

| Port Data Type                                      | Name           | Direction | Role            |
|-----------------------------------------------------|----------------|-----------|-----------------|
| [`Fw::Cmd`](../../../../Fw/Cmd/docs/sdd.md)         | cmdIn          | input     | Cmd             |
| [`Fw::CmdReg`](../../../../Fw/Cmd/docs/sdd.md)      | cmdReg         | output    | CmdRegistration |
| [`Fw::CmdResponse`](..././../../Fw/Cmd/docs/sdd.md) | cmdResponse    | output    | CmdResponse     |
| [`Fw::Log`](../../../../Fw/Log/docs/sdd.md)         | eventOut       | output    | Log             |
| [`Svc::Sched`](../../../../Svc/Sched/docs/sdd.md)   | schedIn        | input     | Sched           |
| [`Svc::Time`](../../../../Svc/SphinxTime/docs/sdd.md) | timeCaller     | output    | TimeGet         |

### 2.3 States

| State            | Description                                                                                                                                 |
|------------------|---------------------------------------------------------------------------------------------------------------------------------------------|
| NORMGR_IDLE      | The state when the manager is not writing, erasing, or reading. Erasing and writing can only start when in the NORMGR_IDLE state.           |
| NORMGR_ERASING   | The state when the manager is erasing a bank on the NOR. Cannot move to another state until the erase is finished or the erase times out.   |
| NORMGR_READING   | When component is reading chunk to the NOR.                                                                                                 |
| NORMGR_RESETING  | When the NOR is resetting.                                                                                                                  |
| NORMGR_WRITING   | The state when the manager is writing to NOR. Cannot move to another state until the writing is done or the write times out.                |
| NORMGR_VERIFYING | The state when the manager is verifying the NOR. Cannot move to another state until the verification is done or the verification times out. |

### 2.4 Functional Description

#### 2.4.1 request_read Port

Used to implement reading data chunks out from NOR Flash.

#### 2.4.2 request_write Port

The client wanting to write to the NOR will issue a request through this port. Let *dest* be the write destination, *src* be the array of bytes to write, *count* be the number of bytes to write, and *NOR_POLL_TIMEOUT* be the max number of tries to verify a byte has been written. These values are passed in from the client.

1. If not in the *IDLE* state, then exit and issue a write done with a nonzero status.  
2. Disable the cache on the NOR.
3. Set the device to the Unlock Bypass Mode to facilitate faster programming.
4. for each byte in *src* do
    1. write byte to NOR
    2. verify data
       1. Read address that we want to verify
       2. If bit 7 matches our bit 7 of our data byte, then we successfully wrote.
       3. Otherwise if bit 5 (timeout bit) is not 1 then go back to verify data step and repeat for up-to *NOR_POLL*TIMEOUT* times
       4. If bit 5 equals 1 then read address to which we want to verify
       5. If bit 7 matches our data then we successfully wrote else we failed.
5. Send the Unlock Bypass Reset command to the device
6. Reset NORFlashManager's state, restore cache, and send client a write_done signal with status.

NOTE: For a successful write, an erase would have needed to be issued.

#### 2.4.3 write_done Port

Signal the client that a write is done with the specified status number. Status number is 0 on success and nonzero on failure.

#### 2.4.4 request_erase Port

Initiate the Chip Erase sequence for the whole bank at the provided bank address as specified in the NOR chip document ([`S29JL064J`](../../NORFlashDriver/docs/S29JL064J.pdf "Die NOR")) on page 36 Table 10.1.
The erase takes 71 seconds excluding the 00h programming of the whole chip prior to erasure. See chapter 18 Erase and Programming Performance in the NOR's data sheet for more information.

Let *bank_number* be the bank to erase. *bank_number* is passed in from the client.

1. If not in the *IDLE* state, then exit and issue a write done with a nonzero status.
2. Validate *bank_number* and map it to the NOR Flash bank address.
3. Disable the cache.
4. Issue a reset to the NOR Driver.
5. Issue an erase to the NOR Driver.
6. Set the state to ERASING

#### 2.4.3 erase_done Port

Signal the client that an erase is done with the specified status number. Status number is 0 on success and nonzero on failure.

#### 2.4.4 worker_done Port

Signal that the worker has finished a request.

#### 2.4.5 worker_erase Port

Start an erase via the worker.

#### 2.4.6 worker_cancel Port

Cancel the active worker function.

#### 2.4.7 worker_reset Port

Reset the worker and nor.

#### 2.4.8 worker_write Port

Write a block via the worker.


#### 2.4.9 schedIn Port

schedIn is used to determine if an erase is done and to timeout after a specified time. The port does the following

1. If in the *ERASING* state then
   1. Increment timeout_timer
   2. If timedout then signal client erase finished with an error and reset the NORFlashManager's state.
   3. Poll NORFlashDriver if erase is done.
   4. If erase is done then signal client erase finished successfully and reset the NORFlashManager's state.

## 3. Rules-Based Tests

#### 3.1 Rules

The `Drv::NORFlashManager` component has the following rules:

Rule | Description | Precondition | Action | Rule Order
-----|-------------|--------------|--------|-----------
`Cmd::Reset` | The NOR_FLASH_RESET command is sent for all 4 bank addresses. | Always true | Send the command and check that the NOR_RESET_FAIL event is triggered and the command response is an error if the state is NORMGR_ERASING. The NOR_FLASH_RESET event is triggered if the state is NORMGR_IDLE. With an invalid bank address the FAIL_TO_RESET event is triggered and the command response is an error. | Apply Reset
`Cmd::Timeout` | The set timeout commands for write, erase, and verify are sent. | Always true | Send the commands to set the write, erase, and verify timeouts with a timeout value of 100. Assert that there was a command response and check that the respective timeout member variable is set to 100. | Apply Timeout
`Erase::OK` | The component requests to erase all 4 banks with the correct command sequence | True when the state is idle | Invoke request erase for each of the 4 banks and assert that the state is updated to NORMGR_ERASING. Check that register 0xAAA is set to 0x10 and register 0x555 is set to 0x55 which corresponds to the NORFlash erase command sequence. | Apply OK
`Erase::ERROR` | The component fails to erase when it starts in the ERASING or WRITING state or with an invalid bank number | Always true | Invoke the request erase function and check that the correct events are triggered (ALREADY_ERASING, BUSY, and ERASE_FAIL respectively). The final state should be NORMGR_IDLE. | Apply ERROR
`Misc::SchedIn` | The component repeatedly calls the schedIn function for the ERASING, WRITING, and VERIFYING states, and calls the function in the READING state which does nothing. | Always true | Invoke the schedIn function 1000 times for each of the erase, write, and verify states. Check that the timer value equals 1001 (increments once after the check). Invoke the schedIn function in the reading state and check that the timer value remains at 0 as this triggers the default case which does nothing. | Apply SchedIn
`Misc::Ping` | The component calls the Ping function with a key of 0xCC. | Always true | Invoke the Ping function and assert in the from_PingResponse_handler that the key is 0cxCC. | Apply Ping
`Misc::Verify` | The component calls the request verification function while in the idle and reading states. | Always true | Invoke the request verification function in the reading state and assert that a VERIFY_BUSY event is triggered. Invoke the request verification function in the idle state with block filesize of 1024 and fsw filesize of 512. Check that the timer is set to zero, the state is set to VERIFYING, and the filesizes are the same in the from_worker_verify_handler | Apply Verify
`Read::OK` | The component requests to read data from 2 registers with edac enabled and disabled. | True when the state is idle | Write known data into registers. Invoke request read for the registers and check that the values are the same. Repeat with edac disabled. Assert that the status is NORMGR_READING. | Apply OK
`Read::ERROR` | The component fails to read when it is already in a busy state, or has a null ptr, invalid address, invalid count, or and out of bounds read. | Always true | Write a known value to a register. Invoke the request read function in the NORMGR_READING state and check that the value is not read back. ASSERT_DEATH when invoking the request read function with a null ptr, invalid address, invalid count, or an out of bounds read. | Apply ERROR
`Size::Block` | The component invokes the block size function for the Linux build | Always true | Invoke the block size function and check that the status is NORMGR_OK and the size is set to 0. | Apply Block
`Size::FSW` | The component invokes the FSW size function for the Linux build | Always true | Invoke the FSW size function and check that the status is NORMGR_OK and the size is set to 0. | Apply FSW
`Worker::Write` | Invokes the worker write with different status' and asserts that the correct event is triggered. | Always true | Invoke the worker write with status of OK, TIMEOUT, FAILED_TO_UNLOCK, FAILED_TO_READ, FAILED_TO_UNLOCK_PROGRAM, FAILED_TO_READ_RESET_BYPASS, FAILED_TO_UNLOCK_PROGRAM_RESET_BYPASS, FAILED_TO_RESET, FAILED_TO_RESET_BYPASS_RESET, and assert that the corresponding event is triggered. | Apply Write
`Worker::Read` | Invokes the worker read with different status' and asserts that the correct event is triggered. | Always true | Invoke the worker read with status of OK, FAILED_TO_READ, TIMEOUT, and assert that the corresponding event is triggered. | Apply Read
`Worker::Erase` | Invokes the worker erase with different status' and asserts that the correct event is triggered. | Always true | Invoke the worker erase with status of OK, FAILED_TO_RESET, TIMEOUT, FAILED_TO_ERASE, FAILED_TO_TIMEOUT_RESET, FAILED_TO_ERASE_RESET and assert that the corresponding event is triggered. | Apply Erase
`Worker::Reset` | Invokes the worker reset with different status' and asserts that the correct event is triggered. | Always true | Invoke the worker reset with status of OK and TIMEOUT, and assert that the corresponding event is triggered. | Apply Reset
`Worker::Verify` | Invokes the worker verify with different status' and asserts that the correct event is triggered. | Always true | Invoke the worker verify with status of OK and FAILED_TO_VERIFY, and assert that the corresponding event is triggered. | Apply Verify
`Worker::Error` | Invokes the worker done with states of WRITING, ERASING, READING, VERIFYING with invalid status'. Invoke worker done in the IDLE state, which is invalid. | Always true | Invoke the worker done with the above states and ASSERTS DEATH. | Apply Error
`Write::OK` | The component requests to write data from 2 registers with edac enabled and disabled. | True when the state is idle | Invoke request write for the registers and check that the values read from the registers are the same. Repeat with edac disabled. Assert that the status is NORMGR_WRITING. | Apply OK
`Write::ERROR` | The component fails to write when it is already in a busy state, or has a null ptr, invalid address, invalid count, or and out of bounds read. | Always true | Write a known value to a register. Invoke the request write function in the NORMGR_WRITING state and check that the value is not read back. ASSERT_DEATH when invoking the request read function with a null ptr, invalid address, invalid count, or an out of bounds read. | Apply ERROR
