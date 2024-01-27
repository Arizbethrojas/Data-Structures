# Makefile for 'counters' module
#
# Arizbeth Rojas, Winter 2024

CC = gcc
CFLAGS = -Wall -pedantic -std=c11 -ggdb -I../lib
OBJS = counterstest.o counters.o ../lib/file.o ../lib/mem.o 

VALGRIND = valgrind --leak-check=full --show-leak-kinds=all

.PHONY: all clean test

counterstest:$(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

test: counterstest
	./counterstest
	
counterstest.o: counters.h 
counters.o: counters.h 
mem.o: mem.h
../lib/file.o: ../lib/file.h

valgrind:  counterstest 
	$(VALGRIND) ./counterstest 

clean:
	rm -rf *.dSYM  # MacOS debugger info
	rm -f *~ *.o
	rm -f counterstest
	rm -f core
