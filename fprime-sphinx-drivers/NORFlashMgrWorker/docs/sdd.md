Drv::NORFlashMgrWorker Component
===

## 1. Introduction

`Drv::NORFlashMgrWorker` is an active F' component that uses the `Drv::NORFlashDriver` component to interface with the NOR Chip hardware.

## 2. Design

#### 2.1 Component Diagram

The `Drv::NORFlashMgrWorker` component has the following component block description
diagram (BDD) diagram:

![`Drv::NORFlashMgrWorker` Diagram](img/NORFlashMgrWorkerBDD.jpg "Drv::NORFlashMgrWorker")

#### 2.2 Ports

The `Drv::NORFlashMgrWorker` component uses the following port types:

Port Data Type                     | Name          | Direction/Kind | Usage  
------------------------------------|---------------|---------------|------
`Drv::NORFlash_Cancel`          | cancel      | guarded_input | Cancel an active request.
`Drv::NORFlash_EraseBankNumber` | erase       | async_input   | Erase a given bank.
`Drv::NORFlash_ReadB`           | read        | output        | Read a byte from nor driver.
`Drv::NOR_done`                 | statusOut   | output        | Return status when finished.
`Drv::NORFlash_Reset`           | reset       | async_input   | Reset the NOR worker.
`Drv::NORFlash_BW`              | write_block | async_input   | Start a write block.
`Drv::NORFlash_WriteB`          | write       | output        | Write a byte from nor driver.



It also has the following role ports:

| Port Data Type                                      | Name           | Direction | Role            |
|-----------------------------------------------------|----------------|-----------|-----------------|
| [`Fw::Time`](../../../../Fw/Time/docs/sdd.md)       | timeCaller     | output    | TimeGet         |
| [`Fw::Log`](../../../../Fw/Log/docs/sdd.md)         | eventOut       | output    | Log             |

### 2.3 States

No states used.

### 2.4 Functional Description

#### 2.4.1 cancel port

Registers a request to cancel. The active request will be canceled on the next erase/write cycle.


#### 2.4.2 erase Port

Starts erase of a given byte.


#### 2.4.2 read Output Port

Read a byte, using the NOR Driver, at the passed in address. The port is expect to return a `Drv::NOR_OK` on a successful read, and any other status on error.

#### 2.4.4 statusOut Port

Returns the status of the current active request.

#### 2.4.5 write_block Port

Write a block out to the nor driver

#### 2.4.6 write Output Port

Write a byte at the specified bank and at the specific address. The cache needs to be disabled before calling this port.

## 3. Rules-Based Tests

#### 3.1 Rules

The `Drv::NORFlashMgrWorker` component has the following rules:

Rule | Description | Precondition | Action | Rule Order
-----|-------------|--------------|--------|-----------
`Erase::OK` | The component invokes the erase function for a given bank | Always true | Determine the correct registers for the erase command sequence. Invoke request erase for bank 0 and assert that the erase sequence was written. | Apply OK
`Misc::Cancel` | The component calls the cancel handler function which sets the m_cancel private variable to true. | Always true | Invoke the cancel function and assert that the m_cancel private member variable is set to true. | Apply Cancel
`Misc::Reset` | The component calls the reset handler function which sets the m_cancel private variable to false. | Always true | Invoke the reset function and assert that the m_cancel private member variable is set to false. | Apply Reset
`Misc::Verify` | The component calls the verification function and computes the checksum | Always true | Invoke the request verification function. Call the verification function with an invalid size and ASSERT DEATH. Call the checksum function and check that the result of the call equals the checksum seed plus the value written to register 512. | Apply Verify
`Read::OK` | The component requests to read data from 2 registers. | Always true | Write known data into registers. Invoke request read for the registers and check that the values are the same. | Apply OK
`Read::ERROR` | The component fails to read when it has a null ptr, invalid bank, or an invalid count. | Always true | Write a known value to a register. Invoke the request read function with an address of 0x20000000 to trigger a NORMGR_FAILED_TO_READ error. ASSERT_DEATH when invoking the request read function with a null ptr, invalid bank, or an invalid count. | Apply ERROR
`Write::OK` | The component requests to write data from 2 registers. | Always true | Clear the registers we are writing to. Invoke request write for the registers and check that the values read from the registers are the same. | Apply OK
`Write::ERROR` | The component fails to write when it has a null ptr, invalid bank, or an invalid count. | Always true | Invoke the request write function and check for an error in statusOut. ASSERT_DEATH when invoking the request write function with a null ptr, invalid bank, or an invalid count. | Apply ERROR
