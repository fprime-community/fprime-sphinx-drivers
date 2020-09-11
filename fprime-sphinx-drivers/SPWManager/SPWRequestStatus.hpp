/*
 * SPWRequestStatus.hpp
 *
 *  Created on: December 19, 2016
 *      Author: Vincent Wong
 */

#ifndef SPWREQUESTSTATUS_HPP_
#define SPWREQUESTSTATUS_HPP_

#include <fprime-sphinx-drivers/SPWDriver/RMAPHeader.hpp>

// generic
enum {
  SPW_REQUEST_STATUS_DONE,
  SPW_REQUEST_STATUS_TIMEDOUT,
  SPW_REQUEST_STATUS_ERROR,
  SPW_REQUEST_STATUS_ABORTED,
  // sync
  SPW_REQUEST_STATUS_BUSY,
  // async
  SPW_REQUEST_STATUS_ACCEPTED,
  SPW_REQUEST_STATUS_QUEUE_FULL,
  // dma
  SPW_REQUEST_STATUS_INVALID_BUF_SIZE,
};

// for request dma users
#define SPW_REQUEST_DMA_HDR_SIZE RMAP_READ_RESPONSE_HDR_SIZE

#endif
