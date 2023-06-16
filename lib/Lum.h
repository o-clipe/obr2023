/*Sensores de Luminosidade*/

#ifndef Lum_h
#define Lum_h


#define MEMSIZE 100000
#include "Arduino.h"

class Lum{
  public:
    Lum(uint8_t ee, uint8_t e, uint8_t m, uint8_t d, uint8_t dd, int milli_step);
    void setup();
    void run();
    void defineLimite(int checkLast);
    void setMemoria();
    int limite[5];
    int memoria[MEMSIZE][5];
    int memoria_last_idx;
  private:
    uint8_t _ee;
    uint8_t _e;
    uint8_t _m;
    uint8_t _d;
    uint8_t _dd;
    int _milli_step;
    int _inicio;

};

#endif