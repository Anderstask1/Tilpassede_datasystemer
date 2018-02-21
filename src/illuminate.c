#include "channels.h"
#include "elev.h"
#include "io.h"
#include "controller.c"

// Funksjonen er skrevet med &. Tanken er at den skal ta inn en referanse
int illuminate_lights(const int &button_array[][], const int n_floors){
  const int width = 2;



  for (int current_floor = 0; current_floor < n_floors; current_floor++) {


    // Floor btn direction up
    if((button_array[current_floor][0])&& (current_floor < n_floors-1)){
      elev_set_button_lamp(BUTTON_CALL_UP, current_floor, 1);
    } else {
      elev_set_button_lamp(BUTTON_CALL_UP, current_floor, 0);
    }

    // Floor btn direction down
    if((button_array[current_floor][1]) && (curront_floor > 0)){
      elev_set_button_lamp(BUTTON_CALL_DOWN, current_floor, 1);
    } else {
      elev_set_button_lamp(BUTTON_CALL_DOWN, current_floor, 0);
    }

    // Elevator btn
    if((button_array[current_floor][0]) && (button_array[current_floor][1])){
      elev_set_button_lamp(BUTTON_COMMAND, current_floor, 1);
    } else {
      elev_set_button_lamp(BUTTON_COMMAND, current_floor, 0);
    }

    // void elev_set_button_lamp(elev_button_type_t button, int floor, int value);
  }
}
