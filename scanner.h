//first pass label declarations...takes a pointer to a symTable
//second pass address variables...takes a pointer to a symTable
#ifndef SCANNER_H
#include "parser.h"
#define SCANNER_H
#define TABLE_SIZE 57
void labelScan(struct Tokens *);
void variableScan(struct Tokens *);
#endif
