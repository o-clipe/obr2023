#define LED LED_BUILTIN

#define SensorForaEsq A4
#define SensorMeioEsq A3
#define SensorMeio    A2
#define SensorMeioDir A1
#define SensorForaDir A0

#define EntradaEn1       3
#define MotorEsquerdo    39
#define MotorEsquerdoRe  38

#define EntradaEn2       4
#define MotorDireito     41
#define MotorDireitoRe   40


#define EColorPinS0 0
#define EColorPinS1 0
#define EColorPinS2 0
#define EColorPinS3 0
#define EColorPinOut 0
#define EColorPinLed 0 //sempre ligado

#define DColorPinS0 0
#define DColorPinS1 0
#define DColorPinS2 0
#define DColorPinS3 0
#define DColorPinOut 0
#define DColorPinLed 0 //sempre ligado

// MAIS OS 2 CABOS DO GIROSCOPIO

#include <Lum.h>
#include <Linha.h>
#include <Giros.h>
#include <Motor.h>
#include <Cor.h>

#define count countStart


Lum lum(SensorForaEsq, SensorMeioEsq, SensorMeio, SensorMeioDir, SensorForaDir);
Motor carro(MotorDireito, MotorEsquerdo, MotorDireitoRe, MotorEsquerdoRe, EntradaEn1, EntradaEn2);
Giros giros;
Cor corE(EColorPinS0, EColorPinS1, EColorPinS2, EColorPinS3, EColorPinOut, EColorPinLed);
Cor corD(DColorPinS0, DColorPinS1, DColorPinS2, DColorPinS3, DColorPinOut, DColorPinLed);
Linha linha(lum, carro, giros);


int countStart = 0;

void setup() 
{
pinMode(LED, OUTPUT);
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
Serial.print(" ");
Serial.print(analogRead(SensorForaEsq));
Serial.print(" | ");
Serial.print(analogRead(SensorMeioEsq));
Serial.print(" | ");
Serial.print(analogRead(SensorMeio));
Serial.print(" | ");
Serial.print(analogRead(SensorMeioDir));
Serial.print(" | ");
Serial.print(analogRead(SensorForaDir));
Serial.println();

// lum.mostraOutputSensores();
Serial.println(count);
if (count != -1){calibrar();}

}


void calibrar()
{
    // AQUI VC APERTA UM BOTÃO
    if (countStart == 0)
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
    countStart = -1;
}  