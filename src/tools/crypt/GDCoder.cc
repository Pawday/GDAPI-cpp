#include <iostream>
#include "gdapi/tools/crypt/GDCoder.hh"

#include "GDXor.hh"
#include "GDBase64.hh"
#include "GDPack.hh"


static void truncateZeroes(MemoryBlock& data)
{
    size_t payloadSize = 0;
    size_t dataSize = data.getSize();
    char *pVoid = static_cast<char *>(data.getPtr());

    while (payloadSize != dataSize && pVoid[payloadSize] != 0) payloadSize++;
    data.resize(payloadSize);
}

bool GDCoder::decode(MemoryBlock& data)
{
    GDXor::XorData(data);
    truncateZeroes(data);
    if (!GDBase64::decode(data)) return false;
    if (!GDPack::unpack(data)) return false;

    return true;
}

bool GDCoder::encode(MemoryBlock& data)
{
    return false;
}
