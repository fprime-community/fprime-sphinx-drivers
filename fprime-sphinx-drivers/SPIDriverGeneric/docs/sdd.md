Drv::SPIDriverGeneric Component
===

## 1. Introduction

`Drv::SPIDriverGeneric` is a passive F' component that provides application level software interface to the GR712 on-chip SPI interface. 
- The driver supports use with multiple SPI slave devices, while protecting against race conditions. 
- The driver port interfaces are generic without any peripheral slave device references or dependencies.
- The driver implements a time-based timeout interface for read/write operations.
- The driver supports additional hardware features of the GR712 on-chip SPI controller, including adjustable SPI word length, and reversed bit order mode.

## 2. Design

#### 2.1 Component Diagram

The `Drv::SPIDriverGeneric` component has the following component block description diagram (BDD) diagram:

![`Drv::SPIDriverGeneric` Diagram](img/SPIDriverGenericBDD.jpg "Drv::SPIDriverGeneric")

#### 2.2 Ports

The `Drv::SPIDriverGeneric` component uses the following port types:

| Port Data Type               |   Name          |Direction   |Kind            |Usage 
| -----------------------------|   --------      |---------   |----------      |----- 
| `Drv::SphinxSPI_RW_Generic`  |   read_write_8  |input       |guarded_input   |Write n SPI words of sizes 4-8 bits from the write buffer to an SPI slave device and read back n spi words  into the read buffer. 
| `Drv::SphinxSPI_RW16_Generic`|   read_write_16 |input       |guarded_input   |Write n SPI words of sizes 9-16 bits from the write buffer to an SPI slave device and read back n spi words into the read buffer. 
| `Drv::SphinxSPI_RW32_Generic`|   read_write_32 |input       |guarded_input   |Write n SPI words of size 32 bits from the write buffer to an SPI slave device and read back n spi words into the read buffer. 
| `Drv::SphinxSPI_Claim`       |   spi_claim     |input       |guarded_input   |Claim the SPI Driver, allowing exclusive access to the SPI controller until it is unclaimed. 
| `Drv::SphinxSPI_Unclaim`     |   spi_unclaim   |input       |guarded_input   |Unclaim the SPI Driver, allowing other components to use it. 
| `Drv::SphinxSPI_Configure`   |   spi_configure |input       |guarded_input   |Configure the SPI Driver, setting mode registers with the desired parameters. 
| `Fw::Time`                   |   timeCaller    |output      |output          |Get the system time to determine when to timeout if data is not received or sent.  


### 2.3 Functional Description

**NOTE: The SPI core is reset (i.e. disabled and enabled) before performing a read/write transaction sequence.**

#### 2.3.1 Constructor (with arguments)
Allows the user to configure the SPI mode registers on construction. See the SPI_Configure port table below for details on how the SPI controller can be configured. This constructor and SPI_configure both take the same arguments.

#### 2.3.2 Constructor (No arguments)
If no arguments are given in the constructor, the SPI mode registers are configured using default settings. See the SPI_Configure table below for details on the default settings.

#### 2.3.3 Read_Write_8 Port
Generic use input port for spi words of sizes 4-8 bits. Components must call spi_claim before attempting to access this port.  Data to be written to the SPI slave device must be passed in as a U8* pointer to a write buffer. Similarly, a U8* pointer passed in will be filled with data read from the SPI slave device. The number of spi words to be transmitted must also be passed in the variable nBytes. Note that the write buffer must be spaced as a U8 array even if word sizes of less than 8 bits are used. 

#### 2.3.4 Read_Write_16 Port
Generic use input port for spi words of sizes 9-16 bits. Components must call spi_claim before attempting to access this port.  Data to be written to the SPI slave device must be passed in as a U16* pointer to a write buffer. Similarly, a U16* pointer passed in will be filled with data read from the SPI slave device. The number of spi words to be transmitted must also be passed in the variable nBytes. Note that the write buffer must be spaced as a U8 array even if word sizes of less than 16 bits are used. 

#### 2.3.5 Read_Write_32 Port
Generic use input port for spi words of size 32 bits. Components must call spi_claim before attempting to access this port. Data to be written to the SPI slave device must be passed in as a U32* pointer to a write buffer. Similarly, a U32* pointer passed in will be filled with data read from the SPI slave device. The number of spi words to be transmitted must also be passed in the variable nBytes. The GR712 on chip spi controller does not support SPI word size between 17-31 bits, so this port can only be used to send 32 bit words.  

#### 2.3.6 SPI_Claim Port 
Used to acquire the SPI semaphore, granting exclusive access to the SPI controller. Also records the Os-level task id of the task currently claiming the SPI controller in order to prevent other devices from using the read-write, unclaim and configure ports, and also prevent the claiming task from calling spi_claim twice and locking up the system.

#### 2.3.7 SPI_Unclaim Port 
Used to release the SPI semaphore, allowing other components to access the SPI controller. Ensures that only the task owning the SPI controller can release the SPI semaphore.

#### 2.3.8 SPI_Configure Port 
Used to configure various SPI mode register, requires that the caller is the task that currently owns the SPI controller.
The registers that can be configured using this port are the following:

|Argument | GR712 Register Name | Default | Usage |
|---------|---------------------|------------------------|------|
|`loopback_mode` | `LOOP` | `0` | Either 0 or 1. When loopback_mode is 1, the spi controller transmitter and receiver are interconnected.
|`clock_polarity`| `CPOL` | `0` | Either 0 or 1. Determines the polarity (idle state) of the SPICLK clock.
|`clock_phase` | `CPHA` | `0` | Either 0 or 1. When clock_phase is 0, data will be read on the first transition of SPICLK. When clock_phase is 1 data will be read on the second transition of SPICLK.
|`div_clock_16` | `DIV16` | `0` | Either 0 or 1. When div_clock_16 is 1, divide the system clock by 16.
|`reverse_mode` | `REV` | `1` | Either 0 or 1. When reverse_mode is 0, data is transmitted and received with least significant bit first. When reverse_mode is 1, data is transmitted and received with the most significant bit first. This register also effects how data is positioned in the TX and RX registers, which is handled during reading/writing depending on how reverse_mode has been configured.
|`word_len` | `LEN` | `8` |     Between 4-16 or 32. Determines the SPI word size in bits. Note that while the actual value written to the register is the word size-1 for 4-16 bit words or 0 for 32 bit word sizes, the driver handles this internally, so the actual desired word size should be passed in with this argument.
|`prescale_modulus ` | `PM` | `12` for SPHINX or `15` for GR712DEV | A 4-bit value (0-15). Used to divide the system clock and generate the SPI SPICLK clock frequency. See p170 of the GR712 manual for more details.
|`prescale_modulus_factor` | `FACT` | `0` | Either 1 or 0. Affects how the prescale_modulus is used to divide the system clock. See p170 of the GR712 manual for more details.
|`clock_gap` | `CG` | `0` | A 4-bit value (0-15). Determines the number of SPICLK clock cycles to insert between each consecutive word. Only applies when the transmit queue is non-empty. A clock_gap value of 0 enables back-to-back transfers.

## 3. Rules-Based Tests

#### 3.1 Rules

The `Drv::SPIDriverGeneric` component has the following rules:

|Rule | Description | Precondition | Action | Rule Order|
|-----|-------------|--------------|--------|-----------|
|`SPIMutex::UnclaimOK` | The component can successfully unclaim the SPI semaphore | The component currently owns the SPI semaphore | Invoke the SPI unclaim which should return without error and unclaim the semaphore | Apply ClaimOK |
|`SPIMutex::UnclaimDouble` | The component will correctly error on a second successive invocation of unclaim | The component currently does not own the SPI semaphore | Attempt to invoke the SPI unclaim function which should return with error SPI_UNCLAIM_NOT_OWNER_ERR | Apply ClaimOK, then Apply UnclaimOK|
|`SPIMutex::ClaimOK` | The component can successfully claim the SPI semaphore  | The component currently does not own the SPI semaphore | Invoke the SPI claim function which should return without error and claim the semaphore | N/A|
|`SPIMutex::ClaimDouble` | The component will correctly error on a second successive invocation of claim | The component currently owns the SPI semaphore | Attempt to invoke the SPI claim function which should return with error SPI_CLAIM_ALREADY_OWNER_ERR | Apply ClaimOK|
|`RWOwner::ERROR` | The component will be unable to read/write 8, 16, and 32 bits if it does not have ownership of the semaphore | The component currently does not own the SPI semaphore | Attempt to invoke the read/write8,16,32 functions which should return with error SPI_RW_NOT_OWNER_ERR|
|`RWOwner::SUCCESS8` | The component will successfully read/write an 8 bit SPI word when it has ownership of the SPI semaphore | The component currently owns the SPI semaphore | Invoke the read_write_8 function which should return without error | Apply ClaimOK|
|`RWOwner::SUCCESS16` | The component will successfully read/write a 16 bit SPI word when it has ownership of the SPI semaphore | The component currently owns the SPI semaphore | Invoke the read_write_16 function which should return without error | Apply ClaimOK|
|`RWOwner::SUCCESS32` | The component will successfully read/write a 32 bit SPI word when it has ownership of the SPI semaphore | The component currently owns the SPI semaphore | Invoke the read_write_32 function which should return without error | Apply ClaimOK|
|`RWReverse::SUCCESS8` | The component will successfully read/write an 8 bit SPI word (while reverse_mode is 0) when it has ownership of the SPI semaphore | The component currently owns the SPI semaphore | Invoke the read_write_8 function which should return without error | Apply ClaimOK|
|`RWReverse::SUCCESS16` | The component will successfully read/write a 16 bit SPI word (while reverse_mode is 0) when it has ownership of the SPI semaphore | The component currently owns the SPI semaphore | Invoke the read_write_16 function which should return without error | Apply ClaimOK|
|`RWReverse::SUCCESS32` | The component will successfully read/write a 32 bit SPI word (while reverse_mode is 0) when it has ownership of the SPI semaphore | The component currently owns the SPI semaphore | Invoke the read_write_32 function which should return without error | Apply ClaimOK|
|`Pointer::Invalid` | The component will correctly error when a null pointer is passed in to a read/write operation | The component currently owns the SPI semaphore | Attempt to invoke the read/write functions which should correctly ASSERT DEATH | Apply ClaimOK|
|`Reset::OK` | The component's SPI core should be reset | The precondition is always true | Do a read register partial and check that the MODE_EN is equal to 1. We can't check for a transition from 0 to 1 so we check that the mode is always enabled | N/A|
