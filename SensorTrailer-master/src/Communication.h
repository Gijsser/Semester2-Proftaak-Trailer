#ifndef _COMMUNICATION_H
#define _COMMUNICATION_H

#define MESSAGE_START ('\x05\x02\x01\x01')
#define MESSAGE_END ('\x03\x04')
#define DELIMITER (':')

SoftwareSerial Bluetooth(10,11);

void communication_send_sensor(int sensor, int distance);
void communication_start();
void communication_receive_message();
void communication_read_message(String message);
void parse_message(String unparsed, String (*Parsed)[2] );
#endif
