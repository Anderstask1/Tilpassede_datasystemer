#include "stop.h"
#include "channels.h"
#include "elev.h"
#include "io.h"
#include "controller.c"

void stop_signal_status(void) {
	if !elev_get_stop_signal() {
		elev_set_stop_lamp(0);
	}
	else {
		if (elev_get_floor_sensor_signal() != -1) {
			open_door();
		}
		while (elev_get_stop_signal()) {
			elev_set_stop_lamp(1);
			elev_set_motor_direction(DIRN_STOP);
			reset_orders();
					}
		open_door_timer();
				}
			}
		}
	}
	return 0;
}



void reset_orders() {  //Legges i controller.c
	for (int i = 0; i < N_FLOORS; i++) {
		for (int j = 0; i < 2, i++) {
			if ((i != 0 && j != 0) && (i != (N_FLOORS - 1) && j != 1)) {
				up_down_floor[i][j] == 0;
			}
		}
	}
}


void open_door(); 
void open_door_timer();