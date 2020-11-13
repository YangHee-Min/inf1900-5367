#include <avr/io.h>
#define F_CPU 8000000UL
#include <avr/eeprom.h>



void initialisationUART (void) {
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

void transmissionUART ( uint8_t donnee ) {
    while (!(UCSR0A & (1<<UDRE0))){};
    UDR0 = donnee;
}



int main(){
    char mots[35] = "Le simulateur SimulIDE en INF1900\n";
    uint8_t i, j;
    for ( i = 0; i < 100; i++ ) {
        for ( j=0; j < 33; j++ ) {
            transmissionUART ( mots[j] );
        }
    }
}