# CS50 Lab 3
## CS50 Winter 2024

### hashtable

A `hashtable` is an array of pointers to pointers to _set_.
The `hastable` starts with num_slot elements and all elements are null, sets within these slots can grow as the caller stores an _item_ and _key_ pair at a time given that each _key_ is unique.

### Usage

The *hashtable* module, defined in `hashtable.h` and implemented in `hashtable.c`, implements an array of pointers to pointers in set, which consist of `void*`` with `char*` keys, and export exactly the following functions through `hashtable.h` :

```c
chashtable_t* hashtable_new(const int num_slots);
bool hashtable_insert(hashtable_t* ht, const char* key, void* item);
void* hashtable_find(hashtable_t* ht, const char* key);
void hashtable_print(hashtable_t* ht, FILE* fp, void (*itemprint)(FILE* fp, const char* key, void* item));
void hashtable_iterate(hashtable_t* ht, void* arg, void (*itemfunc)(void* arg, const char* key, void* item) );
void hashtable_delete(hashtable_t* ht, void (*itemdelete)(void* item) );
```

### Implementation


We implement this hashtable as an array. Each _set_ pointer within the elements is initialized to NULL. 

To insert a new set pointer into the array, we hash the provided key using Jenkins Hash to find the correct index. and insert it at the head of the list. However, the set code gurantees that each `key` must be unique in order to correctly be inserted to a set, which subsequently is added to an element in the hashtable array. 

To view an item from the set we implement set_find method because the array holds set pointers. 

The `hashtable_print` method prints a little syntax around the array elements, and, but mostly calls the `table_print` function on each set pointers by scanning the linked list.

The `hashtable_iterate` method calls the `table_iterate` function on each element in the array.

The `hashtable_delete` method calls the `table_delete` function on each item by scanning the array, freeing set pointers  as it proceeds.
It concludes by freeing the `struct hashtable`.

### Files

* `Makefile` - compilation procedure
* `hashtable.h` - the interface
* `hashtable.c` - the implementation
* `hashtableTest.c` - unit test driver
* `test.names` - test data
* `testing.out` - result of `make test &> testing.out`

### Compilation

To compile, simply `make hashtable.o`.

### Testing

The `hashtabletest.c` program reads lines from stdin and tests errors and edge cases for the hashtable.c program. The print statements will let you know what specific part of the program is being tested. By the end, you will see that all methods run as intended by the hashtable.h file. 

To test, simply `make test`.

To test with valgrind, `make valgrind`.