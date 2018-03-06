#include <stdio.h>

#include "elev.h"
#include "io.h"
#include "channels.h"
#include "illuminate.h"
#include "controller.h"


int main() {
    // Initialize hardware
    if (!elev_init()) {
        printf("Unable to initialize elevator hardware!\n");
        return 1;
    }

    printf("Press STOP button to stop elevator and exit program.\n");

    elev_set_motor_direction(DIRN_UP);

    //counter i
    int counter = 0;
    while (1) {

      //counter while debug
      counter++;

      //print i for debugging
      //printf("While number %d\n", counter);

      illuminate_lights();

      watch_buttons();

      print_up_down_floor_values();

        // Change direction when we reach top/bottom floor
        if (elev_get_floor_sensor_signal() == N_FLOORS - 1) {
            elev_set_motor_direction(DIRN_DOWN);
        } else if (elev_get_floor_sensor_signal() == 0) {
            elev_set_motor_direction(DIRN_UP);
        }

        // Stop elevator and exit program if the stop button is pressed
        // The stop button is a little bit unstable. Some times it stops the program instantaneously
        if (elev_get_stop_signal()) {
            elev_set_motor_direction(DIRN_STOP);
            break;
        }

        watch_buttons();

        //print matrix for debugging
        print_up_down_floor_values();
    }
    return 0;
}
