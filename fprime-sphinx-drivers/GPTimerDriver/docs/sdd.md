Drv::GPTimerDriver Component SDD
===

## 1. Introduction

`Drv::GPTimerDriver` is a passive F' component that provides application-level
clients with dynamic access to some or all of the on-chip general-purpose
timers on the GR712RC.

## 2. Requirements

1. The driver shall allow, at construction time, configuration of all timers and the prescaler.
2. The driver shall allow, at construction time, for timers to be permanently reserved.
2. The driver shall allow clients to claim and unclaim non-reserved timers.
3. The driver shall provide access for the claiming client to the corresponding reload value register.
4. The driver shall provide access for the claiming client to the corresponding counter value register.
5. The driver shall provide access for the claiming client to the corresponding control register.

## 3. Design

### 3.1 Component Diagram

The `Drv::GPTimerDriver` component has the following component block
description diagram (BDD):

![`Drv::GPTimerDriver` Diagram](./img/GPTimerDriverBDD.jpg "Drv::GPTimerDriver")

### 3.2 Ports

The `Drv::GPTimerDriver` component uses the following port types:

| Port Data Type                    | Name                       | Direction | Kind          | Usage                                         |
|-----------------------------------|----------------------------|-----------|---------------|-----------------------------------------------|
| `Drv::GPTimerDriver_Claim`        | gPTimerDriver_Claim        | input     | guarded_input | Attempt to claim a timer                      |
| `Drv::GPTimerDriver_Unclaim`      | gPTimerDriver_Unclaim      | input     | guarded_input | Unclaim a timer                               |
| `Drv::GPTimerDriver_ReadCounter`  | gPTimerDriver_ReadCounter  | input     | sync_input    | Read the counter register of a claimed timer  |
| `Drv::GPTimerDriver_WriteCounter` | gPTimerDriver_WriteCounter | input     | guarded_input | Write the counter register of a claimed timer |
| `Drv::GPTimerDriver_ReadReload`   | gPTimerDriver_ReadReload   | input     | sync_input    | Read the reload register of a claimed timer   |
| `Drv::GPTimerDriver_WriteReload`  | gPTimerDriver_WriteReload  | input     | guarded_input | Write the reload register of a claimed timer  |
| `Drv::GPTimerDriver_ReadControl`  | gPTimerDriver_ReadControl  | input     | sync_input    | Read the control register of a claimed timer  |
| `Drv::GPTimerDriver_WriteControl` | gPTimerDriver_WriteControl | input     | guarded_input | Write the control register of a claimed timer |

### 3.3 Functional Description

#### 3.3.1 Usage Notes

Passive components can own timers, but they cannot have more than one client.
If a passive component is to have multiple clients, it must have its timer
statically assigned to it, and manage the timer itself.

#### 3.3.2 Constructor

The constructor requires configuration of the prescaler, and allows configuration
of each of the timers. Once the constructor has completed, the prescaler is fixed.
For each timer, the following arguments must be provided:

| Argument    | Meaning                                                                                    |
|-------------|--------------------------------------------------------------------------------------------|
| reserved    | If true, the timer is not owned by GPTimerDriver, but is reserved for some other component |
| usrConfig   | If false, the register parameters are ignored, and the timer is configured with defaults   |
| cntReg      | Value to load into the counter register                                                    |
| rldReg      | Value to load into the reload register                                                     |
| cfgReg      | Value to load into the configuration register                                              |

The default configuration for a timer is:

| Flag | Value |
|------|-------|
| CH   | 0     |
| IP   | 0     |
| IE   | 0     |
| LD   | 0     |
| RS   | 0     |
| EN   | 0     |

This should result in a timer that does nothing.

#### 3.3.3 Destructor

The destructor de-configures all non-reserved timers back to the default state.

The destructor will assert if a non-reserved timer is also not free.

#### 3.3.3 gPTimerDriver_Claim Port

This port allows clients to attempt to claim a timer, either by specifying a
particular timer, or by asking for any free timer. In either case, a
representation of the timer that was granted, or a negative error code, will be
returned. Requests for reserved timers will be denied. This return code will be
of type `Drv::GPTimer::Code`, and if it is not an error code, it must be provided
in all future port calls.

Port calls will assert if the request is not for a recognized timer (i.e. a
value that is not a non-error-code member of `Drv::GPTimer::Code`).

#### 3.3.4 gPTimerDriver_Unclaim Port

This port allows clients to unclaim timers that they previously claimed. The
return value of a prior call to gPTimerDriver_Claim should be provided.

If a critical component relies on the availability of a timer, it must
acquire that timer during system initialization, and must never
release it. Once a timer has been released, there is no limit on how
long of a wait there is before a new timer can be acquired.

Port calls will assert if the timer to be unclaimed is not owned by the
requesting client, or if the specified timer is not valid.

#### 3.3.5 gPTimerDriver_ReadCounter Port

This port allows clients to read the counter register of timers that they have
claimed. The return value of a prior call to gPTimerDriver_Claim should be
provided.

Port calls will assert if the specified timer is not owned by the requesting
client, or if the specified timer is not valid.

#### 3.3.6 gPTimerDriver_WriteCounter Port

This port allows clients to write the counter register of timers that they have
claimed. The return value of a prior call to gPTimerDriver_Claim should be
provided.

Port calls will assert if the specified timer is not owned by the requesting
client, or if the specified timer is not valid.

#### 3.3.7 gPTimerDriver_ReadReload Port

This port allows clients to read the reload register of timers that they have
claimed. The return value of a prior call to gPTimerDriver_Claim should be
provided.

Port calls will assert if the specified timer is not owned by the requesting
client, or if the specified timer is not valid.

#### 3.3.8 gPTimerDriver_WriteReload Port

This port allows clients to write the reload register of timers that they have
claimed. The return value of a prior call to gPTimerDriver_Claim should be
provided.

Port calls will assert if the specified timer is not owned by the requesting
client, or if the specified timer is not valid.

#### 3.3.9 gPTimerDriver_ReadControl Port

This port allows clients to read the control register of timers that they have
claimed.

Port calls will assert if the specified timer is not owned by the requesting
client, or if the specified timer is not valid.

#### 3.3.10 gPTimerDriver_WriteControl Port

This port allows clients to write the control register of timers that they have
claimed.

Port calls will assert if the specified timer is not owned by the requesting
client, or if the specified timer is not valid.

## 4. Rules-Based Tests

#### 4.1 Rules

The `Drv::GPTimerDriver` component has the following rules:

Rule | Description | Precondition | Action | Rule Order
-----|-------------|--------------|--------|-----------
`Owner::ClaimOK` | The component successfully claims all four timers | All timers are unclaimed | Invoke the claim with TIMER_ANY to claim the first available timer and then invoke the claim with the remaining three timers. The freeTimers array should be false for all four values. | Apply ClaimOK
`Owner::ClaimERROR` | The component attempts to claim timers that have already been claimed. The component also attempts to claim a timer with an invalid timer number | All timers are already claimed | Invoking a claim on all four timers results in a NOT_AVAILABLE status error. Invoking claim with an invalid timer number of 5 is caught by an ASSERT_DEATH | Apply ClaimOK, Apply ClaimERROR
`Owner::UnclaimOK` | The component successfully unclaims all four timers | All timers are claimed | Invoke the unclaim for all four timers. The freeTimers array should be true for all four values. | Apply ClaimOK, Apply UnclaimOK
`Owner::UnclaimERROR` | The component attempts to unclaim a timer with an invalid timer number | Always true | Invoking an unclaim with an invalid timer number of 5 is caught by an ASSERT_DEATH | Apply ClaimOK, Apply UnclaimERROR
`Read::OK` | The component successfully reads the control, counter, and reload values | All timers are claimed | Write values to the registers for Control, Counter, and Reload and make sure they equal the values returned from invoking the component's read functions. | Apply ClaimOK, Apply ReadOK
`Read::ERROR` | The component attempts to read the control, counter, and reload values with an invalid timer number | Always true | Invocation of the read function for control, counter, and reload ASSERTs DEATH | Apply ReadERROR
`Write::OK` | The component successfully writes the control, counter, and reload values | All timers are claimed | Invoke the write functions for control, counter, and reload and check that the value read from the registers matches what was written | Apply ClaimOK, Apply WriteOK
`Write::ERROR` | The component attempts to write the control, counter, and reload values with an invalid timer number | Always true | Invocation of the write function for control, counter, and reload	ASSERTs DEATH | Apply WriteERROR
