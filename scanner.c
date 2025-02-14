//resolves variables and goto declarations.
#include "scanner.h"
#include "symbolTable.h"
#include "parser.h"
#include <stdio.h>
#include <string.h>
#include <sys/_types/_null.h>
#include <stdlib.h>
#define VARIABLE_ADDRESS 16


unsigned address=VARIABLE_ADDRESS;
int HACK_MEM_ADDRESS=-1;
void labelScan(struct Tokens *ins){;
    int count=ins->count;
    for(int i=0;i<count;i++){
        if(ins->darray[i]->tokenKind==LABEL){
            //Naive Solution:under the assumption that there's a C or A ins ahead.
            //Ideal Solution:search if there's a C or A ins ahead
            setSymValue(ins->darray[i]->tokenType.address, (unsigned)(HACK_MEM_ADDRESS+1));
        }
        else {
            HACK_MEM_ADDRESS++;
        }
    }
}


void variableScan(struct Tokens *ins){
    int i;
    for(i=0;i<ins->count;i++){

        if(!(ins->darray[i]->tokenKind==A))
            continue;

        char *variable = ins->darray[i]->tokenType.address;
        char *p_end = NULL;
        unsigned long strToLong = strtoul(variable, &p_end, 10);
        if(*p_end=='\0')
            continue;
        if(getSymValue(variable)==NULL && strToLong==0){
            setSymValue(variable, address++);
        }
    }
}
