/*
 * VxWorks 6.7 on the sphinx ships with a compiler too old to support atomic builtins.
 * This implements atomic operations using the VxWorks atomic api.
 */
#include <fprime-sphinx-drivers/Util/SphinxAtomicUtil.hpp>

#include <Fw/Types/Assert.hpp>

#include <vxAtomicLib.h>

/*
 * VxWorks's atomic api takes an int type, but we want an api the expects
 * fixed sized integers so we can atomically manipulate registers.
 *
 * Since int is 32 bits on most platforms, this code assumes that atomic is 4
 * bytes. On the offchance that atomic isn't the expected size because of an
 * unsupported VxWorks 6.7 target, crash at compile time.
 */
FW_STATIC_ASSERT(sizeof(atomicVal_t) == sizeof(U32));

namespace Drv {
    I32 AtomicUtil::Add(I32* target, I32 val) {
        return (I32) vxAtomicAdd((atomic_t *)target, (atomicVal_t) val);
    }

    I32 AtomicUtil::Subtract(I32* target, I32 val) {
       return (I32) vxAtomicSub((atomic_t *)target, (atomicVal_t) val);
    }

    U32 AtomicUtil::And(U32* target, U32 val) {
        return (U32) vxAtomicAnd((atomic_t *)target, (atomicVal_t) val);
    }

    U32 AtomicUtil::Or(U32* target, U32 val) {
        return (U32) vxAtomicOr((atomic_t *)target, (atomicVal_t) val);
    }
}
