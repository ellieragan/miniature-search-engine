#Makefile for indexer
#Ellie Boyd
#CS 50

L = ../libcs50
C = ../common
CC = gcc
CFLAGS = -Wall -pedantic -std=c11 -ggdb -I$L -I$C

OBJS = indexer.o
LIBS = $C/common.a $L/libcs50.a

.PHONY: all clean

all: indexer indextest

indexer: $(OBJS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

indextest: indextest.o
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@
	
test:
	bash -v testing.sh >& testing.out

valgrind: indexer
	valgrind -v --leak-check=full --show-leak-kinds=all ./indexer ../data/letters indexFile

clean:
	rm -f indexer
	rm -f indextest
	rm -f *~ *.o
	rm -rf *.dSYM
	rm -f core
