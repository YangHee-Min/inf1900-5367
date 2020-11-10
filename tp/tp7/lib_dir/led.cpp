/**********************************
* File: led.cpp
* Authors: Adam Halim, Chun Yang Li, Hee-Min Yang, Jean Janssen
* Date: November 3 2020
* Updated: November 1 2020
* Description: Implementation of methods related to LEDs.
***********************************/

#include "led.h"

//! Function that turns on the LED
//! \param ledPinSource     pin to which the led gives the current
//!                         (e.g. PORTA2)
//! \param ledPinGround     pin that has 0 as value to receive current.
//! \param port             Port to which the LED is linked to.
//!                         (e.g. PINA, PINB, PINC, PIND)
void Led::turnOn(uint8_t ledPinSource, uint8_t ledPinGround, volatile uint8_t& port){
    port |= 1 << ledPinSource;
    // Clear ground led pin
    port &= ~(1 << ledPinGround);
}

//! Function that turns off the LED
//! \param ledPinSource     pin to which the led gives the current
//!                         (e.g. PORTA2)
//! \param port             Port to which the LED is linked to.
//!                         (e.g. PINA, PINB, PINC, PIND)
void Led::turnOff(uint8_t ledPinSource, volatile uint8_t& port){
    port &= ~(1 << ledPinSource);
}

//! Function that makes a specific LED blink.
//! \param ledPinSource     pin to which the led gives the current
//!                         (e.g. PORTA2)
//! \param ledPinGround     pin that has 0 as value to receive current.
//! \param duration         Time in ms for which the light will be lit 
//! \param port             Port to which the LED is linked to.
//!                         (e.g. PINA, PINB, PINC, PIND)
void Led::blink(uint8_t ledPinSource, uint8_t ledPinGround, uint8_t duration, volatile uint8_t& port){
    // Set source led pin
    turnOn(ledPinSource, ledPinGround, port);
    _delay_ms(duration);

    //Turns the specified source pin back to 0
    turnOff(ledPinSource, port);
}
