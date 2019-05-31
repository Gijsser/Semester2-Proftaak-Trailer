#include "Sensors.h"

int triggerPins[] = {2, 4, 6, 8};
int echoPins[] = {3, 5, 7, 9};

int update_sensors(int sensor) {
    digitalWrite(triggerPins[sensor], LOW);

    delayMicroseconds(2);

    digitalWrite(triggerPins[sensor], HIGH);

    delayMicroseconds(10);

    digitalWrite(triggerPins[sensor], LOW);

    int distanceValue = pulseIn(echoPins[sensor], HIGH);

    distanceValue = distanceValue * 0.034 / 2;

    return distanceValue;
}
