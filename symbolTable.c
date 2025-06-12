#include "symbolTable.h"
#include <assert.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "arena.h"
#include "darray.h"


#define TABLE_SIZE 57

#define FILL_KVN(node) do { \
    node->key=key; \
    node->value=value; \
    return node; \
} while(0)

struct Arena * amemory;
struct symTable hackLangTable = {
    .predefined = {
        {"R0", 0},
        {"R1", 1},
        {"R2", 2},
        {"R3", 3},
        {"R4", 4},
        {"R5", 5},
        {"R6", 6},
        {"R7", 7},
        {"R8", 8},
        {"R9", 9},
        {"R10", 10},
        {"R11", 11},
        {"R12", 12},
        {"R13", 13},
        {"R14", 14},
        {"R15", 15},
        {"SCREEN", 16384},
        {"KBD", 24576},
        {"SP", 0},
        {"LCL", 1},
        {"ARG", 2},
        {"THIS", 3},
        {"THAT", 4}
    },
    .runtime = NULL
};

unsigned hash(const char *v){
    unsigned h;
    for (h=0;*v!='\0';v++)
    	h=(64*h + *v) % TABLE_SIZE;
    return h;
}

struct KVN *initSymTable(void){
  amemory=create_arena(65536);
  hackLangTable.runtime = (struct KVN *)aalloc(amemory,(TABLE_SIZE*sizeof(struct KVN)));
  return hackLangTable.runtime;
};

struct KVN *createKVN(struct KVN *head){
    struct KVN *new=aalloc(amemory,sizeof(*head));
    struct KVN *temp=head->next;
    head->next=new;
    new->next=temp;
    return new;
};

 struct KVN  *getSymValue(struct KVN *rtable,char *key){
     if (!key) return NULL;
    //search and find in predefined table
    for (int i=0;i<PRE_DEFINED_TABLE_SIZE;i++){
        if(strcmp(key, hackLangTable.predefined[i].key)==0){
            return &(hackLangTable.predefined[i]);
        }
    }
    unsigned tableIndex=hash(key);
    struct KVN *cur=&rtable[tableIndex];
    //assert the initial cur is a valid head
    assert(cur->value==0 && cur->next==NULL);

    while(cur){
        if(cur->key && strcmp(key, cur->key)==0){
            return cur;
        }
        cur=cur->next;
    }
    return NULL;
};

struct KVN *setSymValue(struct KVN *rtable,char *key, unsigned int value){
    unsigned tableIndex=hash(key);
    struct KVN *head=&rtable[tableIndex];
    assert(head->value==0 && head->next==NULL);
    struct KVN *node=getSymValue(rtable,key);
    if(node==NULL){
     struct KVN *new=createKVN(head);
      FILL_KVN(new);
    }else{
        FILL_KVN(node);
    }
};
