#include <avr/io.h>
#include <util/delay.h>
#define F_CPU 8000000UL
#define __DELAY_BACKWARD_COMPATIBLE__
#include "../include/del.h"

//! Function that makes a DEL blink
void blinking(int del, uint8_t delay, volatile uint8_t& pin){
    int off = 0;
    pin = del;
    _delay_ms(delay);
    pin = off;
}

//! Fonction qui indique si le bouton spécifié est toujours appuyé 
//! après le délai de rebond.
//! \return True si le bouton D2 est appuyé pendant au moins 
//|         10 ms. Faux sinon.
bool buttonIsPressed(uint8_t button, volatile uint8_t& pin){
    const double DELAI_REBOND = 10;
    if (pin & (1 << button)){
        _delay_ms(DELAI_REBOND);
        if (pin & (1 << button)){
              return true;      
        }
    }
    return false;
}