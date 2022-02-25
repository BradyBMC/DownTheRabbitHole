#include "ll.h"
#include "hs.h"
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool move_to_front = false;
uint32_t seeks = 0;
uint32_t trav = 0;

//Creates list node object and sets hatterspeak pointer
//
ListNode *ll_node_create(HatterSpeak *gs) {
  ListNode *node = (ListNode *)malloc(sizeof(ListNode));
  if (!node) {
    return 0;
  }
  node->gs = gs;
  node->next = NULL;
  return node;
}

//Frees memory for hatterspeak and node
//
void ll_node_delete(ListNode *n) {
  hs_delete(n->gs); //Calls hs_delete bc of object oriented design
  free(n);
  return;
}

//Uses recursion to run though list and delete each node
//
void ll_delete(ListNode *head) {
  if (head->next == NULL) { //Break case
    ll_node_delete(head);
    return;
  } else {
    ll_delete(head->next);
    ll_node_delete(head);
  }
  return;
}

//Inserts new linkeds list object
//
ListNode *ll_insert(ListNode **head, HatterSpeak *gs) {
  if (ll_lookup(
          head, gs->oldspeak)) { //If already exists return head and free hatter
    hs_delete(gs);
    return *head;
  } else {
    ListNode *node = ll_node_create(gs);
    if (!node) {
      return *head;
    }
    node->next = *head; //Adds new node to head
    *head = node;
    return node;
  }
}

//Searches linked list for given word
//
ListNode *ll_lookup(ListNode **head, char *key) {
  seeks++; //Increment for stats
  ListNode *node = *head;
  ListNode *prev = NULL;
  while (node) {
    trav++;
    int value
        = strcmp(node->gs->oldspeak, key); //Compares strings to find match
    if (value == 0) {
      if (move_to_front && prev != NULL) { //Makes sure that prev exists
        prev->next = node->next;
        node->next = *head;
        *head = node;
      }
      return node;
    }
    prev = node;
    node = node->next;
  }
  return NULL;
}
