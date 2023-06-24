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

void Giros::print() 
{
    mpu6050.update();
    Serial.print(" PITCH: ");
    Serial.print(mpu6050.getAngleX());
    Serial.print(" YAW: ");
    Serial.print(mpu6050.getAngleZ());
    Serial.print(" ROLL: ");
    Serial.print(mpu6050.getAngleY());
}


float Giros::girosRead(int option)
{
    mpu6050.update();
    switch(option){
        case PITCH:
            return mpu6050.getAngleX();
        case YAW:
            return mpu6050.getAngleZ();
        case ROLL:
            return mpu6050.getAngleY();
    }

}
