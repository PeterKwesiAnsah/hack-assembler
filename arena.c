#include "arena.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/_types/_null.h>

struct Arena * create_arena(size_t capacity){
    static struct Arena new={};
    void *ptr=malloc(capacity);
    if (ptr==NULL){
        fputs("Not enough memory", stderr);
        exit(1);
    }
    new.memory=ptr;
    new.cap=capacity;
    new.offset=0;
    new.next=NULL;
    return &new;
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

    return NULL;
}
