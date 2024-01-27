# CS50 Lab 3
## CS50 winter 2024

### set

A `set` maintains an unordered collection of (_key_, _item_) pairs; any given _key_ can only occur in the set once. The set starts out empty and grows as the caller inserts new (_key_,_item_) pairs. The caller can retrieve _items_ by asking for their _key_, but cannot remove or update pairs. Items are distinguished by their _key_.

### Usage

The *set* module, defined in `set.h` and implemented in `set.c`, implements a set of `void*` items with `char*` keys, and exports exactly the following functions through `set.h` :

```c
set_t* set_new(void);
bool set_insert(set_t* set, const char* key, void* item);
void* set_find(set_t* set, const char* key);
void set_print(set_t* set, FILE* fp, void (*itemprint)(FILE* fp, const char* key, void* item) );
void set_iterate(set_t* set, void* arg, void (*itemfunc)(void* arg, const char* key, void* item) );
void set_delete(set_t* set, void (*itemdelete)(void* item) );
```

### Implementation

We implement this set as a linked list.
The *set* itself is represented as a `struct set` containing a pointer to the head of the list; the head pointer is NULL when the set is empty.

Each node in the list is a `struct setnode`, a type defined internally to the module.
Each setnode includes a pointer to the `void* item` , a pointer to the `char* key` , and a pointer to the next setnode on the list.

To insert a new item in the set we create a new setnode to hold the `item`, and insert it at the head of the list. However, its `key` must be unique in order to correctly be inserted. 

To view an item from the set we search the linked list for the associated key and return its item.
Of course, if the set is null, the key is null, or an item for the priovided key is not found, we return NULL.

The `set_print` method prints a little syntax around the list, and between items, but mostly calls the `pair_print` function on each item by scanning the linked list.

The `set_iterate` method calls the `pair_iterate` function on each item by scanning the linked list.

The `set_delete` method calls the `pair_delete` function on each item by scanning the linked list, freeing setnodes as it proceeds.
It concludes by freeing the `struct set`.

### Files

* `Makefile` - compilation procedure
* `set.h` - the interface
* `set.c` - the implementation
* `setTest.c` - unit test driver

### Compilation

To compile, simply `make set.o`.

### Testing

The `settest.c` program reads lines from stdin and tests errors and edge cases for the set.c program. The print statements will let you know what specific part of the program is being tested. By the end, you will see that all methods run as intended by the set.h file. 

To test, simply `make test`.

To test with valgrind, `make valgrind`.
