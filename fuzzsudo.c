/* Author: Erich Woo & Spencer Grimm
 * Date: 1 June 2020
 * Purpose: Fuzztesting for Sudoku creator and solver. 
 * Inspired by David Kotz's and Xia Zhou's 'fuzzquery.c'
 *
 * Usage: ./fuzzsudo numPuzzles
 */

#include <stdio.h>
#include <stdlib.h>
#include "s_sudo.h"
#include "c_sudo.h"

int validate(int argc, char* argv[], int* numPuzzles);

int main(int argc, char* argv[]) {
  int numPuzzles, c_error = 0, s_error = 0;
  validate(argc, argv, &numPuzzles);
  
  printf("generating %d puzzles...\n\n", numPuzzles);
  for (int i = 0; i < numPuzzles; i++) {
    int created[9][9] = {0}, solved[9][9];
    printf("------------- Fuzztesting Puzzle %d --------------\n", i + 1);
    printf("The puzzle to solve:\n");
    create(created);
    copy_game(created, solved);

    // solve and check if unique solution
    c_error += solve(solved, 1);

    // check if solution follows Sudoku Rules
    if (!is_valid_grid(solved)) {
      printf("Error: solution does not follow Sudoku rules.\n");
      s_error++;
    }

    // check if solution didn't change original puzzle
    for (int j = 0; j < 9; j++) {
      for (int k = 0; k < 9; k++) {
	int true_val = created[j][k], val;
	if (true_val) {
	  if ((val = solved[j][k]) != true_val) {
	    printf("Error: already-filled cell %dx%d was changed from %d to %d during solve.\n", j + 1, k + 1, true_val, val);
	    s_error++;
	  }
	}
      }
    }
  }
  
  printf("--------------- END OF FUZZTESTING ---------------\n");
  printf("Number of errors found in %d puzzles: %d\n\n", numPuzzles, s_error + c_error);
  if (s_error || c_error) {
    fprintf(stderr, "%d creator errors and %d solver errors\n", c_error, s_error);
  }
  return s_error + c_error; // 0 if no error, positive if error (and its #)
}

int validate(int argc, char* argv[], int* numPuzzles) {
  char extra;
  if (argc != 2) {
    fprintf(stderr, "Usage: ./fuzzsudo numPuzzles\n");
    exit(1);
  }
  if (sscanf(argv[1], "%d%c", numPuzzles, &extra) != 1 || *numPuzzles < 0) {
    fprintf(stderr, "Error: invalid numPuzzles '%s'\n", argv[1]);
    exit(2);
  }
  return 0;
}
