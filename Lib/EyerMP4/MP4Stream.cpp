#include "MP4Stream.hpp"
#include <math.h>


#define FP_SCALE 65536 // scaling factor

namespace Eyer {
    MP4Stream::MP4Stream(EyerBuffer &_buffer) {
        buffer = _buffer;
    }

    MP4Stream::~MP4Stream() {

    }

    uint64_t MP4Stream::ReadBigEndian_uint64(int &offset) {
        uint64_t val_net;
        buffer.CutOff((uint8_t *) &val_net, sizeof(uint64_t));

        offset += sizeof(uint64_t);

        return ntohll(val_net);
    }

    uint32_t MP4Stream::ReadBigEndian_uint32(int &offset) {
        uint32_t val_net;
        buffer.CutOff((uint8_t *) &val_net, sizeof(uint32_t));

        offset += sizeof(uint32_t);

        return ntohl(val_net);
    }

    uint16_t MP4Stream::ReadBigEndian_uint16(int &offset) {
        uint16_t val_net;
        buffer.CutOff((uint8_t *) &val_net, sizeof(uint16_t));

        offset += sizeof(uint16_t);

        return ntohs(val_net);
    }

    float MP4Stream::ReadBigEndianFixedPoint(unsigned int integerLength, unsigned int fractionalLength, int &offset) {
        uint32_t n;
        if (integerLength + fractionalLength == 16) {
            n = ReadBigEndian_uint16(offset);
        } else {
            n = ReadBigEndian_uint32(offset);
        }

        unsigned int integer        = n >> fractionalLength;
        unsigned int fractionalMask = pow(2, fractionalLength) - 1;
        float fractional            = (n & fractionalMask) * 1.0 / (1 << fractionalLength);


        return integer + fractional;
    }

    int MP4Stream::Skip(int len)
    {
        int offset;
        return Skip(len, offset);
    }

    int MP4Stream::Skip(int len, int & offset)
    {
        EyerBuffer b;
        buffer.CutOff(b, len);

        offset += len;

        return 0;
    }





    int MP4Stream::WriteBigEndian(uint64_t val)
    {
        uint64_t net_val = htonll(val);
        buffer.Append((uint8_t *)&net_val, sizeof(uint64_t));
        return sizeof(uint64_t);
    }

    int MP4Stream::WriteBigEndian(uint32_t val)
    {
        uint32_t net_val = htonl(val);
        buffer.Append((uint8_t *)&net_val, sizeof(uint32_t));
        return sizeof(uint32_t);
    }

    int MP4Stream::WriteBigEndian(uint16_t val)
    {
        uint16_t net_val = htons(val);
        buffer.Append((uint8_t *)&net_val, sizeof(uint16_t));
        return sizeof(uint16_t);
    }

    int MP4Stream::WriteBigEndian(uint8_t  val)
    {
        buffer.Append((uint8_t *)&val, sizeof(uint8_t));
        return sizeof(uint8_t);
    }

    int MP4Stream::WriteZero(int len)
    {
        unsigned char * a = (unsigned char *)malloc(len);
        memset(a, 0, len);
        buffer.Append(a, len);
        free(a);
        return len;
    }

    int MP4Stream::WriteBigEndianFixedPoint(float val, unsigned int integerLength, unsigned int fractionalLength)
    {
        if(integerLength == 16 && fractionalLength == 16){
            uint16_t i = (uint16_t)val;
            WriteBigEndian(i);

            float ff = val - i;

            unsigned int fractionalMask = pow(2, fractionalLength) - 1;
            uint16_t f = (uint16_t)(ff * fractionalMask);
            WriteBigEndian(f);
        }

        if(integerLength == 8 && fractionalLength == 8){
            uint8_t i = (uint8_t)val;
            WriteBigEndian(i);

            float ff = val - i;

            unsigned int fractionalMask = pow(2, fractionalLength) - 1;
            uint8_t f = (uint8_t)(ff * fractionalMask);
            WriteBigEndian(f);
        }

        return sizeof(uint32_t);
    }

    EyerBuffer & MP4Stream::GetBuffer()
    {
        return buffer;
    }
}