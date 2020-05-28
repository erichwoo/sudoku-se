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

### Functional decomposition into modules

We anticipate the following modules or functions:
  1. main parses the command-line arguments and either solves from stdin or generates a new puzzle depending on the command.
  2. gridmaker, which randomly generates a fully-solved sudoku grid.
  3. cellremover, which removes at least 40 cells from a fully solved grid, creating a puzzle that still has a unique solution.
  4. solver, which solves a puzzle and indicates how many solutions it has (whether it is unique).

### Pseudocode

For generating a random filled grid:
 1. Backtracing
   1. Note every possible number that can occur in a cell by checking if each digit 1-9 satisfies the Sudoku rules:
      1. Only one of each number per row
      2. Only one of each number per column
      3. Only one of each number per 3x3 square
   2. Randomly select one of these numbers and put it in the cell.
   3. If there are no possible numbers that can be put in a cell:
      1. Return to the previous cell and pick a different number from its set of possible numbers.
      2. Repeat while there are no numbers to choose from for each cell.
 2. Once the grid is fully filled...
   1. For a random number of iterations between 40 and 81...
     1. Remove a random number from the puzzle and replace with 0.
     2. Run the new puzzle through the solver.
        1. If the puzzle is not unique, reinstate the deleted number and try again.
        2. Otherwise, keep the number deleted and move on to another.

 2. 3x3 grid build
    1. for each row of 3x3 grids
       1. for each column of 3x3 grids
       	  1. 
random build



### Dataflow through modules
  1. main parses the arguments and calls eitehr gridmaker or solver, depending on whether instructed to create or solve.
  2. gridmaker randomly generates a puzzle and passes it to cellremover.
  3. cellremover converts some of the cells to 0 and prints the result to stdout.
  4. solver takes an unsolved puzzle from stdin, solves it, and prints the result to stdout. 

### Testing plan
* Unit testing
  * gridmaker
    * We will test the gridmaker by outputting the the fully-filled grid that it produces.
    * This will include checking that each row, column and 3x3 cell contain each number 1 through 9 exactly once.
    * We will output multiple grids from the gridmaker to ensure that a random grid is created each time. 
  * cellremover
    * We will test the cellremover by outputting the updated grid and making sure that at least 40 cells have been removed and replaced with 0. 
    * Additionally, we will run the updated grid through the solver to make sure that each grid has only one solution.
    * We will test the same array from the gridmaker on the cellremover multiple times to make sure it randomly deletes cells.
* Fuzz testing
  * To test the solver, we will perform fuzz testing. To start, we will use the gridmaker to produce many valid puzzles.
  * Then, we will create a new function that randomly removes cells. Unlike the cellremover, this function will not check that it creates a unique puzzle each time. 
  * All of these unique puzzles will be passed to the solver to check for potential edge cases that we would have otherwise missed. We will check the solution to each randomly generated puzzle to make sure it was correctly solved and that the solver correctly indicated how many solutions it has. 
