#pragma once

#include <cstddef>

class MemoryBlock
{
    void* _memoryPtr;
    size_t _size = 0;

public:
    explicit MemoryBlock(size_t size);
    explicit MemoryBlock(void* ptr, size_t size);
    ~MemoryBlock();

    /**
     * Resize block saving content (truncate if shrink or fill end with zeroes if expand)
     * @param newSize
     */
    void resize(size_t newSize);

    void* getPtr();

    /**
     * Read only index op
     * @param index
     */
    const char operator[] (size_t index);

    MemoryBlock& operator= (MemoryBlock&& other) noexcept;

    size_t getSize() const;
};
