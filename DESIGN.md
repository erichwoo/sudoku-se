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
  1. main parses the command-line arguments and either solves from stdin or generates a new puzzle depending on the command.
  2. gridmaker, which randomly generates a fully-solved sudoku grid.
  3. cellremover, which removes at least 40 cells from a fully solved grid, creating a puzzle that still has a unique solution.
  4. solver, which solves a puzzle and indicates how many solutions it has (whether it is unique).

### Pseudo-code for Logic/Algorithmic Flow

We anticipate our *creator* to run as follows:

For generating a random filled grid, we have narrowed down to two options:

 1. Backtracking
    1. Note every possible number that can occur in a cell by checking if each digit 1-9 satisfies the Sudoku rules:
       1. Only one of each number per row
       2. Only one of each number per column
       3. Only one of each number per 3x3 square
    2. Randomly select one of these numbers and put it in the cell.
    3. If there are no possible numbers that can be put in a cell:
       1. Return to the previous cell and pick a different number from its set of possible numbers.
       2. Repeat while there are no numbers to choose from for each cell.

 2. selective/constraint-based Backtracing with 3x3 grid building
    1. initiate int[9][2][9] block[] to 0 for blocked row/columns [#][r/c][r/c #]. 1 signifies that number's row/column # is blocked
    2. initiate an int index at 1, will run from 1-81
    3. initiate an empty *ggrid* (see Major Data Structures)
    4. call BUILD_FUNC(index, block[], *ggrid*)
       1. if index = 82,
       	  1. return true; will recursively return true back to top-level
       2. otherwise, choose # based on 81/9 rounded up (index - 1)/9 + 1
       	  * will increment from 1 to 9
	  * if this isn't still random (which I think it is), then just create variables tracking # selected/still available
       3. select the 3x3 *igrid* based on index % 9 ie. row (1-3, 4-6, 7-8 & 0) and column (147, 258, 360)
       4. get a copy of the set of 0's for that *igrid*
       5. remove blocked rows and blocked columns from set of 0's based block[]
       6. while set of 0's is not empty,
       	  1. randomly select one {r, c} location in set of 0's and place number in that location in *igrid*.
       	  2. if sudoku solver success,
       	     1. fill in which row in that row of grids is blocked in block[]
       	     2. fill in which column in that column of grids is blocked in block[]
	     3. call BUILD_FUNC(index+1, block[], puzzle)
	     4. if above is true, return true
	     5. if above is false, remove # from *igrid*, block[], and set of 0's, then try again.
       7. if set of 0's is exhausted, return false; will go back up one level to previous BUILD_FUNC call.
       
Once the grid is fully filled...
   1. For a number of iterations between 40 and 64... (we'll expand this as much as we can)
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
* a *igrid* struct of 1) integers in a 3x3 array 2) its row within *ggrid* 3) its column within *ggrid* and 4) a set of the 0's in the grid ; The *igrid* represents a single 3x3 grid within the puzzle. 

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
