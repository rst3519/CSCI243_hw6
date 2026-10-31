/**
 * @file hash.c
 * @brief Integer-to-integer hash table using separate chaining.
 *
 * @author Rohit Tripathi
 */

#include <stdlib.h>
#include <stddef.h>

#include "hash.h"

/** # of buckets in table */
#define NUM_BUCKETS 16

/** key value pairings */
typedef struct Entry {
    int key;             /** < key */
    int value;           /**< value stored */
    struct Entry *next;  /**< next entry, or NULL */
} Entry;

/** The table itself */
struct HashTable {
    Entry *buckets[NUM_BUCKETS];  /**< head chain */
    size_t size;                  /**< number of pairs */
};

/**
 * Map a key to index
 *
 * @param key the key
 * @return index in the range
 */
static size_t bucketIndex(int key) {
    return (size_t)((unsigned int)key % NUM_BUCKETS);
}

/**
 * entry holding a key.
 *
 * @param self the table to search
 * @param key the key to look for
 * @return the matching entry, or NULL if the key doesnt exist
 */
static Entry *findEntry(const HashTable *self, int key) {
    Entry *cur = self->buckets[bucketIndex(key)];

    while (cur != NULL) {
        if (cur->key == key) {
            return cur;
        }
        cur = cur->next;
    }

    return NULL;
}

HashTable *ht_create(void) {
    /* sets every bucket to NULL and size to zero */
    return calloc(1, sizeof(HashTable));
}

void ht_destroy(HashTable *self) {
    if (self == NULL) {
        return;
    }
    for (size_t i = 0; i < NUM_BUCKETS; i++) {

        Entry *cur = self->buckets[i];

        while (cur != NULL) {
            Entry *next = cur->next;  /* save before freeing */
            free(cur);
            cur = next;
        }
    }
    free(self);
}

void ht_put(HashTable *self, int key, int value) {
    Entry *existing = findEntry(self, key);

    if (existing != NULL) {
        existing->value = value;
        return;
    }

    Entry *e = malloc(sizeof(Entry));

    if (e == NULL) {
        return;  /* table unchanged */
    }
    size_t b = bucketIndex(key);
    e->key = key;
    e->value = value;
    e->next = self->buckets[b];
    self->buckets[b] = e;
    self->size++;
}

int ht_get(const HashTable *self, int key, int *found) {

    Entry *e = findEntry(self, key);

    if (e == NULL) {
        *found = 0;
        return 0;
    }

    *found = 1;
    return e->value;
}

int ht_contains(const HashTable *self, int key) {
    return findEntry(self, key) != NULL;
}

int ht_remove(HashTable *self, int key) {

    Entry **link = &self->buckets[bucketIndex(key)];

    while (*link != NULL) {
        Entry *cur = *link;
        if (cur->key == key) {
            *link = cur->next;  /* unlink */
            free(cur);
            self->size--;
            return 1;
        }
        link = &cur->next;
    }

    return 0;
}

size_t ht_size(const HashTable *self) {

    return self->size;
}
