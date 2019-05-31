#include <Arduino.h>
#include <SoftwareSerial.h>
#ifndef _COMMUNICATION_H
#define _COMMUNICATION_H

#define MESSAGE_START ('#')
#define MESSAGE_END (';')
#define DELIMITER (':')

typedef enum { WAITING_FOR_MESSAGE, READING_MESSAGE } ComState;

int communication_read_message();
void communication_parse_message(String *Parsed, int size );
void comminucation_bluettooth_start();
void communication_send_message(String message, int value =0);

#endif
