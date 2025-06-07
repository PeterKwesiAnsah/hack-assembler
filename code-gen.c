#include "code-gen.h"
#include "lexical-scanner.h"
#include "symbolTable.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <sys/_types/_null.h>


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
    {"", "000"}, {"M", "001"},    {"D", "010"},    {"MD", "011"},
    {"A", "100"},    {"AM", "101"},   {"AD", "110"},   {"AMD", "111"}
};

KeyValuePair jump_table[] = {
    {"", "000"}, {"JGT", "001"},  {"JEQ", "010"},  {"JGE", "011"},
    {"JLT", "100"},  {"JNE", "101"},  {"JLE", "110"},  {"JMP", "111"}
};

void fgenerate(ScannerTokens tokens, FILE * f){
unsigned int i=0,variable=16;
while(i<tokens.len){
    enum tokenType curtt=tokens.arr[i]->tt;
    char hackMachineCode[HACK_MACHINE_WORD+1];
    hackMachineCode[HACK_MACHINE_WORD]='\0';
    if(curtt==S_ID || curtt==S_NUMBER){
        char *p_end = NULL;
        hackMachineCode[0]='0';
        unsigned long strInt;
        //a ins
        if(curtt==S_NUMBER){
            //translate directly
            strInt = strtoul(tokens.arr[i]->lexeme, &p_end, 10);
        }else{
            //lookup id in table
            struct KVN *trow=getSymValue(tokens.arr[i]->lexeme);
            if(trow!=NULL){
                 strInt =  trow->value;
            }else{
                 strInt=variable;
                 setSymValue(tokens.arr[i]->lexeme, variable++);
            }
        }
        int startIndex=HACK_MACHINE_WORD-1,endIndex=1,shiftPlaces=0;
        for(; startIndex>=endIndex;(startIndex--,shiftPlaces++)){
            hackMachineCode[startIndex]=((strInt & 1<<shiftPlaces) > 0) ? '1':'0';
        }
        fprintf(f,"%s\n",hackMachineCode);
        //genc++;
        i++;
    }else {
        char *dest = NULL;
        char *comp = NULL;
        char *jmp = NULL;
        hackMachineCode[0] = '1';
        hackMachineCode[1] = '1';
        hackMachineCode[2] = '1';
        hackMachineCode[3] = '0';

        // Search dest_table
        assert(tokens.arr[i]->tt == S_DEST);
        {
        for(int j = 0; j < DEST_TABLE_SIZE; j++) {
            if(strcmp(dest_table[j].key, tokens.arr[i]->lexeme) == 0) {
                dest = dest_table[j].value;
                break;
            }
        }
        }

        // Search comp_table
        assert(tokens.arr[i+1]->tt == S_COMP);
        char comp_lexeme[4]; // Create a copy
        strcpy(comp_lexeme, tokens.arr[i+1]->lexeme);
        char *searchChar = strchr(comp_lexeme, 'M');
        if(searchChar) {
            *searchChar = 'A';
            hackMachineCode[3] = '1';
        }
        {

        for(int j = 0; j < COMP_TABLE_SIZE; j++) {
            if(strcmp(comp_table[j].key, comp_lexeme) == 0) {
                comp = comp_table[j].value;
                break;
            }
        }
        }

        // Search jump_table
        assert(tokens.arr[i+2]->tt == S_JMP);
        {
        for(int j = 0; j < JUMP_TABLE_SIZE; j++) {
            if(strcmp(jump_table[j].key, tokens.arr[i+2]->lexeme) == 0) {
                jmp = jump_table[j].value;
                break;
            }
        }
        }

        memcpy(hackMachineCode+DEST_HACK_START_INDEX,dest, DEST_HACK_LEN);
        memcpy(hackMachineCode+COMP_HACK_START_INDEX,comp, COMP_HACK_LEN);
        memcpy(hackMachineCode+JUMP_HACK_START_INDEX,jmp , JUMP_HACK_LEN);
        fprintf(f,"%s\n",hackMachineCode);
        i=i+3;
    }
}
}
