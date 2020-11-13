#define F_CPU 8000000UL
#define __DELAY_BACKWARD_COMPATIBLE__
#include <avr/io.h>
#include <util/delay.h>

int main()
{
    // define ports
    DDRA = 0xff; // PORT A est en mode sortie

    //_delay_us (double __us)
    
    enum LIGHT{OFF, GREEN, RED};
    const double b = 1000;
    const double MINIMUM_A = 100;
    const double INITIAL_A = 700;
    const double REDUCTION_FACTOR = 100;

    double a = INITIAL_A;
    for(;;)
    {
        PORTA = GREEN;
        _delay_ms(a/2);
        PORTA = RED;
        _delay_ms(a/2);
        PORTA = OFF;
        _delay_ms(b - a);
        a = (a == MINIMUM_A) ? INITIAL_A : a - REDUCTION_FACTOR;   
    }
}