// ======================================================================
// \title  SPWManager/test/ut/TesterBase.hpp
// \author Auto-generated
// \brief  hpp file for SPWManager component test harness base class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
// ======================================================================

#ifndef SPWManager_TESTER_BASE_HPP
#define SPWManager_TESTER_BASE_HPP

#include <fprime-sphinx-drivers/SPWManager/SPWManagerComponentAc.hpp>
#include <Fw/Types/Assert.hpp>
#include <Fw/Comp/PassiveComponentBase.hpp>
#include <stdio.h>
#include <Fw/Port/InputSerializePort.hpp>

namespace Drv {

  //! \class SPWManagerTesterBase
  //! \brief Auto-generated base class for SPWManager component test harness
  //!
  class SPWManagerTesterBase :
    public Fw::PassiveComponentBase
  {

    public:

      // ----------------------------------------------------------------------
      // Initialization
      // ----------------------------------------------------------------------

      //! Initialize object SPWManagerTesterBase
      //!
      virtual void init(
          const NATIVE_INT_TYPE instance = 0 /*!< The instance number*/
      );

    public:

      // ----------------------------------------------------------------------
      // Connectors for 'to' ports
      // Connect these output ports to the input ports under test
      // ----------------------------------------------------------------------

      //! Connect read to to_read[portNum]
      //!
      void connect_to_read(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          Drv::InputSphinxSPW_SendRequestPort *const read /*!< The port*/
      );

      //! Connect readAsyncDMA to to_readAsyncDMA[portNum]
      //!
      void connect_to_readAsyncDMA(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          Drv::InputSphinxSPW_SendRequestPort *const readAsyncDMA /*!< The port*/
      );

      //! Connect setParam to to_setParam[portNum]
      //!
      void connect_to_setParam(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          Drv::InputSphinxSPW_SetParamPort *const setParam /*!< The port*/
      );

      //! Connect PingRecv to to_PingRecv[portNum]
      //!
      void connect_to_PingRecv(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          Svc::InputPingPort *const PingRecv /*!< The port*/
      );

      //! Connect writeAsync to to_writeAsync[portNum]
      //!
      void connect_to_writeAsync(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          Drv::InputSphinxSPW_SendRequestPort *const writeAsync /*!< The port*/
      );

      //! Connect resetLink to to_resetLink[portNum]
      //!
      void connect_to_resetLink(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          Drv::InputSphinxSPW_TriggerPort *const resetLink /*!< The port*/
      );

      //! Connect schedIn to to_schedIn[portNum]
      //!
      void connect_to_schedIn(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          Svc::InputSchedPort *const schedIn /*!< The port*/
      );

      //! Connect cmdIn to to_cmdIn[portNum]
      //!
      void connect_to_cmdIn(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          Fw::InputCmdPort *const cmdIn /*!< The port*/
      );

      //! Connect write to to_write[portNum]
      //!
      void connect_to_write(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          Drv::InputSphinxSPW_SendRequestPort *const write /*!< The port*/
      );

      //! Connect readAsync to to_readAsync[portNum]
      //!
      void connect_to_readAsync(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          Drv::InputSphinxSPW_SendRequestPort *const readAsync /*!< The port*/
      );

    public:

      // ----------------------------------------------------------------------
      // Getters for 'from' ports
      // Connect these input ports to the output ports under test
      // ----------------------------------------------------------------------

      //! Get the port that receives input from driverWriteRMAP
      //!
      //! \return from_driverWriteRMAP[portNum]
      //!
      Drv::InputSphinxSPW_WriteRMAPPort* get_from_driverWriteRMAP(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

      //! Get the port that receives input from cmdRegOut
      //!
      //! \return from_cmdRegOut[portNum]
      //!
      Fw::InputCmdRegPort* get_from_cmdRegOut(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

      //! Get the port that receives input from statusOut
      //!
      //! \return from_statusOut[portNum]
      //!
      Drv::InputSphinxSPW_StatusOutPort* get_from_statusOut(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

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

      //! Get the port that receives input from cmdResponseOut
      //!
      //! \return from_cmdResponseOut[portNum]
      //!
      Fw::InputCmdResponsePort* get_from_cmdResponseOut(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

      //! Get the port that receives input from driverReset
      //!
      //! \return from_driverReset[portNum]
      //!
      Drv::InputSphinxSPW_StatusPort* get_from_driverReset(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

      //! Get the port that receives input from driverReadRMAP
      //!
      //! \return from_driverReadRMAP[portNum]
      //!
      Drv::InputSphinxSPW_ReadRMAPPort* get_from_driverReadRMAP(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

      //! Get the port that receives input from timeCaller
      //!
      //! \return from_timeCaller[portNum]
      //!
      Fw::InputTimePort* get_from_timeCaller(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

      //! Get the port that receives input from driverGetStatus
      //!
      //! \return from_driverGetStatus[portNum]
      //!
      Drv::InputSphinxSPW_StatusPort* get_from_driverGetStatus(
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

      //! Construct object SPWManagerTesterBase
      //!
      SPWManagerTesterBase(
#if FW_OBJECT_NAMES == 1
          const char *const compName, /*!< The component name*/
          const U32 maxHistorySize /*!< The maximum size of each history*/
#else
          const U32 maxHistorySize /*!< The maximum size of each history*/
#endif
      );

      //! Destroy object SPWManagerTesterBase
      //!
      virtual ~SPWManagerTesterBase(void);

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

      //! Handler prototype for from_driverWriteRMAP
      //!
      virtual I32 from_driverWriteRMAP_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          U8 dest_addr, 
          U8 dest_key, 
          U32 write_addr, 
          U8 *buf_ptr, 
          U32 num_bytes, 
          U8 increment, 
          U8 verify, 
          U8 acknowledge 
      ) = 0;

      //! Handler base function for from_driverWriteRMAP
      //!
      I32 from_driverWriteRMAP_handlerBase(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          U8 dest_addr, 
          U8 dest_key, 
          U32 write_addr, 
          U8 *buf_ptr, 
          U32 num_bytes, 
          U8 increment, 
          U8 verify, 
          U8 acknowledge 
      );

      //! Handler prototype for from_statusOut
      //!
      virtual void from_statusOut_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          I32 spwStatus 
      ) = 0;

      //! Handler base function for from_statusOut
      //!
      void from_statusOut_handlerBase(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          I32 spwStatus 
      );

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

      //! Handler prototype for from_driverReset
      //!
      virtual I32 from_driverReset_handler(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      ) = 0;

      //! Handler base function for from_driverReset
      //!
      I32 from_driverReset_handlerBase(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

      //! Handler prototype for from_driverReadRMAP
      //!
      virtual I32 from_driverReadRMAP_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          U8 dest_addr, 
          U8 dest_key, 
          U32 read_addr, 
          U8 *buf_ptr, 
          U32 num_bytes, 
          U8 increment 
      ) = 0;

      //! Handler base function for from_driverReadRMAP
      //!
      I32 from_driverReadRMAP_handlerBase(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          U8 dest_addr, 
          U8 dest_key, 
          U32 read_addr, 
          U8 *buf_ptr, 
          U32 num_bytes, 
          U8 increment 
      );

      //! Handler prototype for from_driverGetStatus
      //!
      virtual I32 from_driverGetStatus_handler(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      ) = 0;

      //! Handler base function for from_driverGetStatus
      //!
      I32 from_driverGetStatus_handlerBase(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
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

      //! Push an entry on the history for from_driverWriteRMAP
      void pushFromPortEntry_driverWriteRMAP(
          U8 dest_addr, 
          U8 dest_key, 
          U32 write_addr, 
          U8 *buf_ptr, 
          U32 num_bytes, 
          U8 increment, 
          U8 verify, 
          U8 acknowledge 
      );

      //! A history entry for from_driverWriteRMAP
      //!
      typedef struct {
        U8 dest_addr;
        U8 dest_key;
        U32 write_addr;
        U8 *buf_ptr;
        U32 num_bytes;
        U8 increment;
        U8 verify;
        U8 acknowledge;
      } FromPortEntry_driverWriteRMAP;

      //! The history for from_driverWriteRMAP
      //!
      History<FromPortEntry_driverWriteRMAP> 
        *fromPortHistory_driverWriteRMAP;

      //! Push an entry on the history for from_statusOut
      void pushFromPortEntry_statusOut(
          I32 spwStatus 
      );

      //! A history entry for from_statusOut
      //!
      typedef struct {
        I32 spwStatus;
      } FromPortEntry_statusOut;

      //! The history for from_statusOut
      //!
      History<FromPortEntry_statusOut> 
        *fromPortHistory_statusOut;

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

      //! Push an entry on the history for from_driverReset
      void pushFromPortEntry_driverReset(
          void
      );

      //! Size of history for from_driverReset
      //!
      U32 fromPortHistorySize_driverReset;

      //! Push an entry on the history for from_driverReadRMAP
      void pushFromPortEntry_driverReadRMAP(
          U8 dest_addr, 
          U8 dest_key, 
          U32 read_addr, 
          U8 *buf_ptr, 
          U32 num_bytes, 
          U8 increment 
      );

      //! A history entry for from_driverReadRMAP
      //!
      typedef struct {
        U8 dest_addr;
        U8 dest_key;
        U32 read_addr;
        U8 *buf_ptr;
        U32 num_bytes;
        U8 increment;
      } FromPortEntry_driverReadRMAP;

      //! The history for from_driverReadRMAP
      //!
      History<FromPortEntry_driverReadRMAP> 
        *fromPortHistory_driverReadRMAP;

      //! Push an entry on the history for from_driverGetStatus
      void pushFromPortEntry_driverGetStatus(
          void
      );

      //! Size of history for from_driverGetStatus
      //!
      U32 fromPortHistorySize_driverGetStatus;

    protected:

      // ----------------------------------------------------------------------
      // Invocation functions for to ports
      // ----------------------------------------------------------------------

      //! Invoke the to port connected to read
      //!
      I32 invoke_to_read(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          U32 addr, 
          U32 num_bytes, 
          U8 *buf, 
          U32 buf_size, 
          U32 timeout 
      );

      //! Invoke the to port connected to readAsyncDMA
      //!
      I32 invoke_to_readAsyncDMA(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          U32 addr, 
          U32 num_bytes, 
          U8 *buf, 
          U32 buf_size, 
          U32 timeout 
      );

      //! Invoke the to port connected to setParam
      //!
      I32 invoke_to_setParam(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          U8 dest_addr, 
          U8 dest_key, 
          U8 increment, 
          U8 verify, 
          U8 acknowledge 
      );

      //! Invoke the to port connected to PingRecv
      //!
      void invoke_to_PingRecv(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          U32 key /*!< Value to return to pinger*/
      );

      //! Invoke the to port connected to writeAsync
      //!
      I32 invoke_to_writeAsync(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          U32 addr, 
          U32 num_bytes, 
          U8 *buf, 
          U32 buf_size, 
          U32 timeout 
      );

      //! Invoke the to port connected to resetLink
      //!
      void invoke_to_resetLink(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

      //! Invoke the to port connected to schedIn
      //!
      void invoke_to_schedIn(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          NATIVE_UINT_TYPE context /*!< The call order*/
      );

      //! Invoke the to port connected to write
      //!
      I32 invoke_to_write(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          U32 addr, 
          U32 num_bytes, 
          U8 *buf, 
          U32 buf_size, 
          U32 timeout 
      );

      //! Invoke the to port connected to readAsync
      //!
      I32 invoke_to_readAsync(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          U32 addr, 
          U32 num_bytes, 
          U8 *buf, 
          U32 buf_size, 
          U32 timeout 
      );

    public:

      // ----------------------------------------------------------------------
      // Getters for port counts
      // ----------------------------------------------------------------------

      //! Get the number of to_read ports
      //!
      //! \return The number of to_read ports
      //!
      NATIVE_INT_TYPE getNum_to_read(void) const;

      //! Get the number of from_driverWriteRMAP ports
      //!
      //! \return The number of from_driverWriteRMAP ports
      //!
      NATIVE_INT_TYPE getNum_from_driverWriteRMAP(void) const;

      //! Get the number of from_cmdRegOut ports
      //!
      //! \return The number of from_cmdRegOut ports
      //!
      NATIVE_INT_TYPE getNum_from_cmdRegOut(void) const;

      //! Get the number of to_readAsyncDMA ports
      //!
      //! \return The number of to_readAsyncDMA ports
      //!
      NATIVE_INT_TYPE getNum_to_readAsyncDMA(void) const;

      //! Get the number of from_statusOut ports
      //!
      //! \return The number of from_statusOut ports
      //!
      NATIVE_INT_TYPE getNum_from_statusOut(void) const;

      //! Get the number of from_eventOut ports
      //!
      //! \return The number of from_eventOut ports
      //!
      NATIVE_INT_TYPE getNum_from_eventOut(void) const;

      //! Get the number of to_setParam ports
      //!
      //! \return The number of to_setParam ports
      //!
      NATIVE_INT_TYPE getNum_to_setParam(void) const;

      //! Get the number of from_PingResponse ports
      //!
      //! \return The number of from_PingResponse ports
      //!
      NATIVE_INT_TYPE getNum_from_PingResponse(void) const;

      //! Get the number of to_PingRecv ports
      //!
      //! \return The number of to_PingRecv ports
      //!
      NATIVE_INT_TYPE getNum_to_PingRecv(void) const;

      //! Get the number of from_cmdResponseOut ports
      //!
      //! \return The number of from_cmdResponseOut ports
      //!
      NATIVE_INT_TYPE getNum_from_cmdResponseOut(void) const;

      //! Get the number of from_driverReset ports
      //!
      //! \return The number of from_driverReset ports
      //!
      NATIVE_INT_TYPE getNum_from_driverReset(void) const;

      //! Get the number of from_driverReadRMAP ports
      //!
      //! \return The number of from_driverReadRMAP ports
      //!
      NATIVE_INT_TYPE getNum_from_driverReadRMAP(void) const;

      //! Get the number of to_writeAsync ports
      //!
      //! \return The number of to_writeAsync ports
      //!
      NATIVE_INT_TYPE getNum_to_writeAsync(void) const;

      //! Get the number of from_timeCaller ports
      //!
      //! \return The number of from_timeCaller ports
      //!
      NATIVE_INT_TYPE getNum_from_timeCaller(void) const;

      //! Get the number of to_resetLink ports
      //!
      //! \return The number of to_resetLink ports
      //!
      NATIVE_INT_TYPE getNum_to_resetLink(void) const;

      //! Get the number of to_schedIn ports
      //!
      //! \return The number of to_schedIn ports
      //!
      NATIVE_INT_TYPE getNum_to_schedIn(void) const;

      //! Get the number of to_cmdIn ports
      //!
      //! \return The number of to_cmdIn ports
      //!
      NATIVE_INT_TYPE getNum_to_cmdIn(void) const;

      //! Get the number of to_write ports
      //!
      //! \return The number of to_write ports
      //!
      NATIVE_INT_TYPE getNum_to_write(void) const;

      //! Get the number of to_readAsync ports
      //!
      //! \return The number of to_readAsync ports
      //!
      NATIVE_INT_TYPE getNum_to_readAsync(void) const;

      //! Get the number of from_driverGetStatus ports
      //!
      //! \return The number of from_driverGetStatus ports
      //!
      NATIVE_INT_TYPE getNum_from_driverGetStatus(void) const;

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
      //! Whether to_read[portNum] is connected
      //!
      bool isConnected_to_read(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

      //! Check whether port is connected
      //!
      //! Whether to_readAsyncDMA[portNum] is connected
      //!
      bool isConnected_to_readAsyncDMA(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

      //! Check whether port is connected
      //!
      //! Whether to_setParam[portNum] is connected
      //!
      bool isConnected_to_setParam(
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
      //! Whether to_writeAsync[portNum] is connected
      //!
      bool isConnected_to_writeAsync(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

      //! Check whether port is connected
      //!
      //! Whether to_resetLink[portNum] is connected
      //!
      bool isConnected_to_resetLink(
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
      //! Whether to_cmdIn[portNum] is connected
      //!
      bool isConnected_to_cmdIn(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

      //! Check whether port is connected
      //!
      //! Whether to_write[portNum] is connected
      //!
      bool isConnected_to_write(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

      //! Check whether port is connected
      //!
      //! Whether to_readAsync[portNum] is connected
      //!
      bool isConnected_to_readAsync(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

      // ----------------------------------------------------------------------
      // Functions for sending commands
      // ----------------------------------------------------------------------

    protected:
    
      // send command buffers directly - used for intentional command encoding errors
      void sendRawCmd(FwOpcodeType opcode, U32 cmdSeq, Fw::CmdArgBuffer& args); 

      //! Send a SPWMGR_RMAP_WRITE_WORD command
      //!
      void sendCmd_SPWMGR_RMAP_WRITE_WORD(
          const NATIVE_INT_TYPE instance, /*!< The instance number*/
          const U32 cmdSeq, /*!< The command sequence number*/
          U32 targetAddress, /*!< Address of target to write*/
          U32 value, /*!< Value to write*/
          U32 timeout /*!< Number of cycles to timeout request*/
      );

      //! Send a SPWMGR_RMAP_READ_WORD command
      //!
      void sendCmd_SPWMGR_RMAP_READ_WORD(
          const NATIVE_INT_TYPE instance, /*!< The instance number*/
          const U32 cmdSeq, /*!< The command sequence number*/
          U32 targetAddress, /*!< Address of target to read*/
          U32 timeout /*!< Number of cycles to timeout request*/
      );

      //! Send a SPWMGR_RESET_LINK command
      //!
      void sendCmd_SPWMGR_RESET_LINK(
          const NATIVE_INT_TYPE instance, /*!< The instance number*/
          const U32 cmdSeq /*!< The command sequence number*/
      );

      //! Send a SPWMGR_SET_PARAMS command
      //!
      void sendCmd_SPWMGR_SET_PARAMS(
          const NATIVE_INT_TYPE instance, /*!< The instance number*/
          const U32 cmdSeq, /*!< The command sequence number*/
          U8 destinationAddress, /*!< The destination node address*/
          U8 destinationKey, /*!< The destination node's RMAP key*/
          U8 increment, /*!< RMAP increment setting*/
          U8 verify, /*!< RMAP verify setting*/
          U8 acknowledge /*!< acknowledge*/
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
      // Event: SPWManager_SpaceWireInitializationError
      // ----------------------------------------------------------------------

      //! Handle event SPWManager_SpaceWireInitializationError
      //!
      virtual void logIn_WARNING_HI_SPWManager_SpaceWireInitializationError(
          I32 status /*!< Error status from SPWDriver*/
      );

      //! A history entry for event SPWManager_SpaceWireInitializationError
      //!
      typedef struct {
        I32 status;
      } EventEntry_SPWManager_SpaceWireInitializationError;

      //! The history of SPWManager_SpaceWireInitializationError events
      //!
      History<EventEntry_SPWManager_SpaceWireInitializationError> 
        *eventHistory_SPWManager_SpaceWireInitializationError;

    protected:

      // ----------------------------------------------------------------------
      // Event: SPWManager_SpaceWireLinkDisconnected
      // ----------------------------------------------------------------------

      //! Handle event SPWManager_SpaceWireLinkDisconnected
      //!
      virtual void logIn_WARNING_HI_SPWManager_SpaceWireLinkDisconnected(
          void
      );

      //! Size of history for event SPWManager_SpaceWireLinkDisconnected
      //!
      U32 eventsSize_SPWManager_SpaceWireLinkDisconnected;

    protected:

      // ----------------------------------------------------------------------
      // Event: SPWManager_SpaceWireError
      // ----------------------------------------------------------------------

      //! Handle event SPWManager_SpaceWireError
      //!
      virtual void logIn_WARNING_HI_SPWManager_SpaceWireError(
          SPWManagerComponentBase::SpaceWireError_status status, /*!< Status enum*/
          I32 statusCode /*!< Error status code from SPWDriver*/
      );

      //! A history entry for event SPWManager_SpaceWireError
      //!
      typedef struct {
        SPWManagerComponentBase::SpaceWireError_status status;
        I32 statusCode;
      } EventEntry_SPWManager_SpaceWireError;

      //! The history of SPWManager_SpaceWireError events
      //!
      History<EventEntry_SPWManager_SpaceWireError> 
        *eventHistory_SPWManager_SpaceWireError;

    protected:

      // ----------------------------------------------------------------------
      // Event: SPWManager_SpaceWireTransactionTimeout
      // ----------------------------------------------------------------------

      //! Handle event SPWManager_SpaceWireTransactionTimeout
      //!
      virtual void logIn_WARNING_HI_SPWManager_SpaceWireTransactionTimeout(
          U32 timeout, /*!< Timeout value*/
          SPWManagerComponentBase::SpaceWireTransactionTimeout_command command, /*!< Type of command*/
          U32 address, /*!< Target address to perform command on*/
          SPWManagerComponentBase::SpaceWireTransactionTimeout_status status /*!< State of transaction at timeout*/
      );

      //! A history entry for event SPWManager_SpaceWireTransactionTimeout
      //!
      typedef struct {
        U32 timeout;
        SPWManagerComponentBase::SpaceWireTransactionTimeout_command command;
        U32 address;
        SPWManagerComponentBase::SpaceWireTransactionTimeout_status status;
      } EventEntry_SPWManager_SpaceWireTransactionTimeout;

      //! The history of SPWManager_SpaceWireTransactionTimeout events
      //!
      History<EventEntry_SPWManager_SpaceWireTransactionTimeout> 
        *eventHistory_SPWManager_SpaceWireTransactionTimeout;

    protected:

      // ----------------------------------------------------------------------
      // Event: SPWManager_RMAPWriteResult
      // ----------------------------------------------------------------------

      //! Handle event SPWManager_RMAPWriteResult
      //!
      virtual void logIn_ACTIVITY_LO_SPWManager_RMAPWriteResult(
          U32 address /*!< Target address to perform command on*/
      );

      //! A history entry for event SPWManager_RMAPWriteResult
      //!
      typedef struct {
        U32 address;
      } EventEntry_SPWManager_RMAPWriteResult;

      //! The history of SPWManager_RMAPWriteResult events
      //!
      History<EventEntry_SPWManager_RMAPWriteResult> 
        *eventHistory_SPWManager_RMAPWriteResult;

    protected:

      // ----------------------------------------------------------------------
      // Event: SPWManager_RMAPReadResult
      // ----------------------------------------------------------------------

      //! Handle event SPWManager_RMAPReadResult
      //!
      virtual void logIn_ACTIVITY_LO_SPWManager_RMAPReadResult(
          U32 address, /*!< Target address to perform command on*/
          U32 value /*!< Value returned from read*/
      );

      //! A history entry for event SPWManager_RMAPReadResult
      //!
      typedef struct {
        U32 address;
        U32 value;
      } EventEntry_SPWManager_RMAPReadResult;

      //! The history of SPWManager_RMAPReadResult events
      //!
      History<EventEntry_SPWManager_RMAPReadResult> 
        *eventHistory_SPWManager_RMAPReadResult;

    protected:

      // ----------------------------------------------------------------------
      // Event: SPWManager_Busy
      // ----------------------------------------------------------------------

      //! Handle event SPWManager_Busy
      //!
      virtual void logIn_WARNING_LO_SPWManager_Busy(
          void
      );

      //! Size of history for event SPWManager_Busy
      //!
      U32 eventsSize_SPWManager_Busy;

    protected:

      // ----------------------------------------------------------------------
      // Event: SPWManager_ResetLink
      // ----------------------------------------------------------------------

      //! Handle event SPWManager_ResetLink
      //!
      virtual void logIn_ACTIVITY_LO_SPWManager_ResetLink(
          U32 numAborted /*!< Number of async requests aborted*/
      );

      //! A history entry for event SPWManager_ResetLink
      //!
      typedef struct {
        U32 numAborted;
      } EventEntry_SPWManager_ResetLink;

      //! The history of SPWManager_ResetLink events
      //!
      History<EventEntry_SPWManager_ResetLink> 
        *eventHistory_SPWManager_ResetLink;

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

      //! To port connected to read
      //!
      Drv::OutputSphinxSPW_SendRequestPort m_to_read[1];

      //! To port connected to readAsyncDMA
      //!
      Drv::OutputSphinxSPW_SendRequestPort m_to_readAsyncDMA[1];

      //! To port connected to setParam
      //!
      Drv::OutputSphinxSPW_SetParamPort m_to_setParam[1];

      //! To port connected to PingRecv
      //!
      Svc::OutputPingPort m_to_PingRecv[1];

      //! To port connected to writeAsync
      //!
      Drv::OutputSphinxSPW_SendRequestPort m_to_writeAsync[1];

      //! To port connected to resetLink
      //!
      Drv::OutputSphinxSPW_TriggerPort m_to_resetLink[1];

      //! To port connected to schedIn
      //!
      Svc::OutputSchedPort m_to_schedIn[1];

      //! To port connected to cmdIn
      //!
      Fw::OutputCmdPort m_to_cmdIn[1];

      //! To port connected to write
      //!
      Drv::OutputSphinxSPW_SendRequestPort m_to_write[1];

      //! To port connected to readAsync
      //!
      Drv::OutputSphinxSPW_SendRequestPort m_to_readAsync[1];

    private:

      // ----------------------------------------------------------------------
      // From ports
      // ----------------------------------------------------------------------

      //! From port connected to driverWriteRMAP
      //!
      Drv::InputSphinxSPW_WriteRMAPPort m_from_driverWriteRMAP[1];

      //! From port connected to cmdRegOut
      //!
      Fw::InputCmdRegPort m_from_cmdRegOut[1];

      //! From port connected to statusOut
      //!
      Drv::InputSphinxSPW_StatusOutPort m_from_statusOut[1];

      //! From port connected to eventOut
      //!
      Fw::InputLogPort m_from_eventOut[1];

      //! From port connected to PingResponse
      //!
      Svc::InputPingPort m_from_PingResponse[1];

      //! From port connected to cmdResponseOut
      //!
      Fw::InputCmdResponsePort m_from_cmdResponseOut[1];

      //! From port connected to driverReset
      //!
      Drv::InputSphinxSPW_StatusPort m_from_driverReset[1];

      //! From port connected to driverReadRMAP
      //!
      Drv::InputSphinxSPW_ReadRMAPPort m_from_driverReadRMAP[1];

      //! From port connected to timeCaller
      //!
      Fw::InputTimePort m_from_timeCaller[1];

      //! From port connected to driverGetStatus
      //!
      Drv::InputSphinxSPW_StatusPort m_from_driverGetStatus[1];

#if FW_ENABLE_TEXT_LOGGING == 1
      //! From port connected to LogText
      //!
      Fw::InputLogTextPort m_from_LogText[1];
#endif

    private:

      // ----------------------------------------------------------------------
      // Static functions for output ports
      // ----------------------------------------------------------------------

      //! Static function for port from_driverWriteRMAP
      //!
      static I32 from_driverWriteRMAP_static(
          Fw::PassiveComponentBase *const callComp, /*!< The component instance*/
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          U8 dest_addr, 
          U8 dest_key, 
          U32 write_addr, 
          U8 *buf_ptr, 
          U32 num_bytes, 
          U8 increment, 
          U8 verify, 
          U8 acknowledge 
      );

      //! Static function for port from_cmdRegOut
      //!
      static void from_cmdRegOut_static(
          Fw::PassiveComponentBase *const callComp, /*!< The component instance*/
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          FwOpcodeType opCode /*!< Command Op Code*/
      );

      //! Static function for port from_statusOut
      //!
      static void from_statusOut_static(
          Fw::PassiveComponentBase *const callComp, /*!< The component instance*/
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          I32 spwStatus 
      );

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

      //! Static function for port from_cmdResponseOut
      //!
      static void from_cmdResponseOut_static(
          Fw::PassiveComponentBase *const callComp, /*!< The component instance*/
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          FwOpcodeType opCode, /*!< Command Op Code*/
          U32 cmdSeq, /*!< Command Sequence*/
          Fw::CommandResponse response /*!< The command response argument*/
      );

      //! Static function for port from_driverReset
      //!
      static I32 from_driverReset_static(
          Fw::PassiveComponentBase *const callComp, /*!< The component instance*/
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

      //! Static function for port from_driverReadRMAP
      //!
      static I32 from_driverReadRMAP_static(
          Fw::PassiveComponentBase *const callComp, /*!< The component instance*/
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          U8 dest_addr, 
          U8 dest_key, 
          U32 read_addr, 
          U8 *buf_ptr, 
          U32 num_bytes, 
          U8 increment 
      );

      //! Static function for port from_timeCaller
      //!
      static void from_timeCaller_static(
          Fw::PassiveComponentBase *const callComp, /*!< The component instance*/
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          Fw::Time &time /*!< The U32 cmd argument*/
      );

      //! Static function for port from_driverGetStatus
      //!
      static I32 from_driverGetStatus_static(
          Fw::PassiveComponentBase *const callComp, /*!< The component instance*/
          const NATIVE_INT_TYPE portNum /*!< The port number*/
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
