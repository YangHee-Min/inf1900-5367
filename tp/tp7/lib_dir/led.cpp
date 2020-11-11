/**********************************
* File: led.cpp
* Authors: Adam Halim, Chun Yang Li, Hee-Min Yang, Jean Janssen
* Date: November 3 2020
* Updated: November 1 2020
* Description: Implementation of methods related to LEDs.
***********************************/

#include "led.h"

Led::Led( uint8_t pinSource, uint8_t pinGround, volatile uint8_t& port):
    pinSource_(pinSource),
    pinGround_(pinGround),
    portPtr_(&port){   
}

//! Function that turns on the LED
void Led::turnOn(){
    *portPtr_ |= 1 << pinSource_;
    *portPtr_ &= ~(1 << pinGround_);
}

//! Function that turns off the LED
void Led::turnOff(){
    *portPtr_ &= ~(1 << pinSource_);
}

//! Function that makes a specific LED blink.
//! \param duration     Time in ms for which the light will be lit 
void Led::blink(int duration){
    turnOn();
    _delay_ms(duration);

    turnOff();
}

//! Function specifies if the specific button is still pressed 
//! after the debounce delay.
//! \param  button  pin that is connected to the button
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
