#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H


typedef struct Textfile_T {
	char *name;
	char *text;
} Textfile;


void init_textfile(Textfile *file);


void putchar_to_text_at_position(char **text, char c, int posn);

#endif
