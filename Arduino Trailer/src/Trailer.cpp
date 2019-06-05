#include "Trailer.h"

Connection ConStatus = NOK;
TrailerState TrailerStatus = SOUND;
bool sentfakevalue = true;
int steeringPosition = 90;
/*




*/
//int triggerPins[] = {2, 4, 6, 8};
//int echoPins[] = {3, 5, 7, 9};
int triggerPins[] = {6, 7, 8, 9};
int echoPins[] = {2, 3, 4, 5};

bool waitingForAcknowledge = 0;

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
  //  Serial.println("Received message");
    Serial.println(incommingMessage);
    ConStatus = OK;
    String Parsed[2];
    communication_parse_message(Parsed, &incommingMessage);

    if (Parsed[0] == "TRL_OFF") {
      TrailerStatus = OFF;
      communication_send_message("ACK");
    }
    if (Parsed[0] == "TRL_SOUND") {
      TrailerStatus = SOUND;
        communication_send_message("ACK");
    }
    if (Parsed[0] == "TLR_ASSIST") {
      TrailerStatus = ASSIST;
        communication_send_message("ACK");
    }
    if (Parsed[0] == "STEER_POS") {
      steeringPosition = Parsed[1].toInt();
        communication_send_message("ACK");
    }
    if (Parsed[0] == "BEAT") {
      communication_send_message("ACK");
    }
    if (Parsed[0] == "ACK"){
      communication_set_state(WAITING_FOR_MESSAGE);
      waitingForAcknowledge = false;
    }
  }
}

void trailer_check_distance(){
  static DistanceSensor distanceSensor[] = {SensorOne, SensorTwo, SensorThree, SensorFour};
  static int sensorValue[] = {0, 0, 0, 0};
  static int lastsensor = 0;
  static unsigned long sensortimer;
  if(communication_get_state() == WAITING_FOR_MESSAGE){
    if(!sentfakevalue){
    if((millis()-sensortimer) >250){
      if(distanceSensor[lastsensor].sensor_is_finished()){
        sensortimer = millis();
        int newValue = distanceSensor[lastsensor].sensor_get_value();
        Serial.println("Distande =");
        Serial.println(newValue);
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
           waitingForAcknowledge = true;
           Serial.print("sensor 1 = ");
           Serial.println(newValue);
          break;
          case 2:
           communication_send_message("SENSOR_MIDDLE_LEFT_STATUS", newValue );
           waitingForAcknowledge = true;
           Serial.print("sensor 2 = ");
           Serial.println(newValue);
          break;
          case 3:
          communication_send_message("SENSOR_MIDDLE_RIGHT_STATUS", newValue );
          waitingForAcknowledge = true;
          Serial.print("sensor 3 = ");
          Serial.println(newValue);
          break;
          case 4:
           communication_send_message("SENSOR_RIGHT_STATUS", newValue );
           waitingForAcknowledge = true;
           Serial.print("sensor 4 = ");
           Serial.println(newValue);
          break;
        }
        }
      }
    }
  }
  else{
    trailer_sent_fake_value();
  }
  }
}

void trailer_sent_fake_value(){
  static int lastsensor = 0;
  static unsigned long sensortimer;
  if((millis()-sensortimer) >250){
    Serial.print("trailer_sent_fake_value =");
    sensortimer = millis();
    lastsensor++;
    if (lastsensor >= 4){
      lastsensor=0;
    }
    int newValue = random(0, 30);
    Serial.println(newValue);
    switch (lastsensor ) {
      case 0:
        communication_send_message("SENSOR_LEFT_STATUS", newValue );
        break;
      case 1:
        communication_send_message("SENSOR_MIDDLE_LEFT_STATUS", newValue );
        break;
      case 2:
        communication_send_message("SENSOR_MIDDLE_RIGHT_STATUS", newValue );
        break;
      case 3:
        communication_send_message("SENSOR_RIGHT_STATUS", newValue );
        break;
    }
    waitingForAcknowledge = true;
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
