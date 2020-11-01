/**********************************
* File: motor.cpp
* Authors: Adam Halim, Chun Yang Li, Hee-Min Yang, Jean Janssen
* Date: November 3 2020
* Updated: November 1 2020
* Description: Implementation of methods related to LEDs.
***********************************/

#include "motor.h"

//! Function that changes timer value
//! \param percentage   PWM percentage wanted
//! \param ocrnx        PWM generating pin (oc1a or oc1b)
void Motor::adjustPWM(uint8_t percentage, volatile uint8_t& ocrnx){
    if(percentage > 100){
        percentage = 100;
    }
    ocrnx = convertPercentInPWM8BitTimer(percentage);
}

//! Function that converts the percentage into a PWM
//! \param percentage   percentage wanted for uptime of the PWM wave
//! \return    returns the integer related to max count of the 8 
//!            bit timer and the specified percentage.
uint8_t Motor::convertPercentInPWM8BitTimer(uint8_t percentage){
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

//! Function that turns the wheel for a set duration at a specified frenquency with the PWM
//! \param PWM              Pwm in percentage wanted for the motor
//! \param frequency        Frequency of the pwm wave
//! \param directionPin     Pin that is responsible for the direction of the H bridge
//! \param enablePin        Pin that is responsible for enabling the H bridge
//! \param duration         Duration for which the motor will be turning
//! \param port             Port attached to the H gate
void Motor::turnMotorPWM(double PWM, double frequency, uint8_t directionPin, uint8_t enablePin, double duration, volatile uint8_t& port){

    const int CONVERSION_RATIO_S_TO_MS = 1000;
	const double PERIOD = 1/frequency * CONVERSION_RATIO_S_TO_MS; 

	int numberCycles = duration/(PERIOD);
    double upTime = PERIOD * PWM;
    double downTime = PERIOD - upTime;
	for(int i = 0; i< numberCycles; i++){
		port |= (1 << enablePin) | (1 << directionPin);
		_delay_ms(upTime);
		port &= ~(1 << enablePin);
		_delay_ms(downTime);
	}
}