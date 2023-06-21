/*Algoritimo para o robo seguir a linha - Codigo*/

#include "Arduino.h"
#include "Linha.h"
#include "Lum.h"
#include "Motor.h"
#include "Giros.h"


Linha::Linha(Lum& lum_obj, Motor& motor_obj, Giros& giros_obj): _lum(lum_obj), _carro(motor_obj), _giros(giros_obj) // Constructor
{

}


void Linha::setup() // Chamado no Setup()
{

}


void Linha::run() // Comandos de rotina
{
  segueLinha();
}




bool Linha::segueLinha()
{

}


 