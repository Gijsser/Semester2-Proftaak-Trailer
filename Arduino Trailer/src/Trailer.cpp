#include <Arduino.h>

#include "Communication.h"
#include "ServoControl.h"
#include "Trailer.h"
#include "Sensors.h"

Connection ConStatus = NOK;
TrailerState TrailerStatus = OFF;

int sensorValue[] = {0, 0, 0, 0};
int steeringPosition = 512;

int trailer_get_connection_status() { return ConStatus; }
int trailer_get_trailer_state() { return TrailerStatus; }
int trailer_get_com_state() { return TrailerStatus; }

void trailer_check_message() {
  if (communication_read_message() == 1) {
    ConStatus = OK;
    String Parsed[2];
    communication_parse_message(Parsed, 2);

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
      int val = Parsed[1].toInt();
      steeringPosition = map(val, 0, 1023, SERVO_MIN, SERVO_MAX);
    }
    if (Parsed[0] == "BEAT") {
      communication_send_message("ACK");
    }
  }
}

void trailer_check_distance(){
  for(int i = 0; i <  4; i++){
    int newValue = update_sensors(i);
    if (newValue != sensorValue[i]){
      sensorValue[i] = newValue;
      switch (i)
      {
      case 1:
       communication_send_message("SENSOR_LEFT_STATUS", sensorValue[i] );
      break;
      case 2:
       communication_send_message("SENSOR_MIDDLE_LEFT_STATUS", sensorValue[i] );
      break;
      case 3:
      communication_send_message("SENSOR_MIDDLE_RIGHT_STATUS", sensorValue[i] );
      break;
      case 4:
       communication_send_message("SENSOR_RIGHT_STATUS", sensorValue[i] );
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
