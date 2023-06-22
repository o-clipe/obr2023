/*Biblioteca Template - Header*/

#ifndef Motor_h
#define Motor_h

#include "Arduino.h"

class Motor
{
  public:
    Motor(uint8_t direito, uint8_t esquerdo, uint8_t direitoRe, uint8_t esquerdoRe, uint8_t velocidadeEsquerdo, uint8_t velocidadeDireito);
    void setup();
    void ligarMotor(uint8_t motor, uint8_t vel=0);
    void desligarMotor(uint8_t motor);
    void parar();
    void ligarReto(uint8_t vel=0);
    void ligarRe(uint8_t vel=0);
    uint8_t velocidade;
    uint8_t _direito;
    uint8_t _esquerdo;
    uint8_t _direitoRe;
    uint8_t _esquerdoRe;

  private:

    uint8_t _enEsquerdo;
    uint8_t _enDireito;
};

#endif