#include "Trailer.h"

Connection ConStatus = NOK;
TrailerState TrailerStatus = SOUND;

int steeringPosition = 90;

Connection trailer_get_connection_status() { return ConStatus; }
TrailerState trailer_get_trailer_state() { return TrailerStatus; }

void trailer_check_message() {
  static String incommingMessage = "";
  //Serial.println("Checking message");
  if (communication_read_message(&incommingMessage)) {
    Serial.println("Received message");
    ConStatus = OK;
    String Parsed[2];
    communication_parse_message(Parsed, &incommingMessage);

    if (Parsed[0] == "TRL_OFF") {
      TrailerStatus = OFF;
    }
    if (Parsed[0] == "TRL_SOUND") {
      TrailerStatus = SOUND;
    }
    if (Parsed[0] == "TLR_ASSIST") {
      TrailerStatus = ASSIST;
    }
    if (Parsed[0] == "STEER_POS") {
      steeringPosition = Parsed[1].toInt();
    }
    if (Parsed[0] == "BEAT") {
      communication_send_message("ACK");
      Serial.println("Sending ACK");

    }
  }
}

void trailer_check_distance(){
  static int sensorValue[] = {0, 0, 0, 0};
  static int lastsensor;
  static unsigned long sensortimer;
  if((millis()-sensortimer) >250){
      sensortimer = millis();
      lastsensor++;
      if (lastsensor==4){
        lastsensor=0;
      }
      int newValue = update_sensors(lastsensor);
      Serial.print("newValue= ");
      Serial.println(newValue);
      if (newValue != sensorValue[lastsensor]){
        sensorValue[lastsensor] = newValue;
        switch (lastsensor)
        {
        case 1:
         communication_send_message("SENSOR_LEFT_STATUS", newValue );
         Serial.print("sensor 1 = ");
         Serial.println(newValue);
        break;
        case 2:
         communication_send_message("SENSOR_MIDDLE_LEFT_STATUS", newValue );
         Serial.print("sensor 2 = ");
         Serial.println(newValue);
        break;
        case 3:
        communication_send_message("SENSOR_MIDDLE_RIGHT_STATUS", newValue );
        Serial.print("sensor 3 = ");
        Serial.println(newValue);
        break;
        case 4:
         communication_send_message("SENSOR_RIGHT_STATUS", newValue );
         Serial.print("sensor 4 = ");
         Serial.println(newValue);
        break;
        }
      }
    }
  }


void trailer_assist_steering(){
  if(ConStatus == OK){
    servo_set_position(steeringPosition);
  }
  if (ConStatus == NOK) {
    servo_set_position(SERVO_CENTER);
  }
}
