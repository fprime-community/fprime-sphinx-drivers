// ====================================================================== 
// \title  RandomStub.cpp
// \author arizvi
// \brief  Random number generation stub for compiling in unsupported OS
//
// \copyright
// Copyright (C) 2017 California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
// ====================================================================== 

#include <Fw/Types/BasicTypes.hpp>

namespace Utils {

  namespace Random {

    namespace GetSeedValue {

      U32 fromTime(void) {
        return 0;
      }

    }

    void seed(const U32 value) {
      return;
    }

    U32 inRange(
        const U32 startValue,
        const U32 length
    ) {
      return 0;
    }

  }

}
