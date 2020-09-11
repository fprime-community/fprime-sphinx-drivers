// File: SphinxDrvTimerUtil.hpp
// Author: Nathan Serafin (nathan.serafin@jpl.nasa.gov)
// Date: 2 July, 2018
//
// Utilities and declarations for working with timers
// on the GR712RC.

#ifndef SPHINXDRVTIMERUTIL_HPP
#define SPHINXDRVTIMERUTIL_HPP

#include <Fw/Types/BasicTypes.hpp>

namespace Drv
{
    namespace GPTimer
    {

        // Type to encapsulate timer addresses
        struct TimerAddr {
            POINTER_CAST cntRegAddr;
            POINTER_CAST rldRegAddr;
            POINTER_CAST ctlRegAddr;
        };

        // Timer addresses
        const TimerAddr timerAddr[] = {
            // Timer 1
            {
                0x80000310U, // cntRegAddr
                0x80000314U, // rldRegAddr
                0x80000318U  // ctlRegAddr
            },
            // Timer 2
            {
                0x80000320U, // cntRegAddr
                0x80000324U, // rldRegAddr
                0x80000328U  // ctlRegAddr
            },
            // Timer 3
            {
                0x80000330U, // cntRegAddr
                0x80000334U, // rldRegAddr
                0x80000338U  // ctlRegAddr
            },
            // Timer 4
            {
                0x80000340U, // cntRegAddr
                0x80000344U, // rldRegAddr
                0x80000348U  // ctlRegAddr
            }
        };

        // Representation of timers and errors
        enum Code {
            // Errors
            NOT_AVAILABLE = -1,

            // Timers
            TIMER1 = 0,
            TIMER2 = 1,
            TIMER3 = 2,
            TIMER4 = 3,
            TIMER_ANY = 4,
        };

        //
        // Control register helper functions.
        //

        // Type to represent control register offsets
        enum CtlFlag {
            EN,
            RS,
            LD,
            IE,
            IP,
            CH,
            DH,
        };

        // Type to represent a control register.
        //
        // For an integral type, the default constructor is not implicitly
        // called, so empty CtlRegs should be defined as CtlReg c {};
        typedef U32 CtlReg;

        // Actions to take on control register flags
        enum CtlFlagAct {
            EN_SET,
            EN_CLEAR,
            RS_SET,
            RS_CLEAR,
            LD_SET,
            LD_CLEAR,
            IE_SET,
            IE_CLEAR,
            IP_SET,
            IP_CLEAR,
            CH_SET,
            CH_CLEAR,
            DH_SET,
            DH_CLEAR,
        };

        // Build a control register
        //
        // ctlReg represents the contents of the control register
        // before manipulation: it may either be blank, or may
        // contain a prior version of the control register. Each
        // flag argument indicates whether to set or clear the
        // corresponding flag.
        //
        // Anything from only one to all seven flags can be changed:
        // the order in which the flags are specified does not matter.
        //
        void ctlRegBuild(CtlReg& ctlReg,
                         CtlFlagAct act1);
        void ctlRegBuild(CtlReg& ctlReg,
                         CtlFlagAct act1, CtlFlagAct act2);
        void ctlRegBuild(CtlReg& ctlReg,
                         CtlFlagAct act1, CtlFlagAct act2, CtlFlagAct act3);
        void ctlRegBuild(CtlReg& ctlReg,
                         CtlFlagAct act1, CtlFlagAct act2, CtlFlagAct act3,
                         CtlFlagAct act4);
        void ctlRegBuild(CtlReg& ctlReg,
                         CtlFlagAct act1, CtlFlagAct act2, CtlFlagAct act3,
                         CtlFlagAct act4, CtlFlagAct act5);
        void ctlRegBuild(CtlReg& ctlReg,
                         CtlFlagAct act1, CtlFlagAct act2, CtlFlagAct act3,
                         CtlFlagAct act4, CtlFlagAct act5, CtlFlagAct act6);
        void ctlRegBuild(CtlReg& ctlReg,
                         CtlFlagAct act1, CtlFlagAct act2, CtlFlagAct act3,
                         CtlFlagAct act4, CtlFlagAct act5, CtlFlagAct act6,
                         CtlFlagAct act7);

        // Return true if the given flag is set; false otherwise
        bool ctlRegTest(CtlReg ctlReg, CtlFlag flag);
    }
}

#endif
