#ifndef UART_H
#define UART_H

#include <avr/io.h> 

class uart{
    public:
        void initialisationUART();
        void transmissionUART(uint8_t donnee);
    private:
};
#endif /*UART_H*/