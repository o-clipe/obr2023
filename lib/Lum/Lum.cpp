/* Sensores de Luminosidade - Codigo*/

#include "Arduino.h"
#include "Lum.h"




Lum::Lum(uint8_t ee, uint8_t e, uint8_t m, uint8_t d, uint8_t dd) //  Constructor
{
  _ee = ee;
  _e = e;
  _m = m;
  _d = d;
  _dd = dd;
  uint8_t _limite[5] = {429, 255, 237, 344, 544};  //Limite deve ser colocado manualmente. Valor do sensor no branco.
  uint8_t _sensValueRange[5] = {709-429, 647-255, 633-237, 659-344, 761-544}; // ValueRange também
}


void Lum::setup() //  Chamado no Setup()
{

}


void Lum::mostraOutputSensores()
{
Serial.print(" ");
Serial.print(processedRead(_ee));
Serial.print(" | ");
Serial.print(processedRead(_e));
Serial.print(" | ");
Serial.print(processedRead(_m));
Serial.print(" | ");
Serial.print(processedRead(_d));
Serial.print(" | ");
Serial.print(processedRead(_dd));
Serial.println();
}


uint16_t Lum::processedRead(uint8_t sens)
{
  uint8_t sensores[5] = {_ee, _e, _m, _d, _dd};
  int idx = -1;

  for (int i = 0; i < 5; i++) 
  {
    if (sens == sensores[i]) 
    {
      idx = i;
    }
  }
  return normalizeSensEntry(idx, analogRead(sens));
}

uint16_t Lum::normalizeSensEntry(uint8_t idxSensor, uint16_t entrada){

  uint8_t idx = idxSensor;
  float limiteSens = (float)_limite[idx];
  float read = (float)entrada;
  float range = (float)_sensValueRange[idx];
  float b = (float)OUTPUTRANGE;
  float normalizado = (read - limiteSens)/ range * b;
  uint16_t rtrn = normalizado;
  if (rtrn > OUTPUTRANGE && rtrn < OUTPUTRANGE*2)
  {
    rtrn = OUTPUTRANGE;
  } 
  else if (rtrn > OUTPUTRANGE*2)
  {
    rtrn = 0;
  }
  return rtrn;
}


uint16_t* Lum::processedReadAll()
{
  _processedReadAllOutput[0] = processedRead(_ee);
  _processedReadAllOutput[1] = processedRead(_e);
  _processedReadAllOutput[2] = processedRead(_m);
  _processedReadAllOutput[3] = processedRead(_d);
  _processedReadAllOutput[4] = processedRead(_dd);

  return _processedReadAllOutput;
}


