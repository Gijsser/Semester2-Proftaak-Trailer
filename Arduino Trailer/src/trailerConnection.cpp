#include "trailerConnection.h"
int CONNECTIONLOOP = 13;
ConnectionState trailerConnectionToVehicle = CONNECTED;

void trailerConnection_setup() {
  pinMode(13, INPUT);
}

bool trailerConnection_Get_ConnectionState(){
  return trailerConnectionToVehicle;
}


void trailerConnection_Update_Connection() {
  static bool previousstate;
  static unsigned long pretime;
  const unsigned int debounce = 500;
  int buttonstate = digitalRead(13);
  //Serial.print("new trailerConnection = ");Serial.println(buttonstate);
  if((buttonstate != previousstate) && ((millis() - pretime) > debounce)) {
    previousstate = buttonstate;
    pretime = millis();
    if(buttonstate == 1){
      trailerConnectionToVehicle = CONNECTED;
    }
    else{
      trailerConnectionToVehicle = NOTCONNECTED;
    }
    //communication_send_message("TRAILER_CONECTION",buttonstate);
    Serial.print("new trailerConnection = ");Serial.println(buttonstate);
  }
}
