/*Algoritimo para o robo seguir a linha*/

#ifndef Linha_h
#define Linha_h

#include "Arduino.h"
#include "Lum.h"

class Linha
{
  public:
    Linha(Lum& lum_obj);
    void setup();
    void run();
    String checkState(uint16_t sensorsPosition[5]);
  private:
    Lum& _lum;
};

#endif