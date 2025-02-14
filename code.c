#include "code.h"
#include "parser.h"
#include "symbolTable.h"
#include <stdio.h>
#define HACK_MACHINE_WORD 16
#include <string.h>
#include <stdlib.h>
#define COMP_HACK_LEN 6
#define DEST_HACK_LEN 3
#define JUMP_HACK_LEN 3

#define COMP_HACK_START_INDEX 4
#define DEST_HACK_START_INDEX 10
#define JUMP_HACK_START_INDEX 13

#define COMP_TABLE_SIZE 18
#define DEST_TABLE_SIZE 8
#define JUMP_TABLE_SIZE 8


typedef struct {
    char* key;
    char* value;
} KeyValuePair;

KeyValuePair comp_table[] = {
    {"0", "101010"},    {"1", "111111"},    {"-1", "111010"},   {"D", "001100"},
    {"A", "110000"},    {"!D", "001101"},   {"!A", "110001"},   {"-D", "001111"},
    {"-A", "110011"},   {"D+1", "011111"},  {"A+1", "110111"},  {"D-1", "001110"},
    {"A-1", "110010"},  {"D+A", "000010"},  {"D-A", "010011"},  {"A-D", "000111"},
    {"D&A", "000000"},  {"D|A", "010101"}
};

KeyValuePair dest_table[] = {
    {"null", "000"}, {"M", "001"},    {"D", "010"},    {"MD", "011"},
    {"A", "100"},    {"AM", "101"},   {"AD", "110"},   {"AMD", "111"}
};

KeyValuePair jump_table[] = {
    {"null", "000"}, {"JGT", "001"},  {"JEQ", "010"},  {"JGE", "011"},
    {"JLT", "100"},  {"JNE", "101"},  {"JLE", "110"},  {"JMP", "111"}
};


void translateCode(struct Tokens *ins){
    int i;
    int count=ins->count;
    for(i=0;i<count;i++){
        if(ins->darray[i]->tokenKind==A) {
            //numOfIns++;
            char *variable = ins->darray[i]->tokenType.address;
            char *p_end = NULL;

            char hackMachineCode[HACK_MACHINE_WORD+1];
            memset(hackMachineCode, '0', HACK_MACHINE_WORD );
            hackMachineCode[0]='0';
            hackMachineCode[HACK_MACHINE_WORD]='\0';

            if (*variable == '0' && strlen(variable) == 1){
                //print string
                printf("%s\n",hackMachineCode);
                continue;
            }
            unsigned long strToLong = strtoul(variable, &p_end, 10);
            if(*p_end){
                const unsigned *addressValue=getSymValue(variable);
                if(!addressValue){
                    continue;
                }
                strToLong=*addressValue;
            }

            for(int startIndex=HACK_MACHINE_WORD-1,endIndex=1,shiftPlaces=0; startIndex>=endIndex;startIndex--,shiftPlaces++){
                int test=(strToLong & 1<<shiftPlaces) > 0;
                hackMachineCode[startIndex]=test ? '1':'0';
            }
            //print string
            printf("%s\n",hackMachineCode);
        }
        else if (ins->darray[i]->tokenKind==C){
            //numOfIns++;
            char hackMachineCode[HACK_MACHINE_WORD+1];
            memset(hackMachineCode, '0', HACK_MACHINE_WORD );
            hackMachineCode[0]='1';
            hackMachineCode[1]='1';
            hackMachineCode[2]='1';
            hackMachineCode[HACK_MACHINE_WORD]='\0';

            char *comp=ins->darray[i]->tokenType.c->comp;
            char *dest=ins->darray[i]->tokenType.c->dest;
            char *jump=ins->darray[i]->tokenType.c->jump;
            char *searchChar=NULL;

            //involves M
            if((searchChar=strchr(comp,'M'))){
                //replace M with A
                *searchChar='A';
                hackMachineCode[3]='1';
            }

            int compIndex=-1,destIndex=-1,jumpIndex=-1;
            int compStrCmpRes=-1,destStrCmpRes=-1,jumpStrCmpRes=-1;

            //Find instruction
            while ((compIndex + 1) < COMP_TABLE_SIZE && (compStrCmpRes=strcmp(comp,comp_table[++compIndex].key)));
            while ((destIndex + 1) < DEST_TABLE_SIZE && (destStrCmpRes=strcmp(dest,dest_table[++destIndex].key)));
            while ((jumpIndex + 1) < JUMP_TABLE_SIZE && (jumpStrCmpRes=strcmp(jump,jump_table[++jumpIndex].key)));
            //conditional moves
            if(compStrCmpRes==0){
                memcpy(hackMachineCode+COMP_HACK_START_INDEX,comp_table[compIndex].value , COMP_HACK_LEN);
            }
            if(destStrCmpRes==0){
                memcpy(hackMachineCode+DEST_HACK_START_INDEX,dest_table[destIndex].value, DEST_HACK_LEN);
            }
            if(jumpStrCmpRes==0){
                memcpy(hackMachineCode+JUMP_HACK_START_INDEX,jump_table[jumpIndex].value , JUMP_HACK_LEN);
            }
            printf("%s\n",hackMachineCode);
        }
    }
}
