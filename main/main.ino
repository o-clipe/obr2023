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

#define EColorPinS0 8
#define EColorPinS1 9
#define EColorPinS2 10
#define EColorPinS3 11
#define EColorPinOut 12
#define EColorPinLed 13

#define DColorPinS0 8
#define DColorPinS1 9
#define DColorPinS2 10
#define DColorPinS3 11
#define DColorPinOut 12
#define DColorPinLed 13

#include <Lum.h>
#include <Linha.h>
#include <Giros.h>
#include <Motor.h>
#include <Cor.h>

#define c countStart


Lum lum(SensorForaEsq, SensorMeioEsq, SensorMeio, SensorMeioDir, SensorForaDir);
Motor carro(MotorDireito, MotorEsquerdo, MotorDireitoRe, MotorEsquerdoRe, EntradaEn1, EntradaEn2);
Giros giros;
Cor corE(EColorPinS0, EColorPinS1, EColorPinS2, EColorPinS3, EColorPinOut, EColorPinLed);
Cor corD(DColorPinS0, DColorPinS1, DColorPinS2, DColorPinS3, DColorPinOut, DColorPinLed);
Linha linha(lum, carro, giros);


int countStart = 0;

void setup() 
{
lum.setup();
linha.setup();
giros.setup();
carro.setup();
corE.setup();
corD.setup();

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
            for (int k=0; k < 20; k++) //  pisca o LED 20x em 5 seg. Leu o branco!!!!
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
            for (int k=0; k < 20; k++) //  pisca o LED 20x em 5 seg. Leu o preto e definiu o limite!!
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
        corE.defineLimiteBranco();
        corD.defineLimiteBranco();
        countStart += 1;
        for (int k=0; k < 20; k++) //  pisca o LED 20x em 5 seg. Definiu limite dos sensores de cor.
        { 
            digitalWrite(LED, HIGH);
            delay(50);
            digitalWrite(LED, LOW);
            delay(50);
        }
        return;
    }
    if (countStart == 3)
    {
        linha.definePerfeitamenteNaLinha();
        countStart += 1;
        for (int k=0; k < 20; k++) //  pisca o LED 20x em 5 seg. Definiu estado perfeitamente na linha.
        { 
            digitalWrite(LED, HIGH);
            delay(50);
            digitalWrite(LED, LOW);
            delay(50);
        }
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
    corE.run();
    corD.run();
}