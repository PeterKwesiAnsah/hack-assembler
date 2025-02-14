#include <stdio.h>
#include <sys/_types/_null.h>
#include "tokenizer.h"
#include "parser.h"
#include "symbolTable.h"
#include "scanner.h"
#include "code.h"
#define TABLE_PRINT 0
#define INS_TOKENS_DEBUG 0
#define HACK_INS_PRINT 0
#if TABLE_PRINT
void print_symtable(const struct symTable *table) {
    if (!table) {
        printf("Error: NULL symbol table pointer\n");
        return;
    }

    // Print header
    printf("\n%-30s %-15s %-15s\n", "Key", "Value", "Type");
    printf("----------------------------------------------------\n");

    // Print predefined entries
    for (int i = 0; i < PRE_DEFINED_TABLE_SIZE; i++) {
        if (table->predefined[i].key) {  // Only print if key exists
            printf("%-30s %-13u %-15s\n",
                   table->predefined[i].key,
                   table->predefined[i].value,
                   "Predefined");
        }
    }

    printf("----------------------------------------------------\n\n");
    int i;
    for (i=0;i<TABLE_SIZE;i++){
        // Print runtime entries
        struct KVN *current = &table->runtime[i];
        if(current->key==NULL){
            continue;
        }
        while (current) {
            printf("%-30s %-13u %-15s\n",
                   current->key,
                   current->value,
                   "Runtime");
            current = current->next;
        }
        printf("----------------------------------------------------\n\n");
    }
}
#endif
#if INS_TOKENS_DEBUG
// Function to pretty print the instructions
void pretty_print_instructions(struct ins *head) {
    struct ins *current = head;
    int instruction_number = 1;

    while (current != NULL) {
        // Print the instruction number and the instruction itself
        printf("Instruction %d (Length: %d): %s\n", instruction_number, current->n, current->instruction);

        // Move to the next instruction
        current = current->next;
        instruction_number++;
    }
}
#endif
#if HACK_INS_PRINT
// Function to pretty print the tokens
void pretty_print_tokens(const struct Tokens *tokens) {
    for (size_t i = 0; i < tokens->count; i++) {
        struct token *current = tokens->darray[i];

        switch (current->tokenKind) {
            case A:
                printf("A Instruction: %s\n", current->tokenType.address);
                break;

            case C: {
                struct CIns *c_ins = current->tokenType.c;
                printf("C Instruction: dest=%s, comp=%s, jump=%s\n", c_ins->dest, c_ins->comp, c_ins->jump);
                break;
            }

            case LABEL:
                printf("LABEL: %s\n", current->tokenType.address);
                break;

            default:
                printf("Unknown instruction type\n");
                break;
        }
    }
}
#endif

int main(){
    struct ins *langIns=tokenizer();
    struct Tokens *parsedIns=langParser(langIns);
    initSymTable();
    labelScan(parsedIns);
    variableScan(parsedIns);
    translateCode(parsedIns);
    return 0;
}
