/*
 * ADCPacket.cpp
 *
 *  Created on: May 01, 2017
 *      Author: Kevin F. Ortega
 */

#include <fprime-sphinx-drivers/ADCPacket/ADCPacket.hpp>
#include <Fw/Types/Assert.hpp>

namespace Drv {

    ADCPacket::ADCPacket() : Fw::TlmPacket() {
        this->v0 = 0;
        this->v1 = 0;
        this->v2 = 0;
        this->v3 = 0;
        this->v4 = 0;
        this->v5 = 0;
        this->v6 = 0;
        this->v7 = 0;
        this->v8 = 0;
    }

    ADCPacket::~ADCPacket() {
    }

    Fw::SerializeStatus ADCPacket::serialize(Fw::SerializeBufferBase& buffer) const {
        Fw::SerializeStatus stat;

        stat = buffer.serialize(this->v0);
        if (stat != Fw::FW_SERIALIZE_OK) {
            return stat;
        }
        stat = buffer.serialize(this->v1);
        if (stat != Fw::FW_SERIALIZE_OK) {
            return stat;
        }
        stat = buffer.serialize(this->v2);
        if (stat != Fw::FW_SERIALIZE_OK) {
            return stat;
        }
        stat = buffer.serialize(this->v3);
        if (stat != Fw::FW_SERIALIZE_OK) {
            return stat;
        }
        stat = buffer.serialize(this->v4);
        if (stat != Fw::FW_SERIALIZE_OK) {
            return stat;
        }
        stat = buffer.serialize(this->v5);
        if (stat != Fw::FW_SERIALIZE_OK) {
            return stat;
        }
        stat = buffer.serialize(this->v6);
        if (stat != Fw::FW_SERIALIZE_OK) {
            return stat;
        }
        stat = buffer.serialize(this->v7);
        if (stat != Fw::FW_SERIALIZE_OK) {
            return stat;
        }
        stat = buffer.serialize(this->v8);
        if (stat != Fw::FW_SERIALIZE_OK) {
            return stat;
        }

        return buffer.serialize(this->m_tlmBuffer.getBuffAddr(),m_tlmBuffer.getBuffLength(),true);

    }

    void ADCPacket::setV0(U32 v) { this->v0 = v; }
    void ADCPacket::setV1(U32 v) { this->v1 = v; }
    void ADCPacket::setV2(U32 v) { this->v2 = v; }
    void ADCPacket::setV3(U32 v) { this->v3 = v; }
    void ADCPacket::setV4(U32 v) { this->v4 = v; }
    void ADCPacket::setV5(U32 v) { this->v5 = v; }
    void ADCPacket::setV6(U32 v) { this->v6 = v; }
    void ADCPacket::setV7(U32 v) { this->v7 = v; }
    void ADCPacket::setV8(U32 v) { this->v8 = v; }

} /* namespace Drv */
