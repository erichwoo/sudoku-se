/* 
 * Final project for CS50
 * Sudoku creator--creates a randomized Sudoku puzzle with a unique solution.
 *
 * Spencer Grimm and Erich Woo, May 2020
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "s_sudo.h"

void print_game(int game[9][9]);
int fill_grid(int pos, int game[9][9]);
int set_sum(int digit_set[9]);

int main(int argc, char *argv[])
{
	// validate arguments: exactly one arg which is either 'solve' or 'create'
	if (argc != 2 || (strcmp(argv[1], "create") != 0 && strcmp(argv[1], "solve") != 0)) {
		fprintf(stderr, "Usage: ./creator create|solve\n");
		return 1;
	}

	if (strcmp(argv[1], "create") == 0) {
		// initialize the puzzle's grid and begin filling in numbers, starting in upper left corner
		int game[9][9];
		printf("%d\n", fill_grid(1, game));
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
			else if (j==8) {
				printf(" %d\n", game[i][j]);
			}
			else {
				printf(" %d", game[i][j]);
			}
		}
	}
}

// Creates a random, fully solved Sudoku grid
// return value: 1 = true, 0 = false
int fill_grid (int pos, int game[9][9])
{
	// need a new random seed so generated random sequence is not always the same
	srand(time(0));

	// return true if all of the positions in the game have been successfully filled
	if (pos == 82) {
		print_game(game);
		return 1;
	}

	else {
		// determine location in grid based on 'pos' parameter
		int row = (int) (pos-1) / 9;
		int col = (pos-1) % 9;

		// pick randomly from array of numbers that cell could possibly hold
		int digit_set[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
		while (set_sum(digit_set) != 0) {
			int idx = (rand() + pos)  % 9;
			int number = digit_set[idx];
			digit_set[idx] = 0;
			
			// if the randomly chosen number validly fits into the puzzle, move on to the next
			// otherwise, try a different number
			if (number != 0) {	
				if (is_valid_cell(row, col, number, game)) {
					game[row][col] = number;
			
					if (fill_grid(pos + 1, game) == 1) {
						return 1;
					}
				}
			}
		}
		// If no possible numbers, fit in the puzzle, go back to the previous square and try other numbers
		return 0;
	}
}

// add all of the items in a length-9 array of numbers
int set_sum(int digit_set[9]) 
{
	int sum = 0;
	for (int i=0; i<9; i++) {
		sum += digit_set[i];
	}

	return sum;
}
