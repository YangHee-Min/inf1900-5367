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
        void write(char instruction[], uint8_t operand);
        void receive();
    private:
        void initialisation();
};
#endif /*UART_H*/