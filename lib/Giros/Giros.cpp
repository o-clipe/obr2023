/* Giroscópio - Codigo*/

#include "Arduino.h"
#include <MPU6050_tockn.h>
#include <Wire.h>
#include "Giros.h"

MPU6050 mpu6050(Wire);

Giros::Giros() // Constructor
{
    // #define x 0
    // #define y 1
    // #define z 2
}


void Giros::setup() // Chamado no Setup()
{
    Wire.begin();
    mpu6050.begin();
    mpu6050.calcGyroOffsets(true);
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
