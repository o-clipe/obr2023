/*Sensores de Luminosidade*/

#ifndef Lum_h
#define Lum_h


#define OUTPUTRANGE 20
#define MEMSIZE 200
#define MILLISTEP 100
#define READSECATSTART 3

#include "Arduino.h"

class Lum{
  public:
    Lum(uint8_t ee, uint8_t e, uint8_t m, uint8_t d, uint8_t dd);
    void setup();
    void run();
    void mostraOutputSensores();
    void defineLimite(int checkLast=0);
    void setMemoria();
    uint16_t processedRead(uint8_t sens);
    uint16_t normalizeSensEntry(uint8_t idxSensor, uint16_t entrada);
    uint16_t* processedReadAll();
    uint16_t limite[5];
    uint16_t memoria[MEMSIZE][5];
    uint32_t memoriaLastIdx;
    uint16_t _processedReadAllOutput[5];
  private:
    uint8_t _ee;
    uint8_t _e;
    uint8_t _m;
    uint8_t _d;
    uint8_t _dd;
    uint8_t _inicio;
    uint16_t _sensValueRange[5];
    int _cor1[5];
    int _cor2[5];


};

#endif