// ======================================================================
// \title  FPGASPIDriver/test/ut/TesterBase.hpp
// \author Auto-generated
// \brief  hpp file for FPGASPIDriver component test harness base class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
// ======================================================================

#ifndef FPGASPIDriver_TESTER_BASE_HPP
#define FPGASPIDriver_TESTER_BASE_HPP

#include <fprime-sphinx-drivers/FPGASPIDriver/FPGASPIDriverComponentAc.hpp>
#include <Fw/Types/Assert.hpp>
#include <Fw/Comp/PassiveComponentBase.hpp>
#include <stdio.h>
#include <Fw/Port/InputSerializePort.hpp>

namespace Drv {

  //! \class FPGASPIDriverTesterBase
  //! \brief Auto-generated base class for FPGASPIDriver component test harness
  //!
  class FPGASPIDriverTesterBase :
    public Fw::PassiveComponentBase
  {

    public:

      // ----------------------------------------------------------------------
      // Initialization
      // ----------------------------------------------------------------------

      //! Initialize object FPGASPIDriverTesterBase
      //!
      virtual void init(
          const NATIVE_INT_TYPE instance = 0 /*!< The instance number*/
      );

    public:

      // ----------------------------------------------------------------------
      // Connectors for 'to' ports
      // Connect these output ports to the input ports under test
      // ----------------------------------------------------------------------

      //! Connect read_write to to_read_write[portNum]
      //!
      void connect_to_read_write(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          Drv::InputSphinxFPGASPI_RWPort *const read_write /*!< The port*/
      );

    public:

      // ----------------------------------------------------------------------
      // Getters for 'from' ports
      // Connect these input ports to the output ports under test
      // ----------------------------------------------------------------------

      //! Get the port that receives input from Time
      //!
      //! \return from_Time[portNum]
      //!
      Fw::InputTimePort* get_from_Time(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

    protected:

      // ----------------------------------------------------------------------
      // Construction and destruction
      // ----------------------------------------------------------------------

      //! Construct object FPGASPIDriverTesterBase
      //!
      FPGASPIDriverTesterBase(
#if FW_OBJECT_NAMES == 1
          const char *const compName, /*!< The component name*/
          const U32 maxHistorySize /*!< The maximum size of each history*/
#else
          const U32 maxHistorySize /*!< The maximum size of each history*/
#endif
      );

      //! Destroy object FPGASPIDriverTesterBase
      //!
      virtual ~FPGASPIDriverTesterBase(void);

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

      //! Handler prototype for from_Time
      //!
      virtual void from_Time_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          Fw::Time &time /*!< The U32 cmd argument*/
      ) = 0;

      //! Handler base function for from_Time
      //!
      void from_Time_handlerBase(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          Fw::Time &time /*!< The U32 cmd argument*/
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

      //! Push an entry on the history for from_Time
      void pushFromPortEntry_Time(
          Fw::Time &time /*!< The U32 cmd argument*/
      );

      //! A history entry for from_Time
      //!
      typedef struct {
        Fw::Time time;
      } FromPortEntry_Time;

      //! The history for from_Time
      //!
      History<FromPortEntry_Time> 
        *fromPortHistory_Time;

    protected:
      // ----------------------------------------------------------------------
      // Test time
      // ---------------------------------------------------------------------- 

      //! Set the test time for events and telemetry                                              
      //!                                
    void setTestTime(
        const Fw::Time& timeTag /*!< The time*/
    );

    protected:

      // ----------------------------------------------------------------------
      // Invocation functions for to ports
      // ----------------------------------------------------------------------

      //! Invoke the to port connected to read_write
      //!
      I32 invoke_to_read_write(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          U8 *write_buf_ptr, 
          U8 *read_buf_ptr, 
          U32 nBytes, 
          U8 activate_slave, 
          U16 timeout, 
          U8 clock_bitrate, 
          U8 bit_order, 
          U32 delay 
      );

    public:

      // ----------------------------------------------------------------------
      // Getters for port counts
      // ----------------------------------------------------------------------

      //! Get the number of to_read_write ports
      //!
      //! \return The number of to_read_write ports
      //!
      NATIVE_INT_TYPE getNum_to_read_write(void) const;

      //! Get the number of from_Time ports
      //!
      //! \return The number of from_Time ports
      //!
      NATIVE_INT_TYPE getNum_from_Time(void) const;

    protected:

      // ----------------------------------------------------------------------
      // Connection status for to ports
      // ----------------------------------------------------------------------

      //! Check whether port is connected
      //!
      //! Whether to_read_write[portNum] is connected
      //!
      bool isConnected_to_read_write(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

    private:

      // ----------------------------------------------------------------------
      // To ports
      // ----------------------------------------------------------------------

      //! To port connected to read_write
      //!
      Drv::OutputSphinxFPGASPI_RWPort m_to_read_write[1];

    private:

      // ----------------------------------------------------------------------
      // From ports
      // ----------------------------------------------------------------------

      //! From port connected to Time
      //!
      Fw::InputTimePort m_from_Time[1];

    private:

      // ----------------------------------------------------------------------
      // Static functions for output ports
      // ----------------------------------------------------------------------

      //! Static function for port from_Time
      //!
      static void from_Time_static(
          Fw::PassiveComponentBase *const callComp, /*!< The component instance*/
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          Fw::Time &time /*!< The U32 cmd argument*/
      );

      Fw::Time m_testTime;

  };

} // end namespace Drv

#endif
