#include <Arduino.h>
#include "Communication.h"
#include "trailerConnection.h"
#include "ServoControl.h"
#include "Sensors.h"
#ifndef _TRAILER_H
#define _TRAILER_H

typedef enum { NOK = 0, OK = 1 } Connection;

typedef enum { OFF = 0, SOUND = 1, ASSIST = 2 } TrailerState;

#define SERVO_CENTER (110)
#define SERVO_MIN (55)
#define SERVO_MAX (175)

Connection trailer_get_connection_status();
TrailerState trailer_get_trailer_state();
void trailer_check_message();
void trailer_check_distance();
void trailer_assist_steering();
void trailer_setup();

#endif
