<title>Drv::SphinxTime Component SDD</title>
# Drv::SphinxTime Component

## 1. Introduction

`Drv::SphinxTime` is a passive F' component in the Drv namespace. Components needing time will communicate with this component. In this document, there are two instances of time: FPGA time and CPU time. FPGA time is absolute, and is the time reported by the SPHINX hardware. CPU time is relative (to boot-up), and is the time reported by the LEON3 processor.

## 2. Design

#### 2.1 Component Diagram

The `Drv::SphinxTime` component has the following component block description diagram (BDD) diagram:

![`Drv::SphinxTime` Diagram](img/SphinxTime_BDD.jpg "Drv::SphinxTime")

#### 2.2 Ports

The `Drv::SphinxTime` component uses the following port types:

Port Data Type | Name | Direction | Kind | Usage
-------------- | ---- | --------- | ---- | -----
`Drv::SphinxTimeVal` | TimeIn | input | sync_input | Command handler to set the Spacecraft and CPU time.
`Drv::SphinxRegWrite` | sphinxRegWrite_out | output | output | Write to the FPGA register.
[`Svc::Sched`](../../../Svc/Sched/docs/sdd.html) | schedIn | input | sync_input | Read out time value from Sphinx hardware and update stored CPU and FPGA Spacecraft Time values in FSW.
`Drv::SphinxRegRead` | sphinxRegRead_out | output | output | Read from the FPGA register.
`Fw::Time` | timeGetPort | input | sync_input | Returns the calculated on-board Spacecraft time.

### 2.3 Functional Description

#### 2.3.1 TimeIn
Command handler to set the FPGA and CPU time (To be implemented upon availability of non-volatile CD&H clock).

#### 2.3.2 sphinxRegWrite_out
This port is used to write a value at a particular FPGA register.

#### 2.3.3 schedIn
On every schedIn call, update the stored CPU time and the stored spacecraft time (To be implemented upon availability of non-volatile CD&H clock).

#### 2.3.4 sphinxRegRead_out
This port is used to read a value at a particular FPGA register.

#### 2.3.5 timeGetPort
This call will get the current CPU time and return the following timestamp: `timestamp = stored_spacecraft_time + (current_cpu_time - stored_cpu_time)`
