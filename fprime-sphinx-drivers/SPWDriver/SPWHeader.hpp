/*
 * SPWHeader.hpp
 *
 *  Created on: December 07, 2016
 *      Author: Vincent Wong
 */

#ifndef SPWHEADER_HPP_
#define SPWHEADER_HPP_

#include <Fw/Types/Serializable.hpp>

namespace Drv {

  class SPWHeader : public Fw::Serializable {
    public:

      SPWHeader();
      virtual ~SPWHeader();

      // setters
      void setDestLogicalAddr(U8 v);
      void setProtocolID(U8 v);
      // getters
      U8 getDestLogicalAddr();
      U8 getProtocolID();

    protected:

      Fw::SerializeStatus serializeBase(Fw::SerializeBufferBase& buffer) const ; // called by derived classes to serialize common fields
      Fw::SerializeStatus deserializeBase(Fw::SerializeBufferBase& buffer); // called by derived classes to deserialize common fields

    protected:

      U8 destLogicalAddr;
      U8 protocolID;
  };

} /* namespace Drv */

#endif /* SPWHEADER_HPP_ */
