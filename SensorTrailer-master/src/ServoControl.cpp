#include <Arduino.h>
#include <Servo.h>

#include "ServoControl.h"

Servo ServoSteering;

void attach_servo(){
  ServoSteering.attach(4);
}

void servo_set_position(int position){
  int val = map(position, 0, 1023, 0, 180);
  ServoSteering.write(val);
}
