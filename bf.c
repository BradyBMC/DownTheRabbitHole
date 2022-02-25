#include "bf.h"
#include "speck.h"
#include <stdlib.h>

#include <stdio.h>

BloomFilter *bf_create(uint32_t size) {
  BloomFilter *bf = (BloomFilter *)malloc(sizeof(BloomFilter));
  if (bf) {
    bf->primary[0] = 0xfc28ca6885711cf7;
    bf->primary[1] = 0x2841af568222f773;
    bf->secondary[0] = 0x85ae998311115ae3;
    bf->secondary[1] = 0xb6fac2ae33a40089;
    bf->tertiary[0] = 0xd37b01df0ae8f8d0;
    bf->tertiary[1] = 0x911d45886ca7cf7;
    BitVector *vector = bv_create(size);
    bf->filter = vector;
    return bf;
  }
  return (BloomFilter *)NIL;
}

//Frees memory for bloom filter and uses bv delete to remove bit vector
void bf_delete(BloomFilter *bf) {
  bv_delete(bf->filter);
  free(bf);
  return;
}

//Inserts new word into bloomfilter by hashing
void bf_insert(BloomFilter *bf, char *key) {
  uint32_t index;
  uint32_t length = bv_get_len(bf->filter);
  index = hash(bf->primary, key) % length;
  bv_set_bit(bf->filter, index);
  index = hash(bf->secondary, key) % length;
  bv_set_bit(bf->filter, index);
  index = hash(bf->tertiary, key) % length;
  bv_set_bit(bf->filter, index);
  return;
}

//Checks bloomfilter if the word already exists
bool bf_probe(BloomFilter *bf, char *key) {
  uint32_t index;
  uint32_t length = bv_get_len(bf->filter);
  index = hash(bf->primary, key) % length;
  bool firstCheck = bv_get_bit(bf->filter, index);
  index = hash(bf->secondary, key) % length;
  bool secondCheck = bv_get_bit(bf->filter, index);
  index = hash(bf->tertiary, key) % length;
  bool thirdCheck = bv_get_bit(bf->filter, index);
  return firstCheck && secondCheck && thirdCheck;
}
