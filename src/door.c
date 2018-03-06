#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "channels.h"
#include "elev.h"
#include "io.h"
#include "controller.h"
#include "door.h"
#include "stop.h"
#include "illuminate.h"

//åpner døren i 3 sek
void open_door_timer(void) {
	clock_t start_t, current_t;
	start_t = clock();
	int msec = 0, trigger = 3; // 3ms

	do {
		io_set_bit(LIGHT_DOOR_OPEN);

		current_t = clock() - start_t;
		msec = current_t * 1000 / CLOCKS_PER_SEC;
	} while (msec < trigger);
	io_clear_bit(LIGHT_DOOR_OPEN);
}
