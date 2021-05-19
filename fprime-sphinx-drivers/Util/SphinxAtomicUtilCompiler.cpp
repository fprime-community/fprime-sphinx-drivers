/*
 * Use GCC/Clang compiler builtins for the atomic wrapper implementation
 */
#include <fprime-sphinx-drivers/Util/SphinxAtomicUtil.hpp>

namespace Drv {
    I32 AtomicUtil::Add(I32* target, I32 val) {
        return __sync_fetch_and_add(target, val);
    }

    I32 AtomicUtil::Subtract(I32* target, I32 val) {
        return __sync_fetch_and_sub(target, val);
    }

    U32 AtomicUtil::And(U32* target, U32 val) {
        return __sync_fetch_and_and(target, val);
    }

    U32 AtomicUtil::Or(U32* target, U32 val) {
        return __sync_fetch_and_or(target, val);
    }
}
