#include "str.h"
#include <stdlib.h>

//Allocates memory for string in hatterspeak
//
char *str_create(char *word) {
  char *out = (char *)malloc((strlen(word) + 1));
  if (!out) {
    return 0;
  }
  memcpy(out, word, strlen(word) + 1); //Copy memory over to string
  return out;
}

//Frees memory allocated by str_create
//
void str_delete(char *in) {
  free(in);
  return;
}
