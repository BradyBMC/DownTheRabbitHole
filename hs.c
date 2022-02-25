#include "hs.h"
#include "str.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Creates a hatterspeak and sets oldspeak equal to input
//
HatterSpeak *hs_create(char *oldspeak) {
  HatterSpeak *word = (HatterSpeak *)malloc(sizeof(HatterSpeak));
  if (!word) {
    return 0;
  }
  word->oldspeak = oldspeak;
  word->hatterspeak = NULL;
  return word;
}
//Frees the memory allocated and frees object
//
void hs_delete(HatterSpeak *in) {
  str_delete(in->oldspeak);
  str_delete(in->hatterspeak);
  free(in);
  return;
}
