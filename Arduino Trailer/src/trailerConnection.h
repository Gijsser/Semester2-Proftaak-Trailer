#include <Arduino.h>
#include "Communication.h"
#ifndef _TRAILERCONNECTION_H
  #define _TRAILERCONNECTION_H
  #define CONNECTIONLOOP 13
  typedef enum  {
    NOTCONNECTED = 0,
    CONNECTED = 1
  }ConnectionState;

  void trailerConnection_setup();
  bool trailerConnection_Get_ConnectionState();
  void trailerConnection_Update_Connection();

#endif
