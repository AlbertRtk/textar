/* 
Functions to deal with size of command line window and position of cursor 
*/

#ifndef CMDCS_H
#define CMDCS_H

#include <windows.h>
#include <stdbool.h>


/* Returns size of console window as number of columns (characters in row) and rows */
COORD get_window_size();


/* Sets cursor at position (x, y) in command line window */
void gotoxy(int x, int y);


/* Sets cursor at top left corner of cmd window */
void goto_top_left();


/* Sets cursor at bottom left corner of cmd window */
void goto_bottom_left();


/* Clears cmd if the size of window changed */
void clear_if_window_changed_size(const COORD *oldSize);


/* */
bool are_coords_equal(const COORD *coord1, const COORD *coord2);

#endif
