#ifndef __S_SUDO_H
#define __S_SUDO_H

/* Purpose: Check if having the data in the cell (row, col) as 'value'
 * violates Sudoku rules.
 * Return value: 0 if violates the rules
 * 				 1 if doesn't violate the rules 
 * Assumes parameter value is never 0.
 */ 
int is_valid_cell(int row, int col, int value, int game[9][9]);

/* Purpose: Check is the given game grid is a valid Sudoku grid. 
 * Return value: 0 if not-valid grid
 *				 1 if valid grid
 * Assumes parameter value is never 0.
 */
 
int is_valid_grid(int game[9][9]);

/* Purpose: Find the next cell after (r,c) that has a value 0 (empty cell). 
 * This function only looks for such cells in forward direction.  
 * Return value: None
 * Special note: The row and column numbers of the next empty cell 
 * are populated in the given parameters next_r and next_c. 
 */
 
void get_next_cell(int r, int c, int *next_r, int *next_c, int game[9][9]);

/* Purpose: Backtracking based recursive function to solve a given Sudoku 
 * puzzle. Each call to the function finds a possible value for cell at (r,c)
 * and makes a recursive call to next cell with a 0.
 *
 * Parameters: r and c give the row and col of the cell, 
 *             ggame is the puzzle, 
 *             sol is the grid to return the solution,
 *             num_sols is to keep track of number of solutions seen so far. 
 *
 * Return value: 0 if ggame cannot be solved, 
 *               1 if unique solution, 
 *               2 if multiple solutions are possible
 * Special note: This solver does not find multipl solutions
 */

int recursive_solve(int r, int c, int ggame[9][9], int sol[9][9], int num_sols);

/* Purpose: To print the given puzzle grid to stdout
 */
void print_grid(int ggrid[9][9]);

/* Purpose: To copy ogame grid to ngame grid
 */
void copy_game(int ogame[9][9], int ngame[9][9]);

/* Purpose: To read a Sudoku puzzle grid from stdin
 */
int read_game(int ggame[9][9]);

/* Top level Sudoku solver */
int sudo_solve(int ggame[9][9]);

/* Added by Erich & Spencer
 * reads from stdin then validates input then calls solve() below
 * 
 * @param game a blank game grid
 * @return 1 if reading error, 0 otherwise
 */
int stdin_solve(int game[9][9]);

/* Added by Erich & Spencer
 * calls sudo_solve above, printing output depending on fuzz
 * fuzz = 1: called by fuzztesting
 * 
 * prints # of solutions and solved grid (if # > 0)
 * if fuzz = 1, also prints Success(# = 1) or Fail message
 *
 * @param game the puzzle to solve
 * @param fuzz whether (1) or not (0) fuzztesting output desired
 * @return 1 if error in fuzztesting mode, 0 otherwise
 */
int solve(int game[9][9], int fuzz);
#endif
