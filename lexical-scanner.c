#include "lexical-scanner.h"
#include "arena.h"
#include "darray.h"
#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <memory.h>
#include <stdio.h>
#include <string.h>
#include "symbolTable.h"



ScannerTokens tkns={0,0,NULL};

unsigned int line=0,clabel=-1;
ScannerTokens scanner(char *source,int len){
    struct Arena *amemory=create_arena(1024);
    struct KVN *table=initSymTable();
    int start=0,current=0;
    while(current<len){
        start=current;
        char c=source[current];
        current++;
        switch (c) {
        case '@':{
            clabel++;
            char isID=!isdigit(source[current]);
            for(;(source[current]!='\n' && source[current]!=EOF );current++);
            const size_t lexemeLen =(&source[current])-((&source[start])+1);
            //create ID or Number token
            // +1 for null character
            struct token *tptr=(struct token *)aalloc(amemory, sizeof(struct token)+(lexemeLen+1));
            tptr->tt=isID ? S_ID:S_NUMBER;
            tptr->lexeme = ((char *)tptr) + sizeof(struct token);

            //copy from source
            memcpy((((char *)tptr) + sizeof(struct token)),(&source[start])+1, lexemeLen);
            //null character
            tptr->lexeme[lexemeLen]='\0';
            tptr->len=lexemeLen;

            //append to slice
            append(tkns, tptr, (sizeof(struct token *)));
        break;
        }
        case '(':{
            //Ldec
            for(;(source[current]!=')');current++);
            char *lexeme=(char *)aalloc(amemory,((&source[current])-(&source[start]+1))+1);
            memcpy(lexeme,(&source[start]+1),((&source[current])-(&source[start]+1)));
            const size_t lexemeLen=((&source[current])-(&source[start]+1));
            lexeme[lexemeLen]='\0';
            //build a symtable for label declaration
            setSymValue(table, lexeme, clabel+1);
            //skip over ')'
            current++;
            break;
        }
         case '/':{
            //line comment
            for(;(source[current]!='\n' && source[current]!=EOF);current++);
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
            for(;(charcur=source[current],(charcur!='\n' && source[current]!=EOF));current++){
                if(charcur=='='){
                    destOp=source + current;
                }else if (charcur==';') {
                    jumpOp=source + current;
                }
            }
            if(destOp){
              clabel++;
              //create dest token
              const size_t lexemeLen=destOp-(&source[start]);
              //+1 for null character
              struct token *tptr=(struct token *)aalloc(amemory, sizeof(struct token)+(lexemeLen+1));
              tptr->tt=S_DEST;
              tptr->lexeme = ((char *)tptr) + sizeof(struct token);

              //copy from source
              memcpy((((char *)tptr) + sizeof(struct token)),(&source[start]), lexemeLen);
              //null character
              tptr->lexeme[lexemeLen]='\0';
              tptr->len=lexemeLen;

              //append to slice
              append(tkns, tptr, (sizeof(struct token *)));
              {
                  //create comp token
                  char *end=jumpOp ? jumpOp: &source[current];
                  const size_t lexemeLen=end-(destOp+1);
                  //+1 for null character
                  struct token *tptr=(struct token *)aalloc(amemory, sizeof(struct token)+(lexemeLen+1));
                  tptr->tt=S_COMP;
                  tptr->lexeme = ((char *)tptr) + sizeof(struct token);
                  tptr->len=end-(destOp+1);

                  //copy from source
                  memcpy((((char *)tptr) + sizeof(struct token)),(destOp+1), lexemeLen);
                  //null character
                  tptr->lexeme[lexemeLen]='\0';

                  //append to slice
                  append(tkns, tptr, (sizeof(struct token *)));
              }
            }else {
                clabel++;
                //create dest token (null)
                struct token *tptr=(struct token *)aalloc(amemory, sizeof(struct token)+1);
                tptr->tt=S_DEST;
                tptr->lexeme=((char *)tptr) + sizeof(struct token);
                tptr->lexeme[0]='\0';
                tptr->len=0;
                //append to slice
                append(tkns, tptr, (sizeof(struct token *)));
            }
            if(jumpOp){
                //TODO: refactor as CREATE_COMP macro
                if(!destOp){
                    //create comp token
                    char *end=jumpOp;
                    const size_t lexemeLen=end-(&source[start]);
                    //+1 for null character
                    struct token *tptr=(struct token *)aalloc(amemory, sizeof(struct token)+(lexemeLen+1));
                    tptr->tt=S_COMP;
                    tptr->lexeme = ((char *)tptr) + sizeof(struct token);
                    tptr->len=end-(&source[start]);

                    //copy from source
                    memcpy((((char *)tptr) + sizeof(struct token)),(&source[start]), lexemeLen);
                    //null character
                    tptr->lexeme[lexemeLen]='\0';

                    //append to slice
                    append(tkns, tptr, (sizeof(struct token *)));
                }
                //create jump0p
                const size_t lexemeLen=&source[current]-(jumpOp+1);
                struct token *tptr=(struct token *)aalloc(amemory, sizeof(struct token)+(lexemeLen + 1));
                tptr->tt=S_JMP;
                tptr->lexeme = ((char *)tptr) + sizeof(struct token);
                tptr->len=&source[current]-(jumpOp+1);

                //copy from source
                memcpy((((char *)tptr) + sizeof(struct token)),(jumpOp+1), lexemeLen);
                //null character
                tptr->lexeme[lexemeLen]='\0';

                //append to tokens slice
                append(tkns, tptr, (sizeof(struct token *)));
            }else {
                //create jump token (null)
                struct token *tptr=(struct token *)aalloc(amemory, sizeof(struct token)+1);
                tptr->tt=S_JMP;
                tptr->lexeme=((char *)tptr) + sizeof(struct token);
                tptr->lexeme[0]='\0';
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
