#define led LED_BUILTIN
#define SensorForaEsq A4
#define SensorMeioEsq A3
#define SensorMeio    A2
#define SensorMeioDir A1
#define SensorForaDir A0
#define MotorDireito     2
#define MotorEsquerdo    3
#define MotorDireitoRe   4
#define MotorEsquerdoRe  5
#define EntradaEn1       6
#define EntradaEn2       7

#include <Lum.h>
#include <Linha.h>
#include <Giros.h>
#include <Motor.h>


Lum lum(SensorForaEsq, SensorMeioEsq, SensorMeio, SensorMeioDir, SensorForaDir);
Motor carro(MotorDireito, MotorEsquerdo, MotorDireitoRe, MotorEsquerdoRe, EntradaEn1, EntradaEn2);
Linha linha(lum, carro);
Giros giros;



void setup() 
{
lum.setup();
linha.setup();
giros.setup();
carro.setup();

Serial.begin(9600);
}


void loop() 
{
lum.run();
linha.run();
giros.run();
carro.run();
// giros.print();
// Serial.print(linha.checkState(lum.memoria[lum.memoriaLastIdx]));
// Serial.print(" -> ");
// lum.mostraOutputSensores();
}
