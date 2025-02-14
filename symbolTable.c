#include "symbolTable.h"
#include "scanner.h"
#include "tokenizer.h"
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <sys/_types/_null.h>
#define FILL_KVN(node)  node->key=key;\
                        node->value=value;\
                        return &node->value;\


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

struct symTable *initSymTable(void){
    hackLangTable.runtime=calloc(TABLE_SIZE,sizeof(*hackLangTable.runtime));
    ASSERT_MALLOC(hackLangTable.runtime, "Failed to Initialize Symtable\n");
    return &hackLangTable;
};

struct KVN *createKVN(struct KVN *head){
    struct KVN *new=malloc(sizeof(*head));
    ASSERT_MALLOC(new, "Failed to Create KVN\n");
    struct KVN *temp=head->next;
    head->next=new;
    new->next=temp;
    return new;
};

unsigned int *getSymValue(char *key){
     if (!key) return NULL;
    //search and find in predefined table
    for (int i=0;i<PRE_DEFINED_TABLE_SIZE;i++){
        if(strcmp(key, hackLangTable.predefined[i].key)==0){
            return &hackLangTable.predefined[i].value;
        }
    }
    unsigned tableIndex=hash(key);
    struct KVN *cur=&hackLangTable.runtime[tableIndex];
    if(cur->value==0){
        return NULL;
    }
    while(cur){
        if(strcmp(key, cur->key)==0){
            return &cur->value;
        }
        cur=cur->next;
    }
    return NULL;
};

unsigned int *setSymValue(char *key, unsigned int value){
    unsigned tableIndex=hash(key);
    struct KVN *head=&hackLangTable.runtime[tableIndex];
    if(getSymValue(key)==NULL){
    //no entry for such key found
     if(head->value==0){
      FILL_KVN(head)
     }
     struct KVN *new=createKVN(head);
      FILL_KVN(new)
    }
    return NULL;
};
