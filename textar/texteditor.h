#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H


typedef struct EditedFile_T {
	char *name;				// name of edited file
	char *content;				// content of edited file
	int cursorPosition;		// position of cursors in edited string (file content)
} EditedFile;


void init_file(EditedFile *file);


/* function puts character c into text at given position posn */
void put_char_into_string_at_position(char **text, char c, int posn);


/* put a given character c into file content (string) at position of the cursor */
void put_char_into_file_content_at_cursor_position(EditedFile *file, char c);


/* shifts cursor position by given value */
void shift_cursor_position_by_value(EditedFile *file, int shift);


/* shifts cursor position one char to the left */
void shift_cursor_position_left(EditedFile *file);


/* shifts cursor position one char to the right */
void shift_cursor_position_right(EditedFile *file);


/*  */
void save_edited_file(EditedFile *file);

#endif
