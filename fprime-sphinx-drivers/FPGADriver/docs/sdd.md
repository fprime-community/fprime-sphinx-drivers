Drv::FPGADriver Component SDD
===

## 1. Introduction

`Drv::FPGADriver` is a passive F' component that provides an RTI signal at the system clock rate configured in VxWorks along with a 1 Hz RTI that can be used for time update.

## 2. Design

#### 2.1 Component Diagram

The `Drv::FPGADriver` component has the following component block description diagram (BDD) diagram:

![`Drv::FPGADriver` Diagram](img/FPGADriverBDD.jpg "Drv::FPGADriver")

#### 2.2 Ports

The `Drv::FPGADriver` component uses the following port types:

Port Data Type | Name | Direction | Kind | Usage
-------------- | ---- | --------- | ---- | -----
`Svc::Sched` | timeRTIOut | output | output | Send out an RTI signal at 1Hz intended to be used by Sphinx Time component for reading S/C time from Sphinx FPGA 
`Svc::Cycle` | cycleOut | output | output | Send out an RTI signal at each system clock interrupt intended to be used by the rate group driver component  
`Drv::SphinxRegRead` | read_reg | input | guarded_input | Guarded input port to read a 4-byte value from the user provided memory offset
`Drv::SphinxRegWrite` | write_reg | input | guarded_input | Guarded input port to write a 4-byte value to the user provided memory offset

### 2.3 Functional Description

This component uses VxWorks watchdog timer facility to execute an RTI handler function in system-clock interrupt context each system clock tick. The default system clock rate configured at initialization is set by SYS_CLK_RATE_HZ macro as defined in the Impl.hpp file. The RTI handler function sends out an output signal on the cycleOut port upon each execution and another signal on the timeRTIOut port at 1Hz interval.   

#### 2.3.1 read_reg Port

This is a guarded input port that can be used to read a 4-byte value from the user provided memory offset. It's intended use is to provide access to Sphinx registers.

#### 2.3.2 write_reg Port

This is a guarded input port that can be used to write a 4-byte value to the user provided memory offset. It's intended use is to provide access to Sphinx registers.

## 3. Rules-Based Tests

#### 3.1 Rules

The `Drv::FPGADriver` component has the following rules:

Rule | Description | Precondition | Action | Rule Order
-----|-------------|--------------|--------|-----------
`Time::OK` | The component successfully calls the rti handler and sphinx_time_go functions | Always true | Call sphinx_time_go and return without error. Call sphinx_time_rti_handler 10 times to trigger the timeRTIOUT port call | Apply OK
`Time::ERROR` | The component correctly errors when given an invalid argument | Always true | Passing an address of 0 to sphinx_time_rti_handler should ASSERT DEATH | Apply ERROR
`Read::OK` | The component successfully reads from a register | Always true | Write a value to a register, invoke read_reg, and check that it returns without error and reads the correct value | Apply OK
`Write::OK` | The component successfully writes to a register | Always true | Invoke write_reg and return without error. Do a readReg and make sure the value actually got written | Apply OK
