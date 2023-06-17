#define led LED_BUILTIN
#define SensorForaEsq A4
#define SensorMeioEsq A3
#define SensorMeio    A2
#define SensorMeioDir A1
#define SensorForaDir A0

#include <Lum.h>
#include <Linha.h>


Lum lum(SensorForaEsq, SensorMeioEsq, SensorMeio, SensorMeioDir, SensorForaDir);
Linha line(lum);


void setup() 
{
lum.setup();
Serial.begin(9600);
}


void loop() 
{
lum.run();

Serial.print(line.checkState(lum.memoria[lum.memoriaLastIdx]));
Serial.print(" -> ");
mostraOutputSensores();
}


void mostraOutputSensores()
{
Serial.print(" ");
Serial.print(lum.processedRead(SensorForaEsq));
Serial.print(" | ");
Serial.print(lum.processedRead(SensorMeioEsq));
Serial.print(" | ");
Serial.print(lum.processedRead(SensorMeio));
Serial.print(" | ");
Serial.print(lum.processedRead(SensorMeioDir));
Serial.print(" | ");
Serial.print(lum.processedRead(SensorForaDir));
Serial.println();
}