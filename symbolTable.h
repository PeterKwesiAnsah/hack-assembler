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
struct KVN *getSymValue(char *);
struct KVN *setSymValue(char *,unsigned int);
struct symTable *initSymTable(void);
#endif
//int * get(const char *key)
//void set (const char *key,int value)
//int *find(const char *key)
