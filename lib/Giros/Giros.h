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
    float Giros::girosRead(int option);  // Le giroscopio e retorna valor de PITCH YAW ou ROLL 
};

#endif