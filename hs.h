// hs.h - Contains the definiions used by the hatterspeak ADT

#ifndef __HS_H__ // Check if token has been defined already
#define __HS_H__

#ifndef NIL
#define NIL (void *)0
#endif

#include <stdio.h>

// Definition of a Hatterspeak, a dynamically allocated struct holding 2 strings
//
// oldspeak: oldspeak words
// hatterspeak: hatterspeak translations
//
typedef struct HatterSpeak {
  char *oldspeak;
  char *hatterspeak;
} HatterSpeak;

// Creates and returns a hatterspeak
//
// oldspeak: string used to create struct
//
HatterSpeak *hs_create(char *oldspeak);

// Frees memory for hatterspeak
//
// in: hatterspeak being freed
//
void hs_delete(HatterSpeak *in);

#endif
