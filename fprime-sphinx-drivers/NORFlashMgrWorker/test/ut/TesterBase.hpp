// ======================================================================
// \title  NORFlashMgrWorker/test/ut/TesterBase.hpp
// \author Auto-generated
// \brief  hpp file for NORFlashMgrWorker component test harness base class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
// ======================================================================

#ifndef NORFlashMgrWorker_TESTER_BASE_HPP
#define NORFlashMgrWorker_TESTER_BASE_HPP

#include <fprime-sphinx-drivers/NORFlashMgrWorker/NORFlashMgrWorkerComponentAc.hpp>
#include <Fw/Types/Assert.hpp>
#include <Fw/Comp/PassiveComponentBase.hpp>
#include <stdio.h>
#include <Fw/Port/InputSerializePort.hpp>

namespace Drv {

  //! \class NORFlashMgrWorkerTesterBase
  //! \brief Auto-generated base class for NORFlashMgrWorker component test harness
  //!
  class NORFlashMgrWorkerTesterBase :
    public Fw::PassiveComponentBase
  {

    public:

      // ----------------------------------------------------------------------
      // Initialization
      // ----------------------------------------------------------------------

      //! Initialize object NORFlashMgrWorkerTesterBase
      //!
      virtual void init(
          const NATIVE_INT_TYPE instance = 0 /*!< The instance number*/
      );

    public:

      // ----------------------------------------------------------------------
      // Connectors for 'to' ports
      // Connect these output ports to the input ports under test
      // ----------------------------------------------------------------------

      //! Connect cancel to to_cancel[portNum]
      //!
      void connect_to_cancel(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          Drv::InputNORFlash_CancelPort *const cancel /*!< The port*/
      );

      //! Connect erase to to_erase[portNum]
      //!
      void connect_to_erase(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          Drv::InputNORFlash_EraseBankAddrPort *const erase /*!< The port*/
      );

      //! Connect reset to to_reset[portNum]
      //!
      void connect_to_reset(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          Drv::InputNORFlash_ResetPort *const reset /*!< The port*/
      );

      //! Connect verify to to_verify[portNum]
      //!
      void connect_to_verify(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          Drv::InputNORFlash_VerifyPort *const verify /*!< The port*/
      );

      //! Connect write_block to to_write_block[portNum]
      //!
      void connect_to_write_block(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          Drv::InputNORFlash_BWPort *const write_block /*!< The port*/
      );

      //! Connect read_block to to_read_block[portNum]
      //!
      void connect_to_read_block(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          Drv::InputNORFlash_BRPort *const read_block /*!< The port*/
      );

    public:

      // ----------------------------------------------------------------------
      // Getters for 'from' ports
      // Connect these input ports to the output ports under test
      // ----------------------------------------------------------------------

      //! Get the port that receives input from read
      //!
      //! \return from_read[portNum]
      //!
      Drv::InputNORFlash_ReadBPort* get_from_read(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

      //! Get the port that receives input from statusOut
      //!
      //! \return from_statusOut[portNum]
      //!
      Drv::InputNOR_donePort* get_from_statusOut(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

      //! Get the port that receives input from write
      //!
      //! \return from_write[portNum]
      //!
      Drv::InputNORFlash_WriteBPort* get_from_write(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

    protected:

      // ----------------------------------------------------------------------
      // Construction and destruction
      // ----------------------------------------------------------------------

      //! Construct object NORFlashMgrWorkerTesterBase
      //!
      NORFlashMgrWorkerTesterBase(
#if FW_OBJECT_NAMES == 1
          const char *const compName, /*!< The component name*/
          const U32 maxHistorySize /*!< The maximum size of each history*/
#else
          const U32 maxHistorySize /*!< The maximum size of each history*/
#endif
      );

      //! Destroy object NORFlashMgrWorkerTesterBase
      //!
      virtual ~NORFlashMgrWorkerTesterBase(void);

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

      //! Handler prototype for from_read
      //!
      virtual I8 from_read_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          U32 dest, 
          U8 *data 
      ) = 0;

      //! Handler base function for from_read
      //!
      I8 from_read_handlerBase(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          U32 dest, 
          U8 *data 
      );

      //! Handler prototype for from_statusOut
      //!
      virtual void from_statusOut_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          I8 done, 
          U32 context1, 
          U32 context2 
      ) = 0;

      //! Handler base function for from_statusOut
      //!
      void from_statusOut_handlerBase(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          I8 done, 
          U32 context1, 
          U32 context2 
      );

      //! Handler prototype for from_write
      //!
      virtual I8 from_write_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          U32 dest_addr, 
          U8 src 
      ) = 0;

      //! Handler base function for from_write
      //!
      I8 from_write_handlerBase(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          U32 dest_addr, 
          U8 src 
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

      //! Push an entry on the history for from_read
      void pushFromPortEntry_read(
          U32 dest, 
          U8 *data 
      );

      //! A history entry for from_read
      //!
      typedef struct {
        U32 dest;
        U8 *data;
      } FromPortEntry_read;

      //! The history for from_read
      //!
      History<FromPortEntry_read> 
        *fromPortHistory_read;

      //! Push an entry on the history for from_statusOut
      void pushFromPortEntry_statusOut(
          I8 done, 
          U32 context1, 
          U32 context2 
      );

      //! A history entry for from_statusOut
      //!
      typedef struct {
        I8 done;
        U32 context1;
        U32 context2;
      } FromPortEntry_statusOut;

      //! The history for from_statusOut
      //!
      History<FromPortEntry_statusOut> 
        *fromPortHistory_statusOut;

      //! Push an entry on the history for from_write
      void pushFromPortEntry_write(
          U32 dest_addr, 
          U8 src 
      );

      //! A history entry for from_write
      //!
      typedef struct {
        U32 dest_addr;
        U8 src;
      } FromPortEntry_write;

      //! The history for from_write
      //!
      History<FromPortEntry_write> 
        *fromPortHistory_write;

    protected:

      // ----------------------------------------------------------------------
      // Invocation functions for to ports
      // ----------------------------------------------------------------------

      //! Invoke the to port connected to cancel
      //!
      void invoke_to_cancel(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

      //! Invoke the to port connected to erase
      //!
      void invoke_to_erase(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          U32 bank_addr 
      );

      //! Invoke the to port connected to reset
      //!
      void invoke_to_reset(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          U32 dontcare_addr 
      );

      //! Invoke the to port connected to verify
      //!
      void invoke_to_verify(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          U32 blc_filesize, 
          U32 fsw_filesize 
      );

      //! Invoke the to port connected to write_block
      //!
      void invoke_to_write_block(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          U32 dest, 
          U8 *src, 
          U32 count, 
          U32 bank 
      );

      //! Invoke the to port connected to read_block
      //!
      void invoke_to_read_block(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          U8 *dest, 
          U32 src, 
          U32 count, 
          U32 bank 
      );

    public:

      // ----------------------------------------------------------------------
      // Getters for port counts
      // ----------------------------------------------------------------------

      //! Get the number of to_cancel ports
      //!
      //! \return The number of to_cancel ports
      //!
      NATIVE_INT_TYPE getNum_to_cancel(void) const;

      //! Get the number of to_erase ports
      //!
      //! \return The number of to_erase ports
      //!
      NATIVE_INT_TYPE getNum_to_erase(void) const;

      //! Get the number of from_read ports
      //!
      //! \return The number of from_read ports
      //!
      NATIVE_INT_TYPE getNum_from_read(void) const;

      //! Get the number of from_statusOut ports
      //!
      //! \return The number of from_statusOut ports
      //!
      NATIVE_INT_TYPE getNum_from_statusOut(void) const;

      //! Get the number of to_reset ports
      //!
      //! \return The number of to_reset ports
      //!
      NATIVE_INT_TYPE getNum_to_reset(void) const;

      //! Get the number of to_verify ports
      //!
      //! \return The number of to_verify ports
      //!
      NATIVE_INT_TYPE getNum_to_verify(void) const;

      //! Get the number of to_write_block ports
      //!
      //! \return The number of to_write_block ports
      //!
      NATIVE_INT_TYPE getNum_to_write_block(void) const;

      //! Get the number of from_write ports
      //!
      //! \return The number of from_write ports
      //!
      NATIVE_INT_TYPE getNum_from_write(void) const;

      //! Get the number of to_read_block ports
      //!
      //! \return The number of to_read_block ports
      //!
      NATIVE_INT_TYPE getNum_to_read_block(void) const;

    protected:

      // ----------------------------------------------------------------------
      // Connection status for to ports
      // ----------------------------------------------------------------------

      //! Check whether port is connected
      //!
      //! Whether to_cancel[portNum] is connected
      //!
      bool isConnected_to_cancel(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

      //! Check whether port is connected
      //!
      //! Whether to_erase[portNum] is connected
      //!
      bool isConnected_to_erase(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

      //! Check whether port is connected
      //!
      //! Whether to_reset[portNum] is connected
      //!
      bool isConnected_to_reset(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

      //! Check whether port is connected
      //!
      //! Whether to_verify[portNum] is connected
      //!
      bool isConnected_to_verify(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

      //! Check whether port is connected
      //!
      //! Whether to_write_block[portNum] is connected
      //!
      bool isConnected_to_write_block(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

      //! Check whether port is connected
      //!
      //! Whether to_read_block[portNum] is connected
      //!
      bool isConnected_to_read_block(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

    private:

      // ----------------------------------------------------------------------
      // To ports
      // ----------------------------------------------------------------------

      //! To port connected to cancel
      //!
      Drv::OutputNORFlash_CancelPort m_to_cancel[1];

      //! To port connected to erase
      //!
      Drv::OutputNORFlash_EraseBankAddrPort m_to_erase[1];

      //! To port connected to reset
      //!
      Drv::OutputNORFlash_ResetPort m_to_reset[1];

      //! To port connected to verify
      //!
      Drv::OutputNORFlash_VerifyPort m_to_verify[1];

      //! To port connected to write_block
      //!
      Drv::OutputNORFlash_BWPort m_to_write_block[1];

      //! To port connected to read_block
      //!
      Drv::OutputNORFlash_BRPort m_to_read_block[1];

    private:

      // ----------------------------------------------------------------------
      // From ports
      // ----------------------------------------------------------------------

      //! From port connected to read
      //!
      Drv::InputNORFlash_ReadBPort m_from_read[1];

      //! From port connected to statusOut
      //!
      Drv::InputNOR_donePort m_from_statusOut[1];

      //! From port connected to write
      //!
      Drv::InputNORFlash_WriteBPort m_from_write[1];

    private:

      // ----------------------------------------------------------------------
      // Static functions for output ports
      // ----------------------------------------------------------------------

      //! Static function for port from_read
      //!
      static I8 from_read_static(
          Fw::PassiveComponentBase *const callComp, /*!< The component instance*/
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          U32 dest, 
          U8 *data 
      );

      //! Static function for port from_statusOut
      //!
      static void from_statusOut_static(
          Fw::PassiveComponentBase *const callComp, /*!< The component instance*/
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          I8 done, 
          U32 context1, 
          U32 context2 
      );

      //! Static function for port from_write
      //!
      static I8 from_write_static(
          Fw::PassiveComponentBase *const callComp, /*!< The component instance*/
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          U32 dest_addr, 
          U8 src 
      );

  };

} // end namespace Drv

#endif
