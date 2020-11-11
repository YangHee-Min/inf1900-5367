/**********************************
* File: matrixLed.cpp
* Authors: Adam Halim, Chun Yang Li, Hee-Min Yang, Jean Janssen
* Date: November 11 2020
* Updated: November 11 2020
* Description: Implementation of methods related to matrixLed.
***********************************/


#include "./matrixLed.h"

//! Parametrized Constructeur of the class matrixLed.
//! \param portPtr  Pointer to the port which matrixLed is connected to.
MatrixLed::MatrixLed(volatile uint8_t* portPtr)
    :portPtr_(portPtr){
}

//! Function that turns off the LED.
void MatrixLed::turnOff(){
    *portPtr_ = OFF;
}

//! Function that changes port value of led to that specified.
void MatrixLed::changeLed(uint8_t newLedValue){
    *portPtr_ = newLedValue;
}
