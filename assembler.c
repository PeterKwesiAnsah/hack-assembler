#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "darray.h"
#include "lexical-scanner.h"



int main(){
    //testing A(number) and C ins (with dest)
    char *hack_program =
    "@2\n"
    "D=A\n"
    "@3\n"
    "D=D+A\n"
    "@0\n"
    "M=D\n";
    ScannerTokens programResults=scanner(hack_program, strlen(hack_program));
    struct token *expectedTkns[] = {
        &(struct token){S_NUMBER, "2", 1},
        &(struct token){S_DEST, "D", 1},
        &(struct token){S_COMP, "A", 1},
        &(struct token){S_JMP, NULL, 0},
        &(struct token){S_NUMBER, "3", 1},
        &(struct token){S_DEST, "D", 1},
        &(struct token){S_COMP, "D+A", 3},
        &(struct token){S_JMP, NULL, 0},
        &(struct token){S_NUMBER, "0", 1},
        &(struct token){S_DEST, "M", 1},
        &(struct token){S_COMP, "D", 1},
        &(struct token){S_JMP, NULL, 0},
    };
    int array_size=(sizeof(expectedTkns)/sizeof(expectedTkns[0]));
    ScannerTokens expectedResults={DEFAULT_SLICE_CAP,array_size};
    expectedResults.arr=expectedTkns;
    //assert slice lengths
    assert(programResults.len==expectedResults.len);
    //assert individual tokens
    for(int i=0;i<array_size;i++){
        //assert token members (token type)
        assert(expectedResults.arr[i]->tt==programResults.arr[i]->tt);
        //assert token members (token lexeme)
        //
        // assert tokem members (len)
        assert(expectedResults.arr[i]->len==programResults.arr[i]->len);
    }
    return 0;
}
