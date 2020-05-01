#include <stdio.h>
#include "display.h"
#include "cmdcs.h"
#include "common.h"


/* Print horizontal separator at full width of cmd window */
static void print_horizontal_separator(const short width);


static void print_horizontal_separator(const short width) {
	int i;
	for (i = 0; i < width; i++) putchar('_');
}


void clear_cmd() {
	system("@cls || clear");
}


void display_header(const COORD *wSize) {
	goto_top_left();
	printf("New file\n");
	print_horizontal_separator(wSize->X);
}


void display_footer(const COORD *wSize) {
	gotoxy(0, wSize->Y - 2);
	print_horizontal_separator(wSize->X);
	goto_bottom_left();
	printf("crtl-x: Exit | ");
}


