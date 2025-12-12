#ifndef HASHTABLE_H
#define HASHTABLE_H

typedef struct Nlist {
    struct Nlist *next;
    char *key;
    char *val;
} Nlist;

typedef struct HashTable {
    Nlist **buckets;
    int size;
} HashTable;

HashTable *create_table(int size);
Nlist *install(HashTable *hash_table, char *key, char *val);
Nlist *lookup(HashTable *hash_table, char *key);

#endif
