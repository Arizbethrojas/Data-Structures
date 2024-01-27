/*
 * settest.c - test program for CS50 set module
 *
 * usage: read names from stdin, each on one line
 *
 * This program is a "unit test" for the set module.
 *
 * CS50, Winter 2024
 */

#include <stdio.h>
#include <stdbool.h>
#include "counters.h"
#include "mem.h"

static void iterate_funct(void *arg, const int key, const int count);

/* **************************************** */
int main()
{ /*
   * tests the ability to create counters and successfully add nodes
   */
    counters_t *c1 = counters_new();
    printf("Creates a counter node with a valid key\n");
    int c1_new = counters_add(c1, 4);
    printf("counters_add should return 1 since this is counter is new\n");
    if (c1_new == 1)
    {
        printf("counters_add works as intended for c1 because it returns 1\n");
    }
    if (c1_new != 1)
    {
        fprintf(stderr, "counters_add does not work as intended for c1 because it does not return 1");
        return 1;
    }

    /*
     * checks cases in which counters should not be added
     */

    printf("Creates a counter node with an already existing key\n");
    int c1_add = counters_add(c1, 4);
    printf("counters_add should return 2 since this is counter already exists\n");
    if (c1_add == 2)
    {
        printf("counters_add works as intended for c2 because it returns 2\n");
    }
    if (c1_add != 2)
    {
        fprintf(stderr, "counters_add does not work as intended for c2 because it does not return 2");
        return 1;
    }

    printf("Creates a negative key for a counter\n");
    printf("counters_add should return 0 since for this case\n");
    int c1_neg = counters_add(c1, -10);
    if (c1_neg == 0)
    {
        printf("counters_add works as intended because it returns 0\n");
    }
    if (c1_neg != 0)
    {
        fprintf(stderr, "counters_add does not work as intended because it does not return 0");
        return 1;
    }

    /*
    * tests counters_get method
    */

    printf("we will test counters_get, which should return 0 when given a negative key");
    int c1_get = counters_get(c1, -10);
    if (c1_get == 0)
    {
        printf("counters_get works as intended for c3 because it returns 0\n");
    }
    if (c1_get != 0)
    {
        fprintf(stderr, "counters_get does not work as intended for c3 because it does not return 0");
        return 1;
    }

    /*
    * tests counters_set method
    */

    printf("set the value of the first counter to 10\n");
    bool counters_bool = counters_set(c1, 4, 10);
    printf("According to its description in the counters.h file, counters_set should return true since this has value has been sent to 10\n");
    if (counters_bool == true)
    {
        printf("%s : counters_set works as intended because it is false\n", counters_bool ? "true" : "false");
    }
    if (counters_bool == false)
    {
        fprintf(stderr, "%s : counters_set does not work as intended because it returns false when it should not\n", counters_bool ? "true" : "false");
        return 1;
    }

    printf("Attempt to set the count value of a node to a negative number\n");
    bool counters_bool_negative = counters_set(c1, 4, -10);
    printf("According to its description in the counters.h file, counters_set should return false since this has value has been sent to -10\n");
    if (counters_bool_negative == false)
    {
        printf("%s : counters_set works as intended because it is false and cannot set count to a negative value\n", counters_bool_negative ? "true" : "false");
    }
    if (counters_bool_negative == true)
    {
        fprintf(stderr, "%s : counters_set does not work as intended because it returns false when it should not\n", counters_bool_negative ? "true" : "false");
        return 1;
    }
    //creating valid counters
    printf("lets create a few valid counters");
    counters_t *c_valid = counters_new();
    counters_add(c_valid, 1);
    counters_add(c_valid, 2);
    counters_add(c_valid, 3);
    counters_add(c_valid, 4);
    counters_add(c_valid, 5);
    counters_set(c_valid, 2, 20);
    counters_set(c_valid, 3, 300);

    printf("These are our counters: \n");
    counters_print(c_valid, stdout);
    printf("\n");

    int counterc = 0;
    counters_iterate(c_valid, &counterc, iterate_funct);
    printf("counters_iterate: %d\n", counterc); 

    //deletes counters
    counters_delete(c_valid);
    counters_delete(c1);
    printf("Then we delete our counters \n");
}

// passed into set_iterate as a parameter
void iterate_funct(void *arg, const int key, const int count)
{
    if (key < 0 || count < 0)
    {
        fprintf(arg, "(negative)");
    }
    else
    {
        int *items_number = arg;
        (*items_number)++;
    }
}
