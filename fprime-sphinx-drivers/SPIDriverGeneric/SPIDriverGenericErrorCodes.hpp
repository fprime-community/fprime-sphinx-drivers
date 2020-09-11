#ifndef SPI_GENERIC_ERROR_CODES
#define SPI_GENERIC_ERROR_CODES

namespace Drv
{

  //-1 to -100 reserved for adapter error codes
  enum SPI_Generic_Status {
    SPI_RECV_Q_EMPTY_ERR = -101,
    SPI_RECV_Q_FULL_ERR = -102, 
    SPI_TX_Q_FULL_ERR = -103, 
    SPI_TX_TIMEOUT_ERR = -104,
    SPI_TX_NOT_DONE_ERR = -105,
    SPI_RW_NOT_OWNER_ERR = -106,
    SPI_CLAIM_ALREADY_OWNER_ERR = -107,
    SPI_UNCLAIM_NOT_OWNER_ERR = -108,
    SPI_CONFIGURE_NOT_OWNER_ERR = -109
  };
}


#endif
