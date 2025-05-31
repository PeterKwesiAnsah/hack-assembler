#ifndef LEX
#define LEX
#include "darray.h"
#include <ctype.h>
enum tokenType {S_COMP,S_DEST,S_JMP,S_LABEL,S_ID,S_NUMBER};
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
