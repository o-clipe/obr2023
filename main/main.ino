#define LED LED_BUILTIN

#define SensorForaEsq A0  // ** Sensores de Luminosidade
#define SensorEsq A1
#define SensorMeio A6
#define SensorDir A2
#define SensorForaDir A3
#define SensorTrasEsq A4
#define SensorTrasDir A5

#define EntradaEn1       4  // ********** Motor Esquerdo
#define MotorEsquerdo    6
#define MotorEsquerdoRe  7

#define EntradaEn2       5  // *********** Motor Direito
#define MotorDireito     8
#define MotorDireitoRe   9

#define EColorPinS0 26  // ******* Sensor de Cor Esquerdo
#define EColorPinS1 27
#define EColorPinS2 28
#define EColorPinS3 29
#define EColorPinOut 33
#define EColorPinLed 31

#define DColorPinS0 22   // ******* Sensor de Cor Direito
#define DColorPinS1 23
#define DColorPinS2 24
#define DColorPinS3 25
#define DColorPinOut 32
#define DColorPinLed 30

#define ESomTrigger 0
#define ESomEcho 0

#define DSomTrigger 0
#define DSomEcho 0

// MAIS OS 2 CABOS DO GIROSCOPIO

#include <Lum.h>
#include <Linha.h>
#include <Giros.h>
#include <Motor.h>
#include <Cor.h>
#include <Som.h>

#define LIMITE_BRANCO_E 1000
#define LIMITE_BRANCO_D 100


Lum lum(SensorForaEsq, SensorEsq, SensorMeio, SensorDir, SensorForaDir, SensorTrasEsq, SensorTrasDir);
Motor carro(MotorDireito, MotorEsquerdo, MotorDireitoRe, MotorEsquerdoRe, EntradaEn1, EntradaEn2);
Giros giros;
Cor corE(EColorPinS0, EColorPinS1, EColorPinS2, EColorPinS3, EColorPinOut, EColorPinLed, LIMITE_BRANCO_E);
Cor corD(DColorPinS0, DColorPinS1, DColorPinS2, DColorPinS3, DColorPinOut, DColorPinLed, LIMITE_BRANCO_D);
Som somE(ESomTrigger, ESomEcho);
Som somD(DSomTrigger, DSomEcho);
Linha linha(lum, carro, giros, corE, corD, somE, somD);



int countStart = 0;

void setup() 
{
lum.setup();
linha.setup();
giros.setup();
carro.setup();
corE.setup();
corD.setup();

pinMode(LED, OUTPUT);
Serial.begin(115200);
}


void loop() 
{
// lum.unprocessedPrint();
// lum.processedPrint();
// Serial.println();


// for (int i=0; i < 13; i++)
// {
// linha.pos();
// }
// delay(10000000);

// linha.rotCooldownStep += 100;
// linha.rot(90);
// delay(2000);
// linha.rotCooldownStep += 100;
// linha.nrot(90);
// delay(2000);
// linha.rotCooldownStep += 100;
// linha.rot(360);
// delay(1000);

// corE.ledOn();
// corD.ledOn();
// Serial.print("E");
// corE.printRaw();
// Serial.print("|| D");
// corD.printRaw();
// Serial.println();


linha.segueLinha();

// carro.ligarReto();
// Serial.print(" E: ");
// Serial.print(somE.distRead());
// Serial.print(" -OO- D: ");
// Serial.print(somD.distRead());
// giros.print();
// Serial.println();
}
  