/*
 * hashtabletest.c - test program for CS50 hashtable module
 *
 * usage: read names from stdin, each on one line
 *
 * This program is a "unit test" for the hashtable module.
 *
 * CS50, Winter 2024
 */

#include <stdio.h>
#include <stdbool.h>
#include "hashtable.h"
#include "mem.h"

static void table_print(FILE *fp, const char *key, void *item);
static void table_delete(void *item);
static void table_iterate(void *arg, const char *key, void *item);

/* **************************************** */
int main()
{
    /*
     * tests the ability to create hashtables and successfully insert set elements
     */

    hashtable_t *hash1 = hashtable_new(6);
    printf("Creates a hashtable with 6 indexs in its array\n");
    printf("let's use the print function to make sure each index is correctly initialized to null");
    hashtable_print(hash1, stdout, table_print);
    printf("now, let's start adding values");
    bool hash_bool_1 = hashtable_insert(hash1, "key1", (void *)16);
    printf("hashtable_insert should return true since this is a valid pair\n");
    if (hash_bool_1 == false)
    {
        fprintf(stderr, "%s : hashtable_insert does not work as intended because it returns false\n", hash_bool_1 ? "true" : "false");
        return 1;
    }
    if (hash_bool_1 == true)
    {
        printf("%s : hashtable_insert succeeded\n", hash_bool_1 ? "true" : "false");
    }
    bool hash_bool_2 = hashtable_insert(hash1, NULL, NULL);
    // these are bad inserts

    printf("Create a hashtable element with a NULL key and NULL item\n");
    printf("hashtable_insert should return false since this has NULL key and NULL item values\n");
    if (hash_bool_2 == false)
    {
        printf("%s : hashtable_insert works as intended because it is false\n", hash_bool_2 ? "true" : "false");
    }
    if (hash_bool_2 == true)
    {
        fprintf(stderr, "%s : hashtable_insert does not work as intended because it returns true when it should not\n", hash_bool_2 ? "true" : "false");
        return 1;
    }
    //tests hashtable find
    printf("testing to see if hashtable_find can return the item given a valid key");
    void *item = hashtable_find(hash1, "key1");
    if (item == NULL)
    {
        fprintf(stderr, "hashtable_find does not work as intended because it returns NULL when it should not\n");
        return 1;
    }
    else
    {
        printf("hashtable_find returns the correct item!");
    }

    printf("testing to ensure that hashtable_find returns NULL if given an incorrect key");
    void *item1 = hashtable_find(hash1, "fakekey1");
    if (item1 == NULL)
    {
        printf("hashtable_find works as intended\n");
    }
    else
    {
        fprintf(stderr, "hashtable_find does not work because it returns the item given a bad key");
        return 1;
    }
    //correctly prints
    printf("This is our hashtable: \n");
    hashtable_print(hash1, stdout, table_print);
    printf("\n");
    //tests hashtable_iterate
    hashtable_iterate(hash1, stdout, table_iterate);
    printf("This is our hashtable after hashtable_iterate: \n");
    hashtable_print(hash1, stdout, table_print);
    printf("\n");
    //no memory leaks!
    hashtable_delete(hash1, table_delete);
    printf("This is our hashtable after hashtable_delete: \n");
    hashtable_print(hash1, stdout, table_print);
    printf("\n");
}

// print a key and item pair seperated by a comma
void table_print(FILE *fp, const char *key, void *item)
{

    if (item == NULL || key == NULL)
    {
        fprintf(fp, "(null)");
    }
    else
    {
        fprintf(fp, "%p , %p", key, (char *)item);
    }
}
//passed into hashtable+iterator method
void table_iterate(void *arg, const char *key, void *item)
{
    if (key == NULL || item == NULL)
    {
        fprintf(arg, "(null)");
    }
    else
    {
        printf("numbers are cool!");
    }
}
//frees items
void table_delete(void *item)
{
    if (item != NULL)
    {
        free(item);
    }
}
