/**********************************
* File: servomotor.h
* Authors: Adam Halim, Chun Yang Li, Hee-Min Yang, Jean Janssen
* Date: November 27 2020
* Updated: November 27 2020
* Description: Definition of methods related to Servomotor.
***********************************/

#ifndef SERVOMOTOR_H
#define SERVOMOTOR_H

#ifndef F_CPU
#define F_CPU 8000000UL
#endif

#ifndef __DELAY_BACKWARD_COMPATIBLE__
#define __DELAY_BACKWARD_COMPATIBLE__
#endif

#include <avr/io.h> 
#include <util/delay.h>
#include "debug.h"


class Servomotor {

    public:
        //Constructor
        Servomotor(uint8_t pinServomotor, volatile uint8_t* portPtr);
        void transmissionServomotorPWM(double angle);


    private:
        double ANGLE_TO_MS_FACTOR = 90;
        double MINIMUM_MS_VALUE = 2;
       

        uint8_t pinServomotor_;
        volatile uint8_t* portPtr_;
        
};
#endif
