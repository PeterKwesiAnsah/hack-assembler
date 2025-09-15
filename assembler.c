#include <stdio.h>
#include "lexical-scanner.h"
#include "code-gen.h"


int main(){
     fseek(stdin, 0, SEEK_END);
     long size = ftell(stdin);
     rewind(stdin);
     char source[size];
     fread(source,size, 1, stdin);
     ScannerTokens tkns=scanner(source, size);
    fgenerate(tkns);
    return 0;
}
