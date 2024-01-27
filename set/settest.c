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
#include <stdlib.h>
#include <string.h>
#include "set.h"
#include "mem.h"

static void pair_print(FILE *fp, const char *key, void *item);
static void pair_delete(void *item);
static void pair_iterate(void *arg, const char *key, void *item);

/* **************************************** */
int main()
{
  /*
   * tests the ability to create sets and successfully insert items and keys
   */
  set_t *valid_set = set_new();
  printf("Creates a set node with a valid key and item pair\n");
  char *item1 = "alabama1";
  bool set_bool_1 = set_insert(valid_set, "key1", item1);
  printf("set_insert should return true since this is a valid pair\n");
  if (set_bool_1 == false)
  {
    fprintf(stderr, "%s : set_insert does not work as intended for this valid set because it returns false\n", set_bool_1 ? "true" : "false");
    return 1;
  }
  if (set_bool_1 == true)
  {
    printf("%s : set_insert succeeded for this valid set\n", set_bool_1 ? "true" : "false");
  }

  /*
   * checks cases in which items should not be inserted
   */

  set_t *invalid_set = set_new();
  printf("Create a set node with a NULL key and NULL item\n");
  bool set_bool_2 = set_insert(invalid_set, NULL, NULL);
  printf("set_insert should return false since this has NULL key and NULL item values\n");
  if (set_bool_2 == false)
  {
    printf("%s : set_insert works as intended because it is false for this invalid set\n", set_bool_2 ? "true" : "false");
  }
  if (set_bool_2 == true)
  {
    fprintf(stderr, "%s : set_insert does not work as intended because it returns true for this invalid set\n", set_bool_2 ? "true" : "false");
    return 1;
  }

  printf("Create a set node with a valid key and NULL item\n");
  bool set_bool_3 = set_insert(invalid_set, "key_for_set3", NULL);
  printf("According to its description in the set.h file, set_insert should return false since this has valid key and NULL item values\n");
  if (set_bool_3 == false)
  {
    printf("%s : set_insert works as intended because it is false\n", set_bool_3 ? "true" : "false");
  }
  if (set_bool_3 == true)
  {
    fprintf(stderr, "%s : set_insert does not work as intended because it returns true when it should not\n", set_bool_3 ? "true" : "false");
    return 1;
  }

  printf("Create a set node with a NULL key and a valid item\n");
  char *valid_item = "alaska2";
  bool set_bool_4 = set_insert(invalid_set, NULL, valid_item);
  printf("According to its description in the set.h file, set_insert should return false since this has NULL key and valid item values\n");
  if (set_bool_4 == false)
  {
    printf("%s : set_insert works as intended because it is false\n", set_bool_4 ? "true" : "false");
  }
  if (set_bool_4 == true)
  {
    fprintf(stderr, "%s : set_insert does not work as intended because it returns true for this inavlid node\n", set_bool_4 ? "true" : "false");
    return 1;
  }
  /*
   * tests set_find method
   */
  printf("testing to see if set_find returns the item given a valid key");
  void *item_find_1 = set_find(valid_set, "key1");
  if (item_find_1 == NULL)
  {
    fprintf(stderr, "set_find does not work as intended because it returns NULL when it should not\n");
    return 1;
  }
  if (item_find_1 == item1)
  {
    printf("set_find returns the correct item!");
  }
  if (item_find_1 != item1)
  {
    fprintf(stderr, "set_find does not work because it returns the wrong item");
    return 1;
  }
  printf("testing to ensure that set_find returns NULL if given an incorrect key");
  void *item_find_wrong = set_find(valid_set, "fakekey1");
  if (item_find_wrong == NULL)
  {
    printf("set_find works as intended because this key does not exist\n");
  }
  if (item_find_wrong == item1)
  {
    fprintf(stderr, "set_find does not work because it returns the item given a bad key");
    return 1;
  }

  // creating new valid nodes
  char *item2 = "alaska2";
  set_insert(valid_set, "key2", item2);
  char *item3 = "arizona3";
  set_insert(valid_set, "key3", item3);
  char *item4 = "arkansas4";
  set_insert(valid_set, "key4", item4);
  char *item5 = "california5";
  set_insert(valid_set, "key5", item5);

  printf("This is our set: \n");
  set_print(valid_set, stdout, pair_print);
  printf("\n");

  /*
   *  tests set_iterate
   */

  int countc = 0;
  set_iterate(valid_set, &countc, pair_iterate);
  printf("successfully iterates: %d \n", countc); 

/*
* successfully deletes set with NO memory leaks!
*/
  set_delete(valid_set, pair_delete);
  set_delete(invalid_set, pair_delete);

  printf("Then we delete our set: \n");
}

// print a key and item pair seperated by a colon
void pair_print(FILE *fp, const char *key, void *item)
{

  if (item == NULL || key == NULL)
  {
    fprintf(fp, "(null)");
  }
  else
  {
    fprintf(fp, "%s:%s", key, (char *)item);
  }
}

// passed into set_iterate as a parameter
void pair_iterate(void *arg, const char *key, void *item)
{
  int *items_number = arg;
  if (items_number != NULL && item != NULL)
  {
    (*items_number)++;
  }
}

// sets item = null
void pair_delete(void *item)
{
  if (item != NULL)
  {
    item = NULL;
  }
}
