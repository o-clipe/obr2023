/*Algoritimo para o robo seguir a linha*/

#ifndef Linha_h
#define Linha_h

#include "Arduino.h"
#include "Lum.h"
#include "Motor.h"
#include "Giros.h"
#include "Cor.h"
#include "Som.h"
#include <Adafruit_VL53L0X.h>

#define DELAYPOS 10
#define DELAYROT 27 // Constante, não tocar
#define DELAYTURN 15
#define DELAY 15
#define FATOR_ANGULO 0.087


class Linha
{
  public:
    Linha(Lum& lum_obj, Motor& motor_obj, Giros& giros_obj, Cor& corE_obj, Cor& corD_obj, Som& somE_obj, Som& somD_obj);
    void setup();
    void segueLinha();
    int delayUniversal=DELAY;

    uint8_t _lastOutSeen = 0;  // Entre dd, ee, dd && ee, qual foi o último visto. Direciona rots (rotacionações em 90 graus)

    // Triggers -- Ifs que mudam a rotina padrão do segueLinha
    bool colorTrigger=false;
    bool obstaculoTrigger=false;
    bool rampaTrigger=false;
    bool rampaDeResgateTrigger=false;
    bool gapTrigger=false;
    bool straightLineTrigger=false;
    bool somTrigger=false;
    bool forcedTurnTrigger=false;
    bool turnAroundTrigger=false;
    bool girosTrigger=false;

    // Steps -- O cálculo de tempo / progresso.
    unsigned int step=0; // step de agora. É atualizado a cada ciclo.
    unsigned int lastOutStep=0; // step (passado) +- steps e.g. (steps+0 == ~100) -> tempo para resetar _lastOutSeen
    unsigned int turnStep=0; // Toda vez que lturn ou r turn é chamado, +1
    unsigned int rotCooldownStep=0;  // step quando o robo faz um rot 
    unsigned int noLineStep=0; // Toda vez quando o 2 sensores principais não veem linha, +1
    unsigned int somCapturedStep=0; // step (passado) quando foi feita leitura detalhada de som
    unsigned int accelerateStep=0; // step quando foi inicialmente acelerado o carrinho.
    unsigned int obstaculoStep=0;  // step quando uma sequencia de obstaculo é iniciada.

    // Unidades Mínimas de Movimento
    void pos(int time_=DELAYPOS); // reto
    void npos(int time_=DELAYPOS); // ré
    void rot(float graus=3); // gira 90° sentido horário
    void nrot(float graus=3); // gira 90° sentido anti-horário
    void rturn(int time_=DELAYTURN); // somente motor esquerdo, curva para direita
    void lturn(int time_=DELAYTURN); // somente motor direito, curva para esquerda

    // Objetos
  private:
    Lum& _lum;
    Motor& _carro;
    Giros& _giros;
    Cor& _corE;
    Cor& _corD;
    Som& _somE;
    Som& _somD;
    void setID();
};

#endif