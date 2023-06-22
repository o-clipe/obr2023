/*Giroscópio- Header*/

#ifndef Giros_h
#define Giros_h

#include "Arduino.h"
#include <MPU6050_tockn.h>
#include <Wire.h>

class Giros
{
  public:
    Giros();
    void setup();
    void print();
    float* girosRead();
    void setMemoria();
  private:
    float _xyz[3];
    
};

#endif