#ifndef LEX
#define LEX
#include "darray.h"
#include <stdio.h>
#include <ctype.h>
enum tokenType {S_COMP,S_DEST,S_JMP,S_LABEL,S_ID,S_NUMBER};
struct token {
    enum tokenType tt;
    //cannot be used as a string.
    char *lexeme;
    int len;
};
//create tokens slice type
slice(struct token *, ScannerTokens)
ScannerTokens scanner(FILE *source);
#endif
