/* Sensores de Luminosidade - Codigo*/

#include "Arduino.h"
#include "Lum.h"

#define led LED_BUILTIN


Lum::Lum(uint8_t ee, uint8_t e, uint8_t m, uint8_t d, uint8_t dd) //  Constructor
{
  _ee = ee;
  _e = e;
  _m = m;
  _d = d;
  _dd = dd;

  memoriaLastIdx = 0;
  _inicio = (uint8_t)1;

}


void Lum::setup() //  Chamado no Setup()
{
  pinMode(led, OUTPUT);
}

void Lum::run() //  Roda comandos de rotina
{
  setMemoria();
  if (_inicio > 0){
    defineLimite();
  }
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
  if (idx == -1)
  {
    Serial.println('F');
  }
  
  return normalizeSensEntry(idx, analogRead(sens));
}

uint16_t Lum::normalizeSensEntry(uint8_t idxSensor, uint16_t entrada){

  if (_inicio > 0)
  {
    return entrada;
  }

  uint8_t idx = idxSensor;
  float limiteSens = (float)limite[idx];
  float read = (float)entrada;
  float range = (float)_sensValueRange[idx];
  float b = (float)OUTPUTRANGE;

  float normalizado = (read - limiteSens)/ _sensValueRange[idx] * b;

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

void Lum::setMemoria()
{
  uint16_t read = millis()%(MEMSIZE*MILLISTEP);
  uint32_t idx = (read - read%MILLISTEP)/MILLISTEP;
  
  memoria[idx][0] = analogRead(_ee);
  memoria[idx][1] = analogRead(_e);
  memoria[idx][2] = analogRead(_m);
  memoria[idx][3] = analogRead(_d);
  memoria[idx][4] = analogRead(_dd);

  memoriaLastIdx = idx;
}

void Lum::defineLimite(int checkLast = 0)
{
  if (!checkLast)
  {
    checkLast = READSECATSTART*1000/MILLISTEP; //  checa ultimos READSECATSTART seg
  }
  bool passou = true;
  if (millis() > READSECATSTART*1000)
  {
    int max[5] = {0, 0, 0, 0, 0};
    int min[5] = {1001, 1001, 1001, 1001, 1001};
    int idx = 0;
    for (int i=0; i < checkLast; i++)
    {
      idx = (MEMSIZE+i+memoriaLastIdx-checkLast)%MEMSIZE; //  index negative overflow !!
      for (int j=0; j < 5; j++)
      {
        if(memoria[idx][j] > max[j])
        {
          max[j] = memoria[idx][j];
        }
        if(memoria[idx][j] < min[j])
        {
          min[j] = memoria[idx][j];
        }
      }
    }

    _inicio += 1;
    for (int j=0; j < 5; j++)
    {
      if (max[j] - min[j] > 50 || min[0] == 0)
      {
        _inicio -= 1;
        passou = false;
        break;
      }
    }
    if (_inicio == 2 && passou)
    {
      Serial.println("1a cor guardada");
      for (int j=0; j < 5; j++)
      {
        _cor1[j] = min[j];
      }
      for (uint32_t mem=0; mem < MEMSIZE; mem++)
      {
        for (uint8_t s=0; s < 5; s++)
        {
          memoria[mem][s] = 0;
        }
      }

      for (int k=0; k < 20; k++) //  pisca o led 20x em 2 seg. Leu o branco!!!!
      { 
        digitalWrite(led, HIGH);
        delay(50);
        digitalWrite(led, LOW);
        delay(50);
      }
    }
      
    if (_inicio == 3 && passou)
    {
      Serial.println("2a cor guardada");
      for (int j=0; j < 5; j++)
      {
        _cor2[j] = min[j];
      }

      for (int j=0; j < 5; j++)
      {
        if (_cor1[j] < _cor2[j])
        {
          limite[j] = (uint16_t)_cor1[j];
          _sensValueRange[j] = (uint16_t)(_cor2[j] - _cor1[j]);
        } 
        else
        {
          limite[j] = (uint16_t)_cor2[j];
          _sensValueRange[j] = (uint16_t)(_cor1[j] - _cor2[j]);
        }

        Serial.print(j);
        Serial.print(" idx tem limite ");
        Serial.print(limite[j]);
        Serial.print(" com variacao original de ");
        Serial.println(_sensValueRange[j]);
      }
      _inicio = 0;

      for (int k=0; k < 30; k++) //  pisca o led 30x em 3 seg. Leu o preto e definiu o limite!!
      { 
        digitalWrite(led, HIGH);
        delay(50);
        digitalWrite(led, LOW);
        delay(50);
      }
    }
  }
}


