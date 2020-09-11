// ======================================================================
// \title  FPGADriver/test/ut/TesterBase.hpp
// \author Auto-generated
// \brief  hpp file for FPGADriver component test harness base class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
// ======================================================================

#ifndef FPGADriver_TESTER_BASE_HPP
#define FPGADriver_TESTER_BASE_HPP

#include <fprime-sphinx-drivers/FPGADriver/FPGADriverComponentAc.hpp>
#include <Fw/Types/Assert.hpp>
#include <Fw/Comp/PassiveComponentBase.hpp>
#include <stdio.h>
#include <Fw/Port/InputSerializePort.hpp>

namespace Drv {

  //! \class FPGADriverTesterBase
  //! \brief Auto-generated base class for FPGADriver component test harness
  //!
  class FPGADriverTesterBase :
    public Fw::PassiveComponentBase
  {

    public:

      // ----------------------------------------------------------------------
      // Initialization
      // ----------------------------------------------------------------------

      //! Initialize object FPGADriverTesterBase
      //!
      virtual void init(
          const NATIVE_INT_TYPE instance = 0 /*!< The instance number*/
      );

    public:

      // ----------------------------------------------------------------------
      // Connectors for 'to' ports
      // Connect these output ports to the input ports under test
      // ----------------------------------------------------------------------

      //! Connect read_reg to to_read_reg[portNum]
      //!
      void connect_to_read_reg(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          Drv::InputSphinxRegReadPort *const read_reg /*!< The port*/
      );

      //! Connect write_reg to to_write_reg[portNum]
      //!
      void connect_to_write_reg(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          Drv::InputSphinxRegWritePort *const write_reg /*!< The port*/
      );

    public:

      // ----------------------------------------------------------------------
      // Getters for 'from' ports
      // Connect these input ports to the output ports under test
      // ----------------------------------------------------------------------

      //! Get the port that receives input from timeRTIOut
      //!
      //! \return from_timeRTIOut[portNum]
      //!
      Svc::InputSchedPort* get_from_timeRTIOut(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

      //! Get the port that receives input from cycleOut
      //!
      //! \return from_cycleOut[portNum]
      //!
      Svc::InputCyclePort* get_from_cycleOut(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

    protected:

      // ----------------------------------------------------------------------
      // Construction and destruction
      // ----------------------------------------------------------------------

      //! Construct object FPGADriverTesterBase
      //!
      FPGADriverTesterBase(
#if FW_OBJECT_NAMES == 1
          const char *const compName, /*!< The component name*/
          const U32 maxHistorySize /*!< The maximum size of each history*/
#else
          const U32 maxHistorySize /*!< The maximum size of each history*/
#endif
      );

      //! Destroy object FPGADriverTesterBase
      //!
      virtual ~FPGADriverTesterBase(void);

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

      //! Handler prototype for from_timeRTIOut
      //!
      virtual void from_timeRTIOut_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          NATIVE_UINT_TYPE context /*!< The call order*/
      ) = 0;

      //! Handler base function for from_timeRTIOut
      //!
      void from_timeRTIOut_handlerBase(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          NATIVE_UINT_TYPE context /*!< The call order*/
      );

      //! Handler prototype for from_cycleOut
      //!
      virtual void from_cycleOut_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          Svc::TimerVal &cycleStart /*!< Cycle start timer value*/
      ) = 0;

      //! Handler base function for from_cycleOut
      //!
      void from_cycleOut_handlerBase(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          Svc::TimerVal &cycleStart /*!< Cycle start timer value*/
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

      //! Push an entry on the history for from_timeRTIOut
      void pushFromPortEntry_timeRTIOut(
          NATIVE_UINT_TYPE context /*!< The call order*/
      );

      //! A history entry for from_timeRTIOut
      //!
      typedef struct {
        NATIVE_UINT_TYPE context;
      } FromPortEntry_timeRTIOut;

      //! The history for from_timeRTIOut
      //!
      History<FromPortEntry_timeRTIOut> 
        *fromPortHistory_timeRTIOut;

      //! Push an entry on the history for from_cycleOut
      void pushFromPortEntry_cycleOut(
          Svc::TimerVal &cycleStart /*!< Cycle start timer value*/
      );

      //! A history entry for from_cycleOut
      //!
      typedef struct {
        Svc::TimerVal cycleStart;
      } FromPortEntry_cycleOut;

      //! The history for from_cycleOut
      //!
      History<FromPortEntry_cycleOut> 
        *fromPortHistory_cycleOut;

    protected:

      // ----------------------------------------------------------------------
      // Invocation functions for to ports
      // ----------------------------------------------------------------------

      //! Invoke the to port connected to read_reg
      //!
      I32 invoke_to_read_reg(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          U32 offset, 
          U32 &value 
      );

      //! Invoke the to port connected to write_reg
      //!
      I32 invoke_to_write_reg(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          U32 offset, 
          U32 value 
      );

    public:

      // ----------------------------------------------------------------------
      // Getters for port counts
      // ----------------------------------------------------------------------

      //! Get the number of to_read_reg ports
      //!
      //! \return The number of to_read_reg ports
      //!
      NATIVE_INT_TYPE getNum_to_read_reg(void) const;

      //! Get the number of to_write_reg ports
      //!
      //! \return The number of to_write_reg ports
      //!
      NATIVE_INT_TYPE getNum_to_write_reg(void) const;

      //! Get the number of from_timeRTIOut ports
      //!
      //! \return The number of from_timeRTIOut ports
      //!
      NATIVE_INT_TYPE getNum_from_timeRTIOut(void) const;

      //! Get the number of from_cycleOut ports
      //!
      //! \return The number of from_cycleOut ports
      //!
      NATIVE_INT_TYPE getNum_from_cycleOut(void) const;

    protected:

      // ----------------------------------------------------------------------
      // Connection status for to ports
      // ----------------------------------------------------------------------

      //! Check whether port is connected
      //!
      //! Whether to_read_reg[portNum] is connected
      //!
      bool isConnected_to_read_reg(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

      //! Check whether port is connected
      //!
      //! Whether to_write_reg[portNum] is connected
      //!
      bool isConnected_to_write_reg(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

    private:

      // ----------------------------------------------------------------------
      // To ports
      // ----------------------------------------------------------------------

      //! To port connected to read_reg
      //!
      Drv::OutputSphinxRegReadPort m_to_read_reg[1];

      //! To port connected to write_reg
      //!
      Drv::OutputSphinxRegWritePort m_to_write_reg[1];

    private:

      // ----------------------------------------------------------------------
      // From ports
      // ----------------------------------------------------------------------

      //! From port connected to timeRTIOut
      //!
      Svc::InputSchedPort m_from_timeRTIOut[1];

      //! From port connected to cycleOut
      //!
      Svc::InputCyclePort m_from_cycleOut[1];

    private:

      // ----------------------------------------------------------------------
      // Static functions for output ports
      // ----------------------------------------------------------------------

      //! Static function for port from_timeRTIOut
      //!
      static void from_timeRTIOut_static(
          Fw::PassiveComponentBase *const callComp, /*!< The component instance*/
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          NATIVE_UINT_TYPE context /*!< The call order*/
      );

      //! Static function for port from_cycleOut
      //!
      static void from_cycleOut_static(
          Fw::PassiveComponentBase *const callComp, /*!< The component instance*/
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          Svc::TimerVal &cycleStart /*!< Cycle start timer value*/
      );

  };

} // end namespace Drv

#endif
