#define F_CPU 8000000UL
#define __DELAY_BACKWARD_COMPATIBLE__
#include <avr/io.h>
#include <util/delay.h>

void turnMotorPWM(double PWM, double frequence, uint8_t direction){
	const int ON = direction;
	const int OFF = 0;
	const double PERIOD = 1/frequence * 1000; 

	int numberCycles = 2000/(PERIOD); 
	for(int i = 0; i< numberCycles; i++){ 
		PORTB = ON;
		double upTime = PERIOD * PWM; 
		_delay_ms(upTime);
		PORTB = OFF;
        double downTime = PERIOD - upTime;
		_delay_ms(downTime); 
	}
}


void cycleThroughPWMs(double frequence, uint8_t direction){
    const double INITIAL_PWM = 0; // percentage min pwm
    const double MAX_PWM = 1; // percentage max pwm
    const double PWM_FACTOR = 0.25; // percentage to add each time
    for(double a = INITIAL_PWM; a <= MAX_PWM; a+= PWM_FACTOR){
        turnMotorPWM(a, frequence, direction);
    }
}



int main()
{
    // define ports
    DDRB = 0xff; // PORT A est en mode sortie

    //_delay_ms (double __us)
    const double F1 = 60;
    const double F2 = 400;

    //define directions
    const uint8_t CLOCKWISE = 1;
    const uint8_t C_CLOCKWISE = 3;

    for(;;)
    {   
        cycleThroughPWMs(F1,CLOCKWISE);
        cycleThroughPWMs(F2,C_CLOCKWISE);
    }
}