#ifndef NIL
#define NIL (void *)0
#endif

#ifndef __BF_H__ //Check if token has already been defined
#define __BF_H__

#include "bv.h"
#include <inttypes.h>
#include <stdbool.h>

//bf.h contains the defnitions used by the bloomfilter ADT
//
//Definition of a bloomfilter, a dynamically allocated bit vector with salts
//
// primary, second, third: salts used to hash
// filter: a bit vector to store bits

typedef struct Bloomfilter {
  uint64_t primary[2];
  uint64_t secondary[2];
  uint64_t tertiary[2];
  BitVector *filter;
} BloomFilter;

// Creates and returns a BloomFilter
//
// size: length of the bloomfilter
//
BloomFilter *bf_create(uint32_t size);

// Frees a bloom filter
//
// bf: bloom filter to free
//
void bf_delete(BloomFilter *bf);

// Adds a wordto bloom filter
//
// bf: bloom filter that gets added to
// key: word that gets added
//
void bf_insert(BloomFilter *bf, char *key);

// Checks if bloom filter has the word
//
// bf: bloom filter checked
// key: word that is checked for
//
bool bf_probe(BloomFilter *bf, char *key);

#endif
