#include "bf.h"
#include "bv.h"
#include "hash.h"
#include "hs.h"
#include "ll.h"
#include "parser.h"
#include "str.h"

#include <getopt.h>
#include <inttypes.h>
#include <regex.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

extern uint32_t seeks;
extern uint32_t trav;

//Main function that uses all helper function to take in 2 text files and user input

int main(int argc, char **argv) {
  int c;
  uint32_t h_size = 10000;
  uint32_t b_size = 1048576; //2 ^ 20
  bool stats = false;
  bool b_used = false;
  bool m_used = false;
  char eachword[1000];
  char *old = NULL;
  char *hatter = NULL;
  move_to_front = false;
  while ((c = getopt(argc, argv, "sh:f:mb")) != -1) {
    switch (c) {
    case 's':
      stats = true;
      break;
    case 'h':
      h_size = atoi(optarg);
      break;
    case 'f':
      b_size = atoi(optarg);
      break;
    case 'm':
      if (b_used) {
        puts("m and b contradict");
        return 0;
      }
      move_to_front = true;
      m_used = true;
      break;
    case 'b':
      if (m_used) {
        puts("m and b contradict");
        return 0;
      }
      b_used = true;
      break;
    }
  }
  FILE *fp = fopen("oldspeak.txt", "r");
  if (!fp) {
    return 1;
  }
  BloomFilter *bf
      = bf_create(b_size); //Creates bloom filter objects and check if null
  if (!bf) {
    return 1;
  }
  HashTable *ht = ht_create(h_size);

  //Adds  text file into the bloomfilter and hash table
  while (fscanf(fp, "%s\n", eachword) != EOF) {
    bf_insert(bf, eachword);
    old = str_create(eachword); //Allocates memory for string
    HatterSpeak *hs = hs_create(old); //Create hs object and pass string
    ht_insert(ht, hs);
  }
  fclose(fp);
  fp = fopen("hatterspeak.txt", "r");
  if (!fp) {
    return 1;
  }

  //Adds hatterspeak words in bloomfilter and hashtable
  while (fscanf(fp, "%s", eachword) != EOF) {
    bf_insert(bf, eachword);
    old = str_create(eachword);
    HatterSpeak *hs = hs_create(old);
    fscanf(fp, "%s", eachword);
    hatter = str_create(eachword);
    hs->hatterspeak = hatter;
    ht_insert(ht, hs);
  }
  fclose(fp);

  ListNode *kindabad
      = NULL; //2 different linked list to hold the bad word nodes found
  ListNode *reallybad = NULL;
  regex_t word_regex;
  if (regcomp(&word_regex, "[a-zA-Z0-9_]+(('|-)[a-zA-Z0-9_]*)*",
          REG_EXTENDED)) { //Compiles regex to be used
    printf("expr was wrong\n");
    return 0;
  }
  char *myword = NULL;
  //Runs through to see if user input is bloom filter, and then check
  while (
      (myword = next_word(stdin, &word_regex))) { //Runs as long as user input
    for (uint32_t i = 0; i < strlen(myword); i++) {
      if (myword[i] >= 65 && myword[i] <= 90) {
        myword[i] = myword[i] + 32; //Uses ascii to change case
      }
    }
    if (bf_probe(bf, myword)) { //If the word is in the bloom filter
      ListNode *node
          = ht_lookup(ht, myword); //Checks to make sure not a false positive
      if (node) {
        if (node->gs->hatterspeak
            != NULL) { //Determines if it is a hatterspeak or oldspeak
          HatterSpeak *hs = hs_create(str_create(node->gs->oldspeak));
          hs->hatterspeak = str_create(node->gs->hatterspeak);
          if (kindabad == NULL) { //Checks if null to create new node
            ListNode *head = ll_node_create(hs);
            kindabad = head;
          } else {
            ll_insert(&kindabad, hs);
          }
        } else {
          HatterSpeak *hs = hs_create(str_create(node->gs->oldspeak));
          if (reallybad == NULL) {
            ListNode *head = ll_node_create(hs);
            reallybad = head;
          } else {
            ll_insert(&reallybad, hs);
          }
        }
      }
    } else {
      continue;
    }
  }

  ListNode *rhead = NULL; //Used to save the first node of reallybad
  ListNode *khead = NULL;
  //Prints stats or letter with the illegal words
  if (stats) {
    double asl = (double)trav / seeks; //Extern variable counted for stats
    double alll = (double)seeks / h_size;
    double htl = (double)ht_count(ht) / h_size * 100;
    double count = 0;
    for (uint32_t i = 0; i < b_size; i++) { //Checks if bf is 1 for used bits
      if (bv_get_bit(bf->filter, i) == 1) {
        count++;
      }
    }
    double bfl = count / b_size * 100;
    printf("Seeks: %u\n", seeks);
    printf("Average seek length: %f\n", asl);
    printf("Average Linked List Length: %f\n", alll);
    printf("Hash table load: %f%%\n", htl);
    printf("Bloom filter load: %f%%\n", bfl);
  } else {
    if (kindabad
        && reallybad) { //Series of print statements dependent on kindabadn and reallybad
      printf("Dear Comrade,\n\nYou have chosen to use words that the queen has "
             "decreed oldspeak.\n");
      printf("Due to your infraction you will be sent to the dungeon where you "
             "will be taught hatterspeak.\n\n");
      printf("Your errors:\n\n");
      rhead = reallybad;
      khead = kindabad;
      while (reallybad) {
        printf("%s\n", reallybad->gs->oldspeak);
        reallybad = reallybad->next;
      }
      printf("\nAppropriate hatterspeak translations.\n\n");
      while (kindabad) {
        printf("%s -> %s\n", kindabad->gs->oldspeak, kindabad->gs->hatterspeak);
        kindabad = kindabad->next;
      }
    } else if (kindabad && !reallybad) {
      printf("Dear Wonderlander,\n\nThe decree for hatterspeak finds your "
             "message lacking. Some of the");
      printf(" words that you used are not hatterspeak.\nThe list shows how to "
             "turn the oldspeak words into hatterspeak.\n\n");
      khead = kindabad;
      while (kindabad) {
        printf("%s -> %s\n", kindabad->gs->oldspeak, kindabad->gs->hatterspeak);
        kindabad = kindabad->next;
      }
    } else if (!kindabad && reallybad) {
      printf("Dear Wonderlander,\n\nYou have chosen to use words that the "
             "queen has decreed oldspeak.\n");
      printf("Due to your infraction you will be sent to the dungeon where you "
             "will be taught hatterspeak.\n\n");
      printf("Your errors:\n\n");
      rhead = reallybad;
      while (reallybad) {
        printf("%s\n", reallybad->gs->oldspeak);
        reallybad = reallybad->next;
      }
    }
  }
  reallybad = rhead; //Sets it equal to node head to be free
  kindabad = khead;
  bf_delete(bf);
  ht_delete(ht);
  if (kindabad) {
    ll_delete(kindabad);
  }
  if (reallybad) {
    ll_delete(reallybad);
  }
  regfree(&word_regex);
  clear_words();
  return 0;
}
