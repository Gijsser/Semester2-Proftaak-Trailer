#include "Communication.h"

SoftwareSerial Bluetooth(10, 11);

ComState ComStatus = WAITING_FOR_MESSAGE;

void comminucation_bluettooth_start(){  Bluetooth.begin(9600); }
void communication_set_state(ComState state){  ComStatus = state; }
ComState communication_get_state(){ return ComStatus; }

int communication_read_message(String * incomingMessage) {
  if (Bluetooth.available() > 0) {
    //Serial.println("Bluetooth available");
    int incomingByte = Bluetooth.read();
    if (ComStatus == WAITING_FOR_MESSAGE) {
      if (incomingByte == MESSAGE_START) {
        //Serial.println("Starting read");
        ComStatus = READING_MESSAGE;
        *incomingMessage = "";
        return 0;
      }
    }
    if (ComStatus == READING_MESSAGE) {
      if (incomingByte == MESSAGE_END) {
        ComStatus = WAITING_FOR_MESSAGE;
        //Serial.println("end of message");
        return 1;
      } else {
        *incomingMessage += (char)incomingByte;
        //Serial.println("adding to message");
        //Serial.println(*incomingMessage);
        return 0;
      }
    }
  }
  return 0;
}

void communication_send_message(String message, int value){
  char buffer[50] = "";
  sprintf(buffer, "%c%s:%i%c", MESSAGE_START, message.c_str(), value, MESSAGE_END);
  Bluetooth.write(buffer);
  Serial.println("Sending message");
}

void communication_parse_message (String *Parsed, String * incomingMessage) { // kijken bij watch.c
  String toParse = *incomingMessage;

  int delimiterIndex = toParse.indexOf(DELIMITER); // als mid-marker

  if (delimiterIndex > 0) {
    Parsed[0] = toParse.substring(0, delimiterIndex);
    Parsed[1] = toParse.substring(delimiterIndex + 1, (toParse.length()));
    Serial.println(Parsed[1]);
  } else {
    Parsed[0] = toParse;
  }
}
