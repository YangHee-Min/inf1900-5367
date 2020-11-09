/**********************************
* File: motor.cpp
* Authors: Adam Halim, Chun Yang Li, Hee-Min Yang, Jean Janssen
* Date: November 3 2020
* Updated: November 1 2020
* Description: Implementation of methods related to LEDs.
***********************************/

#ifndef MOTOR_H
#define MOTOR_H

#define F_CPU 8000000UL
#define __DELAY_BACKWARD_COMPATIBLE__
#include <avr/io.h>
#include <util/delay.h>

class Motor {
public:
    Motor();
    void turnMotorPWM(double PWM, double frequency, uint8_t directionPin, uint8_t enablePin, double duration, volatile uint8_t& port);
    uint8_t convertPercentInPWM8BitTimer(uint8_t percentage);
    void adjustPWM(uint8_t percentage, volatile uint8_t& ocrnx);
private:
    const uin8_t PORT_SORTIE = 0xFF;
};

#endif /*MOTOR_H*/
