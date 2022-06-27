#include <cassert>
#include <memory>

#include "gdapi/tools/MemoryBlock.hh"

MemoryBlock::MemoryBlock(size_t size) : _size(size)
{
    this->_memoryPtr = new char[size];
}

MemoryBlock::MemoryBlock(void *ptr, size_t size) : _memoryPtr(ptr), _size(size) {}

MemoryBlock::~MemoryBlock()
{
    this->_size = 0;
    delete[] reinterpret_cast<char*>(this->_memoryPtr);
}

void *MemoryBlock::getPtr()
{
    return this->_memoryPtr;
}

size_t MemoryBlock::getSize() const
{
    return this->_size;
}

const char MemoryBlock::operator[](size_t idx)
{
    assert(idx < this->_size);
    return ((const char*) this->_memoryPtr)[idx];
}


void MemoryBlock::resize(size_t newSize) 
{
    if (this->_size == newSize) return;

    char *newPtr = new char[newSize];

    if (newSize < this->_size)
        memcpy_s(newPtr, newSize, this->_memoryPtr, newSize);
    else
        memcpy_s(newPtr, newSize, this->_memoryPtr, this->_size);

    if (newSize > this->_size)
        memset(newPtr + this->_size, 0, newSize - this->_size);

    delete[] ((char*) this->_memoryPtr);
    this->_memoryPtr = newPtr;

    this->_size = newSize;
}

MemoryBlock &MemoryBlock::operator=(MemoryBlock &&other) noexcept
{
    delete[] ((char*) this->_memoryPtr);

    this->_memoryPtr = other._memoryPtr;
    this->_size = other._size;

    other._memoryPtr = nullptr;
    return *this;
}


