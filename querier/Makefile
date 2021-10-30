#Makefile for querier
#Ellie Boyd
#CS 50

L = ../libcs50
C = ../common
CC = gcc
CFLAGS = -Wall -pedantic -std=c11 -ggdb -I$L -I$C

OBJS = querier.o   
LIBS = $C/common.a $L/libcs50.a

.PHONY: all clean

all: querier

querier: $(OBJS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@
	
test:
	bash -v testing.sh >& testing.out

valgrind: querier
	valgrind -v --leak-check=full --show-leak-kinds=all ./querier ../../shared/tse/output/crawler/pages-letters-depth-1 ../../shared/tse/output/indexer/index-letters-1

clean:
	rm -f querier
	rm -f *~ *.o
	rm -rf *.dSYM
	rm -f core
	rm -rf vgcore.*
