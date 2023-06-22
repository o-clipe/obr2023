/*Giroscópio- Header*/

#ifndef Giros_h
#define Giros_h

#include "Arduino.h"
#include <MPU6050_tockn.h>
#include <Wire.h>

#define PITCH 0
#define YAW 2
#define ROLL 1


class Giros
{
  public:
    Giros();
    void setup();  // Chmados no setup
    void print();  // Printa pos
    float* girosRead();  // Le giroscopio e retorna array com valores dos angulos PITCH ROLL YAW

  private:
    float _xyz[3];
    
};

#endif