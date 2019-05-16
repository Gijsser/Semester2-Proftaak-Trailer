#include <Arduino.h>

#include "Communication.h"
#include "Trailer.h"
void setup() {
   Serial.begin(9600);
   comminucation_bluettooth_start();
  }

void loop() {
  if (trailer_get_connection_status() == OK) {
    Serial.println("Connection OK");
    switch (trailer_get_trailer_state()) {
    case OFF:
      trailer_check_message();
      break;
    case SOUND:
      trailer_check_message();
      trailer_check_distance();
      break;
    case ASSIST:
      trailer_check_message();
      //trailer_check_distance();
      //trailer_assist_steering();
      break;
    }
  } else if (trailer_get_connection_status() == NOK) {
    Serial.println("Connection NOK");
    trailer_check_message();
    trailer_assist_steering();

  }
}
