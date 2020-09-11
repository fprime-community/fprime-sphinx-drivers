Drv::FpgaGpioDriver Component
===

## 1. Introduction

`Drv::FpgaGpioDriver` is a passive F' component that provides application
level software interface to the Sphinx FPGA's GPIO interface.

## 2. Requirements

The requirements for `Drv::FpgaGpioDriver` are as follows:

| Requirement               | Description                                                                                                                                               | Verification Method |
| -----------               | -----------                                                                                                                                               | -------------------
| FPrime-SphinxFpgaGpio-001 | The `Drv::FpgaGpioDriver` component shall provide capability to toggle the Sphinx FPGA GPIO pins high or low                                              | Integration Test    |
| FPrime-SphinxFpgaGpio-002 | The `Drv::FpgaGpioDriver` component shall provide capability to set up the Sphinx FPGA GPIO pins as enabled or disabled at flight software initialization | Integration Test    |

## 3. Design

#### 3.1 Component Diagram

The `Drv::FpgaGpioDriver` component has the following component block description
diagram (BDD) diagram:

![`Drv::FpgaGpioDriver` Diagram](img/FpgaGpioDriverBDD.jpg "Drv::FpgaGpioDriver")

#### 3.2 Ports

The `Drv::FpgaGpioDriver` component uses the following port types:

| Port Data Type             | Name       | Direction | Kind          | Usage                                  |
|----------------------------|------------|-----------|---------------|----------------------------------------|
| `Drv::SphinxGPIO_ReadPin`  | readPin    | input     | guarded_input | Read the signal from the specified pin |
| `Drv::SphinxGPIO_WritePin` | setPin     | input     | guarded_input | Sets the specified pin to high         |
| `Drv::SphinxGPIO_WritePin` | clearPin   | input     | guarded_input | Sets the specified pin to low          |
| `Drv::SphinxGPIO_WritePin` | enablePin  | input     | guarded_input | Turns on the specified output pin      |
| `Drv::SphinxGPIO_WritePin` | disablePin | input     | guarded_input | Turns off the specified output pin     |

### 3.3 Functional Description

#### 3.3.1 readPin Port

Translates the specified pin number into the proper FPGA GPIO address, reads a
single bit, and returns it. If the pin is disabled, the value read will always
be 0.

#### 3.3.2 setPin Port

Sets the signal of the specified FPGA GPIO pin to on (1). If the pin is not
enabled, this operation will do nothing. The port always returns a status of 0.

#### 3.3.3 clearPin Port

Clears the signal of the specified FPGA GPIO pin to off (0).  If the pin is not
enabled, this operation will do nothing. The port always returns a status of 0.

#### 3.3.4 enablePin Port

Sets the enable signal for the specified FPGA GPIO pin. This allows the pin to
be set or cleared.

#### 3.3.5 disablePin Port

Clears the enable signal for the specified FPGA GPIO pin. This clears the pin's
value to off (0), and prevents setting or clearing until it is re-enabled.
