/*
 * hashtable.c - CS50 'hashtable' module
 *
 * see hashtable.h for more information.
 *
 * Arizbeth Rojas, Winter 2024
 */
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "hash.h"
#include "hashtable.h"
#include "set.h"
#include "mem.h"
/**************** file-local global variables ****************/
/* none */

/**************** local types ****************/
typedef struct hashtable
{
    int num_slots;
    set_t **array; // array of pointers to pointers to set
} hashtable_t;

/**************** global functions ****************/
/* that is, visible outside this file */
/* see hashtable.h for comments about exported functions */
hashtable_t* hashtable_new(const int num_slots);
bool hashtable_insert(hashtable_t* ht, const char* key, void* item);
void* hashtable_find(hashtable_t* ht, const char* key);
void hashtable_print(hashtable_t* ht, FILE* fp, void (*itemprint)(FILE* fp, const char* key, void* item));
void hashtable_iterate(hashtable_t* ht, void* arg, void (*itemfunc)(void* arg, const char* key, void* item) );
void hashtable_delete(hashtable_t* ht, void (*itemdelete)(void* item) );

/**************** hashtable_new() ****************/
/* see hashtable.h for description */
hashtable_t *
hashtable_new(const int num_slots)
{
    if (num_slots < 0)
    {
        return NULL; // cannot have negative slots
    }
    hashtable_t *hashtable = mem_malloc(sizeof(hashtable_t));
    if (hashtable == NULL)
    {
        return NULL; // error allocating memory
    }
    else
    {
        hashtable->num_slots = num_slots;
        hashtable->array = mem_malloc(num_slots * sizeof(set_t *));
        if (hashtable->array == NULL)
        {
            mem_free(hashtable);
            return NULL; // error allocating memory
        }
    }
    //loop through all indexes
    for (int i = 0; i < num_slots; i++)
    {
        set_t *new_set = set_new(); // all elements are initialized to null
        hashtable->array[i] = new_set;
    }
    return hashtable;
}
/**************** hashtable_insert() ****************/
/* see hashtable.h for description */
bool hashtable_insert(hashtable_t *ht, const char *key, void *item)
{
    if (ht == NULL || key == NULL || item == NULL)
    {
        return false; // defensive programming
    }
    if (hashtable_find(ht, key) == NULL) // key does not already exist in hashtable
    {
        long index = hash_jenkins(key, ht->num_slots); // use hash function to determine index
        set_insert(ht->array[index], key, item);
        return true;
    }
    else // key already exists
    {
        return false;
    }
}
/**************** hashtable_find() ****************/
/* see hashtable.h for description */
void *
hashtable_find(hashtable_t *ht, const char *key)
{
    if (ht == NULL || key == NULL)
    {
        return NULL; // defensive programming
    }
    long index = hash_jenkins(key, ht->num_slots); // use hash function to determine index
    set_t *curr_set = ht->array[index];
    return set_find(curr_set, key); // returns item at index or returns null if theres is no key associated with that item 
}
/**************** hashtable_print() ****************/
/* see hashtable.h for description */
void hashtable_print(hashtable_t *ht, FILE *fp, void (*itemprint)(FILE *fp, const char *key, void *item))
{
    if (fp != NULL)
    {
        if (ht != NULL)
        {// loops through all elements
            for (int i = 0; i < ht->num_slots; i++)
            {
                if (itemprint != NULL)
                {
                    set_t *curr_set = ht->array[i]; //gets set pointer
                    set_print(curr_set, fp, itemprint);
                }
                else{
                    printf("\n");
                }
            }
        }
        else
        {
            fputs("(null)", fp); // hashtable was null
        }
    }
}

/**************** hashtable_iterate() ****************/
/* see hashtable.h for description */
void hashtable_iterate(hashtable_t *ht, void *arg, void (*itemfunc)(void *arg, const char *key, void *item))
{
    if (ht != NULL && itemfunc != NULL)
    {
        // call itemfunc with arg, on each item
        for (int i = 0; i < ht->num_slots; i++)
        {
            set_t *curr_set = ht->array[i];
            set_iterate(curr_set, arg, itemfunc);
        }
    }
}
/**************** hashtable_delete) ****************/
/* see hashtable.h for description */
void hashtable_delete(hashtable_t *ht, void (*itemdelete)(void *item)) // thsi is the whole description
{
    if (ht != NULL)
    {
        for (int i = 0; i < ht->num_slots; i++)
        {
            if (itemdelete != NULL)
            { // if possible...
                set_t *curr_set = ht->array[i];
                set_delete(curr_set, itemdelete);  //calls set_delete
            }
        }
        mem_free(ht); //releases memory
    }

#ifdef MEMTEST
    mem_report(stdout, "End of set_delete");
#endif
}
