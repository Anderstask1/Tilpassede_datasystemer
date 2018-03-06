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

//function that controll the movement of the elevator, and controll the orders
void controll_elevator_orders(void);

//put values in up_down_floor matrix, watching buttons
void watch_buttons(void);

//print matrix for debugging
void print_up_down_floor_values(void);
