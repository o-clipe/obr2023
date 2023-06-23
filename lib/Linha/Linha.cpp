/*Algoritimo para o robo seguir a linha - Codigo*/

#include "Arduino.h"
#include "Linha.h"
#include "Lum.h"
#include "Motor.h"
#include "Giros.h"
#include "Cor.h"

#define None 0
#define Both 0
#define Esquerda 1
#define Direita 2

Linha::Linha(Lum& lum_obj, Motor& motor_obj, Giros& giros_obj, 
    Cor& corE_obj, Cor& corD_obj):  // Constructor

_lum(lum_obj), _carro(motor_obj), _giros(giros_obj), 
_corE(corE_obj), _corD(corD_obj) 
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
  step += 1;
  bool *status = _lum.processedReadAll();
  bool& ee = status[0];
  bool& e = status[1];
  bool& d = status[2];
  bool& dd = status[3];
  bool& te = status[4];
  bool& td = status[5];
  
  // Triggers
  if (ColorTrigger)
  {
    if(_corE.colorRead() == Green){
      _lastOutSeen = Esquerda;
      lastOutStep = step;
    }
    if(_corD.colorRead() == Green){
      _lastOutSeen = Direita;
      lastOutStep = step;
    }
  }

  if (dd && ee) {
    _lastOutSeen = Both;
    encruzilhadaStep = step;
    ColorTrigger = true;
  } else if (dd && step - encruzilhadaStep > 10) {
    lastOutStep = step;
    _lastOutSeen = Direita;
    ColorTrigger = false;
  } else if (ee && step - encruzilhadaStep > 10) {
    lastOutStep = step;
    _lastOutSeen = Esquerda;
    ColorTrigger = false;
  } else {
    if (step - lastOutStep > 100) {
      _lastOutSeen = None;
    }
  }


  // Movimentação
  if (e && d){
    pos();
  } else if (e) {
    rturn();
  } else if (d) {
    lturn();
  } else {  // !e && !d
    if (te && td && _lastOutSeen) 
    {
      npos();
      if(_lastOutSeen == Direita){
        rot();
      } else if (_lastOutSeen == Esquerda) {
        nrot();
      }
    }
    else 
    {
      pos();
    }
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

  
  while (fmin(fmod(fabs(360+_giros.girosRead()[YAW]-yawAtStart), 360), fmod(fabs(_giros.girosRead()[YAW]-yawAtStart), 360)) < 90.)
  {
    _carro.ligarMotor(me);
    _carro.ligarMotor(mdr);
    delay(time_);
    _carro.parar();
    delay(DELAY);
  }
}

void Linha::nrot(uint16_t time_)  // Rotaciona do sentido antihorario
{
  float yawAtStart = _giros.girosRead()[YAW];
  
  while (fmin(fmod(fabs(360+_giros.girosRead()[YAW]-yawAtStart), 360), fmod(fabs(_giros.girosRead()[YAW]-yawAtStart), 360)) < 90.)
  {
    _carro.ligarMotor(md);
    _carro.ligarMotor(mer);
    delay(time_);
    _carro.parar();
    delay(DELAY);
  }
}

void Linha::rturn(uint16_t time_)  // Vira pra direita
{
  _carro.ligarMotor(me);
  delay(time_);
  _carro.parar();
  delay(DELAY);
}

void Linha::lturn(uint16_t time_)  // vira pra esquerda
{
  _carro.ligarMotor(md);
  delay(time_);
  _carro.parar();
  delay(DELAY);
}
