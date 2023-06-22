#define LED LED_BUILTIN

#define SensorForaEsq A0  // ** Sensores de Luminosidade
#define SensorEsq A1
#define SensorDir A2
#define SensorForaDir A3
#define SensorTrasEsq A4
#define SensorTrasDir A5

#define EntradaEn1       4  // ********** Motor Esquerdo
#define MotorEsquerdo    7
#define MotorEsquerdoRe  6

#define EntradaEn2       5  // *********** Motor Direito
#define MotorDireito     9
#define MotorDireitoRe   8

#define EColorPinS0 0  // ******* Sensor de Cor Esquerdo
#define EColorPinS1 0
#define EColorPinS2 0
#define EColorPinS3 0
#define EColorPinOut 0
#define EColorPinLed 0

#define DColorPinS0 0   // ******* Sensor de Cor Direito
#define DColorPinS1 0
#define DColorPinS2 0
#define DColorPinS3 0
#define DColorPinOut 0
#define DColorPinLed 0 

// MAIS OS 2 CABOS DO GIROSCOPIO

#include <Lum.h>
#include <Linha.h>
#include <Giros.h>
#include <Motor.h>
#include <Cor.h>

#define count countStart


Lum lum(SensorForaEsq, SensorEsq, SensorDir, SensorForaDir, SensorTrasEsq, SensorTrasDir);
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

pinMode(LED, OUTPUT);
Serial.begin(9600);
}


void loop() 
{
lum.unprocessedPrint();
// linha.segueLinha();
}
  