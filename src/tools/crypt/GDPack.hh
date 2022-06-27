#pragma once

#include "gdapi/tools/MemoryBlock.hh"

struct GDPack
{
    static bool unpack(MemoryBlock &data);
    static bool pack(MemoryBlock &data);
};