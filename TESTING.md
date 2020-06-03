# TESTING.md for Sudoku creator/solver
## by Spencer Grimm and Erich Woo, June 2020

### Unit Testing
* To unit test the functions we created in `c_sudo.c`, we used macros to execute printing of the grid at its various stages in the creation process.
* In the function `set_sum()`, we print each digit of the 'digit set' passed to the function each time it runs.
   * This allows us to see what numbers are possible to fill each position as the creator executes.
   * We can also see when the sum of the set is 0, which is when the creator will backtrack.
* We unit test `fill_grid()` by printing the grid after the function has filled all 81 positions with valid numbers.
   * We also check that the completed grid created is a valid Sudoku game and print an error if it's not. 
   * As long as it outputs a full, correct Sudoku game, we know that `fill_grid()` has executed properly.
* We unit test `remove_cells()` by copying the completed game (now with 50 empty cells) into a new game, then solving that game with the provided solver and printing the number of solutions it has.
   * If there is only 1 solution, then `remove_cells()` has correctly done its job of creating a uniqueSudoku game.
* Note that we felt it was sufficient to include the unit tests in a standard run of the creator because our error checking occurs outside of these functions. Therefore, we know for sure that:
   * `fill_grid()` and `remove_cells()` will always be passed a valid 9x9 array as the game.
   * `fill_grid()` will always be called starting from position 1.
   * `remove_cells()` will always remove exactly 50 cells from the grid.

To run unit testing, simply run 'make test'. This will output the tests detailed above in a standard run of the creator.

### Fuzz Testing
* We wrote an additional C program to conduct fuzz testing on the creator and solver.
* This program takes as a command-line arguments the number of puzzles to create and solve.
* It then uses the creator to create *n* puzzles and the solver to solve them.
* If ever the program attempts to create an invalid puzzle or an invalid solution, it prints an error message and continues.
* After all *n* puzzles have been created and solved, it totals the number of errors from the creator and the solver and prints how many there were for each. 
* If no error, it prints a success message. 
