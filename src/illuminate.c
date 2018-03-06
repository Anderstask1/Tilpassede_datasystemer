#include "channels.h"
#include "elev.h"
#include "io.h"
#include "controller.h"
#include "door.h"
#include "stop.h"
#include "illuminate.h"

// Funksjonen er skrevet med &. Tanken er at den skal ta inn en referanse
void illuminate_lights(void){

  // elev_set_floor_indicator setter lyset for etasje.
  elev_set_floor_indicator(get_previous_floor_sensor_signal());


  // Overvåker etasjematrisen og slål av/på lysene i henhold til matrisen
  for (int current_floor = 0; current_floor < N_FLOORS; current_floor++) {

    // int get_up_down_floor(int floor, int direction)

    // Floor btn direction up
    if(current_floor < N_FLOORS-1) {
        if(get_up_down_floor(current_floor, 1)){
          elev_set_button_lamp(BUTTON_CALL_UP, current_floor, 1);
        } else {
          elev_set_button_lamp(BUTTON_CALL_UP, current_floor, 0);
        }
    }

    // Floor btn direction down
    if(current_floor > 0) {
        if(get_up_down_floor(current_floor, 0)){
          elev_set_button_lamp(BUTTON_CALL_DOWN, current_floor, 1);
        } else {
          elev_set_button_lamp(BUTTON_CALL_DOWN, current_floor, 0);
        }
    }

    // Elevator btn
    if(get_up_down_floor(current_floor, 0) && get_up_down_floor(current_floor, 1)){
      elev_set_button_lamp(BUTTON_COMMAND, current_floor, 1);
    } else {
      elev_set_button_lamp(BUTTON_COMMAND, current_floor, 0);
    }

    // Spesialtilfelle for nederste og øverste etasje.
    if (get_up_down_floor(0, 1)){
        elev_set_button_lamp(BUTTON_COMMAND, 0, 1);
    } else {
        elev_set_button_lamp(BUTTON_COMMAND, 0, 0);
    }

    if (get_up_down_floor(N_FLOORS-1,0)){
        elev_set_button_lamp(BUTTON_COMMAND, N_FLOORS-1, 1);
    } else {
        elev_set_button_lamp(BUTTON_COMMAND, N_FLOORS-1, 0);
    }
  }
}
