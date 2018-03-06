#include "channels.h"
#include "elev.h"
#include "io.h"
#include "controller.h"
#include "illuminate.h"

// Funksjonen er skrevet med &. Tanken er at den skal ta inn en referanse
void illuminate_lights(int n_floors){

  for (int current_floor = 0; current_floor < n_floors; current_floor++) {

    // int get_up_down_floor(int floor, int direction)

    // Dirty fix. Vi kaller en posisjon i arraye som alltid vil være null i 4. og i 1. etg.

    // Floor btn direction up
    if((get_up_down_floor(current_floor, 1) && (current_floor < n_floors-1)){
      elev_set_button_lamp(BUTTON_CALL_UP, current_floor, 1);
    } else {
      elev_set_button_lamp(BUTTON_CALL_UP, current_floor, 0);
    }

    // Floor btn direction down
    if((get_up_down_floor(current_floor, 0) && (current_floor > 0)){
      elev_set_button_lamp(BUTTON_CALL_DOWN, current_floor, 1);
    } else {
      elev_set_button_lamp(BUTTON_CALL_DOWN, current_floor, 0);
    }

    // Elevator btn
    if((get_up_down_floor(current_floor, 0) && (get_up_down_floor(current_floor, 1)){
      elev_set_button_lamp(BUTTON_COMMAND, current_floor, 1);
    } else {
      elev_set_button_lamp(BUTTON_COMMAND, current_floor, 0);
    }

    // void elev_set_button_lamp(elev_button_type_t button, int floor, int value);
  }
}
