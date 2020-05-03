#include "texteditor.h"
#include "common.h"
#include "display.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


void init_textfile(Textfile *file) {

	file->name = (char*)malloc(1);
	file->name = (char*)realloc(file->name, 13);
	strcpy_s(file->name, 13, "New file.txt");

	file->text = (char*)malloc(1);
	file->text[0] = NULL_CHAR;

	file->cursorPosition = 0;
}


void put_char_to_text_at_position(char **text, char c, int posn) {
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


void put_char_to_textfile_at_cursor_position(Textfile *file, char c) {
	/* put char into text */
	put_char_to_text_at_position(&file->text, c, file->cursorPosition);

	/* shift cursor to the end of string / text */
	file->cursorPosition++;
}


void save_textfile(Textfile *file) {
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
		fprintf(f, file->text);
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
