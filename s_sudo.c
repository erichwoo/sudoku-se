#include <unistd.h>
#include <stdio.h>
#include "s_sudo.h"

int is_valid_grid(int game[9][9]){
    for (int i = 0; i < 9; i++){
        for (int j = 0; j < 9; j++){
            int test = is_valid_cell(i, j, game[i][j], game);
            if (!test) return 0;
        }
    }
    return 1;
}

void get_next_cell(int r, int c, int *next_r, int *next_c, int game[9][9]){
    int i, j;
    for (i = r; i < 9; i++){
        int start;
        if (i == r) start = c;
        else start = 0;
        for(j = start; j < 9; j++){
            if (game[i][j] == 0){
                *next_r = i;
                *next_c = j;
                return;
            }
        }
    }
    *next_r = -1;
    *next_c = -1;
    return;
}

int is_valid_cell(int row, int col, int value, int game[9][9]){
    int i, j;

    // Check if value exists in the same block
    for (i = 0; i < 9; i++){
        for (j = 0; j < 9; j++){
            if ((i != row) || (j != col)){
                if ((((int) i/3) == ((int) row/3)) && (((int) j / 3) == ((int) col/3))) {
                    if (game[i][j] == value){
                        return 0;
                    }
                }
            }
        }
    }

    // Check if value exists in the same row
    for (i = 0; i < 9; i++){
        if (i != col){
            if (game[row][i] == value) {
                return 0;
            }
        }
    }

    // Check if value exists in the same column

    for (i = 0; i < 9; i++){
        if (i != row){
            if (game[i][col] == value) {
                return 0;
            }
        }
    }

    return 1;
}

void print_grid(int ggrid[9][9]){
    for (int i = 0; i < 9; i++){
        for (int j = 0; j < 9; j++){
            printf("%d ", ggrid[i][j]);
        }
        printf("\n");
    }
}

void copy_game(int ogame[9][9], int ngame[9][9]){
    for (int i=0; i < 9; i++){
        for (int j=0; j < 9; j++){
            ngame[i][j] = ogame[i][j];
        }
    }
}

int read_game(int ggame[9][9]){
    for (int i=0; i < 9; i++){
        for(int j=0; j < 9; j++){
            int val;
            int ret = fscanf(stdin, "%d", &val);
            ggame[i][j] = val;
            if (ret != 1){
                return 0;
            }
        }
    }
    return 1;
}

int recursive_solve(int r, int c, int ggame[9][9], int sol[9][9], int num_sols){
    for (int i=1; i <= 9; i++){
        // Try all values 1 to 9 and if valid make recursive calls
        if (is_valid_cell(r, c, i, ggame)){
            int next_r, next_c;
            ggame[r][c] = i;

            // Find the next cell with a missing value (represented as 0)
            get_next_cell(r, c, &next_r, &next_c, ggame);
            if ((next_r != -1) || (next_c != -1)){
                int ret = recursive_solve(next_r, next_c, ggame, sol, num_sols);
                num_sols = ret;

                //if found more than two solutions are found then return 2, 
                //indicating the puzzle doesn't have a unique solution.
                //otherwise continue looking for solutions.
                if (ret >= 2){
                    return ret;
                }
                ggame[r][c] = 0;
            }
            else {
                // No more cells with missing values remain.
                // ggame contains the puzzle with successful guesses for missing
                // values. Copy it into sol grid as backtracking to find 
                // next solution will overwrite the values in ggame.

                copy_game(ggame, sol);

		// reset that last cell from solfor finding next sol
		ggame[r][c] = 0;
		
                // Successfully found a solution so update the num_sols and
                // return it.
                return (num_sols + 1);
            }
        }
    }

    // Exhausted all possible values (r,c) and none of them 
    // worked. Return 0 to indicat puzzle is not solvable.
    return num_sols;
}

int sudo_solve(int ggame[9][9]){
    int r, c;
    int sol[9][9];

    //copy_game(ggame, sol);
    get_next_cell(0, 0, &r, &c, ggame); // get the first cell that has 0 entry 
    int pass1 = recursive_solve(r, c, ggame, sol, 0);
    int pass2 = is_valid_grid(sol);

    if (!(pass1 && pass2)) {
        return 0;
    }
    
    copy_game(sol, ggame);
    return pass1;
}

int stdin_solve(int game[9][9]) {
  if (read_game(game) == 1)
    solve(game, 0);
  else {
    fprintf(stderr, "Error: passed invalid game\n");
    return 1;
  }
  return 0;
}

// for some reason implicit declaration still happens with stdio.h
int fileno(FILE *stream);

int solve(int game[9][9], int fuzz) {
  if (fuzz || isatty(fileno(stdin))) // for better readability
    printf("\n");
  int solutions = sudo_solve(game);
  printf("%d solution(s) found.\n", solutions);
  if (solutions)
    print_grid(game);
  
  if (fuzz == 1 && solutions != 1) {
    printf("Error: Sudoku creator failed to create unique solution.\n");
    return 1;
  }

  return 0;
}
