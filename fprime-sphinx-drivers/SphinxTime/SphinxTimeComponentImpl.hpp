// ======================================================================
// \title  SphinxTimeComponentImpl.hpp
//  *  Created on: July 28, 2016
// *      Author: ortega and arizvi
// \brief  hpp file for SphinxTime component implementation class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
//
// ======================================================================

#ifndef SphinxTime_HPP
#define SphinxTime_HPP

#include "fprime-sphinx-drivers/SphinxTime/SphinxTimeComponentAc.hpp"
extern "C" {
  #include "SphinxTimeRegs.h"
}

namespace Drv {

  class SphinxTimeComponentImpl :
    public SphinxTimeComponentBase
  {

    public:

      // ----------------------------------------------------------------------
      // Construction, initialization, and destruction
      // ----------------------------------------------------------------------

      //! Construct object SphinxTime
      //!
      SphinxTimeComponentImpl(
#if FW_OBJECT_NAMES == 1
          const char *const compName /*!< The component name*/
#else
          void
#endif
      );

      //! Initialize object SphinxTime
      //!
      void init(
          const NATIVE_INT_TYPE instance = 0 /*!< The instance number*/
      );

      //! Destroy object SphinxTime
      //!
      ~SphinxTimeComponentImpl(void);

    PRIVATE:

      typedef enum {
          SPHINX_SC,
          SPHINX_UPTIME,
          GR712
      } time_source;

      bool m_first_cycle;

      void get_cpu_time(volatile U32 *secs, volatile U32 *usecs);
      void get_time(Fw::Time &time, time_source src);
      void update_time(U32 secs, U32 uSecs);
      void update_time_members(void);
      void read_sphinx_uptime(void);

      // ----------------------------------------------------------------------
      // Handler implementations for user-defined typed input ports
      // ----------------------------------------------------------------------

      //! Handler implementation for timeInREL
      //!
      void timeInREL_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          U32 SC_Time_Secs, 
          U32 SC_Time_uSecs 
      );

      //! Handler implementation for timeInABS
      //!
      void timeInABS_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          U32 SC_Time_Secs, 
          U32 SC_Time_uSecs 
      );

      //! Handler implementation for schedIn
      //!
      void schedIn_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          NATIVE_UINT_TYPE context /*!< The call order*/
      );

      //! Handler implementation for timeGetPort
      //!
      void timeGetPort_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          Fw::Time &time /*!< The U32 cmd argument*/
      );


    };

} // end namespace Drv

#endif
