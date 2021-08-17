// ======================================================================
// \title  SphinxUartOnboardDriverImpl.cpp
// \author muellerd, amand
// \brief  cpp file for SphinxUartOnboardDriver component implementation class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
// ======================================================================

#include <fprime-sphinx-drivers/SphinxUartOnboardDriver/SphinxUartOnboardDriverComponentImpl.hpp>

#include <Fw/Log/LogString.hpp>
#include <fprime-sphinx-drivers/Util/SphinxDrvIntUtil.hpp>
#include <Os/Log.hpp>
#include "Fw/Types/Assert.hpp"
#include "Fw/Types/BasicTypes.hpp"

namespace Drv {

  // ----------------------------------------------------------------------
  // Construction, initialization, and destruction
  // ----------------------------------------------------------------------


  // Constructor
  SphinxUartOnboardDriverComponentImpl ::
#if FW_OBJECT_NAMES == 1
    SphinxUartOnboardDriverComponentImpl(
        const char *const compName     // Component name
    ) :
      SphinxUartOnboardDriverComponentBase(compName), GPIOInterruptHandler()
#else
    SphinxUartOnboardDriverImpl(
    ) : SphinxUartOnboardDriverComponentBase(), GPIOInterruptHandler();
#endif
  {
    memset(this->m_read_buf, 0, READ_BUF_SIZE);
    this->m_read_buf_wp = 0;
    this->m_read_buf_rp = 0;
    this->m_control = 0x00;
    #ifdef TGT_OS_TYPE_VXWORKS
    SPIN_LOCK_ISR_INIT(&this->m_read_buf_lock, 0);
    #endif

    // Initialize members with HARDWARE UART PORT 0
    // by default in constructor.
    // Other UART ports configured via init_comp()
    this->m_address = REG_PORT_0;
    this->m_registerType = RegisterType_HARDWARE;
  }


  // ----------------------------------------------------------------------
  // Initializer
  void SphinxUartOnboardDriverComponentImpl :: init(
        const NATIVE_INT_TYPE instance ) {
    SphinxUartOnboardDriverComponentBase::init(instance);
    }


  // ----------------------------------------------------------------------
  // Destructor
  SphinxUartOnboardDriverComponentImpl ::
    ~SphinxUartOnboardDriverComponentImpl(void) {
    // Disable UART
    this->push_control(0x00);
  }


  void SphinxUartOnboardDriverComponentImpl :: init_comp(
            U8 portNum,               // UART port to use
            U32 baudRate,             // Transceive rate
            U32 clockSpeed,           // Processor clock speed (MegaHertz))
	    U32 flag                  // flag to determine if interrupts are setup (1 = not setup)
          )
  {
      // Initialize UART and put in disabled state
      this->setup_port(portNum);
      this->set_baud_rate(clockSpeed, baudRate);
      this->purge_fifos();
      this->push_status(0x00);
      this->push_control(0x00);

      // Enable RX Interrupts, by default flag is 0 on VxWorks builds
      if(!flag)
      {
        this->setup_interrupts(portNum);
      }

      // Start the UART
      this->set_rx_enable(true);
  }


  // ----------------------------------------------------------------------
  // Internal functions
  // ----------------------------------------------------------------------


  U32 SphinxUartOnboardDriverComponentImpl :: pull_byte() {

    if( this->m_registerType == RegisterType_HARDWARE) {
      return (U8) Drv::readReg(this->m_address + REG_OFF_HW_DATA);
    } else {
      U32 temp = (U8) Drv::readReg(this->m_address + REG_OFF_FW_RX_PORT);
      this->push_control(FW_CTRL_TRIGGER_READ | FW_CTRL_ENABLE_RX);
      return temp;
    }
  }


  void SphinxUartOnboardDriverComponentImpl :: push_byte(const U8 bits) {

    if( this->m_registerType == RegisterType_HARDWARE) {
      Drv::writeReg(this->m_address + REG_OFF_HW_DATA, bits);
    } else {
      Drv::writeReg(this->m_address + REG_OFF_FW_TX_PORT, bits);
      this->push_control(FW_CTRL_TRIGGER_WRITE | FW_CTRL_ENABLE_RX);
    }
  }


  void SphinxUartOnboardDriverComponentImpl :: push_control(const U32 bits) {

    this->m_control = bits;

    if( this->m_registerType == RegisterType_HARDWARE){
      Drv::writeReg(this->m_address + REG_OFF_HW_CONTROL, bits);
    } else{
      Drv::writeReg(this->m_address + REG_OFF_FW_CONTROL, bits);
    }
  }


  U32 SphinxUartOnboardDriverComponentImpl :: pull_status(void) {
    if( this->m_registerType == RegisterType_HARDWARE){
      return Drv::readReg(this->m_address + REG_OFF_HW_STATUS);
    } else{
      return Drv::readReg(this->m_address + REG_OFF_FW_STATUS);
    }
  }


  void SphinxUartOnboardDriverComponentImpl :: push_status(const U32 bits, U32 flag) {

    if( this->m_registerType == RegisterType_HARDWARE){
      Drv::writeReg(this->m_address + REG_OFF_HW_STATUS, bits, flag);
    } else{
      // FW status is read only
    }
  }


  bool SphinxUartOnboardDriverComponentImpl :: is_data_ready(void) {

    U32 status = this->pull_status();

    if( this->m_registerType == RegisterType_HARDWARE ){
      return status & HW_STAT_DR;
    } else{
      // Firmware has no data ready bit
      return false;
    }
  }


  bool SphinxUartOnboardDriverComponentImpl :: is_tx_empty(void) {

    U32 status = this->pull_status();

    if( this->m_registerType == RegisterType_HARDWARE ){
      return (status & HW_STAT_TS) && (status & HW_STAT_TE);
    } else{
      // No access to TX FIFO or # of bytes
      return false;
    }
  }


  bool SphinxUartOnboardDriverComponentImpl :: is_tx_full(void) {

    U32 status = this->pull_status();

    if( this->m_registerType == RegisterType_HARDWARE ) {
      return status & HW_STAT_TF;
    } else{
      return status & FW_STAT_TF;
    }
  }


  bool SphinxUartOnboardDriverComponentImpl :: is_rx_empty(void) {

    U32 status = this->pull_status();

    if( this->m_registerType == RegisterType_HARDWARE) {
      return !(status & HW_STAT_RCNT);
    } else {
      return status & FW_STAT_RE;
    }
  }


  U32 SphinxUartOnboardDriverComponentImpl :: has_rx_error(void) {

    U8 result = 0x00;

    U32 status = this->pull_status();

    // On hardware...
    if( this->m_registerType == RegisterType_HARDWARE ) {

      // If any error is detected...
      if( status & HW_STAT_ERROR ) {

        // Encode the error in result
        if( status & HW_STAT_OV )
          result |= IOErrorBit_OVERFLOW;

        if( status & HW_STAT_FE )
          result |= IOErrorBit_FRAMING;

        if( status & HW_STAT_PE )
          result |= IOErrorBit_PARITY;
      }

    }

    return result;

  }


  void SphinxUartOnboardDriverComponentImpl :: clear_errors(void) {

    U32 status = this->pull_status();

    if( this->m_registerType == RegisterType_HARDWARE ) {
      this->push_status(status & ~HW_STAT_ERROR);
    } else {
      // Firmware doesn't have any error bits that can be cleared
    }
  }


  void SphinxUartOnboardDriverComponentImpl :: set_rx_enable(const bool enable){

    if( this->m_registerType == RegisterType_HARDWARE ){
      if( enable ){
        this->push_control(this->m_control | HW_CTRL_ENABLE_RX);
      } else{
        this->push_control(this->m_control & ~HW_CTRL_ENABLE_RX);
      }
    } else{
      if( enable ){
        this->push_control(FW_CTRL_ENABLE_RX);
      } else{
        this->push_control(FW_CTRL_DISABLE_RX);
      }
    }
  }


  void SphinxUartOnboardDriverComponentImpl :: set_tx_enable(const bool enable) {


    if( this->m_registerType == RegisterType_HARDWARE ) {

      if( enable ){
        this->push_control(this->m_control | HW_CTRL_ENABLE_TX);
      } else {
        this->push_control(this->m_control & ~HW_CTRL_ENABLE_TX);
      }

    } else {
      // No TX enable in Firmware
    }
  }


void SphinxUartOnboardDriverComponentImpl :: setup_port(U8 portNum) {

    switch( portNum ) {

    // -----------------------------------
    // Hardware ports
    // -----------------------------------
    case 0:
      this->m_address = REG_PORT_0;
      this->m_registerType = RegisterType_HARDWARE;
      break;

    case 1:
     this->m_address = REG_PORT_1;
     this->m_registerType = RegisterType_HARDWARE;
     break;

    case 4:
     this->m_address = REG_PORT_4;
     this->m_registerType = RegisterType_HARDWARE;
     break;

    case 5:
     this->m_address = REG_PORT_5;
     this->m_registerType = RegisterType_HARDWARE;
     break;

    // -----------------------------------
    // Firmware ports
    // -----------------------------------
    case 2:
     this->m_address = REG_PORT_2;
     this->m_registerType = RegisterType_FIRMWARE;
     break;

    case 3:
     this->m_address = REG_PORT_3;
     this->m_registerType = RegisterType_FIRMWARE;
     break;

    case 6:
     this->m_address = REG_PORT_6;
     this->m_registerType = RegisterType_FIRMWARE;
     break;

    case 7:
     this->m_address = REG_PORT_7;
     this->m_registerType = RegisterType_FIRMWARE;
     break;

    // -----------------------------------
    // Invalid port number
    // -----------------------------------
    default:
     FW_ASSERT(0);
     break;
    }
  }


  void SphinxUartOnboardDriverComponentImpl :: set_baud_rate(U32 clockSpeed, U32 baudRate) {

    // Validate baud rate based on type of port: hardware or firmware
    if( this->m_registerType == RegisterType_HARDWARE ) {

      // Restrict baud rate to hardware-limited range, and compatible with both
      //   receive and transmit, which have different MIN and MAX rates
      FW_ASSERT( baudRate >= BAUD_TX_MIN && baudRate <= BAUD_RX_MAX );

      // Set the UART scaler, which is tied to the baud rate
      U32 scaler = (clockSpeed * MEGA_FACTOR) / (baudRate * 8) - 1;
      Drv::writeReg(this->m_address + REG_OFF_HW_SCALER, scaler);

    } else {

       // At this point, if we aren't talking about firmware, something went awry
       FW_ASSERT(this->m_registerType == RegisterType_FIRMWARE);

       // Baud rate on firmware must be one of a discrete set of values (as
       //   opposed to a continuous range, as is the case with hardware)
       FW_ASSERT( baudRate == BAUD_2400    ||
                  baudRate == BAUD_4800    ||
                  baudRate == BAUD_9600    ||
                  baudRate == BAUD_19200   ||
                  baudRate == BAUD_38500   ||
                  baudRate == BAUD_57600   ||
                  baudRate == BAUD_115200  ||
                  baudRate == BAUD_1000000 );

        U32 baudMask;

        switch( baudRate ) {

        case BAUD_2400:
          baudMask = REG_BAUD_2400;
          break;

        case BAUD_4800:
          baudMask = REG_BAUD_4800;
          break;

        case BAUD_9600:
          baudMask = REG_BAUD_9600;
          break;

        case BAUD_19200:
          baudMask = REG_BAUD_19200;
          break;

        case BAUD_38500:
          baudMask = REG_BAUD_38500;
          break;

        case BAUD_57600:
          baudMask = REG_BAUD_57600;
          break;

        case BAUD_115200:
          baudMask = REG_BAUD_115200;
          break;

        case BAUD_1000000:
          baudMask = REG_BAUD_1000000;
          break;

        default:
          FW_ASSERT(0);
          return;

        }

        Drv::writeReg(this->m_address + REG_OFF_FW_BAUD_RATE, baudMask);
      }
  }


  void SphinxUartOnboardDriverComponentImpl :: purge_fifos() {

    U8 bit;
    U32 status;

    this->push_status(0x00);
    this->set_rx_enable(true);
    this->set_tx_enable(true);


    // Clear the RX FIFO
    U32 loopCnt = 0;
    while( !this->is_rx_empty() && (loopCnt < MAX_PURGE_CNT)) {
      // Reset inner counter
      (void) this->pull_byte();
      loopCnt++;
    }

    // Bounding counter for outer loop
    if( loopCnt >= MAX_PURGE_CNT ) {
      this->log_WARNING_HI_UOBD_HardwareInitPurgeError();
    }

    // If hardware, clear the TX FIFO
    if (this->m_registerType == RegisterType_HARDWARE){
      U32 loopCnt = 0;
      while( !this->is_tx_empty() && (loopCnt < MAX_PURGE_CNT) ) {
        // Reset inner counter
        this->push_byte(0x00);
        loopCnt++;
      }
      // Bounding counter for outer loop
      if( ++loopCnt >= MAX_PURGE_CNT ) {
        this->log_WARNING_HI_UOBD_HardwareInitPurgeError();
      }
    }

    this->push_control(0x00);

    // If Hardware, check error status
    if (this->m_registerType == RegisterType_HARDWARE){
      status = this->pull_status();

      bit = (bool)(status & HW_STAT_DR);
      if( bit != HwStatusPostInit_DR ) {
        Fw::LogStringArg logStringArg("DR");
        this->log_WARNING_HI_UOBD_HardwareInitStatusError(
           (U8) HW_STAT_DR,
           bit,
           (U8) HwStatusPostInit_DR,
           logStringArg);
      }

      bit = (bool)(status & HW_STAT_TS);
      if( bit != HwStatusPostInit_TS ) {
        Fw::LogStringArg logStringArg("TS");
        this->log_WARNING_HI_UOBD_HardwareInitStatusError(
            (U8) HW_STAT_TS,
            bit,
            (U8) HwStatusPostInit_TS,
            logStringArg);
      }

      bit = (bool)(status & HW_STAT_TE);
      if( bit != HwStatusPostInit_TE ) {
        Fw::LogStringArg logStringArg("TE");
        this->log_WARNING_HI_UOBD_HardwareInitStatusError(
            (U8) HW_STAT_TE,
            bit,
            (U8) HwStatusPostInit_TE,
            logStringArg);
      }

      bit = (bool)(status & HW_STAT_TH);
      if( bit != HwStatusPostInit_TH ) {
        Fw::LogStringArg logStringArg("TH");
        this->log_WARNING_HI_UOBD_HardwareInitStatusError(
            (U8) HW_STAT_TH,
            bit,
            (U8) HwStatusPostInit_TH,
            logStringArg);
      }

      bit = (bool)(status & HW_STAT_RH);
      if( bit != HwStatusPostInit_RH ) {
        Fw::LogStringArg logStringArg("RH");
        this->log_WARNING_HI_UOBD_HardwareInitStatusError(
            (U8) HW_STAT_RH,
            bit,
            (U8) HwStatusPostInit_RH,
            logStringArg);
      }

      bit = (bool)(status & HW_STAT_TF);
      if( bit != HwStatusPostInit_TF ) {
        Fw::LogStringArg logStringArg("TF");
        this->log_WARNING_HI_UOBD_HardwareInitStatusError(
            (U8) HW_STAT_TF,
            bit,
            (U8) HwStatusPostInit_TF,
            logStringArg);
      }

      bit = (bool)(status & HW_STAT_RF);
      if( bit != HwStatusPostInit_RF ) {
        Fw::LogStringArg logStringArg("RF");
        this->log_WARNING_HI_UOBD_HardwareInitStatusError(
            (U8) HW_STAT_RF,
            bit,
            (U8) HwStatusPostInit_RF,
            logStringArg);
      }
    }
    this->push_status(0x00);

  }



  void SphinxUartOnboardDriverComponentImpl :: setup_interrupts(U8 portNum){

    #if defined (BUILD_SPHINX) || defined(BUILD_GR712DEV)
    I32 status=0;
    #endif

    switch(portNum){

    #if defined (BUILD_SPHINX) || defined(BUILD_GR712DEV)

    case 0:
      status = intConnect(INUM_TO_IVEC(UART0_IVEC_NUM), (VOIDFUNCPTR)&UARTHWintHandler, (I32)this);
      FW_ASSERT(status != ERROR);
      this->push_control(HW_CTRL_RX_INT );
      break;

    case 1:
      status = intConnect(INUM_TO_IVEC(UART1_IVEC_NUM), (VOIDFUNCPTR)&UARTHWintHandler, (I32)this);
      FW_ASSERT(status != ERROR);
      this->push_control(HW_CTRL_RX_INT );
     break;

    case 4:
      status = intConnect(INUM_TO_IVEC(UART4_IVEC_NUM), (VOIDFUNCPTR)&UARTHWintHandler, (I32)this);
      FW_ASSERT(status != ERROR);
      this->push_control(HW_CTRL_RX_INT );
      break;

    case 5:
      status = intConnect(INUM_TO_IVEC(UART5_IVEC_NUM), (VOIDFUNCPTR)&UARTHWintHandler, (I32)this);
      FW_ASSERT(status != ERROR);
      this->push_control(HW_CTRL_RX_INT );
      break;

    #endif

    case 2:
      EnableFWInterrupt(UART2_INT_BIT_NUM);
      break;

    case 3:
      EnableFWInterrupt(UART3_INT_BIT_NUM);
      break;

    case 6:
      EnableFWInterrupt(UART6_INT_BIT_NUM);
      break;

    case 7:
      EnableFWInterrupt(UART7_INT_BIT_NUM);
      break;

    default:
      FW_ASSERT(0);
      break;
    }
  }



  // ----------------------------------------------------------------------
  // Interrupt Handling
  // ----------------------------------------------------------------------


  void SphinxUartOnboardDriverComponentImpl :: EnableFWInterrupt(U32 intNum){
    Drv::setBit(REG_FW_INT, intNum);
  }


  // Interrupt Handler. Used to handle RX interrupts
  void UARTHWintHandler
  #ifdef TGT_OS_TYPE_VXWORKS
    (I32 arg)
  #else
    (I64 arg)
  #endif
  {
    SphinxUartOnboardDriverComponentImpl* comp_ptr = reinterpret_cast<Drv::SphinxUartOnboardDriverComponentImpl*>(arg);
    FW_ASSERT(comp_ptr != NULL);

    // Read all available bytes from UART Fifo and stores
    // them on circular buffer. Locks all interrupts.
    comp_ptr->read_fifo();
  }


  void SphinxUartOnboardDriverComponentImpl :: HandleGPIOInterrupt(void){
    this->read_fifo();
  }

  void SphinxUartOnboardDriverComponentImpl :: read_fifo(void)
  {
    U8 lpCnt;
    bool wrapped = false;

    #ifdef TGT_OS_TYPE_VXWORKS
    SPIN_LOCK_ISR_TAKE(&this->m_read_buf_lock);
    #endif

    // Copy contents of receive FIFO into read buf while RX FIFO is not empty;
    // Necessary because interrupts are disabled, thus can be missed, so there
    // may be more than one byte available in the RX FIFO
    for(lpCnt = 0; !this->is_rx_empty() && (lpCnt < 8); lpCnt++) {
      this->m_read_buf[this->m_read_buf_wp] = this->pull_byte();
      this->m_read_buf_wp = (this->m_read_buf_wp + 1) % READ_BUF_SIZE;
      if (this->m_read_buf_wp == this->m_read_buf_rp){
        wrapped = true;
      }
    }

    #ifdef TGT_OS_TYPE_VXWORKS
    SPIN_LOCK_ISR_GIVE(&this->m_read_buf_lock);
    #endif

    if(wrapped) {
      this->log_WARNING_HI_UOBD_BUFF_WRAP();
    }
  }


  // ----------------------------------------------------------------------
  // Handler implementations for user-defined typed input ports
  // ----------------------------------------------------------------------


  U32 SphinxUartOnboardDriverComponentImpl :: bytesUsed_handler(
        const NATIVE_INT_TYPE portNum
    )
  {
    // Returns number of bytes of data in circular buffer
    return ((this->m_read_buf_wp + READ_BUF_SIZE) - this->m_read_buf_rp) % READ_BUF_SIZE;
  }


  I32 SphinxUartOnboardDriverComponentImpl :: read_handler(
        NATIVE_INT_TYPE portNum,
        U8 *read_buf_ptr,
        U32 nBytes,
        U32 timeout ) {

    U32 usecs = 0;
    U32 bytesRead = 0;
    U32 temp_buf_rp = this->m_read_buf_rp;
    I32 result = 0x00;
    U8 errorCode;
    Fw::Time baseT;
    Fw::Time currT;

    // Reset read buffer pointers and flush FIFO if nBytes == 0 or
    // read_buf_ptr is NULL. Allows user to reset read buffer without
    // an additional port
    if (nBytes == 0){
      this->read_fifo();
      this->m_read_buf_rp = this->m_read_buf_wp;
      return result;
    }

    FW_ASSERT(read_buf_ptr != NULL);
    baseT = this->getTime();
    for (U32 i = 0; i < nBytes; i++){
      do {
        //// Check for any bytes left in FIFO ////
        if (!this->is_rx_empty()){
          this->read_fifo();
        }

        #ifdef TGT_OS_TYPE_VXWORKS
        SPIN_LOCK_ISR_TAKE(&this->m_read_buf_lock);
        #endif

        //// Hardware/Firmware Read ////
        if (temp_buf_rp != this->m_read_buf_wp){
          *(read_buf_ptr++) = this->m_read_buf[temp_buf_rp];
          temp_buf_rp = (temp_buf_rp + 1) % READ_BUF_SIZE;
          bytesRead++;
          #ifdef TGT_OS_TYPE_VXWORKS
          SPIN_LOCK_ISR_GIVE(&this->m_read_buf_lock);
          #endif
          break;
        }

        #ifdef TGT_OS_TYPE_VXWORKS
        SPIN_LOCK_ISR_GIVE(&this->m_read_buf_lock);
        #endif

        //// Update Time ////
        currT = this->getTime();
        FW_ASSERT(currT >= baseT);
        currT = currT.sub(currT, baseT);
        usecs = (currT.getUSeconds() + currT.getSeconds()*MEGA_FACTOR);

      } while (usecs < timeout);

      // If timed out, leave for loop
      if ((timeout > 0) && (usecs >= timeout)){
        break;
      }
    }

    // Check if any errors occured during read
    errorCode = this->has_rx_error();
    if( errorCode ) {
      result |= errorCode;
      this->clear_errors();
    }

    // If all bytes weren't read, timeout occured
    if (bytesRead < nBytes){
      result |= IOErrorBit_TIMEOUT;
    }

    // If no errors or timeout occured, adjust buffer read index
    if (!result){
      this->m_read_buf_rp = temp_buf_rp;
    }

    return result;
  }


  I32 SphinxUartOnboardDriverComponentImpl :: write_handler(
        NATIVE_INT_TYPE portNum,
        U8 *write_buf_ptr,
        U32 nBytes,
        U32 timeout) {

    U32 usecs = 0;
    U32 bytesSent = 0;
    I32 result = 0x00;
    Fw::Time baseT;
    Fw::Time currT;

    FW_ASSERT(write_buf_ptr != NULL);

    // Reset status register and enable TX
    // push_status flag set to 1 to prevent clearing of bit
    // that we want set to prevent an infinite loop
    this->push_status(0x00, 1);
    this->set_tx_enable(true);

    // Write each byte to TX FIFO as long as FIFO is not full
    baseT = this->getTime();
    for(U32 i = 0; i < nBytes; i++) {

      while (usecs < timeout){

        //// Hardware/Firmware Send ////
        if (!this->is_tx_full()){
          this->push_byte(*(write_buf_ptr++));
          bytesSent++;
          break;
        }

        //// Update Time ////
        currT = this->getTime();
        FW_ASSERT(currT >= baseT);
        currT = currT.sub(currT, baseT);
        usecs = (currT.getUSeconds() + currT.getSeconds()*MEGA_FACTOR);
      }

      // If timed out, leave for loop
      if (usecs >= timeout){
        break;
      }

    }

    // Wait until all bytes have been shifted out (or timeout)
    while(usecs < timeout){

      // Check if TX Fifo is empty
      if (is_tx_empty()){
        break;
      }

      // Update Time //
      currT = this->getTime();
      FW_ASSERT(currT >= baseT);
      currT = currT.sub(currT, baseT);
      usecs = currT.getUSeconds();
    }

    // Disable the UART TX
    this->set_tx_enable(false);

    // If all bytes weren't sent, timeout occured
    if (bytesSent != nBytes){
      result |= IOErrorBit_TIMEOUT;
    }

    // If TX fifo isn't empty and register type is HW,
    // a timeout occured. FW has no method for checking
    // if TX fifo is empty, so we only check for HW.
    if (!is_tx_empty() && this->m_registerType == RegisterType_HARDWARE){
      result |= IOErrorBit_TIMEOUT;
    }

    return result;
  }


} // end namespace Drv
