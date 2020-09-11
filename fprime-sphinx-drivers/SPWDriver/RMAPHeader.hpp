/*
 * RMAPHeader.hpp
 *
 *  Created on: December 07, 2016
 *      Author: Vincent Wong
 */

#ifndef RMAPHEADER_HPP_
#define RMAPHEADER_HPP_

#include <fprime-sphinx-drivers/SPWDriver/SPWHeader.hpp>

#define MAX_RMAP_PACKET_SIZE 0xfffffc // 16 MiB - 4
#define MAX_RMAP_TRANSACTION_ID 0xffff

#define MAX_RMAP_HDR_SIZE 16
#define RMAP_READ_RESPONSE_HDR_SIZE 12

namespace Drv {

  class RMAPHeader : public SPWHeader {

    public:

      typedef enum {
        RMAP_COMMAND,
        RMAP_RESPONSE
      } RMAPPacketType;

      typedef enum {
        RMAP_WRITE,
        RMAP_READ,
        RMAP_READ_MODIFY_WRITE
      } RMAPCommandType;

    public:

      RMAPHeader();
      virtual ~RMAPHeader();

      // interface overrides, delegates to real implementation withCRC = true
      virtual Fw::SerializeStatus serialize(Fw::SerializeBufferBase& buffer) const;
      virtual Fw::SerializeStatus deserialize(Fw::SerializeBufferBase& buffer);

      // real implementation
      virtual Fw::SerializeStatus serialize(Fw::SerializeBufferBase& buffer, bool withCRC) const;
      virtual Fw::SerializeStatus deserialize(Fw::SerializeBufferBase& buffer, bool withCRC);

      // setters
      void setPacketType(RMAPPacketType v);
      void setCommandType(RMAPCommandType v);
      void setVerify(U8 v);
      void setAcknowledge(U8 v);
      void setIncrement(U8 v);
      void setDestKey(U8 v);
      void setStatus(U8 v);
      void setSrcLogicalAddr(U8 v);
      void setTransactionID(U16 v);
      void setExtendedAddr(U8 v);
      void setAddr(U32 v);
      void setDataLen(U32 v);
      void setCRC(U8 v);

      // getters
      RMAPPacketType getPacketType();
      RMAPCommandType getCommandType();
      U8 getVerify();
      U8 getAcknowledge();
      U8 getIncrement();
      U8 getDestKey();
      U8 getStatus();
      U8 getSrcLogicalAddr();
      U16 getTransactionID();
      U8 getExtendedAddr();
      U32 getAddr();
      U32 getDataLen();
      U8 getCRC();

    protected:

      RMAPPacketType packetType;
      RMAPCommandType commandType;
      U8 verify;
      U8 acknowledge;
      U8 increment;
      U8 destKey;
      U8 status;
      U8 srcLogicalAddr;
      U16 transactionID;
      U8 extendedAddr;
      U32 addr;
      U32 dataLen;
      U8 crc;

  };

} /* namespace Drv */

#endif /* RMAPHEADER_HPP_ */
