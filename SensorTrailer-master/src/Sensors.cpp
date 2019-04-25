#include <Arduino.h>

#include "Sensors.h"
#include "Communication.h"

int numberOfSensors = 4;

int triggerPins[] = {2, 4, 6, 8};
int echoPins[] = {3, 5, 7, 9};
int distanceValue[] = {0,0,0,0};
int oldDistanceValue[] = {0, 0, 0, 0};

void update_sensors(){
    for(int i = 0; i < numberOfSensors; i++){
        digitalWrite(triggerPins[i], LOW);

        delayMicroseconds(2);

        digitalWrite(triggerPins[i], HIGH);

        delayMicroseconds(10);

        digitalWrite(triggerPins[i], LOW);

        distanceValue[i] = pulseIn(echoPins[i], HIGH);

        distanceValue[i] =  distanceValue[i] *0.034/2;


        if(distanceValue[i] != oldDistanceValue[i]){
            communication_send_sensor(i, distanceValue[i]);
            oldDistanceValue[i] = distanceValue[i];
        }
    }
}
