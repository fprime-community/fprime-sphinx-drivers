// ====================================================================== 
// \title  SPIDriverGenericImpl.hpp
// \author bsoudry
// \brief  hpp file for SPIDriverGeneric component implementation class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
// ====================================================================== 

#ifndef SPIDriverGeneric_HPP
#define SPIDriverGeneric_HPP

#include "fprime-sphinx-drivers/SPIDriverGeneric/SPIDriverGenericComponentAc.hpp"
#include <Os/Mutex.hpp>
#include <Os/Task.hpp>
#include <Fw/Types/BasicTypes.hpp>

#define SS_GPIO_PIN_NUM_MAX 64
#define MAX_WORDS_PER_SPI_TRANSACTION (100*1024*1024) /* 100 MB assuming 1 byte SPI words*/
#define MAX_TIP_CYCLES 1000
#define SPI_COUNT_PER_USEC_OF_DELAY 100 /*Assuming <100MHz processor*/
#define SPI_MAX_TIMEOUT_USECS 1000000 /*1 second max timeout for read/write*/

/* SPI Register Offsets */
#define SPI_CTRL_MODE_REG	0x80000420
#define SPI_CTRL_EVT_REG	0x80000424
#define SPI_CMD_REG		0x8000042C
#define SPI_TX_REG		0x80000430
#define SPI_RX_REG		0x80000434

/* Mode Register bit locations */
 #define MODE_LOOP		30	/* Loop mode */
 #define MODE_CPOL		29	/* Clock polarity */
 #define MODE_CPHA 		28	/* Clock phase */
 #define MODE_DIV16		27	/* Clock divide by 16 */
 #define MODE_REV		26	/* Reverse data */
 #define MODE_MS		25	/* Master mode */
 #define MODE_EN		24	/* Enable SPI core */

 #define MODE_LEN 	20      /* Word len (23:20) */ 
 #define MODE_PM3 	19      /* Prescale Modulus (PM) (19:16) */
 #define MODE_PM2		18 
 #define MODE_PM1		17 
 #define MODE_PM0		16 
 #define MODE_FACT		13	/* PM Factor */
 #define MODE_CG    7     /*Clock Gap (11:7)*/

/* Event Register bit locations */
 #define EVENT_TIP		31 	/* Transfer in progress */
 #define EVENT_LT		14	/* Last character */
 #define EVENT_OV 		12	/* Overrun */
 #define EVENT_UN 		11	/* Underrun */
 #define EVENT_NE 		9	/* Not Empty */
 #define EVENT_NF 		8	/* Not Full */

/*CMD Register bit locations */
 #define CMD_LST		22	/* Last */


namespace Drv {

  class SPIDriverGenericComponentImpl :
    public SPIDriverGenericComponentBase
  {

    public:

      // ----------------------------------------------------------------------
      // Construction, initialization, and destruction
      // ----------------------------------------------------------------------

      //! Construct object SPIDriverGeneric
      //!
      SPIDriverGenericComponentImpl(
#if FW_OBJECT_NAMES == 1
          const char *const compName, /*!< The component name*/
          const U8 loopback_mode,
          const U8 clock_polarity,
          const U8 clock_phase,
          const U8 div_clock_16,
          const U8 reverse_mode,
          const U8 word_len,
          const U8 prescale_modulus,
          const U8 prescale_modulus_factor,
          const U8 clock_gap
#else
          const U8 loopback_mode,
          const U8 clock_polarity,
          const U8 clock_phase,
          const U8 div_clock_16,
          const U8 reverse_mode,
          const U8 word_len,
          const U8 prescale_modulus,
          const U8 prescale_modulus_factor,
          const U8 clock_gap
#endif
      );
      
    SPIDriverGenericComponentImpl(
#if FW_OBJECT_NAMES == 1
          const char *const compName /*!< The component name*/
#else
          void
#endif
      );


      //! Initialize object SPIDriverGeneric
      //!
      void init(
          const NATIVE_INT_TYPE instance = 0 /*!< The instance number*/
      );

      //! Destroy object SPIDriverGeneric
      //!
      ~SPIDriverGenericComponentImpl(void);

    PRIVATE:
      //SPI controller register initialization variables
      U8 m_loopback_mode;
      U8 m_clock_polarity;
      U8 m_clock_phase;
      U8 m_div_clock_16;
      U8 m_reverse_mode;
      U8 m_word_len; //Note: actual spi word length, not what is set in MODE_LEN register 
      U8 m_prescale_modulus;
      U8 m_prescale_modulus_factor;
      U8 m_clock_gap;

      //Claim/unclaim variables
      Os::Mutex m_mutex;
      Os::TaskId m_ownerID;
      U8 m_isOwned;
      
      //SPI read/write buffer pointer size enum
      enum SPI_buf_ptr_size{
        SPI_U8_BUF_PTR = 1,
        SPI_U16_BUF_PTR = 2,
        SPI_U32_BUF_PTR = 3
      };
    
      // ----------------------------------------------------------------------
      // Handler implementations for user-defined typed input ports
      // ----------------------------------------------------------------------

      //! Handler implementation for read_write
      //!
      I32 read_write_8_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          U8 *write_buf_ptr, 
          U8 *read_buf_ptr, 
          U32 nWords, 
          U32 timeout_uS 
      );

      //! Handler implementation for read_write_16
      //!
      I32 read_write_16_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          U16 *write_buf_ptr, 
          U16 *read_buf_ptr, 
          U32 nWords, 
          U32 timeout_uS 
      );

      //! Handler implementation for read_write_32
      //!
      I32 read_write_32_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          U32 *write_buf_ptr, 
          U32 *read_buf_ptr, 
          U32 nWords, 
          U32 timeout_uS 
      );

      //! Handler implementation for spi_unclaim
      //!
      I32 spi_unclaim_handler(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

      //! Handler implementation for spi_claim
      //!
      I32 spi_claim_handler(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );
    
      //! Handler implementation for spi_configure
      //!
      I32 spi_configure_handler(
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


      // ----------------------------------------------------------------------
      // Helper functions
      // ----------------------------------------------------------------------
       I32 read(
            void *data_ptr,
            U8 data_ptr_size,
            U32 nWords,
            const U32 timeout_uS
        );
      I32 write(
            void *data_ptr,
            U8 data_ptr_size,
            U32 nBytes,
            const U32 timeout_uS
        );


      I32 spi_rw(
            void *write_buf_ptr,
            void *read_buf_ptr,
            U8 buf_ptr_size,
            U32 nWords,
            U32 timeout_uS
        );

      void init_registers(void); 
      
      void incrementPointer(void*& ptr, U8 ptr_size); 

      void resetSpiCore(void);

      Fw::Time getTime(void);
    };

} // end namespace Drv

#endif
