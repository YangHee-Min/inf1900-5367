#ifndef UART_H
#define UART_H

#include <avr/io.h> 

class Uart{
    public:
        static void initialisation();
        static void transmission(uint8_t info);
    private:
};
#endif /*UART_H*/