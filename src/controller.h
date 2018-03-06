//set values to array of orders
void button_read();

//get values from array get_up_down_floor
int get_up_down_floor();

//get values from value in pointer motor_direction
elev_motor_direction_t get_motor_direction(void);

//set value to dereferenced pointer motor_direction
void set_motor_direction(elev_motor_direction_t dirn);

//set value to variable previous_floor_sensor_signal
void set_previous_floor_sensor_signal(int previous_floor_sensor_signal);

//print matrix for debugging
void print_up_down_floor_values(void);

//put values in up_down_floor matrix, watching buttons
void watch_buttons(void);

//reset current floor in up_down_floor matrix
void clear_current_floor(int);

//reset entire up_down_floor matrix
void reset_orders(void);

//stopper heisen når stoppknappen er inne, og åpner dørene hvis den er i en etasje
void stop_signal_status(void);

//åpner døren i 3 sek
void open_door_timer(void);

//function that controll the movement of the elevator, and controll the orders
void controll_elevator_orders(void);

//delete orders in current floor
void clear_current_floor (int current_floor);
