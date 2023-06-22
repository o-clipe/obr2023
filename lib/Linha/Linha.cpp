/*Algoritimo para o robo seguir a linha - Codigo*/

#include "Arduino.h"
#include "Linha.h"
#include "Lum.h"
#include "Motor.h"
#include "Giros.h"

#define Meio 0
#define Both 0
#define Esquerda 1
#define Direita 2

Linha::Linha(Lum& lum_obj, Motor& motor_obj, Giros& giros_obj): _lum(lum_obj), _carro(motor_obj), _giros(giros_obj) // Constructor
{
  #define md _carro._direito
  #define me _carro._esquerdo
  #define mdr _carro._direitoRe
  #define mer _carro._esquerdoRe
}


void Linha::setup() // Chamado no Setup()
{

}


bool Linha::segueLinha()
{
  bool *status = _lum.processedReadAll();
  bool& ee = status[0];
  bool& e = status[1];
  bool& d = status[2];
  bool& dd = status[3];
  bool& te = status[4];
  bool& td = status[5];
  
  // Triggers
  
  if (dd && ee) {
    _lastOutSeen = Both;
  } else if (dd) {
    _lastOutSeen = Direita;
  } else if (ee) {
    _lastOutSeen = Esquerda;
  }

  if (e)
  {
    rturn();
  }
  else if(d)
  {
    lturn();
  }
  else if(!e && !d)
  {
    if (te && td)
    {
      
    }
    _carro.ligarRe();
  }
  else
  {
    pos();
  }
}







// Unidades Mínimas de Movimento

void Linha::pos(uint16_t time_)  // Avança para frente
{
  _carro.ligarReto();
  delay(time_);
  _carro.parar();
  delay(DELAY);
}

void Linha::npos(uint16_t time_)  // Volta em ré
{
  _carro.ligarRe();
  delay(time_);
  _carro.parar();
  delay(DELAY);
}

void Linha::rot(uint16_t time_)  // Rotaciona do sentido horario
{
  float yawAtStart = _giros.girosRead()[YAW];
  
  while (fabs(_giros.girosRead()[YAW]-yawAtStart < 90.))
  {
    _carro.ligarMotor(me);
    _carro.ligarMotor(mdr);
    delay(DELAYROT);
    _carro.parar();
    delay(DELAY);
  }
}

void Linha::nrot(uint16_t time_)  // Rotaciona do sentido antihorario
{
  float yawAtStart = _giros.girosRead()[YAW];
  
  while (fabs(_giros.girosRead()[YAW]-yawAtStart < 90.))
  {
    _carro.ligarMotor(md);
    _carro.ligarMotor(mer);
    delay(DELAYROT);
    _carro.parar();
    delay(DELAY);
  }
}

void Linha::rturn(uint16_t time_)  // Vira pra direita
{
  _carro.ligarMotor(mer);
  delay(time_);
  _carro.parar();
  delay(DELAY);
}

void Linha::lturn(uint16_t time_)  // vira pra esquerda
{
    _carro.ligarMotor(mdr);
  delay(time_);
  _carro.parar();
  delay(DELAY);
}
