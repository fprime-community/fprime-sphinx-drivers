// ====================================================================== 
// \title  SphinxDrvIntUtil.hpp
// \author nserafin
// \brief  Convenience functions for dealing with the interrupt mask
//         register on the GR712RC.
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
// ====================================================================== 

#ifndef SPHINXDRVINTUTIL_HPP
#define SPHINXDRVINTUTIL_HPP

#include <fprime-sphinx-drivers/Util/SphinxDrvBitUtil.hpp>
#include <Fw/Types/BasicTypes.hpp>
#include <Fw/Types/Assert.hpp>

namespace Drv {

    /*
     * Constants
     */

    // Lowest-number interrupt on the system
    static const U8 lowInt = 1;
    // Highest-number interrupt on the system
    static const U8 highInt = 15;

    /*
     * Addresses
     */

    static const U32 interruptClearRegAddr = 0x8000020CU;

    static const U32 interruptMaskRegAddr[] = {
        0x80000240U,
        0x80000244U
    };

    /*
     * Enumerations
     */

    // Enumerate the processors
    enum Proc {
        PROC0 = 0,
        PROC1 = 1,
    };

    // Enumerate the IRQs
    enum Irq {
        IRQ1 = 1,
        IRQ2 = 2,
        IRQ3 = 3,
        IRQ4 = 4,
        IRQ5 = 5, 
        IRQ6 = 6,
        IRQ7 = 7,
        IRQ8 = 8,
        IRQ9 = 9,
        IRQ10 = 10,
        IRQ11 = 11,
        IQR12 = 12,
        IRQ13 = 13,
        IRQ14 = 14,
        IRQ15 = 15,
        IRQ16 = 16,
        IRQ17 = 17,
        IRQ18 = 18,
        IRQ19 = 19,
        IRQ20 = 20,
        IRQ21 = 21,
        IRQ22 = 22,
        IRQ23 = 23,
        IRQ24 = 24,
        IRQ25 = 25,
        IRQ26 = 26,
        IRQ27 = 27,
        IRQ28 = 28,
        IRQ29 = 29,
        IRQ30 = 30,
        IRQ31 = 31,
    };

    /*
     * Clear pending interrupts of the given type.
     *
     * Extended interrupts (IRQs > 15) cannot be cleared,
     * and there is no interrupt 0; this function will assert
     * if either of those are attempted.
     */
    inline void clearPendingInt(Irq irq)
    {
        FW_ASSERT((lowInt <= irq) && (irq <= highInt));
        setBitAtomic(interruptClearRegAddr, irq);
    }

    /*
     * Mask interrupts of the given type on the given processor.
     */
    inline void maskInt(Proc proc, Irq irq)
    {
        clearBitAtomic(interruptMaskRegAddr[proc], irq);
    }

    /*
     * Unmask interrupts of the given type on the given processor.
     */
    inline void unmaskInt(Proc proc, Irq irq)
    {
        setBitAtomic(interruptMaskRegAddr[proc], irq);
    }

}

#endif
