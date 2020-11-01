/**********************************
* File: led.cpp
* Authors: Adam Halim, Chun Yang Li, Hee-Min Yang, Jean Janssen
* Date: November 3 2020
* Updated: November 1 2020
* Description: Implementation of methods related to LEDs.
***********************************/

#include "led.h"

//! Function that makes a specific LED blink.
//! \param led      pin to which the led receives the current
//!                 (e.g. PORTA2)
//! \param delay    Time in ms for which the light will be 
//!                 lit then turned off
//! \param port     Port to which the LED is linked to.
//!                 (e.g. PORTA, PORTB, PORTC, PORTD)
void Led::blink(uint8_t ledPin, uint8_t delay, volatile uint8_t& port){
    port |= 1 << ledPin;
    _delay_ms(delay);

    //Turns the specified pin back to 0
    port ^= 1 << ledPin;
    _delay_ms(delay);
}

//! Function specifies if the specific button is still pressed 
//! after the debounce delay.
//! \param  button  pin that is connected to the button
//! \param  port    port that has the button pin
//! \return True if button D2 is pressed for specified debounce 
//!         time. False otherwise.
bool Led::buttonIsPressed(uint8_t button, volatile uint8_t& port){
    const double DELAI_REBOND = 10;
    if (port & (1 << button)){
        _delay_ms(DELAI_REBOND);
        if (port & (1 << button)){
              return true;      
        }
    }
    return false;
}