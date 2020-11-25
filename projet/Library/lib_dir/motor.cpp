/**********************************
* File: motor.cpp
* Authors: Adam Halim, Chun Yang Li, Hee-Min Yang, Jean Janssen
* Date: November 3 2020
* Updated: November 11 2020
* Description: Implementation of methods related to Motor.
***********************************/

#include "motor.h"

//! Parameters constructor that also initializes an 8 bits timer
//! \param ocrnxPtr     Pointer to PWM timer value
//! \param directionPin Pin which manipulates the direction
Motor::Motor(volatile uint16_t* ocrnxPtr, uint8_t directionPin): ocrnxPtr_(ocrnxPtr), directionPin_(directionPin){
    // If instantiating multiple motor classes, we won't instantiate 
    // registers more than once.
    #ifndef MOTOR
    #define MOTOR
    // Set timer to 0
    TCNT1 = 0;

    // Clock division by 8 - Implies a fixed PWM frequency
    TCCR1A |= (1 << COM1A1) | (1 << COM1B1) | (1 << WGM10);    
    TCCR1B |= (1 << CS11);
    TCCR1C = 0;
    #endif
}

//! Function that changes timer value
//! \param pwm8Bit  PWM percentage wanted on 8 bits (over 255)
//! \param ocrnx_   PWM timer value
void Motor::adjustPWM(uint16_t pwm8Bit, uint8_t directionValue){
    PORTD = (directionValue == 0) ? PORTD & ~(1 << directionPin_): PORTD | (1 << directionPin_);
    *ocrnxPtr_ = pwm8Bit;
}

//! Function that stops the motor.
void Motor::stop(){
    adjustPWM(OFF, FORWARD);
}

//! Function that turns the wheel for a set duration at a specified frenquency with the PWM
//! Note that this method is used in the case where we are not using TCNT as the PWM timer.
//! \param PWM              Pwm in percentage wanted for the motor
//! \param frequency        Frequency of the pwm wave
//! \param enablePin        Pin that is responsible for enabling the H bridge
//! \param duration         Duration for which the motor will be turning
void Motor::turnMotorPWM(double PWM, double frequency, uint8_t enablePin, double duration){

    const int CONVERSION_RATIO_S_TO_MS = 1000;
	const double PERIOD = 1/frequency * CONVERSION_RATIO_S_TO_MS; 

	int numberCycles = duration/(PERIOD);
    double upTime = PERIOD * PWM;
    double downTime = PERIOD - upTime;
	for(int i = 0; i< numberCycles; i++){
		PORTD |= (1 << enablePin) | (1 << directionPin_);
		_delay_ms(upTime);
		PORTD &= ~(1 << enablePin);
		_delay_ms(downTime);
	}
}

//! Function that converts the percentage into a PWM
//! \param percentage   Percentage wanted for uptime of the PWM wave
//! \return             Returns the integer related to max count of the 8 
//!                     bit timer and the specified percentage.
uint8_t Motor::convertPercentInPWM8BitTimer(uint16_t percentage){
    uint8_t pwm = 0;
    switch(percentage){
        case 0:
            pwm = 0;
            break;
        case 25:
            pwm = 64;
            break;
        case 50:
            pwm = 128;
            break;
        case 75:
            pwm = 192;
            break;
        case 100:
            pwm = 254;
            break;
    }
    return pwm;
}

//! Function that delays the motor by the specified number of seconds. 
//! \param seconds   Number of seconds we want to delay the motor by
void Motor::delaySeconds(long unsigned int seconds){
    long unsigned int cyclesPerSecond = F_CPU / PRESCALER;
    for(long unsigned int currentSecond = 0; currentSecond < seconds; currentSecond++){
        for(long unsigned int currentCycle = 0; currentCycle < cyclesPerSecond; currentCycle++){
        }
    }
}
