/* Giroscópio - Codigo*/

#include "Arduino.h"
#include <MPU6050_tockn.h>
#include <Wire.h>
#include "Giros.h"

MPU6050 mpu6050(Wire);

Giros::Giros() // Constructor
{
    memoriaLastIdx = 0;
}


void Giros::setup() // Chamado no Setup()
{
    Wire.begin();
    mpu6050.begin();
    mpu6050.calcGyroOffsets(true);
}


void Giros::run() // Comandos de rotina
{
    setMemoria();
}


void Giros::print() //
{
    mpu6050.update();
    Serial.print("posX: ");
    Serial.print(mpu6050.getAngleX());
    Serial.print(" posY: ");
    Serial.print(mpu6050.getAngleY());
    Serial.print(" posZ: ");
    Serial.println(mpu6050.getAngleZ());
}


float* Giros::girosRead()
{
    _xyz[0] = mpu6050.getAngleX();
    _xyz[1] = mpu6050.getAngleY();
    _xyz[2] = mpu6050.getAngleZ();
    return _xyz;
}


void Giros::setMemoria()
{
  uint16_t read = millis()%(MEMSIZE*MILLISTEP);
  uint32_t idx = (read - read%MILLISTEP)/MILLISTEP;

  girosRead();
  memoria[idx][0] = _xyz[0];
  memoria[idx][1] = _xyz[1];
  memoria[idx][2] = _xyz[2];

  memoriaLastIdx = idx;
}


void Giros::defineVariacaoPadrao()
{
    float max[3] = {-100, -100, -100};
    float min[3] = {100, 100, 100}; 
    for (uint8_t i=0; i < 10; i++)
    {
        for (uint8_t j=0; j < 3; j++)
        {
            if (memoria[i][j] > max[j])
            {
                max[j] = memoria[i][j];
            }
            if (memoria[i][j] < min[j])
            {
                min[j] = memoria[i][j];
            }
        }
    }

    _variacaoPadrao[0] = max[0] - min[0];
    _variacaoPadrao[1] = max[1] - min[1];
    _variacaoPadrao[2] = max[2] - min[2];
}

bool Giros::detectaVariacao(char eixo)
{
    uint8_t anterior = (memoriaLastIdx+MEMSIZE-1)%MEMSIZE;
    uint8_t e = _traduzCharParaIdx(eixo);
    if (fabs(memoria[memoriaLastIdx][e] - memoria[anterior][e]) >= _variacaoPadrao[e]*FATORERROVARIACAO)
    {
        return true;
    }
    return false;
}

uint8_t _traduzCharParaIdx(char arg)
{
    if (arg == 'x') return 0;
    if (arg == 'y') return 1;
    if (arg == 'z') return 2;
    if (arg == 'X') return 0;
    if (arg == 'Y') return 1;
    if (arg == 'Z') return 2;
}