Drv::FPGASPIDriver Component
===

## 1. Introduction

`Drv::FPGASPIDriver` is a passive F' component that provides application level
software interface to the Sphinx FPGA's three SPI ports (1, 2, and 3). 

## 2. Requirements

Requirement | Description | Verification Method |
----------- | ----------- | -------------------
FPrime-FPGASPIDriver-00 | The component shall provide synchronous read and write port for SPI transactions | Inspection |
FPrime-FPGASPIDriver-01 | The component shall support multiple slave devices accessing the read/write port | Inspection |

## 3. Design

#### 3.1 Component Diagram

The `Drv::FPGASPIDriver` component has the following component block description
diagram (BDD) diagram:

![`Drv::FPGASPIDriver` Diagram](img/FPGASPIDriver.jpg "Drv::FPGASPIDriver")

#### 3.2 Ports

The `Drv::FPGASPIDriver` component uses the following port types:

| Port Data Type             | Name        | Direction | Kind          | Usage                                    |
|----------------------------|-------------|-----------|---------------|------------------------------------------|
| `Drv::SphinxFPGASPI_RW`    | read_write  | input     | guarded_input | Write to the SPI and read returned data. |

### 3.3 Functional Description

All of the interaction with the FPGA SPI driver is done through a single port. One call to this port acts as a single
SPI transaction (SS goes low and then returns high).  This means that all data for a given SPI transaction should be
written to the port in one call, and all the data returned from that transaction will return with the same call.

`Note:`this design was chosen to ensure that SPI transactions are completely atomic and will not be interrupted
by another component attempting to use the SPI.

This component is instantiated with the number (1, 2, or 3) of the FPGA SPI port that it is driving.

#### 3.3.1 read_write Port

The read_write port is used to send a data buffer (U8\*) to the SPI and fill a data buffer (U8\*) with the results. The
required parameters for this port are:

| Parameter Type | Name           | Direction | Description                                                 |
|--------------- |----------------|-----------|-------------------------------------------------------------|
| U8\*           | write_buf_ptr  | input     | Buffer containing data to write to SPI.                     |
| U8\*           | read_buf_ptr   | output    | Buffer to fill with returned SPI data. Will be overwritten. |
| U32            | nBytes         | input     | Number of bytes to both read and write.                     |
| U8             | activate_slave | input     | SPI slave to talk to. Must be slave number 0-7.             |
| U16            | timeout        | input     | Maximum CPU cycles allowed for each byte's SPI transmission |
| U8             | clock_bitrate  | input     | SPI clock-rate. 0: 10Mbs 1: 5Mbs, 2: 2.5Mbs, 3: 1.25Mbs.    |
| U8             | bit_order      | input     | Bit order for SPI transmission. 1: MSB first 0: LSB first.  |

### 3.4 Sequence Description

The slave-select line will be set low for the given slave. Then a byte will be written and a byte read nByte times
ensuring that all data was written and all data was read. Finally, the slave-select line will be returned high

If any byte takes more than timeout cycles to successfully transmit to the SPI, the entire transaction will end
with status: FPGA_SPI_ER_TIMEOUT

## 4. Rules-Based Tests

#### 4.1 Rules

The `Drv::FPGASPIDriver` component has the following rules:

Rule | Description | Precondition | Action | Rule Order
-----|-------------|--------------|--------|-----------
`ReadWrite::OK` | The component successfully initializes and read/writes | Always true | Invoke read/write with delay to busy-wait, eventually asserting DEATH when timeout occurs. Successfully invoke read/write with delay of 0 to prevent busy waiting | Apply OK
`ReadWrite::ERROR` | The component correctly errors when given invalid arguments | Always true | Null pointers, invalid nBytes, bit rates, bit order, and delay should ASSERT DEATH | Apply ERROR

## 5 Useful Definitions

The following table lists useful definitions for using the FPGASPI driver.  These definitions can be found by
including: FPGASPIDriverComponentImpl.hpp

| Symbol                             | Description                                                   |
|------------------------------------|---------------------------------------------------------------|
| FPGA_SPI_1_NUMBER                  | Convenience definition for the number of SPI 1 (1)            |
| FPGA_SPI_2_NUMBER                  | Convenience definition for the number of SPI 2 (2)            |
| FPGA_SPI_3_NUMBER                  | Convenience definition for the number of SPI 3 (3)            |
| FPGA_SPI_BITRATE_10_MBS            | Definition to specify 10Mbs data rate                         |
| FPGA_SPI_BITRATE_5_MBS             | Definition to specify 5Mbs data rate                          |
| FPGA_SPI_BITRATE_2_5_MBS           | Definition to specify 2.5Mbs data rate                        |
| FPGA_SPI_BITRATE_1_25_MBS          | Definition to specify 1.25Mbs data rate                       |
| FPGA_SPI_MAX_BYTES_PER_TRANSACTION | Maximum bytes allowed for 1 SPI transaction                   |
| FPGA_SPI_MAX_SLAVE_SELECT          | Maximum slave number                                          |
| FPGA_SPI_MSB_FIRST                 | Definition to specify MSB first transmission                  |
| FPGA_SPI_LSB_FIRST                 | Definition to specify LSB first transmission                  |
| FPGA_SPI_ER_TIMEOUT                | Error status representing timeout                             |
