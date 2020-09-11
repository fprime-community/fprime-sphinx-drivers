/*
 * SPWStatus.hpp
 *
 *  Created on: December 05, 2016
 *      Author: Vincent Wong
 */

#ifndef SPWSTATUS_HPP_
#define SPWSTATUS_HPP_

enum {
  SPW_STATUS_SUCCESS,
  SPW_STATUS_SENDING,
  SPW_STATUS_RECEIVING,

  SPW_STATUS_ERR_INIT,
  SPW_STATUS_ERR_DISCONNECTED,

  SPW_STATUS_ERR_TX_LINK,
  SPW_STATUS_ERR_RX_TRUNCATED,
  SPW_STATUS_ERR_RX_DATA_CRC,
  SPW_STATUS_ERR_RX_HDR_CRC,
  SPW_STATUS_ERR_RX_EEP,
  SPW_STATUS_ERR_RX_DESERIALIZATION,
  SPW_STATUS_ERR_RX_UNEXPECTED_REPLY,

  SPW_STATUS_ERR_RMAP_TRANS_ID_MISMATCH,
  SPW_STATUS_ERR_RMAP_DATA_LEN_MISMATCH,
  SPW_STATUS_ERR_RMAP_STAT_GENERAL,
  SPW_STATUS_ERR_RMAP_STAT_UNUSED_TYPE,
  SPW_STATUS_ERR_RMAP_STAT_INVALID_KEY,
  SPW_STATUS_ERR_RMAP_STAT_INVALID_DATA_CRC,
  SPW_STATUS_ERR_RMAP_STAT_EARLY_EOP,
  SPW_STATUS_ERR_RMAP_STAT_CARGO_TOO_LARGE,
  SPW_STATUS_ERR_RMAP_STAT_EEP,
  SPW_STATUS_ERR_RMAP_STAT_VERIFY_BUFFER_OVERRUN,
  SPW_STATUS_ERR_RMAP_STAT_CMD_UNAUTHORIZED,
  SPW_STATUS_ERR_RMAP_STAT_DATA_LEN_ERR,
  SPW_STATUS_ERR_RMAP_STAT_INVALID_DEST_ADDR,
  SPW_STATUS_ERR_RMAP_STAT_UNKNOWN,
};

#endif
