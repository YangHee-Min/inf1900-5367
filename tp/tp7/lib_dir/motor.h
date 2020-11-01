#ifndef MOTOR_H
#define MOTOR_H

#define F_CPU 8000000UL
#define __DELAY_BACKWARD_COMPATIBLE__
#include <avr/io.h>
#include <util/delay.h>

class Motor {
public:

    static void turnMotorPWM(double PWM, double frequency, uint8_t direction, double duration, volatile uint8_t& port);
    static uint8_t convertPercentInPWM8BitTimer(uint8_t percentage);
    static void adjustPWM(uint8_t percentage, uint8_t ocrnx);
};

#endif /*MOTOR_H*/
