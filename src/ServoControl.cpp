
#include "ServoControl.h"

Servo ServoSteering;

void servo_set_position(int position){
  ServoSteering.attach(SERVO_PIN);
  ServoSteering.write(position);
}
