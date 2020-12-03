/**********************************
* File: uart.h
* Authors: Adam Halim, Chun Yang Li, Hee-Min Yang, Jean Janssen
* Date: November 1 2020
* Updated: November 1 2020
* Description: Definition of methods related to UART and RS232.
***********************************/

#ifndef UART_H
#define UART_H

#include <avr/io.h>
#include <avr/eeprom.h> 

class Uart{
    public:
        // Constructor
        Uart();

        // Functions
        void transmission(uint8_t data); 
        void print(const char message[], const unsigned int size);
        uint8_t sendUsartToEeprom();
        uint8_t readByteEeprom(const uint16_t address);
        void saveByteEeprom(const uint16_t address, uint8_t byteToSave); 

    private:
        // Functions
        uint8_t receiveRS232Byte();
        void initialisation();
        
        // Attributes
        static uint16_t currentEepromAddress_;

        // Constants
        static const uint16_t firstEepromAddress = 0x0000;
        
};
#endif /*UART_H*/

