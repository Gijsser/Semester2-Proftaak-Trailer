#include "trailerConnection.h"

ConnectionState trailerConnectionToVehicle = NOTCONNECTED;

void trailerConnection_setup() {
  pinMode(CONNECTIONLOOP, INPUT);
}

bool trailerConnection_Get_ConnectionState(){
  return trailerConnectionToVehicle;
}

void trailerConnection_Update_Connection() {
  static bool previousstate;
  static unsigned long pretime;
  const unsigned int debounce = 200;
  int buttonstate = digitalRead(CONNECTIONLOOP);

  if((buttonstate!= previousstate) && ((millis() - pretime) > debounce)) {
    previousstate = buttonstate;
    pretime = millis();
    trailerConnectionToVehicle = buttonstate;
    communication_send_message("TRAILER_CONECTION",buttonstate);
    Serial.print("new trailerConnection = ");Serial.println(buttonstate);
  }
}
