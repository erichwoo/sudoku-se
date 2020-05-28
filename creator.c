/* 
 * Final project for CS50
 * Sudoku creator--creates a randomized Sudoku puzzle with a unique solution.
 *
 * Spencer Grimm and Erich Woo, May 2020
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "s_sudo.h"

void print_game(int game[9][9]);

int main(int argc, char *argv[])
{
	// validate arguments: exactly one arg which is either 'solve' or 'create'
	if (argc != 2 || (strcmp(argv[1], "create") != 0 && strcmp(argv[1], "solve") != 0)) {
		fprintf(stderr, "Usage: ./creator create|solve\n");
		return 1;
	}

	if (strcmp(argv[1], "create") == 0) {
		int game[9][9];
		print_game(game);
	}

	return 0;
}

void print_game(int game[9][9])
{
	for (int i=0; i<=9; i++) {
		for (int j=0; j<=9; j++) {
			if (j==0) {
				printf("%d", game[i][j]);
			}
			else if (j==9) {
				printf(" %d\n", game[i][j]);
			}
			else {
				printf(" %d", game[i][j]);
			}
		}
	}

}
