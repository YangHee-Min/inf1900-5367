#include <avr/io.h>
#include <util/delay.h>


//! Fonction qui indique si le bouton spécifié est toujours appuyé 
//! après le délai de rebond.
//! \return True si le bouton D2 est appuyé pendant au moins 
//|         10 ms. Faux sinon.
bool buttonIsPressed(uint8_t button, volatile uint8_t& pin){
    const double DELAI_REBOND = 10;
    if (pin & (1 << button)){
        _delay_ms(DELAI_REBOND);
        if (pin & (1 << button)){
              return true;      
        }
    }
    return false;
}

//! Function that turns the wheel for a set duration at a specified frenquency with the PWM
void turnMotorPWM(double PWM, double frequency, uint8_t direction, double duration, volatile uint8_t& pin){
	const int ON = direction;
	const int OFF = 0;
	const double PERIOD = 1/frequency * 1000; 

	int numberCycles = duration/(PERIOD);
    double upTime = PERIOD * PWM;
    double downTime = PERIOD - upTime;
	for(int i = 0; i< numberCycles; i++){
		pin = ON;
		_delay_ms(upTime);
		pin = OFF;
		_delay_ms(downTime);
	}
}
//! Function that makes a DEL blink
void blinking(int del, uint8_t delay, volatile uint8_t& pin){
    int off = 0;
    pin = del;
    _delay_ms(delay);
    pin = off;
}
//! Function that converts the percentage into a PWM
uint8_t convertPercentInPWM8BitTimer(uint8_t percentage){
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
//! Function that changes timer value
void ajustPWM(uint8_t pourcentage, uint8_t ocrnx){
    if(pourcentage > 100){
        pourcentage = 100;
    }
    ocrnx = conversionPourcentage(pourcentage);
}

void initialisationUART (void) {
    // 2400 bauds. Nous vous donnons la valeur des deux
    // premier registres pour vous éviter des complications
    UBRR0H = 0;
    UBRR0L = 0xCF;
    // permettre la réception et la transmission par le UART0
    // UCSR0A = ;
    UCSR0B = (1<<RXEN0) | (1<<TXEN0) ;
    // Format des trames: 8 bits, 1 stop bits, none parity
    UCSR0C = (1 << USBS0) |  (3<<UCSZ00);
}

void transmissionUART ( uint8_t donnee ) {
    while (!(UCSR0A & (1<<UDRE0))){};
    UDR0 = donnee;
}