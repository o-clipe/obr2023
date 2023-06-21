/*Giroscópio- Header*/

#ifndef Giros_h
#define Giros_h

#include "Arduino.h"
#include <MPU6050_tockn.h>
#include <Wire.h>

#define MEMSIZE 10
#define MILLISTEP 500
#define FATORERROVARIACAO 1.5

class Giros
{
  public:
    Giros();
    void setup();
    void run();
    void print();
    float* girosRead();
    void setMemoria();
    void defineVariacaoPadrao();
    bool detectaVariacao(char eixo);
    float memoria[MEMSIZE][3];
    uint8_t memoriaLastIdx;
    float variacaoPadrao[3];
    // MPU6050 mpu6050;
  private:
    uint8_t _traduzStrParaIdx(String& arg);
    float _xyz[3];
    
};

#endif