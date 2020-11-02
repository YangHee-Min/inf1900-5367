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
#include <avr/io.h>
#include <util/delay.h>

class Led {
    public:
        static void blink(uint8_t ledPinSource, uint8_t ledPinGround, uint8_t duration, volatile uint8_t& port);
        static bool buttonIsPressed(uint8_t button, volatile uint8_t& pinx);
    private:
};
#endif