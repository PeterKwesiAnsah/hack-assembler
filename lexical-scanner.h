#ifndef LEX
#define LEX
#include "darray.h"
enum tokenType {S_COMP,S_DEST,S_JMP,S_LABEL,S_A};
struct token {
    enum tokenType tt;
    //cannot be used as a string but as a character array.
    char *lexeme;
    int len;
};
//create tokens slice type
slice(struct token *, ScannerTokens)
ScannerTokens scanner(char *source,int len);
#endif
