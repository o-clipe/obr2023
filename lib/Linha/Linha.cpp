/*Algoritimo para o robo seguir a linha - Codigo*/

#include "Arduino.h"
#include "Linha.h"
#include "Lum.h"
#include "Motor.h"
#include "Giros.h"

#define DELAYPOS 50
#define DELAYROT 50

#define Left 0
#define Middle 1
#define Right 2


Linha::Linha(Lum& lum_obj, Motor& motor_obj, Giros& giros_obj): _lum(lum_obj), _carro(motor_obj), _giros(giros_obj) // Constructor
{
  uint8_t ideal[5] = {0, 2, 5, 2, 0}; // Calibrar isso idealmente na hora
  int goodAlignment = 5;
  int goodSymmetry = 5;
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
  uint8_t *status = _lum.processedReadAll();
  uint8_t& ee = status[0];
  uint8_t& e = status[1];
  uint8_t& m = status[2];
  uint8_t& d = status[3];
  uint8_t& dd = status[4];
  int symmetryScore = (abs(((int)dd-ee))+1)*(abs(((int)d-e))+1) - 1;
  int alignmentScore = abs(((int)ideal[0]-dd)) + abs(((int)ideal[1]-d)) +
  abs(((int)ideal[2]-m)) + abs(((int)ideal[3]-ee)) + abs(((int)ideal[4]-ee));
  currentState = getState(status);

  if (symmetryScore <= goodSymmetry && alignmentScore <= goodAlignment)
  {
    lastStateIsCurrent = false;
    lastState = Middle;
    pos();
  } 
  else if (symmetryScore > goodSymmetry)
  {
    if (!lastStateIsCurrent)
    {
      lastState = currentState;
      lastStateIsCurrent = true;
    }
    
    testCurve(symmetryScore);
  }
  else if (alignmentScore > goodAlignment) // symmetry is good, alignment is bad
  {
    inPlace(alignmentScore); // Contar quantas vezes é chamado pq ele vai ativar num GAP
  }
  
}

void Linha::pos(uint16_t delay_=DELAYPOS)
{
  _carro.ligarReto();
  delay(delay_);
  _carro.parar();
  delay(5);
}

void Linha::npos(uint16_t delay_=DELAYPOS)
{
  _carro.ligarRe();
  delay(delay_);
  _carro.parar();
  delay(5);
}

void Linha::rot(uint16_t delay_=DELAYROT)
{
  _carro.ligarMotor(me);
  _carro.ligarMotor(mdr);
  delay(delay_);
  _carro.parar();
  delay(5);
}

void Linha::nrot(uint16_t delay_=DELAYROT)
{
  _carro.ligarMotor(mer);
  _carro.ligarMotor(md);
  delay(delay_);
  _carro.parar();
  delay(5);
}

uint8_t Linha::getState(uint8_t* state)
{
  if (state[1] < state[2] && state[2] > state[3]) return Middle;
  if (state[1] > state[2]) return Left;
  if (state[3] > state[2]) return Right;
  if (state[3] < state[2]) return Left;
  if (state[1] < state[2]) return Right;
  
}

void Linha::inPlace(int alignmentScore)
{
  if (lastState == Right)
  {
    rot();
  }
  if (lastState == Left)
  {
    nrot();
  }
  if (lastState == Middle) // Here comes complexity
  {

  }
}

void Linha::testCurve(int symmetryScore)
{
  if (lastState == Right)
  {
    npos();
    rot();
    pos();
  }
  if (lastState == Left)
  {
    npos();
    nrot();
    pos();
  }
}