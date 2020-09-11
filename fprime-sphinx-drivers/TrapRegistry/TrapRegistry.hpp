// ======================================================================
// \title  TrapRegistry.hpp
// \author mstarch
// \brief  header file for Sparc V8 custom trap handles
//
// \copyright
// Copyright 2009-2018, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
// ======================================================================

#include <Fw/Types/BasicTypes.hpp>
#include <Fw/Trap/TrapHandler.hpp>

#ifndef DRV_SPHINX_TRAP_REGISTRY_HPP
#define DRV_SPHINX_TRAP_REGISTRY_HPP

#define TRAP_REGISTRY_COUNT 256
#define TRAP_BASE_REGISTER 0x9040000C

namespace Drv {
    /**
     *  TrapRegistry:
     *    The trap registry class allows FSW to capture and handle Sparc V8 style
     *  traps enabling FSW-level error handling for overridden trap ids. It does so
     *  by registering a generic handler in assembly, which passes control to a C
     *  function. The C function checks for a globally established Singleton of
     *  the C++ registry. If said singleton is non-NULL, the trap registry table
     *  is searched for an entry pertaining to that trap. If the trap's entry is
     *  non-NULL, that entry's doTrap method is executed.
     *
     *  Sparc V8 traps are held in a trap table defining 4-word (4 instruction)
     *  entries. This gives the implementor 4 instructions to get to a "real"
     *  trap handle.  The TrapRegistry overwrites the exiting 4 instructions
     *  with the following, which allows specific trap overrides without breaking
     *  needed built-in trap handling. Overwriting instructions:
     *       1: brach always to "handler" (aborting next instruction)
     *       2-4: unimplmented
     *
     *  Thus the full process is as follows:
     *      1. Trap occurs
     *      2. If trap registered, branch to "handler" (else use existing handler)
     *      3. "handler" gives control to C-based "trap_handle" while preventing
     *         handling of reentrant trap calls. (see trap.S)
     *      4. "trap_handle" looks up global Singleton TrapRegistry
     *      5. If singleton exists (not-NULL) and singleton handler entry for trap
     *         exists (non-NULL), runs registered object's "doTrap" method.
     *      6. When control returns to "handler", the trap response is ended
     *
     *
     * trap --> <Trap Table>
     *              ....
     *              ....
     *           trap entry  --> handler --> trap_handle (C) --> TrapRegistry
     *                                                               ....
     *                                                               ....
     *                                                        registered handler --> (out)
     *                          end-trap <------ (ret) ----------------------------- (ret)
     *
     *
     * Cheers -- mstarch
     */
    class TrapRegistry {
        public:
            /**
             * Constructs, clears, and sets to NULL the trap registry table.
             * In a given system, only one of these TrapRegistrys should be
             * constructed.
             */
            TrapRegistry();

            /**
             * Registers a given trap-handler to the given trap. Once that trap
             * is triggered, this object's "doTrap" will be called.
             * Note: the "doTrap" should remain simple, as traps are expected
             *       to be fast.
             * \param U32 trap: trap to handle
             * \param Fw::TrapHandler handle: handler object to handle function
             */
            void register_trap_handle(U32 trap, Fw::TrapHandler& handler);

            //!< Trap registry singlton instance to share with C function
            static TrapRegistry* s_trap_instance;
            //!< Trap registry table, public for exposure to C method
            Fw::TrapHandler* m_handlers[TRAP_REGISTRY_COUNT];
   };
}; //Namespace Drv

//Avoids name-mangling on assembly interface functions
extern "C" {
    /**
     * A C-function used as a destination from the jump from
     * the Assembly/Machine code trap table and handler.
     */
    void trap_handle();
//Handler only exists in sparc assembly
#if defined(BUILD_SPHINX) || defined(BUILD_GR712DEV)
    /**
     * Used to acquire the address for the assembly "handler"
     * label. DO NOT CALL directly as a call will initiate
     * a trap response and *should not* be done in non-trap
     * context.
     */
    void handler(void);
#endif
}
#endif
