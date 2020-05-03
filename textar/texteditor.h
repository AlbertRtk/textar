#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H


typedef struct Textfile_T {
	char *name;				// name of edited file
	char *text;				// content of edited file
	int cursorPosition;		// position of cursors in edited string (file content)
} Textfile;


void init_textfile(Textfile *file);


/* function puts character c into text at given position posn */
void put_char_to_text_at_position(char **text, char c, int posn);


/*  */
void put_char_to_textfile_at_cursor_position(Textfile *file, char c);



void save_textfile(Textfile *file);

#endif
