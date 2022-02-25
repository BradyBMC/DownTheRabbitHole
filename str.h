//str.h - Contains the definions used by STR ADT
#ifndef __STR_H__ // Check if token has been defined
#define __STR_H__

#include <stdio.h>
#include <string.h>

// Creates and returns a String
//
// word: string to allocate memory for
//
char *str_create(char *word);

// Frees memory allocated for string
//
// in: string that is being free
//
void str_delete(char *in);

#endif
