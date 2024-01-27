# Makefile for 'set' module
#
# Arizbeth Rojas, Winter 2024

LIBS =

# uncomment the following to turn on verbose memory logging
#TESTING=-DMEMTEST

CC = gcc
CFLAGS = -Wall -pedantic -std=c11 -ggdb -I../lib
OBJS = settest.o set.o ../lib/file.o ../lib/mem.o 

VALGRIND = valgrind --leak-check=full --show-leak-kinds=all

.PHONY: all clean test

settest:$(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

test: settest
	./settest
	
settest.o: set.h 
set.o: set.h 
mem.o: 
../lib/file.o: ../lib/file.h

valgrind:  settest 
	$(VALGRIND) ./settest 

clean:
	rm -rf *.dSYM  # MacOS debugger info
	rm -f *~ *.o
	rm -f settest
	rm -f core
