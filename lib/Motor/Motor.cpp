/* Motor - Codigo*/

#include "Arduino.h"
#include "Motor.h"

Motor::Motor(uint8_t direito, uint8_t esquerdo, uint8_t direitoRe, uint8_t esquerdoRe, uint8_t enEsquerdo, uint8_t enDireito) // Constructor
{
    _direito = direito;
    _esquerdo = esquerdo;
    _direitoRe = direitoRe;
    _esquerdoRe = esquerdoRe;
    _enEsquerdo = enEsquerdo;
    _enDireito = enDireito;
    #define md _direito
    #define me _esquerdo
    #define mdr _direitoRe
    #define mer _esquerdoRe
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


void Motor::ligarMotor(uint8_t motor, uint8_t vel)
{
    if (vel)
    {
        analogWrite(_enEsquerdo, (uint8_t)vel*VELOCIDADE_ESQUERDO);
        analogWrite(_enDireito, (uint8_t)vel*VELOCIDADE_DIREITO);
    }
    else
    {
        analogWrite(_enEsquerdo, (uint8_t)VELOCIDADE*VELOCIDADE_ESQUERDO);
        analogWrite(_enDireito, (uint8_t)VELOCIDADE*VELOCIDADE_DIREITO);
    }
    digitalWrite(motor, HIGH);
}


void Motor::desligarMotor(uint8_t motor)
{
    digitalWrite(motor, LOW);
}


void Motor::parar()
{
    desligarMotor(md);
    desligarMotor(me);
    desligarMotor(mdr);
    desligarMotor(mer);
}

void Motor::ligarReto(uint8_t vel)
{
    desligarMotor(mdr);
    desligarMotor(mer);
    ligarMotor(md, vel);
    ligarMotor(me, vel);
}

void Motor::ligarRe(uint8_t vel)
{
    desligarMotor(md);
    desligarMotor(me);
    ligarMotor(mdr, vel);
    ligarMotor(mer, vel);
}

