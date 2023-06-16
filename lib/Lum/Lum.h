/*Sensores de Luminosidade*/

#ifndef Lum_h
#define Lum_h


#define OUTPUTRANGE 10
#define MEMSIZE 500
#define MILLISTEP 200

#include "Arduino.h"

class Lum{
  public:
    Lum(uint8_t ee, uint8_t e, uint8_t m, uint8_t d, uint8_t dd);
    void setup();
    void run();
    void defineLimite(int checkLast=0);
    void setMemoria();
    uint16_t processedRead(uint8_t sens);
    uint16_t normalizeSensEntry(uint8_t idxSensor, uint16_t entrada);
    uint16_t limite[5];
    uint16_t memoria[MEMSIZE][5];
    uint32_t memoriaLastIdx;
  private:
    uint8_t _ee;
    uint8_t _e;
    uint8_t _m;
    uint8_t _d;
    uint8_t _dd;
    uint8_t _inicio;
    float _sensValueRange[5];


};

#endif