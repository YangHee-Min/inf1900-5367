/**********************************
* File: led.cpp
* Authors: Adam Halim, Chun Yang Li, Hee-Min Yang, Jean Janssen
* Date: November 3 2020
* Updated: November 1 2020
* Description: Implementation of methods related to LEDs.
***********************************/

#include "led.h"

//! Function that makes a specific LED blink.
//! \param ledPinSource     pin to which the led gives the current
//!                         (e.g. PORTA2)
//! \param ledPinGround     pin that has 0 as value to receive current.
//! \param duration         Time in ms for which the light will be lit 
//! \param port             Port to which the LED is linked to.
//!                         (e.g. PINA, PINB, PINC, PIND)
void Led::blink(uint8_t ledPinSource, uint8_t ledPinGround, uint8_t duration, volatile uint8_t& pinx){
    // Set source led pin
    port |= 1 << ledPinSource;
    // Clear ground led pin
    port &= ~(1 << ledPinGround);
    _delay_ms(duration);

    //Turns the specified source pin back to 0
    port &= ~(1 << ledPinSource);
}

//! Function specifies if the specific button is still pressed 
//! after the debounce delay.
//! \param  button  pin that is connected to the button
//! \param  port    port that has the button pin
//! \return True if button D2 is pressed for specified debounce 
//!         time. False otherwise.
bool Led::buttonIsPressed(uint8_t button, volatile uint8_t& pinx){
    const double DEBOUNCE_DELAY = 10;
    if (pinx & (1 << button)){
        _delay_ms(DEBOUNCE_DELAY);
        if (pinx & (1 << button)){
              return true;      
        }
    }
    return false;
}