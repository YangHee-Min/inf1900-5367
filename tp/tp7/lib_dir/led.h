/**********************************
* File: led.h
* Authors: Adam Halim, Chun Yang Li, Hee-Min Yang, Jean Janssen
* Date: November 3 2020
* Updated: November 1 2020
* Description: Definition of methods related to LEDs.
***********************************/

#ifndef LED_H
#define LED_H

#define F_CPU 8000000UL
#define __DELAY_BACKWARD_COMPATIBLE__
#include <util/delay.h>
#include <avr/io.h>

class Led {
    public:
        void blink(int del, uint8_t delay, volatile uint8_t& pin);
        bool buttonIsPressed(uint8_t button, volatile uint8_t& pin);
    private:
};
#endif