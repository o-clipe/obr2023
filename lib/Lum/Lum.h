/*Sensores de Luminosidade*/

#ifndef Lum_h
#define Lum_h

#include "Arduino.h"

#define LIMITE_EE 700
#define LIMITE_E 670
#define LIMITE_M 650
#define LIMITE_D 670
#define LIMITE_DD 700
#define LIMITE_TE 750
#define LIMITE_TD 750

class Lum{
  public:
    Lum(uint8_t ee, uint8_t e, uint8_t m, uint8_t d, uint8_t dd, uint8_t te, uint8_t td);
    void setup();  // Pra rodar no setup()
    void processedPrint();  // printa no Serial os valores sendo 0 ou 1
    void unprocessedPrint();  // printa no Serial os valores analogicos crus
    bool* processedReadAll();  // retorna o valor processado boolean dos sensores



    // Uso interno // *********************
    bool processedRead(uint8_t sens);
    bool normalizeSensEntry(uint8_t idxSensor, uint16_t entradaAnalog);
    
  private:
    uint8_t _ee;
    uint8_t _e;
    uint8_t _m;
    uint8_t _d;
    uint8_t _dd;
    uint8_t _te;
    uint8_t _td;
    bool _processedReadAllOutput[7];
    uint16_t _limite[7];


};

#endif