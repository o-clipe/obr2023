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
    Linha(Lum& lum_obj, Motor& motor_obj, Giros& giros_obj);
    void setup();
    void run();
    uint8_t checkState(uint16_t sensorsPosition[5]);
    void pararSeOutroStatus(uint8_t f_status);
    bool segueLinha();
    bool girar90Graus(char l);
    bool paralelar();
    bool alignInPlace();
    bool gap();

    bool _paralelarLadoE();
    bool _paralelarLadoD();

    uint8_t status;
  private:
    Lum& _lum;
    Motor& _carro;
    Giros& _giros;
    bool _loopBool=true;  // _loopBool é sempre, quando não está sendo usado, _true_. Ou seja, deve sempre existir antes de return false;
    float _startGirosPos[3];
    char _paralelarLado;
    bool _paralelarLadoDone=false;
    uint8_t _paralelarBest=0;
    bool _paralelarBestAssigned=false;
};

#endif