#include "Trailer.h"

Connection ConStatus = NOK;
TrailerState TrailerStatus = SOUND;

int steeringPosition = 90;

int triggerPins[] = {2, 4, 6, 8};
int echoPins[] = {3, 5, 7, 9};

DistanceSensor SensorOne(triggerPins[0], echoPins[0], echoPins[0]);
DistanceSensor SensorTwo(triggerPins[1], echoPins[1], echoPins[1]);
DistanceSensor SensorThree(triggerPins[2], echoPins[2], echoPins[2]);
DistanceSensor SensorFour(triggerPins[3], echoPins[3], echoPins[3]);

Connection trailer_get_connection_status() { return ConStatus; }
TrailerState trailer_get_trailer_state() { return TrailerStatus; }

void trailer_setup(){
  SensorOne.sensor_begin();
  SensorTwo.sensor_begin();
  SensorThree.sensor_begin();
  SensorFour.sensor_begin();
  SensorOne.sensor_start();
}

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
    if (Parsed[0] == "ACK"){
      communication_set_state(WAITING_FOR_MESSAGE);
    }
  }
}

void trailer_check_distance(){
  static DistanceSensor distanceSensor[] = {SensorOne, SensorTwo, SensorThree, SensorFour};
  static int sensorValue[] = {0, 0, 0, 0};
  static int lastsensor = 0;
  static unsigned long sensortimer;
  if(communication_get_state() == WAITING_FOR_MESSAGE){
    if((millis()-sensortimer) >250){
      if(distanceSensor[lastsensor].isFinished()){
        sensortimer = millis();
        int newValue = distanceSensor[lastsensor].sensor_get_value();
        lastsensor++;
        if (lastsensor >= 4){
          lastsensor=0;
        }
        distanceSensor[lastsensor].sensor_start();
        //Serial.print("newValue= ");
        //Serial.println(newValue);
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
  }


void trailer_assist_steering(){
  static unsigned long timesincelastupdate;
  if(ConStatus == OK){
    servo_set_position(steeringPosition);
  }
  if (ConStatus == NOK) {
    servo_set_position(SERVO_CENTER);
  }
}
