#ifndef VMAP_H
#define VMAP_H
#define PRE_DEFINED_TABLE_SIZE 23
struct KVN {
    char *key;
    unsigned int value;
    struct KVN *next;
};
struct symTable {
    struct KVN predefined[PRE_DEFINED_TABLE_SIZE];
    struct KVN *runtime;
};
struct KVN *getSymValue(struct KVN *,char *);
struct KVN *setSymValue(struct KVN *,char *,unsigned int);
struct KVN  *initSymTable(void);
#endif
