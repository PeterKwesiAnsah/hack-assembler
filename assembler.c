#include <stdio.h>
#include "lexical-scanner.h"
#include "code-gen.h"


int main(int argc, char *argv[]){
    if (argc!=2) {
        fputs("Usage: assembler [sourcefile] >[outputfile]\n",stderr);
        return 1;
    }
    FILE *fsource=fopen(argv[1],"r");
    if (!fsource){
        fputs("Cannot open source file",stderr);
        return 1;
    }
    ScannerTokens tkns=scanner(fsource);
    fgenerate(tkns);
    return 0;
}
