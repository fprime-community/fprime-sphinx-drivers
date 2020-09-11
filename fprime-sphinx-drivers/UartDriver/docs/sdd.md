<title>Drv::UartDriver Component SDD</title>
# Drv::UartDriver Component

## 1. Introduction

Drv::UartDriver is a passive F' component that provides interface for communicating over a UART port using a file descriptor interface as configured in the VxWorks kernel.

## 2. Design

#### 2.1 Component Diagram

The `Drv::UartDriver` component has the following component block description diagram (BDD) diagram:

![`Drv::UartDriver` Diagram](img/UartDriverBDD.jpg "Drv::UartDriver")

#### 2.2 Ports

The `Drv::UartDriver` component uses the following port types:

Port Data Type | Name | Direction | Kind | Usage
-------------- | ---- | --------- | ---- | -----
`Drv::SphinxUartBuffer` | WriteSerial | input | guarded_input | Write data of size nbytes to the UART device. Returns the number of bytes written.
`Drv::SphinxUartBuffer` | ReadSerial | input | guarded_input | Non-blocking call to read data of up-to a specified number of bytes. Returns the number of bytes read.

### 2.3 Functional Description

#### 2.3.1 ReadSerial

When `Drv::UartDriver` receives a message on `ReadSerial`, the following occurs:
* Check if the UART file descriptor is open. If not then raise an ASSERT.
* Initialize the fd_set set to the empty set.
* Add the opened UART file descriptor to the fd_set set.
* Use the select call to determine if there is data to be read on the UART file descriptor. This select call will block until there is data in the UART file descriptor or the specified timeout has been reached. The timeout in this component is set to 0 for an immediate timeout.
* The select call returns a value status.
* If status is greater than 0, then read from the UART file descriptor up to nbytes. The read call returns a value bytes_read. If bytes_read is negative, then raise an ASSERT, otherwise return bytes_read.
* Else if status is less than 0, then raise an ASSERT.
* Return status.

#### 2.3.2 WriteSerial
When `Drv::UartDriver` receives a message on `WriteSerial`, the following occurs:
* Check if the UART file descriptor is open. If not then raise an ASSERT.
* Write data, up to nbytes, to the UART file descriptor. This write call returns a value status.
* If status == ERROR then raise an ASSERT
* Return status.
