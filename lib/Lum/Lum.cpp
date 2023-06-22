/* Sensores de Luminosidade - Codigo*/

#include "Arduino.h"
#include "Lum.h"


Lum::Lum(uint8_t ee, uint8_t e, uint8_t d, uint8_t dd, uint8_t te, uint8_t td) //  Constructor
{
  _ee = ee;
  _e = e;
  _d = d;
  _dd = dd;
  _te = te;
  _td = td;
  _limite[0] = 713;
  _limite[1] = 589;
  _limite[2] = 655;
  _limite[3] = 713;
  _limite[4] = 656;
  _limite[5] = 679;
  _sensValueRange[0] = 800-_limite[0];
  _sensValueRange[1] = 800-_limite[1];
  _sensValueRange[2] = 800-_limite[2];
  _sensValueRange[3] = 800-_limite[3];
  _sensValueRange[4] = 800-_limite[4];
  _sensValueRange[5] = 800-_limite[5];
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
Serial.print(processedRead(_d));
Serial.print(" | ");
Serial.print(processedRead(_dd));
Serial.print(" | ");
Serial.print(processedRead(_te));
Serial.print(" | ");
Serial.print(processedRead(_td));
Serial.println();
}


int Lum::processedRead(uint8_t sens)
{
  int sensores[6] = {_ee, _e, _d, _dd, _te, _td};
  int idx = -1;

  for (int i = 0; i < 6; i++) 
  {
    if (sens == sensores[i]) 
    {
      idx = i;
    }
  }
  return normalizeSensEntry(idx, analogRead(sens));
}

int Lum::normalizeSensEntry(uint8_t idxSensor, uint16_t entrada){

  uint8_t idx = idxSensor;
  float limiteSens = (float)_limite[idx];
  float read = (float)entrada;
  float range = (float)_sensValueRange[idx];
  float b = (float)OUTPUTRANGE;
  float normalizado = (read - limiteSens)/ range * b;
  int rtrn = normalizado;
  if (rtrn > OUTPUTRANGE && rtrn < OUTPUTRANGE*2)
  {
    rtrn = OUTPUTRANGE;
  } 
  else if (rtrn > OUTPUTRANGE*2 || rtrn < 0)
  {
    rtrn = 0;
  }
  return rtrn;
}


int* Lum::processedReadAll()
{
  _processedReadAllOutput[0] = processedRead(_ee);
  _processedReadAllOutput[1] = processedRead(_e);
  _processedReadAllOutput[2] = processedRead(_d);
  _processedReadAllOutput[3] = processedRead(_dd);
  _processedReadAllOutput[4] = processedRead(_te);
  _processedReadAllOutput[5] = processedRead(_td);

  return _processedReadAllOutput;
}


