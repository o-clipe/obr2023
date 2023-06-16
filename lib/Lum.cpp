/* Sensores de Luminosidade - Codigo*/

#include "Arduino.h"
#include "Lum.h"

#define led LED_BUILTIN

Lum::Lum(uint8_t ee, uint8_t e, uint8_t m, uint8_t d, uint8_t dd, int milli_step) // Constructor
{
    _ee = ee;
    _e = e;
    _m = m;
    _d = m;
    _dd = d;

    _milli_step = milli_step;
    int _last_step_idx;

}

void Lum::setup() // Chamado no Setup()
{
  pinMode(led, OUTPUT);
}

void Lum::run() // Roda comandos de rotina
{
  setMemoria();

}

void Lum::setMemoria()
{
  int read = millis()%(MEMSIZE*_milli_step);
  int idx = (read - read%_milli_step)/_milli_step;
  
  memoria[idx][0] = analogRead(_ee);
  memoria[idx][1] = analogRead(_e);
  memoria[idx][2] = analogRead(_m);
  memoria[idx][3] = analogRead(_d);
  memoria[idx][4] = analogRead(_dd);

  memoria_last_idx = idx;
}

void Lum::defineLimite(int checkLast = 100)
{

  bool loop = true;
  while (loop){
    
  }
}


