#ifndef DEL_H
#define DEL_H

#define F_CPU 8000000UL
#define __DELAY_BACKWARD_COMPATIBLE__
#include <util/delay.h>
#include <avr/io.h>

class Del {
    public:
        void blinking(int del, uint8_t delay, volatile uint8_t& pin);
        bool buttonIsPressed(uint8_t button, volatile uint8_t& pin);
    private:
};
#endif