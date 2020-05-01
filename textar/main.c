#include <stdio.h>
#include <windows.h>


/* Returns size of console window as number of columns (characters in row) and rows */
COORD get_window_size();

void gotoxy(int x, int y);


int main(int argc, char *argv[]) {
	COORD wSize;
	int oldWidth = 0;
	int i;

	/* clear console after start */
	system("@cls || clear");
	
	while (1) {
		wSize = get_window_size();

		/* window width reduced - clear console to remove extra print of title / header */
		if (oldWidth > wSize.X) {
			system("@cls || clear");
		}

		/* widnow width changed - print everthing again to adjust to new width */
		if (oldWidth != wSize.X) {
			oldWidth = wSize.X;
			gotoxy(0, 0);
			for (i = 0; i < wSize.X; i++) putchar('_');
			putchar('\n');
		}
	}
	
	return 0;
}


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
