// ======================================================================
// \title  SPIDriverGeneric/test/ut/TesterBase.hpp
// \author Auto-generated
// \brief  hpp file for SPIDriverGeneric component test harness base class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
// ======================================================================

#ifndef SPIDriverGeneric_TESTER_BASE_HPP
#define SPIDriverGeneric_TESTER_BASE_HPP

#include <fprime-sphinx-drivers/SPIDriverGeneric/SPIDriverGenericComponentAc.hpp>
#include <Fw/Types/Assert.hpp>
#include <Fw/Comp/PassiveComponentBase.hpp>
#include <stdio.h>
#include <Fw/Port/InputSerializePort.hpp>

namespace Drv {

  //! \class SPIDriverGenericTesterBase
  //! \brief Auto-generated base class for SPIDriverGeneric component test harness
  //!
  class SPIDriverGenericTesterBase :
    public Fw::PassiveComponentBase
  {

    public:

      // ----------------------------------------------------------------------
      // Initialization
      // ----------------------------------------------------------------------

      //! Initialize object SPIDriverGenericTesterBase
      //!
      virtual void init(
          const NATIVE_INT_TYPE instance = 0 /*!< The instance number*/
      );

    public:

      // ----------------------------------------------------------------------
      // Connectors for 'to' ports
      // Connect these output ports to the input ports under test
      // ----------------------------------------------------------------------

      //! Connect spi_unclaim to to_spi_unclaim[portNum]
      //!
      void connect_to_spi_unclaim(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          Drv::InputSphinxSPI_UnclaimPort *const spi_unclaim /*!< The port*/
      );

      //! Connect read_write_16 to to_read_write_16[portNum]
      //!
      void connect_to_read_write_16(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          Drv::InputSphinxSPI_RW16_GenericPort *const read_write_16 /*!< The port*/
      );

      //! Connect read_write_32 to to_read_write_32[portNum]
      //!
      void connect_to_read_write_32(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          Drv::InputSphinxSPI_RW32_GenericPort *const read_write_32 /*!< The port*/
      );

      //! Connect spi_claim to to_spi_claim[portNum]
      //!
      void connect_to_spi_claim(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          Drv::InputSphinxSPI_ClaimPort *const spi_claim /*!< The port*/
      );

      //! Connect spi_configure to to_spi_configure[portNum]
      //!
      void connect_to_spi_configure(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          Drv::InputSphinxSPI_ConfigurePort *const spi_configure /*!< The port*/
      );

      //! Connect read_write_8 to to_read_write_8[portNum]
      //!
      void connect_to_read_write_8(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          Drv::InputSphinxSPI_RW_GenericPort *const read_write_8 /*!< The port*/
      );

    public:

      // ----------------------------------------------------------------------
      // Getters for 'from' ports
      // Connect these input ports to the output ports under test
      // ----------------------------------------------------------------------

      //! Get the port that receives input from timeCaller
      //!
      //! \return from_timeCaller[portNum]
      //!
      Fw::InputTimePort* get_from_timeCaller(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

    protected:

      // ----------------------------------------------------------------------
      // Construction and destruction
      // ----------------------------------------------------------------------

      //! Construct object SPIDriverGenericTesterBase
      //!
      SPIDriverGenericTesterBase(
#if FW_OBJECT_NAMES == 1
          const char *const compName, /*!< The component name*/
          const U32 maxHistorySize /*!< The maximum size of each history*/
#else
          const U32 maxHistorySize /*!< The maximum size of each history*/
#endif
      );

      //! Destroy object SPIDriverGenericTesterBase
      //!
      virtual ~SPIDriverGenericTesterBase(void);

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

      //! Handler prototype for from_timeCaller
      //!
      virtual void from_timeCaller_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          Fw::Time &time /*!< The U32 cmd argument*/
      ) = 0;

      //! Handler base function for from_timeCaller
      //!
      void from_timeCaller_handlerBase(
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

      //! Push an entry on the history for from_timeCaller
      void pushFromPortEntry_timeCaller(
          Fw::Time &time /*!< The U32 cmd argument*/
      );

      //! A history entry for from_timeCaller
      //!
      typedef struct {
        Fw::Time time;
      } FromPortEntry_timeCaller;

      //! The history for from_timeCaller
      //!
      History<FromPortEntry_timeCaller> 
        *fromPortHistory_timeCaller;

    protected:

      // ----------------------------------------------------------------------
      // Invocation functions for to ports
      // ----------------------------------------------------------------------

      //! Invoke the to port connected to spi_unclaim
      //!
      I32 invoke_to_spi_unclaim(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

      //! Invoke the to port connected to read_write_16
      //!
      I32 invoke_to_read_write_16(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          U16 *write_buf_ptr, 
          U16 *read_buf_ptr, 
          U32 nWords, 
          U32 timeout_uS 
      );

      //! Invoke the to port connected to read_write_32
      //!
      I32 invoke_to_read_write_32(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          U32 *write_buf_ptr, 
          U32 *read_buf_ptr, 
          U32 nWords, 
          U32 timeout_uS 
      );

      //! Invoke the to port connected to spi_claim
      //!
      I32 invoke_to_spi_claim(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

      //! Invoke the to port connected to spi_configure
      //!
      I32 invoke_to_spi_configure(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          U8 loopback_mode, 
          U8 clock_polarity, 
          U8 clock_phase, 
          U8 div_clock_16, 
          U8 reverse_mode, 
          U8 word_len, 
          U8 prescale_modulus, 
          U8 prescale_modulus_factor, 
          U8 clock_gap 
      );

      //! Invoke the to port connected to read_write_8
      //!
      I32 invoke_to_read_write_8(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          U8 *write_buf_ptr, 
          U8 *read_buf_ptr, 
          U32 nWords, 
          U32 timeout_uS 
      );

    public:

      // ----------------------------------------------------------------------
      // Getters for port counts
      // ----------------------------------------------------------------------

      //! Get the number of to_spi_unclaim ports
      //!
      //! \return The number of to_spi_unclaim ports
      //!
      NATIVE_INT_TYPE getNum_to_spi_unclaim(void) const;

      //! Get the number of to_read_write_16 ports
      //!
      //! \return The number of to_read_write_16 ports
      //!
      NATIVE_INT_TYPE getNum_to_read_write_16(void) const;

      //! Get the number of from_timeCaller ports
      //!
      //! \return The number of from_timeCaller ports
      //!
      NATIVE_INT_TYPE getNum_from_timeCaller(void) const;

      //! Get the number of to_read_write_32 ports
      //!
      //! \return The number of to_read_write_32 ports
      //!
      NATIVE_INT_TYPE getNum_to_read_write_32(void) const;

      //! Get the number of to_spi_claim ports
      //!
      //! \return The number of to_spi_claim ports
      //!
      NATIVE_INT_TYPE getNum_to_spi_claim(void) const;

      //! Get the number of to_spi_configure ports
      //!
      //! \return The number of to_spi_configure ports
      //!
      NATIVE_INT_TYPE getNum_to_spi_configure(void) const;

      //! Get the number of to_read_write_8 ports
      //!
      //! \return The number of to_read_write_8 ports
      //!
      NATIVE_INT_TYPE getNum_to_read_write_8(void) const;

    protected:

      // ----------------------------------------------------------------------
      // Connection status for to ports
      // ----------------------------------------------------------------------

      //! Check whether port is connected
      //!
      //! Whether to_spi_unclaim[portNum] is connected
      //!
      bool isConnected_to_spi_unclaim(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

      //! Check whether port is connected
      //!
      //! Whether to_read_write_16[portNum] is connected
      //!
      bool isConnected_to_read_write_16(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

      //! Check whether port is connected
      //!
      //! Whether to_read_write_32[portNum] is connected
      //!
      bool isConnected_to_read_write_32(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

      //! Check whether port is connected
      //!
      //! Whether to_spi_claim[portNum] is connected
      //!
      bool isConnected_to_spi_claim(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

      //! Check whether port is connected
      //!
      //! Whether to_spi_configure[portNum] is connected
      //!
      bool isConnected_to_spi_configure(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

      //! Check whether port is connected
      //!
      //! Whether to_read_write_8[portNum] is connected
      //!
      bool isConnected_to_read_write_8(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

    private:

      // ----------------------------------------------------------------------
      // To ports
      // ----------------------------------------------------------------------

      //! To port connected to spi_unclaim
      //!
      Drv::OutputSphinxSPI_UnclaimPort m_to_spi_unclaim[1];

      //! To port connected to read_write_16
      //!
      Drv::OutputSphinxSPI_RW16_GenericPort m_to_read_write_16[1];

      //! To port connected to read_write_32
      //!
      Drv::OutputSphinxSPI_RW32_GenericPort m_to_read_write_32[1];

      //! To port connected to spi_claim
      //!
      Drv::OutputSphinxSPI_ClaimPort m_to_spi_claim[1];

      //! To port connected to spi_configure
      //!
      Drv::OutputSphinxSPI_ConfigurePort m_to_spi_configure[1];

      //! To port connected to read_write_8
      //!
      Drv::OutputSphinxSPI_RW_GenericPort m_to_read_write_8[1];

    private:

      // ----------------------------------------------------------------------
      // From ports
      // ----------------------------------------------------------------------

      //! From port connected to timeCaller
      //!
      Fw::InputTimePort m_from_timeCaller[1];

    private:

      // ----------------------------------------------------------------------
      // Static functions for output ports
      // ----------------------------------------------------------------------

      //! Static function for port from_timeCaller
      //!
      static void from_timeCaller_static(
          Fw::PassiveComponentBase *const callComp, /*!< The component instance*/
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          Fw::Time &time /*!< The U32 cmd argument*/
      );

  };

} // end namespace Drv

#endif
