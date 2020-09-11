Drv::Sphinx UART Onboard Driver Component SDD
===

## 1. Introduction

`Drv::SphinxUartOnboardDriver` is a passive F' component that handles UART communication on the Sphinx platform.

## 2. Design

#### 2.1 Component Diagram

The `Drv::SphinxUartOnboardDriver` component has the following component block description diagram (BDD):

![`Drv::SphinxUartOnboardDriver` BDD](img/SphinxUartOnboardDriverBDD.jpg "Drv::SphinxUartOnboardDriver block description diagram")

#### 2.2 Ports

The `Drv::SphinxUartOnboardDriver` component uses the following port types:

Name | Port Data Type | Direction | Kind | Usage
---- | -------------- | --------- | ---- | -----
read | `Drv::SphinxUart_readPort` | input | guarded_input | Receive n bytes of data from the UART device receiver into the specified read buffer.
write | `Drv::SphinxUart_writePort` | input | guarded_input | Transmit n bytes of data from the specified write buffer to the UART device transmitter.
bytesUsed | `Drv::SphinxUart_bytesUsedPort` | input | guarded_input | Returns the number of bytes available for reading in the buffer.
logOut | `Fw::Log` | output | output | Framework binary log output port
timeCaller | `Fw::Time` | output | output | Get current system time

### 2.3 Functional Description

#### 2.3.1 Component

`U8 portNum`               UART port to use

`U32 baudRate`             Transceiver rate

`U32 clockSpeed`            Processor clock speed (MHz)

The Sphinx Onboard UART Driver Component is a passive component that acts as the interface between other components and the UART hardware. Other components can utilize the read/write port in order to receive/send data over the UART. Both the read port and write port utilize timeouts to prevent the software getting stuck waiting for input/output.

The UART Driver Component can be initialized to utilize either hardware or firmware UARTs. UART ports 0, 1, 4 and 5 are hardware UARTs. UART ports 2, 3, 6 and 7 are firmware UARTs.


#### 2.3.2 read Port

`U8 *read_buf_ptr`      Pointer to buffer to store read bytes

`U32 nBytes`    Number of bytes to read

`U32 timeout`      Longest time to wait for data (in us)


The read port allows a user to request `nBytes` number of bytes from the UART driver, waiting at most `timeout` number of milliseconds for data to be available for reading. The requested bytes are stored to a location, `read_buf_ptr`, passed by the user. If less than `nBytes` are read within the timeout period, the timeout bit will be set in the return value. If a timeout occurs, any read bytes will remain in the internal buffer. Whether or not a timeout occurs, the UART communication error bits are checked and if active, the corresponding bits in the return value are set.

0 is a valid `timeout`. The behavior is the same as described above, except that the driver will not wait for data to become available for reading and instead will read what data is immediately available. It will return a timeout if `nBytes` number of bytes are not available. Passing 0 for `nBytes` will reset the internal circular buffer as well as flush the UART FIFO. For example, if there are 5 bytes in the internal circular buffer, invoking the write port with a 0 for `nBytes` will reset the buffer to contain 0 bytes.

If either a firmware or hardware UART is being utilized, the read port will read from an internal circular buffer that is filled using interrupts. This means that you may read data that was received before the read port was invoked.

The port returns 0 in the absence of any errors. In case of a non-zero return value, the flags are defined by the `IOErrorBit` enum in [SphinxUartOnboardDriverComponentImpl.hpp](../SphinxUartOnboardDriverComponentImpl.hpp "Drv::SphinxUartOnboardDriver Implementation Header"). All error flags have the most significant bit (MSB) set, resulting in a negative value when parsed as an integer. The receiver will be disabled at component destruction.

#### 2.3.3 write Port

`U8 *write_buf_ptr`      Pointer to buffer to write bytes from

`U32 nBytes`    Number of bytes to write

`U32 timeout`      Longest time to wait for data to be written (in us)

The write port allows a user to send `nBytes` number of bytes to the UART driver, waiting at most `timeout` number of milliseconds for data to be sent. The bytes to be sent are stored at a location, `write_buf_ptr`, passed by the user. If less than `nBytes` are sent over UART within the timeout period, the timeout bit will be set in the return value. Whether or not a timeout occurs, the bytes that were written successfully within the timeout period are sent over the UART interface.

If 0 is passed for `timeout` the port will immediately return a timeout bit value. Passing 0 for `nBytes` will immediately return without any error.

If a hardware UART is being utilized, the write port will return after all bytes have been transmitted over the UART (or after a timeout). If a firmware UART is being utilized, the write port will always wait until timeout is reached before returning.

The port returns 0 in the absence of any errors. In case of a non-zero return value, the flags are defined by the `IOErrorBit` enum in [SphinxUartOnboardDriverComponentImpl.hpp](../SphinxUartOnboardDriverComponentImpl.hpp "Drv::SphinxUartOnboardDriver Implementation Header"). All error flags have the most significant bit (MSB) set, resulting in a negative value when parsed as an integer.

#### 2.3.4 bytesUsed Port

The bytesUsed port returns a `U32` with the number of bytes available to be read from the internal circular buffer.

## 3. Rules-Based Tests

#### 3.1 Rules

The `Drv::SphinxUartOnboardDriver` component has the following rules:

Rule | Description | Precondition | Action | Rule Order
-----|-------------|--------------|--------|-----------
`BytesUsed::OK` | Port returns a U32 with the number of bytes available to read from circular buffer | Always true | Invoke to_bytesUsed which should return a nonnegative U32 | N/A
`Init::OK` | Initialize all FW ports at varying baud rates | Always true | Successfully initialize FW ports at different baud rates, fail for invalid port/baud rate | N/A
`Init::HWOK` | Initialize all HW ports at varying baud rates | Always true | Successfully initialize HW ports at different baud rates, fail for invalid port/baud rate | N/A
`Interrupt::OK` | Invoke the UART and GPIO interrupt handlers | Always true | The interrupts should return without error | N/A
`Reader::OK` | Read from the port into the buffer correctly | Always true | The read should return without error | N/A
`Reader::TIMEOUT` | The component will attempt a read with a timeout value of 0 | Always true | Invoke the read function with a timeout of zero and return with status IOErrorBit_TIMEOUT (0x1 << 2) | N/A
`Reader::NBYTES` | The component will attempt a read with a nBytes value of 0 | Always true | Invoke the read function with 0 nBytes and return without error and the circular buffer should be reset to zero | N/A
`Reader::NULLPTR` | The component will attempt a read into a nullptr buffer | Always true | Invoke the read function which should return with ASSERT_DEATH | N/A
`Reader::ERROR` | Write bits to overrun, parity, and framing errors during a read | Always true | Invoke the read function which should return the error codes for overrun (0x1 << 3), parity (0x1 << 0), and framing (0x1 << 1) | N/A
`Reader::EMPTY` | Set the rx_empty bit and read without error | Always true | Invoke the read function and return without error because the receiver is empty | N/A
`Reader::DATA` | Inovke the is_data_ready() function | Always true | Invoke the is_data_ready() function and return without error | N/A
`Reader::FWOK` | Initialize a firmware port and perform a read | Always true | Invoke the read function for the firmware port and return without error | N/A
`Writer::OK` | Write to the port into the buffer correctly | Always true | The write should return without error | N/A
`Writer::TIMEOUT` | The component will attempt a write with a timeout value of 0 | Always true | Invoke the write function with a timeout of zero and return with status IOErrorBit_TIMEOUT (0x1 << 2) | N/A
`Writer::NBYTES` | The component will attempt a write with a nBytes value of 0 | Always true | Invoke the write function with 0 nBytes and return without error | N/A
`Writer::NULLPTR` | The component will attempt a write into a nullptr buffer | Always true | Invoke the write function which should return with ASSERT_DEATH | N/A
