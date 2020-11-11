/**********************************
* File: matrixLedFourByFour.h
* Authors: Adam Halim, Chun Yang Li, Hee-Min Yang, Jean Janssen
* Date: November 3 2020
* Updated: November 11 2020
* Description: Definition of methods related to Matrix LED 4x4.
***********************************/

#ifndef MATRIXLEDFOURBYFOUR_H
#define MATRIXLEDFOURBYFOUR_H

#include "./matrixLed.h"

class MatrixLedFourByFour : public MatrixLed{
    public:
        //Constructor
        MatrixLedFourByFour(volatile uint8_t* portPtr);
};
#endif
