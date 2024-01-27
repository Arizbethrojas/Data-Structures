# Makefile for 'hashtable' module
#
# Arizbeth Rojas, Winter 2024

CC = gcc
CFLAGS = -Wall -pedantic -std=c11 -ggdb -I../lib -I../set
OBJS = hashtabletest.o hashtable.o hash.o ../lib/file.o ../lib/mem.o ../set/set.o 

VALGRIND = valgrind --leak-check=full --show-leak-kinds=all

.PHONY: all clean test

hashtabletest:$(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

test: hashtabletest
	./hashtabletest
	
hashtabletest.o: hashtable.h 
hashtable.o: hashtable.h 
mem.o: mem.h
../lib/file.o: ../lib/file.h
hash.o: hash.h

valgrind:  hashtabletest 
	$(VALGRIND) ./hashtabletest 

clean:
	rm -rf *.dSYM  # MacOS debugger info
	rm -f *~ *.o
	rm -f hashtabletest
	rm -f core
