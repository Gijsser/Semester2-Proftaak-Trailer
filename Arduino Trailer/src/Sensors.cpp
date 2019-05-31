#include "Sensors.h"

int triggerPins[] = {2, 4, 6, 8};
int echoPins[] = {3, 5, 7, 9};
int update_sensors(int sensor) {
    static unsigned long hallos = millis();
    hallos = millis();
    digitalWrite(triggerPins[sensor], LOW);

    delayMicroseconds(2);

    digitalWrite(triggerPins[sensor], HIGH);

    delayMicroseconds(10);

    digitalWrite(triggerPins[sensor], LOW);

    int distanceValue = pulseIn(echoPins[sensor], HIGH,5000);

      distanceValue = distanceValue * 0.034 / 2;

      Serial.print("sensor time = ");
      Serial.println(millis()-hallos);
    return distanceValue;
      //return 0;

}
unsigned long read_pulse(int pin)
{
    static unsigned long rising_time;  // time of the rising edge
    static int last_state;             // previous pin state
    int state = digitalRead(pin);      // current pin state
    unsigned long pulse_length = 0;    // default return value

    // On rising edge: record current time.
    if (last_state == LOW && state == HIGH) {
        rising_time = micros();
    }

    // On falling edge: report pulse length.
    if (last_state == HIGH && state == LOW) {
        unsigned long falling_time = micros();
        pulse_length = falling_time - rising_time;
    }

    last_state = state;
    return pulse_length;
}
