/*
 * SPWHeader.cpp
 *
 *  Created on: October 18, 2016
 *      Author: Kevin F. Ortega
 */

#include <fprime-sphinx-drivers/SPWDriver/SPWHeader.hpp>
#include <Fw/Types/Assert.hpp>

namespace Drv {

  SPWHeader::SPWHeader()
  {
    destLogicalAddr = 254;
    protocolID = 0;
  }

  SPWHeader::~SPWHeader()
  {
  }

  Fw::SerializeStatus SPWHeader::serializeBase(Fw::SerializeBufferBase& buffer) const
  {
    Fw::SerializeStatus stat;

    stat = buffer.serialize(this->destLogicalAddr);
    if (stat != Fw::FW_SERIALIZE_OK) {
      return stat;
    }

    return buffer.serialize(this->protocolID);
  }

  Fw::SerializeStatus SPWHeader::deserializeBase(Fw::SerializeBufferBase& buffer)
  {
    Fw::SerializeStatus stat;
    
    stat = buffer.deserialize(destLogicalAddr);
    if (stat != Fw::FW_SERIALIZE_OK) {
      return stat;
    }

    return buffer.deserialize(protocolID);
  }

  void SPWHeader::setDestLogicalAddr(U8 v) { this->destLogicalAddr = v; }
  void SPWHeader::setProtocolID(U8 v) { this->protocolID = v; }

  U8 SPWHeader::getDestLogicalAddr() { return this->destLogicalAddr; }
  U8 SPWHeader::getProtocolID() { return this->protocolID; }

} /* namespace Drv */
