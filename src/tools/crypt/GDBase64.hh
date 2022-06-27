#pragma once

#include "gdapi/tools/MemoryBlock.hh"

struct GDBase64
{
    static bool decode(MemoryBlock& data);
    static void encode(MemoryBlock& data);
};
