#include <Arduino.h>

#include "Sensors.h"
#include "Communication.h"

void setup(){
}

void loop(){
  update_sensors();
  communication_receive_message();
}
