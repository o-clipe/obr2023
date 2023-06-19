/*Algoritimo para o robo seguir a linha - Codigo*/

#include "Arduino.h"
#include "Linha.h"
#include "Lum.h"
#include "Motor.h"


Linha::Linha(Lum& lum_obj, Motor& motor_obj): _lum(lum_obj), _carro(motor_obj) // Constructor
{
    status = "inicio";
}


void Linha::setup() // Chamado no Setup()
{

}


void Linha::run() // Comandos de rotina
{
  rotinaBasica();
}


String Linha::checkState(uint16_t sensorsPosition[5])
{
    uint16_t ee = _lum.normalizeSensEntry(0, sensorsPosition[0]);
    uint16_t e = _lum.normalizeSensEntry(1, sensorsPosition[1]);
    uint16_t m = _lum.normalizeSensEntry(2, sensorsPosition[2]);
    uint16_t d = _lum.normalizeSensEntry(3, sensorsPosition[3]);
    uint16_t dd = _lum.normalizeSensEntry(4, sensorsPosition[4]);

    Serial.print((String)ee + " " + (String)e + " " + (String)m + " " + (String)d + " " + (String)dd + ": ");

    if (ee < e && e < m && m > d && d > dd) return "default";
    else if (e >= m && m > d && d >= dd) return "linha a esquerda";
    else if (ee <= e && e < m && m <= d) return "linha a direita";
    else if (ee == 0 && e == 0 && m == 0 && d == 0 && dd == 0) return "sem linha";
    else if (ee > 0 && e > 0 && m > 0 && d > 0 && dd > 0) return "paralelo a linha";

    return "F";
}


void Linha::pararSeOutroStatus(String f_status)
{
    if (f_status != status)
    {
        _carro.parar();
    }
}


void Linha::rotinaBasica()
{
    String status = checkState(_lum.processedReadAll());
    if (status == "default")
    {
        _carro.ligarReto();
    }
    if (status == "linha a esquerda")
    {
        pararSeOutroStatus("linha a esquerda");
        _carro.ligarMotor("e", VELOCIDADEDECURVA);
    }
    if (status == "linha a direita")
    {
        pararSeOutroStatus("linha a direita");
        _carro.ligarMotor("d", VELOCIDADEDECURVA);
    }
    if (status == "sem linha"){
        _carro.parar();
    }
    else if (status == "paralelo a linha")
    {
        _carro.ligarRe();
    }

}




 