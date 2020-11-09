/**********************************
* File: uart.h
* Authors: Adam Halim, Chun Yang Li, Hee-Min Yang, Jean Janssen
* Date: November 3 2020
* Updated: November 1 2020
* Description: Definition of methods related to UART and RS232.
***********************************/

#ifndef UART_H
#define UART_H

#include <avr/io.h>
#include <avr/eeprom.h> 

class Uart{
    public:
        Uart();
        void transmission(uint8_t data); 
        void write(const char debugMessage[], const unsigned int size);
        uint16_t receiveWord(const uint16_t* address);
    private:
        void initialisation();
};
#endif /*UART_H*/
