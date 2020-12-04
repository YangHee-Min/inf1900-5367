/**********************************
* File: led.h
* Authors: Adam Halim, Chun Yang Li, Hee-Min Yang, Jean Janssen
* Date: November 1 2020
* Updated: November 1 2020
* Description: Definition of methods related to LEDs.
***********************************/

#ifndef LED_H
#define LED_H

#include <avr/io.h>
#include <util/delay.h>

class Led {
    public:
        // Constructor
        Led(uint8_t pinSource, uint8_t pinGround, volatile uint8_t& port);
        
        // Fonctions
        void turnOn();
        void turnOff(); 
        void blink(int duration);
        bool buttonIsPressed(uint8_t button, volatile uint8_t& pinx);

        // Constants
        static const uint8_t OFF = 0x00;
        static const int S_TO_MS_FACTOR = 1000;
    private:
    
        // Attributes
		uint8_t pinSource_;
		uint8_t pinGround_;
        volatile uint8_t* portPtr_;
};
#endif
