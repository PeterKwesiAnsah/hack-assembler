//produce code from stream of tokens
#ifndef CODE_GEN
#include "lexical-scanner.h"
#include <stdio.h>
#define HACK_MACHINE_WORD 16
#include <string.h>
#define COMP_HACK_LEN 6
#define DEST_HACK_LEN 3
#define JUMP_HACK_LEN 3

#define COMP_HACK_START_INDEX 4
#define DEST_HACK_START_INDEX 10
#define JUMP_HACK_START_INDEX 13

#define COMP_TABLE_SIZE 18
#define DEST_TABLE_SIZE 8
#define JUMP_TABLE_SIZE 8
#define CODE_GEN
void fgenerate(ScannerTokens);
#endif
