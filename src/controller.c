#include "channels.h"
#include "elev.h"
#include "io.h"

#include <assert.h>
#include <stdlib.h>

//TEST, put up and down values in array
static int up_down_floor[N_FLOORS][2] = {0};

void button_read(){
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
}

int get_up_down_floor(){
  return up_down_floor;
}

for(int i = N_FLOORS-1; i >= 0; i--) {
    printf("%d", up_down_floor[i][0]);
    printf("%d\n", up_down_floor[i][1]);
  }
printf("\n----------------\n",0);

int illuminate_lights(const int button_array[][], int lengt_button_array){
  for(){

  }
}
