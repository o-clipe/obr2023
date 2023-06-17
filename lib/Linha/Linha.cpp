/*Algoritimo para o robo seguir a linha - Codigo*/

#include "Arduino.h"
#include "Linha.h"
#include "Lum.h"


Linha::Linha(Lum& lum_obj): _lum(lum_obj) // Constructor
{

}


void Linha::setup() // Chamado no Setup()
{

}


void Linha::run() // Comandos de rotina
{
  
}


String Linha::checkState(uint16_t sensorsPosition[5])
{
    uint16_t ee = _lum.normalizeSensEntry(0, sensorsPosition[0]);
    uint16_t e = _lum.normalizeSensEntry(1, sensorsPosition[1]);
    uint16_t m = _lum.normalizeSensEntry(2, sensorsPosition[2]);
    uint16_t d = _lum.normalizeSensEntry(3, sensorsPosition[3]);
    uint16_t dd = _lum.normalizeSensEntry(4, sensorsPosition[4]);

    Serial.print((String)ee + " " + (String)e + " " + (String)m + " " + (String)d + " " + (String)dd + ": ");

    if (ee < e && e < m && m > d && d > dd){
        return "default";
    }
    return "not";
}


 