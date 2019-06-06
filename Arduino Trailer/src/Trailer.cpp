#include "Trailer.h"
#include <NewPing.h>

Connection ConStatus = NOK;
TrailerState TrailerStatus = OFF;

bool waitingForAcknowledge = 0;


Connection trailer_get_connection_status() { return ConStatus; }
TrailerState trailer_get_trailer_state() { return TrailerStatus; }

int steeringPosition;

void trailer_check_message() {
  static String incommingMessage = "";
  static unsigned long timeSinceLastMessage = 0;
  if ((millis() - timeSinceLastMessage) > 5000){
    ConStatus = NOK;
  }
  if (communication_read_message(&incommingMessage)) {
    timeSinceLastMessage = millis();
    Serial.println(incommingMessage);
    ConStatus = OK;
    String Parsed[2];
    communication_parse_message(Parsed, &incommingMessage);

    // if(waitingForAcknowledge){
    //   if (Parsed[0] == "ACK"){
    //     communication_set_state(WAITING_FOR_MESSAGE);
    //     waitingForAcknowledge = false;
    //   }
    //   else{
    //     communication_send_message("NACK");
    //   }
    // }
    // else{
    if (Parsed[0] == "TRL_OFF") {
      TrailerStatus = OFF;
      communication_send_message("ACK");
    }
    if (Parsed[0] == "TRL_SOUND") {
      TrailerStatus = SOUND;
        communication_send_message("ACK");
    }
    if (Parsed[0] == "TRL_ASSIST") {
      TrailerStatus = ASSIST;
        communication_send_message("ACK");
    }
    if (Parsed[0] == "WHEEL_POS") {
        steeringPosition = Parsed[1].toInt();
        communication_send_message("ACK");
    }
    if (Parsed[0] == "BEAT") {
      communication_send_message("ACK");
    }
  //}
  }
}

void trailer_check_distance(){

  static unsigned long timeSinceLastPing = 0;
  static int currentSensor = 0;
  static int sensorValue[] = {0, 0};
  if(communication_get_state() == WAITING_FOR_MESSAGE){
      if((millis() - timeSinceLastPing) > 100 ){
        int newValue = 0;
        //Serial.print("current sensor = ");
        //Serial.println(currentSensor);

        sensor_update_values(&newValue, currentSensor);
        if (newValue != sensorValue[currentSensor]){
          sensorValue[currentSensor] = newValue;
          switch (currentSensor)
          {
          case 0:
           communication_send_message("SENSOR_LEFT_STATUS", newValue );
           waitingForAcknowledge = true;
           //Serial.print("sensor 1 = ");
           //Serial.println(newValue);
          break;
          case 1:
           communication_send_message("SENSOR_MIDDLE_LEFT_STATUS", newValue );
           waitingForAcknowledge = true;
           //Serial.print("sensor 2 = ");
           //Serial.println(newValue);
          break;
          case 2:
          communication_send_message("SENSOR_MIDDLE_RIGHT_STATUS", newValue );
          waitingForAcknowledge = true;
          //Serial.print("sensor 3 = ");
          //Serial.println(newValue);
          break;
          case 3:
           communication_send_message("SENSOR_RIGHT_STATUS", newValue );
           waitingForAcknowledge = true;
           Serial.print("sensor 4 = ");
           Serial.println(newValue);
          break;
          }
        }
        if(currentSensor == 1 ){
          currentSensor = 0;
        }
        else{
          currentSensor = 1;
        }
        update_sensors(currentSensor);
        timeSinceLastPing = millis();
      }
    }
}



void trailer_assist_steering(){
  static unsigned long timesincelastupdate;
  static int lastPos = 110;
  if(ConStatus == OK && TrailerStatus == ASSIST){
    if((steeringPosition - lastPos) >= 3 || (lastPos - steeringPosition) >= 3){
    lastPos = steeringPosition;
    timesincelastupdate = millis();
    servo_set_position(steeringPosition);
  }
  }
  if(ConStatus == OK && TrailerStatus != ASSIST){
    lastPos = SERVO_CENTER;
    timesincelastupdate = millis();
    servo_set_position(SERVO_CENTER);

  }
  if (ConStatus == NOK || (millis() -timesincelastupdate) > 5000) {
    timesincelastupdate = millis();
    servo_set_position(SERVO_CENTER);
    lastPos = SERVO_CENTER;
  }
}
