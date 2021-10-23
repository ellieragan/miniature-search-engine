#Makefile for common.a
#Ellie Boyd
#CS 50

L = ../libcs50
CC = gcc
CFLAGS = -Wall -pedantic -std=c11 -ggdb $(FLAGS) -I$L
OBJS = pagedir.o index.o word.o
LIB = common.a
MAKE = make

$(LIB): $(OBJS)
	ar cr $(LIB) $(OBJS) 

pagedir.o: pagedir.h $L/file.h $L/webpage.h
index.o: index.h $L/hashtable.h
word.o: word.h

clean:
	rm -f core
	rm -f $(LIB) *~ *.o


#only .o files go in the library!
