#include <stdio.h>
#include <stdbool.h>
#include <conio.h>
#include "cmdcs.h"
#include "display.h"
#include "common.h"
#include "texteditor.h"


#define CTRL_KEYPRESS(k) ((k) & 0x1f)


int main(int argc, char *argv[]) {
	COORD wSize;
	COORD oldSize;
	char c;
	EditedFile editedFile;
	
	oldSize.X = 0;
	oldSize.Y = 0;
	c = NULL_CHAR;

	/* clear console after start */
	clear_cmd();
	
	init_file(&editedFile);

	while (true) {
		wSize = get_window_size();

		/* widnow size changed - print everthing again to adjust to new width */
		if (NOT(are_coords_equal(&oldSize, &wSize))) {
			copy_coord(&wSize, &oldSize);
			clear_cmd();
			display_header(&wSize);
			display_footer(&wSize);
			gotoxy(0, 2);
			printf("%s", editedFile.content);
		}

		/* catching char if button was hit */
		if (_kbhit()) {
			c = _getch();
		}

		if (-32 == c) {
			/* fetch the second value of extended key (arrows) */
			c = _getch();	
		}

		/* taking action depending on c value */
		switch (c) {

			/* crtl-x pressed - exit */
			case CTRL_KEYPRESS('x'):
				save_edited_file(&editedFile);
				clear_cmd();
				return 0;
			
			/* nothing pressed - continue */
			case NULL_CHAR:
				break;

			/* Enter hit - put new line */
			case ENTER_ASCII_VALUE:
				put_char_at_cursor_position(&editedFile, NEW_LINE);
				break;

			case LEFT_ASCII_VALUE:
				shift_cursor_position_left(&editedFile);
				break;

			case RIGHT_ASCII_VALUE:
				shift_cursor_position_right(&editedFile);
				break;

			case UP_ASCII_VALUE:
				shift_cursor_position_up(&editedFile);
				break;

			case DOWN_ASCII_VALUE:
				shift_cursor_position_down(&editedFile);
				break;

			//case BACKSPACE_ASCII_VALUE:
			//	break;

			/* typing - put char to screen */
			default:
				put_char_at_cursor_position(&editedFile, c);
				break;
		}

		if (NULL_CHAR != c) {
			c = NULL_CHAR;
		}
			
	}
	
	return 0;
}
