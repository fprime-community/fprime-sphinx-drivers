// ====================================================================== 
// \title  Random.hpp
// \author bocchino
// \brief  Random number generation
//
// \copyright
// Copyright (C) 2017 California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
// ====================================================================== 

#ifndef Test_Random_HPP
#define Test_Random_HPP

#include <limits.h>
#include <sys/time.h>

#include "Fw/Types/BasicTypes.hpp"

namespace Utils {

  namespace Random {

    enum {
      //! The maximum value of a random number
      MAX_VALUE = INT_MAX
    };

    namespace GetSeedValue {

      //! Get a seed value from the system time
      U32 fromTime(void);

    }

    //! Seed the random number generator
    void seed(
        const U32 value //!< The seed value
    );

    //! Return a random number in the given range.
    //! For example, Random::inRange(5, 3) returns a number
    //! between 5 and 7, inclusive.
    //! \return The number
    U32 inRange(
        const U32 startValue, //!< The start value of the range
        const U32 length //!< the length of the range, including the start and end values
    );

  }

}

#endif
