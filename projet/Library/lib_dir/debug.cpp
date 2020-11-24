/**********************************
* File: debug.cpp
* Authors: Adam Halim, Chun Yang Li, Hee-Min Yang, Jean Janssen
* Date: November 3 2020
* Updated: November 3 2020
* Description: Implementation of methods related to debug.
***********************************/

#include "./debug.h"

//! Prints specified message of specified size.
//! \param debugMessage     Message to be printed
//! \param size             Size of the message
void Debug::DEBUG_PRINT(const char debugMessage[], const unsigned int size){
    uart_.print(debugMessage, size);
}

void Debug::transmission(uint8_t data){
    uart_.transmission(data);
}
