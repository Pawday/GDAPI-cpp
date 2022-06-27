#pragma once

#include "gdapi/tools/MemoryBlock.hh"

/**
 * MemoryBlock = XOR > Truncate > GDBase64 > Gzip
 * MemoryBlock = Gzip > GDBase64 > XOR
 */

struct GDCoder
{
    /**
     * Decode MemoryBlock
     * @param input modifiable dataBlock
     * @return decode status
     */
    static bool decode(MemoryBlock& block);

    /**
     * Encode GD MemoryBlock
     * @param input modifiable dataBlock
     * @return encode status
     */
    static bool encode(MemoryBlock& block);
};