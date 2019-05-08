#include <Arduino.h>
#include <Servo.h>

#include "ServoControl.h"

Servo ServoSteering;

void servo_set_position(int position){
    ServoSteering.attach(4);
  ServoSteering.write(position);
}
