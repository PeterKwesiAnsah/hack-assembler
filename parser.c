#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parser.h"
#include "tokenizer.h"

#define CHAR_START_AINS '@'
#define CHAR_START_LABEL '('
#define DEST_OPERATOR '='
#define JUMP_OPERATOR ';'
#define ALLOC_FACTOR 2


size_t resize(struct Tokens *tokenXS){
    size_t newCap;
    if(tokenXS->capacity==0){
        tokenXS->darray=NULL;
        newCap=256;
    }else{
      newCap=tokenXS->capacity * 2;
    }
    tokenXS->darray=(struct token **)realloc(tokenXS->darray, newCap * sizeof(struct token *));
    return newCap;
};
void append(struct Tokens *tokenXS, struct token *p){
    if(tokenXS->count>=tokenXS->capacity){
       size_t newSize= resize(tokenXS);
        ASSERT_MALLOC(tokenXS->darray, "failed to allocate memory\n")
        tokenXS->capacity=newSize;
    }
    tokenXS->darray[tokenXS->count++]=p;
};


struct Tokens *langParser(struct ins *tokens){
   struct ins *cur=tokens;
   //initizializing tokens dynamic array
   struct Tokens static ins = {0, 0,NULL};

    while(cur){
        int startOfIns=cur->instruction[0];
        if(startOfIns==CHAR_START_AINS){
            //A instruction -> @Value
            struct token *AIns=(struct token*)malloc(sizeof(struct token));
            ASSERT_MALLOC(AIns, "failed to allocate memory\n")
            char *curInstructionAddress=cur->instruction;
            AIns->tokenKind=A;
            //TODO: free memory occupied by link node??
            AIns->tokenType.address=(char *)malloc(sizeof(*cur->instruction)*cur->n);
            ASSERT_MALLOC(AIns->tokenType.address, "failed to allocate memory\n")
            memcpy(AIns->tokenType.address, ++curInstructionAddress,cur->n);
            append(&ins, AIns);
        }else if (startOfIns== CHAR_START_LABEL) {
             struct token *labelIns=(struct token*)malloc(sizeof(struct token));
             ASSERT_MALLOC(labelIns, "failed to allocate memory\n")
             labelIns->tokenKind=LABEL;
             labelIns->tokenType.address=(char *)calloc(1,sizeof(*cur->instruction)*cur->n);
             ASSERT_MALLOC(labelIns->tokenType.address, "failed to allocate memory\n")
             char *p=cur->instruction;
            //TODO: free memory occupied by link node??
             memcpy(labelIns->tokenType.address, ++p, cur->n-2);
             append(&ins, labelIns);
        }else {
            //C instruction -> dest=comp;jump
            struct token *CIns=(struct token*)malloc(sizeof(struct token));
            ASSERT_MALLOC(CIns, "failed to allocate memory\n")
            CIns->tokenKind=C;
            CIns->tokenType.c=(struct CIns*)calloc(1,sizeof(struct CIns));
            ASSERT_MALLOC(CIns->tokenType.c, "failed to allocate memory\n");


            char *insP=cur->instruction;

            char *destOperatorP=strchr(insP, DEST_OPERATOR);
            char *jumpOperatorP=strchr(insP, JUMP_OPERATOR);
            char *nullCharP=cur->instruction+cur->n;

            //0;JMP
            //dest null
            //comp 0
            if(destOperatorP){
                //handing dest
                //TODO: we can use parameteriezed macro
                char *dest=CIns->tokenType.c->dest;
                char *src=cur->instruction;
                memcpy(dest, src, destOperatorP-src);
                //handing comp
                {
                    //TODO: we can use parameteriezed macro
                    char *dest=CIns->tokenType.c->comp;
                    char *src=destOperatorP+1;
                    memcpy(dest, src,(jumpOperatorP ? jumpOperatorP:nullCharP)-src);
                }
            }
            if(jumpOperatorP) {
                //move comp only when it has not been handled or dest is null
                //TODO: we can use parameteriezed macro
                char *dest=CIns->tokenType.c->jump;
                char *src=jumpOperatorP+1;
                memcpy(dest, src, nullCharP-src);
                if(!destOperatorP){
                    char *dest=CIns->tokenType.c->comp;
                    char *src=jumpOperatorP-1;
                    memcpy(dest, src, jumpOperatorP-insP);
                }
            }
            append(&ins, CIns);
        }
        cur=cur->next;
    }

    return &ins;
}
