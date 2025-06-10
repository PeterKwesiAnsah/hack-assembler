#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "darray.h"
#include "lexical-scanner.h"
#include "code-gen.h"


int main(){

    struct timespec start, end;
       double diff;

       clock_gettime(CLOCK_MONOTONIC, &start);

       fseek(stdin, 0, SEEK_END);
       long size = ftell(stdin);
       rewind(stdin);
       char source[size];
       fread(source,size, 1, stdin);
       ScannerTokens tkns=scanner(source, size);
       fgenerate(tkns, stdout);

       clock_gettime(CLOCK_MONOTONIC, &end);

       diff = (end.tv_sec - start.tv_sec) * 1e9;
       diff = (diff + (end.tv_nsec - start.tv_nsec)) * 1e-9;

       fprintf(stderr,"Elapsed time: %lf seconds\n", diff);

    return 0;
}
