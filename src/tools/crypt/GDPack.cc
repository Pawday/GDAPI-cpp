#include <iostream>
#include "GDPack.hh"

#include <zlib.h>

#define UNPACK_BUFFER_CHUNK_SIZE 1024000


bool GDPack::unpack(MemoryBlock &data)
{
    z_stream stream;

    
    MemoryBlock unpackBuffer(UNPACK_BUFFER_CHUNK_SIZE);

    stream.zalloc = Z_NULL;
    stream.zfree = Z_NULL;
    stream.opaque = Z_NULL;

    stream.avail_in = data.getSize();
    stream.next_in = (Byte *) data.getPtr();


    int status = inflateInit2(&stream, MAX_WBITS + 32);
    if (status != Z_OK) return false;

    int inflateStatus = Z_OK;

    size_t unpackBufferOffset = 0;
    size_t unpackChunkIndex = 1;



    while (inflateStatus != Z_STREAM_END)
    {
        unpackBuffer.resize(unpackChunkIndex * UNPACK_BUFFER_CHUNK_SIZE);
        stream.avail_out = UNPACK_BUFFER_CHUNK_SIZE;
        stream.next_out = (Byte*) unpackBuffer.getPtr() + unpackBufferOffset;

        inflateStatus = inflate(&stream, Z_SYNC_FLUSH);

        if (inflateStatus < 0) return false;
        unpackBufferOffset = stream.total_out;
        unpackChunkIndex++;
    }

    unpackBuffer.resize(stream.total_out);
    
    data = std::move(unpackBuffer);

    return true;
}