/* Sensores de Luminosidade - Codigo*/

#include "Arduino.h"
#include "Lum.h"




Lum::Lum(uint8_t ee, uint8_t e, uint8_t m, uint8_t d, uint8_t dd, uint8_t te, uint8_t td) //  Constructor
{
  _ee = ee;
  _e = e;
  _m = m;
  _d = d;
  _dd = dd;
  _te = te;
  _td = td;
  _limite[0] = LIMITE_EE;  //Limite deve ser colocado manualmente. Valor do sensor no branco.
  _limite[1] = LIMITE_E;
  _limite[2] = LIMITE_M;
  _limite[3] = LIMITE_D;
  _limite[4] = LIMITE_DD;
  _limite[5] = LIMITE_TE;
  _limite[6] = LIMITE_TD;
}


void Lum::setup()  // Pra rodar no setup()
{

}


void Lum::processedPrint()
{
  Serial.print("  ");
  Serial.print(processedRead(_ee));
  Serial.print(" | ");
  Serial.print(processedRead(_e));
  Serial.print(" | ");
  Serial.print(processedRead(_m));
  Serial.print(" | ");
  Serial.print(processedRead(_d));
  Serial.print(" | ");
  Serial.print(processedRead(_dd));
  Serial.print("  > ");
  Serial.print(processedRead(_te));
  Serial.print(" | ");
  Serial.print(processedRead(_td));
}


void Lum::unprocessedPrint()
{
  Serial.print(" ");
  Serial.print(analogRead(_ee));
  Serial.print(" | ");
  Serial.print(analogRead(_e));
  Serial.print(" | ");
  Serial.print(analogRead(_m));
  Serial.print(" | ");
  Serial.print(analogRead(_d));
  Serial.print(" | ");
  Serial.print(analogRead(_dd));
  Serial.print("  > ");
  Serial.print(analogRead(_te));
  Serial.print(" | ");
  Serial.print(analogRead(_td));
}


bool Lum::processedRead(uint8_t sens)
{
  uint8_t sensores[7] = {_ee, _e, _m, _d, _dd, _te, _td};
  int idx = -1;

  for (int i = 0; i < 7; i++) 
  {
    if (sens == sensores[i]) 
    {
      idx = i;
    }
  }
  return normalizeSensEntry(idx, analogRead(sens));
}

bool Lum::normalizeSensEntry(uint8_t idxSensor, uint16_t entradaAnalog){

  float limiteSens = (float)_limite[idxSensor];
  float read = (float)entradaAnalog;
  if (read >= limiteSens)
  {
    return true;
  }
  else
  {
    return false;
  }
}


bool* Lum::processedReadAll()
{
  _processedReadAllOutput[0] = processedRead(_ee);
  _processedReadAllOutput[1] = processedRead(_e);
  _processedReadAllOutput[2] = processedRead(_m);
  _processedReadAllOutput[3] = processedRead(_d);
  _processedReadAllOutput[4] = processedRead(_dd);
  _processedReadAllOutput[5] = processedRead(_te);
  _processedReadAllOutput[6] = processedRead(_td);

  return _processedReadAllOutput;
}


