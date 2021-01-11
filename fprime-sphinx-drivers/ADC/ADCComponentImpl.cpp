// ======================================================================
// \title  ADCImpl.cpp
// \author ortega
// \brief  cpp file for ADC component implementation class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
// ======================================================================


#include <fprime-sphinx-drivers/ADC/ADCComponentImpl.hpp>
#include <Fw/Types/Assert.hpp>
#include <fprime-sphinx-drivers/Util/SphinxDrvIntUtil.hpp>

namespace Drv {

  // ----------------------------------------------------------------------
  // Construction, initialization, and destruction
  // ----------------------------------------------------------------------

  ADCComponentImpl ::
#if FW_OBJECT_NAMES == 1
    ADCComponentImpl(
        const char *const compName,
        U8 rate,
        U32 apid_rt,
        U32 apid_rec,
        U32 timeout
    ) :
      ADCComponentBase(compName),
#else
    ADCImpl(U8 rate,
            U32 apid_rt,
            U32 apid_rec,
            U32 timeout),
#endif
    m_apid_rt(apid_rt),
    m_apid_rec(apid_rec),
    m_timeout(timeout),
    m_timer(0)
  {

    // Rate of 1Hz needs to set bit to 0
    // Rate of 0.1Hz needs to set bit to 1
    U8 rate_bit = (rate == 0) ? 1 : 0;
    U32 control_val;

    // Write only access
    this->adc_soc_init(&m_a2d_ctrl, SPHINX_ADC_SOC_CTRL_OFFSET, 4);

    // Read only access
    this->adc_soc_init(&m_a2d_stat, SPHINX_ADC_SOC_STAT_OFFSET, 3);

    // Read only access
    this->adc_soc_init(&m_tlm0, SPHINX_ADC_SOC_TLM0_OFFSET, 12);
    this->adc_soc_init(&m_tlm1, SPHINX_ADC_SOC_TLM1_OFFSET, 12);
    this->adc_soc_init(&m_tlm2, SPHINX_ADC_SOC_TLM2_OFFSET, 12);
    this->adc_soc_init(&m_tlm3, SPHINX_ADC_SOC_TLM3_OFFSET, 12);
    this->adc_soc_init(&m_tlm4, SPHINX_ADC_SOC_TLM4_OFFSET, 12);
    this->adc_soc_init(&m_tlm5, SPHINX_ADC_SOC_TLM5_OFFSET, 12);
    this->adc_soc_init(&m_tlm6, SPHINX_ADC_SOC_TLM6_OFFSET, 12);
    this->adc_soc_init(&m_tlm7, SPHINX_ADC_SOC_TLM7_OFFSET, 12);

    // Setup the control register and write to it
    control_val = 0;
    control_val |= ((U32)1 << SPHINX_ADC_SOC_TLM_ACK_BIT);
    control_val |= ((U32)1 << SPHINX_ADC_SOC_RUN_BIT);
    control_val |= ((U32)rate_bit << SPHINX_ADC_SOC_RATE_BIT);
    control_val |= ((U32)1 << SPHINX_ADC_SOC_PWR_CTRL_BIT);
    m_a2d_ctrl.val = control_val;
#if defined(BUILD_SPHINX)
    Drv::writeReg(m_a2d_ctrl.addr, m_a2d_ctrl.val);
#endif
  }

  void ADCComponentImpl ::
    init(
        const NATIVE_INT_TYPE queueDepth,
        const NATIVE_INT_TYPE instance
    )
  {
    ADCComponentBase::init(queueDepth, instance);
  }

  ADCComponentImpl ::
    ~ADCComponentImpl(void)
  {

  }

  void ADCComponentImpl ::
    preamble(void)
  {
    // NOTE: tlm_ready bit is set when tlm_ack bit is unset.
    //       unsetting tlm_ack bit here just in case it is set
    //       at boot up.
    this->adc_soc_unset_tlm_ack();
  }

  // ----------------------------------------------------------------------
  // Handler implementations for user-defined typed input ports
  // ----------------------------------------------------------------------

  void ADCComponentImpl ::
    schedIn_handler(
        const NATIVE_INT_TYPE portNum,
        NATIVE_UINT_TYPE context
    )
  {
    m_timer++;
    if(m_timeout != 0 &&
      (m_timer % m_timeout) == 0)
    {
      this->log_WARNING_HI_ADC_SOC_TimedOut(m_timer);
      // unset tlm_ack bit as a safety measure
      this->adc_soc_unset_tlm_ack();
      m_timer = 0;
    }

    if(this->adc_soc_is_tlm_ready())
    {
      // get tlm
      this->adc_soc_get_and_pack_tlm();

      // send out tlm
      this->adc_soc_send_out_tlm();

      // send control register a tlm_ack
      this->adc_soc_send_tlm_ack();

      // unset control register's tlm_ack bit
      this->adc_soc_unset_tlm_ack();

      // reset timer
      m_timer = 0;
    }
  }

  void ADCComponentImpl ::
    PingRecv_handler(
        const NATIVE_INT_TYPE portNum,
        U32 key
    )
  {
    if (this->isConnected_PingResponse_OutputPort(0))
    {
      this->PingResponse_out(0, key);
    }
  }


  // ----------------------------------------------------------------------
  // Command handler implementations
  // ----------------------------------------------------------------------

  void ADCComponentImpl ::
    ADC_SOC_SET_RATE_cmdHandler(
        const FwOpcodeType opCode,
        const U32 cmdSeq,
        U8 rate
    )
  {
    // Set the rate bit to the specified number
    U8 rate_bit = (rate == 0) ? 1 : 0;
    m_a2d_ctrl.val =  ((m_a2d_ctrl.val & ~((U32)1 << SPHINX_ADC_SOC_RATE_BIT)) |
                       ((U32)rate_bit << SPHINX_ADC_SOC_RATE_BIT));
#if defined(BUILD_SPHINX)
    Drv::writeReg(m_a2d_ctrl.addr, m_a2d_ctrl.val);
    this->log_ACTIVITY_HI_ADC_SOC_SetRate(rate, rate_bit);
    this->cmdResponse_out(opCode, cmdSeq, Fw::COMMAND_OK);
#else
    this->log_ACTIVITY_HI_ADC_SOC_CouldNotSetRate();
    this->cmdResponse_out(opCode, cmdSeq, Fw::COMMAND_EXECUTION_ERROR);
#endif
  }

  void ADCComponentImpl ::
    ADC_SOC_SET_RUN_cmdHandler(
        const FwOpcodeType opCode,
        const U32 cmdSeq,
        U8 run_mode
    )
  {
    // Set the rate bit to the specified number
    U8 run_bit = (run_mode == 0) ? 0 : 1;
    m_a2d_ctrl.val =  ((m_a2d_ctrl.val & ~((U32)1 << SPHINX_ADC_SOC_RUN_BIT)) |
                       ((U32)run_bit << SPHINX_ADC_SOC_RUN_BIT));
#if defined(BUILD_SPHINX)
    Drv::writeReg(m_a2d_ctrl.addr, m_a2d_ctrl.val);
    this->log_ACTIVITY_HI_ADC_SOC_SetRun(run_bit);
    this->cmdResponse_out(opCode, cmdSeq, Fw::COMMAND_OK);
#else
    this->log_ACTIVITY_HI_ADC_SOC_CouldNotSetRunBit();
    this->cmdResponse_out(opCode, cmdSeq, Fw::COMMAND_EXECUTION_ERROR);
#endif
  }

  void ADCComponentImpl ::
    ADC_SOC_SET_PWR_CTRL_cmdHandler(
        const FwOpcodeType opCode,
        const U32 cmdSeq,
        U8 pwr_ctrl
    )
  {
    // Set the rate bit to the specified number
    U8 pwr_bit = (pwr_ctrl == 0) ? 0 : 1;
    m_a2d_ctrl.val =  ((m_a2d_ctrl.val & ~((U32)1 << SPHINX_ADC_SOC_PWR_CTRL_BIT)) |
                       ((U32)pwr_bit << SPHINX_ADC_SOC_PWR_CTRL_BIT));
#if defined(BUILD_SPHINX)
    Drv::writeReg(m_a2d_ctrl.addr, m_a2d_ctrl.val);
    this->log_ACTIVITY_HI_ADC_SOC_SetPwrCtrl(pwr_bit);
    this->cmdResponse_out(opCode, cmdSeq, Fw::COMMAND_OK);
#else
    this->log_ACTIVITY_HI_ADC_SOC_CouldNotSetPwrCtrlBit();
    this->cmdResponse_out(opCode, cmdSeq, Fw::COMMAND_EXECUTION_ERROR);
#endif
  }

  void ADCComponentImpl ::
    ADC_SOC_SET_TLM_TIMEOUT_cmdHandler(
        const FwOpcodeType opCode,
        const U32 cmdSeq,
        U32 timeout
    )
  {
    m_timer = 0;
    m_timeout = timeout;
    this->log_ACTIVITY_HI_ADC_SOC_SetTimeout(timeout);
    this->cmdResponse_out(opCode, cmdSeq, Fw::COMMAND_OK);
  }

  // ----------------------------------------------------------------------
  // Private helper functions
  // ----------------------------------------------------------------------

  void ADCComponentImpl ::
    adc_soc_init(adc_soc *tlm, const U32 offset, const U32 size)
  {
    FW_ASSERT(tlm != NULL);

    U32 i = 0;

    // Create the mask based on size (which should be in bits)
    tlm->mask = 0x0;
    for(i = 0; i < size; i++)
    {
      tlm->mask |= ((U32)1 << i);
    }

    tlm->offset = offset;
    tlm->addr = SPHINX_ADC_SOC_BASE_ADDR + SPHINX_ADC_SOC_DEV_ID + offset;
    tlm->size = size;
    tlm->val = 0;
  }

  void ADCComponentImpl ::
    adc_soc_get_and_pack_tlm(void)
  {
    Fw::SerializeStatus stat;

    this->adc_soc_get_tlm(&m_tlm0);
    m_adc_packet.setV0(m_tlm0.val);

    this->adc_soc_get_tlm(&m_tlm1);
    m_adc_packet.setV1(m_tlm1.val);

    this->adc_soc_get_tlm(&m_tlm2);
    m_adc_packet.setV2(m_tlm2.val);

    this->adc_soc_get_tlm(&m_tlm3);
    m_adc_packet.setV3(m_tlm3.val);

    this->adc_soc_get_tlm(&m_tlm4);
    m_adc_packet.setV4(m_tlm4.val);

    this->adc_soc_get_tlm(&m_tlm5);
    m_adc_packet.setV5(m_tlm5.val);

    this->adc_soc_get_tlm(&m_tlm6);
    m_adc_packet.setV6(m_tlm6.val);

    this->adc_soc_get_tlm(&m_tlm7);
    m_adc_packet.setV7(m_tlm7.val);

    this->adc_soc_get_tlm(&m_a2d_stat);
    m_adc_packet.setV8(m_a2d_stat.val);

    m_com_buff.resetSer();
    stat = m_adc_packet.serialize(m_com_buff);
    FW_ASSERT(stat == Fw::FW_SERIALIZE_OK, stat);
  }

  void ADCComponentImpl ::
    adc_soc_get_tlm(adc_soc *tlm)
  {
    FW_ASSERT(tlm != NULL);

    U32 val = 0;
#if defined(BUILD_SPHINX)
    val = Drv::readReg(tlm->addr);
#endif
    tlm->val = (val & tlm->mask);
  }

  bool ADCComponentImpl ::
    adc_soc_is_tlm_ready(void)
  {
#if defined(BUILD_SPHINX)
    // return true of tlm_rdy bit is set to 1
    return Drv::readBit(m_a2d_stat.addr, SPHINX_ADC_SOC_STAT_TLM_RDY_BIT) == 1;
#else
    return true;
#endif
  }

  void ADCComponentImpl ::
    adc_soc_send_out_tlm(void)
  {
    Fw::Time timetag;
    timetag = this->getTime();

    if (this->isConnected_adcOut_OutputPort(0)) {
      this->adcOut_out(0, timetag, m_apid_rt, m_com_buff, m_apid_rec);
    }

    // telemeter raw values from ADC
    this->tlmWrite_ADC_o_a2d_tlm0( m_tlm0.val );
    this->tlmWrite_ADC_o_a2d_tlm1( m_tlm1.val );
    this->tlmWrite_ADC_o_a2d_tlm2( m_tlm2.val );
    this->tlmWrite_ADC_o_a2d_tlm3( m_tlm3.val );
    this->tlmWrite_ADC_o_a2d_tlm4( m_tlm4.val );
    this->tlmWrite_ADC_o_a2d_tlm5( m_tlm5.val );
    this->tlmWrite_ADC_o_a2d_tlm6( m_tlm6.val );
    this->tlmWrite_ADC_o_a2d_tlm7( m_tlm7.val );
  }

  void ADCComponentImpl ::
    adc_soc_send_tlm_ack(void)
  {
#if defined(BUILD_SPHINX)
    Drv::setBit(m_a2d_ctrl.addr, SPHINX_ADC_SOC_TLM_ACK_BIT);
#endif
  }

  void ADCComponentImpl ::
    adc_soc_unset_tlm_ack(void)
  {
#if defined(BUILD_SPHINX)
    Drv::clearBit(m_a2d_ctrl.addr, SPHINX_ADC_SOC_TLM_ACK_BIT);
#endif
  }

} // end namespace Drv
