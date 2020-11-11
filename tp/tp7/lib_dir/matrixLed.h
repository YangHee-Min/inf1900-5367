#ifndef MATRIXLED_H
#define MATRIXLED_H

#include <avr/io.h>

class MatrixLed {
    public:
        MatrixLed(volatile uint8_t* portPtr);
        virtual void turnOff();
        virtual void changeLed(uint8_t newLedValue);
    protected:
        static const uint8_t OFF = 0x00;
        volatile uint8_t* portPtr_;
};
#endif