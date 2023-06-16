/* Sensores de Luminosidade - Codigo*/

#include "Arduino.h"
#include "Lum.h"

#define led LED_BUILTIN

Lum::Lum(uint8_t ee, uint8_t e, uint8_t m, uint8_t d, uint8_t dd) // Constructor
{
    _ee = ee;
    _e = e;
    _m = m;
    _d = m;
    _dd = d;

    memoriaLastIdx = 0;
    _inicio = 1;

}

void Lum::setup() // Chamado no Setup()
{
  pinMode(led, OUTPUT);
}

void Lum::run() // Roda comandos de rotina
{
  setMemoria();
  Serial.print(_inicio);
  if (_inicio > 0){
    defineLimite();
  }

}

uint16_t Lum::processedRead(uint8_t sens, int base=5)
{
  if (!limite[0]){
    return analogRead(sens);
  }
  uint8_t sensores[5] = {_ee, _e, _m, _d, _dd};
  int idx = -1;
  for (int i = 0; i < 5; i++) {
    if (sens == sensores[i]) {
      idx = i;
    }
  }
  float limiteSens = (float)limite[idx];
  float read = (float)analogRead(sens);
  float range = (float)_sensValueRange[idx];
  float b = (float)base;

  float normalizado = (read - limiteSens)/ _sensValueRange[idx] * b;
  Serial.print(normalizado);
  Serial.print("float ");
  uint16_t rtrn = normalizado;
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
  if (!checkLast){
    checkLast = 5000/MILLISTEP; // checa ultimos 5seg
  }
  int branco[5];
  int preto[5];
  bool passou = true;
  if (millis() > 5000){
    int max[5] = {0, 0, 0, 0, 0};
    int min[5] = {1001, 1001, 1001, 1001, 1001};
    int idx = 0;
    for (int i=0; i < checkLast; i++){
      idx = i+memoriaLastIdx-checkLast;
      for (int j=0; j < 5; j++){
        if(memoria[idx][j] > max[j]){
          max[j] = memoria[idx][j];
        }
        if(memoria[idx][j] < min[j]){
          min[j] = memoria[idx][j];
        }
      }
    }

    _inicio += 1;
    for (int j=0; j < 5; j++){
      if (max[j] - min[j] > 50 || min[0] == 0){
        _inicio -= 1;
        passou = false;
        break;
      }
    }
    if (_inicio == 2 && passou){
      Serial.println("passou 2");
      branco[5] = min[5];
      for (uint32_t mem=0; mem < MEMSIZE; mem++){
        for (uint8_t s=0; s < 5; s++){
          memoria[mem][s] = 0;
        }
      }
      for (int k=0; k < 20; k++){ // pisca o led 20x em 2 seg. Leu o branco!!!!
        digitalWrite(led, HIGH);
        delay(50);
        digitalWrite(led, LOW);
        delay(50);
      }
    } 
    if (_inicio == 3 && passou) {
      Serial.println("passou 3");
      preto[5] = max[5];
      for (int j=0; j < 5; j++){
        limite[j] = branco[j] + (preto[j] - branco[j]) / 2;
        _sensValueRange[j] = preto[j] - branco[j];
      }
      _inicio = 0;

      for (int k=0; k < 30; k++){ // pisca o led 30x em 3 seg. Leu o preto e definiu o limite!!
        digitalWrite(led, HIGH);
        delay(50);
        digitalWrite(led, LOW);
        delay(50);
      }
    }
  }
}


