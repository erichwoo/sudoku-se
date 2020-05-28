#CS50 Project
## Project Design Spec
## Erich Woo & Spencer Grimm

### Sudoku

Sudoku is well known logic puzzle where numbers between 1 and 9 are placed on a 9x9 grid of cells. The placement of numbers has to follow certain rules according to the most common version of Sudoku. In this version the 9x9 grid is further divided into 9 square shaped regions of size 3x3.

In a valid Sudoku grid every number from 1 to 9 must appear:

*Only once in every row
*Only once in every column
*Only once in every 3x3 squared region

Our *Sudoku* can *create* a randomized puzzle with a unique solution for solving, and can *solve* a puzzle.

### User Interface
### Inputs and Outputs

Input: The *creator* takes no inputs. The *solver* reads a puzzle from `stdin`, with the following structure:

* The grid is represented as 9 lines of text
* Each line contains 9 integers that range from 0 to 9, separated by a whitespace
* 0 represents a missing number in the grid

The inputted puzzle may have multiple or one solution.

Output: The *creator* prints a randomized puzzle with a unique solution and containing at least 40 missing numbers. The puzzle's structure follows as stated above. If the command-line usage is incorrect, prints an error message.

The *solver* prints one solved solution for the inputted puzzle. If the puzzle has multiple solutions, any one of them may be printed. If there is no solution, a message indicating so is printed. The solved puzzle is printed with the same structure stated above. 

### Functional Decomposition into Modules
### Pseudo-code for Logic/Algorithmic Flow

For generating a random filled grid:
 1. Backtracing
    
 2. 3x3 grid build
    1. for each number 1-9,
       1. initate int[3][3] c_block, signifying which column of grids, then which column within that column of grids is blocked. Scope is for each number, but shouldn't reset every row of grids; need to trace across every grid. 
       2. for each row of grids in puzzle (3)
       	  1. initiate int[3] r_block of {0,0,0} signifiying (0/1) whether the {top,middle/bot} is blocked out within that row of grids. Scope is for each row of grids; should reset every row, but need to trace while walking down each grid in the row. 
       	  2. for each column of grids in puzzle (3)
       	     1. get the set of 0's for that grid
	     	1. will be a set of {row, column} locations in the grid
	     2. remove blocked rows and blocked columns from set of 0's based on int[3] r_block and int[3][3] c_block
	     3. randomly select one {r, c} location in set of 0's and place number in that location in grid.
	     4. fill in which row in that row of grids is blocked in r_block
	     5. fill in which column in that column of grids is blocked in c_block

### Dataflow through Modules

### Major Data Structures

* It's not an explicit data "struct", but we will be working with a *puzzle* of integers in a 9x9 array.

If we go ahead with our "3x3 grid build* method, we expect the following structures:

* a *ggrid* of *igrid*s in a 3x3 array; THE *ggrid* represents the whole 9x9 puzzle containing 9 *igrid*s in a 3x3 setup.
* a *igrid* struct of 1) integers in a 3x3 array and 2) its row within *ggrid* and 3) its column within *ggrid*; The *igrid* represents a single 3x3 grid within the puzzle. 

### Testing Plan