/*Biblioteca Template - Header*/

#ifndef Som_h
#define Som_h

#include "Arduino.h"
#include <HCSR04.h>

#define DIST_OBSTACULO 30
#define DELAY_CAPTURE 10
#define MEMORIA 5

class Som
{
  public:
    Som(uint8_t _trigger, uint8_t _echo);
    void setup();
    float distRead();
    float mediaRead();
  private:
    HCSR04 sensorHCSR04;
};

#endif