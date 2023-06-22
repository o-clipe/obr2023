/*Algoritimo para o robo seguir a linha*/

#ifndef Linha_h
#define Linha_h

#include "Arduino.h"
#include "Lum.h"
#include "Motor.h"
#include "Giros.h"

#define DELAYPOS 50
#define DELAYROT 50
#define DELAYTURN 50
#define DELAY 50


class Linha
{
  public:
    Linha(Lum& lum_obj, Motor& motor_obj, Giros& giros_obj);
    void setup();
    bool segueLinha();

    uint8_t _lastOutSeen = 0;  // Entre dd, ee, dd+ee, qual foi o último visto

    // Unidades Mínimas de Movimento
    void pos(uint16_t time_=DELAYPOS);
    void npos(uint16_t time_=DELAYPOS);
    void rot(uint16_t time_=DELAYROT);
    void nrot(uint16_t time_=DELAYROT);
    void rturn(uint16_t time_=DELAYTURN);
    void lturn(uint16_t time_=DELAYTURN);

    // Objetos
  private:
    Lum& _lum;
    Motor& _carro;
    Giros& _giros;
};

#endif