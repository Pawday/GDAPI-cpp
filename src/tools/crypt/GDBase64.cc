#include "GDBase64.hh"

#include <memory>

#define DECODE_TABLE_MIN_VAL 45
#define DECODE_TABLE_MAX_VAL 122
#define DECODE_TABLE_LEN 78

static const char *encodeTable =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "abcdefghijklmnopqrstuvwxyz"
    "0123456789-_";

static const unsigned char decodeTable[DECODE_TABLE_LEN] =
{
    0x3e, 0xff, 0xff, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39,
    0x3a, 0x3b, 0x3c, 0x3d, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0x45, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06,
    0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
    0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18,
    0x19, 0xff, 0xff, 0xff, 0xff, 0x3f, 0xff, 0x1a, 0x1b,
    0x1c, 0x1d, 0x1e, 0x1f, 0x20, 0x21, 0x22, 0x23, 0x24,
    0x25, 0x26, 0x27, 0x28, 0x29, 0x2a, 0x2b, 0x2c, 0x2d,
    0x2e, 0x2f, 0x30, 0x31, 0x32, 0x33
};


bool GDBase64::decode(MemoryBlock& data)
{
    size_t initialSize = data.getSize();

    if (initialSize % 4 != 0) return false;

    size_t decodedSize = initialSize / 4 * 3;

    char *inputData = (char*) data.getPtr();

    if (inputData[initialSize - 1] == '=') decodedSize--;
    if (inputData[initialSize - 2] == '=') decodedSize--;

    char *decodedData = new char[decodedSize];

    size_t chunksAm = initialSize / 4;
    
    for (size_t chunkIndex = 0; chunkIndex < chunksAm; chunkIndex++)
    {
        unsigned char i[4];
        unsigned char o[3];

        i[0] = inputData[chunkIndex * 4 + 0];
        i[1] = inputData[chunkIndex * 4 + 1];

        if (chunkIndex != chunksAm - 1)
        {
            i[2] = inputData[chunkIndex * 4 + 2];
            i[3] = inputData[chunkIndex * 4 + 3];
        }
        else
        {
            if (inputData[chunkIndex * 4 + 2] != '=')
                i[2] = inputData[chunkIndex * 4 + 2];
            else i[2] = 0;
            if (inputData[chunkIndex * 4 + 3] != '=')
                i[3] = inputData[chunkIndex * 4 + 3];
            else i[3] = 0;
        }



        i[0] = decodeTable[i[0] - DECODE_TABLE_MIN_VAL];
        i[1] = decodeTable[i[1] - DECODE_TABLE_MIN_VAL];

        if (chunkIndex != chunksAm - 1)
        {
            i[2] = decodeTable[i[2] - DECODE_TABLE_MIN_VAL];
            i[3] = decodeTable[i[3] - DECODE_TABLE_MIN_VAL];
        }
        else
        {
            if (i[2] != 0) i[2] = decodeTable[i[2] - DECODE_TABLE_MIN_VAL];
            if (i[3] != 0) i[3] = decodeTable[i[3] - DECODE_TABLE_MIN_VAL];
        }


        o[0] = (i[0] << 2) | (i[1] >> 4 & 0b11);
        o[1] = (i[1] << 4) | ((i[2] >> 2) & 0b1111);
        o[2] = (i[2] << 6) | (i[3] & 0b111111);

        decodedData[chunkIndex * 3 + 0] = (char) o[0];

        if (chunkIndex != chunksAm - 1)
        {
            decodedData[chunkIndex * 3 + 1] = (char) o[1];
            decodedData[chunkIndex * 3 + 2] = (char) o[2];
        }
        else
        {
            if (decodedSize > chunkIndex * 3 + 1) decodedData[chunkIndex * 3 + 1] = (char) o[1];
            if (decodedSize > chunkIndex * 3 + 2) decodedData[chunkIndex * 3 + 2] = (char) o[2];
        }

    }

    data.resize(decodedSize);
    memcpy_s(data.getPtr(), decodedSize, decodedData, decodedSize);

    delete[] decodedData;

    return true;
}

void GDBase64::encode(MemoryBlock& data)
{
    
}

