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

    // Set motor direction at startup.
    elev_set_motor_direction(DIRN_STOP);

    while (1) {

      //print i for debugging
      //printf("While number %d\n", counter);
      watch_buttons();

      illuminate_lights();

      controll_elevator_orders();

      stop_signal_status();


        // Stop elevator and exit program if the stop button is pressed
        // The stop button is a little bit unstable. Some times it stops the program instantaneously
        if (elev_get_obstruction_signal()) {
            elev_set_motor_direction(DIRN_STOP);
            break;
        }

        //print matrix for debugging
        //print_up_down_floor_values();
    }
    return 0;
}
