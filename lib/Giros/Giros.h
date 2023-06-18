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
    void run();
    void print();
    // MPU6050 mpu6050;
  private:
    int _none;
};

#endif