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
ScannerTokens scanner(FILE *source){
    struct Arena *amemory=create_arena(65536);
    struct KVN *rtable= initSymTable();
    unsigned int start=0,pos=0;
    char c='\0';
    //we can have a pos variable to mimic ftell result
    while((c=getchar(),pos++,c!=EOF)){

        start=pos-1;

        switch (c) {
        case '@':{
            clabel++;
            char cur=getchar();
            pos++;
            char isID=!isdigit(cur);
            while((cur!='\n' && cur!=EOF )){
                cur=getchar();
                pos++;
            };
            line++;
            //NB: it skips over new line
            // (ftell(source))-1 gets you &source[current]
            const size_t lexemeLen =(pos-1)-(start+1);
            //create ID or Number token
            // +1 for null character
            struct token *tptr=(struct token *)aalloc(amemory, sizeof(struct token)+(lexemeLen+1));
            tptr->tt=isID ? S_ID:S_NUMBER;
            tptr->lexeme = ((char *)tptr) + sizeof(struct token);

            //copy from source (at which file position??)
            // before read

            fseek(source, start+1, SEEK_SET);

            fread((((char *)tptr) + sizeof(struct token)), lexemeLen,1, source);

            //restore file position
            fseek(source, pos, SEEK_SET);

            //null character
            tptr->lexeme[lexemeLen]='\0';
            tptr->len=lexemeLen;

            //append to slice
            append(tkns, tptr, (sizeof(struct token *)));
        break;
        }
        case '(':{
            //Ldec
            char cur=getchar();
            pos++;
            while((cur!=')' && cur!=EOF )){
                cur=getchar();
                pos++;
            };
            //ftell(source) is at ')'+1
            char *lexeme=(char *)aalloc(amemory,((pos-1)-(start+1))+1);

            //copy from source
            // before read
            //size_t ori_pos=ftell(source);
            fseek(source, start+1, SEEK_SET);

            fread(lexeme,((pos-1)-(start+1)),1,source);

            //restore file position
            fseek(source, pos, SEEK_SET);

            unsigned int lexemeLen=((pos-1)-(start+1));
            lexeme[lexemeLen]='\0';
            //build a symtable for label declaration
            setSymValue(rtable, lexeme, clabel+1);
            break;
        }
         case '/':{
            //line comment
            char cur=getchar();
            pos++;
            while((cur!='\n' && cur!=EOF )){
                cur=getchar();
                pos++;
            };
            line++;
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
            unsigned int destOp = 0;
            unsigned int jumpOp = 0;
            char cur=getchar();
            pos++;
            while((cur!='\n' && cur!=EOF )){
                if(cur=='='){
                    destOp=pos-1;
                } else if (cur==';') {
                   jumpOp= pos-1;
                }
                cur=getchar();
                pos++;
            };
            line++;

            if(destOp){
              clabel++;
              //create dest token
              unsigned int lexemeLen=destOp-start;
              //+1 for null character
              struct token *tptr=(struct token *)aalloc(amemory, sizeof(struct token)+((destOp-start)+1));
              tptr->tt=S_DEST;
              tptr->lexeme = ((char *)tptr) + sizeof(struct token);

              //copy from source
              // before read
              //size_t ori_pos=ftell(source);
              fseek(source, start, SEEK_SET);

              //assert(destOp-start < 20);
              fread((((char *)tptr) + sizeof(struct token)), destOp-start,1, source);

              //restore position
              fseek(source, pos, SEEK_SET);
              //null character
              tptr->lexeme[lexemeLen]='\0';
              tptr->len=lexemeLen;

              //append to slice
              append(tkns, tptr, (sizeof(struct token *)));
              {
                  //create comp token
                  // (pos is at '\n' + 1)
                  unsigned int end = jumpOp==0 ? (pos-1): jumpOp;
                  unsigned int lexemeLen=end-(destOp+1);
                  //+1 for null character
                  struct token *tptr=(struct token *)aalloc(amemory, sizeof(struct token)+((end-(destOp+1))+1));
                  tptr->tt=S_COMP;
                  tptr->lexeme = ((char *)tptr) + sizeof(struct token);
                  tptr->len=end-(destOp+1);

                  //copy from source (at which file position??)
                  // before read
                  //size_t ori_pos=ftell(source);
                  fseek(source, destOp+1, SEEK_SET);

                  fread((((char *)tptr) + sizeof(struct token)), (end-(destOp+1)),1, source);

                  //restore original position
                  fseek(source, pos, SEEK_SET);


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
                if(destOp==0){
                    //create comp token
                    //+1 for null character
                    struct token *tptr=(struct token *)aalloc(amemory, sizeof(struct token)+((jumpOp-start)+1));
                    tptr->tt=S_COMP;
                    tptr->lexeme = ((char *)tptr) + sizeof(struct token);
                    tptr->len=jumpOp-start;

                    //copy from source
                    // before read
                    //size_t ori_pos=ftell(source);
                    fseek(source, start, SEEK_SET);

                    fread((((char *)tptr) + sizeof(struct token)), (jumpOp-start),1, source);
                    fseek(source, pos, SEEK_SET);

                    //null character
                    tptr->lexeme[(jumpOp-start)]='\0';

                    //append to slice
                    append(tkns, tptr, (sizeof(struct token *)));
                }
                //create jump0p
                //// (pos is at '\n' + 1)
                unsigned int lexemeLen=(pos-1)-(jumpOp+1);
                struct token *tptr=(struct token *)aalloc(amemory, sizeof(struct token)+((pos-1)-(jumpOp+1) + 1));
                tptr->tt=S_JMP;
                tptr->lexeme = ((char *)tptr) + sizeof(struct token);
                tptr->len=(pos-1)-(jumpOp+1);

                //copy from source
                //before read
                //size_t ori_pos=ftell(source);
                fseek(source, jumpOp+1, SEEK_SET);

                fread((((char *)tptr) + sizeof(struct token)), (pos-1)-(jumpOp+1), 1,source);

                //restore original position
                fseek(source,pos,SEEK_SET);
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
