/*Biblioteca Template - Header*/

#ifndef Cor_h
#define Cor_h

#include "Arduino.h"

class Cor
{
  public:
    Cor(uint8_t s0, uint8_t s1, uint8_t s2, uint8_t s3, uint8_t out, uint8_t led);
    void setup();
    void run();
    uint8_t* rgbaRead();
    char rgbaToChar(uint8_t* rgba);
    void defineLimiteBranco();
    uint8_t _rgba[4];
  private:
    uint8_t _s0;
    uint8_t _s1;
    uint8_t _s2;
    uint8_t _s3;
    uint8_t _out;
    uint8_t _led;
    uint8_t _limiteBranco;
};

#endif