#include "lexical-scanner.h"
#include "arena.h"
#include <sys/_types/_null.h>



ScannerTokens tkns;
int line,clabel=0;
ScannerTokens scanner(char *source,int len){
    struct Arena *amemory=create_arena(1024);
    int start,current=0;
    while(current<len){
        start=current;
        char c=source[current];
        current++;
        switch (c) {
        case '@':
            //Ains
            for(;(source[current]!='\n');current++)
            //create A ins token
            //append to slice
        break;
        case '(':
            //Ldec
            while((source[current++]!=')'))
            //create Label dec token
         break;
         case '/':
             //comment
            for(;(source[current]!='\n');current++)
        break;
       	case ' ':
          break;
		case '\r':
          break;
		case '\t':
		  break;
        case '\n':
            ++line;
        break;
        default:{
            //find dest,jump operators
            char *destOp =NULL;
            char *jumpOp=NULL;
            char charcur;
            for(;(charcur=source[current],charcur!='\n');current++){
                if(charcur=='='){
                    destOp=source + current;
                }else if (charcur==';') {
                    destOp=source + current;
                }
            }
            if(destOp){
              //create dest token
              struct token *tptr=(struct token *)aalloc(amemory, sizeof(struct token));
              tptr->tt=S_DEST;
              tptr->lexeme=&source[start];
              tptr->len=destOp-&source[start];
              //append to slice
              {
                  //create comp token
                  struct token *tptr=(struct token *)aalloc(amemory, sizeof(struct token));
                  tptr->tt=S_COMP;
                  tptr->lexeme=destOp+1;
                  char *end=jumpOp ? jumpOp: &source[current];
                  tptr->len=end-destOp+1;
                  //append to slice
              }
            }else {
                //create dest token (null)
                struct token *tptr=(struct token *)aalloc(amemory, sizeof(struct token));
                tptr->tt=S_DEST;
                tptr->lexeme=NULL;
                tptr->len=0;
                //append to slice
            }
            if(jumpOp){
                //create jump0p
                struct token *tptr=(struct token *)aalloc(amemory, sizeof(struct token));
                tptr->tt=S_JMP;
                tptr->lexeme=jumpOp+1;
                tptr->len=&source[current]-jumpOp+1;
                //append to slice
            }else {
                //create jump token (null)
                struct token *tptr=(struct token *)aalloc(amemory, sizeof(struct token));
                tptr->tt=S_JMP;
                tptr->lexeme=NULL;
                tptr->len=0;
                //append to slice
            }
           break;
        }
        }
    }
    return tkns;
}
