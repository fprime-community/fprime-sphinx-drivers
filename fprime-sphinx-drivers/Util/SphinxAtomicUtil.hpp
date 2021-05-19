#ifndef SPHINX_ATOMIC_UTIL_HPP
#define SPHINX_ATOMIC_UTIL_HPP

#include <Fw/Types/BasicTypes.hpp>

namespace Drv {
    class AtomicUtil {
        public:
            static I32 Add(I32* target, I32 val); //!< Atomically add value to location
            static I32 Subtract(I32* target, I32 val); //!< Atomically subtract value from location
            static U32 And(U32* target, U32 val); //!< Atomically bitwise AND value at location
            static U32 Or(U32* target, U32 val); //!< Atomically bitwise OR value at location
    };
}

#endif
