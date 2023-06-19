/*Algoritimo para o robo seguir a linha*/

#ifndef Linha_h
#define Linha_h

#include "Arduino.h"
#include "Lum.h"
#include "Motor.h"

#define VELOCIDADEDECURVA 50

class Linha
{
  public:
    Linha(Lum& lum_obj, Motor& motor_obj);
    void setup();
    void run();
    String checkState(uint16_t sensorsPosition[5]);
    void pararSeOutroStatus(String f_status);
    void rotinaBasica();
    String status;
  private:
    Lum& _lum;
    Motor& _carro;
};

#endif