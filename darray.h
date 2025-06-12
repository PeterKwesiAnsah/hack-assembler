#ifndef DYNAMIC_ARRAY
#define DYNAMIC_ARRAY
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#define slice(type,name) \
typedef struct {   \
    size_t cap;\
    size_t len;\
    type *arr;\
} name;
#define DEFAULT_SLICE_CAP 256
#define append(slice,el,size) do{ \
    if (slice.len >= slice.cap) \
       { \
        size_t allocap=slice.cap == 0 ? DEFAULT_SLICE_CAP: (2 * slice.cap);\
        void *ptr = realloc(slice.arr,allocap*size); \
        if (ptr!=NULL) { \
            slice.cap=allocap;  \
            slice.arr=ptr;    \
            slice.arr[slice.len++]=el;\
        }else{ fputs("Not enough memory",stderr); exit(1); } \
    } else{ slice.arr[slice.len++]=el; } \
} while(0)
#endif
