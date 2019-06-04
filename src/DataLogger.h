#include <Arduino.h>
#ifndef _DATALOGGER_H
#define _DATALOGGER_H

void datalog_log_sensor(String data);
void datalog_log_servo(String data);
void datalog_log_message(String data);

#endif
