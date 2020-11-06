/**********************************
* File: uart.cpp
* Authors: Adam Halim, Chun Yang Li, Hee-Min Yang, Jean Janssen
* Date: November 3 2020
* Updated: November 1 2020
* Description: Implementation of methods related to UART and RS232.
***********************************/

#include "uart.h"

//! Default constructor for the UART class. Uses the initialisation function.
Uart::Uart(){
    initialisation();
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

//! Function that transmits data through the UDR0 register.
//! \param data information sent to the PC via RS232 protocol.
void Uart::transmission(uint8_t data){
    while (!(UCSR0A & (1<<UDRE0))){};
    UDR0 = data;
}


void Uart::write(uint8_t instruction, uint8_t operand){
    uint16_t instructionOperand = ((instruction << 8) | (operand));
    eeprom_write_block((const uint8_t*) &instructionOperand, (void*)0x0000, sizeof(instructionOperand));
    transmission(instruction);
    transmission(operand);
}

