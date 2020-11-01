#ifndef UART_H
#define UART_H

#include <avr/io.h> 

class Uart{
    public:
        static void initialisation();
        static void transmission(uint8_t donnee);
    private:
};
#endif /*UART_H*/