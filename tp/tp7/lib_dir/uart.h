#ifndef UART_H
#define UART_H

#include <avr/io.h>
#include <avr/eeprom.h> 

class Uart{
    public:
        Uart();
        void transmission(uint8_t info);
    private:
        void initialisation();
};
#endif /*UART_H*/