#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H


typedef struct Textfile_T {
	char *name;
	char *text;
} Textfile;


void init_textfile(Textfile *file);


/* function puts character c into text at given position posn */
/* AT THE MOMENT ONLY APPENDS IN THE END OF TEXT */
void putchar_to_text_at_position(char **text, char c, int posn);

#endif
