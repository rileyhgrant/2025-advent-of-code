#include "hashtable.h"
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

HashTable *create_table(int size)
{
    struct HashTable *hash_table = malloc(sizeof(HashTable));

    hash_table->size = size;
    hash_table->buckets = calloc(size, sizeof(Nlist *));

    return hash_table;
}

unsigned hash(HashTable *hash_table, char *s)
{
    unsigned hashval;
    for (hashval = 0; *s != '\0'; s++) {
        hashval = *s + 31 * hashval;
    }

    return hashval % hash_table->size;
}

Nlist *lookup(HashTable *hash_table, char *s)
{
    Nlist *np;

    for (np = hash_table->buckets[hash(hash_table, s)]; np != NULL;
         np = np->next) {
        if (strcmp(s, np->key) == 0) {
            return np;
        }
    }

    return NULL;
}

Nlist *install(HashTable *hash_table, char *key, char *val)
{
    struct Nlist *np;
    unsigned hashval;

    if ((np = lookup(hash_table, key)) == NULL) {
        np = (Nlist *)malloc(sizeof(*np));
        if (np == NULL || (np->key = strdup(key)) == NULL) {
            return NULL;
        }

        hashval = hash(hash_table, key);

        np->next = hash_table->buckets[hashval];
        hash_table->buckets[hashval] = np;
    } else {
        free((void *)np->val);
    }

    if ((np->val = strdup(val)) == NULL) {
        return NULL;
    }

    return np;
}
