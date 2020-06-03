# CS50 Project
## Sudoku Implementation Spec
### Erich Woo & Spencer Grimm, Spring 2020

### Pseudocode for sudoku `main()`

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
1. initiate a struct timeval t to track time in microseconds
2. get the microsecond of the t (ignore seconds) and use as seed in srand()
3. loop n times, where n is desired cells to remove,
   1. initiate start condition 'temp' = 0; after while loop begins, temp = number of solutions in solved sudoku game
   2. while 'temp' doesn't equal 1 (aka the solution after removing cell wasn't unique, so try again),
      1. initiate another start condition 'blank' = 0; after while loop begins, blank = the value at randomly chosen cell
      2. while 'blank' is 0 (aka the randomly chosen cell already has been removed earlier, so try again)
      	 1. get time of day for timeval t, use as a horizontal shift for rand() below
	 2. randomly select cell # from 0 to 80 using modulus
	 3. calculate the row and column based on idx
	 4. set 'blank' equal to the value at (row, col). Will keep looping 1-4 until this isn't 0
      3. copy the game to test a potential removal of that (row, col).
      4. set (row, col) in copy to 0, and call *sudo_solve* on copy (set to 'temp'). Will keep looping 1-4 until this 'temp' value is 1
   3. Set (row, col) in the game to 0

Note: I chose to do a while loop within a while loop (instead of a single while loop with two expressions connected with &&), because of speed concerns as the # desired to remove increases. The inner while loop requires a tiny constant clock time to loop while validating one of the expressions, but the outer loop requires an large & increasing amount of clock time while validating the other expression. More details in s_sudo.c inline comments.

### Function Prototypes

Within the creator module *c_sudo*:

```c
void fill_grid(int pos, int game[9][9]);
void remove_cells(int num, int game[9][9]);
int set_sum(int digit_set[9]);
void create(int game[9][9]);
```
* `num` indicates the number of cells to be removed in `remove_cells()`
* `pos` indicates the position (1 through 81) of the current cell being filled in `fill_grid()`
* `game[9][9]` always refers to the representation of a Sudoku game as an array of 9 arrays (each containing 9 integers)
* `set_sum()` is just a helper function for `fill_grid()` that calculates the sum of all values in a set containing 9 integers.
* `print_grid()` simply formats the given grid into 9 rows containing 9 digits each, each digit separated by a space and each row separated by a newline, and prints to `stdout`.

Additional functions we added to Professor Vasanta's *s_sudo*:

```c
int stdin_solve(int game[9][9]);
int solve(int game[9][9], int fuzz);
```

* `game[9][9]` in stdin_solve is an empty game grid, which will be filled by standard input and solved by the internal solver
* `game[9][9]` in solve is the puzzle to be solved.
* `fuzz` in solve is either 1 or 0, signifying whether or not in fuzztesting (additional printing is desired)

These functions were added to aid in our *sudoku.c* and *fuzzsudo.c*

### Data Structures

No additional data structures created.

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
