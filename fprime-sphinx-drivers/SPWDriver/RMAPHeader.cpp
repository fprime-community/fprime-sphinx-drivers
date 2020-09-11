/*
 * RMAPHeader.cpp
 *
 *  Created on: December 07, 2016
 *      Author: Vincent Wong
 */

#include <fprime-sphinx-drivers/SPWDriver/RMAPHeader.hpp>
#include <fprime-sphinx-drivers/Util/SphinxDrvUtil.hpp>
#include <Fw/Types/Assert.hpp>

namespace Drv {

    RMAPHeader::RMAPHeader() : Drv::SPWHeader()
  {
      setProtocolID(1);

      packetType = RMAP_COMMAND;
      commandType = RMAP_READ;
      verify = 0;
      acknowledge = 0;
      increment = 0;
      destKey = 0;
      status = 0;
      srcLogicalAddr = 0;
      transactionID = 0;
      extendedAddr = 0;
      addr = 0;
      dataLen = 0;
      crc = 0;
    }

    RMAPHeader::~RMAPHeader()
    {
    }

    Fw::SerializeStatus RMAPHeader::serialize(Fw::SerializeBufferBase& buffer) const
    {
      return serialize(buffer, true);
    }

    Fw::SerializeStatus RMAPHeader::serialize(Fw::SerializeBufferBase& buffer, bool withCRC) const
    {
      Fw::SerializeStatus stat;

      stat = serializeBase(buffer);
      if (stat != Fw::FW_SERIALIZE_OK) {
        return stat;
      }

      U8 flagByte = 0;
      Drv::writeMemBit(&flagByte, 6, this->packetType == RMAP_COMMAND);
      switch (this->commandType) {
        case RMAP_WRITE:
          Drv::writeMemBit(&flagByte, 5, 1);
          Drv::writeMemBit(&flagByte, 4, this->verify);
          Drv::writeMemBit(&flagByte, 3, this->acknowledge | (this->packetType == RMAP_RESPONSE));
          Drv::writeMemBit(&flagByte, 2, this->increment);
          break;
        case RMAP_READ:
          Drv::writeMemBit(&flagByte, 5, 0);
          Drv::writeMemBit(&flagByte, 4, 0);
          Drv::writeMemBit(&flagByte, 3, 1);
          Drv::writeMemBit(&flagByte, 2, this->increment);
          break;
        case RMAP_READ_MODIFY_WRITE:
          Drv::writeMemBit(&flagByte, 5, 0);
          Drv::writeMemBit(&flagByte, 4, 1);
          Drv::writeMemBit(&flagByte, 3, 1);
          Drv::writeMemBit(&flagByte, 2, 1);
        default:
          break;
      }
      stat = buffer.serialize(flagByte);
      if (stat != Fw::FW_SERIALIZE_OK) {
        return stat;
      }

      if (this->packetType == RMAP_COMMAND) {
        stat = buffer.serialize(this->destKey);
      } else {
        stat = buffer.serialize(this->status);
      }
      if (stat != Fw::FW_SERIALIZE_OK) {
        return stat;
      }

      stat = buffer.serialize(this->srcLogicalAddr);
      if (stat != Fw::FW_SERIALIZE_OK) {
        return stat;
      }

      stat = buffer.serialize(this->transactionID);
      if (stat != Fw::FW_SERIALIZE_OK) {
        return stat;
      }

      if (this->packetType == RMAP_COMMAND) {
        stat = buffer.serialize(this->extendedAddr);
      } else if (this->commandType != RMAP_WRITE) {
        U8 reserved = 0;
        stat = buffer.serialize(reserved);
      }
      if (stat != Fw::FW_SERIALIZE_OK) {
        return stat;
      }

      if (this->packetType == RMAP_COMMAND) {
        stat = buffer.serialize(this->addr);
        if (stat != Fw::FW_SERIALIZE_OK) {
          return stat;
        }
      }

      if (this->packetType != RMAP_RESPONSE || this->commandType != RMAP_WRITE) {
        U8 dataLenBuf[3];
        dataLenBuf[2] = this->dataLen & 0xff;
        dataLenBuf[1] = (this->dataLen >> 8) & 0xff;
        dataLenBuf[0] = (this->dataLen >> 16) & 0xff;
        stat = buffer.serialize(dataLenBuf, sizeof(dataLenBuf), true);
        if (stat != Fw::FW_SERIALIZE_OK) {
          return stat;
        }
      }

      if (withCRC) {
        stat = buffer.serialize(this->crc);
        if (stat != Fw::FW_SERIALIZE_OK) {
          return stat;
        }
      }

      return Fw::FW_SERIALIZE_OK;
    }

    Fw::SerializeStatus RMAPHeader::deserialize(Fw::SerializeBufferBase& buffer)
    {
      return deserialize(buffer, true);
    }

    Fw::SerializeStatus RMAPHeader::deserialize(Fw::SerializeBufferBase& buffer, bool withCRC)
    {
        Fw::SerializeStatus stat;

        stat = deserializeBase(buffer);
        if (stat != Fw::FW_SERIALIZE_OK) {
            return stat;
        }

        if (getProtocolID() != 1) {
          return Fw::FW_DESERIALIZE_FORMAT_ERROR;
        }

        U8 flagByte;
        stat = buffer.deserialize(flagByte);
        if (stat != Fw::FW_SERIALIZE_OK) {
            return stat;
        }
        if (Drv::readMemBit(&flagByte, 6)) {
          this->packetType = RMAP_COMMAND;
        } else {
          this->packetType = RMAP_RESPONSE;
        }
        U8 cmdBit = Drv::readMemBit(&flagByte, 5);
        this->verify = Drv::readMemBit(&flagByte, 4);
        if (cmdBit) {
          this->commandType = RMAP_WRITE;
        } else if (!verify) {
          this->commandType = RMAP_READ;
        } else {
          this->commandType = RMAP_READ_MODIFY_WRITE;
        }
        this->acknowledge = Drv::readMemBit(&flagByte, 3);
        this->increment = Drv::readMemBit(&flagByte, 2);

        if (this->packetType == RMAP_COMMAND) {
          stat = buffer.deserialize(this->destKey);
        } else {
          stat = buffer.deserialize(this->status);
        }
        if (stat != Fw::FW_SERIALIZE_OK) {
            return stat;
        }

        stat = buffer.deserialize(this->srcLogicalAddr);
        if (stat != Fw::FW_SERIALIZE_OK) {
            return stat;
        }

        stat = buffer.deserialize(this->transactionID);
        if (stat != Fw::FW_SERIALIZE_OK) {
            return stat;
        }

        if (this->packetType == RMAP_COMMAND) {
          stat = buffer.deserialize(this->extendedAddr);
          if (stat != Fw::FW_SERIALIZE_OK) {
              return stat;
          }

          stat = buffer.deserialize(this->addr);
          if (stat != Fw::FW_SERIALIZE_OK) {
              return stat;
          }
        } else if (this->commandType == RMAP_READ || this->commandType == RMAP_READ_MODIFY_WRITE) {
          // read and rmw response has a reserved byte
          U8 tmp;
          stat = buffer.deserialize(tmp);
          if (stat != Fw::FW_SERIALIZE_OK) {
              return stat;
          }
        }

        if (this->packetType != RMAP_RESPONSE || this->commandType != RMAP_WRITE) {
          U8 dataLenBuf[3];
          U32 dataLenBufSize = sizeof(dataLenBuf);
          stat = buffer.deserialize(dataLenBuf, dataLenBufSize, true);
          if (stat != Fw::FW_SERIALIZE_OK) {
              return stat;
          }
          this->dataLen = (static_cast<U32>(dataLenBuf[0]) << 16) +
                          (static_cast<U32>(dataLenBuf[1]) << 8) +
                          (dataLenBuf[2]);
        }

        if (withCRC) {
          stat = buffer.deserialize(this->crc);
          if (stat != Fw::FW_SERIALIZE_OK) {
              return stat;
          }
        }

        return Fw::FW_SERIALIZE_OK;
    }

    void RMAPHeader::setPacketType(RMAPPacketType v) { this->packetType = v; }
    void RMAPHeader::setCommandType(RMAPCommandType v) { this->commandType = v; }
    void RMAPHeader::setVerify(U8 v) { this->verify = v; }
    void RMAPHeader::setAcknowledge(U8 v) { this->acknowledge = v; }
    void RMAPHeader::setIncrement(U8 v) { this->increment = v; }
    void RMAPHeader::setDestKey(U8 v) { this->destKey = v; }
    void RMAPHeader::setStatus(U8 v) { this->status = v; }
    void RMAPHeader::setSrcLogicalAddr(U8 v) { this->srcLogicalAddr = v; }
    void RMAPHeader::setTransactionID(U16 v) { this->transactionID = v; }
    void RMAPHeader::setExtendedAddr(U8 v) { this->extendedAddr = v; }
    void RMAPHeader::setAddr(U32 v) { this->addr = v; }
    void RMAPHeader::setDataLen(U32 v) { this->dataLen = v; }
    void RMAPHeader::setCRC(U8 v) { this->crc = v; }

    RMAPHeader::RMAPPacketType RMAPHeader::getPacketType() { return this->packetType; }
    RMAPHeader::RMAPCommandType RMAPHeader::getCommandType() { return this->commandType; }
    U8 RMAPHeader::getVerify() { return this->verify; }
    U8 RMAPHeader::getAcknowledge() { return this->acknowledge; }
    U8 RMAPHeader::getIncrement() { return this->increment; }
    U8 RMAPHeader::getDestKey() { return this->destKey; }
    U8 RMAPHeader::getStatus() { return this->status; }
    U8 RMAPHeader::getSrcLogicalAddr() { return this->srcLogicalAddr; }
    U16 RMAPHeader::getTransactionID() { return this->transactionID; }
    U8 RMAPHeader::getExtendedAddr() { return this->extendedAddr; }
    U32 RMAPHeader::getAddr() { return this->addr; }
    U32 RMAPHeader::getDataLen() { return this->dataLen; }
    U8 RMAPHeader::getCRC() { return this->crc; }

} /* namespace Drv */
