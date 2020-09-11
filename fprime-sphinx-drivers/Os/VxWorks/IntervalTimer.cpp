#include <Os/IntervalTimer.hpp>
#include <Fw/Types/Assert.hpp>
#include <fprime-sphinx-drivers/UtilityFunctions/UtilityFunctions.hpp>
extern "C" {
  #include <fprime-sphinx-drivers/SphinxTime/SphinxTimeRegs.h>
  #include <string.h>
}

//Note: These functions are called at least 20 times a second, possibly more
//      and when profiled, these functions take up the most time of any
//      non-idle processing. Thus performance is crucial, and the functions
//      have been optimized for GR712 processing.
//
//      --mstarch

namespace Os {

    U32 IntervalTimer::getDiffUsec(const RawTime& t1, const RawTime& t2) {
        RawTime diff;
        if (t2.lower > t1.lower) {
            diff.lower = 0xFFFFFFFF - (t2.lower - t1.lower - 1);
            diff.upper = t1.upper - t2.upper - 1;
        } else {
            const U64 al = (((U64) t1.upper << 32) + (U64) t1.lower);
            const U64 bl = (((U64) t2.upper << 32) + (U64) t2.lower);
            diff.lower = (U32) (al - bl);
            diff.upper = (U32) ((U64)(al - bl) >> 32);
        }
        return ((diff.upper * 1000000) + (diff.lower));
    }

    void IntervalTimer::getRawTime(RawTime& time) {
        U32 secs;
        U32 usecs;
        //Use standard atomic counter read
        Utils::read_U64_counter(
            reinterpret_cast<volatile U32*>(TSTMP_HI_CNT_REG),
            reinterpret_cast<volatile U32*>(TSTMP_LO_CNT_REG),
            secs,
            usecs
        );
        //GR712 uses down counter, so rectify the values
        usecs = TSTMP_LO_RLD_VAL - usecs;
        secs = TSTMP_HI_RLD_VAL - secs;

        //Interval timer expects a contiguous 64bit value in terms of system ticks
        U64 tmp = (U64) usecs + ((U64)secs * (U64)1000000ll);
        time.upper = tmp >> 32;
        time.lower = (U32)tmp;
    }
}
