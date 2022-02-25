#include "hash.h"
#include "speck.h"
#include <stdio.h>
#include <stdlib.h>

HashTable *ht_create(uint32_t length) {
  HashTable *ht = (HashTable *)malloc(sizeof(HashTable));
  if (ht) {
    ht->salt[0] = 0x85ae998311115ae3;
    ht->salt[1] = 0xb6fac2ae33a40089;
    ht->length = length;
    ht->heads = (ListNode **)calloc(length, sizeof(ListNode *));
    return ht;
  }
  return (HashTable *)NIL;
}

//Frees memory allocted by hash table
//
void ht_delete(HashTable *ht) {
  for (uint32_t i = 0; i < ht->length;
       i++) { //Runs through for each index of hash table
    if (ht->heads[i]) {
      ll_delete(ht->heads[i]);
    }
  }
  free(ht->heads);
  free(ht);
  return;
}

//Counts the hashtable length for each ehad at index
//
uint32_t ht_count(HashTable *h) {
  uint32_t count = 0;
  for (uint32_t i = 0; i < h->length; i++) {
    if (h->heads[i]) {
      count++;
    }
  }
  return count;
}

//Hash to get index in hash table and uses ll_lookup to search linked list
//
ListNode *ht_lookup(HashTable *ht, char *key) {
  uint32_t index;
  index = hash(ht->salt, key) % ht->length;
  return ll_lookup(&ht->heads[index], key);
}

//Inserts new linked list at index of hash table
//
void ht_insert(HashTable *ht, HatterSpeak *gs) {
  char *key = gs->oldspeak;
  uint32_t index = hash(ht->salt, key) % ht->length;
  ll_insert(&ht->heads[index], gs);
  return;
}
