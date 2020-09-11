/*
 * SPWRequest.hpp
 *
 *  Created on: December 19, 2016
 *      Author: Vincent Wong
 */

#ifndef SPWREQUEST_HPP_
#define SPWREQUEST_HPP_

#include "fprime-sphinx-drivers/SPWDriver/RMAPHeader.hpp"

namespace Drv {

  struct SPWRequest
  {

    // port that client used to initiate request
    NATIVE_INT_TYPE client_port;

    // command type of the transaction
    RMAPHeader::RMAPCommandType command;

    // remote target address to operate (read/write) on
    U32 target_addr;

    // destination logical address and key
    U8 dest_addr;
    U8 dest_key;

    // client buffers to copy from/to working buffer
    U8* client_buf;
    U32 client_length;

    // work buffer
    U8* work_buf;

    // the state of the most recent transaction
    U32 offset; // how much of the request processed so far
    U32 transaction_length; // length of most recent transaction

    // frozen RMAP flags at the time of request
    U8 acknowledge;
    U8 increment;
    U8 verify;

    // is request async
    bool async;

    // whether to DMA into client buffer instead of using work buffer
    bool dma;

    // indicates whether or not this request is in progress
    bool active;

    // track the amount of time passed for timeout
    U32 timer;
    U32 timeout;
      SPWRequest()
              : client_port(0)
              , command(RMAPHeader::RMAP_READ)
              , target_addr(0)
              , dest_addr(0)
              , dest_key(0)
              , client_buf(0)
              , client_length(0)
              , work_buf(0)
              , offset(0)
              , transaction_length(0)
              , acknowledge(0)
              , increment(0)
              , verify(0)
              , async(0)
              , dma(0)
              , active(0)
              , timer(0)
              , timeout(0)
      {
      };
  };
}

#endif
