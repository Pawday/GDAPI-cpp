#include "GDXor.hh"

void GDXor::XorData(MemoryBlock& memoryBlock)
{
    char* cntPtr = reinterpret_cast<char*>(memoryBlock.getPtr());
    for (size_t i = 0; i < memoryBlock.getSize(); i++)
        cntPtr[i] ^= 0xB;
}

