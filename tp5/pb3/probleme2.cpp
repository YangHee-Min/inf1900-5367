#define F_CPU 8000000UL
#define __DELAY_BACKWARD_COMPATIBLE__
#define insanity 100


#include <avr/io.h>
#include <util/delay.h>
#include <avr/eeprom.h>

void initialisationUART ( void ) {

    // 2400 bauds. Nous vous donnons la valeur des deux
    // premier registres pour vous éviter des complications
    UBRR0H = 0;
    UBRR0L = 0xCF;
    // permettre la réception et la transmission par le UART0
    UCSR0A |= (1 << RXC0) | (1 << TXC0);
    UCSR0B |= (1 << RXEN0) | (1 << TXEN0);
    // Format des trames: 8 bits, 1 stop bits, none parity
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00) ;
}

// De l'USART vers le PC
void transmissionUART ( uint8_t donnee ) {
    UDR0 = donnee;
}


int main()
{
    char mots[45] = "I am absolutely done with transmission lmao\n"; 
    uint16_t address = 0x0000;
    eeprom_write_block((const uint8_t*) &mots, (void*)address, sizeof(mots));

    for(int i = 0; i < insanity; i++){
        for(uint16_t currentAddress = 0x0000; eeprom_read_byte((uint8_t*)currentAddress) != 0xFF; currentAddress++){
            transmissionUART(eeprom_read_byte((uint8_t*)currentAddress));
        }
    }
}