#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <stdio.h>
#define MIN_INS_LEN 3
#define ASSERT_MALLOC(ptr,msg)     if((ptr)==NULL){ \
    fprintf(stderr, msg); \
    exit(EXIT_FAILURE); \
} \

struct ins{
    int n;//where n is the number of characters in the instruction
    struct ins *next;//a pointer to the next instruction.
    char instruction[];//instruction container.
};

struct ins *tokenizer(void);
#endif
