#include "Communication.h"

SoftwareSerial Bluetooth(10, 11);

ComState ComStatus = WAITING_FOR_MESSAGE;

String incomingMessage = "";

int communication_read_message() {
  if (Bluetooth.available() > 0) {
    Serial.println("Bluetooth available");
    int incomingByte = Bluetooth.read();
    if (ComStatus == WAITING_FOR_MESSAGE) {
      if (incomingByte == MESSAGE_START) {
        Serial.println("Starting read");
        ComStatus = READING_MESSAGE;
        incomingMessage = "";
        return 0;
      }
    }
    if (ComStatus == READING_MESSAGE) {
      if (incomingByte == MESSAGE_END) {
        ComStatus = WAITING_FOR_MESSAGE;
        Serial.println(incomingMessage);
        Serial.println("end of message");
        return 1;
      } else {
        incomingMessage += (char)incomingByte;
        Serial.println("adding to message");
        return 0;
      }
    }
  }
  return 0;
}

void communication_send_message(String message, int value = 0){
  char buffer[50] = "";
  sprintf(buffer, "%c%s:%i%c", MESSAGE_START, message.c_str(), value, MESSAGE_END);
  Bluetooth.write(buffer);
  Serial.println("Sending message");
}

void communication_parse_message (String *Parsed, int size) { // kijken bij watch.c
  // String parsed;
  //
  // for (uint8_t i = 0; i < incomingMessage.length(); i++) {
  //   parsed = parsed + incomingMessage[i];
  // }

  int delimiterIndex = incomingMessage.indexOf(DELIMITER); // als mid-marker

  if (delimiterIndex > 0) {
    Parsed[0] = incomingMessage.substring(0, delimiterIndex);
    Parsed[1] = incomingMessage.substring(delimiterIndex + 1, (incomingMessage.length()));
    Serial.println(Parsed[1]);
  } else {
    Parsed[0] = incomingMessage;
  }
}

void comminucation_bluettooth_start(){
  Bluetooth.begin(9600);
}
