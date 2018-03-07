//initialize the elevator
void initialize_elevator(void);

//finite state machine function
void fsm(void);

//set values to array of orders
void button_read();

//get values from array get_up_down_floor
int get_up_down_floor();

//get values from value in pointer motor_direction
elev_motor_direction_t get_motor_direction(void);

//set value to dereferenced pointer motor_direction
void set_motor_direction(elev_motor_direction_t dirn);

//set value to variable previous_floor_sensor_signal
void set_previous_floor_sensor_signal(void);

//print matrix for debugging
void print_up_down_floor_values(void);

//put values in up_down_floor matrix, watching buttons
void watch_buttons(void);

//reset current floor in up_down_floor matrix
void clear_current_floor(int);

//reset entire up_down_floor matrix
void reset_orders(void);

//stopper heisen når stoppknappen er inne, og åpner dørene hvis den er i en etasje
int stop_signal_status(void);

//åpner døren i 3 sek
void open_door_timer(void);

//check if there is orders
int check_for_orders(void);

//controll the comming orders of elevator
elev_motor_direction_t order_handler(void);

//check if the elevator has arrived the floor ordered
int check_for_arrived(void);

//stop the elevator when arrived at ordered floor
int stop_handler(void);


//delete orders in current floor
void clear_current_floor (int current_floor);

// Get function for illiminate.c
int get_previous_floor_sensor_signal(void);
