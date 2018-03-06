#include "door.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <stop.h>

open_door_timer() {
	clock_t start_t, current_t;
	start_t = clock();
	int msec = 0, trigger = 3; // 3ms

	do {
		io_set_bit(LIGHT_DOOR_OPEN);

		current_t = clock() - start_t;
		msec = current_t * 1000 / CLOCKS_PER_SEC;
		//iterations++;
	} while (msec < trigger);
	io_clear_bit(LIGHT_DOOR_OPEN);

}

/*open_door() {
	if (elev_get_floor_sensor_signal() != -1) {
		open_door_timer();
		//
	}
}
*/

