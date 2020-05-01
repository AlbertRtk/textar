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
	int i;
	char c;
	
	oldSize.X = 0;
	oldSize.Y = 0;
	c = NULL;

	/* clear console after start */
	clear_cmd();
	
	while (true) {
		wSize = get_window_size();
		
		/* clear console to remove extra print of title, header, ... */
		clear_if_window_changed_size(&oldSize);

		/* widnow size changed - print everthing again to adjust to new width */
		if (NOT(are_coords_equal(&oldSize, &wSize))) {
			copy_coord(&wSize, &oldSize);
			goto_top_left();
			for (i = 0; i < wSize.X; i++) putchar('_');
			putchar('\n');
			goto_bottom_left();
			putchar('C');

			gotoxy(0, 1);
		}

		/* catching char if button was hit */
		if (_kbhit()) {
			c = _getch();
		}

		switch (c) {
			case CTRL_KEYPRESS('x'):
				return 0;
			case NULL:
				break;
			default:
				putchar(c);
				c = NULL;
				break;
		}
	}
	
	return 0;
}

