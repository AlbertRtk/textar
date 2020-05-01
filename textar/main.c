#include <stdio.h>
#include <stdbool.h>
#include "cmdcs.h"
#include "common.h"


int main(int argc, char *argv[]) {
	COORD wSize;
	COORD oldSize;
	int i;
	
	oldSize.X = 0;
	oldSize.Y = 0;

	/* clear console after start */
	system("@cls || clear");
	
	while (true) {
		wSize = get_window_size();
		
		/* clear console to remove extra print of title, header, ... */
		clear_if_window_changed_size(&oldSize);

		/* widnow width changed - print everthing again to adjust to new width */
		if (NOT(are_coords_equal(&oldSize, &wSize))) {
			copy_coord(&wSize, &oldSize);
			goto_top_left();
			for (i = 0; i < wSize.X; i++) putchar('_');
			putchar('\n');
			goto_bottom_left();
			putchar('C');
		}
	}
	
	return 0;
}

