/*Biblioteca Template - Header*/

#ifndef Lib_h
#define Lib_h

#include "Arduino.h"

class Lib{
  public:
    Lib(int pin);
    void setup();
    void dot();
    void dash();
  private:
    int _pin;
};

#endif