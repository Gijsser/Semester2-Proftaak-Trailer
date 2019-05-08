#ifndef _TRAILER_H
#define _TRAILER_H

typedef enum { NOK = 0, OK = 1 } Connection;

typedef enum { OFF = 0, SOUND = 1, ASSIST = 2 } TrailerState;

#define SERVO_CENTER (90)
#define SERVO_MIN (20)
#define SERVO_MAX (160)

int trailer_get_connection_status();
int trailer_get_trailer_state();
int trailer_get_com_state();
void trailer_check_message();
void trailer_check_distance();
void trailer_assist_steering();

#endif
