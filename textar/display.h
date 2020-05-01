#ifndef DISPLAY_H
#define DISPALY_H

#include <windows.h>


/* Clears cmd */
void clear_cmd();


/* Prints header at the top of cmd window */
void display_header(const COORD *wSize);


/* Print footer at the bottom of cmd window */
void display_footer(const COORD *wSize);


#endif
