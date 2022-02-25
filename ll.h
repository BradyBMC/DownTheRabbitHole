//ll.h - Contains the definitions used by the LinkedList ADT

#ifndef __LL_H__ // Check if token has been defined already
#define __LL_H__

#ifndef NIL
#define NIL (void *)0
#endif

#include "hs.h"
#include <stdbool.h>

extern bool move_to_front;

typedef struct ListNode ListNode;

// Definition of a List Node, a dynamically allocated Linked List
//
// gs: Hatterspeak struct to store 2 diff string
// next: a linked list node it points to
//
struct ListNode {
  HatterSpeak *gs;
  ListNode *next;
};

// Creates and returns a linked list node
//
// gs: hatterspeak struct of words
//
ListNode *ll_node_create(HatterSpeak *gs);

//
// Frees a linked list node
//
// n: List node to be freed
//
void ll_node_delete(ListNode *n);

// Goes through linked list and deletes all nodes
//
// head: beginning of linked list
//
void ll_delete(ListNode *head);

// Inserts a new linked list node if it doesnt already exist
//
// head: begginning of linked list
// gs: hatterspeak for new linked list node to be created
//
ListNode *ll_insert(ListNode **head, HatterSpeak *gs);

// Looks up linked list to see if it already exists
//
// head: beginning of linked list being serached
// key: string be compared to in linked list
ListNode *ll_lookup(ListNode **head, char *key);

#endif
