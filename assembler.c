#include <stdio.h>
#include "lexical-scanner.h"
#include "code-gen.h"


int main(){
    ScannerTokens tkns=scanner(stdin);
    fgenerate(tkns);
    return 0;
}
