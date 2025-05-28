#include "arena.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/_types/_null.h>

#define MIN_ARENA_CAP 256

struct Arena * create_arena(size_t capacity){
    struct Arena *new=malloc(sizeof(struct Arena));
    void *ptr=malloc(capacity);
    if (ptr==NULL){
        fputs("Not enough memory", stderr);
        exit(1);
    }
    new->memory=ptr;
    new->cap=capacity;
    new->offset=0;
    new->next=NULL;
    return new;
}

void * aalloc(struct Arena * arena,size_t size){
    struct Arena *current=arena;
    struct Arena *tail=NULL;

    struct Arena *avail=NULL;

    while(current!=NULL){
        tail=current;
        if(current->offset + size < current->cap){
            avail=current;
            break;
        }
        current=current->next;
    }
    if (avail==NULL){
        //create node
        avail=create_arena(MIN_ARENA_CAP);
        //attach node
        tail->next=avail;
    }
    //allocate memory
    void *ptr=avail->memory + avail->offset;
    avail->offset=avail->offset+size;
    return ptr;
}
