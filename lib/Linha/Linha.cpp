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
    Cor& corE_obj, Cor& corD_obj):                               // Constructor

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


// Segue a Linha
void Linha::segueLinha()
{
  Serial.println(_lastOutSeen);

  step += 1;
  bool *status = _lum.processedReadAll();
  bool& ee = status[0];
  bool& e = status[1];
  bool& d = status[2];
  bool& dd = status[3];
  bool& te = status[4];
  bool& td = status[5];
  
  if (turnStep%7 == 1)
  {
    npos(40);
    turnStep += 1;
  }
  
  // Triggers
  // if (colorTrigger)                              
  // {
  //   if(_corE.colorRead() == Green){
  //     _lastOutSeen = Esquerda;
  //     lastOutStep = step;
  //   }
  //   if(_corD.colorRead() == Green){
  //     _lastOutSeen = Direita;
  //     lastOutStep = step;
  //   }
  // }
  if (gapTrigger) {
    if (e) {                                 // Se o sensor da esquerda disparou, vira pra direita
      lturn();
      gapTrigger = false;
    } else if (d) {                                 // Se o sensor da direita disparou, vira pra esquerda
      rturn();
      gapTrigger = false;
    } else if (ee){
      lturn(45);
      pos(100);
      gapTrigger = false;
    } else if (dd) {
      rturn(45);
      pos(100);
      gapTrigger = false;
    }
    
  }

  if (dd && ee || (step - lastOutStep < 20 && ee && _lastOutSeen == Direita) || (step - lastOutStep < 20 && dd && _lastOutSeen == Esquerda)) {                                 // Manipula _lastOutSeen e colorTrigger
    _lastOutSeen = Both;
    encruzilhadaStep = step;
    colorTrigger = true;
    _corD.ledOn();
    _corE.ledOn();
  } else if (dd && step - encruzilhadaStep > 20) {
    lastOutStep = step;
    _lastOutSeen = Direita;
  } else if (ee && step - encruzilhadaStep > 20) {
    lastOutStep = step;
    _lastOutSeen = Esquerda;
  } else {
    if (step - lastOutStep > 80) {
      _lastOutSeen = None;
    }
  }

  if (!ee && !e && !d && !dd && !te && !td){
    gapTrigger = true;
  }
  // if (!dd && !ee && lastOutStep < 13){
  //   colorTrigger = false;
  //   _corD.ledOff();
  //   _corE.ledOff();
  // }

  // Movimentação
  if (e && d){                                    // Se as dois sensores da frente virem ao mesmo tempo, da um pulo pra frente
    pos();
  } else if (e) {                                 // Se o sensor da esquerda disparou, vira pra direita
    lturn();
  } else if (d) {                                 // Se o sensor da direita disparou, vira pra esquerda
    rturn();
  } else {  // !e && !d                           // Se não tem mais informação dos sensores da frente
    if (te && td && _lastOutSeen) {                   //  Se os sensores de tras ambos disparam - Rotaciona 90 graus caso _lastOutSeen tenha valor de lado.       
      npos();
      if(_lastOutSeen == Direita){
        rot(90);
        _lastOutSeen = None;
      } else if (_lastOutSeen == Esquerda) {
        nrot(90);
        _lastOutSeen = None;
      }
    } else if (te && _lastOutSeen == Esquerda) {      // Se o sensor tras esquerda dispara e _lastOutSeen era esquerda, Rotaciona -90 graus.
      npos(DELAYPOS*1.5);
      nrot(90);
      _lastOutSeen = None;
    } else if (td && _lastOutSeen == Direita) {       // Se o sensor tras direita dispara e _lastOutSeen era direita, Rotaciona 90 graus.
      npos(DELAYPOS*1.5);
      rot(90);
      _lastOutSeen = None;
    } else {                                          // Se não tem sinal para curva fechada (_lastOutSeen = 0), segue reto.
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

void Linha::rot(float graus)  // Rotaciona do sentido horario
{
  if (step - rotCooldownStep >= 20) {
    for (int i=0; i < graus*FATOR_ANGULO; i++)
    {
      _carro.ligarMotor(me);
      _carro.ligarMotor(mdr);
      delay(DELAYROT);
      _carro.parar();
      delay(DELAY);
    }
    rotCooldownStep = step;
  }
  
}

void Linha::nrot(float graus)  // Rotaciona do sentido antihorario
{
  if (step - rotCooldownStep >= 20) {
    for (int i=0; i < graus*FATOR_ANGULO; i++)
    {
      _carro.ligarMotor(md);
      _carro.ligarMotor(mer);
      delay(DELAYROT);
      _carro.parar();
      delay(DELAY);
    }
    rotCooldownStep = step;
  }
  
}

void Linha::rturn(uint16_t time_)  // Vira pra direita
{
  turnStep += 1;
  _carro.ligarMotor(me);
  delay(time_);
  _carro.parar();
  delay(DELAY);
}

void Linha::lturn(uint16_t time_)  // vira pra esquerda
{
  turnStep += 1;
  _carro.ligarMotor(md);
  delay(time_);
  _carro.parar();
  delay(DELAY);
}
