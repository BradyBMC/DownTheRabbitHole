#include "bv.h"
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

BitVector *bv_create(uint32_t bit_len) { //Inspiration from asgn3 and Oly in Lab
  BitVector *out = (BitVector *)malloc(sizeof(BitVector));
  if (!out) {
    return 0;
  }
  if (bit_len < 1) { //Edge case for negative length
    bit_len = 1;
  }
  out->length = bit_len;
  out->vector = (uint8_t *)calloc(
      (bit_len / 8 + 1), sizeof(uint8_t)); //Determine how many bits neeeded
  if (out->vector == NULL) { //Makes sure no mem leak
    free(out);
    return 0;
  }
  return out;
}

void bv_delete(BitVector *v) { //Frees memory used for create
  free(v->vector);
  free(v);
  return;
}

uint32_t bv_get_len(BitVector *v) { //Returns length for object oriented design
  if (!v) {
    return 0;
  }
  return v->length;
}

void bv_set_bit(BitVector *v,
    uint32_t i) { //Shfits 1 left and does or operator and store in bit
  v->vector[i / 8] |= (0x1 << (i % 8));
  return;
}

void bv_clr_bit(BitVector *v,
    uint32_t
        i) { //Clears bit by inverting with tilde and stores it using and operator
  v->vector[i / 8] &= ~(0x1 << (i % 8));
  return;
}

uint8_t bv_get_bit(
    BitVector *v, uint32_t i) { //Gets bit at index and performs and with 1
  if (!v) {
    return -1;
  }
  return (v->vector[i / 8] >> (i % 8)) & 1;
}

void bv_set_all_bits(BitVector *v) {
  for (uint32_t i = 0; i < (v->length) / 8 + 1;
       i++) { //Goes through and sets byte to all 1
    v->vector[i] |= 0xFF;
  }
  return;
}
