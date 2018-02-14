#include "elev.h"
#include <stdio.h>


int main() {
    // Initialize hardware
    if (!elev_init()) {
        printf("Unable to initialize elevator hardware!\n");
        return 1;
    }

    printf("Press STOP button to stop elevator and exit program.\n");

    elev_set_motor_direction(DIRN_UP);

    while (1) {
        // Change direction when we reach top/bottom floor
        if (elev_get_floor_sensor_signal() == N_FLOORS - 1) {
            elev_set_motor_direction(DIRN_DOWN);
        } else if (elev_get_floor_sensor_signal() == 0) {
            elev_set_motor_direction(DIRN_UP);
        }

        // Stop elevator and exit program if the stop button is pressed
        if (elev_get_stop_signal()) {
            elev_set_motor_direction(DIRN_STOP);
            break;
        }
        //TEST, put up and down values in array
        int up_down_floor[N_FLOORS][2] = {0};
        for(int button = 0; button < N_BUTTONS; button++){
          for(int floor = 0; floor < N_FLOORS; floor++) {
            if(!((floor == N_FLOORS-1 && button == BUTTON_CALL_UP) || (floor == 0 && button == BUTTON_CALL_DOWN))) {//Impossible to call elevator up when on top, or call elevator down when on bottom
              if(button == BUTTON_CALL_DOWN && elev_get_button_signal(button,floor)) {
                up_down_floor[floor][0] = 1;
              }
              if(button == BUTTON_CALL_UP && elev_get_button_signal(button,floor)) {
                up_down_floor[floor][1] = 1;
              }
              if(button == BUTTON_COMMAND && elev_get_button_signal(button,floor)){
                if(floor == 1 || floor == 2 || floor == 3) {
                  up_down_floor[floor][0] = 1;
                }
                if(floor == 0 || floor == 1 || floor == 2) {
                  up_down_floor[floor][1] = 1;
                }
              }
            }
          }
        }

        for(int i = N_FLOORS-1; i >= 0; i--) {
            printf("%d", up_down_floor[i][0]);
            printf("%d\n", up_down_floor[i][1]);
          }
        printf("\n----------------\n",0);
    }
    return 0;
}
