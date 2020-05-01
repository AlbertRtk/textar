#include "display.h"
#include "cmdcs.h"
#include "common.h"


void clear_cmd() {
	system("@cls || clear");
}


void clear_if_window_changed_size(const COORD *oldSize) {
	COORD sizeNow;

	sizeNow = get_window_size();

	if (NOT(are_coords_equal(&sizeNow, oldSize))) {
		clear_cmd();
	}
}
