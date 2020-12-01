/**********************************
* File: servomotor.cpp
* Authors: Adam Halim, Chun Yang Li, Hee-Min Yang, Jean Janssen
* Date: November 27 2020
* Updated: November 27 2020
* Description: Implementation of methods related to Servomotor.
***********************************/

#include "servomotor.h"

Servomotor::Servomotor(uint8_t pinServomotor, volatile uint8_t* portPtr)
    :pinServomotor_(pinServomotor)
    ,portPtr_(portPtr)
{
}

void Servomotor::transmissionServomotorPWM(double angle){
   
    double pwmDuration = (angle*ANGLE_TO_MS_FACTOR + MINIMUM_MS_VALUE);
    PORTA |= (1 << pinServomotor_);
    _delay_ms(pwmDuration);
    PORTA &= ~(1 << pinServomotor_);
}

