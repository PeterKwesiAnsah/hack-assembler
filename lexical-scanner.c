#include "lexical-scanner.h"
#include "arena.h"
#include "darray.h"



ScannerTokens tkns;
int line=0,clabel=0,variable=16;
ScannerTokens scanner(char *source,int len){
    struct Arena *amemory=create_arena(1024);
    int start=0,current=0;
    while(current<len){
        start=current;
        char c=source[current];
        current++;
        switch (c) {
        case '@':{
            clabel++;
            char isID=!isdigit(source[current]);
            for(;(source[current]!='\n');current++);
            //create ID or Number token
            struct token *tptr=(struct token *)aalloc(amemory, sizeof(struct token));
            tptr->tt=isID ? S_ID:S_NUMBER;
            tptr->lexeme=(&source[start])+1;
            tptr->len=(&source[current])-((&source[start])+1);
            //append to slice
            append(tkns, tptr, (sizeof(struct token *)));
            //TODO: if token is ID we insert into a symbol tabel
        break;
        }
        case '(':
            //Ldec
            while((source[current++]!=')'));
            //insert into a symbol tabel
         break;
         case '/':{
            char nextchar=source[current];
            //line comment
            if(nextchar=='/'){
                for(;(source[current]!='\n');current++);
                continue;
            }
            //single block comment
            //if(nextchar!='*')//wrong syntax, we don't worry about syntax error for now.

            // skip over '*'
            while((source[current++]!='*'));
            //skip over '/'
            current++;
            break;
         }
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
              tptr->len=destOp-(&source[start]);
              //append to slice
              append(tkns, tptr, (sizeof(struct token *)));
              {
                  //create comp token
                  struct token *tptr=(struct token *)aalloc(amemory, sizeof(struct token));
                  tptr->tt=S_COMP;
                  tptr->lexeme=destOp+1;
                  char *end=jumpOp ? jumpOp: &source[current];
                  tptr->len=end-(destOp+1);
                  //append to slice
                  append(tkns, tptr, (sizeof(struct token *)));
              }
            }else {
                clabel++;
                //create dest token (null)
                struct token *tptr=(struct token *)aalloc(amemory, sizeof(struct token));
                tptr->tt=S_DEST;
                tptr->lexeme=NULL;
                tptr->len=0;
                //append to slice
                append(tkns, tptr, (sizeof(struct token *)));
            }
            if(jumpOp){
                //create jump0p
                struct token *tptr=(struct token *)aalloc(amemory, sizeof(struct token));
                tptr->tt=S_JMP;
                tptr->lexeme=jumpOp+1;
                tptr->len=&source[current]-(jumpOp+1);
                //append to tokens slice
                append(tkns, tptr, (sizeof(struct token *)));
                //TODO: create Comp
            }else {
                //create jump token (null)
                struct token *tptr=(struct token *)aalloc(amemory, sizeof(struct token));
                tptr->tt=S_JMP;
                tptr->lexeme=NULL;
                tptr->len=0;
                //append to tokens slice
                append(tkns, tptr, (sizeof(struct token *)));
            }
           break;
        }
    }
    }
    return tkns;
}
