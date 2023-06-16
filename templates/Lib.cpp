/* Biblioteca Template - Codigo*/

#include "Arduino.h"
#include "Lib.h"

Lib::Lib(int pin) // Constructor
{
  _pin = pin;
}

void Lib::setup() // Chamado no Setup()
{
  pinMode(_pin, OUTPUT);
}

void Lib::dot()
{
  digitalWrite(_pin, HIGH);
  delay(250);
  digitalWrite(_pin, LOW);
  delay(250);  
}


void Lib::dash()
{
  digitalWrite(_pin, HIGH);
  delay(1000);
  digitalWrite(_pin, LOW);
  delay(250);
}