#ifndef _ENGINE__MEMORY_H
#define _ENGINE__MEMORY_H


struct memory_block
{
    s64 Size;
    s64 Used;
    u8* Base;
};


internal_function inline void
InitializeMemoryBlock(memory_block* block, memory_size size, u8* base)
{
    block->Size = size;
    block->Base = base;
    block->Used = 0;
}

#define Memory_PushArray(block, elementCount, type) (type*)push_size_(block, (elementCount) * sizeof(type))
#define Memory_PushStruct(block, type) (type*)push_size_(block, sizeof(type))
#define Memory_PushSize(block, size) push_size_(block, size)

internal_function inline  void*
push_size_(memory_block* block, memory_size size)
{
    ASSERT((block->Used + size) <= block->Size);
    void* result = (block->Base + block->Used);
    block->Used += size;
    return(result);
}


#endif //_ENGINE__MEMORY_H
