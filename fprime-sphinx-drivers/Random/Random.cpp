// ====================================================================== 
// \title  Random.cpp
// \author bocchino
// \brief  Random number generation
//
// \copyright
// Copyright (C) 2017 California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
// ====================================================================== 

#include <time.h>

#include "fprime-sphinx-drivers/Random/Random.hpp"

extern "C" {
#include "fprime-sphinx-drivers/Random/bsd_random.h"
}

namespace Utils {

  namespace Random {

    namespace GetSeedValue {

      U32 fromTime(void) {
        struct timeval tv;
        (void) gettimeofday(&tv, NULL);
        return tv.tv_usec;
      }

    }

    void seed(const U32 value) {
      bsd_srandom(value);
    }

    U32 inRange(
        const U32 startValue,
        const U32 length
    ) {
      const U32 randInt = bsd_random();
      const F64 ratio = static_cast<F64>(randInt) / MAX_VALUE;
      const F64 randFloat = ratio * length;
      const U32 offset = static_cast<U32>(randFloat);
      return startValue + offset;
    }

  }

}
