# Makefile for Sudoku 'creator'
#
# Spencer Grimm and Erich Woo, May 2020

PROG = creator
OBJS = creator.o s_sudo.o

# uncomment to turn on unit testing
#UNITTEST = -DUTEST

CFLAGS = -Wall -pedantic -std=c11 $(UNITTEST)
CC = gcc
MAKE = make

$(PROG): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

creator.o: s_sudo.h
s_sudo.o: s_sudo.h

.PHONY: clean

clean:
	rm -f *~ $(PROG).o *.dSYM
	rm -f $(PROG)
	rm -f stocks
