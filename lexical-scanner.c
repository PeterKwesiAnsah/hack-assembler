#include "lexical-scanner.h"


ScannerTokens tkns;
int line,clabel=1;
ScannerTokens scanner(char *source,int len){
    int start,current=0;
    while(current<len){
        start=current;
        char c=source[current];
        current++;
        switch (c) {
         case '@':
            break;
         default:
            break;
        }
    }
    return tkns;
}
