// ======================================================================
// \title  ADCImpl.hpp
// \author ortega
// \brief  hpp file for ADC component implementation class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
// ======================================================================

#ifndef ADC_HPP
#define ADC_HPP

#include "fprime-sphinx-drivers/ADC/ADCComponentAc.hpp"
#include "fprime-sphinx-drivers/ADCPacket/ADCPacket.hpp"
#include "Fw/Com/ComBuffer.hpp"

#ifndef SPHINX_ADC_SOC_BASE_ADDR
#define SPHINX_ADC_SOC_BASE_ADDR 0x20000000
#endif

#ifndef SPHINX_ADC_SOC_CTRL_OFFSET
#define SPHINX_ADC_SOC_CTRL_OFFSET 0x0000
#endif

#ifndef SPHINX_ADC_SOC_STAT_OFFSET
#define SPHINX_ADC_SOC_STAT_OFFSET 0x0004
#endif

#ifndef SPHINX_ADC_SOC_TLM0_OFFSET
#define SPHINX_ADC_SOC_TLM0_OFFSET 0x0100
#endif

#ifndef SPHINX_ADC_SOC_TLM1_OFFSET
#define SPHINX_ADC_SOC_TLM1_OFFSET 0x0104
#endif

#ifndef SPHINX_ADC_SOC_TLM2_OFFSET
#define SPHINX_ADC_SOC_TLM2_OFFSET 0x0108
#endif

#ifndef SPHINX_ADC_SOC_TLM3_OFFSET
#define SPHINX_ADC_SOC_TLM3_OFFSET 0x010C
#endif

#ifndef SPHINX_ADC_SOC_TLM4_OFFSET
#define SPHINX_ADC_SOC_TLM4_OFFSET 0x0110
#endif

#ifndef SPHINX_ADC_SOC_TLM5_OFFSET
#define SPHINX_ADC_SOC_TLM5_OFFSET 0x0114
#endif

#ifndef SPHINX_ADC_SOC_TLM6_OFFSET
#define SPHINX_ADC_SOC_TLM6_OFFSET 0x0118
#endif

#ifndef SPHINX_ADC_SOC_TLM7_OFFSET
#define SPHINX_ADC_SOC_TLM7_OFFSET 0x011C
#endif

#ifndef SPHINX_ADC_SOC_DEV_ID
#define SPHINX_ADC_SOC_DEV_ID 0x00080000
#endif

#ifndef SPHINX_ADC_SOC_TLM_ACK_BIT
#define SPHINX_ADC_SOC_TLM_ACK_BIT 3
#endif

#ifndef SPHINX_ADC_SOC_RUN_BIT
#define SPHINX_ADC_SOC_RUN_BIT 2
#endif

#ifndef SPHINX_ADC_SOC_RATE_BIT
#define SPHINX_ADC_SOC_RATE_BIT 1
#endif

#ifndef SPHINX_ADC_SOC_PWR_CTRL_BIT
#define SPHINX_ADC_SOC_PWR_CTRL_BIT 0
#endif

#ifndef SPHINX_ADC_SOC_STAT_TLM_RDY_BIT
#define SPHINX_ADC_SOC_STAT_TLM_RDY_BIT 1
#endif

namespace Drv {

  class ADCComponentImpl :
    public ADCComponentBase
  {

    public:

      // ----------------------------------------------------------------------
      // Construction, initialization, and destruction
      // ----------------------------------------------------------------------

      //! Construct object ADC
      //!
      ADCComponentImpl(
#if FW_OBJECT_NAMES == 1
          const char *const compName, //!< The component name
#endif
          U8 rate, //!< The rate at which the ADC will run. Rate of 1 for 1Hz and a rate
                   //!< of anything else for 0.1Hz.
          U32 apid_rt, //!< The real time APID number
          U32 apid_rec, //!< The recorded APID number
          U32 timeout //!< Timeout if we don't get tlm_ready signal
      );

      //! Initialize object ADC
      //!
      void init(
          const NATIVE_INT_TYPE queueDepth, //!< The queue depth
          const NATIVE_INT_TYPE instance = 0 //!< The instance number
      );

      //! Destroy object ADC
      //!
      ~ADCComponentImpl(void);

      //! Preamble
      //!
      void preamble(void);

    PRIVATE:

      // ----------------------------------------------------------------------
      // Handler implementations for user-defined typed input ports
      // ----------------------------------------------------------------------

      //! Handler implementation for schedIn
      //!
      void schedIn_handler(
          const NATIVE_INT_TYPE portNum, //!< The port number
          NATIVE_UINT_TYPE context //!< The call order
      );

      //! Handler implementation for PingRecv
      //!
      void PingRecv_handler(
          const NATIVE_INT_TYPE portNum, //!< The port number
          U32 key //!< Value to return to pinger
      );


    PRIVATE:

      // ----------------------------------------------------------------------
      // Command handler implementations
      // ----------------------------------------------------------------------

      //! Implementation for ADC_SOC_SET_RATE command handler
      //! Selects 0.1Hz or 1Hz acquisition rate.
      void ADC_SOC_SET_RATE_cmdHandler(
          const FwOpcodeType opCode, //!< The opcode
          const U32 cmdSeq, //!< The command sequence number
          U8 rate //!<  Rate of acquisition. 1 = 1Hz, anything else is 0.1Hz
      );

      //! Implementation for ADC_SOC_SET_RUN command handler
      //! Set ADC's run mode.
      void ADC_SOC_SET_RUN_cmdHandler(
          const FwOpcodeType opCode, //!< The opcode
          const U32 cmdSeq, //!< The command sequence number
          U8 run_mode //!<  Set run mode. 0 will stop ADC. Anything else will have ADC running.
      );

      //! Implementation for ADC_SOC_SET_PWR_CTRL command handler
      //! Set ADC's power mode.
      void ADC_SOC_SET_PWR_CTRL_cmdHandler(
          const FwOpcodeType opCode, //!< The opcode
          const U32 cmdSeq, //!< The command sequence number
          U8 pwr_ctrl //!<  Set power mode. 0 will disable power. Anything else will enable power.
      );

      //! Implementation for ADC_SOC_SET_TLM_TIMEOUT command handler
      //! Set timeout value for how long to wait for new telemetry before generating a warning.
      void ADC_SOC_SET_TLM_TIMEOUT_cmdHandler(
          const FwOpcodeType opCode, //!< The opcode
          const U32 cmdSeq, //!< The command sequence number
          U32 timeout //!<  Timeout value in tick units -- based on connected rategroup connection.
      );

      typedef struct
      {
        U32 offset;
        U32 addr; //!< base_addr + offset
        U32 size; //!< in bits
        U32 mask; //!< mask for bits we care about
        U32 val; //!< read value of addr
      } adc_soc;

      // ----------------------------------------------------------------------
      // Private helper functions
      // ----------------------------------------------------------------------

      void adc_soc_get_and_pack_tlm(void);
      void adc_soc_get_tlm(adc_soc *tlm);
      void adc_soc_init(adc_soc *tlm, const U32 offset, const U32 size);
      bool adc_soc_is_tlm_ready(void);
      void adc_soc_send_out_tlm(void);
      void adc_soc_send_tlm_ack(void);
      void adc_soc_unset_tlm_ack(void);

      // ----------------------------------------------------------------------
      // Private member variables
      // ----------------------------------------------------------------------

      adc_soc m_tlm0;
      adc_soc m_tlm1;
      adc_soc m_tlm2;
      adc_soc m_tlm3;
      adc_soc m_tlm4;
      adc_soc m_tlm5;
      adc_soc m_tlm6;
      adc_soc m_tlm7;
      adc_soc m_a2d_stat;
      adc_soc m_a2d_ctrl;

      ADCPacket m_adc_packet;
      Fw::ComBuffer m_file_buff;

      U32 m_apid_rt;
      U32 m_apid_rec;
      U32 m_timeout;
      U32 m_timer;
    };

} // end namespace Drv

#endif
