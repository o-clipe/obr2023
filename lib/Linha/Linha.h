/*Algoritimo para o robo seguir a linha*/

#ifndef Linha_h
#define Linha_h

#include "Arduino.h"
#include "Lum.h"
#include "Motor.h"
#include "Giros.h"
#include "Cor.h"

#define DELAYPOS 10
#define DELAYROT 25 // Constante, não tocar
#define DELAYTURN 15
#define DELAY 10
#define FATOR_ANGULO 0.10


class Linha
{
  public:
    Linha(Lum& lum_obj, Motor& motor_obj, Giros& giros_obj, Cor& corE_obj, Cor& corD_obj);
    void setup();
    void segueLinha();

    uint8_t _lastOutSeen = 0;  // Entre dd, ee, dd && ee, qual foi o último visto. Direciona rots (rotacionações em 90 graus)

    // Triggers -- Ifs que mudam a rotina padrão do segueLinha
    bool colorTrigger=false;
    bool obstaculoTrigger=false;
    bool subidaTrigger=false;
    bool rampaDeResgateTrigger=false;
    bool gapTrigger=false;

    // Steps -- O cálculo de tempo / progresso.
    unsigned int step=0; // step de agora. É atualizado a cada ciclo.
    unsigned int encruzilhadaStep=0; // step (passado) -> tempo para liberar _lastOutStep
    unsigned int lastOutStep=0; // step (passado) +- steps e.g. (steps+0 == ~100) -> tempo para resetar _lastOutSeen
    unsigned int turnStep=0; // Toda vez que lturn ou r turn é chamado, +1
    unsigned int rotCooldownStep=0;


    // Unidades Mínimas de Movimento
    void pos(uint16_t time_=DELAYPOS); // reto
    void npos(uint16_t time_=DELAYPOS); // ré
    void rot(float graus=3); // gira 90° sentido horário
    void nrot(float graus=3); // gira 90° sentido anti-horário
    void rturn(uint16_t time_=DELAYTURN); // somente motor esquerdo, curva para direita
    void lturn(uint16_t time_=DELAYTURN); // somente motor direito, curva para esquerda

    // Objetos
  private:
    Lum& _lum;
    Motor& _carro;
    Giros& _giros;
    Cor& _corE;
    Cor& _corD;
};

#endif