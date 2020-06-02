/* 
 * Final project for CS50
 * Sudoku creator--creates a randomized Sudoku puzzle with a unique solution.
 *
 * Spencer Grimm and Erich Woo, May 2020
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <limits.h>
#include "s_sudo.h"

void remove_cells(int num, int game[9][9]);
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

	int game[9][9] = {0};
	if (strcmp(argv[1], "create") == 0) {
	  // begin filling in numbers, starting in upper left corner
	  fill_grid(1, game);
	  remove_cells(50, game);
	  print_game(game);
	}
	
	// read and solve game from stdin
	if (strcmp(argv[1], "solve") == 0) {
		if (read_game(game) == 1) {
			int solutions = sudo_solve(game);
			if (solutions == 0) {
				printf("No solution.\n");
			}
			else {
				print_game(game);
			}
		}
		else {
			fprintf(stderr, "Error: passed invalid game\n");
			return 2;
		}
	}

	return 0;
}

/* Removes a set number of cells from a complete grid
 * while retaining valid Sudoku characteristics
 *
 * @param num the number of cells to remove
 * @param game the filled grid
 */
void remove_cells(int num, int game[9][9]) {
  struct timeval t;
  gettimeofday(&t, NULL);
  srand(t.tv_usec % UINT_MAX); // ensure 32-bit system can handle 6 digits (2^16)
  int temp, blank, t_shift, idx, row, col, copy[9][9];  

  for (int i = 0; i < num + 1; i++) {
    temp = 0; // initiate start condition, reset temp with meaningful val after 1st loop
    // loop until a successful/valid trial-removal of r/c position from grid
    while (temp != 1) {
      blank = 0; // same idea as 'temp'
      /* while-loop within while-loop to minimize sudo_solve calls
         'blank' loop < 10us constant time
         the rest of sudo_solve increases time as i increases
         ~70us(i=0), up to 600us(i=40), 20000us(i=50)
      */
      // randomly selects a r/c position to remove number from
      // keeps trying until that position hasn't already been removed
      while (!blank) { 
	gettimeofday(&t, NULL);
	t_shift = t.tv_usec % 1000; // allow more circulation of difference in 3 digits with mod 1000 since time differences will often vary in less than 1000us
	idx = (rand() + t_shift) % 81; // randomly select one space in 81
	row = idx / 9;
	col = idx % 9;
	blank = game[row][col];
      }
      // test removal on a copy of the game
      copy_game(game,copy);
      copy[row][col] = 0;
      temp = sudo_solve(copy);
    }
    // if the tried position can be removed while still
    // being unique, add it and move on in forloop
    game[row][col] = 0;
  }

// unit testing: copy the game and solve to check that it only has 1 solution
#ifdef UTEST
  printf("After remove_cells:\n");
  int ngame[9][9] = {0};
  copy_game(game, ngame); 
  printf("Grid has %d solutions.\n", sudo_solve(ngame));
#endif
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

// unit testing: indicate that print function executed successfully
#ifdef UTEST
	printf("Succesful print.\n");
#endif
}

// Creates a random, fully solved Sudoku grid
// return value: 1 = true, 0 = false
int fill_grid (int pos, int game[9][9])
{
	// need a new random seed so generated random sequence is not always the same
        struct timeval t;
	gettimeofday(&t, NULL);
	srand(t.tv_usec % UINT_MAX); // ensure 32-bit system can handle 6 digits (max 2^16)

	// return true if all of the positions in the game have been successfully filled
	if (pos == 82) {
// unit testing: print the game at this point, after it has been filled
#ifdef UTEST
		printf("\nAfter fill_grid:\n");
		print_game(game);
		printf("\n");
#endif
		return 1;
	}

	else {
		// determine location in grid based on 'pos' parameter
		int row = (int) (pos-1) / 9;
		int col = (pos-1) % 9;
		int t_shift;

		// pick randomly from array of numbers that cell could possibly hold
		int digit_set[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
		
		while (set_sum(digit_set) != 0) {
		        gettimeofday(&t, NULL);
			t_shift = t.tv_usec % 1000; // time variance is in final 1000us range
			int idx = (rand() + t_shift) % 9;
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
					//delete from grid
					game[row][col] = 0;
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

// unit testing: check that function correctly adds each item in the digit set
#ifdef UTEST
	printf("Sum:");
	for (int i=0; i<8; i++) {
		printf(" %d +", digit_set[i]);
	}
	printf(" %d = ", digit_set[8]);
	printf("%d\n", sum);
#endif
	return sum;
}
