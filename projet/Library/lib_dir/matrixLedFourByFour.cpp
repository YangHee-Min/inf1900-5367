/**********************************
* File: matrixLedFourByFour.cpp
* Authors: Adam Halim, Chun Yang Li, Hee-Min Yang, Jean Janssen
* Date: November 3 2020
* Updated: November 11 2020
* Description: Implementation of methods related to Matrix LED 4x4.
***********************************/

#include "./matrixLedFourByFour.h"

//! Parametrized constructor of MatrixLedFourByFour
//! \param portPtr Pointer to the 4D matrix port.
MatrixLedFourByFour::MatrixLedFourByFour(volatile uint8_t* portPtr)
    : MatrixLed(portPtr){
}
