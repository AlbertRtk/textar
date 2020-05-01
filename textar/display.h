#ifndef DISPLAY_H
#define DISPALY_H

#include <windows.h>


/* Clears cmd */
void clear_cmd();


/* Clears cmd if the size of window changed */
void clear_if_window_changed_size(const COORD *oldSize);


#endif
