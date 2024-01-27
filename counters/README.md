# CS50 Lab 3
## CS50 Winter 2024

### counter

A `counter` set is a set of counters, each distinguished by an integer _key_ . It's a set - each _key_ can only occur once in the set - and it tracks a _counter_ for each _key_. It is initialized to one. Each time `counters_add` is called on a given _key_, the corresponding _counter_ is incremented. The current _counter_ value can be retrieved by asking for the relevant _key_.


### Usage

The *counter* module, defined in `counter.h` and implemented in `counter.c`, implements counters with `int` _keys_ (where _keys_ must be non-negative), and exports the following functions through `counters.h`:

```c
counters_t* counters_new(void);
int counters_add(counters_t* ctrs, const int key);
int counters_get(counters_t* ctrs, const int key);
bool counters_set(counters_t* ctrs, const int key, const int count);
void counters_print(counters_t* ctrs, FILE* fp);
void counters_iterate(counters_t* ctrs, void* arg, void (*itemfunc)(void* arg, const int key, const int count));
void counters_delete(counters_t* ctrs);
```

### Implementation

We implement counters as a linked list.
The *counters* themselves are represented as a `struct counters` containing a pointer to the head of the list; the head pointer is NULL when counters are empty.

Each node in the list is a `struct countersnode`, a type defined internally to the module.
Each countersnode includes a pointer to the `int count` and `int key` a pointer to the next countersnode on the list.

To insert a new node into counters we create a new countersnode to hold the `count`, and insert it at the head of the list.

You can set the value of a counter or you can increment it one by one. Of course, if counters is empty, we return NULL instead.

The `counters_print` method prints a little syntax around the count. 

The `counters_iterate` method calls the `iterate_funct` function on each item by scanning the linked list.

The `counters_delete` method scans the linked list, freeing countersnodes as it proceeds.
It concludes by freeing the `struct counters`.


### Assumptions

The `key` inserted cannot be NULL or negative.


### Files

* `Makefile` - compilation procedure
* `counters.h` - the interface
* `counters.c` - the implementation
* `countersTest.c` - unit test driver
* `test.names` - test data
* `testing.out` - result of `make test &> testing.out`

### Compilation

To compile, simply `make counters.o`.

### Testing

The `counterstest.c` program reads lines from stdin and tests errors and edge cases for the set.c program. The print statements will let you know what specific part of the program is being tested. By the end, you will see that all methods run as intended by the set.h file. 

To test, simply `make test`.

To test with valgrind, `make valgrind`.
