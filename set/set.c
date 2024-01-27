/*
 * set.c - CS50 'set' module
 *
 * see set.h for more information.
 *
 * Arizbeth Rojas, Winter 2024
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "set.h"
#include "mem.h"

/**************** file-local global variables ****************/
/* none */

/**************** local types ****************/
typedef struct setnode
{
  char *key;            // pointer to key for this node
  void *item;           // pointer to data for this node
  struct setnode *next; // link to next node
} setnode_t;

/**************** global types ****************/
typedef struct set
{
  struct setnode *head; // head of the list of nodes in set
} set_t;

/**************** global functions ****************/
/* that is, visible outside this file */
/* see set.h for comments about exported functions */
set_t *set_new(void);
bool set_insert(set_t *set, const char *key, void *item);
void *set_find(set_t *set, const char *key);
void set_print(set_t *set, FILE *fp, void (*itemprint)(FILE *fp, const char *key, void *item));
void set_iterate(set_t* set, void* arg, void (*itemfunc)(void* arg, const char* key, void* item) );
void set_delete(set_t* set, void (*itemdelete)(void* item) );

/**************** local functions ****************/
/* not visible outside this file */
static setnode_t *setnode_new(const char *key, void *item);

/**************** set_new() ****************/
/* see set.h for description */
set_t *
set_new(void)
{
  set_t *set = mem_malloc(sizeof(set_t)); // allocate memory for the set structure
  if (set == NULL)
  {
    return NULL; // error allocating set
  }
  else
  {
    // initialize contents of set structure
    set->head = NULL; // initially NULL
    return set;
  }
}

/**************** set_insert() ****************/
/* see set.h for description */
bool set_insert(set_t *set, const char *key, void *item)
{
  if (set == NULL || key == NULL || item == NULL)
  {
    return false; // defensive programming
  }
  if (set_find(set, key) == NULL) // verifies that this key does not already exists
  {
    setnode_t *new = setnode_new(key, item); // allocate a new node to be added to the list
    new->next = set->head;                   // links the node to the rest of the list by setting the newly created node's next pointer to the current head of the list
    set->head = new;                         // makes the new node the head of the list
    return true; // successfully inserted
  }
  if (set_find(set, key) != NULL) // this key already exists
  {
    return false; // failed to insert
  }
#ifdef MEMTEST
  mem_report(stdout, "After set_insert");
#endif
  return false;
}

/**************** setnode_new ****************/
/* Allocate and initialize a setnode */
static setnode_t * // not visible outside this file
setnode_new(const char *key, void *item)
{
  if (key == NULL)
  { // defensive programming
    return NULL;
  }
  setnode_t *node = mem_malloc(sizeof(setnode_t));
  if (node == NULL)
  {
    // error allocating memory for node
    return NULL;
  }
  else
  {
    node->key = mem_malloc(strlen(key) + 1); //we add one to the length to account for the null character
    if (node->key == NULL)
    {
      mem_free(node); // in case there was an error allocating memory
      return NULL;
    }
    else
    {
      strcpy(node->key, key); // otherwise, create this node
      node->item = item;
      node->next = NULL;
      return node;
    }
  }
}

/**************** set_find() ****************/
/* see set.h for description */
void *
set_find(set_t *set, const char *key)
{
  if (set == NULL || key == NULL)
  {
    return NULL; // defensive programming
  }
  //loops through all nodes
  for (setnode_t *node = set->head; node != NULL; node = node->next)
  {
    char *curr_key = node->key;
    if (strcmp(curr_key, key) == 0) //keys match!
    {
      void *curr_item = node->item;
      return curr_item; // successfully returns item
    }
  }
  return NULL; // key was never found
}

/**************** set_print() ****************/
/* see set.h for description */
void set_print(set_t *set, FILE *fp, void (*itemprint)(FILE *fp, const char *key, void *item))
{
  if (fp != NULL) // defensive programming
  {
    if (set != NULL) // defensive programming
    {
      fputc('{', fp);
      // loops through all nodes
      for (setnode_t *node = set->head; node != NULL; node = node->next)
      {
        // look at this node
        if (itemprint != NULL)
        { // print the node's item
          (*itemprint)(fp, node->key, node->item);
          fputc(',', fp);
        }
      }
      fputc('}', fp);
    }
    else
    {
      fputs("(null)", fp); // set was null
    }
  }
}

/**************** set_iterate() ****************/
/* see set.h for description */
void set_iterate(set_t *set, void *arg, void (*itemfunc)(void *arg, const char *key, void *item))
{
  if (set != NULL && itemfunc != NULL)
  {
    // call itemfunc with arg, on each item
    for (setnode_t *node = set->head; node != NULL; node = node->next)
    {
      (*itemfunc)(arg, node->key, node->item);
    }
  }
}

/**************** set_delete() ****************/
/* see set.h for description */
void set_delete(set_t *set, void (*itemdelete)(void *item))
{
  if (set != NULL)
  {
    // loops through all nodes
    for (setnode_t *node = set->head; node != NULL;)
    {
      if (itemdelete != NULL)
      {                            // if node is not null
        (*itemdelete)(node->item); // delete node's item
      }
      setnode_t *next = node->next; // remember what comes next
      if (node->key != NULL)
      {
        mem_free(node->key); //release key memory 
      }
      mem_free(node); // free the node
      node = next;    // and move on to next
    }

    mem_free(set);
  }

#ifdef MEMTEST
  mem_report(stdout, "End of set_delete");
#endif
}
