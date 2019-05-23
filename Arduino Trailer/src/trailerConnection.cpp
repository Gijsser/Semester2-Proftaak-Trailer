#include "trailerConnection.h"
#include "Communication.h"
#include <Arduino.h>

int previousstate = false;
unsigned long pretime = 0;
unsigned int debounce = 200;

ConnectionState trailerConnectionToVehicle = NOTCONNECTED;

void trailerConnection_setup() {
  pinMode(CONNECTIONLOOP, INPUT);
}

bool trailerConnection_Get_ConnectionState(){
  return trailerConnectionToVehicle;
}

void trailerConnection_Update_Connection() {
  int buttonstate = digitalRead(CONNECTIONLOOP);

  if((buttonstate!= previousstate) && ((millis() - pretime) > debounce)) {
    previousstate = buttonstate;
    pretime = millis();
    trailerConnectionToVehicle = buttonstate;
    communication_send_message("TRAILER_CONECTION",buttonstate);
    Serial.print("new trailerConnection = ");Serial.println(buttonstate);
  }
}
