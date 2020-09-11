// File: GPTimerDriverPriv.hpp
// Author: Nathan Serafin (nathan.serafin@jpl.nasa.gov)
// Date: 2 July, 2018
//
// Private header file for GPTimerDriver.

#ifndef GPTIMERDRIVERPRIV_HPP
#define GPTIMERDRIVERPRIV_HPP

#include <Fw/Types/BasicTypes.hpp>

#include <fprime-sphinx-drivers/Util/SphinxDrvUtil.hpp>

namespace Drv
{
    namespace GPTimer
    {
        //
        // General Information
        //

        // Number of timers available on board
        const U8 NTIMERS = 4;

        //
        // Types
        //

        // Type to encapsulate prescaler addresses
        struct PrescalerAddr {
            POINTER_CAST cntRegAddr;
            POINTER_CAST rldRegAddr;
        };

        //
        // Addresses
        //

        const PrescalerAddr prescalerAddr = {
            0x80000300U, // cntRegAddr
            0x80000304U  // rldRegAddr
        };

        //
        // Defaults
        //

        // Counter register
        const U32 DFL_CNT_REG = 0U;
        // Reload register
        const U32 DFL_RLD_REG = 0U;
        // Control register
        const U32 DFL_CTL_REG = 0U;

        //
        // Masks
        //

        // Mask off only the valid control bits.
        const U32 CONTROL_BITS_MASK = 0x3F;
    }
}

#endif
