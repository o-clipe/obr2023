/*Algoritimo para o robo seguir a linha - Codigo*/

#include "Arduino.h"
#include "Linha.h"
#include "Lum.h"
#include "Motor.h"
#include "Giros.h"
#include "Cor.h"
#include "Som.h"
#include <Adafruit_VL53L0X.h>

#define LOX1_ADDRESS 0x30
#define LOX2_ADDRESS 0x31

#define SHT_LOX1 43
#define SHT_LOX2 45

#define None 0
#define Both 0
#define Esquerda 1
#define Direita 2

Adafruit_VL53L0X infraBaixo = Adafruit_VL53L0X();
Adafruit_VL53L0X infraAlto = Adafruit_VL53L0X();

VL53L0X_RangingMeasurementData_t measureBaixo;
VL53L0X_RangingMeasurementData_t measureAlto;


Linha::Linha(Lum& lum_obj, Motor& motor_obj, Giros& giros_obj, 
    Cor& corE_obj, Cor& corD_obj, Som& somE_obj, Som& somD_obj):                               // Constructor

_lum(lum_obj), _carro(motor_obj), _giros(giros_obj), 
_corE(corE_obj), _corD(corD_obj), _somE(somE_obj), _somD(somD_obj)
{
  #define md _carro._direito
  #define me _carro._esquerdo
  #define mdr _carro._direitoRe
  #define mer _carro._esquerdoRe
}


void Linha::setup() // Chamado no Setup()
{
  infraBaixo.begin();

  pinMode(SHT_LOX1, OUTPUT);
  pinMode(SHT_LOX2, OUTPUT);

  Serial.println(F("Shutdown pins inited..."));

  digitalWrite(SHT_LOX1, LOW);
  digitalWrite(SHT_LOX2, LOW);

  Serial.println(F("Both in reset mode...(pins are low)"));
  
  
  Serial.println(F("Starting..."));
  setID();
}

// Segue a Linha
void Linha::segueLinha()
{
  if (step%10 == 0)
  {
    infraBaixo.rangingTest(&measureBaixo, false); // pass in 'true' to get debug data printout!
    infraAlto.rangingTest(&measureAlto, false);
  }

  step += 1;
  bool *status = _lum.processedReadAll();
  bool& ee = status[0];
  bool& e = status[1];
  bool& m = status[2];
  bool& d = status[3];
  bool& dd = status[4];
  bool& te = status[5];
  bool& td = status[6];
  
  if (turnStep%18 == 1)
  {
    npos(60);
    turnStep += 1;
  }
  
  // Triggers
  if (colorTrigger)                              
  {
    long dir = _corD.readBranco();
    long esq = _corE.readBranco();
    if (esq > LIMITE_BRANCO && dir > LIMITE_BRANCO && esq < 90 && dir < 90)
    {
      turnAroundTrigger=true;
      _lastOutSeen = None;
    } else if(esq > LIMITE_BRANCO && esq < 90){
      if (forcedTurnTrigger && _lastOutSeen == Direita) {
        turnAroundTrigger=true;
        _lastOutSeen = None;
      } else {
        _lastOutSeen = Esquerda;
        forcedTurnTrigger = true;
        lastOutStep = step;
      }
    } else if(dir > LIMITE_BRANCO && dir < 90){
      if (forcedTurnTrigger && _lastOutSeen == Esquerda) {
        turnAroundTrigger=true;
        _lastOutSeen = None;
      } else {
        _lastOutSeen = Direita;
        forcedTurnTrigger = true;
        lastOutStep = step;
      }
    }
  }
  if (turnAroundTrigger) {
    delay(300);
    rot(180);
    delay(300);
    pos(30);
    turnAroundTrigger=false;
  }
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
  if (obstaculoTrigger) {
    if (!e || !d){
      rturn(150);
      pos(100);
      obstaculoTrigger=false;
      delayUniversal = DELAY;
    } else if (!ee || !dd) {
      pos();
    }
  }

  // if (somTrigger && step - somCapturedStep < 3) {
  //   float resultE = _somE.mediaRead();
  //   float resultD = _somD.mediaRead();
  //   if (resultE < 100 && resultD < 100) {
  //     rampaDeResgateTrigger = true;
  //   }
  //   somTrigger=false;
  //   somCapturedStep = step;
  // }

  if (dd && m || ee && m || ee && dd && m){                                 // Manipula _lastOutSeen e colorTrigger
    _corD.ledOn();
    _corE.ledOn();
    colorTrigger=true;
  }
  if (dd && !forcedTurnTrigger) {
    lastOutStep = step;
    _lastOutSeen = Direita;
  } else if (ee && !forcedTurnTrigger) {
    lastOutStep = step;
    _lastOutSeen = Esquerda;
  } else {
    if (step - lastOutStep > 80) {
      _lastOutSeen = None;
    }
  }

  if (!ee && !e && !m && !d && !dd && !te && !td){
    gapTrigger = true;
  }
  if (!dd && !ee && (step - lastOutStep > 6) ){
    colorTrigger = false;
    _corD.ledOff();
    _corE.ledOff();
  }
  if (measureAlto.RangeMilliMeter < 150 && step - obstaculoStep > 200) {
    delayUniversal = 40;
    obstaculoTrigger = true;
    obstaculoStep = step;
    npos(300);
    rotCooldownStep += 100;
    rot(90);
    pos(200);
    pos(200);
    rotCooldownStep += 100;
    nrot(90);
    pos(200);
    pos(200);
    pos(200);
    pos(90);
    rotCooldownStep += 100;
    nrot(90);
    infraBaixo.readRange();    
  } else if (measureBaixo.RangeMilliMeter < 100) {
    delayUniversal = 5;
    accelerateStep = step;
    girosTrigger = true;
  }
  if (step - accelerateStep > 30)
  {
    delayUniversal = DELAY;
  }

  // girosTrigger aqui em baixo pois deve overwrite declração acima  >> delayUniversal = 5;
  if (girosTrigger) {
    float pitch = _giros.girosRead(PITCH);
    Serial.println(PITCH);
    if (pitch < 15) {
      delayUniversal = 0;
      pos(20);
    } else {
      girosTrigger=false;
      if (delayUniversal == 0)
      {
        delayUniversal = DELAY;
      }
    }
  }
  
  // Movimentação
  if (m){
    noLineStep = 0;
  }
  if (e && d){                                    // Se as dois sensores da frente virem ao mesmo tempo, da um pulo pra frente
    pos();
    noLineStep = 0;
  } else if (e) {                                 // Se o sensor da esquerda disparou, vira pra direita
    if (straightLineTrigger){
      nrot(10);
    } else {
      lturn();
    }
    noLineStep = 0;
  } else if (d) {                                 // Se o sensor da direita disparou, vira pra esquerda
    if (straightLineTrigger){
      rot(10);
    } else {
      rturn();
    }
    noLineStep = 0;
  } else {  // !e && !d                           // Se não tem mais informação dos sensores da frente
    noLineStep += 1;
    if (te && td && _lastOutSeen && (noLineStep > 4 || forcedTurnTrigger)) {                   //  Se os sensores de tras ambos disparam - Rotaciona 90 graus caso _lastOutSeen tenha valor de lado.       
      forcedTurnTrigger=false;
      npos();
      if(_lastOutSeen == Direita){
        rot(90);
        _lastOutSeen = None;
        delay(500);
        npos(100);
      } else if (_lastOutSeen == Esquerda) {
        nrot(90);
        _lastOutSeen = None;
        delay(500);
        npos(100);
      }
    } else if (te && _lastOutSeen == Esquerda && (noLineStep > 4 || forcedTurnTrigger)) {      // Se o sensor tras esquerda dispara e _lastOutSeen era esquerda, Rotaciona -90 graus.
      forcedTurnTrigger=false;
      nrot(90);
      _lastOutSeen = None;
      delay(500);
      npos(100);
    } else if (td && _lastOutSeen == Direita && (noLineStep > 4 || forcedTurnTrigger)) {       // Se o sensor tras direita dispara e _lastOutSeen era direita, Rotaciona 90 graus.
      forcedTurnTrigger=false;
      rot(90);
      _lastOutSeen = None;
      delay(500);
      npos(100);
    } else {  
      straightLineTrigger = true;                                        // Se não tem sinal para curva fechada (_lastOutSeen = 0), segue reto.
      pos();
    }
  }

}







// Unidades Mínimas de Movimento

void Linha::pos(int time_)  // Avança para frente
{
  _carro.ligarReto();
  delay(time_);
  _carro.parar();
  delay(delayUniversal);
}

void Linha::npos(int time_)  // Volta em ré
{
  _carro.ligarRe();
  delay(time_);
  _carro.parar();
  delay(delayUniversal);   
}

void Linha::rot(float graus)  // Rotaciona do sentido horario
{
  if (graus > 30) {
    if (!(step - rotCooldownStep >= 10)) 
    {
      return;
    }
    delay(300);
  }
  for (int i=0; i < graus*FATOR_ANGULO; i++)
  {
    _carro.ligarMotor(me);
    _carro.ligarMotor(mdr);
    delay(DELAYROT);
    _carro.parar();
    delay(delayUniversal);;   
  }
  straightLineTrigger = false;
  rotCooldownStep = step;
}

void Linha::nrot(float graus)  // Rotaciona do sentido antihorario
{
  if (graus > 30) {
    if (!(step - rotCooldownStep >= 10)) 
    {
      return;
    }
    delay(300);
  }

  for (int i=0; i < graus*FATOR_ANGULO; i++)
  {
    _carro.ligarMotor(md);
    _carro.ligarMotor(mer);
    delay(DELAYROT);
    _carro.parar();
    delay(delayUniversal);
  }
  straightLineTrigger = false;
  rotCooldownStep = step;
  
  
}

void Linha::rturn(int time_)  // Vira pra direita
{
  turnStep += 1;
  _carro.ligarMotor(me);
  delay(time_);
  _carro.parar();
  delay(delayUniversal);
  straightLineTrigger = false;
}

void Linha::lturn(int time_)  // vira pra esquerda
{
  turnStep += 1;
  _carro.ligarMotor(md);
  delay(time_);
  _carro.parar();
  delay(delayUniversal);
  straightLineTrigger = false;
}

void Linha::setID() {
  // all reset
  digitalWrite(SHT_LOX1, LOW);    
  digitalWrite(SHT_LOX2, LOW);
  delay(10);
  // all unreset
  digitalWrite(SHT_LOX1, HIGH);
  digitalWrite(SHT_LOX2, HIGH);
  delay(10);

  // activating LOX1 and resetting LOX2
  digitalWrite(SHT_LOX1, HIGH);
  digitalWrite(SHT_LOX2, LOW);

  // initing LOX1
  if(!infraBaixo.begin(LOX1_ADDRESS)) {
    Serial.println(F("Failed to boot first VL53L0X"));
    while(1);
  }
  delay(10);

  // activating LOX2
  digitalWrite(SHT_LOX2, HIGH);
  delay(10);

  //initing LOX2
  if(!infraAlto.begin(LOX2_ADDRESS)) {
    Serial.println(F("Failed to boot second VL53L0X"));
    while(1);
  }
}