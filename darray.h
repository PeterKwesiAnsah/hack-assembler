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
        size_t allocap=slice.cap == 0 ? DEFAULT_SLICE_CAP: (2 * DEFAULT_SLICE_CAP);\
        void *ptr = malloc(DEFAULT_SLICE_CAP*size); \
        if (ptr!=NULL) { \
            slice.cap=allocap;  \
            slice.array=ptr;    \
            slice.array[slice.len++]=el;    \
        }else{ fputs(stderr,"Not enough memory"); exit(1); } \
    }\
} while(0)
#endif
