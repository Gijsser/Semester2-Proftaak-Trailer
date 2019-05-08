#include <Arduino.h>

#ifndef _COMMUNICATION_H
#define _COMMUNICATION_H

#define MESSAGE_START ('\x05\x02\x01\x01')
#define MESSAGE_END ('\x03\x04')
#define DELIMITER (':')

typedef enum { WAITING_FOR_MESSAGE, READING_MESSAGE } ComState;

int communication_read_message();
void communication_send_sensor(int sensor, int distance);
void communication_parse_message(String *Parsed, int size );
void comminucation_bluettooth_start();
void communication_send_acknowlegde();

#endif
