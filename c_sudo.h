#ifndef __C_SUDO_H
#define __C_SUDO_H

/* Author: Erich Woo & Spencer Grimm
 * Date: 2 June 2020
 * Purpose: Header file for c_sudo.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <limits.h>
#include "s_sudo.h"

/* Creates a random, fully solved Sudoku grid
 *
 * @param pos the position in grid to fill
 * @param game the game grid to fill
 * @return 1 = true, 0 = false    
 */
int fill_grid (int pos, int game[9][9]);

/* Add all of the items in a length-9 array of numbers
 *
 * @param digit_set the len-9 set of digits
 * @return the sum of the digits in set
 */
int set_sum(int digit_set[9]);

/* Removes a set number of cells from a complete grid
 * while retaining valid Sudoku characteristics
 *
 * @param num the number of cells to remove
 * @param game the filled grid
 */
void remove_cells(int num, int game[9][9]);

/* Creates a Sudoku Game and prints it to stdout
 *
 * @param game an empty 9x9 game grid to fill
 */
void create(int game[9][9]);

#endif // __C_SUDO_H
