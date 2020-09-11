Drv::NORFlashDriver Component
===

## 1. Introduction

`Drv::NORFlashDriver` is a passive F' component that provides application level
software interface to the off-chip NOR Flash (Die: [`S29JL064J`](S29JL064J.pdf "Die NOR")). Specifically, it
handles writing to, reading from, and erasing of the NOR Chip.

## 2. Design

#### 2.1 Component Diagram

The `Drv::NORFlashDriver` component has the following component block description
diagram (BDD) diagram:

![`Drv::NORFlashDriver` Diagram](img/NORFlashDriverBDD.jpg "Drv::NORFlashDriver")

#### 2.2 Ports

The `Drv::NORFlashDriver` component uses the following port types:

| Port Data Type                | Name          | Direction | Kind       | Usage                                                    |
|-------------------------------|---------------|-----------|------------|----------------------------------------------------------|
| `Drv::NORFlash_ReadB`         | read          | input     | sync_input | Read a byte from NOR at the specified address. Note: only one client should be attached. guarded_input is too slow. |
| `Drv::NORFlash_WriteB`        | write         | input     | sync_input | Write a byte to NOR at the specified address. Note: only one client should be attached. guarded_input is too slow. |

### 2.3 Functional Description

#### 2.3.1 read Port

Read a byte at the passed in address and assigns value to the passed in data pointer.

RETURN:  0 on success and non-zero on failure. Failure may occur if destination is not within the NOR_BANK memory map range.

#### 2.3.2 write Port

Write a byte at the specified bank and at the specific address. The write is a non-blocking operation. Typical program time is 6 microseconds. Maximum program time is 80 microseconds.
This timing does not include system level overhead like executing the two-or-four bus cycle sequence for the program command. See chapter 18 Erase and Programming Performance
in the NOR's data sheet for more information.

RETURN: 0 on success and non-zero on failure. Failure may occur if destination is not within the NOR_BANK memory map range.

## 3. Rules-Based Tests

#### 3.1 Rules

The `Drv::NORFlashDriver` component has the following rules:

Rule | Description | Precondition | Action | Rule Order
-----|-------------|--------------|--------|-----------
`Read::OK` | The component successfully (for LINUX) reads the NORFlash | Always true | Invoke read and assert that the status is NOR_FAILED since it is not running on VxWorks | Apply OK
`Read::ERROR` | The component correctly errors when given invalid arguments | Always true | Invoking read with a null pointer read buffer ASSERTS DEATH while invoking read with an invalid address returns with status NOR_FAILED | Apply ERROR
`Write::OK` | The component successfully (for LINUX) writes the NORFlash | Always true | Invoke write and assert that the status is NOR_FAILED since it is not running on VxWorks | Apply OK
`Write::ERROR` | The component correctly errors when given invalid arguments | Always true | Invoke write with an invalid address which returns with status NOR_FAILED | Apply ERROR
