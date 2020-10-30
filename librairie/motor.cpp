#include <util/delay.h>
#include "motor.h"

//! Function that changes timer value
void motor::adjustPWM(uint8_t pourcentage, uint8_t ocrnx){
    if(pourcentage > 100){
        pourcentage = 100;
    }
    ocrnx = convertPercentInPWM8BitTimer(pourcentage);
}

//! Function that converts the percentage into a PWM
uint8_t motor::convertPercentInPWM8BitTimer(uint8_t percentage){
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
void motor::turnMotorPWM(double PWM, double frequency, uint8_t direction, double duration, volatile uint8_t& port){

    // Change method to have E and D pins
	const int ON = direction;
	const int OFF = 0;
	const double PERIOD = 1/frequency * 1000; 

	int numberCycles = duration/(PERIOD);
    double upTime = PERIOD * PWM;
    double downTime = PERIOD - upTime;
	for(int i = 0; i< numberCycles; i++){
		port = ON;
		_delay_ms(upTime);
		port = OFF;
		_delay_ms(downTime);
	}
}