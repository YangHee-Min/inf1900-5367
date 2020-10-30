#include "./uart.h"

void uart::initialisationUART () {
    // 2400 bauds. Nous vous donnons la valeur des deux
    // premier registres pour vous éviter des complications
    UBRR0H = 0;
    UBRR0L = 0xCF;
    // permettre la réception et la transmission par le UART0
    // UCSR0A = ;
    UCSR0B = (1<<RXEN0) | (1<<TXEN0) ;
    // Format des trames: 8 bits, 1 stop bits, none parity
    UCSR0C = (1 << USBS0) |  (3<<UCSZ00);
}

void uart::transmissionUART ( uint8_t donnee ) {
    while (!(UCSR0A & (1<<UDRE0))){};
    UDR0 = donnee;
}