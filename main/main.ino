#define LED LED_BUILTIN
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

#define ColorPinS0 8
#define ColorPinS1 9
#define ColorPinS2 10
#define ColorPinS3 11
#define ColorPinOut 12
#define ColorPinLed 13

#include <Lum.h>
#include <Linha.h>
#include <Giros.h>
#include <Motor.h>
#include <Cor.h>

#define c countStart


Lum lum(SensorForaEsq, SensorMeioEsq, SensorMeio, SensorMeioDir, SensorForaDir);
Motor carro(MotorDireito, MotorEsquerdo, MotorDireitoRe, MotorEsquerdoRe, EntradaEn1, EntradaEn2);
Cor cor(ColorPinS0, ColorPinS1, ColorPinS2, ColorPinS3, ColorPinOut, ColorPinLed);
Linha linha(lum, carro);
Giros giros;

int countStart = 0;

void setup() 
{
lum.setup();
linha.setup();
giros.setup();
carro.setup();
cor.setup();

Serial.begin(9600);
}


void loop() 
{
rotina();
if (c != -1) {calibrar();}
// giros.print();
// Serial.print(linha.checkState(lum.memoria[lum.memoriaLastIdx]));
// Serial.print(" -> ");
// lum.mostraOutputSensores();
}


void calibrar()
{
    if (countStart == 0)
    {
        if (lum.defineLimite(c))
        {
            countStart += 1;
            for (int k=0; k < 20; k++) //  pisca o LED 20x em 2 seg. Leu o branco!!!!
            { 
                digitalWrite(LED, HIGH);
                delay(50);
                digitalWrite(LED, LOW);
                delay(50);
            }
        }
        return;
    }
    if (countStart == 1)
    {
        if(lum.defineLimite(c))
        {
            countStart += 1;
            for (int k=0; k < 20; k++) //  pisca o LED 20x em 2 seg. Leu o preto e definiu o limite!!
            { 
                digitalWrite(LED, HIGH);
                delay(50);
                digitalWrite(LED, LOW);
                delay(50);
            }
        }
        return;
    }
    if (countStart == 2)
    {
        cor.defineLimiteBranco();
        countStart += 1;
        return;
    }
    countStart = -1;
}

void rotina()
{
    lum.run();
    linha.run();
    giros.run();
    carro.run();   
    cor.run();
}