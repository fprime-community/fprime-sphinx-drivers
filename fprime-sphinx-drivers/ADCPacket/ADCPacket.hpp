/*
 * ADCPacket.hpp
 *
 *  Created on: May 01, 2017
 *      Author: Kevin F. Ortega
 */

#ifndef ADCPACKET_HPP_
#define ADCPACKET_HPP_

#include <Fw/Tlm/TlmPacket.hpp>

namespace Drv {

    class ADCPacket : public Fw::TlmPacket {
        public:

            ADCPacket();
            virtual ~ADCPacket();

            Fw::SerializeStatus serialize(Fw::SerializeBufferBase& buffer) const; //!< serialize contents
            // setters
            void setV0(U32 v);
            void setV1(U32 v);
            void setV2(U32 v);
            void setV3(U32 v);
            void setV4(U32 v);
            void setV5(U32 v);
            void setV6(U32 v);
            void setV7(U32 v);
            void setV8(U32 v);

        PRIVATE:
            U32 v0;
            U32 v1;
            U32 v2;
            U32 v3;
            U32 v4;
            U32 v5;
            U32 v6;
            U32 v7;
            U32 v8;
    };

} /* namespace Drv */

#endif /* ADCPACKET_HPP_ */
