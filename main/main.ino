#define led LED_BUILTIN
#define SensorForaEsq A4
#define SensorMeioEsq A3
#define SensorMeio    A2
#define SensorMeioDir A1
#define SensorForaDir A0

#include <Lum.h>
#include <Linha.h>
#include <Giros.h>


Lum lum(SensorForaEsq, SensorMeioEsq, SensorMeio, SensorMeioDir, SensorForaDir);
Linha line(lum);
Giros giros;


void setup() 
{
lum.setup();
giros.setup();
Serial.begin(9600);
}


void loop() 
{
lum.run();
giros.print();
// Serial.print(line.checkState(lum.memoria[lum.memoriaLastIdx]));
// Serial.print(" -> ");
// lum.mostraOutputSensores();
}
