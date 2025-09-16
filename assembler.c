#include <_stdio.h>
#include <stdio.h>
#include "lexical-scanner.h"
#include "code-gen.h"


int main(int argc, char *argv[]){
    FILE *fsource=fopen(argv[1], "r");
    if (!fsource){
        fputs("Cannot open source file", stderr);
        return 1;
    }
     fseek(fsource, 0, SEEK_END);
     long size = ftell(fsource);
     rewind(fsource);
     char source[size];
     fread(source,size, 1, fsource);
     ScannerTokens tkns=scanner(source, size);
    fgenerate(tkns);
    return 0;
}
