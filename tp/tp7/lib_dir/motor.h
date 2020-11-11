/**********************************
* File: motor.h
* Authors: Adam Halim, Chun Yang Li, Hee-Min Yang, Jean Janssen
* Date: November 3 2020
* Updated: November 1 2020
* Description: Implementation of methods related to LEDs.
***********************************/

#ifndef MOTOR_H
#define MOTOR_H

#define F_CPU 8000000UL
#define PRESCALER 8
#define __DELAY_BACKWARD_COMPATIBLE__
#include <avr/io.h>
#include <util/delay.h>

class Motor {
public:
    static const uint8_t OFF = 0;
    static const uint8_t TURNING_PWM = 128;
    enum DirectionValue: uint8_t {  BACKWARD, 
                                    FORWARD};

    Motor(volatile uint16_t* ocrnxPtr, uint8_t directionPin);
    void adjustPWM(uint16_t pwm8Bit, uint8_t directionValue);
    void stop();
    void turnMotorPWM(double PWM, double frequency, uint8_t enablePin, double duration);
    uint8_t convertPercentInPWM8BitTimer(uint16_t percentage);
    void delaySeconds(long unsigned int seconds);
private:
    volatile uint16_t* ocrnxPtr_;
    uint8_t directionPin_;
};
#endif
