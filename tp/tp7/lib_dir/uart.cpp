/**********************************
* File: uart.cpp
* Authors: Adam Halim, Chun Yang Li, Hee-Min Yang, Jean Janssen
* Date: November 3 2020
* Updated: November 1 2020
* Description: Implementation of methods related to UART and RS232.
***********************************/

#include "uart.h"

uint16_t Uart::currentEepromAddress_ = 0;

//! Default constructor for the UART class. Uses the initialisation function.
Uart::Uart(){
    initialisation();
}

//! Function that transmits data through the UDR0 register.
//! \param data information sent to the PC via RS232 protocol.
void Uart::transmission(uint8_t data){
    while (!(UCSR0A & (1<<UDRE0))){};
    UDR0 = data;
}

//! Function that writes a message to serial monitor
//! \param message 
void Uart::print(const char message[], const unsigned int size){
    for ( unsigned int currentIndex = 0; currentIndex < size; currentIndex++ ) {
            transmission(message[currentIndex]);
    }
}

uint8_t Uart::sendUsartToEeprom(){
    uint8_t byteToSend = receiveRS232Byte();
    saveByteEeprom(currentEepromAddress_, byteToSend);
    currentEepromAddress_+= 0x0001;
    return byteToSend;
}

//! Function that reads byte at certain address.
uint8_t Uart::readByteEeprom(const uint16_t address){
    return eeprom_read_byte((uint8_t*) address);
}

void Uart::saveByteEeprom(const uint16_t address, uint8_t byteToSave){
    eeprom_write_byte((uint8_t*) address, byteToSave);
}

uint8_t Uart::receiveRS232Byte(){
        while ( !(UCSR0A & (1<<RXC0)));
        return UDR0;
}

//! Function that initialises the UART registers to enable the reception and transmission
//! by UART. The symbol rate (modulation rate) is set to 2400 bauds. Uses 8 bits, 1 stop bit
//! and no parity bit.
void Uart::initialisation(){
    // 2400 bauds.
    UBRR0H = 0;
    UBRR0L = 0xCF;
    // Lets UART0 do transmission and reception
    UCSR0B = (1<<RXEN0) | (1<<TXEN0);
    // Format of frames : 8 bits, 1 stop bit, none parity
    UCSR0C = (1 << USBS0) | (3<<UCSZ00);
}