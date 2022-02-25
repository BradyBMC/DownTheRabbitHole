//hash.h - Contains the definitions used by the Hashtable ADT

#ifndef __HASH_H__ //Ceck if token has already been defined
#define __HASH_H__

#ifndef NIL
#define NIL (void *)0
#endif

#include "ll.h"
#include <inttypes.h>

//
// Definitions of a HashTable, a dynamically allocated hash table
//
// salt: used to hash words into index
// length: size of hash table
// heads: beginning of linked lists
typedef struct HashTable {
  uint64_t salt[2];
  uint32_t length;
  ListNode **heads;
} HashTable;

// Creates and returns a hash table
//
// length: The size of the hash table
//
HashTable *ht_create(uint32_t length);

// Deletes the hash table
//
// ht: hash table that is deleted
//
void ht_delete(HashTable *ht);

// Counts for each list node head in hash table
//
// ht: hash table being counted
//
uint32_t ht_count(HashTable *ht);

// Looks through hash table to find if word can be found in linked list
//
// ht: hash table being searched
// key: string being searched for
//
ListNode *ht_lookup(HashTable *ht, char *key);

// Inserts a new linked list node into hash table
//
// gs: struct used to make linked list
//
void ht_insert(HashTable *ht, HatterSpeak *gs);

#endif
