#include <Arduino.h>
#ifndef _SENSORS_H
#define _SENSORS_H

//int update_sensors(int sensor);
void start_sensors();

class DistanceSensor{
public:
  DistanceSensor(int triggerPin, int echoPin, int interruptPin);

  void sensor_begin();
  void sensor_start();
  bool sensor_is_finished(){ return isFinished; }
  unsigned int sensor_get_value();
  static DistanceSensor* instance(){ return sensorInstance; }

private:
 static void sensor_echo_trigger();

 int trigger, echo, interrupt;
 volatile unsigned long startRead, endRead;
 volatile bool isFinished;
 static DistanceSensor* sensorInstance;
};

#endif
