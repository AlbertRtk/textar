#include <stdio.h>
#include <stdbool.h>
#include <conio.h>
#include "cmdcs.h"
#include "display.h"
#include "common.h"


#define CTRL_KEYPRESS(k) ((k) & 0x1f)


int main(int argc, char *argv[]) {
	COORD wSize;
	COORD oldSize;
	char c;
	
	oldSize.X = 0;
	oldSize.Y = 0;
	c = EMPTY_CHAR;

	/* clear console after start */
	clear_cmd();
	
	while (true) {
		wSize = get_window_size();

		/* widnow size changed - print everthing again to adjust to new width */
		if (NOT(are_coords_equal(&oldSize, &wSize))) {
			copy_coord(&wSize, &oldSize);
			clear_cmd();
			display_header(&wSize);
			display_footer(&wSize);
			gotoxy(0, 2);
		}

		/* catching char if button was hit */
		if (_kbhit()) {
			c = _getch();
		}

		/* taking action depending on c value */
		switch (c) {

			/* crtl-x pressed - exit */
			case CTRL_KEYPRESS('x'):
				clear_cmd();
				return 0;
			
			/* nothing pressed - continue */
			case EMPTY_CHAR:
				break;

			/* Enter hit - put new line */
			case ENTER_ASCII_VALUE:
				putchar(NEW_LINE);
				c = EMPTY_CHAR;
				break;

			/* typing - put char to screen */
			default:
				putchar(c);
				c = EMPTY_CHAR;
				break;
		}
	}
	
	return 0;
}
