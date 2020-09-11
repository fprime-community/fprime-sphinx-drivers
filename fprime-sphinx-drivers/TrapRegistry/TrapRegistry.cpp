// ======================================================================
// \title  TrapRegistry.cpp
// \author mstarch
// \brief  .cpp file for Sparc V8 custom trap handles
//
// \copyright
// Copyright 2009-2018, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
// ======================================================================

#include <Fw/Types/BasicTypes.hpp>
#include <fprime-sphinx-drivers/TrapRegistry/TrapRegistry.hpp>
#include <fprime-sphinx-drivers/Util/SphinxDrvIntUtil.hpp>
#include <stdio.h>
#include <Fw/Logger/Logger.hpp>
#ifdef TGT_OS_TYPE_VXWORKS
    #include <taskLib.h>
#endif


//For the VxWorks interface function, this "trap_handle_exlib"
//must be defined within C-linkage as VxWorks can call C functions
extern "C" {
#ifdef TGT_OS_TYPE_VXWORKS
    #include <excLib.h>
    void trap_handle_exlib(int task, int vecNum, void* frame) {
        U32 trap = (U32) vecNum;
        //Check for registrar and defined trap handle not-NULL
        if (Drv::TrapRegistry::s_trap_instance != NULL && Drv::TrapRegistry::s_trap_instance->m_handlers[trap] != NULL) {
            Drv::TrapRegistry::s_trap_instance->m_handlers[trap]->doTrap(trap);
        }
    }
#endif
};

namespace Drv {

//Singleton pointer to global trap registry
TrapRegistry* TrapRegistry::s_trap_instance = NULL;

TrapRegistry ::
  TrapRegistry()
{
    //Clear and initialize the handler array to ensure
    //that any unregistered handlers are "NULL"
    for (U32 i = 0; i < TRAP_REGISTRY_COUNT; i++) {
       m_handlers[i] = NULL; 
    }
    //Set singleton pointer to latest construction of this
    //trap registrar. Should not be set twice.
    FW_ASSERT(s_trap_instance == NULL);
    s_trap_instance = this;
} 

void TrapRegistry ::
  register_trap_handle(U32 trap, Fw::TrapHandler& handler_func)
{
    FW_ASSERT(trap < TRAP_REGISTRY_COUNT);
    //Register C/C++ level trap handler into our
    //handler table.
    this->m_handlers[trap] = &handler_func;
#ifdef TGT_OS_TYPE_VXWORKS
    // Note: register hook needs to be called exactly one time
    static bool registered = false;
    if (!registered) {
        excHookAdd((FUNCPTR) &trap_handle_exlib );
        registered = true;
    }
#endif
}
}; //End Drv namespace
