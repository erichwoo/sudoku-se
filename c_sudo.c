/* Author: Erich Woo & Spencer Grimm
 * Date: 2 June 2020
 * Purpose: Create a valid randomized Sudoku puzzle with a unique solution.
 */

#include "c_sudo.h"

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
		print_grid(game);
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

int remove_cells(int num, int game[9][9]) {
  struct timeval t;
  gettimeofday(&t, NULL);
  srand(t.tv_usec % UINT_MAX); // ensure 32-bit system can handle 6 digits (2^16)
  int temp, blank, t_shift, idx, row, col, copy[9][9];

  for (int i = 0; i < num; i++) {
    temp = 0; // initiate start condition, reset temp with meaningful val after 1st loop
    // loop until a successful/valid trial-removal of r/c position from grid

    // https://www.math.ucdavis.edu/~tracy/courses/math135A/UsefullCourseMaterial/couponProblem.pdf
    // make sure doesn't break into infinite loop
    double k = 0; // track how many times each number is tried to cut off infinite loop if no solution 
    double n = 81 - i; // # of filled cells that the algorithm must all select
    double gamma = 0.5772156649; // Euler–Mascheroni constant approximation
    double expected_n = n * (log(n) + gamma + 1 / n); // coupon collector's problem
    while (temp != 1) {
      if (k > 2 * expected_n) { // looking at distribution, highly unlikely past 2*expected
	printf("Got stuck in search with no solutions at %d depth after %d tries.\n", i + 1, (int)k);
	return 1;
      }
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
      k++;
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

   return 0;
}

int create(int num, int game[9][9]) {
  fill_grid(1, game);
  if (remove_cells(num, game))
    return 1;
  print_grid(game);
  return 0;
}
