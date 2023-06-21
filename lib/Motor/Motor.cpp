/* Biblioteca Template - Codigo*/

#include "Arduino.h"
#include "Motor.h"


Motor::Motor(uint8_t direito, uint8_t esquerdo, uint8_t direitoRe, uint8_t esquerdoRe, uint8_t en1, uint8_t en2) // Constructor
{
    _direito = direito;
    _esquerdo = esquerdo;
    _direitoRe = direitoRe;
    _esquerdoRe = esquerdoRe;
    _en1 = en1;
    _en2 = en2;
    velocidade = DEFAULTVELOCITY;
}


void Motor::setup() // Chamado no Setup()
{
    pinMode(_direito, OUTPUT);
    pinMode(_esquerdo, OUTPUT);
    pinMode(_direitoRe, OUTPUT);
    pinMode(_esquerdoRe, OUTPUT);
    pinMode(_en1, OUTPUT);
    pinMode(_en2, OUTPUT);
    analogWrite(_en1, DEFAULTVELOCITY);
    analogWrite(_en2, DEFAULTVELOCITY);
}


void Motor::run() // Comandos de rotina
{
 
}


uint8_t Motor::_traduzStrParaPorta(String& arg)
{
    if (arg == "d") return _direito;
    if (arg == "e") return _esquerdo;
    if (arg == "er") return _esquerdoRe;
    if (arg == "dr") return _direitoRe;
    if (arg == "direito") return _direito;
    if (arg == "esquerdo") return _esquerdo;
    if (arg == "esquerdo_re") return _direitoRe;
    if (arg == "direito_re") return _esquerdoRe;

}


void Motor::ligarMotor(String m, uint8_t vel=0)
{
    if (vel != 0)
    {
        analogWrite(_en1, (uint8_t)vel*VELESQUERDO);
        analogWrite(_en2, (uint8_t)vel*VELDIREITO);
    }
    else
    {
        analogWrite(_en1, (uint8_t)velocidade*VELESQUERDO);
        analogWrite(_en2, (uint8_t)velocidade*VELDIREITO);
    }
    digitalWrite(_traduzStrParaPorta(m), HIGH);
}


void Motor::desligarMotor(String m)
{
    digitalWrite(_traduzStrParaPorta(m), LOW);
}


void Motor::parar()
{
    desligarMotor("d");
    desligarMotor("e");
    desligarMotor("dr");
    desligarMotor("er");
}

void Motor::ligarReto(uint8_t vel=0)
{
    desligarMotor("dr");
    desligarMotor("er");
    ligarMotor("d", vel);
    ligarMotor("e", vel);
}

void Motor::ligarRe(uint8_t vel=0)
{
    desligarMotor("d");
    desligarMotor("e");
    ligarMotor("dr", vel);
    ligarMotor("er", vel);
}

