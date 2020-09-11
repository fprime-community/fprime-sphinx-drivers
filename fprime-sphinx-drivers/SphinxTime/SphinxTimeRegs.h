// ======================================================================
// \title  SphinxTimeRegs.h
//  *  Created on: June 18, 2020
// *      Author: arizvi
// \brief  h file for register offsets used by SphinxTime
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
//
// ======================================================================

#ifndef SphinxTimeRegs_h
#define SphinxTimeRegs_h

/* PRE-SCALER register address and their values */
#define GR712_SCALER_CNT_REG        0x80000300
#define GR712_SCALER_CNT_VAL        0x27
#define GR712_SCALER_RLD_REG        0x80000304
#define GR712_SCALER_RLD_VAL        0x27

/* Latch pre-scaler register addresses and their values */
/* The values should match the regular pre-scaler, or the */
/* two sets of timers will be on different time scales */
#define GR712_LATCH_SCALER_CNT_REG 0x80100600
#define GR712_LATCH_SCALER_CNT_VAL 0x27
#define GR712_LATCH_SCALER_RLD_REG 0x80100604
#define GR712_LATCH_SCALER_RLD_VAL 0x27

/* Low part of timestamp register address and their values */
#define TSTMP_LO_CNT_REG        0x80100610
#define TSTMP_LO_CNT_VAL        0x0
#define TSTMP_LO_RLD_REG        0x80100614
#define TSTMP_LO_RLD_VAL        0xf423f     // 999,999 usecs
#define TSTMP_LO_CTRL_REG       0x80100618
#define TSTMP_LO_CTRL_VAL       0x7

/* High part of timestamp register address and their values */
#define TSTMP_HI_CNT_REG        0x80100620
#define TSTMP_HI_CNT_VAL        0x0
#define TSTMP_HI_RLD_REG        0x80100624
#define TSTMP_HI_RLD_VAL        0xffffffff  // chained with TSTMP_LO for second count
#define TSTMP_HI_CTRL_REG       0x80100628
#define TSTMP_HI_CTRL_VAL       0x27

/* Watchdog register address and their values */
#define WATCHDOG_CNT_REG        0x80000340
#define WATCHDOG_CNT_VAL        0x39386C4
#define WATCHDOG_RLD_REG        0x80000344
#define WATCHDOG_RLD_VAL        0x11E1A1D4   // 999,999 counts/sec * 300 secs (5 mins) = 299,999,700 counts in 5 mins.
#define WATCHDOG_CTRL_REG       0x80000348
#define WATCHDOG_CTRL_VAL       0xF
#define WATCHDOG_FW_REG         0x200D0014
#define WATCHDOG_FW_VAL         0x4E61686F

/* Sphinx FPGA Time Registers */
#define SPHINX_SC_TIME_LO            0x20010000
#define SPHINX_SC_TIME_HI            0x20010004
#define SPHINX_SC_TIME_CTRL          0x20010008
#define SPHINX_SC_TIME_LO_SET        0x20010010
#define SPHINX_SC_TIME_HI_SET        0x20010020

/* Sphinx Up-Time Registers */
#define SPHINX_UP_TIME_LO            0x201F0000
#define SPHINX_UP_TIME_HI            0x201F0004

#endif
