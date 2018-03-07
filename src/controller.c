#include "channels.h"
#include "elev.h"
#include "io.h"
#include "controller.h"
#include "illuminate.h"


#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

//initialize the elevator
void initialize_elevator(void) {
  reset_orders();
  while(elev_get_floor_sensor_signal() == -1) {
    set_motor_direction(DIRN_DOWN);
  }
  set_motor_direction(DIRN_STOP);
}

//declare pointer to array of orders
static int up_down_floor[N_FLOORS][2];
static int previous_floor_sensor_signal = 0;
static elev_motor_direction_t motor_direction = DIRN_STOP;
static int current_motor_direction = 0;


// Get function
int get_previous_floor_sensor_signal(void){
  assert(previous_floor_sensor_signal >= 0);
  assert(previous_floor_sensor_signal < N_FLOORS);
  return previous_floor_sensor_signal;
}

//set values to array of orders
void button_read(){
  for(int button = 0; button < N_BUTTONS; button++){
    for(int floor = 0; floor < N_FLOORS; floor++) {
      if(!((floor == N_FLOORS-1 && button == BUTTON_CALL_UP) || (floor == 0 && button == BUTTON_CALL_DOWN))) {
        //Impossible to call elevator up when on top, or call elevator down when on bottom
        if(button == BUTTON_CALL_DOWN && elev_get_button_signal(button,floor)) {
          up_down_floor[floor][0] = 1;
        }
    while (elev_get_stop_signal()) {
  		elev_set_stop_lamp(1);
          if (elev_get_floor_sensor_signal() != -1) {
  			open_door_timer();
  		}
  		elev_set_motor_direction(DIRN_STOP);
  		reset_orders();
  	}
      if (!elev_get_stop_signal()) {
  		elev_set_stop_lamp(0);
  	}    if(button == BUTTON_CALL_UP && elev_get_button_signal(button,floor)) {
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

int get_up_down_floor(int floor, int direction){
  return up_down_floor[floor][direction];
}

elev_motor_direction_t get_motor_direction(void) {
  return motor_direction;
}

void set_motor_direction(elev_motor_direction_t dirn) {
  elev_set_motor_direction(dirn);
  current_motor_direction = dirn;
}

void set_previous_floor_sensor_signal(void) {
  int temp = elev_get_floor_sensor_signal();
  if(temp != -1) {
    previous_floor_sensor_signal = temp;
  }
}

//print matrix for debugging#include "door.h"
void print_up_down_floor_values(void) {
  for(int i = N_FLOORS-1; i >= 0; i--) {
      printf("%d", up_down_floor[i][0]);
      printf("%d\n", up_down_floor[i][1]);
    }
  printf("\n----------------\n");
}

void watch_buttons(void) {
    set_previous_floor_sensor_signal();
    for(int button = 0; button < N_BUTTONS; button++){
        for(int floor = 0; floor < N_FLOORS; floor++) {
          //Impossible to call elevator up when on top, or call elevator down when on bottom
          if(!((floor == N_FLOORS-1 && button == BUTTON_CALL_UP) || (floor == 0 && button == BUTTON_CALL_DOWN))) {
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

//reset current floor in up_down_floor matrix
void clear_current_floor(int current_floor){
    up_down_floor[current_floor][0] = 0;
    up_down_floor[current_floor][1] = 0;
}

//reset entire up_down_floor matrix
void reset_orders(void) {
	for (int i = 0; i < N_FLOORS; i++) {
		clear_current_floor(i);
	}
}

//stopper heisen når stoppknappen er inne, og åpner dørene hvis den er i en etasje
void stop_signal_status(void) {
  if(elev_get_stop_signal()) {
  	while (elev_get_stop_signal()) {
  		elev_set_stop_lamp(1);
          if (elev_get_floor_sensor_signal() != -1) {
  			open_door_timer();
  		}
  		elev_set_motor_direction(DIRN_STOP);
  		reset_orders();
  	}
      if (!elev_get_stop_signal()) {
  		elev_set_stop_lamp(0);
  	}
}
}

//åpner døren i 3 sek

void open_door_timer(void) {
    set_motor_direction(DIRN_STOP);
	clock_t start_t, current_t;
	start_t = clock();
	int msec = 0, trigger = 3000; // 3ms
	do {
        stop_signal_status();
        watch_buttons();
        illuminate_lights();
		elev_set_door_open_lamp(1);
		current_t = clock() - start_t;
		msec = current_t * 1000 / CLOCKS_PER_SEC;
	} while (msec < trigger);
	elev_set_door_open_lamp(0);
}

/*;
void open_door_timer(void){
    set_motor_direction(DIRN_STOP);
    elev_set_door_open_lamp(1);
    delay(3000);
    elev_set_door_open_lamp(0);
}
*/

//function that controll the movement of the elevator, and controll the orders
void controll_elevator_orders(void) {
    watch_buttons();
    print_up_down_floor_values();
  int comming_orders = 0;
  motor_direction = current_motor_direction;
  if ((motor_direction == DIRN_UP || motor_direction == DIRN_STOP)) {
    for (int i = previous_floor_sensor_signal; i < N_FLOORS; i++) {
      if((elev_get_floor_sensor_signal() != -1) && up_down_floor[elev_get_floor_sensor_signal()][1]) {
        clear_current_floor(elev_get_floor_sensor_signal());
        open_door_timer();
      }
      if(up_down_floor[i][1]) {
        set_motor_direction(DIRN_UP);
        // Hvis heisen er på grensen til ny etasje så skal den ikke snu.
        comming_orders = 1;
      }
    }

    for(int i = N_FLOORS-1; i > previous_floor_sensor_signal && !comming_orders; i--) {
        if((elev_get_floor_sensor_signal() != -1) && up_down_floor[elev_get_floor_sensor_signal()][0] && elev_get_floor_sensor_signal() == i) {
            clear_current_floor(elev_get_floor_sensor_signal());
            open_door_timer();
        }
        if(up_down_floor[i][0]) {
          set_motor_direction(DIRN_UP);
          comming_orders = 1;
          break;
          // Hvis heisen er på grensen til set_motor_direction(DIRN_STOP);ny etasje så skal den ikke snu
        }
    }
    if(!comming_orders) {
      motor_direction = DIRN_DOWN;
    }
  }
  if(motor_direction == DIRN_DOWN) {
    for(int i = previous_floor_sensor_signal; i >= 0; i--) {
      if((elev_get_floor_sensor_signal() != -1) && up_down_floor[elev_get_floor_sensor_signal()][0]) {
          clear_current_floor(elev_get_floor_sensor_signal());
          open_door_timer();
      }
      if(up_down_floor[i][0]) {
        set_motor_direction(DIRN_DOWN);
        // Hvis heisen er på grensen til ny etasje så skal den ikke snu.
        comming_orders = 1;
      }
    }
    for(int i = 0; i < previous_floor_sensor_signal && !comming_orders; i++) {
        if((elev_get_floor_sensor_signal() != -1) && up_down_floor[elev_get_floor_sensor_signal()][1] && elev_get_floor_sensor_signal() == i) {
            clear_current_floor(elev_get_floor_sensor_signal());
            open_door_timer();
        }
        if(up_down_floor[i][1]) {
          set_motor_direction(DIRN_DOWN);
          comming_orders = 1;
          break;
          // Hvis heisen er på grensen til ny etasje så skal den ikke snu.
        }
    }
  }
  if(elev_get_floor_sensor_signal() == 0 && !comming_orders){
      set_motor_direction(DIRN_STOP);
      clear_current_floor(elev_get_floor_sensor_signal());
      open_door_timer();
  }
  /*
  if(!comming_orders) {
      if(elev_get_floor_sensor_signal() != 0){
          set_motor_direction(DIRN_DOWN);
      }else{
          set_motor_direction(DIRN_STOP);
      }
  }
  */
}
