#ifndef LEX
#define LEX
#include "darray.h"
enum tokenType {COMP,DEST,JMP,LABEL,A};
struct token {
    enum tokenType tt;
    char *lexeme;
};
//create tokens slice type
slice(struct token, ScannerTokens)
ScannerTokens scanner(char *source,int len);
#endif
