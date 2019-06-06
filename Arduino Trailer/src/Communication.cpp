#include "Communication.h"

SoftwareSerial Bluetooth(10, 11);

ComState ComStatus = WAITING_FOR_MESSAGE;

void comminucation_bluettooth_start(){  Bluetooth.begin(9600); }
void communication_set_state(ComState state){  ComStatus = state; }
ComState communication_get_state(){ return ComStatus; }



int communication_read_message(String* incomingMessage) {

  int returnval = 0;

  while(Bluetooth.available() > 0) {

    int incomingByte = Bluetooth.read();

    switch(ComStatus) {
      case WAITING_FOR_MESSAGE:
        if(incomingByte == MESSAGE_START) {
          ComStatus = READING_MESSAGE;
          *incomingMessage = "";
        }
      break;
      case READING_MESSAGE:
        if(incomingByte == MESSAGE_END) {
          ComStatus = WAITING_FOR_MESSAGE;
          returnval = 1;

        } else {
         *incomingMessage += (char)incomingByte;
        }
      break;
    }
  }

  return returnval;
}

void communication_send_message(String message, int value){
  char buffer[50] = "";
  sprintf(buffer, "%c%s:%i%c", MESSAGE_START, message.c_str(), value, MESSAGE_END);
  Bluetooth.write(buffer);
  Serial.println("Sending message");
  Serial.println(buffer);
}

void communication_parse_message (String *Parsed, String * incomingMessage) { // kijken bij watch.c
  String toParse = *incomingMessage;

  int delimiterIndex = 0;
  delimiterIndex = toParse.indexOf(DELIMITER); // als mid-marker

  if (delimiterIndex != 0) {
    Parsed[0] = toParse.substring(0, delimiterIndex);
    Parsed[1] = toParse.substring(delimiterIndex + 1, (toParse.length()));
    Serial.println(Parsed[1]);
  } else {
    Parsed[0] = toParse;
  }
}
