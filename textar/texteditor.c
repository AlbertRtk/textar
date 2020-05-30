#include "texteditor.h"
#include "common.h"
#include "display.h"
#include "cmdcs.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


static int force_cursor_position_within_range(int posn, int min, int max);


static int previous_new_line_position(EditedFile *file);


void init_file(EditedFile *file) {
	file->name = (char*)malloc(1);
	file->name = (char*)realloc(file->name, 13);
	strcpy_s(file->name, 13, "New file.txt");

	file->content = (char*)malloc(1);
	file->content[0] = NULL_CHAR;

	file->cursorPosition = 0;
}


void put_char_into_string_at_position(char **text, char c, int posn) {
	int i;
	int newLen;
	char newChar[2] = { c, NULL_CHAR };

	/* get text new length, +2 = +1 because '\0' is not counted and +1 for new char*/
	newLen = strlen(*text) + 2;

	/* memory for text realloc */
	*text = (char *)realloc(*text, newLen);	// MEMORY LEAK ??

	/* from the end of string down to the posn move characters one position up */
	for (i = newLen; i > posn; i--) {
		(*text)[i] = (*text)[i - 1];
	}
	/* at position posn place new character c */
	(*text)[posn] = c;
}


void put_char_at_cursor_position(EditedFile *file, char c) {
	int i;
	int textLen;

	/* put char into text */
	put_char_into_string_at_position(&file->content, c, file->cursorPosition);
	putchar(c);

	/* shift cursor position */
	file->cursorPosition++;

	textLen = strlen(file->content);

	/* cursor position is not in the end of text - re-print characters after cursor */
	if (textLen != file->cursorPosition) {
		COORD consolCursorPosn;

		/* remember cursor position*/
		consolCursorPosn = get_console_cursor_position();

		/* re-print end of string */
		for (i = file->cursorPosition; i < textLen; i++) {
			putchar(file->content[i]);
		}

		/* restore cursor position */
		goto_coord(&consolCursorPosn);
	}
}


void shift_cursor_position_by_unit_value(EditedFile *file, Shift shift) {
	int oldPosition;	// current cursor position
	int newPosition;	// cursor position after shift
	int minPosition;	// min value for cursor position
	int maxPosition;	// max value for cursor position

	oldPosition = file->cursorPosition;
	newPosition = file->cursorPosition + shift;
	minPosition = 0;
	maxPosition = strlen(file->content);

	file->cursorPosition = force_cursor_position_within_range(newPosition, minPosition, maxPosition);

	/* cursor position changed - move cursor on the screan */
	if (oldPosition != file->cursorPosition) {
		COORD consolCursorPosn;
		COORD consoleSize;
		int tempPositionX;

		consolCursorPosn = get_console_cursor_position();
		consoleSize = get_window_size();
		
		/* end of line and shifting right - jump to next line*/
		if (SHIFT_RIGHT == shift && (NEW_LINE == file->content[file->cursorPosition - 1] || consoleSize.X - 1 == consolCursorPosn.X)) {
			consolCursorPosn.X = 0;
			consolCursorPosn.Y += shift;
		}
		/* beginning of line and shifting left - jump to previous line */
		else if (SHIFT_LEFT == shift && (NEW_LINE == file->content[file->cursorPosition] || 0 == consolCursorPosn.X)) {
			/* calculate cursore position in relation to previous new line */
			tempPositionX = previous_new_line_position(file);

			if (tempPositionX) {
				/* new line sign found */
				tempPositionX = file->cursorPosition - tempPositionX - 1;
			}
			else {
				/* no new line - refere to beginnign of string */
				tempPositionX = file->cursorPosition;
			}
			
			/* on the screen lines are wrapped - calculate position of last line end in the console */
			consolCursorPosn.X = tempPositionX % consoleSize.X;
			consolCursorPosn.Y += shift;
		}
		/* shift within line */
		else {
			consolCursorPosn.X += shift;
		}
		
		goto_coord(&consolCursorPosn);
	}
}


void shift_cursor_position_left(EditedFile *file) {
	shift_cursor_position_by_unit_value(file, SHIFT_LEFT);
}


void shift_cursor_position_right(EditedFile *file) {
	shift_cursor_position_by_unit_value(file, SHIFT_RIGHT);
}



void shift_cursor_position_up(EditedFile *file) {

}


void shift_cursor_position_down(EditedFile *file) {

}


static int force_cursor_position_within_range(int posn, int min, int max) {
	int output;

	if (posn < min) {
		output = min;
	}
	else if (posn > max) {
		output = max;
	}
	else {
		output = posn;
	}

	return output;
}


static int previous_new_line_position(EditedFile *file) {
	int i;
	i = file->cursorPosition - 1;

	while (i > 0 && NEW_LINE != file->content[i]) {
		i--;
	}

	return i;
}


void save_edited_file(EditedFile *file) {
	FILE *f;
	errno_t err;
	
	err = fopen_s(&f, file->name, "w");

	if (err) {
		/* cmd shouldn't be cleaned here and program shouldn't close - handle error differently */
		clear_cmd();
		printf("Error while saving file. Cannot open.\n");
		exit(1);
	}
	else {
		fprintf(f, file->content);
	}
	
	if (f) {
		err = fclose(f);

		if (err) {
			/* cmd shouldn't be cleaned here and program shouldn't close - handle error differently */
			clear_cmd();
			printf("Error while saving file. Cannot close.\n");
			exit(1);
		}
	}
}
