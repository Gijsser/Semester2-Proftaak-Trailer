#include <Arduino.h>

#include "Trailer.h"
#include "ServoControl.h"
#include "Communication.h"

int Distances[] = {0, 0, 0, 0};

State TrailerState = Sound;

State trailer_get_state(){
  return TrailerState;
}

void trailer_set_state(State state){
 TrailerState = state;
}

void trailer_set_distance(int sensor, int distance){
  Distances[sensor] = distance;
}

void trailer_check_message(){
  communication_check_available();
}
