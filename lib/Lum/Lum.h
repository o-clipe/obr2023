/*Sensores de Luminosidade*/

#ifndef Lum_h
#define Lum_h


#define OUTPUTRANGE 1

#include "Arduino.h"

class Lum{
  public:
    Lum(uint8_t ee, uint8_t e, uint8_t d, uint8_t dd, uint8_t te, uint8_t td);
    void setup();
    void mostraOutputSensores();
    int processedRead(uint8_t sens);
    int normalizeSensEntry(uint8_t idxSensor, uint16_t entrada);
    int* processedReadAll();
  private:
    uint8_t _ee;
    uint8_t _e;
    uint8_t _te;
    uint8_t _td;
    uint8_t _d;
    uint8_t _dd;
    int _sensValueRange[6];
    int _processedReadAllOutput[6];
    int _limite[6];


};

#endif