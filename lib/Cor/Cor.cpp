/* Cor - Codigo*/

#include "Arduino.h"
#include "Cor.h"


Cor::Cor(uint8_t s0, uint8_t s1, uint8_t s2, uint8_t s3, uint8_t out, uint8_t led) // Constructor
{
    _s0 = s0;
    _s1 = s1;
    _s2 = s2;
    _s3 = s3;
    _out = out;
    _led = led;
}


void Cor::setup() // Chamado no Setup()
{
  pinMode(_s0, OUTPUT);
  pinMode(_s1, OUTPUT);
  pinMode(_s2, OUTPUT);
  pinMode(_s3, OUTPUT);
  pinMode(_out, INPUT);
  pinMode(_led, OUTPUT);

  digitalWrite(_s0, HIGH);
  digitalWrite(_s1, LOW);
  digitalWrite(_led, HIGH);
}


uint8_t* Cor::rgbaRead()
{
    pinMode(_s2, HIGH);
    pinMode(_s3, HIGH);
    _rgba[1] = pulseIn(_out, LOW);   

    pinMode(_s2, LOW);
    _rgba[2] = pulseIn(_out, LOW);

    pinMode(_s3, LOW);
    _rgba[0] = pulseIn(_out, LOW);

    pinMode(_s2, HIGH);
    _rgba[3] = pulseIn(_out, LOW);
}

uint8_t Cor::rgbaToColorInt(uint8_t* rgba)
{
    if (rgba[3] < LIMITE_BRANCO) return None;
    if (rgba[0] < rgba[1] && rgba[0] < rgba[2]) return Red;
    if (rgba[1] < rgba[0] && rgba[1] < rgba[2]) return Green;
    if (rgba[2] < rgba[0] && rgba[2] < rgba[1]) return Blue;
}


uint8_t Cor::rgbaToColorInt(uint8_t* rgba)
{
    return rgbaToColorInt(rgbaRead());
}


/*
    Photodiode colors
         S2   S3
   RED   LOW  LOW
   BLUE  LOW  HIGH
   NONE  HIGH LOW
   GREEN HIGH HIGH

    Frequency scaling
         S0   S1
   0     LOW  LOW
   2%    LOW  HIGH
   20%   HIGH LOW  <- Mais Comum
   100%  HIGH HIGH
*/