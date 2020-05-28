# CS50 Project
## Sudoku Design Spec
## Erich Woo & Spencer Grimm, Spring 2020

### Sudoku

Sudoku is well known logic puzzle where numbers between 1 and 9 are placed on a 9x9 grid of cells. The placement of numbers has to follow certain rules according to the most common version of Sudoku. In this version the 9x9 grid is further divided into 9 square shaped regions of size 3x3.

In a valid Sudoku grid every number from 1 to 9 must appear:

* Only once in every row
* Only once in every column
* Only once in every 3x3 squared region

Our *Sudoku* can *create* a randomized puzzle with a unique solution for solving, and can *solve* a puzzle.

### User Interface

The Sudoku program will run from the command line with one argument. The two possible usages are:
 * `./sudoku create`
 * `./sudoku solve`

Any other command-line arguments will be considered invalid.
If the command is 'solve', the puzzle to solve will be read as an array from stdin.

### Inputs and Outputs

Input: The *creator* takes no inputs. The *solver* reads a puzzle from `stdin`, with the following structure:

* The grid is represented as 9 lines of text
* Each line contains 9 integers that range from 0 to 9, separated by a whitespace
* 0 represents a missing number in the grid

The inputted puzzle may have multiple or one solution.

Output: The *creator* prints a randomized puzzle with a unique solution and containing at least 40 missing numbers. The puzzle's structure follows as stated above. If the command-line usage is incorrect, prints an error message.

The *solver* prints one solved solution for the inputted puzzle. If the puzzle has multiple solutions, any one of them may be printed. If there is no solution, a message indicating so is printed. The solved puzzle is printed with the same structure stated above. 

### Functional decomposition into modules

We anticipate the following modules or functions:
  1. main, which parses the command-line arguments and either solves from stdin or generates a new puzzle depending on the command.
  2. gridmaker, which randomly generates a fully-solved sudoku grid.
  3. cellremover, which removes at least 40 cells from a fully solved grid, creating a puzzle that still has a unique solution.
  4. solver, which solves a puzzle and indicates how many solutions it has (whether it is unique).

### Pseudo-code for Logic/Algorithmic Flow

We anticipate our *creator* to run as follows:

For generating a random filled grid, we have narrowed down to two options:

 1. Recursive backtracking
    1. Starting with the first square in the puzzle...
       1. Call a recursive function on a square in the puzzle.
       2. If the square's position is 82, return true. This means that all 81 squares in the puzzle have been correctly filled.
       3. If the square's position is not 82...
          1. Create a set of numbers, 1 through 9.
          2. While the set is not empty...
             1. Remove a number from the set
             2. Insert this number into the square of interest in the puzzle
             3. Check if the insertion has maintained a valid puzzle.
             4. If it has, recursively call the function on the next square in the puzzle.
                1. If this call to the function returns true (meaning all 81 squares are filled), return true.
                2. Otherwise, repeat with a different random number from the set.
          3. If the set has emptied out without returning, return false. This will cause the function to return to the previous square and try a different number in its set.

 2. 3x3 grid build
    1. for each number 1-9,
       1. initate int[3][3] c_block, signifying which column of grids, then which column within that column of grids is blocked. Scope is for each number, but shouldn't reset every row of grids; need to trace across every grid. 
       2. for each row of grids in puzzle (3)
       	  1. initiate int[3] r_block of {0,0,0} signifiying (0/1) whether the {top,middle/bot} is blocked out within that row of grids. Scope is for each row of grids; should reset every row, but need to trace while walking down each grid in the row. 
       	  2. for each column of grids in puzzle (3)
       	     1. get the set of 0's for that grid
	     	* will be a set of {row, column} locations in the grid
	     2. remove blocked rows and blocked columns from set of 0's based on int[3] r_block and int[3][3] c_block
	     3. randomly select one {r, c} location in set of 0's and place number in that location in grid.
	     4. fill in which row in that row of grids is blocked in r_block
	     5. fill in which column in that column of grids is blocked in c_block

Once the grid is fully filled...
   1. For a random number of iterations between 40 and 81...
      1. Remove a random number from the puzzle and replace with 0.
      2. Run the new puzzle through the solver.
      	 1. If the puzzle is not unique, reinstate the deleted number and try again.
         2. Otherwise, keep the number deleted and move on to another.

### Dataflow through modules
  1. main parses the arguments and calls eitehr gridmaker or solver, depending on whether instructed to create or solve.
  2. gridmaker randomly generates a puzzle and passes it to cellremover.
  3. cellremover converts some of the cells to 0 and prints the result to stdout.
  4. solver takes an unsolved puzzle from stdin, solves it, and prints the result to stdout. 

### Major Data Structures

* It's not an explicit data "struct", but we will be working with a *puzzle* of integers in a 9x9 array.

If we go ahead with our "3x3 grid build* method, we expect the following structures:

* a *ggrid* of *igrid*s in a 3x3 array; THE *ggrid* represents the whole 9x9 puzzle containing 9 *igrid*s in a 3x3 setup.
* a *igrid* struct of 1) integers in a 3x3 array and 2) its row within *ggrid* and 3) its column within *ggrid*; The *igrid* represents a single 3x3 grid within the puzzle. 

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
