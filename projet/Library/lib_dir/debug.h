/**********************************
* File: debug.h
* Authors: Adam Halim, Chun Yang Li, Hee-Min Yang, Jean Janssen
* Date: November 3 2020
* Updated: November 3 2020
* Description: Definition of methods related to debug.
***********************************/

#include "uart.h"

#ifndef DEBUG_H
#define DEBUG_H
class Debug{
    public:
        // Functions
        void DEBUG_PRINT_MSG(const char debugMessage[], const unsigned int size);
        void DEBUG_PRINT_VALUE(uint8_t data);
    private:
        // Attributes
        Uart uart_;
};
#endif