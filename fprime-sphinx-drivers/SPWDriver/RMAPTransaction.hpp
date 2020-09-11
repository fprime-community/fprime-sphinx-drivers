/*
 * RMAPTransaction.hpp
 *
 *  Created on: December 05, 2016
 *      Author: Vincent Wong
 */

#ifndef RMAPTRANSACTION_HPP_
#define RMAPTRANSACTION_HPP_

#include "fprime-sphinx-drivers/SPWDriver/sphinx-spw/rmapapi.h"

namespace Drv {

  struct RMAPTransaction
  {
    // rmapapi packet structure
    struct rmap_pkt pkt;

    // bookkeeping of buffers used for DMA
    U8* tx_hdr_buf;
    U32 tx_hdr_size;
    U8* tx_data_buf;
    U32 tx_data_size;
    U8* rx_buf;
    U32 rx_size;
  };

}

#endif
