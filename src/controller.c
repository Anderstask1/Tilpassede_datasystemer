#include "channels.h"
#include "elev.h"
#include "io.h"

#include <assert.h>
#include <stdlib.h>

//declare pointer to array of orders
static int up_down_floor[N_FLOORS][2] = {0};
int (*up_down_floor_ptr)[N_FLOORS][2] = &up_down_floor;

static int *previous_floor_sensor_signal;
static elev_motor_direction_t *motor_direction = DIRN_STOP;

//set values to array of orders
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

int * get_up_down_floor(){
  return *up_down_floor;
}

elev_motor_direction_t get_motor_direction(void) {
  return motor_direction;
}

void set_motor_direction(elev_motor_direction_t dirn) {
  elev_set_motor_direction(dirn);
  *motor_direction = dirn;
}

void set_previous_floor_sensor_signal(int &previous_floor_sensor_signal) {
  int temp = elev_get_floor_sensor_signal();
  if(temp =! -1) {
    previous_floor_sensor_signal = temp;
  }
}

//print matrix
for(int i = N_FLOORS-1; i >= 0; i--) {
    printf("%d", up_down_floor[i][0]);
    printf("%d\n", up_down_floor[i][1]);
  }
printf("\n----------------\n",0);

void controll_elevator_orders(void) {
  bool comming_orders = 0;
  if (motor_direction == DIRN_UP && comming_orders) {
    for (int i = *previous_floor_sensor_signal; i < N_FLOORS; i++) {
      if(elev_get_floor_sensor_signal() == up_down_floor[i][1]) {
        //åpne dør 3 sek og null ordelisten i etasje i
      }
      if(up_down_floor[i][1]) {
        //kjør til etasje i
        comming_orders = 1;
      }
    }
    if(!comming_orders) {
      set_motor_direction(DIRN_DOWN);
    }
  }
  if(motor_direction == DIRN_DOWN) {

  }

}
