#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <dark/Foundation.h>

type (MemoryPool)
{
    long count;
    long total;
    long size;
    void* ptr;
};

method MemoryPool* New(MemoryPool* self, long size, long total)
{
    self->count = 0;
    self->total = total;
    self->size = size;
    self->ptr = DSmalloc(size * total);
    return self;
}
method void Dispose(MemoryPool* self)
{
    if (_use_gc) return;
    free(self->ptr);
}
method void* Alloc(MemoryPool* self)
{
    if (self->count >= self->total) {
        Log("Enable to allocate memory");
        return nullptr;
    }
    void* ptr = self->ptr + (self->count * self->size);
    self->count += 1;
    return memset(ptr, 0, self->size);
}
