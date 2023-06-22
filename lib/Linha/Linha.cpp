/*Algoritimo para o robo seguir a linha - Codigo*/

#include "Arduino.h"
#include "Linha.h"
#include "Lum.h"
#include "Motor.h"
#include "Giros.h"

#define Reto 0
#define VirarEsquerda 1
#define VirarDireita 2


Linha::Linha(Lum& lum_obj, Motor& motor_obj, Giros& giros_obj): _lum(lum_obj), _carro(motor_obj), _giros(giros_obj) // Constructor
{
  #define md _carro._direito
  #define me _carro._esquerdo
  #define mdr _carro._direitoRe
  #define mer _carro._esquerdoRe
  _modo = Reto;
}


void Linha::setup() // Chamado no Setup()
{

}


bool Linha::segueLinha()
{
  int* status =  _lum.processedReadAll();
  int& ee = status[0];
  int& e = status[1];
  int& d = status[2];
  int& dd = status[3];
  int& te = status[4];
  int& td = status[5];
  if (te > 0 && td > 0)
  {
    _encruzilhada = true;
   _carro.ligarReto();
   delay(500);
   _carro.parar();
  }
  else if (te > 0)
  {
     _curvaFechadaDetectada = VirarEsquerda;
  }
  else if (td > 0)
  {
     _curvaFechadaDetectada = VirarEsquerda;
  }
  else if (e > 0)
  {
     pararSeTroucouModo(VirarEsquerda);
    _carro.ligarMotor(md, VELOCIDADEDECURVA);
  }
  else if(d > 0)
  {
    pararSeTroucouModo(VirarEsquerda);
    _carro.ligarMotor(me, VELOCIDADEDECURVA);
  }
  else if(e == 0 && d == 0)
  {
    if (te > 0 && td > 0)
    {
      _carro.parar();
      // girar90Graus();
    }
    _carro.ligarRe();
  }
  else
  {
    pararSeTroucouModo(Reto);
    _carro.ligarReto();
  }
}

void Linha::pararSeTroucouModo(uint8_t modo)
{
  if (modo != _modo)
  {
    _carro.parar();
  }
  _modo = modo;
}