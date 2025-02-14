#ifndef PARSE_H
#define PARSE_H
#include <stddef.h>
#include "tokenizer.h"
enum Kind {A,C,LABEL};
struct AIns {
    int n;//number of the address characters
    char address;//address
};
struct CIns {
    char dest[4];
    char comp[4];
    char jump[4];
};
struct token {
    enum Kind tokenKind;
    union {
        char *address;
        struct CIns *c;
    } tokenType;
};

struct Tokens {
//number of tokens stored currently
size_t  count;
//maximum number of tokens
size_t capacity;
struct token **darray;
};

struct Tokens *langParser(struct ins *);
#endif
