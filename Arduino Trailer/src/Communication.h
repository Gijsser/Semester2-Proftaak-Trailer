#include <Arduino.h>
#include <SoftwareSerial.h>
#ifndef _COMMUNICATION_H
#define _COMMUNICATION_H

#define MESSAGE_START ('#')
#define MESSAGE_END (';')
#define DELIMITER (':')

typedef enum { WAITING_FOR_MESSAGE, READING_MESSAGE, WAITING_FOR_ACKNOWLEDGE } ComState;

int communication_read_message(String * incomingMessage);
void communication_parse_message(String *Parsed, String * incomingMessage );
void comminucation_bluettooth_start();
void communication_send_message(String message, int value =0);
ComState communication_get_state();
void communication_set_state(ComState state);

#endif
