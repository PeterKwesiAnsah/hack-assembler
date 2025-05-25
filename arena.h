#ifndef ARENA
#define ARENA
#include <stddef.h>
#include <stdint.h>
struct Arena {
    uint8_t *memory;
    size_t  offset;
    size_t cap;
    struct Arena *next;
};
struct Arena * create_arena(size_t capacity);
void * aalloc(struct Arena *,size_t);
#endif
