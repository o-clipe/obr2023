/*Biblioteca Template - Header*/

#ifndef Motor_h
#define Motor_h

#include "Arduino.h"

#define DEFAULTVELOCITY 200 //  max 255

class Motor
{
  public:
    Motor(uint8_t direito, uint8_t esquerdo, uint8_t direitoRe, uint8_t esquerdoRe, uint8_t en1, uint8_t en2);
    void setup();
    void run();
    void ligarMotor(String motor, uint8_t vel=0);
    void desligarMotor(String motor);
    void parar();
    void ligarReto(uint8_t vel=0);
    void ligarRe(uint8_t vel=0);
    uint8_t velocidade;

  private:
    uint8_t _traduzStrParaPorta(String& arg);
    uint8_t _direito;
    uint8_t _esquerdo;
    uint8_t _direitoRe;
    uint8_t _esquerdoRe;
    uint8_t _en1;
    uint8_t _en2;
};

#endif