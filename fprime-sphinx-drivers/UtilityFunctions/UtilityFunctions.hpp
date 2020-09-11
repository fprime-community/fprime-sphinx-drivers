// ======================================================================
// \title  UtilityFunctions.hpp
// \author mstarch
// \brief  hpp file for Util functions
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
// ======================================================================

#ifndef UTILS_UTIL_FUNCTIONS_HPP
#define UTILS_UTIL_FUNCTIONS_HPP
#include <Fw/Types/BasicTypes.hpp>
#include <Fw/Types/Assert.hpp>
namespace Utils {

/**
 * Reads a 64-bit monotonically increasing counter, atomically, from its two constituent locations.
 * It does this by checking for roll-over from the bottom-location to the top location, and re-reading
 * the bottom location in case of roll-over.
 *
 * Note: this is most commonly used to read time-values consistently.
 *
 * \param volatile U32* top_loc: location of the upper 32bits (least frequently varying) of the 64bits
 * \param volatile U32* bottom_loc: location of the lower 23bits (most frequently varying) of the 64bits
 * \param U32& top_val: (output) location to store upper 32 bits of the read value
 * \param U32& bottom_val: (output) location to store lower 32 bits of the read value
 */
inline void read_U64_counter(volatile U32* top_loc, volatile U32* bottom_loc, U32& top_val, U32& bottom_val) {
    U32 prev_top;
    FW_ASSERT(bottom_loc != NULL);
    FW_ASSERT(top_loc != NULL);
    //Initial read of both
    prev_top = *top_loc;
    bottom_val = *bottom_loc;
    // Read current secs again
    top_val = *top_loc;
    //Check for roll-over, if so reread usecs
    if (top_val != prev_top) {
        bottom_val = *bottom_loc;
    }
}

};

#endif /* UTILS_UTIL_FUNCTIONS_HPP */
