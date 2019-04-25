#include <Arduino.h>
#include <SoftwareSerial.h>

#include "Communication.h"

SoftwareSerial Bluetooth(10,11);

void communication_start(){
  Bluetooth.begin(9600);
}

void communication_send_sensor(int sensor, int distance){
  char buffer[50]= "";
  switch (sensor) {
    case 0:
      sprintf(buffer, MESSAGE_START +"SENSOR_LEFT_STATUS:%d"  + MESSAGE_END, distance);
      Bluetooth.write(buffer);
      //Serial.write(buffer);
      return;
    case 1:
      sprintf(buffer,  MESSAGE_START + "SENSOR_MIDDLE_LEFT_STATUS:%d" + MESSAGE_END, distance);
      Bluetooth.write(buffer);
      //Serial.write(buffer);
      return;
    case 2:
      sprintf(buffer,  MESSAGE_START + "SENSOR_MIDDLE_RIGHT_STATUS:%d"  + MESSAGE_END, distance);
      Bluetooth.write(buffer);
      //Serial.write(buffer);
      return;
    case 3:
      sprintf(buffer, MESSAGE_START +"SENSOR_RIGHT_STATUS:%d" + MESSAGE_END, distance);
      Bluetooth.write(buffer);
      //Serial.write(buffer);
      return;
    }
}

void parse_message(String unparsed, String *Parsed, int size){ //kijken bij watch.c
  String parsed;

  for (uint8_t i = 1; i < unparsed.length(); i++) {
    parsed = parsed + unparsed[i];
  }

  int delimiterIndex = parsed.indexOf(DELIMITER); // als mid-marker

  if (delimiterIndex > 0) {
    Parsed[0] = parsed.substring(0, delimiterIndex);
    Parsed[1] = parsed.substring(delimiterIndex + 1, (parsed.length()));
    Serial.println(Parsed[1]);
  } else {
    Parsed[0] = parsed;
  }
}

void communication_recieve_message(){
  if(Bluetooth.available > 0){
    communication_read_message(Bluetooth.readStringUntil(DELIMITER));
  }
}
void communication_read_message(String message){
  if(message[0] == MESSAGE_START){ // als start-marker
    char buffer[50]= "";
    String Parsed[2];

    parse_message(message, Parsed, 2);

    if (Parsed[0] == "TRAILER_ASSIST_ON") {
        //messages to receive

      }
    }
  }