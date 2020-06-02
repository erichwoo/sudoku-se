# Makefile for Sudoku 'creator'
#
# Spencer Grimm and Erich Woo, May 2020

PROG = creator
OBJS = creator.o s_sudo.o

UNITTEST = -DUTEST

CFLAGS = -Wall -pedantic -std=c11 -ggdb
CC = gcc
MAKE = make

$(PROG): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

creator.o: s_sudo.h
s_sudo.o: s_sudo.h

# run 'make unit' to unit test the creator
.PHONY: unit unittest clean

unittest: creator.c s_sudo.h s_sudo.o
	$(CC) $(CFLAGS) $(UNITTEST) $^ -o $@

unit: unittest
	./unittest create

clean:
	rm -f *~ *.o *.dSYM
	rm -f $(PROG)
	rm -f stocks
	rm -f unittest
