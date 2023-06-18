/* Giroscópio - Codigo*/

#include "Arduino.h"
#include <MPU6050_tockn.h>
#include <Wire.h>
#include "Giros.h"

MPU6050 mpu6050(Wire);

Giros::Giros() // Constructor
{

}

void Giros::setup() // Chamado no Setup()
{
    Wire.begin();
    mpu6050.begin();
    mpu6050.calcGyroOffsets(true);
}

void Giros::run() // Comandos de rotina
{
 
}

void Giros::print() //
{
    mpu6050.update();
    Serial.print("posX: ");
    Serial.print(mpu6050.getAngleX());
    Serial.print(" posY: ");
    Serial.print(mpu6050.getAngleY());
    Serial.print(" posY: ");
    Serial.println(mpu6050.getAngleY());
}
