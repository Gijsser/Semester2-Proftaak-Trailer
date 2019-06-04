#include <Arduino.h>
#include <Servo.h>
#ifndef _SERVOCONTROL_H
#define _SERVOCONTROL_H

#define SERVO_PIN (12)

void attach_servo();
void servo_set_position(int position);

#endif
