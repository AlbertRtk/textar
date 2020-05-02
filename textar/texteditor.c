#include "texteditor.h"
#include "common.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


void init_textfile(Textfile *file) {
	file->name = (char*)malloc(1);
	file->text = (char*)malloc(1);
	file->name[0] = NULL_CHAR;
	file->text[0] = NULL_CHAR;
}


void putchar_to_text_at_position(char **text, char c, int posn) {
	int i;
	int newLen;
	char newChar[2] = { c, NULL_CHAR };

	/* get text new length, +2 = +1 because '\0' is not counted and +1 for new char*/
	newLen = strlen(*text) + 2;

	/* memory for text realloc */
	*text = (char *)realloc(*text, newLen);
	
	/*  */
	strcat_s(*text, newLen, newChar);

	/*for (i = len; i > posn; i--) {
		*text[i] = *text[i - 1];
	}
	*text[posn] = c;*/
}
