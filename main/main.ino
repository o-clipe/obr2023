#define LED LED_BUILTIN

#define SensorForaEsq A0  // ** Sensores de Luminosidade
#define SensorEsq A1
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

// MAIS OS 2 CABOS DO GIROSCOPIO

#include <Lum.h>
#include <Linha.h>
#include <Giros.h>
#include <Motor.h>
#include <Cor.h>

#define LIMITE_BRANCO_E 1000
#define LIMITE_BRANCO_D 100


Lum lum(SensorForaEsq, SensorEsq, SensorDir, SensorForaDir, SensorTrasEsq, SensorTrasDir);
Motor carro(MotorDireito, MotorEsquerdo, MotorDireitoRe, MotorEsquerdoRe, EntradaEn1, EntradaEn2);
Giros giros;
Cor corE(EColorPinS0, EColorPinS1, EColorPinS2, EColorPinS3, EColorPinOut, EColorPinLed, LIMITE_BRANCO_E);
Cor corD(DColorPinS0, DColorPinS1, DColorPinS2, DColorPinS3, DColorPinOut, DColorPinLed, LIMITE_BRANCO_D);
Linha linha(lum, carro, giros, corE, corD);



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
lum.unprocessedPrint();
lum.processedPrint();
Serial.println();


// for (int i=0; i < 13; i++)
// {
// linha.pos();
// }
// delay(10000000);


// linha.rot(90);
// delay(2000);
// linha.nrot(90);
// delay(2000);
// linha.rot(360);
// delay(1000);


// Serial.print("E");
// corE.printRaw();
// Serial.print("|| D");
// corD.printRaw();
// Serial.println();


linha.segueLinha();
}
  