#ifndef SONAR_H
#define SONAR_H

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

class Sonar{
    public:
    Sonar(volatile uint8_t* portPtr, uint8_t trigPin, uint8_t echoPin);

    void initialisationISR();


};
#endif