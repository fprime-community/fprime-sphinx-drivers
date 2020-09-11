// ======================================================================
// \title  NORFlashManager/test/ut/TesterBase.hpp
// \author Auto-generated
// \brief  hpp file for NORFlashManager component test harness base class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
// ======================================================================

#ifndef NORFlashManager_TESTER_BASE_HPP
#define NORFlashManager_TESTER_BASE_HPP

#include <fprime-sphinx-drivers/NORFlashManager/NORFlashManagerComponentAc.hpp>
#include <Fw/Types/Assert.hpp>
#include <Fw/Comp/PassiveComponentBase.hpp>
#include <stdio.h>
#include <Fw/Port/InputSerializePort.hpp>

namespace Drv {

  //! \class NORFlashManagerTesterBase
  //! \brief Auto-generated base class for NORFlashManager component test harness
  //!
  class NORFlashManagerTesterBase :
    public Fw::PassiveComponentBase
  {

    public:

      // ----------------------------------------------------------------------
      // Initialization
      // ----------------------------------------------------------------------

      //! Initialize object NORFlashManagerTesterBase
      //!
      virtual void init(
          const NATIVE_INT_TYPE instance = 0 /*!< The instance number*/
      );

    public:

      // ----------------------------------------------------------------------
      // Connectors for 'to' ports
      // Connect these output ports to the input ports under test
      // ----------------------------------------------------------------------

      //! Connect get_bl_size to to_get_bl_size[portNum]
      //!
      void connect_to_get_bl_size(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          Drv::InputNORFlash_GetSizePort *const get_bl_size /*!< The port*/
      );

      //! Connect PingRecv to to_PingRecv[portNum]
      //!
      void connect_to_PingRecv(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          Svc::InputPingPort *const PingRecv /*!< The port*/
      );

      //! Connect request_verification to to_request_verification[portNum]
      //!
      void connect_to_request_verification(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          Drv::InputNORFlash_VerifyPort *const request_verification /*!< The port*/
      );

      //! Connect cmdIn to to_cmdIn[portNum]
      //!
      void connect_to_cmdIn(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          Fw::InputCmdPort *const cmdIn /*!< The port*/
      );

      //! Connect get_fsw_size to to_get_fsw_size[portNum]
      //!
      void connect_to_get_fsw_size(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          Drv::InputNORFlash_GetSizePort *const get_fsw_size /*!< The port*/
      );

      //! Connect request_write to to_request_write[portNum]
      //!
      void connect_to_request_write(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          Drv::InputNORFlash_RWPort *const request_write /*!< The port*/
      );

      //! Connect worker_done to to_worker_done[portNum]
      //!
      void connect_to_worker_done(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          Drv::InputNOR_donePort *const worker_done /*!< The port*/
      );

      //! Connect request_read to to_request_read[portNum]
      //!
      void connect_to_request_read(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          Drv::InputNORFlash_RWPort *const request_read /*!< The port*/
      );

      //! Connect schedIn to to_schedIn[portNum]
      //!
      void connect_to_schedIn(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          Svc::InputSchedPort *const schedIn /*!< The port*/
      );

      //! Connect request_erase to to_request_erase[portNum]
      //!
      void connect_to_request_erase(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          Drv::InputNORFlash_EraseBankNumberPort *const request_erase /*!< The port*/
      );

    public:

      // ----------------------------------------------------------------------
      // Getters for 'from' ports
      // Connect these input ports to the output ports under test
      // ----------------------------------------------------------------------

      //! Get the port that receives input from eventOut
      //!
      //! \return from_eventOut[portNum]
      //!
      Fw::InputLogPort* get_from_eventOut(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

      //! Get the port that receives input from PingResponse
      //!
      //! \return from_PingResponse[portNum]
      //!
      Svc::InputPingPort* get_from_PingResponse(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

      //! Get the port that receives input from verification_done
      //!
      //! \return from_verification_done[portNum]
      //!
      Drv::InputNORFlash_ChecksumDonePort* get_from_verification_done(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

      //! Get the port that receives input from erase_done
      //!
      //! \return from_erase_done[portNum]
      //!
      Drv::InputNOR_donePort* get_from_erase_done(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

      //! Get the port that receives input from read_done
      //!
      //! \return from_read_done[portNum]
      //!
      Drv::InputNOR_donePort* get_from_read_done(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

      //! Get the port that receives input from worker_verify
      //!
      //! \return from_worker_verify[portNum]
      //!
      Drv::InputNORFlash_VerifyPort* get_from_worker_verify(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

      //! Get the port that receives input from timeCaller
      //!
      //! \return from_timeCaller[portNum]
      //!
      Fw::InputTimePort* get_from_timeCaller(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

      //! Get the port that receives input from cmdResponse
      //!
      //! \return from_cmdResponse[portNum]
      //!
      Fw::InputCmdResponsePort* get_from_cmdResponse(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

      //! Get the port that receives input from worker_write
      //!
      //! \return from_worker_write[portNum]
      //!
      Drv::InputNORFlash_BWPort* get_from_worker_write(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

      //! Get the port that receives input from cmdReg
      //!
      //! \return from_cmdReg[portNum]
      //!
      Fw::InputCmdRegPort* get_from_cmdReg(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

      //! Get the port that receives input from write_done
      //!
      //! \return from_write_done[portNum]
      //!
      Drv::InputNOR_donePort* get_from_write_done(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

      //! Get the port that receives input from worker_erase
      //!
      //! \return from_worker_erase[portNum]
      //!
      Drv::InputNORFlash_EraseBankAddrPort* get_from_worker_erase(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

      //! Get the port that receives input from worker_cancel
      //!
      //! \return from_worker_cancel[portNum]
      //!
      Drv::InputNORFlash_CancelPort* get_from_worker_cancel(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

      //! Get the port that receives input from worker_reset
      //!
      //! \return from_worker_reset[portNum]
      //!
      Drv::InputNORFlash_ResetPort* get_from_worker_reset(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

      //! Get the port that receives input from worker_read
      //!
      //! \return from_worker_read[portNum]
      //!
      Drv::InputNORFlash_BRPort* get_from_worker_read(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

#if FW_ENABLE_TEXT_LOGGING == 1
      //! Get the port that receives input from LogText
      //!
      //! \return from_LogText[portNum]
      //!
      Fw::InputLogTextPort* get_from_LogText(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );
#endif

    protected:

      // ----------------------------------------------------------------------
      // Construction and destruction
      // ----------------------------------------------------------------------

      //! Construct object NORFlashManagerTesterBase
      //!
      NORFlashManagerTesterBase(
#if FW_OBJECT_NAMES == 1
          const char *const compName, /*!< The component name*/
          const U32 maxHistorySize /*!< The maximum size of each history*/
#else
          const U32 maxHistorySize /*!< The maximum size of each history*/
#endif
      );

      //! Destroy object NORFlashManagerTesterBase
      //!
      virtual ~NORFlashManagerTesterBase(void);

      // ----------------------------------------------------------------------
      // Test history
      // ----------------------------------------------------------------------

    protected:

      //! \class History
      //! \brief A history of port inputs
      //!
      template <typename T> class History {

        public:

          //! Create a History
          //!
          History(
              const U32 maxSize /*!< The maximum history size*/
          ) : 
              numEntries(0), 
              maxSize(maxSize) 
          { 
            this->entries = new T[maxSize];
          }

          //! Destroy a History
          //!
          ~History() {
            delete[] this->entries;
          }

          //! Clear the history
          //!
          void clear() { this->numEntries = 0; }

          //! Push an item onto the history
          //!
          void push_back(
              T entry /*!< The item*/
          ) {
            FW_ASSERT(this->numEntries < this->maxSize);
            entries[this->numEntries++] = entry;
          }

          //! Get an item at an index
          //!
          //! \return The item at index i
          //!
          T at(
              const U32 i /*!< The index*/
          ) const {
            FW_ASSERT(i < this->numEntries);
            return entries[i];
          }

          //! Get the number of entries in the history
          //!
          //! \return The number of entries in the history
          //!
          U32 size(void) const { return this->numEntries; }

        private:

          //! The number of entries in the history
          //!
          U32 numEntries;

          //! The maximum history size
          //!
          const U32 maxSize;

          //! The entries
          //!
          T *entries;

      };

      //! Clear all history
      //!
      void clearHistory(void);

    protected:

      // ----------------------------------------------------------------------
      // Handler prototypes for typed from ports
      // ----------------------------------------------------------------------

      //! Handler prototype for from_PingResponse
      //!
      virtual void from_PingResponse_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          U32 key /*!< Value to return to pinger*/
      ) = 0;

      //! Handler base function for from_PingResponse
      //!
      void from_PingResponse_handlerBase(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          U32 key /*!< Value to return to pinger*/
      );

      //! Handler prototype for from_verification_done
      //!
      virtual void from_verification_done_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          I32 valid_nor, 
          U32 read_blc_checksum, 
          U32 read_fsw_checksum, 
          U32 cptd_blc_checksum, 
          U32 cptd_fsw_checksum 
      ) = 0;

      //! Handler base function for from_verification_done
      //!
      void from_verification_done_handlerBase(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          I32 valid_nor, 
          U32 read_blc_checksum, 
          U32 read_fsw_checksum, 
          U32 cptd_blc_checksum, 
          U32 cptd_fsw_checksum 
      );

      //! Handler prototype for from_erase_done
      //!
      virtual void from_erase_done_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          I8 done, 
          U32 context1, 
          U32 context2 
      ) = 0;

      //! Handler base function for from_erase_done
      //!
      void from_erase_done_handlerBase(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          I8 done, 
          U32 context1, 
          U32 context2 
      );

      //! Handler prototype for from_read_done
      //!
      virtual void from_read_done_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          I8 done, 
          U32 context1, 
          U32 context2 
      ) = 0;

      //! Handler base function for from_read_done
      //!
      void from_read_done_handlerBase(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          I8 done, 
          U32 context1, 
          U32 context2 
      );

      //! Handler prototype for from_worker_verify
      //!
      virtual void from_worker_verify_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          U32 blc_filesize, 
          U32 fsw_filesize 
      ) = 0;

      //! Handler base function for from_worker_verify
      //!
      void from_worker_verify_handlerBase(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          U32 blc_filesize, 
          U32 fsw_filesize 
      );

      //! Handler prototype for from_worker_write
      //!
      virtual void from_worker_write_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          U32 dest, 
          U8 *src, 
          U32 count, 
          U32 bank 
      ) = 0;

      //! Handler base function for from_worker_write
      //!
      void from_worker_write_handlerBase(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          U32 dest, 
          U8 *src, 
          U32 count, 
          U32 bank 
      );

      //! Handler prototype for from_write_done
      //!
      virtual void from_write_done_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          I8 done, 
          U32 context1, 
          U32 context2 
      ) = 0;

      //! Handler base function for from_write_done
      //!
      void from_write_done_handlerBase(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          I8 done, 
          U32 context1, 
          U32 context2 
      );

      //! Handler prototype for from_worker_erase
      //!
      virtual void from_worker_erase_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          U32 bank_addr 
      ) = 0;

      //! Handler base function for from_worker_erase
      //!
      void from_worker_erase_handlerBase(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          U32 bank_addr 
      );

      //! Handler prototype for from_worker_cancel
      //!
      virtual void from_worker_cancel_handler(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      ) = 0;

      //! Handler base function for from_worker_cancel
      //!
      void from_worker_cancel_handlerBase(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

      //! Handler prototype for from_worker_reset
      //!
      virtual void from_worker_reset_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          U32 dontcare_addr 
      ) = 0;

      //! Handler base function for from_worker_reset
      //!
      void from_worker_reset_handlerBase(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          U32 dontcare_addr 
      );

      //! Handler prototype for from_worker_read
      //!
      virtual void from_worker_read_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          U8 *dest, 
          U32 src, 
          U32 count, 
          U32 bank 
      ) = 0;

      //! Handler base function for from_worker_read
      //!
      void from_worker_read_handlerBase(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          U8 *dest, 
          U32 src, 
          U32 count, 
          U32 bank 
      );

    protected:

      // ----------------------------------------------------------------------
      // Histories for typed from ports
      // ----------------------------------------------------------------------

      //! Clear from port history
      //!
      void clearFromPortHistory(void);

      //! The total number of from port entries
      //!
      U32 fromPortHistorySize;

      //! Push an entry on the history for from_PingResponse
      void pushFromPortEntry_PingResponse(
          U32 key /*!< Value to return to pinger*/
      );

      //! A history entry for from_PingResponse
      //!
      typedef struct {
        U32 key;
      } FromPortEntry_PingResponse;

      //! The history for from_PingResponse
      //!
      History<FromPortEntry_PingResponse> 
        *fromPortHistory_PingResponse;

      //! Push an entry on the history for from_verification_done
      void pushFromPortEntry_verification_done(
          I32 valid_nor, 
          U32 read_blc_checksum, 
          U32 read_fsw_checksum, 
          U32 cptd_blc_checksum, 
          U32 cptd_fsw_checksum 
      );

      //! A history entry for from_verification_done
      //!
      typedef struct {
        I32 valid_nor;
        U32 read_blc_checksum;
        U32 read_fsw_checksum;
        U32 cptd_blc_checksum;
        U32 cptd_fsw_checksum;
      } FromPortEntry_verification_done;

      //! The history for from_verification_done
      //!
      History<FromPortEntry_verification_done> 
        *fromPortHistory_verification_done;

      //! Push an entry on the history for from_erase_done
      void pushFromPortEntry_erase_done(
          I8 done, 
          U32 context1, 
          U32 context2 
      );

      //! A history entry for from_erase_done
      //!
      typedef struct {
        I8 done;
        U32 context1;
        U32 context2;
      } FromPortEntry_erase_done;

      //! The history for from_erase_done
      //!
      History<FromPortEntry_erase_done> 
        *fromPortHistory_erase_done;

      //! Push an entry on the history for from_read_done
      void pushFromPortEntry_read_done(
          I8 done, 
          U32 context1, 
          U32 context2 
      );

      //! A history entry for from_read_done
      //!
      typedef struct {
        I8 done;
        U32 context1;
        U32 context2;
      } FromPortEntry_read_done;

      //! The history for from_read_done
      //!
      History<FromPortEntry_read_done> 
        *fromPortHistory_read_done;

      //! Push an entry on the history for from_worker_verify
      void pushFromPortEntry_worker_verify(
          U32 blc_filesize, 
          U32 fsw_filesize 
      );

      //! A history entry for from_worker_verify
      //!
      typedef struct {
        U32 blc_filesize;
        U32 fsw_filesize;
      } FromPortEntry_worker_verify;

      //! The history for from_worker_verify
      //!
      History<FromPortEntry_worker_verify> 
        *fromPortHistory_worker_verify;

      //! Push an entry on the history for from_worker_write
      void pushFromPortEntry_worker_write(
          U32 dest, 
          U8 *src, 
          U32 count, 
          U32 bank 
      );

      //! A history entry for from_worker_write
      //!
      typedef struct {
        U32 dest;
        U8 *src;
        U32 count;
        U32 bank;
      } FromPortEntry_worker_write;

      //! The history for from_worker_write
      //!
      History<FromPortEntry_worker_write> 
        *fromPortHistory_worker_write;

      //! Push an entry on the history for from_write_done
      void pushFromPortEntry_write_done(
          I8 done, 
          U32 context1, 
          U32 context2 
      );

      //! A history entry for from_write_done
      //!
      typedef struct {
        I8 done;
        U32 context1;
        U32 context2;
      } FromPortEntry_write_done;

      //! The history for from_write_done
      //!
      History<FromPortEntry_write_done> 
        *fromPortHistory_write_done;

      //! Push an entry on the history for from_worker_erase
      void pushFromPortEntry_worker_erase(
          U32 bank_addr 
      );

      //! A history entry for from_worker_erase
      //!
      typedef struct {
        U32 bank_addr;
      } FromPortEntry_worker_erase;

      //! The history for from_worker_erase
      //!
      History<FromPortEntry_worker_erase> 
        *fromPortHistory_worker_erase;

      //! Push an entry on the history for from_worker_cancel
      void pushFromPortEntry_worker_cancel(
          void
      );

      //! Size of history for from_worker_cancel
      //!
      U32 fromPortHistorySize_worker_cancel;

      //! Push an entry on the history for from_worker_reset
      void pushFromPortEntry_worker_reset(
          U32 dontcare_addr 
      );

      //! A history entry for from_worker_reset
      //!
      typedef struct {
        U32 dontcare_addr;
      } FromPortEntry_worker_reset;

      //! The history for from_worker_reset
      //!
      History<FromPortEntry_worker_reset> 
        *fromPortHistory_worker_reset;

      //! Push an entry on the history for from_worker_read
      void pushFromPortEntry_worker_read(
          U8 *dest, 
          U32 src, 
          U32 count, 
          U32 bank 
      );

      //! A history entry for from_worker_read
      //!
      typedef struct {
        U8 *dest;
        U32 src;
        U32 count;
        U32 bank;
      } FromPortEntry_worker_read;

      //! The history for from_worker_read
      //!
      History<FromPortEntry_worker_read> 
        *fromPortHistory_worker_read;

    protected:

      // ----------------------------------------------------------------------
      // Invocation functions for to ports
      // ----------------------------------------------------------------------

      //! Invoke the to port connected to get_bl_size
      //!
      I32 invoke_to_get_bl_size(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          U32 &size 
      );

      //! Invoke the to port connected to PingRecv
      //!
      void invoke_to_PingRecv(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          U32 key /*!< Value to return to pinger*/
      );

      //! Invoke the to port connected to request_verification
      //!
      void invoke_to_request_verification(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          U32 blc_filesize, 
          U32 fsw_filesize 
      );

      //! Invoke the to port connected to get_fsw_size
      //!
      I32 invoke_to_get_fsw_size(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          U32 &size 
      );

      //! Invoke the to port connected to request_write
      //!
      void invoke_to_request_write(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          U32 dest, 
          U8 *src, 
          U32 count, 
          bool disable_edac 
      );

      //! Invoke the to port connected to worker_done
      //!
      void invoke_to_worker_done(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          I8 done, 
          U32 context1, 
          U32 context2 
      );

      //! Invoke the to port connected to request_read
      //!
      void invoke_to_request_read(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          U32 dest, 
          U8 *src, 
          U32 count, 
          bool disable_edac 
      );

      //! Invoke the to port connected to schedIn
      //!
      void invoke_to_schedIn(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          NATIVE_UINT_TYPE context /*!< The call order*/
      );

      //! Invoke the to port connected to request_erase
      //!
      void invoke_to_request_erase(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          U8 bank_number 
      );

    public:

      // ----------------------------------------------------------------------
      // Getters for port counts
      // ----------------------------------------------------------------------

      //! Get the number of to_get_bl_size ports
      //!
      //! \return The number of to_get_bl_size ports
      //!
      NATIVE_INT_TYPE getNum_to_get_bl_size(void) const;

      //! Get the number of from_eventOut ports
      //!
      //! \return The number of from_eventOut ports
      //!
      NATIVE_INT_TYPE getNum_from_eventOut(void) const;

      //! Get the number of from_PingResponse ports
      //!
      //! \return The number of from_PingResponse ports
      //!
      NATIVE_INT_TYPE getNum_from_PingResponse(void) const;

      //! Get the number of from_verification_done ports
      //!
      //! \return The number of from_verification_done ports
      //!
      NATIVE_INT_TYPE getNum_from_verification_done(void) const;

      //! Get the number of to_PingRecv ports
      //!
      //! \return The number of to_PingRecv ports
      //!
      NATIVE_INT_TYPE getNum_to_PingRecv(void) const;

      //! Get the number of from_erase_done ports
      //!
      //! \return The number of from_erase_done ports
      //!
      NATIVE_INT_TYPE getNum_from_erase_done(void) const;

      //! Get the number of from_read_done ports
      //!
      //! \return The number of from_read_done ports
      //!
      NATIVE_INT_TYPE getNum_from_read_done(void) const;

      //! Get the number of from_worker_verify ports
      //!
      //! \return The number of from_worker_verify ports
      //!
      NATIVE_INT_TYPE getNum_from_worker_verify(void) const;

      //! Get the number of from_timeCaller ports
      //!
      //! \return The number of from_timeCaller ports
      //!
      NATIVE_INT_TYPE getNum_from_timeCaller(void) const;

      //! Get the number of from_cmdResponse ports
      //!
      //! \return The number of from_cmdResponse ports
      //!
      NATIVE_INT_TYPE getNum_from_cmdResponse(void) const;

      //! Get the number of to_request_verification ports
      //!
      //! \return The number of to_request_verification ports
      //!
      NATIVE_INT_TYPE getNum_to_request_verification(void) const;

      //! Get the number of to_cmdIn ports
      //!
      //! \return The number of to_cmdIn ports
      //!
      NATIVE_INT_TYPE getNum_to_cmdIn(void) const;

      //! Get the number of from_worker_write ports
      //!
      //! \return The number of from_worker_write ports
      //!
      NATIVE_INT_TYPE getNum_from_worker_write(void) const;

      //! Get the number of to_get_fsw_size ports
      //!
      //! \return The number of to_get_fsw_size ports
      //!
      NATIVE_INT_TYPE getNum_to_get_fsw_size(void) const;

      //! Get the number of to_request_write ports
      //!
      //! \return The number of to_request_write ports
      //!
      NATIVE_INT_TYPE getNum_to_request_write(void) const;

      //! Get the number of from_cmdReg ports
      //!
      //! \return The number of from_cmdReg ports
      //!
      NATIVE_INT_TYPE getNum_from_cmdReg(void) const;

      //! Get the number of to_worker_done ports
      //!
      //! \return The number of to_worker_done ports
      //!
      NATIVE_INT_TYPE getNum_to_worker_done(void) const;

      //! Get the number of to_request_read ports
      //!
      //! \return The number of to_request_read ports
      //!
      NATIVE_INT_TYPE getNum_to_request_read(void) const;

      //! Get the number of from_write_done ports
      //!
      //! \return The number of from_write_done ports
      //!
      NATIVE_INT_TYPE getNum_from_write_done(void) const;

      //! Get the number of from_worker_erase ports
      //!
      //! \return The number of from_worker_erase ports
      //!
      NATIVE_INT_TYPE getNum_from_worker_erase(void) const;

      //! Get the number of from_worker_cancel ports
      //!
      //! \return The number of from_worker_cancel ports
      //!
      NATIVE_INT_TYPE getNum_from_worker_cancel(void) const;

      //! Get the number of from_worker_reset ports
      //!
      //! \return The number of from_worker_reset ports
      //!
      NATIVE_INT_TYPE getNum_from_worker_reset(void) const;

      //! Get the number of to_schedIn ports
      //!
      //! \return The number of to_schedIn ports
      //!
      NATIVE_INT_TYPE getNum_to_schedIn(void) const;

      //! Get the number of to_request_erase ports
      //!
      //! \return The number of to_request_erase ports
      //!
      NATIVE_INT_TYPE getNum_to_request_erase(void) const;

      //! Get the number of from_worker_read ports
      //!
      //! \return The number of from_worker_read ports
      //!
      NATIVE_INT_TYPE getNum_from_worker_read(void) const;

#if FW_ENABLE_TEXT_LOGGING == 1
      //! Get the number of from_LogText ports
      //!
      //! \return The number of from_LogText ports
      //!
      NATIVE_INT_TYPE getNum_from_LogText(void) const;
#endif

    protected:

      // ----------------------------------------------------------------------
      // Connection status for to ports
      // ----------------------------------------------------------------------

      //! Check whether port is connected
      //!
      //! Whether to_get_bl_size[portNum] is connected
      //!
      bool isConnected_to_get_bl_size(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

      //! Check whether port is connected
      //!
      //! Whether to_PingRecv[portNum] is connected
      //!
      bool isConnected_to_PingRecv(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

      //! Check whether port is connected
      //!
      //! Whether to_request_verification[portNum] is connected
      //!
      bool isConnected_to_request_verification(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

      //! Check whether port is connected
      //!
      //! Whether to_cmdIn[portNum] is connected
      //!
      bool isConnected_to_cmdIn(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

      //! Check whether port is connected
      //!
      //! Whether to_get_fsw_size[portNum] is connected
      //!
      bool isConnected_to_get_fsw_size(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

      //! Check whether port is connected
      //!
      //! Whether to_request_write[portNum] is connected
      //!
      bool isConnected_to_request_write(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

      //! Check whether port is connected
      //!
      //! Whether to_worker_done[portNum] is connected
      //!
      bool isConnected_to_worker_done(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

      //! Check whether port is connected
      //!
      //! Whether to_request_read[portNum] is connected
      //!
      bool isConnected_to_request_read(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

      //! Check whether port is connected
      //!
      //! Whether to_schedIn[portNum] is connected
      //!
      bool isConnected_to_schedIn(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

      //! Check whether port is connected
      //!
      //! Whether to_request_erase[portNum] is connected
      //!
      bool isConnected_to_request_erase(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

      // ----------------------------------------------------------------------
      // Functions for sending commands
      // ----------------------------------------------------------------------

    protected:
    
      // send command buffers directly - used for intentional command encoding errors
      void sendRawCmd(FwOpcodeType opcode, U32 cmdSeq, Fw::CmdArgBuffer& args); 

      //! Send a NOR_FLASH_RESET command
      //!
      void sendCmd_NOR_FLASH_RESET(
          const NATIVE_INT_TYPE instance, /*!< The instance number*/
          const U32 cmdSeq, /*!< The command sequence number*/
          U8 bank_number /*!< The bank number to reset*/
      );

      //! Send a NOR_FLASH_SET_WRITE_TIMEOUT command
      //!
      void sendCmd_NOR_FLASH_SET_WRITE_TIMEOUT(
          const NATIVE_INT_TYPE instance, /*!< The instance number*/
          const U32 cmdSeq, /*!< The command sequence number*/
          U32 timeout /*!< The timeout value in schedIn ticks*/
      );

      //! Send a NOR_FLASH_SET_ERASE_TIMEOUT command
      //!
      void sendCmd_NOR_FLASH_SET_ERASE_TIMEOUT(
          const NATIVE_INT_TYPE instance, /*!< The instance number*/
          const U32 cmdSeq, /*!< The command sequence number*/
          U32 timeout /*!< The timeout value in schedIn ticks*/
      );

      //! Send a NOR_FLASH_SET_VERIFY_TIMEOUT command
      //!
      void sendCmd_NOR_FLASH_SET_VERIFY_TIMEOUT(
          const NATIVE_INT_TYPE instance, /*!< The instance number*/
          const U32 cmdSeq, /*!< The command sequence number*/
          U32 timeout /*!< The timeout value in schedIn ticks*/
      );

    protected:

      // ----------------------------------------------------------------------
      // Command response handling
      // ----------------------------------------------------------------------

      //! Handle a command response
      //!
      virtual void cmdResponseIn(
          const FwOpcodeType opCode, /*!< The opcode*/
          const U32 cmdSeq, /*!< The command sequence number*/
          const Fw::CommandResponse response /*!< The command response*/
      );

      //! A type representing a command response
      //!
      typedef struct {
        FwOpcodeType opCode;
        U32 cmdSeq;
        Fw::CommandResponse response;
      } CmdResponse;

      //! The command response history
      //!
      History<CmdResponse> *cmdResponseHistory;

    protected:

      // ----------------------------------------------------------------------
      // Event dispatch
      // ----------------------------------------------------------------------

      //! Dispatch an event
      //!
      void dispatchEvents(
          const FwEventIdType id, /*!< The event ID*/
          Fw::Time& timeTag, /*!< The time*/
          const Fw::LogSeverity severity, /*!< The severity*/
          Fw::LogBuffer& args /*!< The serialized arguments*/
      );

      //! Clear event history
      //!
      void clearEvents(void);

      //! The total number of events seen
      //!
      U32 eventsSize;

#if FW_ENABLE_TEXT_LOGGING

    protected:

      // ----------------------------------------------------------------------
      // Text events
      // ----------------------------------------------------------------------

      //! Handle a text event
      //!
      virtual void textLogIn(
          const FwEventIdType id, /*!< The event ID*/
          Fw::Time& timeTag, /*!< The time*/
          const Fw::TextLogSeverity severity, /*!< The severity*/
          const Fw::TextLogString& text /*!< The event string*/
      );

      //! A history entry for the text log
      //!
      typedef struct {
        U32 id;
        Fw::Time timeTag;
        Fw::TextLogSeverity severity;
        Fw::TextLogString text;
      } TextLogEntry;

      //! The history of text log events
      //!
      History<TextLogEntry> *textLogHistory;

      //! Print a text log history entry
      //!
      static void printTextLogHistoryEntry(
          const TextLogEntry& e,
          FILE* file
      );

      //! Print the text log history
      //!
      void printTextLogHistory(FILE *const file);

#endif

    protected:

      // ----------------------------------------------------------------------
      // Event: NOR_ERASE_BUSY
      // ----------------------------------------------------------------------

      //! Handle event NOR_ERASE_BUSY
      //!
      virtual void logIn_WARNING_HI_NOR_ERASE_BUSY(
          U32 actual_state, /*!< The state of the NOR Manager*/
          U32 expected_state, /*!< The expected state of the NOR Manager*/
          U32 error_status /*!< The error status*/
      );

      //! A history entry for event NOR_ERASE_BUSY
      //!
      typedef struct {
        U32 actual_state;
        U32 expected_state;
        U32 error_status;
      } EventEntry_NOR_ERASE_BUSY;

      //! The history of NOR_ERASE_BUSY events
      //!
      History<EventEntry_NOR_ERASE_BUSY> 
        *eventHistory_NOR_ERASE_BUSY;

    protected:

      // ----------------------------------------------------------------------
      // Event: NOR_ERASE_FAIL
      // ----------------------------------------------------------------------

      //! Handle event NOR_ERASE_FAIL
      //!
      virtual void logIn_WARNING_HI_NOR_ERASE_FAIL(
          U32 error_status /*!< The error status*/
      );

      //! A history entry for event NOR_ERASE_FAIL
      //!
      typedef struct {
        U32 error_status;
      } EventEntry_NOR_ERASE_FAIL;

      //! The history of NOR_ERASE_FAIL events
      //!
      History<EventEntry_NOR_ERASE_FAIL> 
        *eventHistory_NOR_ERASE_FAIL;

    protected:

      // ----------------------------------------------------------------------
      // Event: NOR_ERASING
      // ----------------------------------------------------------------------

      //! Handle event NOR_ERASING
      //!
      virtual void logIn_ACTIVITY_LO_NOR_ERASING(
          void
      );

      //! Size of history for event NOR_ERASING
      //!
      U32 eventsSize_NOR_ERASING;

    protected:

      // ----------------------------------------------------------------------
      // Event: NOR_ERASE_TIMEOUT
      // ----------------------------------------------------------------------

      //! Handle event NOR_ERASE_TIMEOUT
      //!
      virtual void logIn_WARNING_HI_NOR_ERASE_TIMEOUT(
          void
      );

      //! Size of history for event NOR_ERASE_TIMEOUT
      //!
      U32 eventsSize_NOR_ERASE_TIMEOUT;

    protected:

      // ----------------------------------------------------------------------
      // Event: NOR_ERASE_DONE
      // ----------------------------------------------------------------------

      //! Handle event NOR_ERASE_DONE
      //!
      virtual void logIn_ACTIVITY_LO_NOR_ERASE_DONE(
          void
      );

      //! Size of history for event NOR_ERASE_DONE
      //!
      U32 eventsSize_NOR_ERASE_DONE;

    protected:

      // ----------------------------------------------------------------------
      // Event: NOR_RESET_FAIL
      // ----------------------------------------------------------------------

      //! Handle event NOR_RESET_FAIL
      //!
      virtual void logIn_WARNING_HI_NOR_RESET_FAIL(
          U32 actual_state, /*!< The state of the NOR Manager*/
          U32 expected_state /*!< The expected state of the NOR Manager*/
      );

      //! A history entry for event NOR_RESET_FAIL
      //!
      typedef struct {
        U32 actual_state;
        U32 expected_state;
      } EventEntry_NOR_RESET_FAIL;

      //! The history of NOR_RESET_FAIL events
      //!
      History<EventEntry_NOR_RESET_FAIL> 
        *eventHistory_NOR_RESET_FAIL;

    protected:

      // ----------------------------------------------------------------------
      // Event: NOR_RESETTING
      // ----------------------------------------------------------------------

      //! Handle event NOR_RESETTING
      //!
      virtual void logIn_ACTIVITY_LO_NOR_RESETTING(
          void
      );

      //! Size of history for event NOR_RESETTING
      //!
      U32 eventsSize_NOR_RESETTING;

    protected:

      // ----------------------------------------------------------------------
      // Event: NOR_UNLOCK_BYPASS_FAILED
      // ----------------------------------------------------------------------

      //! Handle event NOR_UNLOCK_BYPASS_FAILED
      //!
      virtual void logIn_WARNING_HI_NOR_UNLOCK_BYPASS_FAILED(
          void
      );

      //! Size of history for event NOR_UNLOCK_BYPASS_FAILED
      //!
      U32 eventsSize_NOR_UNLOCK_BYPASS_FAILED;

    protected:

      // ----------------------------------------------------------------------
      // Event: NOR_UNLOCK_BYPASS_PROGRAM_FAILED
      // ----------------------------------------------------------------------

      //! Handle event NOR_UNLOCK_BYPASS_PROGRAM_FAILED
      //!
      virtual void logIn_WARNING_HI_NOR_UNLOCK_BYPASS_PROGRAM_FAILED(
          void
      );

      //! Size of history for event NOR_UNLOCK_BYPASS_PROGRAM_FAILED
      //!
      U32 eventsSize_NOR_UNLOCK_BYPASS_PROGRAM_FAILED;

    protected:

      // ----------------------------------------------------------------------
      // Event: NOR_UNLOCK_BYPASS_RESET_FAILED
      // ----------------------------------------------------------------------

      //! Handle event NOR_UNLOCK_BYPASS_RESET_FAILED
      //!
      virtual void logIn_WARNING_HI_NOR_UNLOCK_BYPASS_RESET_FAILED(
          void
      );

      //! Size of history for event NOR_UNLOCK_BYPASS_RESET_FAILED
      //!
      U32 eventsSize_NOR_UNLOCK_BYPASS_RESET_FAILED;

    protected:

      // ----------------------------------------------------------------------
      // Event: NOR_FAILED_TO_VERIFY_DATA
      // ----------------------------------------------------------------------

      //! Handle event NOR_FAILED_TO_VERIFY_DATA
      //!
      virtual void logIn_WARNING_HI_NOR_FAILED_TO_VERIFY_DATA(
          U32 dest_addr, /*!< The destination address*/
          U8 source /*!< The data to be written*/
      );

      //! A history entry for event NOR_FAILED_TO_VERIFY_DATA
      //!
      typedef struct {
        U32 dest_addr;
        U8 source;
      } EventEntry_NOR_FAILED_TO_VERIFY_DATA;

      //! The history of NOR_FAILED_TO_VERIFY_DATA events
      //!
      History<EventEntry_NOR_FAILED_TO_VERIFY_DATA> 
        *eventHistory_NOR_FAILED_TO_VERIFY_DATA;

    protected:

      // ----------------------------------------------------------------------
      // Event: NOR_UNLOCK_BYPASS_RESET_DURING_ERASE
      // ----------------------------------------------------------------------

      //! Handle event NOR_UNLOCK_BYPASS_RESET_DURING_ERASE
      //!
      virtual void logIn_WARNING_HI_NOR_UNLOCK_BYPASS_RESET_DURING_ERASE(
          void
      );

      //! Size of history for event NOR_UNLOCK_BYPASS_RESET_DURING_ERASE
      //!
      U32 eventsSize_NOR_UNLOCK_BYPASS_RESET_DURING_ERASE;

    protected:

      // ----------------------------------------------------------------------
      // Event: NOR_FAILED_TO_RESET
      // ----------------------------------------------------------------------

      //! Handle event NOR_FAILED_TO_RESET
      //!
      virtual void logIn_WARNING_HI_NOR_FAILED_TO_RESET(
          void
      );

      //! Size of history for event NOR_FAILED_TO_RESET
      //!
      U32 eventsSize_NOR_FAILED_TO_RESET;

    protected:

      // ----------------------------------------------------------------------
      // Event: NOR_WRITE_TIMEOUT
      // ----------------------------------------------------------------------

      //! Handle event NOR_WRITE_TIMEOUT
      //!
      virtual void logIn_WARNING_HI_NOR_WRITE_TIMEOUT(
          void
      );

      //! Size of history for event NOR_WRITE_TIMEOUT
      //!
      U32 eventsSize_NOR_WRITE_TIMEOUT;

    protected:

      // ----------------------------------------------------------------------
      // Event: NOR_FAILED_TO_VERIFY_CHECKSUM
      // ----------------------------------------------------------------------

      //! Handle event NOR_FAILED_TO_VERIFY_CHECKSUM
      //!
      virtual void logIn_WARNING_HI_NOR_FAILED_TO_VERIFY_CHECKSUM(
          void
      );

      //! Size of history for event NOR_FAILED_TO_VERIFY_CHECKSUM
      //!
      U32 eventsSize_NOR_FAILED_TO_VERIFY_CHECKSUM;

    protected:

      // ----------------------------------------------------------------------
      // Event: NOR_CHECKSUM_VERIFY_DONE
      // ----------------------------------------------------------------------

      //! Handle event NOR_CHECKSUM_VERIFY_DONE
      //!
      virtual void logIn_ACTIVITY_LO_NOR_CHECKSUM_VERIFY_DONE(
          void
      );

      //! Size of history for event NOR_CHECKSUM_VERIFY_DONE
      //!
      U32 eventsSize_NOR_CHECKSUM_VERIFY_DONE;

    protected:

      // ----------------------------------------------------------------------
      // Event: NOR_VERIFY_BUSY
      // ----------------------------------------------------------------------

      //! Handle event NOR_VERIFY_BUSY
      //!
      virtual void logIn_WARNING_HI_NOR_VERIFY_BUSY(
          U32 actual_state, /*!< The state of the NOR Manager*/
          U32 expected_state /*!< The expected state of the NOR Manager*/
      );

      //! A history entry for event NOR_VERIFY_BUSY
      //!
      typedef struct {
        U32 actual_state;
        U32 expected_state;
      } EventEntry_NOR_VERIFY_BUSY;

      //! The history of NOR_VERIFY_BUSY events
      //!
      History<EventEntry_NOR_VERIFY_BUSY> 
        *eventHistory_NOR_VERIFY_BUSY;

    protected:

      // ----------------------------------------------------------------------
      // Event: NOR_FAILED_TO_READ_DATA
      // ----------------------------------------------------------------------

      //! Handle event NOR_FAILED_TO_READ_DATA
      //!
      virtual void logIn_WARNING_HI_NOR_FAILED_TO_READ_DATA(
          U32 nor_addr, /*!< The address in NOR to read from*/
          U32 dest /*!< The memory buffer address use to store the value of nor_addr*/
      );

      //! A history entry for event NOR_FAILED_TO_READ_DATA
      //!
      typedef struct {
        U32 nor_addr;
        U32 dest;
      } EventEntry_NOR_FAILED_TO_READ_DATA;

      //! The history of NOR_FAILED_TO_READ_DATA events
      //!
      History<EventEntry_NOR_FAILED_TO_READ_DATA> 
        *eventHistory_NOR_FAILED_TO_READ_DATA;

    protected:

      // ----------------------------------------------------------------------
      // Event: NOR_READ_TIMEOUT
      // ----------------------------------------------------------------------

      //! Handle event NOR_READ_TIMEOUT
      //!
      virtual void logIn_WARNING_HI_NOR_READ_TIMEOUT(
          void
      );

      //! Size of history for event NOR_READ_TIMEOUT
      //!
      U32 eventsSize_NOR_READ_TIMEOUT;

    protected:

      // ----------------------------------------------------------------------
      // Event: NOR_ALREADY_ERASING
      // ----------------------------------------------------------------------

      //! Handle event NOR_ALREADY_ERASING
      //!
      virtual void logIn_WARNING_HI_NOR_ALREADY_ERASING(
          void
      );

      //! Size of history for event NOR_ALREADY_ERASING
      //!
      U32 eventsSize_NOR_ALREADY_ERASING;

    protected:

      // ----------------------------------------------------------------------
      // Test time
      // ----------------------------------------------------------------------

      //! Set the test time for events and telemetry
      //!
      void setTestTime(
          const Fw::Time& timeTag /*!< The time*/
      );

    private:

      // ----------------------------------------------------------------------
      // To ports
      // ----------------------------------------------------------------------

      //! To port connected to get_bl_size
      //!
      Drv::OutputNORFlash_GetSizePort m_to_get_bl_size[1];

      //! To port connected to PingRecv
      //!
      Svc::OutputPingPort m_to_PingRecv[1];

      //! To port connected to request_verification
      //!
      Drv::OutputNORFlash_VerifyPort m_to_request_verification[1];

      //! To port connected to cmdIn
      //!
      Fw::OutputCmdPort m_to_cmdIn[1];

      //! To port connected to get_fsw_size
      //!
      Drv::OutputNORFlash_GetSizePort m_to_get_fsw_size[1];

      //! To port connected to request_write
      //!
      Drv::OutputNORFlash_RWPort m_to_request_write[1];

      //! To port connected to worker_done
      //!
      Drv::OutputNOR_donePort m_to_worker_done[1];

      //! To port connected to request_read
      //!
      Drv::OutputNORFlash_RWPort m_to_request_read[1];

      //! To port connected to schedIn
      //!
      Svc::OutputSchedPort m_to_schedIn[1];

      //! To port connected to request_erase
      //!
      Drv::OutputNORFlash_EraseBankNumberPort m_to_request_erase[1];

    private:

      // ----------------------------------------------------------------------
      // From ports
      // ----------------------------------------------------------------------

      //! From port connected to eventOut
      //!
      Fw::InputLogPort m_from_eventOut[1];

      //! From port connected to PingResponse
      //!
      Svc::InputPingPort m_from_PingResponse[1];

      //! From port connected to verification_done
      //!
      Drv::InputNORFlash_ChecksumDonePort m_from_verification_done[1];

      //! From port connected to erase_done
      //!
      Drv::InputNOR_donePort m_from_erase_done[1];

      //! From port connected to read_done
      //!
      Drv::InputNOR_donePort m_from_read_done[1];

      //! From port connected to worker_verify
      //!
      Drv::InputNORFlash_VerifyPort m_from_worker_verify[1];

      //! From port connected to timeCaller
      //!
      Fw::InputTimePort m_from_timeCaller[1];

      //! From port connected to cmdResponse
      //!
      Fw::InputCmdResponsePort m_from_cmdResponse[1];

      //! From port connected to worker_write
      //!
      Drv::InputNORFlash_BWPort m_from_worker_write[1];

      //! From port connected to cmdReg
      //!
      Fw::InputCmdRegPort m_from_cmdReg[1];

      //! From port connected to write_done
      //!
      Drv::InputNOR_donePort m_from_write_done[1];

      //! From port connected to worker_erase
      //!
      Drv::InputNORFlash_EraseBankAddrPort m_from_worker_erase[1];

      //! From port connected to worker_cancel
      //!
      Drv::InputNORFlash_CancelPort m_from_worker_cancel[1];

      //! From port connected to worker_reset
      //!
      Drv::InputNORFlash_ResetPort m_from_worker_reset[1];

      //! From port connected to worker_read
      //!
      Drv::InputNORFlash_BRPort m_from_worker_read[1];

#if FW_ENABLE_TEXT_LOGGING == 1
      //! From port connected to LogText
      //!
      Fw::InputLogTextPort m_from_LogText[1];
#endif

    private:

      // ----------------------------------------------------------------------
      // Static functions for output ports
      // ----------------------------------------------------------------------

      //! Static function for port from_eventOut
      //!
      static void from_eventOut_static(
          Fw::PassiveComponentBase *const callComp, /*!< The component instance*/
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          FwEventIdType id, /*!< Log ID*/
          Fw::Time &timeTag, /*!< Time Tag*/
          Fw::LogSeverity severity, /*!< The severity argument*/
          Fw::LogBuffer &args /*!< Buffer containing serialized log entry*/
      );

      //! Static function for port from_PingResponse
      //!
      static void from_PingResponse_static(
          Fw::PassiveComponentBase *const callComp, /*!< The component instance*/
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          U32 key /*!< Value to return to pinger*/
      );

      //! Static function for port from_verification_done
      //!
      static void from_verification_done_static(
          Fw::PassiveComponentBase *const callComp, /*!< The component instance*/
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          I32 valid_nor, 
          U32 read_blc_checksum, 
          U32 read_fsw_checksum, 
          U32 cptd_blc_checksum, 
          U32 cptd_fsw_checksum 
      );

      //! Static function for port from_erase_done
      //!
      static void from_erase_done_static(
          Fw::PassiveComponentBase *const callComp, /*!< The component instance*/
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          I8 done, 
          U32 context1, 
          U32 context2 
      );

      //! Static function for port from_read_done
      //!
      static void from_read_done_static(
          Fw::PassiveComponentBase *const callComp, /*!< The component instance*/
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          I8 done, 
          U32 context1, 
          U32 context2 
      );

      //! Static function for port from_worker_verify
      //!
      static void from_worker_verify_static(
          Fw::PassiveComponentBase *const callComp, /*!< The component instance*/
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          U32 blc_filesize, 
          U32 fsw_filesize 
      );

      //! Static function for port from_timeCaller
      //!
      static void from_timeCaller_static(
          Fw::PassiveComponentBase *const callComp, /*!< The component instance*/
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          Fw::Time &time /*!< The U32 cmd argument*/
      );

      //! Static function for port from_cmdResponse
      //!
      static void from_cmdResponse_static(
          Fw::PassiveComponentBase *const callComp, /*!< The component instance*/
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          FwOpcodeType opCode, /*!< Command Op Code*/
          U32 cmdSeq, /*!< Command Sequence*/
          Fw::CommandResponse response /*!< The command response argument*/
      );

      //! Static function for port from_worker_write
      //!
      static void from_worker_write_static(
          Fw::PassiveComponentBase *const callComp, /*!< The component instance*/
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          U32 dest, 
          U8 *src, 
          U32 count, 
          U32 bank 
      );

      //! Static function for port from_cmdReg
      //!
      static void from_cmdReg_static(
          Fw::PassiveComponentBase *const callComp, /*!< The component instance*/
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          FwOpcodeType opCode /*!< Command Op Code*/
      );

      //! Static function for port from_write_done
      //!
      static void from_write_done_static(
          Fw::PassiveComponentBase *const callComp, /*!< The component instance*/
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          I8 done, 
          U32 context1, 
          U32 context2 
      );

      //! Static function for port from_worker_erase
      //!
      static void from_worker_erase_static(
          Fw::PassiveComponentBase *const callComp, /*!< The component instance*/
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          U32 bank_addr 
      );

      //! Static function for port from_worker_cancel
      //!
      static void from_worker_cancel_static(
          Fw::PassiveComponentBase *const callComp, /*!< The component instance*/
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

      //! Static function for port from_worker_reset
      //!
      static void from_worker_reset_static(
          Fw::PassiveComponentBase *const callComp, /*!< The component instance*/
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          U32 dontcare_addr 
      );

      //! Static function for port from_worker_read
      //!
      static void from_worker_read_static(
          Fw::PassiveComponentBase *const callComp, /*!< The component instance*/
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          U8 *dest, 
          U32 src, 
          U32 count, 
          U32 bank 
      );

#if FW_ENABLE_TEXT_LOGGING == 1
      //! Static function for port from_LogText
      //!
      static void from_LogText_static(
          Fw::PassiveComponentBase *const callComp, /*!< The component instance*/
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          FwEventIdType id, /*!< Log ID*/
          Fw::Time &timeTag, /*!< Time Tag*/
          Fw::TextLogSeverity severity, /*!< The severity argument*/
          Fw::TextLogString &text /*!< Text of log message*/
      );
#endif

    private:

      // ----------------------------------------------------------------------
      // Test time
      // ----------------------------------------------------------------------

      //! Test time stamp
      //!
      Fw::Time m_testTime;

  };

} // end namespace Drv

#endif
