// ====================================================================== 
// \title  NORFlashDriverImpl.cpp
// \author ortega
// \brief  cpp file for NORFlashDriver component implementation class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
// ====================================================================== 


#include <fprime-sphinx-drivers/NORFlashDriver/NORFlashDriverComponentImpl.hpp>
#include "Fw/Types/BasicTypes.hpp"
#include "Fw/Types/Assert.hpp"
#include <fprime-sphinx-drivers/NOR/nor.hpp>

namespace Drv {

  // ----------------------------------------------------------------------
  // Construction, initialization, and destruction 
  // ----------------------------------------------------------------------

  NORFlashDriverComponentImpl ::
#if FW_OBJECT_NAMES == 1
    NORFlashDriverComponentImpl(
        const char *const compName
    ) :
      NORFlashDriverComponentBase(compName)
#else
    NORFlashDriverImpl(void)
#endif
  {

  }

  void NORFlashDriverComponentImpl ::
    init(
        const NATIVE_INT_TYPE instance
    ) 
  {
    NORFlashDriverComponentBase::init(instance);
  }

  NORFlashDriverComponentImpl ::
    ~NORFlashDriverComponentImpl(void)
  {

  }

  // ----------------------------------------------------------------------
  // Handler implementations for user-defined typed input ports
  // ----------------------------------------------------------------------

  I8 NORFlashDriverComponentImpl ::
    read_handler(
        const NATIVE_INT_TYPE portNum,
        U32 dest,
        U8 *data
    )
  {
    FW_ASSERT(data != NULL);
    return read8_nocache(dest, data);
  }

  I8 NORFlashDriverComponentImpl ::
    write_handler(
        const NATIVE_INT_TYPE portNum,
        U32 dest_addr,
        U8 src
    )
  {
    return write8(dest_addr, src);
  }

  /*--------------------------------------------------------------------------
   * Function:    write8()
   * Arguments:
   *    Inputs:
   *              - U32 * address
   *              - U8 * data
   *    Outputs:
   *              N/A
   * return:      I8 status
   * Description: write one byte data. Return NOR_OK on success or NOR_FAILED on failure
   * -----------------------------------------------------------------------*/
  inline I8 NORFlashDriverComponentImpl::write8( U32 address, U8 data )
  {
#ifdef TGT_OS_TYPE_VXWORKS
    // This function should never fail unless operator passes invalid address.
    // Failure in user's implementation if this function fails.
    // return if address is not valid
    if(!Drv::isInNorAddrSpace(address))
    {
      return NOR_FAILED;
    }

    __asm__ volatile ("stb %0, [%1] "
        :
        : "r"( data ), "r"( address )
    );
    return NOR_OK;
#else
    return NOR_FAILED;
#endif
  }

  /*--------------------------------------------------------------------------
   * Function:    read8_nocache()
   * Arguments:
   *    Inputs:
   *              - UINT32_t * address
   *    Outputs:
   *              N/A
   * return:      NOR_OK on success or NOR_FAILED on failure
   * Description: read one 8-bit data
   * -----------------------------------------------------------------------*/
  inline I8 NORFlashDriverComponentImpl::read8_nocache( U32 address, U8 *data )
  {
    FW_ASSERT(data != NULL);

#ifdef TGT_OS_TYPE_VXWORKS
    // return if address is not valid
    if(!Drv::isInNorAddrSpace(address))
    {
      return NOR_FAILED;
    }

    U8 tmp;
    __asm__ volatile ("flush %1; lduba [%1]1, %0 "
        : "=r"( tmp )
        : "r"( address )
    );

    *data = tmp;
    return NOR_OK;
#else
    return NOR_FAILED;
#endif
  }
};
