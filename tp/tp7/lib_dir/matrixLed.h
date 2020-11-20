/**********************************
* File: matrixLed.h
* Authors: Adam Halim, Chun Yang Li, Hee-Min Yang, Jean Janssen
* Date: November 11 2020
* Updated: November 11 2020
* Description: Definition of methods related to matrixLed.
***********************************/

#ifndef MATRIXLED_H
#define MATRIXLED_H

#include <avr/io.h>

class MatrixLed {
    public:
        // Constructor
        MatrixLed(volatile uint8_t* portPtr);

        // Functions
        virtual void turnOff();
        virtual void changeLed(uint8_t newLedValue);

    protected:
        // Constants
        static const uint8_t OFF = 0x00;

        // Attributes
        volatile uint8_t* portPtr_;
};
#endif
