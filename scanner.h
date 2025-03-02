#ifndef SCANNER_H
#include "parser.h"
#define SCANNER_H
#define TABLE_SIZE 57
void labelScan(struct Tokens *);
void variableScan(struct Tokens *);
#endif
