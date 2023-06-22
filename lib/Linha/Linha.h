/*Algoritimo para o robo seguir a linha*/

#ifndef Linha_h
#define Linha_h

#include "Arduino.h"
#include "Lum.h"
#include "Motor.h"
#include "Giros.h"

#define VELOCIDADEDECURVA 96
#define DELAYPOS 50
#define DELAYROT 50
class Linha
{
  public:
    Linha(Lum& lum_obj, Motor& motor_obj, Giros& giros_obj);
    void setup();
    bool segueLinha();
    void pos(uint16_t delay_=DELAYPOS);
    void npos(uint16_t delay_=DELAYPOS);
    void rot(uint16_t delay_=DELAYROT);
    void nrot(uint16_t delay_=DELAYROT);
    int goodAlignment;
    int goodSymmetry;
    uint8_t getState(uint8_t* state);
    void inPlace(int alignmentScore);
    void testCurve(int symmetryScore);
    uint8_t currentState;
    uint8_t lastState;
    uint8_t lastStateIsCurrent;
    int lastSymmetryScore;
    int lastAlignmentScore;
  private:
    Lum& _lum;
    Motor& _carro;
    Giros& _giros;
    uint8_t ideal[5];
};

#endif