 #include "Sensors.h"
#include <NewPing.h>


#define SENSOR_NUMBER      2
#define MAX_DISTANCE 200
#define PING_INTERVAL 33

int cm[SENSOR_NUMBER];

int currentSensor;

NewPing Sensors[SENSOR_NUMBER] = {
  NewPing(4, 2, MAX_DISTANCE),
  NewPing(5, 3, MAX_DISTANCE)
};

void sensor_update_values(int * value, int currentsensor){
  *value = cm[currentsensor];
}

void echo_check_result() {
  if (Sensors[currentSensor].check_timer()) {
    cm[currentSensor] = Sensors[currentSensor].ping_result / US_ROUNDTRIP_CM;
  }
}

void update_sensors(int currentsensor){
      Sensors[currentSensor].timer_stop();
      currentSensor = currentsensor;
      cm[currentSensor] = 0;
      Sensors[currentSensor].ping_timer(echo_check_result);
}











// DistanceSensor *DistanceSensor::sensorInstance(NULL);
//
// DistanceSensor::DistanceSensor(int trigger, int echo, int interrupt)
//     : trigger(trigger), echo(echo), interrupt(interrupt), isFinished(false)
// {
//   if(sensorInstance==0) sensorInstance=this;
// }
//
// void DistanceSensor::sensor_begin(){
//   pinMode(trigger, OUTPUT);
//   digitalWrite(trigger, LOW);
//   pinMode(echo, INPUT);
//   attachInterrupt(interrupt, sensor_echo_trigger, CHANGE);
// }
//
// void DistanceSensor::sensor_start(){
//   isFinished = false;
//   digitalWrite(trigger, HIGH);
//   delayMicroseconds(10);
//   digitalWrite(trigger, LOW);
// }
//
// unsigned int DistanceSensor::sensor_get_value(){
//   return (endRead-startRead)/58;//((units)?58:148);
// }
//
// void DistanceSensor::sensor_echo_trigger(){
//   DistanceSensor* currentSensor = DistanceSensor::instance();
//   Serial.println("interupt echo");
//   switch(digitalRead(currentSensor->echo)){
//     case HIGH:
//       currentSensor->startRead=micros();
//       break;
//     case LOW:
//       currentSensor->endRead=micros();
//       currentSensor->isFinished=true;
//       break;
//   }
// }

// int update_sensors(int sensor) {
  //     static unsigned long hallos = millis();
  //     hallos = millis();
  //     digitalWrite(triggerPins[sensor], LOW);
  //
  //     delayMicroseconds(2);
  //
  //     digitalWrite(triggerPins[sensor], HIGH);
  //
  //     delayMicroseconds(10);
  //
  //     digitalWrite(triggerPins[sensor], LOW);
  //
  //     int distanceValue = pulseIn(echoPins[sensor], HIGH,5000);
  //
  //       distanceValue = distanceValue * 0.034 / 2;
  //
  //       Serial.print("sensor time = ");
  //       Serial.println(millis()-hallos);
  //     return distanceValue;
  //       //return 0;
  //
  // }
