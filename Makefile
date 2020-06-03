# Makefile for Sudoku 'creator'
#
# Spencer Grimm and Erich Woo, May 2020

#programs
PROG = sudoku
FUZZ = fuzzsudo
UNIT = unittest

#modues
C = c_sudo
S = s_sudo

#object dependencies
OBJS = $(S).o $(C).o $(PROG).o
FUZZOBJS = $(S).o $(C).o $(FUZZ).o
UNITTESTOBJS = $(S).o $(C)_$(UNIT).o $(PROG).o

UNITTEST = -DUTEST

CFLAGS = -Wall -pedantic -std=c11 -ggdb -lm
CC = gcc
MAKE = make

all: $(PROG) $(FUZZ) $(UNIT)

$(PROG): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

$(FUZZ): $(FUZZOBJS)
	$(CC) $(CFLAGS) $^ -o $@

$(PROG).o: $(S).h $(C).h

$(S).o: $(S).h

$(C).o: $(S).h $(C).h

$(C)_$(UNIT).o: $(S).h $(C).h
	$(CC) $(CFLAGS) $(UNITTEST) -c -o $@ $(C).c

# run 'make unit' to unit test the creator
.PHONY: unit unittest clean

$(UNIT): $(UNITTESTOBJS)
	$(CC) $(CFLAGS) $^ -o $@

unit: unittest
	./unittest create

test: testing.sh
	bash -v testing.sh

clean:
	rm -f *~ *.o *.dSYM core
	rm -f $(PROG) $(FUZZ)
	rm -f stocks
	rm -f unittest
