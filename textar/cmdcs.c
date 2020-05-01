#include "cmdcs.h"


COORD get_window_size() {
	COORD wSize;
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	wSize.X = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	wSize.Y = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

	return wSize;
}


void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}


void goto_top_left() {
	gotoxy(0, 0);
}


void goto_bottom_left() {
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	gotoxy(0, csbi.srWindow.Bottom);
}


void clear_if_window_changed_size(const COORD *oldSize) {
	COORD sizeNow;

	sizeNow = get_window_size();

	if (oldSize->X != sizeNow.X || oldSize->Y != sizeNow.Y) {
		system("@cls || clear");
	}
}


bool are_coords_equal(const COORD *coord1, const COORD *coord2) {
	bool f_equal = false;

	if ((coord1->X == coord2->X) && (coord1->Y == coord2->Y)) {
		f_equal = true;
	}

	return f_equal;
}
