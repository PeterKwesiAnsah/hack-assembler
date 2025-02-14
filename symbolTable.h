#ifndef VMAP_H
#define VMAP_H
#define PRE_DEFINED_TABLE_SIZE 23
struct KVN {
    char *key;
    unsigned int value;
    struct KVN *next;
};
struct symTable {
    struct {
        char *key;
        unsigned int value;
    } predefined[PRE_DEFINED_TABLE_SIZE];
    struct KVN *runtime;
};
unsigned int *getSymValue(char *);
unsigned int *setSymValue(char *,unsigned int);
struct symTable *initSymTable(void);
#endif
//int * get(const char *key)
//void set (const char *key,int value)
//int *find(const char *key)
