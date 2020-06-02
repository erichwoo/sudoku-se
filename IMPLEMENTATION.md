# CS50 Project
## Sudoku Implementation Spec
### Erich Woo & Spencer Grimm, Spring 2020

### Pseudocode for `main()`

1. Validate parameters
   1. If there is not exactly one parameter with the call to 'creator'...
   2. Or if the one parameter is not the word 'create' or the word 'solve'...
      1. Exit with error status
2. Initialize the game data structure, a 9x9 array of arrays.
3. If the command-line argument is 'create':
   1. Call the `fill_grid()` function on the game starting from the first cell.
   2. Call the `remove_cells()` function on the game to remove 50 cells.
   3. Print the game, which should now have a unique solution and contain 50 spaces with 0s.
4. If the command-line argument is 'solve':
   1. Making use of the provided `s_sudo.h` module...
   2. Call `read_game()` to get the 9x9 grid game representation from `stdin`.
      1. If `read_game()` returns 0, return with error status, as an invalid grid has been passed to the solver.
   3. Call `sudo_solve()` on the game to file in the empty spaces. 
   4. If the return value of `sudo_solve()` on the game is 0:
      1. Indicate that there is no solution to the provided puzzle.
   5. Otherwise:
      2. Print the solved game to `stdout`.


### Pseudocode for `fill_grid()`

1. Use the current time of day as a seed for the `rand()` function to prevent the creation of the same grid with each call to the creator.
2. If the current position (a parameter of the function) is 82:
   1. Return 'true'. This means that all 81 cells in the grid have been correctly filled.
3. Otherwise:
   1. Calculate the row and column from the current cell position (knowing that there are 9 rows and 9 columns).
   2. Initialize an array of digits 1 through 9, representing the possible values that can occupy the current cell.
   3. While the sum of all 9 digits in the set is not 0:
      1. Use `rand()` with a timeshift to randomly generate an index into the digit set.
         1. Note: shift is necessary to prevent recurring patterns in the output grid.
      2. Store the number in that index in a variable and replace it with 0 in the array.
      3. If the obtained number is not 0 (meaning it has not already been tried as a member of the current well:
         1. If the number when put in the current row and column of the game would comply with Sudoku rules (verify by calling `is_valid_cell()`);
            1. Insert the number into the game at the current position.
            2. Recursively call `fill_grid()` on the next position. 
            3. If this call returns 'true' (will only happen if *all* of the rest of the cells have filled in validly):
               1. Return 'true'; the puzzle is complete.
            4. Otherwise:
               1. Remove the number from the puzzle. It cannot create a valid puzzle. Repeat the whole process with another random digit in the digit set.
   4. If none of the digits in the digit set, can create a valid puzzle, return 'false'.
      1. This means that backtracking must occur (values in previous positions must be altered) to create a valid puzzle.

### Pseudocode for `remove_cells()`

### Function Prototypes

```
void fill_grid(int pos, int game[9][9]);
void remove_cells(int num, int game[9][9]);
void print_grid(int game[9][9]);
int set_sum(int digit_set[9]);
```
* `num` indicates the number of cells to be removed in `remove_cells()`
* `pos` indicates the position (1 through 81) of the current cell being filled in `fill_grid()`
* `game[9][9]` always refers to the representation of a Sudoku game as an array of 9 arrays (each containing 9 integers)
* `set_sum()` is just a helper function for `fill_grid()` that calculates the sum of all values in a set containing 9 integers.
* `print_grid()` simply formats the given grid into 9 rows containing 9 digits each, each digit separated by a space and each row separated by a newline, and prints to `stdout`.

### Data Structures

### Error Handling

Will exit with status:
   * 0 if no error.
   * 1 if invalid arguments (incorrect number or argument is neither 'create' nor 'solve'.
   * 2 if the solver is passed an invalid game (not 9x9 grid).

Note:
   * A game with no solution being passed to the solver is not considered an error. The program will simply indicate that the puzzle cannot be solved and return without error status.

### Resource Management

* This program does not dynamically allocate any memory.
* Instead, it uses a locally initialized array-of-arrays data structure and passes it into various functions that alter its contents.
* It is not optimally efficient to store the `digit_set` as an array and iterate over its entirety to find the sum in each iteration of the while-loop, but because the array only ever holds 9 items, there is not a significant drain on time from this implementation.

### Persistent Storage

This program does not feature any persistent storage. All output goes to `stdout` and must be saved independently if the user desires to save it.
