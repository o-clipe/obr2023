/* Biblioteca Template - Codigo*/

#include "Arduino.h"
#include "Som.h"
#include <HCSR04.h>



Som::Som(uint8_t _trigger, uint8_t _echo): sensorHCSR04(_trigger, _echo) // Constructor
{

}

void Som::setup() // Chamado no Setup()
{

}

float Som::distRead()
{
    return sensorHCSR04.dist();
}

float Som::mediaRead()
{
    float total;
    for (byte i=0; i < MEMORIA; i++)
    {
        total += sensorHCSR04.dist();
        delay(DELAY_CAPTURE);
    }
    return total/MEMORIA;
    
}
