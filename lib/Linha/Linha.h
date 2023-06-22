/*Algoritimo para o robo seguir a linha*/

#ifndef Linha_h
#define Linha_h

#include "Arduino.h"
#include "Lum.h"
#include "Motor.h"
#include "Giros.h"

#define VELOCIDADEDECURVA 128
#define DELAYPOS 100
#define DELAYROT 100
#define DELAYPOST 50
class Linha
{
  public:
    Linha(Lum& lum_obj, Motor& motor_obj, Giros& giros_obj);
    void setup();
    bool segueLinha();
    void pararSeTroucouModo(uint8_t modo);
    uint8_t getState(int* state);

  private:
    Lum& _lum;
    Motor& _carro;
    Giros& _giros;
    uint8_t _modo;
    uint8_t _curvaFechadaDetectada; 
    bool _encruzilhada = false;
};

#endif