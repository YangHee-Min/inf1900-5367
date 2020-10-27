#define F_CPU 8000000UL
#define __DELAY_BACKWARD_COMPATIBLE__
#define MAX_AMOUNT_CYCLES 255

#include <avr/io.h>
#include <util/delay.h>

uint8_t conversionPourcentage(uint8_t pourcentage){
    uint8_t pwm = 0;
    switch(pourcentage){
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

void ajustementPWM(uint8_t pourcentage){
    if(pourcentage > 100){
        pourcentage = 100;
    }
    OCR1A = conversionPourcentage(pourcentage);
    OCR1B = conversionPourcentage(pourcentage);
    // division d'horloge par 8 - implique une frequence de PWM fixe
    TCCR1A |= (1 << COM1A1) | (1 << COM1B1) | (1 << WGM10);
    TCCR1B |= (1 << CS11);
    TCCR1C = 0;
}

int main()
{
    //Entree
    DDRD = 0xFF; 
    PORTD |= (1 << PORTD3) | (1 << PORTD6);

    //Initialiser timer
    TCNT1 = 0;

    // int amountOfCyclesPerSecond = F_CPU / MAX_AMOUNT_CYCLES;
    // int totalAmountOfSeconds = amountOfCyclesPerSecond * 2;
    // for(int pwmPresent = 0; pwmPresent <= 100; pwmPresent += 25){
    //     for(int i = 0; i <= totalAmountOfSeconds; i++){
    //         ajustementPWM(pwmPresent);
    //     }
    // }

    for(;;){
        ajustementPWM(0);
        _delay_ms(2000);
        ajustementPWM(25);
        _delay_ms(2000);
        ajustementPWM(50);
        _delay_ms(2000);
        ajustementPWM(75);
        _delay_ms(2000);
        ajustementPWM(100);
        _delay_ms(2000);
    }
}