/*Motor - Header*/

#ifndef Motor_h
#define Motor_h

#include "Arduino.h"

#define VELOCIDADE_CURVA 64
#define VELOCIDADE 96  //max 255
#define VELOCIDADE_DIREITO 1.1
#define VELOCIDADE_ESQUERDO 1.0


class Motor
{
  public:
    Motor(uint8_t direito, uint8_t esquerdo, uint8_t direitoRe, uint8_t esquerdoRe, uint8_t velocidadeEsquerdo, uint8_t velocidadeDireito);
    void setup();  // Pra rodar no setup()
    void ligarMotor(uint8_t motor, uint8_t vel=0);  // Liga Motor com o n_ da porta
    void desligarMotor(uint8_t motor);  // Desliga Moto com o n_ da porta
    void parar();  // Desliga todos os motores.
    void ligarReto(uint8_t vel=0);  // Liga somente os motores me, md, desliga os outros.
    void ligarRe(uint8_t vel=0);  // Liga somente os motores mer, mdr, desliga os outros.


    // Uso interno // *********************
    uint8_t _direito; // md
    uint8_t _esquerdo; // me
    uint8_t _direitoRe; // mdr
    uint8_t _esquerdoRe; // mer

  private:

    uint8_t _enEsquerdo;
    uint8_t _enDireito;
};

#endif