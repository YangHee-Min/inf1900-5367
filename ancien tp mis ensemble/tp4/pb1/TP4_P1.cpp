#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>
#include <avr/interrupt.h>


const uint8_t DEBOUNCE_DELAY = 30;  
enum Etat {INIT, VERTE, ROUGE};
volatile Etat etat = INIT;
volatile Etat etatSuivant;

void initialisation (){
    cli();
    DDRA = 0xff; // PORT A est en mode sortie
    DDRB = 0xff; // PORT B est en mode sortie
    DDRC = 0xff; // PORT C est en mode sortie
    DDRD = 0x00; // PORT D est en mode entree
    EIMSK |= (1 << INT0) | (1 << INT1);
    EICRA |= (1 << ISC01) | (1 << ISC00);
    sei ();
}


ISR (INT0_vect){
    _delay_ms(DEBOUNCE_DELAY);
    etat = etatSuivant;
    EIFR |= (1 << INTF0);
}

ISR (INT1_vect){
    _delay_ms(DEBOUNCE_DELAY);
    etat = Etat(etat+1);
    EIFR |= (1 << INTF1);
}

int main()
{   
    initialisation();
    for(;;){
        switch(etat){
        case INIT:
        PORTA = 0;
        etatSuivant = VERTE;
        break;
            
        case VERTE:
        PORTA = 1 << PORTA0;
        etatSuivant = ROUGE;
        break;

        case ROUGE:
        PORTA = 1 << PORTA1;
        etatSuivant = INIT;
        break;
        }
    }
    return 0;
}