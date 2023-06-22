/*Sensores de Luminosidade*/

#ifndef Lum_h
#define Lum_h


#define OUTPUTRANGE 10

#include "Arduino.h"

class Lum{
  public:
    Lum(uint8_t ee, uint8_t e, uint8_t m, uint8_t d, uint8_t dd);
    void setup();
    void run();
    void mostraOutputSensores();
    uint8_t processedRead(uint8_t sens);
    uint8_t normalizeSensEntry(uint8_t idxSensor, uint16_t entrada);
    uint8_t* processedReadAll();
  private:
    uint8_t _ee;
    uint8_t _e;
    uint8_t _m;
    uint8_t _d;
    uint8_t _dd;
    uint16_t _sensValueRange[5];
    uint8_t _processedReadAllOutput[5];
    uint16_t _limite[5];


};

#endif