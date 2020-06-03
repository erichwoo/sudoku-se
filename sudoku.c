/* 
 * Final project for CS50
 * Sudoku creator and solver
 * Usages:
 *    './sudoku create' to create a randomized Sudoku puzzle with a unique solution.
 *    './sudoku solve' to solve a Sudoku puzzle
 *    './sudoku create | ./sudoku solve' to pipe your created Sudoku to a solver 
 *
 * Spencer Grimm and Erich Woo, May 2020
 */

#include <stdio.h>
#include <string.h>
#include "s_sudo.h"
#include "c_sudo.h"

int main(int argc, char *argv[])
{
	// validate arguments: exactly one arg which is either 'solve' or 'create'
	if (argc != 2 || (strcmp(argv[1], "create") != 0 && strcmp(argv[1], "solve") != 0)) {
		fprintf(stderr, "Usage: ./sudoku (create|solve)\n");
		return 1;
	}

	int game[9][9] = {0};
	if (strcmp(argv[1], "create") == 0) {
	  create(game);
	}
	
	// read and solve game from stdin
	if (strcmp(argv[1], "solve") == 0) {
	  if (stdin_solve(game))
	    return 2;
	}

	return 0;
}

// print the 9x9 grid, each number separated by a space
void print_game(int game[9][9])
{
	for (int i=0; i<9; i++) {
		for (int j=0; j<9; j++) {
			if (j==0) {
				printf("%d", game[i][j]);
			}
			else {
				printf(" %d", game[i][j]);
			}
		}
		printf("\n");
	}
}
