#Makefile for crawler
#Ellie Boyd
#CS 50

L = ../libcs50
C = ../common
CC = gcc
CFLAGS = -Wall -pedantic -std=c11 -ggdb -I$L -I$C

OBJS = crawler.o 
LIBS = $L/libcs50.a $C/common.a

.PHONY: all clean

all: crawler

crawler: $(OBJS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

test:
	bash -v testing.sh >& testing.out

valgrind: crawler
	valgrind --leak-check=full --show-leak-kinds=all ./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/index.html ../data/letters 3
clean:
	rm -f crawler
	rm -f *~ *.o
	rm -rf *.dSYM
	rm -f core
