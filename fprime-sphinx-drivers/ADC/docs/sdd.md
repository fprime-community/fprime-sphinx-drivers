# Drv::ADC Component

## 1. Introduction

`Drv::ADC` is an active F' component that interfaces with the Sphinx's on-chip ADC through register reads and writes. The ADC has a control register, a status register, and multiple telemetry channels. Telemetry channels, and control/status registers are accessed as 32-bit registers at an offset from the ADC's chip base-address, but the number of bits with valid data and with writable data is variable.

### 1.1 ADC Software Interface
Offset   | Size(bits) | Access | Name | Description |
---------|----|---|------------|------------------|
`0x0000` | 4  | W | a2d_ctrl   | Control register |
`0x0004` | 3  | R | a2d_stat   | Status register  |
`0x0100` | 12 | R | 0_a2d_tlm0 | Input 0 result   |
`0x0104` | 12 | R | 0_a2d_tlm1 | Input 1 result   |
`0x0108` | 12 | R | 0_a2d_tlm2 | Input 2 result   |
`0x010C` | 12 | R | 0_a2d_tlm3 | Input 3 result   |
`0x0110` | 12 | R | 0_a2d_tlm4 | Input 4 result   |
`0x0114` | 12 | R | 0_a2d_tlm5 | Input 5 result   |
`0x0118` | 12 | R | 0_a2d_tlm6 | Input 6 result   |
`0x011C` | 12 | R | 0_a2d_tlm7 | Input 7 result   |


## 2. Requirements

The requirements for `Drv::ADC` are as follows:

Requirement | Description | Verification Method |
----------- | ----------- | -------------------
FPrime-SphinxADC-001 | The `Drv::ADC` component shall read telemetry from the ADC through register offsets | Inspection |
FPrime-SphinxADC-002 | The `Drv::ADC` component shall report telemetry | Unit Test |


## 3. Design

#### 3.1 Component Diagram

The `Drv::ADC` component has the following component block description diagram (BDD) diagram:

![`Drv::ADC` Diagram](img/ADC_BDD.jpg "Drv::ADC")

#### 3.2 Ports

The `Drv::ADC` component uses the following ports:

| Port Data Type                     | Name          | Direction | Kind          | Usage                                                    |
|------------------------------------|---------------|-----------|---------------|----------------------------------------------------------|
| `Fw::Apid`                         | adcOut        | output    | output        | Send out adc telemetry via APID.                         |

It also has the following role ports:

| Port Data Type                                        | Name           | Direction | Role            |
|-------------------------------------------------------|----------------|-----------|-----------------|
| [`Fw::Cmd`](../../../../Fw/Cmd/docs/sdd.md)           | cmdIn          | input     | Cmd             |
| [`Fw::CmdReg`](../../../../Fw/Cmd/docs/sdd.md)        | cmdReg         | output    | CmdRegistration |
| [`Fw::CmdResponse`](..././../../Fw/Cmd/docs/sdd.md)   | cmdResponseOut | output    | CmdResponse     |
| [`Fw::Log`](../../../../Fw/Log/docs/sdd.md)           | eventOut       | output    | Log             |
| [`Svc::Sched`](../../../../Svc/Sched/docs/sdd.md)     | schedIn        | input     | Sched           |
| [`Svc::TlmChan`](../../../../Svc/TlmChan/docs/sdd.md) | tlmOut         | output    | Telemetry       |
| [`Fw::Time`](../../../../Fw/Time/docs/sdd.md)         | timeCaller     | output    | Time            |

### 3.3 Functional Description

#### 3.3.1 schedIn

1. Check if the tlm_ready bit has been unset for some time (timeout period). If the bit hasn't been set by CDH during the timeout period then reset the timer and send out an EVR. Unset the tlm_ack bit as a safety measure -- the tlm_ready bit cannot be set while the tlm_ack is set.
2. If tlm_ready bit is set, then do the following
    3. Read the telemetry values for tlm0, tlm1, ..., tlm7, and a2d_stat; and packetize them into an ADC Packet.
    4. Send out ADC Packet with telemetry values for tlm0, tlm1, ..., tlm7, and a2d_stat.
    5. Set the telemetry acknowledgement bit.
    6. Unset the telemetry acknowledgement bit.
