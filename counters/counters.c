/*
 * counter.c - CS50 'counter' module
 *
 * see counter.h for more information.
 *
 * Arizbeth Rojas, Winter 2024
 */

#include <stdio.h>
#include <stdbool.h>
#include "counters.h"
#include "mem.h"
/**************** file-local global variables ****************/
/* none */

/**************** local types ****************/
typedef struct countersnode
{
  int key;                   // key needed to modify the count
  int count;                 // count in this node
  struct countersnode *next; // link to next node
} countersnode_t;

/**************** global types ****************/
typedef struct counters
{
  struct countersnode *head; // head of the list of counters
} counters_t;

/**************** global functions ****************/
/* that is, visible outside this file */
/* see counters.h for comments about exported functions */
//
counters_t* counters_new(void);

/**************** local functions ****************/
/* not visible outside this file */
static countersnode_t *countersnode_new(int key, int count);
int counters_add(counters_t* ctrs, const int key);
int counters_get(counters_t* ctrs, const int key);
bool counters_set(counters_t* ctrs, const int key, const int count);
void counters_print(counters_t* ctrs, FILE* fp);
void counters_iterate(counters_t* ctrs, void* arg, void (*itemfunc)(void* arg, const int key, const int count));
void counters_delete(counters_t* ctrs);

/**************** counters_new ****************/
/* see counters.h for description */
counters_t *
counters_new(void)
{
  counters_t *ctrs = mem_malloc(sizeof(counters_t));
  if (ctrs == NULL)
  {
    return NULL; // error allocating counter
  }
  else
  {
    // initialize contents of counter structure
    ctrs->head = NULL; // initially empty
    return ctrs;
  }
}
/**************** countersnode_new ****************/
/* Allocate and initialize a countersnode */
static countersnode_t * // not visible outside this file
countersnode_new(int key, int count)
{
  if (key < 0) // defensive programming
  {
    return NULL;
  }
  countersnode_t *node = mem_malloc(sizeof(countersnode_t));
  if (node == NULL)
  {
    return NULL; // error allocating memory
  }

  node->key = key;
  node->count = count;
  node->next = NULL; 
  return node;
}

/**************** counters_add() ****************/
/* see counters.h for description */
int counters_add(counters_t *ctrs, const int key)
{
  if (ctrs == NULL || key < 0)
  {
    return 0; // error allocating counters
  }
  if (ctrs != NULL && key > 0) //defensive programming
  {
    for (countersnode_t *node = ctrs->head; node != NULL; node = node->next)
    {
      if (node->key == key) //check if key matches 
      {
        node->count = node->count + 1; // increments by one
        return node->count; // updates count 
      }
    }
    countersnode_t *new_counter = countersnode_new(key, 1);
    if (new_counter != NULL)
    {
      new_counter->next = ctrs->head; 
      ctrs->head = new_counter;
      return new_counter->count;
    }
  }
  return 0;
}
/**************** counters_get() ****************/
/* see counters.h for description */
int counters_get(counters_t *ctrs, const int key)
{
  if (ctrs == NULL || key < 0)
  {
    return 0; // null counter or negative key
  }
  //loops through nodes
  for (countersnode_t *node = ctrs->head; node != NULL; node = node->next)
  {
    int curr_key = node->key;
    if (curr_key == key)
    {
      int curr_count = node->count; //assigns values
      return curr_count;
    }
  }
  return 0; // key was never found
}
/**************** counters_set() ****************/
/* see counters.h for description */
bool counters_set(counters_t *ctrs, const int key, const int count)
{
  if (ctrs == NULL || key < 0 || count < 0) //defensive programming
  {
    return false; // error allocating bag
  }
  if (counters_get(ctrs, key) == 0)
  {
    countersnode_t *new = countersnode_new(key, count);
    if (new != NULL)
    {
      new->count = count; // this counter does not exist already, so we will initialize it to count
      new->next = ctrs->head;
      ctrs->head = new;
      return true;
    }
    else
    {
      return false; // if you can't allocate any more memory, return false
    }
  }
  if (counters_get(ctrs, key) != 0)
  { // this counter already exists, update its value
    countersnode_t *existing = countersnode_new(key, count);
    if (existing != NULL)
    { 
      //loop through all nodes to find the corresponding node
      for (countersnode_t *node = ctrs->head; node != NULL; node = node->next)
      {
        if (node->key == key)
        {
          node->count = count;
          mem_free(existing); //releases memory
          return true;
        }
      }
    }
  }
  return false; // this key does not exist in the linked list
}

/**************** counters_print() ****************/
/* see counters.h for description */
void counters_print(counters_t *ctrs, FILE *fp)
{
  if (fp != NULL)
  {
    if (ctrs != NULL)
    { 
      fputc('{', fp);
      for (countersnode_t *node = ctrs->head; node != NULL; node = node->next)
      {
        {
          fprintf(fp, "%d", node->count); //returns count
          fputc(',', fp);
        }
      }
    }
    fputc('}', fp);
  }
  else
  {
    fputs("(null)", fp); //linked list was null
  }
}
/**************** counters_iterate() ****************/
/* see counters.h for description */
void counters_iterate(counters_t *ctrs, void *arg, void (*itemfunc)(void *arg, const int key, const int count))
{
  if (ctrs != NULL && itemfunc != NULL)
  {
    // call itemfunc with arg, on each item
    for (countersnode_t *node = ctrs->head; node != NULL; node = node->next)
    {
      (*itemfunc)(arg, node->key, node->count);
    }
  }
}

/**************** counters_delete() ****************/
/* see counters.h for description */
void counters_delete(counters_t *ctrs)
{
  if (ctrs != NULL)
  {
    for (countersnode_t *node = ctrs->head; node != NULL;)
    {
      countersnode_t *next = node->next; // remember what comes next
      mem_free(node);                    // free the node
      node = next;                       // and move on to next
    }

    mem_free(ctrs); //release the counters struct
  }

#ifdef MEMTEST
  mem_report(stdout, "End of counters_delete");
#endif
}
