/* Biblioteca Template - Codigo*/

#include "Arduino.h"
#include "Motor.h"

#define VELOCIDADE 96  //max 255
#define VELDIREITO 1.2
#define VELESQUERDO 1.0

Motor::Motor(uint8_t direito, uint8_t esquerdo, uint8_t direitoRe, uint8_t esquerdoRe, uint8_t enEsquerdo, uint8_t enDireito) // Constructor
{
    _direito = direito;
    _esquerdo = esquerdo;
    _direitoRe = direitoRe;
    _esquerdoRe = esquerdoRe;
    _enEsquerdo = enEsquerdo;
    _enDireito = enDireito;
    velocidade = VELOCIDADE;
    #define d _direito
    #define e _esquerdo
    #define er _direitoRe
    #define dr _esquerdoRe
}


void Motor::setup() // Chamado no Setup()
{
    pinMode(_direito, OUTPUT);
    pinMode(_esquerdo, OUTPUT);
    pinMode(_direitoRe, OUTPUT);
    pinMode(_esquerdoRe, OUTPUT);
    pinMode(_enEsquerdo, OUTPUT);
    pinMode(_enDireito, OUTPUT);
}


void Motor::ligarMotor(uint8_t motor, uint8_t vel=0)
{
    if (vel != 0)
    {
        analogWrite(_enEsquerdo, (uint8_t)vel*VELESQUERDO);
        analogWrite(_enDireito, (uint8_t)vel*VELDIREITO);
    }
    else
    {
        analogWrite(_enEsquerdo, (uint8_t)velocidade*VELESQUERDO);
        analogWrite(_enDireito, (uint8_t)velocidade*VELDIREITO);
    }
    digitalWrite(motor, HIGH);
}


void Motor::desligarMotor(uint8_t motor)
{
    digitalWrite(motor, LOW);
}


void Motor::parar()
{
    desligarMotor(d);
    desligarMotor(e);
    desligarMotor(dr);
    desligarMotor(er);
}

void Motor::ligarReto(uint8_t vel=0)
{
    desligarMotor(dr);
    desligarMotor(er);
    ligarMotor(d, vel);
    ligarMotor(e, vel);
}

void Motor::ligarRe(uint8_t vel=0)
{
    desligarMotor(d);
    desligarMotor(e);
    ligarMotor(dr, vel);
    ligarMotor(er, vel);
}

