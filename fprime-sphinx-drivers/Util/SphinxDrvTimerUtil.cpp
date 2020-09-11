// File: SphinxDrvTimerUtil.cpp
// Author: Nathan Serafin (nathan.serafin@jpl.nasa.gov)
// Date: 10 July, 2018
//
// Implementation of utilities for working with timers on the
// GR712RC.

#include <fprime-sphinx-drivers/Util/SphinxDrvIntUtil.hpp>

//
// Constants needed only for this file
//

static const U32 CTL_REG_EN_OFFSET = 0U;
static const U32 CTL_REG_RS_OFFSET = 1U;
static const U32 CTL_REG_LD_OFFSET = 2U;
static const U32 CTL_REG_IE_OFFSET = 3U;
static const U32 CTL_REG_IP_OFFSET = 4U;
static const U32 CTL_REG_CH_OFFSET = 5U;
static const U32 CTL_REG_DH_OFFSET = 6U;

namespace Drv
{
    namespace GPTimer
    {
        // Sort out which flag to set or clear, and set or clear it.
        static void handleFlag(CtlReg& ctlReg, CtlFlagAct act)
        {
            switch (act) {
                case EN_SET:
                    setBitInWord(ctlReg, CTL_REG_EN_OFFSET);
                    break;
                case EN_CLEAR:
                    clearBitInWord(ctlReg, CTL_REG_EN_OFFSET);
                    break;
                case RS_SET:
                    setBitInWord(ctlReg, CTL_REG_RS_OFFSET);
                    break;
                case RS_CLEAR:
                    clearBitInWord(ctlReg, CTL_REG_RS_OFFSET);
                    break;
                case LD_SET:
                    setBitInWord(ctlReg, CTL_REG_LD_OFFSET);
                    break;
                case LD_CLEAR:
                    clearBitInWord(ctlReg, CTL_REG_LD_OFFSET);
                    break;
                case IE_SET:
                    setBitInWord(ctlReg, CTL_REG_IE_OFFSET);
                    break;
                case IE_CLEAR:
                    clearBitInWord(ctlReg, CTL_REG_IE_OFFSET);
                    break;
                case IP_SET:
                    setBitInWord(ctlReg, CTL_REG_IP_OFFSET);
                    break;
                case IP_CLEAR:
                    clearBitInWord(ctlReg, CTL_REG_IP_OFFSET);
                    break;
                case CH_SET:
                    setBitInWord(ctlReg, CTL_REG_CH_OFFSET);
                    break;
                case CH_CLEAR:
                    clearBitInWord(ctlReg, CTL_REG_CH_OFFSET);
                    break;
                case DH_SET:
                    setBitInWord(ctlReg, CTL_REG_DH_OFFSET);
                    break;
                case DH_CLEAR:
                    clearBitInWord(ctlReg, CTL_REG_DH_OFFSET);
                    break;
                default:
                    FW_ASSERT(false);
                    break;
            }
        }

        void ctlRegBuild(CtlReg& ctlReg,
                         CtlFlagAct act1)
        {
            handleFlag(ctlReg, act1);
        }
        void ctlRegBuild(CtlReg& ctlReg,
                         CtlFlagAct act1, CtlFlagAct act2)
        {
            handleFlag(ctlReg, act1);
            handleFlag(ctlReg, act2);
        }
        void ctlRegBuild(CtlReg& ctlReg,
                         CtlFlagAct act1, CtlFlagAct act2, CtlFlagAct act3)
        {
            handleFlag(ctlReg, act1);
            handleFlag(ctlReg, act2);
            handleFlag(ctlReg, act3);
        }
        void ctlRegBuild(CtlReg& ctlReg,
                         CtlFlagAct act1, CtlFlagAct act2, CtlFlagAct act3,
                         CtlFlagAct act4)
        {
            handleFlag(ctlReg, act1);
            handleFlag(ctlReg, act2);
            handleFlag(ctlReg, act3);
            handleFlag(ctlReg, act4);
        }
        void ctlRegBuild(CtlReg& ctlReg,
                         CtlFlagAct act1, CtlFlagAct act2, CtlFlagAct act3,
                         CtlFlagAct act4, CtlFlagAct act5)
        {
            handleFlag(ctlReg, act1);
            handleFlag(ctlReg, act2);
            handleFlag(ctlReg, act3);
            handleFlag(ctlReg, act4);
            handleFlag(ctlReg, act5);
        }
        void ctlRegBuild(CtlReg& ctlReg,
                         CtlFlagAct act1, CtlFlagAct act2, CtlFlagAct act3,
                         CtlFlagAct act4, CtlFlagAct act5, CtlFlagAct act6)
        {
            handleFlag(ctlReg, act1);
            handleFlag(ctlReg, act2);
            handleFlag(ctlReg, act3);
            handleFlag(ctlReg, act4);
            handleFlag(ctlReg, act5);
            handleFlag(ctlReg, act6);
        }
        void ctlRegBuild(CtlReg& ctlReg,
                         CtlFlagAct act1, CtlFlagAct act2, CtlFlagAct act3,
                         CtlFlagAct act4, CtlFlagAct act5, CtlFlagAct act6,
                         CtlFlagAct act7)
        {
            handleFlag(ctlReg, act1);
            handleFlag(ctlReg, act2);
            handleFlag(ctlReg, act3);
            handleFlag(ctlReg, act4);
            handleFlag(ctlReg, act5);
            handleFlag(ctlReg, act6);
            handleFlag(ctlReg, act7);
        }

        bool ctlRegTest(U32 ctlReg, CtlFlag flag)
        {
            U32 mask = static_cast<U32>(1U) << static_cast<U32>(flag);

            return (ctlReg & mask);
        }
    }
}
