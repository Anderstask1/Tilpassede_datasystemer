#include "channels.h"
#include "elev.h"
#include "io.h"

#include <assert.h>
#include <stdlib.h>

//put up and down values in array
int up_down_floor[N_FLOORS][2];
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

for(int i = 0; i < N_FLOORS, i++) {
    printf("d", up_down_floor[i][0]);
    printf("d\n --------------- \n", up_down_floor[i][1]);
  }
}
