#Makefile for common.a
#Ellie Boyd
#CS 50

L = ../libcs50
CC = gcc
CFLAGS = -Wall -pedantic -std=c11 -ggdb $(FLAGS)
OBJS = pagedir.o
LIB = common.a
MAKE = make

$(LIB): $(OBJS)
	ar cr $(LIB) $(OBJS) 

pagedir.o: pagedir.h $L/file.h

clean:
	rm -f core
	rm -f $(LIB) *~ *.o


#only .o files go in the library!
