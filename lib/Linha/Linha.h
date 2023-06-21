/*Algoritimo para o robo seguir a linha*/

#ifndef Linha_h
#define Linha_h

#include "Arduino.h"
#include "Lum.h"
#include "Motor.h"
#include "Giros.h"

#define VELOCIDADEDECURVA 96

class Linha
{
  public:
    Linha(Lum& lum_obj, Motor& motor_obj, Giros& giros_obj);
    void setup();
    void run();
    bool segueLinha();

  private:
    Lum& _lum;
    Motor& _carro;
    Giros& _giros;
};

#endif