
#include "ServoControl.h"

Servo ServoSteering;

void servo_set_position(int position){
    ServoSteering.attach(12);
  ServoSteering.write(position);
}
