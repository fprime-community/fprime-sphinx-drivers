// ====================================================================== 
// \title  UartDriverImpl.cpp
// \author ortega
// \brief  cpp file for UartDriver component implementation class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
// ====================================================================== 


#include <fprime-sphinx-drivers/UartDriver/UartDriverComponentImpl.hpp>
#include "Fw/Types/BasicTypes.hpp"
#include "Fw/Types/Assert.hpp"

extern "C" {
#ifdef TGT_OS_TYPE_VXWORKS
#include <ioLib.h>
#include <vxWorks.h>
#include <sioLib.h>
#include <selectLib.h>
#include <errnoLib.h>
#include <logLib.h>
#elif defined TGT_OS_TYPE_LINUX || TGT_OS_TYPE_DARWIN
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <errno.h>
#define ERROR (-1)
#endif
}

namespace Drv {

  // ----------------------------------------------------------------------
  // Construction, initialization, and destruction 
  // ----------------------------------------------------------------------

  UartDriverComponentImpl ::
#if FW_OBJECT_NAMES == 1
    UartDriverComponentImpl(
        const char *const compName,
        const char *deviceName,
        const U32 baudrate
    ) :
      UartDriverComponentBase(compName)
#else
    UartDriverImpl(
          const char *deviceName,
          const U32 baudrate
    ) :
      UartDriverComponentBase()

#endif
  {
    this->ts.tv_sec = 0;
    this->ts.tv_usec = 0;

    this->m_deviceName = deviceName;
    this->m_baudrate = baudrate;

    // The O_NONBLOCK most likely does nothing for our serial device.
    this->m_serialFd = open(deviceName, O_RDWR | O_NONBLOCK, 0666);
    if(this->m_serialFd < 0)
    {
       (void)printf("openSerial: Unable to open %s\n", deviceName);
       FW_ASSERT(0);
    }

    #ifdef TGT_OS_TYPE_VXWORKS
    /* TODO: Set baudrate for OS other than vxworks. */
    /* Remove this block of code. Expecting UART to be configured at
       the kernel level. */
    /*
    I32 status;
    status = ioctl(this->m_serialFd, SIO_BAUD_SET, baudrate);
    if(status < 0)
    {
      (void)printf("openSerial: Unable to set options.\n");
      FW_ASSERT(0);
    }
    */
    #endif
  }

  void UartDriverComponentImpl ::
    init(
        const NATIVE_INT_TYPE instance
    ) 
  {
    UartDriverComponentBase::init(instance);

    // initialize timeout to 0 for immediate timeout
    this->ts.tv_sec = 0;
    this->ts.tv_usec = 0;
  }

  UartDriverComponentImpl ::
    ~UartDriverComponentImpl(void)
  {
    int status;

    status = close(this->m_serialFd);
    FW_ASSERT(status >= 0);
  }

  // ----------------------------------------------------------------------
  // Handler implementations for user-defined typed input ports
  // ----------------------------------------------------------------------

  void UartDriverComponentImpl ::
    WriteSerial_handler(
        const NATIVE_INT_TYPE portNum,
        Fw::Buffer &fwBuffer
    )
  {
    I32 status;
    U8 *data = reinterpret_cast<U8*>(fwBuffer.getdata());
    U32 nbytes = fwBuffer.getsize();

    FW_ASSERT(this->m_serialFd > 0);
    FW_ASSERT(data != NULL);

    status = write(this->m_serialFd, (char*)data, nbytes);
    FW_ASSERT(status != ERROR);

  }

  void UartDriverComponentImpl ::
    ReadSerial_handler(
        const NATIVE_INT_TYPE portNum,
        Fw::Buffer &fwBuffer
    )
  {
    I32 status;
    U8 *data = reinterpret_cast<U8*>(fwBuffer.getdata());
    U32 nbytes = fwBuffer.getsize();

    FW_ASSERT(this->m_serialFd > 0);
    FW_ASSERT(data != NULL);

    // FD_SET the file descriptors set since on return, select will zero out the set.
    FD_ZERO(&(this->readfds));
    FD_SET(this->m_serialFd, &(this->readfds));

    // Read data from UART
    status = select(this->m_serialFd+1, &(this->readfds), NULL, NULL, &(this->ts));
    if(status > 0)
    {
      status = read(this->m_serialFd, (char*)data, nbytes);
      FW_ASSERT(status >= 0, status);
    }
    else if(status < 0)
    {
      printf("failed to poll CMD/TLM port through UART with ERRNO %d\n", errno); 
      FW_ASSERT(0);
    }
    else
    {
      // Poll on file descriptor did not return any data.
      //logMsg("uartdriver: poll on file descriptor did not return any data.\n", 0,0,0,0,0,0);
    }

  }

} // end namespace Drv
