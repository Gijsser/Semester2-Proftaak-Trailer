#ifndef _TRAILER_H
#define _TRAILER_H

enum State {
Sound = 0,
Assist = 1
};


void trailer_set_state(State state);
State trailer_get_state();
void trailer_check_message();
void trailer_set_distance(int sensor, int distance);


#endif
