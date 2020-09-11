// ======================================================================
// \title  ADC.hpp
// \author ortega
// \brief  cpp file for ADC test harness implementation class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
// ======================================================================

#include "Tester.hpp"

#define INSTANCE 0
#define CMD_SEQ 0
#define MAX_HISTORY_SIZE 10
#define QUEUE_DEPTH 10

namespace Drv {

  // ----------------------------------------------------------------------
  // Construction and destruction
  // ----------------------------------------------------------------------

  Tester ::
    Tester(void) :
#if FW_OBJECT_NAMES == 1
      ADCGTestBase("Tester", MAX_HISTORY_SIZE),
      component("ADC", 0, 2, 102, 60)
#else
      ADCGTestBase(MAX_HISTORY_SIZE),
      component(0, 2, 102, 60)
#endif
  {
    this->initComponents();
    this->connectPorts();
  }

  Tester ::
    ~Tester(void)
  {

  }

  void Tester :: dispatchOne(void)
  {
      this->component.doDispatch();
  }

  void Tester :: dispatchAll(void)
  {
    while(this->component.m_queue.getNumMsgs() > 0)
        this->dispatchOne();
  }

  void Tester::clearAndDispatch(void) {
      this->clearHistory();
      ASSERT_EQ(Fw::QueuedComponentBase::MSG_DISPATCH_OK,this->component.doDispatch());
  }


  // ----------------------------------------------------------------------
  // Tests
  // ----------------------------------------------------------------------

  void Tester ::
    testTelemetry(void)
  {
    this->invoke_to_schedIn(0, 0);
    this->component.doDispatch();
    ASSERT_from_adcOut_SIZE(1);

    ASSERT_TLM_ADC_o_a2d_tlm0_SIZE(1);
    ASSERT_TLM_ADC_o_a2d_tlm1_SIZE(1);
    ASSERT_TLM_ADC_o_a2d_tlm2_SIZE(1);
    ASSERT_TLM_ADC_o_a2d_tlm3_SIZE(1);
    ASSERT_TLM_ADC_o_a2d_tlm4_SIZE(1);
    ASSERT_TLM_ADC_o_a2d_tlm5_SIZE(1);
    ASSERT_TLM_ADC_o_a2d_tlm6_SIZE(1);
    ASSERT_TLM_ADC_o_a2d_tlm7_SIZE(1);
    //Stat not sent through tlm chain
    //ASSERT_TLM_ADC_a2d_stat_SIZE(1);
  }

  void Tester ::
    testSetRate(void)
  {
    U32 curr_rate_bit = 0;

    this->component.preamble();

    this->sendCmd_ADC_SOC_SET_RATE(INSTANCE, CMD_SEQ, 0);
    this->component.doDispatch();
    curr_rate_bit = (this->component.m_a2d_ctrl.val & (1 << SPHINX_ADC_SOC_RATE_BIT)) >> SPHINX_ADC_SOC_RATE_BIT;
    ASSERT_EQ(curr_rate_bit, 1);
    ASSERT_EVENTS_SIZE(1);
    ASSERT_CMD_RESPONSE_SIZE(1);

    this->clearHistory();

    this->sendCmd_ADC_SOC_SET_RATE(INSTANCE, CMD_SEQ, 1);
    this->component.doDispatch();
    curr_rate_bit = (this->component.m_a2d_ctrl.val & (1 << SPHINX_ADC_SOC_RATE_BIT)) >> SPHINX_ADC_SOC_RATE_BIT;
    ASSERT_EQ(curr_rate_bit, 0);
    ASSERT_EVENTS_SIZE(1);
    ASSERT_CMD_RESPONSE_SIZE(1);
  }

  void Tester ::
    testSetRun(void)
  {
    U32 curr_run_bit = 0;

    this->component.preamble();

    this->sendCmd_ADC_SOC_SET_RUN(INSTANCE, CMD_SEQ, 0);
    this->component.doDispatch();
    curr_run_bit = (this->component.m_a2d_ctrl.val & (1 << SPHINX_ADC_SOC_RUN_BIT)) >> SPHINX_ADC_SOC_RUN_BIT;
    ASSERT_EQ(curr_run_bit, 0);
    ASSERT_EVENTS_SIZE(1);
    ASSERT_CMD_RESPONSE_SIZE(1);

    this->clearHistory();

    this->sendCmd_ADC_SOC_SET_RUN(INSTANCE, CMD_SEQ, 1);
    this->component.doDispatch();
    curr_run_bit = (this->component.m_a2d_ctrl.val & (1 << SPHINX_ADC_SOC_RUN_BIT)) >> SPHINX_ADC_SOC_RUN_BIT;
    ASSERT_EQ(curr_run_bit, 1);
    ASSERT_EVENTS_SIZE(1);
    ASSERT_CMD_RESPONSE_SIZE(1);
  }

  void Tester ::
    testSetPwrCtrl(void)
  {
    U32 curr_pwr_bit = 0;

    this->component.preamble();

    this->sendCmd_ADC_SOC_SET_PWR_CTRL(INSTANCE, CMD_SEQ, 0);
    this->component.doDispatch();
    curr_pwr_bit = (this->component.m_a2d_ctrl.val & (1 << SPHINX_ADC_SOC_PWR_CTRL_BIT)) >> SPHINX_ADC_SOC_PWR_CTRL_BIT;
    ASSERT_EQ(curr_pwr_bit, 0);
    ASSERT_EVENTS_SIZE(1);
    ASSERT_CMD_RESPONSE_SIZE(1);

    this->clearHistory();

    this->sendCmd_ADC_SOC_SET_PWR_CTRL(INSTANCE, CMD_SEQ, 1);
    this->component.doDispatch();
    curr_pwr_bit = (this->component.m_a2d_ctrl.val & (1 << SPHINX_ADC_SOC_PWR_CTRL_BIT)) >> SPHINX_ADC_SOC_PWR_CTRL_BIT;
    ASSERT_EQ(curr_pwr_bit, 1);
    ASSERT_EVENTS_SIZE(1);
    ASSERT_CMD_RESPONSE_SIZE(1);
  }

  void Tester ::
    testTimeOut(void)
  {
    this->component.preamble();
    this->component.m_timer = 59;
    this->invoke_to_schedIn(0, 0);
    this->component.doDispatch();
    ASSERT_EVENTS_ADC_SOC_TimedOut_SIZE(1);
    ASSERT_EVENTS_ADC_SOC_TimedOut(0, 60);
    ASSERT_EQ(this->component.m_timer, 0);
  }

  void Tester ::
    testSetTimeOut(void)
  {
    U32 new_timeout = 6;
    this->component.preamble();
    this->sendCmd_ADC_SOC_SET_TLM_TIMEOUT(INSTANCE, CMD_SEQ, new_timeout);
    this->component.doDispatch();
    ASSERT_EVENTS_ADC_SOC_SetTimeout_SIZE(1);
    ASSERT_EVENTS_ADC_SOC_SetTimeout(0, 6);
    ASSERT_CMD_RESPONSE_SIZE(1);

    this->component.m_timer = (new_timeout-1);
    this->invoke_to_schedIn(0, 0);
    this->component.doDispatch();
    ASSERT_EVENTS_ADC_SOC_TimedOut_SIZE(1);
    ASSERT_EVENTS_ADC_SOC_TimedOut(0, new_timeout);
    ASSERT_EQ(this->component.m_timer, 0);
  }

     void Tester::pingTest(void){
         // make sure ping is responded to
         this->invoke_to_PingRecv(0,(U32)1234);
         this->clearAndDispatch();
         ASSERT_from_PingResponse_SIZE(1);
         ASSERT_from_PingResponse(0,(U32)1234);
     }

  // ----------------------------------------------------------------------
  // Handlers for typed from ports
  // ----------------------------------------------------------------------

  void Tester ::
    from_PingResponse_handler(
        const NATIVE_INT_TYPE portNum,
        U32 key
    )
  {
    this->pushFromPortEntry_PingResponse(key);
  }


  void Tester ::
    from_adcOut_handler(
        const NATIVE_INT_TYPE portNum,
        Fw::Time timetag,
        U16 apid,
        Fw::FileBuffer &data,
        U16 apid_rec
    )
  {
    this->pushFromPortEntry_adcOut(timetag, apid, data, apid_rec);
  }

  // ----------------------------------------------------------------------
  // Helper methods
  // ----------------------------------------------------------------------

  void Tester ::
    connectPorts(void)
  {

    // schedIn
    this->connect_to_schedIn(
        0,
        this->component.get_schedIn_InputPort(0)
    );

    // cmdIn
    this->connect_to_cmdIn(
        0,
        this->component.get_cmdIn_InputPort(0)
    );

    // cmdReg
    this->component.set_cmdReg_OutputPort(
        0,
        this->get_from_cmdReg(0)
    );

    // timeCaller
    this->component.set_timeCaller_OutputPort(
        0,
        this->get_from_timeCaller(0)
    );

    // eventOut
    this->component.set_eventOut_OutputPort(
        0,
        this->get_from_eventOut(0)
    );

    // cmdResponse
    this->component.set_cmdResponse_OutputPort(
        0,
        this->get_from_cmdResponse(0)
    );

    // adcOut
    this->component.set_adcOut_OutputPort(
        0,
        this->get_from_adcOut(0)
    );

    // tlmOut
    this->component.set_tlmOut_OutputPort(
        0,
        this->get_from_tlmOut(0)
    );

    // LogText
    this->component.set_LogText_OutputPort(
        0,
        this->get_from_LogText(0)
    );

    // PingRecv
    this->connect_to_PingRecv(
        0,
        this->component.get_PingRecv_InputPort(0)
    );

    // PingResponse
    this->component.set_PingResponse_OutputPort(
        0,
        this->get_from_PingResponse(0)
    );


  }

  void Tester ::
    initComponents(void)
  {
    this->init();
    this->component.init(
        QUEUE_DEPTH, INSTANCE
    );
  }

} // end namespace Drv
