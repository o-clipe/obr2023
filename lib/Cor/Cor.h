/*Cor - Header*/

#ifndef Cor_h
#define Cor_h

#include "Arduino.h"

#define None 0
#define Red 1
#define Green 2
#define Blue 3


class Cor
{
  public:
    Cor(uint8_t s0, uint8_t s1, uint8_t s2, uint8_t s3, uint8_t out, uint8_t led, long limiteBranco);
    void setup();  // Pra rodar no setup()
    long* rgbaRead();  // Le sensor e retorna array sendo [red, green, blue, all]
    uint8_t rgbaToColorInt(long* rgba);  // Calcula cor mais visível e retorna código entre Red Green Blue.
    uint8_t colorRead();  // Le sensor e retorna o código da cor mais visível.
    void printRaw();  // Mostra valor dos sensores.
    void ledOn();
    void ledOff();
    
  // Uso interno // *********************
  private:
    long _rgba[4];
  uint8_t _s0;
    uint8_t _s1;
    uint8_t _s2;
    uint8_t _s3;
    uint8_t _out;
    uint8_t _led;
    long _limiteBranco;
};

#endif