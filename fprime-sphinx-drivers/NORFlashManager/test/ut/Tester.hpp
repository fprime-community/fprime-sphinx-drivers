// ====================================================================== 
// \title  NORFlashManager/test/ut/Tester.hpp
// \author ciankc
// \brief  hpp file for NORFlashManager test harness implementation class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
// ====================================================================== 

#ifndef TESTER_HPP
#define TESTER_HPP

#include "GTestBase.hpp"
#include "fprime-sphinx-drivers/NORFlashManager/NORFlashManagerComponentImpl.hpp"
#include "fprime-sphinx-drivers/Util/SphinxDrvReg.hpp"
#include "fprime-sphinx-drivers/Util/SphinxDrvUtil.hpp"

namespace Drv {

  class Tester :
    public NORFlashManagerGTestBase
  {

      // ----------------------------------------------------------------------
      // Construction and destruction
      // ----------------------------------------------------------------------

    public:

      //! Construct object Tester
      //!
      Tester(const char* compName, U32 timeout);

      //! Destroy object Tester
      //!
      ~Tester(void);

    public:

      // ---------------------------------------------------------------------- 
      // Tests
      // ---------------------------------------------------------------------- 

      //! To do
      //!
      void toDo(void);

    private:

      // ----------------------------------------------------------------------
      // Handlers for typed from ports
      // ----------------------------------------------------------------------

      //! Handler for from_PingResponse
      //!
      void from_PingResponse_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          U32 key /*!< Value to return to pinger*/
      );

      //! Handler for from_verification_done
      //!
      void from_verification_done_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          I32 valid_nor, 
          U32 read_blc_checksum, 
          U32 read_fsw_checksum, 
          U32 cptd_blc_checksum, 
          U32 cptd_fsw_checksum 
      );

      //! Handler for from_erase_done
      //!
      void from_erase_done_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          I8 done, 
          U32 context1, 
          U32 context2 
      );

      //! Handler for from_read_done
      //!
      void from_read_done_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          I8 done, 
          U32 context1, 
          U32 context2 
      );

      //! Handler for from_worker_verify
      //!
      void from_worker_verify_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          U32 blc_filesize, 
          U32 fsw_filesize 
      );

      //! Handler for from_worker_write
      //!
      void from_worker_write_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          U32 dest, 
          U8 *src, 
          U32 count, 
          U32 bank 
      );

      //! Handler for from_write_done
      //!
      void from_write_done_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          I8 done, 
          U32 context1, 
          U32 context2 
      );

      //! Handler for from_worker_erase
      //!
      void from_worker_erase_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          U32 bank_addr
      );

      //! Handler for from_worker_cancel
      //!
      void from_worker_cancel_handler(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

      //! Handler for from_worker_reset
      //!
      void from_worker_reset_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          U32 dontcare_addr 
      );

      //! Handler for from_worker_read
      //!
      void from_worker_read_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          U8 *dest, 
          U32 src, 
          U32 count, 
          U32 bank 
      );

    private:

      // ----------------------------------------------------------------------
      // Helper methods
      // ----------------------------------------------------------------------

      //! Connect ports
      //!
      void connectPorts(void);

      //! Initialize components
      //!
      void initComponents(void);

    protected:

      // ----------------------------------------------------------------------
      // Variables
      // ----------------------------------------------------------------------

      //! The component under test
      //!
      NORFlashManagerComponentImpl component;

  };

} // end namespace Drv

#endif
