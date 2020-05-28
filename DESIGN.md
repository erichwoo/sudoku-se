#CS50 Project
## Project Design Spec
## Erich Woo & Spencer Grimm

### Sudoku

### User Interface
The Sudoku program will run from the command line with one argument. The two possible usages are:
 * `./sudoku create`
 * `./sudoku solve`
Any other command-line arguments will be considered invalid.
If the command is 'solve', the puzzle to solve will be read as an array from stdin.

### Pseudocode

For generating a random filled grid:
 1. Backtracing
 2. 3x3 grid build
    1. for each row of 3x3 grids
       1. for each column of 3x3 grids
       	  1. 
random build
