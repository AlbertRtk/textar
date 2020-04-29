#include <stdio.h>
#include <windows.h>


typedef struct _WindowSize {
	unsigned short columns;
	unsigned short rows;
} WindowSize;


WindowSize get_window_size();


int main(int argc, char *argv[]) {
	WindowSize wSize;
	int i;
	
	while (1) {
		wSize = get_window_size();
		for (i = 0; i < wSize.columns; i++) putchar('_');
		getchar();
	}
	
	return 0;
}


WindowSize get_window_size() {
	WindowSize wSize;
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	wSize.columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	wSize.rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

	return wSize;
}