# Spencer Grimm and Erich Woo
## CS50 Spring 2020, Sudoku Project
## Project Name: sudoku-se

Github usernames: erichwoo & spencergrimm23

To make executables for `sudoku`, `fuzzsudo`, and `unittest`, run `make`.

To unit test the creator, run `make unit`.

To fuzztest the creator and solver, run `./fuzzsudo numPuzzles`, where `numPuzzles` is the number of puzzles you want the fuzztester to create and solve.

The usage for `sudoku` is either `./sudoku create` or `./sudoku solve`
* 'create' will generate a randomized Sudoku puzzle and print to `stdout`
* 'solve' will read a puzzle represented as a 9x9 grid from `stdin`, fill in the missing values to create a valid solution, and print the result to `stdout`. 

To test unittesting and fuzztesting together, run `make test`.

To clean, run `make clean`.

Notes:

No extra credit done.

We added two functions to Professor's *s_sudo.c* solver module (for organization & consolidation of solver-related methods). They are `stdin_solve` and `solve`, at the bottom of the .c and .h file.

We did not unit test the *solver* module, as it was created by Professor.

