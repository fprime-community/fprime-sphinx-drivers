Drv::GPIODriver Component SDD
===

## 1. Introduction

`Drv::GPIODriver` is a passive F' component that provides application level
software interface to the GR712 on-chip GPIO interface managing 2 sets of 32 on-chip GPIOs for a total of 64 GPIO pins.

## 2. Design

#### 2.1 Component Diagram

The `Drv::GPIODriver` component has the following component block description
diagram (BDD) diagram:

![`Drv::GPIODriver` Diagram](img/GPIODriverBDD.jpg "Drv::GPIODriver")

#### 2.2 Ports

The `Drv::GPIODriver` component uses the following port types:

| Port Data Type             | Name          | Direction | Kind          | Usage                                        |
|----------------------------|---------------|-----------|---------------|----------------------------------------------|
| `Drv::SphinxGPIO_ReadPin`  | gpio_readPin  | input     | guarded_input | Read the signal from the specified input pin |
| `Drv::SphinxGPIO_WritePin` | gpio_setPin   | input     | guarded_input | Turns on the specified output pin            |
| `Drv::SphinxGPIO_WritePin` | gpio_clearPin | input     | guarded_input | Turns off the specified output pin           |

### 2.3 Functional Description

This component configures a set of GPIO pins passed in from the constructor at initialization for: -
- Direction (0 = input, 1 = output)
- Interrupt mask (0 = masked, 1 = enabled) (NOTE: interrupts can only be configured as inputs)
- Interrupt polarity (0 = low/falling, 1 = high/rising)
- Interrupt edge (0 = level, 1 = edge) 

#### 2.3.1 gpio_readPin Port

Generic use port. Translates the specified pin number into the proper GPIO
address, reads a single bit indicating the GPIO pin status and returns the value (0 = low, 1 = high). If the pin is configured as an input then the value is read from the data register; however, if the pin is configured as an output then the value is read from the output register.

#### 2.3.2 gpio_setPin Port

Generic use port. Sets the signal of the specified GPIO pin to on (1). If the
pin is not an output pin, this operation will do nothing. The port always
returns a status of 0.

#### 2.3.3 gpio_clearPin Port

Generic use port. Clears the signal of the specified GPIO pin to off (0). If
the pin is not an output pin, this operation will do nothing. The port always
returns a status of 0.

## 3. Rules-Based Tests

#### 3.1 Rules

The `Drv::GPIODriver` component has the following rules:

Rule | Description | Precondition | Action | Rule Order
-----|-------------|--------------|--------|-----------
`ReadWrite::DIRIN` | The component sets the direction of GPIO pins in both banks to 0 (input) | Always true | Clear the bits associated with the GPIO_DIR_OFFSET for both GPIO banks | Apply DIRIN
`ReadWrite::DIROUT` | The component sets the direction of GPIO pins in both banks to 1 (output) | Always true | Set the bits associated with the GPIO_DIR_OFFSET for both GPIO banks | Apply DIROUT
`ReadWrite::READIN` | The component reads from the data register since the GPIO pin is configured as an input | The GPIO pin is an input | Invoke the read GPIO function and assert that the value matches the bit that is read from the GPIO_DATA register | Apply DIRIN, Apply READIN
`ReadWrite::READOUT` | The component reads from the output register since the GPIO pin is configured as an output | The GPIO pin is an output | Invoke the read GPIO function and assert that the value matches the bit that is read from the GPIO_OUT register | Apply DIROUT, Apply READOUT
`ReadWrite::SETOUT` | The component sets the GPIO pin to 1 | The GPIO pin is an output | Invoke the set GPIO function and assert that the bit that is read from the GPIO_OUT register is 1 | Apply DIROUT, Apply SETOUT
`ReadWrite::CLEAROUT` | The component clears the GPIO pin to 0 | The GPIO pin is an output | Invoke the clear GPIO function and assert that the bit that is read from the GPIO_OUT register is 0 | Apply DIROUT, Apply CLEAROUT
`ReadWrite::ERROR` | Invoke the read, set, and clear, functions with an invalid pin number | Always true | ASSERT_DEATH when attempting to read, set, and clear with an invalid pin number | Apply ERROR
`Init::OK` | Initialize the GPIODriver component and check that the bits are set correctly | Always true | Call the component's initialization function and check that the pin number, direction, interrupt, polarity, and edge are set correctly | Apply OK
`Init::ERROR` | Initialize the GPIODriver component with invalid values and correctly error | Always true | ASSERT_DEATH when attempting to initialize with invalid values | Apply ERROR
`Interrupt::OK` | Call GPIO interrupt handler 11 for UART6 | Always true | Call the dummy HandleGPIOInterrupt() function in the GPIODriverInterrupt class that writes 0xDEADBEEF to 0x10020000 and asserts that the correct bits were written | Apply OK
